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
  cclasses,
  aasmtai, aasmdata,
  systems,
  symbase,symconst,symtype,symdef,symsym,
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

constructor TOPDFDebugWriter.Create;
begin
  inherited Create;
  FTypeMapper := TTypeMapper.Create;
  FWriter := nil; { Will be created when output file is opened }
end;

destructor TOPDFDebugWriter.Destroy;
begin
  if assigned(FWriter) then
    FWriter.Free;
  FTypeMapper.Free;
  inherited Destroy;
end;

{ Type definition handlers - Phase 1D stubs }

procedure TOPDFDebugWriter.appenddef_ord(list: TAsmList; def: TOrdDef);
begin
  { Phase 1E: Implement ordinal type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_float(list: TAsmList; def: TFloatDef);
begin
  { Phase 1E: Implement float type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_enum(list: TAsmList; def: TEnumDef);
begin
  { Phase 1E: Implement enumeration type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_array(list: TAsmList; def: TArrayDef);
begin
  { Phase 2C: Implement array type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_record(list: TAsmList; def: TRecordDef);
begin
  { Phase 3A: Implement record type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_object(list: TAsmList; def: TObjectDef);
begin
  { Phase 3B: Implement class type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_pointer(list: TAsmList; def: TPointerDef);
begin
  { Phase 2B: Implement pointer type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_string(list: TAsmList; def: TStringDef);
begin
  { Phase 2A: Implement string type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_procvar(list: TAsmList; def: TProcVarDef);
begin
  { Phase 4A: Implement procedural type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_variant(list: TAsmList; def: TVariantDef);
begin
  { Phase 2A: Implement variant type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_set(list: TAsmList; def: TSetDef);
begin
  { Phase 2A: Implement set type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_file(list: TAsmList; def: TFileDef);
begin
  { Phase 2A: Implement file type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_formal(list: TAsmList; def: TFormalDef);
begin
  { Phase 2A: Implement formal type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

procedure TOPDFDebugWriter.appenddef_undefined(list: TAsmList; def: TUndefinedDef);
begin
  { Phase 2A: Implement undefined type mapping }
  if assigned(def) then
    FTypeMapper.GetTypeID(def);
end;

{ Symbol handlers - Phase 1D stubs }

procedure TOPDFDebugWriter.appendsym_staticvar(list: TAsmList; sym: TStaticVarSym);
begin
  { Phase 4A: Implement static variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_paravar(list: TAsmList; sym: TParaVarSym);
begin
  { Phase 4A: Implement parameter variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_localvar(list: TAsmList; sym: TLocalVarSym);
begin
  { Phase 4A: Implement local variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_fieldvar(list: TAsmList; sym: TFieldVarSym);
begin
  { Phase 3A: Implement field variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_const(list: TAsmList; sym: TConstSym);
begin
  { Phase 2A: Implement constant symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_type(list: TAsmList; sym: TTypeSym);
begin
  { Phase 1D: Implement type symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_label(list: TAsmList; sym: TLabelSym);
begin
  { Phase 4A: Implement label symbol mapping }
end;

procedure TOPDFDebugWriter.appendsym_absolute(list: TAsmList; sym: TAbsoluteVarSym);
begin
  { Phase 2A: Implement absolute variable mapping }
end;

procedure TOPDFDebugWriter.appendsym_property(list: TAsmList; sym: TPropertySym);
begin
  { Phase 3C: Implement property mapping }
end;

{ Main entry points }

procedure TOPDFDebugWriter.inserttypeinfo;
begin
  { Phase 1E: Write collected type information to OPDF }
  { For now, this is a stub. Type info is collected during appenddef_* calls }
end;

procedure TOPDFDebugWriter.insertmoduleinfo;
begin
  { Phase 1E: Write module information and finalize OPDF }
  { For now, this is a stub. Module info will be written when compilation completes }
end;

initialization
  RegisterDebugInfo(dbg_opdf_info, TOPDFDebugWriter);

end.
