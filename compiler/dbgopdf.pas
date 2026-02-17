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
  finput,
  fmodule,
  globtype,
  cgbase,
  defutil,
  DbgBase,
  tpdf_type_mapper;

type
  { OPDF Debug Format Writer - emits debug data into asm list }
  TOPDFDebugWriter = class(TDebugInfo)
  private
    { Type mapper for allocating type IDs }
    FTypeMapper: TTypeMapper;

    { Accumulated line info records from insertlineinfo calls.
      These are collected per-procedure and merged into al_opdf
      during inserttypeinfo, after the section header is emitted. }
    FLineInfoList: TAsmList;

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

    { Override proc definition handler for function scope records }
    procedure appendprocdef(list: TAsmList; def: TProcDef); override;
  public
    constructor Create; override;
    destructor Destroy; override;

    { Main OPDF entry points }
    procedure inserttypeinfo; override;
    procedure insertmoduleinfo; override;
    procedure insertlineinfo(list: TAsmList); override;
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
  REC_PRIMITIVE      = 1;
  REC_GLOBALVAR      = 2;
  REC_SHORTSTR       = 3;
  REC_ANSISTR        = 4;
  REC_UNICODESTR     = 5;
  REC_POINTER        = 6;
  REC_ARRAY          = 7;
  REC_RECORD         = 8;
  REC_CLASS          = 9;
  REC_LOCALVAR       = 12;
  REC_PARAMETER      = 13;
  REC_LINEINFO       = 14;
  REC_FUNCSCOPE      = 15;
  REC_INTERFACE      = 16;
  REC_ENUM           = 17;

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
  FLineInfoList := TAsmList.Create;
end;

destructor TOPDFDebugWriter.Destroy;
begin
  FLineInfoList.Free;
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
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TypeName: AnsiString;
  Size: Integer;
  NameLen: Word;
  RecSize: Cardinal;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  Size := def.size;
  if Size < 1 then
    Size := 1;

  { All float types are signed }
  RecSize := 4 + 1 + 1 + 2 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_PRIMITIVE, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitByte(opdflist, Byte(Size));
  EmitByte(opdflist, 1); { IsSigned = 1 for all floats }
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);
end;

