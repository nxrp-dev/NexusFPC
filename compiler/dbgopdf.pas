{
    Copyright (c) 2025 by Graeme Geldenhuys

    This unit contains OPDF debug format support for the FPC compiler.
    OPDF (Object Pascal Debug Format) is an alternative to DWARF and STABS.

    Debug data is emitted into an asm list (al_opdf) which produces an
    .opdf ELF section in the final binary. This follows the same pattern
    used by DWARF (dbgdwarf.pas) for label-based address resolution.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 ****************************************************************************
}
unit dbgopdf;

{$i fpcdefs.inc}

interface

uses
  cclasses,
  aasmbase, aasmtai, aasmdata,
  systems,
  symbase, symconst, symtype, symdef, symsym,
  fmodule,
  globtype,
  DbgBase,
  tpdf_type_mapper;

type
  { OPDF Debug Format Writer - emits debug data into asm list }
  TOPDFDebugWriter = class(TDebugInfo)
  private
    { Type mapper for allocating type IDs }
    FTypeMapper: TTypeMapper;

    { Emit helpers - write raw bytes into asm list }
    procedure EmitByte(list: TAsmList; value: Byte);
    procedure EmitWord(list: TAsmList; value: Word);
    procedure EmitDWord(list: TAsmList; value: Cardinal);
    procedure EmitQWord(list: TAsmList; value: QWord);
    procedure EmitString(list: TAsmList; const S: AnsiString);
    procedure EmitRecordHeader(list: TAsmList; recType: Byte; recSize: Cardinal);
    procedure EmitOPDFHeader(list: TAsmList);
  protected
    { Override TDebugInfo virtual methods for type definitions }
    procedure appenddef_ord(list: TAsmList; def: TOrdDef); override;
    procedure appenddef_float(list: TAsmList; def: TFloatDef); override;
    procedure appenddef_enum(list: TAsmList; def: TEnumDef); override;
    procedure appenddef_array(list: TAsmList; def: TArrayDef); override;
    procedure appenddef_record(list: TAsmList; def: TRecordDef); override;
    procedure appenddef_object(list: TAsmList; def: TObjectDef); override;
    procedure appenddef_pointer(list: TAsmList; def: TPointerDef); override;
    procedure appenddef_string(list: TAsmList; def: TStringDef); override;
    procedure appenddef_procvar(list: TAsmList; def: TProcVarDef); override;
    procedure appenddef_variant(list: TAsmList; def: TVariantDef); override;
    procedure appenddef_set(list: TAsmList; def: TSetDef); override;
    procedure appenddef_file(list: TAsmList; def: TFileDef); override;
    procedure appenddef_formal(list: TAsmList; def: TFormalDef); override;
    procedure appenddef_undefined(list: TAsmList; def: TUndefinedDef); override;

    { Override TDebugInfo virtual methods for symbols }
    procedure appendsym_staticvar(list: TAsmList; sym: TStaticVarSym); override;
    procedure appendsym_paravar(list: TAsmList; sym: TParaVarSym); override;
    procedure appendsym_localvar(list: TAsmList; sym: TLocalVarSym); override;
    procedure appendsym_fieldvar(list: TAsmList; sym: TFieldVarSym); override;
    procedure appendsym_const(list: TAsmList; sym: TConstSym); override;
    procedure appendsym_type(list: TAsmList; sym: TTypeSym); override;
    procedure appendsym_label(list: TAsmList; sym: TLabelSym); override;
    procedure appendsym_absolute(list: TAsmList; sym: TAbsoluteVarSym); override;
    procedure appendsym_property(list: TAsmList; sym: TPropertySym); override;
  public
    constructor Create; override;
    destructor Destroy; override;

    { Main OPDF entry points }
    procedure inserttypeinfo; override;
    procedure insertmoduleinfo; override;
  end;

  { OPDF debug format info record }
  const dbg_opdf_info : tdbginfo =
    (
      id     : dbg_opdf;
      idtxt  : 'OPDF'
    );

implementation

{ OPDF format constants - must match ogopdf.pas definitions }
const
  OPDF_MAGIC_0 = Ord('O');
  OPDF_MAGIC_1 = Ord('P');
  OPDF_MAGIC_2 = Ord('D');
  OPDF_MAGIC_3 = Ord('F');
  OPDF_VERSION  = 1;

  { Record types - must match TOPDFRecordType in ogopdf.pas }
  REC_PRIMITIVE  = 1;
  REC_GLOBALVAR  = 2;

