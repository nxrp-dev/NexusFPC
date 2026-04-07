{
    Copyright (c) 2025 by Graeme Geldenhuys

    This unit contains the type mapping functionality for OPDF debug format.
    Maps FPC's type definitions (TDef hierarchy) to OPDF type records.

    Cross-unit type deduplication uses mangled type names (like DWARF) rather
    than tdef pointer comparison, because PPU loading creates new tdef
    instances for each compilation unit.

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
      { type ID mapping entry — used for pointer-based cache }
      PTypeMapEntry=^TTypeMapEntry;
      TTypeMapEntry=record
        Def    : tdef;
        TypeID : Cardinal;
      end;

      { type ID allocator for OPDF debug format }
      TTypeMapper=class
      private
        { pointer-based cache for fast within-unit lookups }
        FPtrMap     : array of TTypeMapEntry;
        FPtrCount   : Longint;
        FPtrCapacity: Longint;
        { name-based map for cross-unit dedup (key=mangled name, val=TypeID) }
        FNameMap    : TFPHashList;
        { next available type ID }
        FNextTypeID : Cardinal;

        { expand the pointer cache array }
        procedure ExpandPtrMap;
        { build a name-based key for cross-unit dedup; empty for anonymous types }
        function GetTypeKey(def:tdef):AnsiString;
        { add entry to pointer cache }
        procedure AddToPtrCache(def:tdef;typeid:Cardinal);
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

    uses
      cutils;

    const
      INITIAL_CAPACITY = 256;
      EXPAND_FACTOR    = 2;

    function FNV1aHash(const S: AnsiString): Cardinal;
    const
      FNV_OFFSET_BASIS = Cardinal(2166136261);
      FNV_PRIME        = Cardinal(16777619);
    var
      I: Integer;
    begin
      Result := FNV_OFFSET_BASIS;
      for I := 1 to Length(S) do
      begin
        Result := Result xor Ord(S[I]);
        Result := Result * FNV_PRIME;
      end;
      if Result = 0 then
        Result := 1;  { reserve 0 for "no type" }
    end;


    constructor TTypeMapper.Create;
      begin
        inherited Create;
        FPtrCount:=0;
        FPtrCapacity:=INITIAL_CAPACITY;
        FNextTypeID:=$F0000000; { fallback sequential range for anonymous types without names }
        SetLength(FPtrMap,FPtrCapacity);
        FNameMap:=TFPHashList.Create;
      end;


    destructor TTypeMapper.Destroy;
      begin
        SetLength(FPtrMap,0);
        FNameMap.Free;
        inherited Destroy;
      end;


    procedure TTypeMapper.ExpandPtrMap;
      var
        newcapacity : Longint;
      begin
        newcapacity:=FPtrCapacity*EXPAND_FACTOR;
        if newcapacity<FPtrCapacity then
          newcapacity:=MaxInt; { overflow protection }
        SetLength(FPtrMap,newcapacity);
        FPtrCapacity:=newcapacity;
      end;


    function TTypeMapper.GetTypeKey(def:tdef):AnsiString;
      var
        elemkey : AnsiString;
        setdef  : tsetdef;
      begin
        result:='';
        if not assigned(def) then
          exit;
        { named types: use mangled name for globally unique key }
        if assigned(def.typesym) and assigned(def.typesym.owner) then
          begin
            result:=make_mangledname('',def.typesym.owner,def.typesym.RealName);
            exit;
          end;
        { Anonymous compound types whose element type is named: derive a
          stable structural key so identical compound types declared inline
          across different units dedup to a single OPDF type record. Truly
          anonymous compounds (e.g. set of an anonymous enum) fall through
          and are allocated sequentially by GetTypeID. }
        if def is tsetdef then
          begin
            setdef:=tsetdef(def);
            elemkey:=GetTypeKey(setdef.elementdef);
            if elemkey<>'' then
              result:='set:'+elemkey+':'+
                      tostr(setdef.setbase)+':'+
                      tostr(setdef.setmax)+':'+
                      tostr(setdef.size);
          end;
      end;


    procedure TTypeMapper.AddToPtrCache(def:tdef;typeid:Cardinal);
      begin
        if FPtrCount>=FPtrCapacity then
          ExpandPtrMap;
        FPtrMap[FPtrCount].Def:=def;
        FPtrMap[FPtrCount].TypeID:=typeid;
        inc(FPtrCount);
      end;


    function TTypeMapper.HasType(Def:tdef):Boolean;
      var
        i   : Longint;
        key : AnsiString;
      begin
        result:=false;
        if Def=nil then
          exit;

        key:=GetTypeKey(def);
        if key<>'' then
          begin
            { named type: check name-based map only }
            {$push}{$warn 6058 off}
            result:=FNameMap.Find(key)<>nil;
            {$pop}
          end
        else
          begin
            { anonymous type: check pointer cache }
            for i:=0 to FPtrCount-1 do
              if FPtrMap[i].Def=Def then
                begin
                  result:=true;
                  exit;
                end;
          end;
      end;


    function TTypeMapper.GetTypeID(Def:tdef):Cardinal;
      var
        i   : Longint;
        key : AnsiString;
        p   : Pointer;
      begin
        if Def=nil then
          begin
            result:=0;
            exit;
          end;

        { build name-based key; non-empty for named types }
        key:=GetTypeKey(def);

        if key<>'' then
          begin
            { named type: use name-based map exclusively.
              Do NOT use pointer cache — stale pointers from previous
              units can match unrelated types due to memory reuse. }
            {$push}{$warn 6058 off}
            p:=FNameMap.Find(key);
            {$pop}
            if p<>nil then
              begin
                result:=Cardinal(PtrUInt(p));
                exit;
              end;

            { allocate new TypeID via FNV-1a hash of canonical name }
            result:=FNV1aHash(key);
            FNameMap.Add(key,Pointer(PtrUInt(result)));
          end
        else
          begin
            { anonymous type: use pointer-based lookup (unit-local only) }
            for i:=0 to FPtrCount-1 do
              if FPtrMap[i].Def=Def then
                begin
                  result:=FPtrMap[i].TypeID;
                  exit;
                end;

            { allocate new TypeID sequentially from the reserved range.
              Anonymous types have no stable identity beyond their declaration
              site, so hashing GetTypeName is unsafe — distinct anonymous sets,
              arrays or records routinely share display names like
              "Set Of <enumeration type>" or "Array Of LongInt", which would
              collide and (via TypeAlreadyEmitted's TypeID-keyed dedup) cause
              the second type's record to be silently dropped. The pointer
              cache above guarantees within-unit dedup for the same tdef. }
            result:=FNextTypeID;
            inc(FNextTypeID);
            AddToPtrCache(def,result);
          end;
      end;


    function TTypeMapper.GetTypeCount:Longint;
      begin
        { total unique TypeIDs: named types in FNameMap + anonymous types in FPtrCache }
        result:=FNameMap.Count+FPtrCount;
      end;


    procedure TTypeMapper.Clear;
      begin
        FPtrCount:=0;
        FNextTypeID:=$F0000000;
        SetLength(FPtrMap,FPtrCapacity);
        FNameMap.Clear;
      end;


end.