procedure TOPDFDebugWriter.appenddef_enum(list: TAsmList; def: TEnumDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  MemberCount: Cardinal;
  hp: TEnumSym;
  MemberName: AnsiString;
  MemberNameLen: Word;
  i: Longint;
begin
  if not assigned(def) then
    Exit;
  if not assigned(def.symtable) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  { Count members in range }
  MemberCount := 0;
  for i := 0 to def.symtable.SymList.Count - 1 do
  begin
    hp := TEnumSym(def.symtable.SymList[i]);
    if (hp.value >= def.minval) and (hp.value <= def.maxval) then
      Inc(MemberCount);
  end;

  { Calculate record size: TypeID(4) + SizeInBytes(1) + MemberCount(4) + NameLen(2) + Name }
  RecSize := 4 + 1 + 4 + 2 + Cardinal(NameLen);
  { Add member sizes: Value(8) + MemberNameLen(2) + MemberName per member }
  for i := 0 to def.symtable.SymList.Count - 1 do
  begin
    hp := TEnumSym(def.symtable.SymList[i]);
    if (hp.value >= def.minval) and (hp.value <= def.maxval) then
      RecSize := RecSize + 8 + 2 + Cardinal(Length(hp.RealName));
  end;

  EmitRecordHeader(opdflist, REC_ENUM, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitByte(opdflist, Byte(def.size));
  EmitDWord(opdflist, MemberCount);
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);

  { Emit enum members }
  for i := 0 to def.symtable.SymList.Count - 1 do
  begin
    hp := TEnumSym(def.symtable.SymList[i]);
    if (hp.value >= def.minval) and (hp.value <= def.maxval) then
    begin
      EmitQWord(opdflist, QWord(hp.value));
      MemberName := hp.RealName;
      MemberNameLen := Word(Length(MemberName));
      EmitWord(opdflist, MemberNameLen);
      EmitString(opdflist, MemberName);
    end;
  end;
end;

procedure TOPDFDebugWriter.appenddef_array(list: TAsmList; def: TArrayDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  ElemTypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  IsDyn: Boolean;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  { Get element type ID }
  if assigned(def.elementdef) then
    ElemTypeID := FTypeMapper.GetTypeID(def.elementdef)
  else
    ElemTypeID := 0;

  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  IsDyn := is_dynamic_array(def);

  { REC_ARRAY: TypeID(4) + ElementTypeID(4) + Dimensions(1) + IsDynamic(1) + NameLen(2) + Name }
  { For static arrays, add bounds: LowerBound(8) + UpperBound(8) per dimension }
  RecSize := 4 + 4 + 1 + 1 + 2 + Cardinal(NameLen);
  if not IsDyn then
    RecSize := RecSize + 16; { One dimension: LowerBound(8) + UpperBound(8) }

  EmitRecordHeader(opdflist, REC_ARRAY, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitDWord(opdflist, ElemTypeID);
  EmitByte(opdflist, 1); { Dimensions: always 1 for Pascal arrays }
  if IsDyn then
    EmitByte(opdflist, 1)
  else
    EmitByte(opdflist, 0);
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);

  { Write bounds for static arrays }
  if not IsDyn then
  begin
    EmitQWord(opdflist, QWord(def.lowrange));
    EmitQWord(opdflist, QWord(def.highrange));
  end;
end;

procedure TOPDFDebugWriter.appenddef_record(list: TAsmList; def: TRecordDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  FieldCount: Cardinal;
  FieldTypeID: Cardinal;
  FieldName: AnsiString;
  FieldNameLen: Word;
  i: Longint;
  sym: TSym;
  fvsym: TFieldVarSym;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  { Get record name }
  if assigned(def.objrealname) then
    TypeName := def.objrealname^
  else
    TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  { Count non-static fields }
  FieldCount := 0;
  if assigned(def.symtable) then
    for i := 0 to def.symtable.SymList.Count - 1 do
    begin
      sym := TSym(def.symtable.SymList[i]);
      if (sym.typ = fieldvarsym) and
         not (sp_static in sym.symoptions) then
        Inc(FieldCount);
    end;

  { Calculate record size }
  { Header: TypeID(4) + FieldCount(4) + TotalSize(4) + NameLen(2) + Name }
  RecSize := 4 + 4 + 4 + 2 + Cardinal(NameLen);
  { Fields: FieldTypeID(4) + Offset(4) + FieldNameLen(2) + FieldName per field }
  if assigned(def.symtable) then
    for i := 0 to def.symtable.SymList.Count - 1 do
    begin
      sym := TSym(def.symtable.SymList[i]);
      if (sym.typ = fieldvarsym) and
         not (sp_static in sym.symoptions) then
        RecSize := RecSize + 4 + 4 + 2 + Cardinal(Length(sym.RealName));
    end;

  EmitRecordHeader(opdflist, REC_RECORD, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitDWord(opdflist, FieldCount);
  EmitDWord(opdflist, Cardinal(def.size));
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);

  { Emit field descriptors }
  if assigned(def.symtable) then
    for i := 0 to def.symtable.SymList.Count - 1 do
    begin
      sym := TSym(def.symtable.SymList[i]);
      if (sym.typ = fieldvarsym) and
         not (sp_static in sym.symoptions) then
      begin
        fvsym := TFieldVarSym(sym);

        if assigned(fvsym.vardef) then
          FieldTypeID := FTypeMapper.GetTypeID(fvsym.vardef)
        else
          FieldTypeID := 0;

        FieldName := fvsym.RealName;
        FieldNameLen := Word(Length(FieldName));

        EmitDWord(opdflist, FieldTypeID);
        EmitDWord(opdflist, Cardinal(fvsym.fieldoffset));
        EmitWord(opdflist, FieldNameLen);
        EmitString(opdflist, FieldName);
      end;
    end;
end;

procedure TOPDFDebugWriter.appenddef_object(list: TAsmList; def: TObjectDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  ParentTypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  FieldCount: Cardinal;
  FieldTypeID: Cardinal;
  FieldName: AnsiString;
  FieldNameLen: Word;
  i: Longint;
  sym: TSym;
  fvsym: TFieldVarSym;
  IntfTypeByte: Byte;
  MethodCount: Cardinal;
  psym: TProcsym;
  pdef: TProcDef;
  MtdName: AnsiString;
  MtdNameLen: Word;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  { Get parent type ID }
  if assigned(def.childof) then
    ParentTypeID := FTypeMapper.GetTypeID(def.childof)
  else
    ParentTypeID := 0;

  { Get type name }
  if assigned(def.objrealname) then
    TypeName := def.objrealname^
  else
    TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  case def.objecttype of
    odt_interfacecom, odt_interfacecorba, odt_dispinterface:
      begin
        { Emit REC_INTERFACE }

        { Determine interface type }
        case def.objecttype of
          odt_interfacecom:   IntfTypeByte := 0; { COM }
          odt_interfacecorba: IntfTypeByte := 1; { CORBA }
          odt_dispinterface:  IntfTypeByte := 2; { Dispatch }
          else                IntfTypeByte := 0;
        end;

        { Count methods (procsym entries) }
        MethodCount := 0;
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if sym.typ = procsym then
              Inc(MethodCount);
          end;

        { Calculate record size }
        { TypeID(4) + ParentTypeID(4) + IntfType(1) + GUID(16) + MethodCount(4) + NameLen(2) + Name }
        RecSize := 4 + 4 + 1 + 16 + 4 + 2 + Cardinal(NameLen);
        { Methods: ReturnTypeID(4) + ParamCount(1) + MtdNameLen(2) + MtdName per method }
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if sym.typ = procsym then
              RecSize := RecSize + 4 + 1 + 2 + Cardinal(Length(sym.RealName));
          end;

        EmitRecordHeader(opdflist, REC_INTERFACE, RecSize);
        EmitDWord(opdflist, TypeID);
        EmitDWord(opdflist, ParentTypeID);
        EmitByte(opdflist, IntfTypeByte);

        { Emit GUID - 16 bytes }
        if assigned(def.iidguid) then
        begin
          EmitDWord(opdflist, def.iidguid^.D1);
          EmitWord(opdflist, def.iidguid^.D2);
          EmitWord(opdflist, def.iidguid^.D3);
          for i := 0 to 7 do
            EmitByte(opdflist, def.iidguid^.D4[i]);
        end
        else
        begin
          { Null GUID: 16 zero bytes }
          for i := 0 to 15 do
            EmitByte(opdflist, 0);
        end;

        EmitDWord(opdflist, MethodCount);
        EmitWord(opdflist, NameLen);
        EmitString(opdflist, TypeName);

        { Emit method descriptors }
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if sym.typ = procsym then
            begin
              psym := TProcsym(sym);
              { Use the first procdef for return type and param count }
              if psym.ProcdefList.Count > 0 then
              begin
                pdef := TProcDef(psym.ProcdefList[0]);
                if assigned(pdef.returndef) and not is_void(pdef.returndef) then
                  EmitDWord(opdflist, FTypeMapper.GetTypeID(pdef.returndef))
                else
                  EmitDWord(opdflist, 0);
                EmitByte(opdflist, Byte(pdef.paras.Count));
              end
              else
              begin
                EmitDWord(opdflist, 0);
                EmitByte(opdflist, 0);
              end;

              MtdName := sym.RealName;
              MtdNameLen := Word(Length(MtdName));
              EmitWord(opdflist, MtdNameLen);
              EmitString(opdflist, MtdName);
            end;
          end;
      end;

    odt_class, odt_object:
      begin
        { Emit REC_CLASS }

        { Count non-static fields }
        FieldCount := 0;
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if (sym.typ = fieldvarsym) and
               not (sp_static in sym.symoptions) then
              Inc(FieldCount);
          end;

        { Calculate record size }
        { TypeID(4) + ParentTypeID(4) + VMTAddress(8) + InstanceSize(4) + FieldCount(4) + NameLen(2) + Name }
        RecSize := 4 + 4 + 8 + 4 + 4 + 2 + Cardinal(NameLen);
        { Fields: FieldTypeID(4) + Offset(4) + FieldNameLen(2) + FieldName per field }
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if (sym.typ = fieldvarsym) and
               not (sp_static in sym.symoptions) then
              RecSize := RecSize + 4 + 4 + 2 + Cardinal(Length(sym.RealName));
          end;

        EmitRecordHeader(opdflist, REC_CLASS, RecSize);
        EmitDWord(opdflist, TypeID);
        EmitDWord(opdflist, ParentTypeID);
        EmitQWord(opdflist, 0); { VMTAddress: 0 placeholder }
        EmitDWord(opdflist, Cardinal(def.size));
        EmitDWord(opdflist, FieldCount);
        EmitWord(opdflist, NameLen);
        EmitString(opdflist, TypeName);

        { Emit field descriptors }
        if assigned(def.symtable) then
          for i := 0 to def.symtable.SymList.Count - 1 do
          begin
            sym := TSym(def.symtable.SymList[i]);
            if (sym.typ = fieldvarsym) and
               not (sp_static in sym.symoptions) then
            begin
              fvsym := TFieldVarSym(sym);

              if assigned(fvsym.vardef) then
                FieldTypeID := FTypeMapper.GetTypeID(fvsym.vardef)
              else
                FieldTypeID := 0;

              FieldName := fvsym.RealName;
              FieldNameLen := Word(Length(FieldName));

              EmitDWord(opdflist, FieldTypeID);
              EmitDWord(opdflist, Cardinal(fvsym.fieldoffset));
              EmitWord(opdflist, FieldNameLen);
              EmitString(opdflist, FieldName);
            end;
          end;
      end;

    else
      { Other object types (ObjC, Java, etc.) - just register type ID }
      ;
  end;
end;

procedure TOPDFDebugWriter.appenddef_pointer(list: TAsmList; def: TPointerDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TargetTypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  { Resolve target type - 0 for void pointers }
  if is_voidpointer(def) then
    TargetTypeID := 0
  else if assigned(def.pointeddef) then
    TargetTypeID := FTypeMapper.GetTypeID(def.pointeddef)
  else
    TargetTypeID := 0;

  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  { REC_POINTER: TypeID(4) + TargetTypeID(4) + NameLen(2) + Name }
  RecSize := 4 + 4 + 2 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_POINTER, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitDWord(opdflist, TargetTypeID);
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, TypeName);
end;

procedure TOPDFDebugWriter.appenddef_string(list: TAsmList; def: TStringDef);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  TypeName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
begin
  if not assigned(def) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(def);

  TypeName := def.GetTypeName;
  NameLen := Word(Length(TypeName));

  case def.stringtype of
    st_shortstring:
      begin
        { REC_SHORTSTR: TypeID(4) + MaxLength(1) + NameLen(2) + Name }
        RecSize := 4 + 1 + 2 + Cardinal(NameLen);
        EmitRecordHeader(opdflist, REC_SHORTSTR, RecSize);
        EmitDWord(opdflist, TypeID);
        EmitByte(opdflist, Byte(def.len and $FF));
        EmitWord(opdflist, NameLen);
        EmitString(opdflist, TypeName);
      end;
    st_ansistring:
      begin
        { REC_ANSISTR: TypeID(4) + NameLen(2) + Name }
        RecSize := 4 + 2 + Cardinal(NameLen);
        EmitRecordHeader(opdflist, REC_ANSISTR, RecSize);
        EmitDWord(opdflist, TypeID);
        EmitWord(opdflist, NameLen);
        EmitString(opdflist, TypeName);
      end;
    st_unicodestring, st_widestring:
      begin
        { REC_UNICODESTR: TypeID(4) + NameLen(2) + Name }
        RecSize := 4 + 2 + Cardinal(NameLen);
        EmitRecordHeader(opdflist, REC_UNICODESTR, RecSize);
        EmitDWord(opdflist, TypeID);
        EmitWord(opdflist, NameLen);
        EmitString(opdflist, TypeName);
      end;
    else
      { st_longstring or other: just register type ID }
      ;
  end;
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
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  ParamName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  IsVar, IsConst, IsOut: Byte;
begin
  if not assigned(sym) or not assigned(sym.vardef) then
    Exit;

  { Skip the hidden self/vmt/result parameters }
  if vo_is_hidden_para in sym.varoptions then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(sym.vardef);

  ParamName := sym.RealName;
  NameLen := Word(Length(ParamName));

  { Determine var/const/out flags }
  IsVar := 0;
  IsConst := 0;
  IsOut := 0;
  case sym.varspez of
    vs_var:
      IsVar := 1;
    vs_out:
      IsOut := 1;
    vs_const, vs_constref:
      IsConst := 1;
    else
      ; { vs_value, vs_final }
  end;

  { REC_PARAMETER: TypeID(4) + IsVar(1) + IsConst(1) + IsOut(1) + NameLen(2) + Name }
  RecSize := 4 + 1 + 1 + 1 + 2 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_PARAMETER, RecSize);
  EmitDWord(opdflist, TypeID);
  EmitByte(opdflist, IsVar);
  EmitByte(opdflist, IsConst);
  EmitByte(opdflist, IsOut);
  EmitWord(opdflist, NameLen);
  EmitString(opdflist, ParamName);
end;

procedure TOPDFDebugWriter.appendsym_localvar(list: TAsmList; sym: TLocalVarSym);
var
  opdflist: TAsmList;
  TypeID: Cardinal;
  VarName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  StackOffset: Longint;
  FuncName: AnsiString;
begin
  if not assigned(sym) or not assigned(sym.vardef) then
    Exit;

  { Only handle reference-based locations (stack variables) }
  if not (sym.localloc.loc in [LOC_REFERENCE, LOC_CREFERENCE]) then
    Exit;

  opdflist := current_asmdata.asmlists[al_opdf];

  TypeID := FTypeMapper.GetTypeID(sym.vardef);

  VarName := sym.RealName;
  NameLen := Word(Length(VarName));

  StackOffset := sym.localloc.reference.offset;

  { Clamp offset to ShortInt range }
  if StackOffset > 127 then
    StackOffset := 127
  else if StackOffset < -128 then
    StackOffset := -128;

  { REC_LOCALVAR: TypeID(4) + ScopeID(4) + LocationExpr(1) + NameLen(2) + LocationData(1) + Name }
  RecSize := 4 + 4 + 1 + 2 + 1 + Cardinal(NameLen);

  EmitRecordHeader(opdflist, REC_LOCALVAR, RecSize);
  EmitDWord(opdflist, TypeID);

  { ScopeID: use the owning function's address as scope ID }
  if assigned(sym.owner) and assigned(sym.owner.defowner) and
     (sym.owner.defowner.typ = procdef) then
  begin
    FuncName := TProcDef(sym.owner.defowner).mangledname;
    opdflist.concat(tai_const.Create_type_sym(aitconst_32bit_unaligned,
      current_asmdata.RefAsmSymbol(FuncName, AT_FUNCTION)));
  end
  else
    EmitDWord(opdflist, 0);

  EmitByte(opdflist, 1); { LocationExpr: 1 = RBP-relative }
  EmitWord(opdflist, NameLen);
  EmitByte(opdflist, Byte(ShortInt(StackOffset))); { LocationData }
  EmitString(opdflist, VarName);
end;

procedure TOPDFDebugWriter.appendsym_fieldvar(list: TAsmList; sym: TFieldVarSym);
begin
  { Fields are emitted inline within record/class records.
    No separate field record is needed. }
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
  { Properties are not emitted as separate records.
    Property access is resolved via field offsets or method addresses
    in the class record. }
end;

procedure TOPDFDebugWriter.appendprocdef(list: TAsmList; def: TProcDef);
var
  opdflist: TAsmList;
  procendlabel: TAsmLabel;
  FuncName: AnsiString;
  NameLen: Word;
  RecSize: Cardinal;
  in_currentunit: Boolean;
begin
  if not assigned(def) then
    Exit;

  in_currentunit := def.in_currentunit;

  { Only write debug info for procedures defined in the current module,
    except for methods }
  if not in_currentunit and
     not (def.owner.symtabletype in [objectsymtable, recordsymtable]) then
    Exit;

  { Skip units without init section }
  if in_currentunit and not assigned(def.procstarttai) then
    Exit;

  { Skip generics }
  if df_generic in def.defoptions then
    Exit;

  { Check if already written }
  if (def.dbg_state in [dbg_state_writing, dbg_state_written]) then
    Exit;
  defnumberlist.Add(def);

  { For methods: only write in scope of their parent objectdef }
  if (def.owner.symtabletype in [objectsymtable, recordsymtable]) then
  begin
    if assigned(def.owner.defowner) and
       (tdef(def.owner.defowner).dbg_state <> dbg_state_writing) then
      Exit;
  end;

  def.dbg_state := dbg_state_writing;

  opdflist := current_asmdata.asmlists[al_opdf];

  FuncName := def.mangledname;
  NameLen := Word(Length(FuncName));

  if in_currentunit then
  begin
    { Create a label for the end of the procedure }
    current_asmdata.getlabel(procendlabel, alt_dbgtype);
    current_asmdata.asmlists[al_procedures].insertbefore(
      tai_label.create(procendlabel), def.procendtai);

    { REC_FUNCSCOPE: ScopeID(4) + LowPC(8) + HighPC(8) + NameLen(2) + Name }
    RecSize := 4 + 8 + 8 + 2 + Cardinal(NameLen);

    EmitRecordHeader(opdflist, REC_FUNCSCOPE, RecSize);

    { ScopeID: emit as placeholder 0 — will use LowPC address as scope ID
      at debug time. Emit the function start address as ScopeID too. }
    opdflist.concat(tai_const.Create_type_sym(aitconst_32bit_unaligned,
      current_asmdata.RefAsmSymbol(FuncName, AT_FUNCTION)));

    { LowPC - function start address }
    opdflist.concat(tai_const.Create_type_sym(aitconst_ptr_unaligned,
      current_asmdata.RefAsmSymbol(FuncName, AT_FUNCTION)));

    { HighPC - function end address }
    opdflist.concat(tai_const.Create_type_sym(aitconst_ptr_unaligned,
      procendlabel));

    EmitWord(opdflist, NameLen);
    EmitString(opdflist, FuncName);
  end;

  { Write parameter symbols }
  if assigned(def.paras) then
    write_symtable_parasyms(opdflist, def.paras);

  { Write local variable symbols }
  if in_currentunit and
     assigned(def.localst) and
     (def.localst.symtabletype = localsymtable) then
    write_symtable_syms(opdflist, def.localst);

  { Write local type definitions }
  if assigned(def.parast) then
    write_symtable_defs(opdflist, def.parast);
  if in_currentunit and
     assigned(def.localst) and
     (def.localst.symtabletype = localsymtable) then
    write_symtable_defs(opdflist, def.localst);

  def.dbg_state := dbg_state_written;
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

  { Write procedure definitions (function scopes, locals, params) }
  if assigned(current_module.globalsymtable) then
    write_symtable_procdefs(opdflist, current_module.globalsymtable);
  if assigned(current_module.localsymtable) then
    write_symtable_procdefs(opdflist, current_module.localsymtable);

  { Reset dbg_state on all tracked defs so they can be reused }
  for i := 0 to defnumberlist.count - 1 do
  begin
    def := tdef(defnumberlist[i]);
    if assigned(def) then
      def.dbg_state := dbg_state_unused;
  end;

  { Append accumulated line info records (collected during insertlineinfo calls) }
  opdflist.concatList(FLineInfoList);

  defnumberlist.free;
  defnumberlist := nil;
  deftowritelist.free;
  deftowritelist := nil;
end;

procedure TOPDFDebugWriter.insertlineinfo(list: TAsmList);
var
  currfileinfo,
  lastfileinfo : tfileposinfo;
  currsectype  : TAsmSectiontype;
  hp           : tai;
  infile       : tinputfile;
  currlabel    : tasmlabel;
  nolineinfolevel : Integer;
  FileName     : AnsiString;
  FileNameLen  : Word;
  RecSize      : Cardinal;
begin
  FillChar(lastfileinfo, sizeof(lastfileinfo), 0);
  currsectype := sec_code;
  nolineinfolevel := 0;

  hp := Tai(list.first);
  while assigned(hp) do
  begin
    case hp.typ of
      ait_section:
        currsectype := tai_section(hp).sectype;
      ait_force_line:
        lastfileinfo.line := -1;
      ait_marker:
        begin
          case tai_marker(hp).kind of
            mark_NoLineInfoStart:
              inc(nolineinfolevel);
            mark_NoLineInfoEnd:
              dec(nolineinfolevel);
            else
              ;
          end;
        end;
      else
        ;
    end;

    if (currsectype = sec_code) and
       (hp.typ = ait_instruction) then
    begin
      currfileinfo := tailineinfo(hp).fileinfo;

      { Set line to 0 for code without line info }
      if nolineinfolevel > 0 then
        currfileinfo.line := 0;

      { Emit a record when file or line changes }
      if (currfileinfo.fileindex <> 0) and
         (currfileinfo.line <> 0) and
         ((lastfileinfo.line <> currfileinfo.line) or
          (lastfileinfo.fileindex <> currfileinfo.fileindex) or
          (lastfileinfo.moduleindex <> currfileinfo.moduleindex)) then
      begin
        { Create a label at this instruction for address resolution }
        current_asmdata.getlabel(currlabel, alt_dbgline);
        list.insertbefore(tai_label.create(currlabel), hp);

        { Resolve source file name }
        infile := get_module(currfileinfo.moduleindex).sourcefiles.get_file(currfileinfo.fileindex);
        if assigned(infile) then
        begin
          FileName := infile.path + infile.name;
          FileNameLen := Word(Length(FileName));

          { Record payload: Address(8) + LineNumber(4) + ColumnNumber(2) + FileNameLen(2) + FileName }
          RecSize := 8 + 4 + 2 + 2 + Cardinal(FileNameLen);

          { Write to FLineInfoList — merged into al_opdf during inserttypeinfo }
          EmitRecordHeader(FLineInfoList, REC_LINEINFO, RecSize);

          { Address - linker resolves the label to final address }
          FLineInfoList.concat(tai_const.Create_type_sym(aitconst_ptr_unaligned, currlabel));

          { LineNumber (4 bytes) }
          EmitDWord(FLineInfoList, Cardinal(currfileinfo.line));

          { ColumnNumber (2 bytes) }
          EmitWord(FLineInfoList, currfileinfo.column);

          { FileNameLen + FileName }
          EmitWord(FLineInfoList, FileNameLen);
          EmitString(FLineInfoList, FileName);
        end;

        lastfileinfo := currfileinfo;
      end;
    end;

    hp := tai(hp.next);
  end;
end;

procedure TOPDFDebugWriter.insertmoduleinfo;
begin
  { Nothing to do - data is in asm list, handled by assembler }
end;

initialization
  RegisterDebugInfo(dbg_opdf_info, TOPDFDebugWriter);

end.