{ Emit helpers }

procedure TOPDFDebugWriter.EmitByte(list: TAsmList; value: Byte);
begin
  list.concat(tai_const.Create_8bit(value));
end;

procedure TOPDFDebugWriter.EmitWord(list: TAsmList; value: Word);
begin
  list.concat(tai_const.Create_16bit_unaligned(value));
end;

procedure TOPDFDebugWriter.EmitDWord(list: TAsmList; value: Cardinal);
begin
  list.concat(tai_const.Create_32bit_unaligned(longint(value)));
end;

procedure TOPDFDebugWriter.EmitQWord(list: TAsmList; value: QWord);
begin
  { Emit as two 32-bit values in little-endian order }
  list.concat(tai_const.Create_32bit_unaligned(longint(value and $FFFFFFFF)));
  list.concat(tai_const.Create_32bit_unaligned(longint(value shr 32)));
end;

procedure TOPDFDebugWriter.EmitString(list: TAsmList; const S: AnsiString);
var
  i: longint;
begin
  for i := 1 to Length(S) do
    list.concat(tai_const.Create_8bit(Ord(S[i])));
end;

procedure TOPDFDebugWriter.EmitRecordHeader(list: TAsmList; recType: Byte; recSize: Cardinal);
begin
  EmitByte(list, recType);
  EmitDWord(list, recSize);
end;

procedure TOPDFDebugWriter.EmitOPDFHeader(list: TAsmList);
var
  ArchByte: Byte;
  PtrSize: Byte;
  i: longint;
begin
  { Magic: 'OPDF' (4 bytes) }
  EmitByte(list, OPDF_MAGIC_0);
  EmitByte(list, OPDF_MAGIC_1);
  EmitByte(list, OPDF_MAGIC_2);
  EmitByte(list, OPDF_MAGIC_3);

  { Version (2 bytes) }
  EmitWord(list, OPDF_VERSION);

  { BuildID: 16 zero bytes (not needed for embedded sections) }
  for i := 1 to 16 do
    EmitByte(list, 0);

  { Target architecture (1 byte) }
{$if defined(cpu64bitaddr)}
  ArchByte := 2; { archX86_64 }
  PtrSize := 8;
{$elseif defined(cpu32bitaddr)}
  ArchByte := 1; { archI386 }
  PtrSize := 4;
{$else}
  ArchByte := 0; { archUnknown }
  PtrSize := 4;
{$endif}
  EmitByte(list, ArchByte);

  { Pointer size (1 byte) }
  EmitByte(list, PtrSize);

  { TotalRecords: 0 = stream-terminated mode (4 bytes) }
  EmitDWord(list, 0);

  { Flags: reserved (4 bytes) }
  EmitDWord(list, 0);
end;

{ Constructor / Destructor }

constructor TOPDFDebugWriter.Create;
begin
  inherited Create;
  FTypeMapper := TTypeMapper.Create;
end;

destructor TOPDFDebugWriter.Destroy;
begin
  FTypeMapper.Free;
  inherited Destroy;
end;

{ Type definition handlers }

procedure TOPDFDebugWriter.appenddef_ord(list: TAsmList; def: TOrdDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TypeName: AnsiString;
  Size: Integer;
  IsSigned: Byte;
  NameLen: Word;
  RecSize: Cardinal;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  { Get or allocate TypeID }
  TypeID := FTypeMapper.GetTypeID(def);

  { Determine type name }
  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  { Get size in bytes }
  Size := def.size;
  if Size < 1 then
    Size := 1;

  { Determine signedness }
  IsSigned := 0;
  case def.ordtype of
    s8bit, s16bit, s32bit, s64bit, s128bit:
      IsSigned := 1;
    else
      IsSigned := 0;
  end;

  { Record payload: TypeID(4) + SizeInBytes(1) + IsSigned(1) + NameLen(2) + Name(variable) }
  RecSize := 4 + 1 + 1 + 2 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_PRIMITIVE, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitByte(opdflist, Byte(Size));
  EmitByte(opdflist, IsSigned);
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);
end;

