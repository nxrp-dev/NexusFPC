{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ This file helps us determine what size an object would be on a desktop
  platform so that we can produce files and streams from java which
  are byte-identical to those produced on other platforms (a file
  written on any platform should be readable on any other platform). }

function MeasurePrimitive(aClass: JLClass): LongInt;
begin
  Result := 0;
  case shortstring(aClass.GetName) of
    'byte': Result := 1;
    'boolean': Result := 1;
    'short': Result := 2;
    'int': Result := 4;
    'long': Result := 8;
    'char': Result := 2;
    'float': Result := 4;
    'double': Result := 8
  else
    raise JLException.Create(
      'Cannot measure primitive of type ' + aClass.GetName + '.');
  end;
end;

function MeasureEnum(aClass: JLClass): LongInt;
  { we can measure the minimum size of an enum but we do not know the
    actual size because this is affected by the packenum directive,
    for now assume tightly packed (packenum 1) }
var
  FieldList: array of JLRField;
  MinimumSize, Index: LongInt;
  HighEnum: FpcEnumValueObtainable;
  IsAccessible: Boolean;
begin
  FieldList := aClass.GetFields;
  Index := High(FieldList);
  while (Index <> 0) and (FieldList[Index].GetType <> aClass) do
    Dec(Index);
  IsAccessible := FieldList[Index].IsAccessible;
  FieldList[Index].SetAccessible(True);
  HighEnum := FpcEnumValueObtainable(FieldList[Index].Get(aClass));
  if not IsAccessible then
    FieldList[Index].SetAccessible(False);

  Result := 0;
  case Longword(HighEnum.FpcOrdinal) of
    0 .. High(Byte): Result := 1;
    256 .. High(Word): Result := 2
  else
    Result := 4
  end;

  MinimumSize := 1; // assume tightly packed
  if Result < MinimumSize then
    Result := MinimumSize;
end;

function MeasureEnumSet(anObject: JLObject): LongInt;
  { we can measure the minimum size of an enum set but we do not know the
    actual size because this is affected by the packset directive,
    for now assume tightly packed (packset 1) }
var
  EnumSet: JUEnumSet;
  EnumClass: JLClass;
  FieldList: array of JLRField;
  IsAccessible: Boolean;
  Index: LongInt;
  HighEnum: FpcEnumValueObtainable;
  MinimumSize: LongInt;
begin
  EnumSet := JUEnumSet(anObject);
  if EnumSet.IsEmpty then
    EnumSet := EnumSet.ComplementOf(EnumSet);
  EnumClass := EnumSet.Iterator.Next.GetClass;
  FieldList := EnumClass.GetFields;
  Index := High(FieldList);
  while (Index <> 0) and (FieldList[Index].GetType <> EnumClass) do
    Dec(Index);
  IsAccessible := FieldList[Index].IsAccessible;
  FieldList[Index].SetAccessible(True);
  HighEnum := FpcEnumValueObtainable(FieldList[Index].Get(EnumClass));
  if not IsAccessible then
    FieldList[Index].SetAccessible(False);

  Result := 0;
  case Longword(HighEnum.FpcOrdinal) of
    0 .. 7: Result := 1;
    8 .. 15: Result := 2;
    16 .. 31: Result := 4;
    32 .. 63: Result := 8;
    64 .. 127: Result := 16;
    128 .. 255: Result := 32
  else
    raise JLException.Create(
      'Cannot measure enum set of ' + EnumClass.GetName + '.');
  end;

  MinimumSize := 1; // assume tightly packed
  if Result < MinimumSize then
    Result := MinimumSize;
end;

function MeasureShortstring(aShortstring: ShortstringClass): LongInt;
begin
  Result := Length(aShortstring.FData) + SizeOf(aShortstring.CurLen);
end;

function MeasureAnsistring(anAnsistring: AnsistringClass): LongInt;
begin
  Result := 0;
  if anAnsistring <> nil then
    Result := anAnsistring.Length;
end;

function MeasureUnicodestring(aUnicodestring: JLString): LongInt;
begin
  Result := 0;
  if aUnicodestring <> nil then
    Result := aUnicodestring.Length * SizeOf(WideChar);
end;

function MeasureObject(anObject: JLObject): LongInt; forward;

function GetIsPointerType(
  anEmptyRecord: JLObject;
  aField: JLRField): Boolean;
  { Dynamic arrays and some pointers use the same java type as fixed length arrays.
    A record, shortstring or set has the exact same java type as its pointer.
    To know for certain if we are dealing with a pointer type we can check
    whether the compiler initialises the field to nil for a new empty record. }
var
  FieldType: JLClass;
  IsAccessible: Boolean;
