{
    Copyright (c) 2025 by Graeme Geldenhuys

    This unit contains the type mapping functionality for OPDF debug format.
    Maps FPC's type definitions (TDef hierarchy) to OPDF type records.

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
unit tpdf_type_mapper;

{$i fpcdefs.inc}

interface

uses
  cclasses,
  symdef;

type
  { Type ID mapping entry }
  PTypeMapEntry = ^TTypeMapEntry;
  TTypeMapEntry = record
    Def: TDef;
    TypeID: Word;
  end;

  { Type ID allocator for OPDF debug format }
  TTypeMapper = class
  private
    { Array of type mappings }
    FTypeMap: array of TTypeMapEntry;
    { Current number of entries in map }
    FTypeCount: Word;
    { Allocated capacity of array }
    FCapacity: Word;
    { Next available type ID }
    FNextTypeID: Word;

    { Expand the type map array }
    procedure Expand;
  public
    constructor Create;
    destructor Destroy; override;

    { Get or allocate a unique TypeID for a definition }
    function GetTypeID(Def: TDef): Word;

    { Check if a type has already been registered }
    function HasType(Def: TDef): Boolean;

    { Get total number of types registered }
    function GetTypeCount: Word;

    { Reset all type mappings }
    procedure Clear;
  end;

implementation

const
  INITIAL_CAPACITY = 256;
  EXPAND_FACTOR = 2;

constructor TTypeMapper.Create;
begin
  inherited Create;
  FTypeCount := 0;
  FCapacity := INITIAL_CAPACITY;
  FNextTypeID := 1; { Start TypeIDs from 1; 0 is reserved for "no type" }
  SetLength(FTypeMap, FCapacity);
end;

destructor TTypeMapper.Destroy;
begin
  SetLength(FTypeMap, 0);
  inherited Destroy;
end;

procedure TTypeMapper.Expand;
var
  NewCapacity: Word;
begin
  if FCapacity >= $7FFF then
    NewCapacity := $7FFF
  else
    NewCapacity := FCapacity * EXPAND_FACTOR;

  SetLength(FTypeMap, NewCapacity);
  FCapacity := NewCapacity;
end;

function TTypeMapper.HasType(Def: TDef): Boolean;
var
  I: Word;
begin
  Result := False;
  if (Def = nil) or (FTypeCount = 0) then
    Exit;

  for I := 0 to FTypeCount - 1 do
    begin
      if FTypeMap[I].Def = Def then
        begin
          Result := True;
          Exit;
        end;
    end;
end;

function TTypeMapper.GetTypeID(Def: TDef): Word;
var
  I: Word;
begin
  if Def = nil then
    begin
      Result := 0;
      Exit;
    end;

  { Quick check: already in map? }
  for I := 0 to FTypeCount - 1 do
    begin
      if FTypeMap[I].Def = Def then
        begin
          Result := FTypeMap[I].TypeID;
          Exit;
        end;
    end;

  { Allocate new TypeID }
  if FTypeCount >= FCapacity then
    Expand;

  if FNextTypeID >= High(Word) then
    begin
      { Exhausted TypeID space - very rare }
      WriteLn('Warning: Type ID space exhausted.');
      Result := High(Word);
    end
  else
    begin
      FTypeMap[FTypeCount].Def := Def;
      FTypeMap[FTypeCount].TypeID := FNextTypeID;
      Result := FNextTypeID;
      Inc(FTypeCount);
      Inc(FNextTypeID);
    end;
end;

function TTypeMapper.GetTypeCount: Word;
begin
  Result := FTypeCount;
end;

procedure TTypeMapper.Clear;
begin
  FTypeCount := 0;
  FNextTypeID := 1;
  SetLength(FTypeMap, FCapacity);
end;

end.
