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
unit dbgopdf_typemap;

{$i fpcdefs.inc}

interface

    uses
      cclasses,
      symdef,
      symtype;

    type
      { type ID mapping entry }
      PTypeMapEntry=^TTypeMapEntry;
      TTypeMapEntry=record
        Def    : tdef;
        TypeID : Cardinal;
      end;

      { type ID allocator for OPDF debug format }
      TTypeMapper=class
      private
        { array of type mappings }
        FTypeMap    : array of TTypeMapEntry;
        { current number of entries in map }
        FTypeCount  : Longint;
        { allocated capacity of array }
        FCapacity   : Longint;
        { next available type ID }
        FNextTypeID : Cardinal;

        { expand the type map array }
        procedure Expand;
      public
        constructor Create;
        destructor Destroy;override;

        { get or allocate a unique TypeID for a definition }
        function GetTypeID(Def:tdef):Cardinal;

        { check if a type has already been registered }
        function HasType(Def:tdef):Boolean;

        { get total number of types registered }
        function GetTypeCount:Longint;

        { reset all type mappings }
        procedure Clear;
      end;

implementation

    const
      INITIAL_CAPACITY = 256;
      EXPAND_FACTOR    = 2;


    constructor TTypeMapper.Create;
      begin
        inherited Create;
        FTypeCount:=0;
        FCapacity:=INITIAL_CAPACITY;
        FNextTypeID:=1; { start TypeIDs from 1; 0 is reserved for "no type" }
        SetLength(FTypeMap,FCapacity);
      end;


    destructor TTypeMapper.Destroy;
      begin
        SetLength(FTypeMap,0);
        inherited Destroy;
      end;


    procedure TTypeMapper.Expand;
      var
        newcapacity : Longint;
      begin
        newcapacity:=FCapacity*EXPAND_FACTOR;
        if newcapacity<FCapacity then
          newcapacity:=MaxInt; { overflow protection }
        SetLength(FTypeMap,newcapacity);
        FCapacity:=newcapacity;
      end;


    function TTypeMapper.HasType(Def:tdef):Boolean;
      var
        i : Longint;
      begin
        result:=false;
        if (Def=nil) or (FTypeCount=0) then
          exit;
        for i:=0 to FTypeCount-1 do
          begin
            if FTypeMap[i].Def=Def then
              begin
                result:=true;
                exit;
              end;
          end;
      end;


    function TTypeMapper.GetTypeID(Def:tdef):Cardinal;
      var
        i : Longint;
      begin
        if Def=nil then
          begin
            result:=0;
            exit;
          end;

        { quick check: already in map? }
        if FTypeCount>0 then
          for i:=0 to FTypeCount-1 do
            begin
              if FTypeMap[i].Def=Def then
                begin
                  result:=FTypeMap[i].TypeID;
                  exit;
                end;
            end;

        { allocate new TypeID }
        if FTypeCount>=FCapacity then
          Expand;

        FTypeMap[FTypeCount].Def:=Def;
        FTypeMap[FTypeCount].TypeID:=FNextTypeID;
        result:=FNextTypeID;
        inc(FTypeCount);
        inc(FNextTypeID);
      end;


    function TTypeMapper.GetTypeCount:Longint;
      begin
        result:=FTypeCount;
      end;


    procedure TTypeMapper.Clear;
      begin
        FTypeCount:=0;
        FNextTypeID:=1;
        SetLength(FTypeMap,FCapacity);
      end;


end.