begin
  FieldType := aField.GetType;
  Result := False;
  if
    ( not FieldType.IsPrimitive ) and
    ( not JLClass(JLEnum).IsAssignableFrom(FieldType) ) then
  begin
    IsAccessible := aField.IsAccessible;
    aField.SetAccessible(True);
    Result := (aField.Get(anEmptyRecord) = nil);
    if not IsAccessible then
      aField.SetAccessible(False);
  end;
end;

function MeasureRecordField(
  aRecord: JLObject;
  aField: JLRField;
  anIsPointerType: Boolean): LongInt;
var
  FieldValue: JLObject;
  IsAccessible: Boolean;
begin
  Result := 0;
  if anIsPointerType then
    Result := SizeOf(Pointer)
  else if aField.GetType.IsPrimitive then
    Result := MeasurePrimitive(aField.GetType)
  else
  begin
    IsAccessible := aField.IsAccessible;
    aField.SetAccessible(True);
    FieldValue := aField.Get(aRecord);
    if not IsAccessible then
      aField.SetAccessible(False);
    Result := MeasureObject(FieldValue);
  end;

  if Result = 0 then
    raise JLException.Create(
      'Cannot determine the size of field ' + aRecord.GetClass.GetName + '.' +  aField.GetName);
end;

function MeasureRecord(aRecord: FpcBaseRecordType): LongInt;
var
  Field: JLRField;
  EmptyRecord: FpcBaseRecordType;
  IsPointerType: Boolean;
begin
  Result := 0;
  EmptyRecord := aRecord.NewEmpty;
  for Field in aRecord.GetOrderedFields do
  begin
    IsPointerType := GetIsPointerType(EmptyRecord, Field);
    Result := Result + MeasureRecordField(aRecord, Field, IsPointerType);
  end;
end;

function MeasureArray(anArray: JLObject): LongInt;
var
  ComponentType: JLClass;
  ItemSize: LongInt;
begin
  ComponentType := anArray.GetClass.GetComponentType;

  if ComponentType.IsPrimitive then
    ItemSize := MeasurePrimitive(ComponentType)
  else
    ItemSize := MeasureObject(Arr1JLObject(anArray)[0]);

  Result := JLRArray.GetLength(anArray) * ItemSize;
end;

{ JVM Notes:
  * We cannot determine the size of a bitset.
  * We can measure the minimum size of an enum or enum set, but we do not know the
    actual size because this is affected by the packenum and packset directives.
  * The compiler wraps all integer types as JLLong instead of JLByte, JLShort or
    JLInteger so the reported size may be incorrect.
  * Dynamic arrays and some pointers map to the same java type as fixed length
    arrays. We cannot tell them apart so we assume we are measuring a fixed length array.
  * A record, shortstring or set has the exact same java type as its pointer. We
    cannot tell them apart so we assume we are measuring the non-pointer type. }
function MeasureObject(anObject: JLObject): LongInt;
begin
  Result := 0;
  if anObject = nil then
    Result := SizeOf(Pointer)
  else if anObject.GetClass.IsPrimitive then
    Result := MeasurePrimitive(anObject.GetClass)
  else if anObject.GetClass.IsArray then
    Result := MeasureArray(anObject)
  else if anObject is JLEnum then
    Result := MeasureEnum(anObject.GetClass)
  else if anObject is ShortstringClass then
    Result := MeasureShortstring(ShortstringClass(anObject))
  else if anObject is AnsistringClass then
    Result := MeasureAnsistring(AnsistringClass(anObject))
  else if anObject is JLString then
    Result := MeasureUnicodestring(JLString(anObject))
  else if anObject is JUEnumSet then
    Result := MeasureEnumSet(JUEnumSet(anObject))
  else if anObject is JUBitSet then
    raise JLException.Create(
      'Cannot measure a bit set of type ' + anObject.GetClass.GetName + '.')
  else if anObject is FpcBaseRecordType then
    Result := MeasureRecord(FpcBaseRecordType(anObject))
  else if anObject is JLByte then
    Result := SizeOf(Byte)
  else if anObject is JLShort then
    Result := SizeOf(Word)
  else if anObject is JLInteger then
    Result := SizeOf(Longword)
  else if anObject is JLLong then
    Result := SizeOf(QWord)
  else if anObject is JLCharacter then
    Result := SizeOf(WideChar)
  else if anObject is JLFloat then
    Result := SizeOf(Single)
  else if anObject is JLDouble then
    Result := SizeOf(Double)
  else if anObject is JLBoolean then
    Result := SizeOf(Boolean)
  else
    Result := SizeOf(Pointer);
end;