procedure TOPDFDebugWriter.appenddef_float(list: TAsmList; def: TFloatDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_enum(list: TAsmList; def: TEnumDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_array(list: TAsmList; def: TArrayDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_record(list: TAsmList; def: TRecordDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_object(list: TAsmList; def: TObjectDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_pointer(list: TAsmList; def: TPointerDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_string(list: TAsmList; def: TStringDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_procvar(list: TAsmList; def: TProcVarDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_variant(list: TAsmList; def: TVariantDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_set(list: TAsmList; def: TSetDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_file(list: TAsmList; def: TFileDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_formal(list: TAsmList; def: TFormalDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_undefined(list: TAsmList; def: TUndefinedDef);
begin
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

{ Symbol handlers }

procedure TOPDFDebugWriter.appendsym_staticvar(list: TAsmList; sym: TStaticVarSym);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  VarName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
begin
  if not assigned(sym) or not assigned(sym.vardef) then
    Exit;

  { Skip external variables }
  if vo_is_external in sym.varoptions then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  { Get the variable's type ID }
  TypeID := FTypeMapper.GetTypeID(sym.vardef);

  { Use mangled name for the variable }
  VarName := sym.mangledname;
  NameLen := Word(Length(VarName));

  { Record payload: TypeID(4) + Address(8) + NameLen(2) + Name(variable) }
  RecSize := 4 + 8 + 2 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_GLOBALVAR, RecSize);
  EmitDWord(opdflist, TypeID);

  { Emit address as a symbol reference - linker resolves the actual address }
  opdflist.concat(tai_const.Create_type_sym(aitconst_ptr_unaligned,
    current_asmdata.RefAsmSymbol(sym.mangledname, AT_DATA)));

  EmitWord(opdflist, NameLen);
  EmitString(opdflist, VarName);
end;

procedure TOPDFDebugWriter.appendsym_paravar(list: TAsmList; sym: TParaVarSym);
begin
  { TODO: Implement parameter variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_localvar(list: TAsmList; sym: TLocalVarSym);
begin
  { TODO: Implement local variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_fieldvar(list: TAsmList; sym: TFieldVarSym);
begin
  { TODO: Implement field variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_const(list: TAsmList; sym: TConstSym);
begin
  { TODO: Implement constant symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_type(list: TAsmList; sym: TTypeSym);
begin
  { TODO: Implement type symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_label(list: TAsmList; sym: TLabelSym);
begin
  { TODO: Implement label symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_absolute(list: TAsmList; sym: TAbsoluteVarSym);
begin
  { TODO: Implement absolute variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_property(list: TAsmList; sym: TPropertySym);
begin
  { TODO: Implement property mapping }
end;

{ Main entry points }

procedure TOPDFDebugWriter.inserttypeinfo;
var
  opdflist: TAsmList;
  i: longint;
  def: tdef;
begin
  { Get the OPDF asm list }
  opdflist := current_asmdata.asmlists[al_opdf];

  { Create the .opdf section }
  new_section(opdflist, sec_user, '.opdf', 0);

  { Emit OPDF file header }
  EmitOPDFHeader(opdflist);

  { Initialize base class lists required by inherited write_symtable_* methods }
  defnumberlist := TFPObjectList.Create(false);
  deftowritelist := TFPObjectList.Create(false);

  { Write types from used units }
  write_used_unit_type_info(opdflist, current_module);

  { Write types from global symbol table }
  if assigned(current_module.globalsymtable) then
    write_symtable_defs(opdflist, current_module.globalsymtable);

  { Write types from local symbol table }
  if assigned(current_module.localsymtable) then
    write_symtable_defs(opdflist, current_module.localsymtable);

  { Write symbols (variables) from global symbol table }
  if assigned(current_module.globalsymtable) then
    write_symtable_syms(opdflist, current_module.globalsymtable);

  { Write symbols (variables) from local symbol table }
  if assigned(current_module.localsymtable) then
    write_symtable_syms(opdflist, current_module.localsymtable);

  { Reset dbg_state on all tracked defs so they can be reused }
  for i := 0 to defnumberlist.count - 1 do
  begin
    def := tdef(defnumberlist[i]);
    if assigned(def) then
      def.dbg_state := dbg_state_unused;
  end;

  defnumberlist.free;
  defnumberlist := nil;
  deftowritelist.free;
  deftowritelist := nil;
end;

procedure TOPDFDebugWriter.insertmoduleinfo;
begin
  { Nothing to do - data is in asm list, handled by assembler }
end;

initialization
  RegisterDebugInfo(dbg_opdf_info, TOPDFDebugWriter);

end.
