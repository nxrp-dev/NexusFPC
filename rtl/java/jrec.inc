{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2011 by Jonas Maebe,
    members of the Free Pascal development team.

    This file implements support infrastructure for records under the JVM

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

  constructor FpcBaseRecordType.create;
    begin
    end;


  function FpcBaseRecordType.clone: JLObject;
    begin
      result:=inherited;
    end;


  function FpcBaseRecordType.newEmpty: FpcBaseRecordType;
    var
      ctor: _JLRConstructor;
      accessible: boolean;
    begin
      ctor:=_JLClass(JLObject(GetClass)).GetConstructor(nil);
      accessible:=ctor.IsAccessible;
      ctor.SetAccessible(True);
      result:=FpcBaseRecordType(ctor.NewInstance(nil));
      if not accessible then
        ctor.SetAccessible(False);
    end;


  class function FpcBaseRecordType.getOrderedFields: Arr1JLRField;
    { exclude constants and return fields in the order they were declared }
    const
      STATIC = 8;
{$ifdef ANDROID}
    function Sort(unsorted: Arr1JLRField): Arr1JLRField;
      { we need the field order from the compiler, for now use a workaround }
      var
        fields : Arr1JLRField;
        index : longint;
        value : JLObject;
        accessible : boolean;
        lookup : _JUHashTable;
        namelist : Arr1JLString;
        expected : unicodestring;
      begin
        result:=nil;
        lookup:=_JUHashTable.Create;
        fields:=JLClass(Self).GetDeclaredFields;
        index:=0;
        while (index<>length(fields)) and ((fields[index].GetModifiers and STATIC=0) or (fields[index].GetName.ToLowercase<>'fieldorder')) do
          inc(index);
        value:=nil;
        if index<>length(fields) then
          begin
            accessible:=fields[index].IsAccessible;
            fields[index].SetAccessible(true);
            value:=fields[index].Get(nil);
            if not accessible then
              fields[index].SetAccessible(false);
            if not (value is JLString) then
              value:=nil;
          end;
        if value<>nil then
          namelist:=JLString(value).Trim.ToLowercase.Split(',')
        else
          namelist:=nil;
        if length(namelist)=length(unsorted) then
          begin
            for index:=0 to high(namelist) do
              lookup.put(namelist[index].Trim,JLInteger.Create(index));
            setlength(result,length(unsorted));
            index:=0;
            repeat
              value:=lookup.Get(unsorted[index].GetName.ToLowercase);
              if value<>nil then
                result[JLInteger(value).IntValue]:=unsorted[index];
              inc(index);
            until (index=length(unsorted)) or (value=nil);
            if index<>length(unsorted) then
              result:=nil;
          end;
        if length(result)=0 then
          begin
            expected:=unsorted[0].GetName;
            for index:=1 to high(unsorted) do
              expected:=expected+','+unsorted[index].GetName;
            raise JLException.Create(
              'To serialize record '+JLClass(Self).GetSimpleName+' on android add a constant named FieldOrder listing every field in the format "const FieldOrder ='''+expected+'''"');
          end;
      end;
{$endif ANDROID}
    var
      list: Arr1JLRField;
      index,destCount: longint;
    begin
      list:=JLClass(Self).GetDeclaredFields;
      result:=nil;
      setlength(result,length(list));
      destCount:=0;
      for index:=0 to high(list) do
        { exclude constants defined in the record }
        if list[index].GetModifiers and STATIC=0 then
          begin
            result[destCount]:=list[index];
            inc(destCount);
          end;
      setlength(result,destCount);
{$ifdef ANDROID}
      if length(result)>1 then
        result:=sort(result);
{$endif ANDROID}
    end;

