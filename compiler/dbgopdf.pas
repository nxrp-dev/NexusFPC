{
    Copyright (c) 2025 by Graeme Geldenhuys

    This unit contains OPDF debug format support for the FPC compiler.
    OPDF (Object Pascal Debug Format) is an alternative to DWARF and STABS.

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
  cclasses, classes,
  sysutils,
  aasmtai, aasmdata,
  systems,
  symbase,symconst,symtype,symdef,symsym,
  fmodule,
  globtype,
  DbgBase,
  tpdf_type_mapper,
  ogopdf, opdf_io, opdf_demangle;

type
  { OPDF Debug Format Writer }
  TOPDFDebugWriter = class(TDebugInfo)
  private
    { Type mapper for allocating type IDs }
    FTypeMapper: TTypeMapper;
    { OPDF writer for binary output }
    FWriter: TOPDFWriter;
    { Output stream for OPDF file }
    FStream: TStream;
  protected
    { Mark types used by all variables in a symbol table }
    procedure MarkVariableTypesUsed(st: TSymtable);

    { Initialize output stream }
    procedure SetOutputStream(AStream: TStream);

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

constructor TOPDFDebugWriter.Create;
begin
  inherited Create;
  FTypeMapper := TTypeMapper.Create;
  FWriter := nil; { Will be created when output file is opened }
  FStream := nil;
end;

destructor TOPDFDebugWriter.Destroy;
begin
  if assigned(FWriter) then
    FWriter.Free;
  FTypeMapper.Free;
  { Note: FStream is owned by caller, don't free here }
  inherited Destroy;
end;

procedure TOPDFDebugWriter.MarkVariableTypesUsed(st: TSymtable);
var
  i: Longint;
  def: TDef;
begin
  if not assigned(st) or not assigned(st.DefList) then
    Exit;

  { For OPDF Phase 1E, mark all types in DefList as used so they get collected }
  { This is appropriate for collecting debug information }
  for i := 0 to st.DefList.Count - 1 do
  begin
    def := TDef(st.DefList[i]);
    if assigned(def) and (def.dbg_state = dbg_state_unused) then
      def.dbg_state := dbg_state_used;
  end;
end;

procedure TOPDFDebugWriter.SetOutputStream(AStream: TStream);
var
  Arch: TTargetArch;
  PointerSize: Byte;
begin
  FStream := AStream;

  { Determine target architecture }
  if target_cpu = cpu_x86_64 then
    Arch := archX86_64
  else if target_cpu = cpu_i386 then
    Arch := archI386
  else if target_cpu = cpu_arm then
    Arch := archARM
  else if target_cpu = cpu_aarch64 then
    Arch := archAArch64
  else
    Arch := archUnknown;

  { Determine pointer size based on target }
  PointerSize := 8; { Default to 64-bit }
  if target_cpu = cpu_i386 then
    PointerSize := 4
  else if target_cpu = cpu_arm then
    PointerSize := 4;

  { Create the OPDF writer }
  FWriter := TOPDFWriter.Create(FStream, Arch, PointerSize);

  { Write the header }
  if assigned(FWriter) then
    FWriter.WriteHeader;
end;

{ Type definition handlers - Phase 1E+ implementation }

procedure TOPDFDebugWriter.appenddef_ord(list: TAsmList; def: TOrdDef);
var
  TypeID: Cardinal;
  TypeName: String;
  Size: Integer;
  IsSigned: Boolean;
begin
  if not assigned(def) or not assigned(FWriter) then
    Exit;

  { Get or allocate TypeID }
  TypeID := FTypeMapper.GetTypeID(def);

  { Determine type name }
  TypeName := def.GetTypeName;

  { Get size in bytes }
  Size := def.size;
  if Size < 1 then
    Size := 1; { Fallback for unknown sizes }

  { Determine signedness based on ordtype }
  IsSigned := False;
  case def.ordtype of
    s8bit, s16bit, s32bit, s64bit, s128bit: IsSigned := True;
    else IsSigned := False;
  end;

  { Write primitive type to OPDF }
  FWriter.WritePrimitive(TypeID, TypeName, Size, IsSigned);
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
  TypeID: Cardinal;
  VarName: String;
  Address: QWord;
begin
  if not assigned(sym) or not assigned(FWriter) or not assigned(sym.vardef) then
    Exit;

  { Skip external variables (their addresses are resolved at link time) }
  if vo_is_external in sym.varoptions then
    Exit;

  { Get the variable's type ID }
  TypeID := FTypeMapper.GetTypeID(sym.vardef);

  { Get the variable name }
  VarName := sym.name;

  { Address 0 - the debugger resolves real addresses using symbol names }
  Address := 0;

  { Write the global variable to OPDF }
  FWriter.WriteGlobalVar(VarName, TypeID, Address);
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
  OPDFFilename: String;
  DummyList: TAsmList;
  i: longint;
  def: tdef;
begin
  { Initialize the output stream BEFORE collecting types }
  if FStream = nil then
  begin
    if assigned(current_module) then
    begin
      OPDFFilename := ChangeFileExt(current_module.objfilename, '.opdf');
      try
        FStream := TFileStream.Create(OPDFFilename, fmCreate);
        SetOutputStream(FStream);
      except
        on E: Exception do
        begin
          WriteLn('Warning: Could not create OPDF file ', OPDFFilename);
          WriteLn('Error: ', E.Message);
          Exit;
        end;
      end;
    end
    else
      Exit; { No module, can't proceed }
  end;

  { Initialize base class lists required by inherited write_symtable_* methods }
  defnumberlist := TFPObjectList.Create(false);
  deftowritelist := TFPObjectList.Create(false);

  { Collect and write all types and symbols }
  DummyList := TAsmList.create;
  try
    { Write types from used units }
    write_used_unit_type_info(DummyList, current_module);

    { Write types from global symbol table }
    if assigned(current_module.globalsymtable) then
      write_symtable_defs(DummyList, current_module.globalsymtable);

    { Write types from local symbol table }
    if assigned(current_module.localsymtable) then
      write_symtable_defs(DummyList, current_module.localsymtable);

    { Write symbols (variables) from global symbol table }
    if assigned(current_module.globalsymtable) then
      write_symtable_syms(DummyList, current_module.globalsymtable);

    { Write symbols (variables) from local symbol table }
    if assigned(current_module.localsymtable) then
      write_symtable_syms(DummyList, current_module.localsymtable);
  finally
    DummyList.Free;
  end;

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
  { Finalize the OPDF output }
  if assigned(FWriter) then
    FWriter.Finalize;
end;

initialization
  RegisterDebugInfo(dbg_opdf_info, TOPDFDebugWriter);

end.
