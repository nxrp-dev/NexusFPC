{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ This file helps us to convert an object into a form which is
  convenient to feed into a serializer. A primitive is placed
  in an array so we can use it as a reference type. Other types
  may be converted into a record or an array of bytes. We undo
  this conversion when we return the object back to java. }

function WrapEnumSet(anEnumSet: JLObject; aSize: LongInt): JLObject;
var
  Iterator: JUIterator;
  Index: LongInt;
  BitIndex: LongInt;
  JByteArray: Arr1JByte;
begin
  Iterator := JUEnumSet(anEnumSet).Iterator;

  JByteArray := nil;
  SetLength(JByteArray, aSize);

  BitIndex := -1;
  if Iterator.HasNext then
    BitIndex := FpcEnumValueObtainable(Iterator.Next).FpcOrdinal;

  while (BitIndex <> -1) and (BitIndex < aSize * 8) do
  begin
    Index := BitIndex div 8;
    JByteArray[Index] :=
      JByte( ( Byte(JByteArray[Index]) ) or ( 1 shl ( BitIndex mod 8 ) ) );
    BitIndex := -1;
    if Iterator.HasNext then
      BitIndex := FpcEnumValueObtainable(Iterator.Next).FpcOrdinal;
  end;

  Result := AsObject(JByteArray);
end;

function UnwrapEnumSet(Wrapped: JLObject; Original: JUEnumSet): JLObject;
var
  EnumType: FpcEnumValueObtainable;
  Enum: JLEnum;
  EnumOrdinal: LongInt;
  Iterator: JUIterator;
  Index: LongInt;
  BitIndex: LongInt;
  JByteArray: Arr1JByte;
  Mask: Byte;
begin
  JByteArray := Arr1JByte(Wrapped);
  Original.Clear;
  EnumType := FpcEnumValueObtainable(JUEnumSet.ComplementOf(Original).Iterator.Next);

  Index := 0;
  while Index <> Length(JByteArray) do
  begin
    if JByteArray[Index] <> 0 then
      for BitIndex := 0 to 7 do
      begin
        Mask := ( 1 shl BitIndex );
        if JByteArray[Index] and Mask <> 0 then
        begin
          EnumOrdinal := (Index * 8) + BitIndex;
          Enum := EnumType.FpcGenericValueOf(EnumOrdinal);
          Original.Add(Enum);
        end;
      end;
    Inc(Index);
  end;

  Result := Original;
end;

function WrapBitSet(aBitSet: JLObject; aSize: LongInt): JLObject;
var
  BitSet: FpcBitSet;
  Index: LongInt;
  BitIndex: LongInt;
  Size: LongInt;
  JByteArray: Arr1JByte;
begin
  JByteArray := nil;
  SetLength(JByteArray, aSize);
  BitSet := FpcBitSet(aBitSet);
  BitIndex := BitSet.NextSetBit(0);
  while (BitIndex <> -1) and (BitIndex < aSize * 8) do
  begin
    Index := BitIndex div 8;
    JByteArray[Index] :=
      JByte( ( Byte(JByteArray[Index]) ) or ( 1 shl ( BitIndex mod 8 ) ) );
    BitIndex := BitSet.NextSetBit(BitIndex + 1);
  end;
  Result := AsObject(JByteArray);
end;

function UnwrapBitSet(Wrapped: JLObject; Original: FpcBitSet): JLObject;
var
  BitSet: FpcBitSet;
  Index: LongInt;
  BitIndex: LongInt;
  JByteArray: Arr1JByte;
  Mask: Byte;
begin
  JByteArray := Arr1JByte(Wrapped);
  Original := FpcBitSet(Original.Clone);
  Original.Clear;
  Index := 0;
  while Index <> Length(JByteArray) do
  begin
    if JByteArray[Index] <> 0 then
      for BitIndex := 0 to 7 do
      begin
        Mask := ( 1 shl BitIndex );
        if JByteArray[Index] and Mask <> 0 then
          Original.Add((Index * 8) + BitIndex);
      end;
    Inc(Index);
  end;
  Result := Original;
end;

type
  ShortstringRec = record
    Len: Byte;
    { the dynamic array of chars is wrapped in a fixed length array so the
      serializer will treat it as a stack based type instead of a pointer type }
    Chars: array[0 .. 0] of TAnsiCharArray;
{$ifdef ANDROID}
  const
    FieldOrder='Len,Chars';
{$endif ANDROID}
  end;

function WrapShortstring(aShortstring: JLObject): JLObject;
var
  Rec: ShortstringRec;
begin
  Rec.Len := ShortstringClass(aShortstring).CurLen;
  Rec.Chars[0] := ShortstringClass(aShortstring).FData;
  Result := AsObject(Rec);
end;

function UnwrapShortstring(
  const Wrapped;
  Original: ShortstringClass): ShortstringClass;
begin
  Original.CurLen := ShortstringRec(Wrapped).Len;
  Result := Original;
end;

function WrapUnicodestring(aUnicodestring: JLObject): JLObject;
begin
  Result := JLObject(JLString(aUnicodestring).ToCharArray);
end;

function UnwrapUnicodestring(const Wrapped): JLString;
begin
  Result := JLString.Create(Arr1JChar(Wrapped));
end;

function WrapAnsistring(anAnsistring: JLObject): JLObject;
begin
  Result := JLObject(AnsistringClass.InternChars(ansistring(anAnsistring)));
end;

function UnwrapAnsistring(
  const Wrapped;
  Original: AnsistringClass): JLObject;
const
  NullTerminatorLength = 1;
begin
  Result := AnsistringClass.Create(
    TAnsiCharArray(Wrapped),
    Length(TAnsiCharArray(Wrapped)) - NullTerminatorLength,
    Original.CodePage);
end;

function WrapPointer(aPointer: JLObject; aPointerLookup: _JUHashTable): JLObject;
var
  JIntArray: array of JInt;
begin
  JIntArray := nil;
  SetLength(JIntArray, 1);
  JIntArray[0] := JLSystem.IdentityHashCode(aPointer);
  Result := JLObject(JIntArray);
  if (aPointerLookup <> nil) and (aPointer <> nil) then
    aPointerLookup.Put(JLInteger.Create(JIntArray[0]), aPointer);
end;

function UnwrapPointer(Wrapped, Original: JLObject; PointerLookup: _JUHashTable): JLObject;
var
  OriginalBuffer, UpdatedBuffer: array of JInt;
  Index: LongInt;
  Key: JLInteger;
begin
  Result := Original;
  OriginalBuffer := Arr1JInt(WrapPointer(Original, PointerLookup));
  UpdatedBuffer := Arr1JInt(Wrapped);
  Key := JLInteger.Create(UpdatedBuffer[0]);

  if UpdatedBuffer[0] = 0 then
    Result := nil
  else if UpdatedBuffer[0] = OriginalBuffer[0] then
    Result := Original
  else if (PointerLookup <> nil) and (PointerLookup.ContainsKey(Key)) then
    Result := PointerLookup.Get(Key)
  else
    raise JLException.Create(
      'Cannot change a pointer to a value other than nil');
end;

function Wrap(const Original; Size: SizeInt; PointerLookup: _JUHashTable): JLObject;
var
  Index: LongInt;
  JByteArray: array[0 .. 0] of JByte;
  JShortArray: array[0 .. 0] of JShort;
  JIntArray: array[0 .. 0] of JInt;
  JLongArray: array[0 .. 0] of JLong;
  JCharArray: array[0 .. 0] of JChar;
  JFloatArray: array[0 .. 0] of JFloat;
  JDoubleArray: array[0 .. 0] of JDouble;
  JBooleanArray: array[0 .. 0] of JBoolean;
  JLEnumArray: array[0 .. 0] of JLEnum;
begin
  Result := JLObject(Original);

  if Result is JLByte then
  begin
    JByteArray[0] := JLByte(Result).ByteValue;
    Result := AsObject(JByteArray)
  end
  else if Result is JLShort then
  begin
    JShortArray[0] := JLShort(Result).ShortValue;
    Result := AsObject(JShortArray)
  end
  else if Result is JLInteger then
  begin
    JIntArray[0] := JLInteger(Result).IntValue;
    Result := AsObject(JIntArray)
  end
  else if Result is JLLong then
  begin
    JLongArray[0] := JLLong(Result).LongValue;
    Result := AsObject(JLongArray)
  end
  else if Result is JLCharacter then
  begin
    JCharArray[0] := JLCharacter(Result).CharValue;
    Result := AsObject(JCharArray)
  end
  else if Result is JLBoolean then
  begin
    JBooleanArray[0] := JLBoolean(Result).BooleanValue;
    Result := AsObject(JBooleanArray)
  end
  else if Result is JLFloat then
  begin
    JFloatArray[0] := JLFloat(Result).FloatValue;
    Result := AsObject(JFloatArray)
  end
  else if Result is JLDouble then
  begin
    JDoubleArray[0] := JLDouble(Result).DoubleValue;
    Result := AsObject(JDoubleArray)
  end
  else if Result is JLEnum then
  begin
    JLEnumArray[0] := JLEnum(Result);
    Result := AsObject(JLEnumArray)
  end
  else if Result is JUEnumSet then
    Result := WrapEnumSet(Result, Size)
  else if Result is FpcBitSet then
    Result := WrapBitSet(Result, Size)
  else if Result is ShortstringClass then
    Result := WrapShortstring(Result)
  else if Result is JLString then
    Result := WrapUnicodestring(Result)
  else if Result is AnsistringClass then
    Result := WrapAnsistring(Result)
  else if
    ( Result = nil ) or
    ( ( not Result.GetClass.IsArray ) and
      ( not (Result is FpcBaseRecordType) ) ) then
  begin
    Result := WrapPointer(Result, PointerLookup);
  end;
end;

function Unwrap(Wrapped, Original: JLObject; PointerLookup: _JUHashTable): JLObject;
var
  JByteArray: Arr1JByte;
  JShortArray: array[0 .. 0] of JShort;
  JIntArray: array[0 .. 0] of JInt;
  JLongArray: array[0 .. 0] of JLong;
  JBooleanArray: array[0 .. 0] of JBoolean;
  JFloatArray: array[0 .. 0] of JFloat;
  JDoubleArray: array[0 .. 0] of JDouble;
  JCharArray: array[0 .. 0] of JChar;
begin
  Result := JLObject(Original);

  if JLObject(Original) is JLLong then
  begin
    if Wrapped.GetClass = AsObject(JByteArray).GetClass then
      Result := JLLong.Create(Arr1JByte(Wrapped)[0])
    else if Wrapped.GetClass = AsObject(JShortArray).GetClass then
      Result := JLLong.Create(Arr1JShort(Wrapped)[0])
    else if Wrapped.GetClass = AsObject(JIntArray).GetClass then
      Result := JLLong.Create(Arr1JInt(Wrapped)[0])
    else if Wrapped.GetClass = AsObject(JLongArray).GetClass then
      Result := JLLong.Create(Arr1JLong(Wrapped)[0]);
  end
  else if JLObject(Original) is JLBoolean then
    Result := JLBoolean.Create(Arr1JBoolean(Wrapped)[0])
  else if JLObject(Original) is JLCharacter then
    Result := JLCharacter.Create(Arr1JChar(Wrapped)[0])
  else if JLObject(Original) is JLFloat then
    Result := JLFloat.Create(Arr1JFloat(Wrapped)[0])
  else if JLObject(Original) is JLDouble then
    Result := JLDouble.Create(Arr1JDouble(Wrapped)[0])
  else if JLObject(Original) is JLEnum then
    Result := Arr1JLEnum(Wrapped)[0]
  else if JLObject(Original) is JUEnumSet then
    Result := UnwrapEnumSet(Wrapped, JUEnumSet(Original))
  else if JLObject(Original) is FpcBitSet then
    Result := UnwrapBitSet(Wrapped, FpcBitSet(Original))
  else if JLObject(Original) is ShortstringClass then
    Result := UnwrapShortstring(Wrapped, ShortstringClass(Original))
  else if JLObject(Original) is JLString then
    Result := UnwrapUnicodestring(Wrapped)
  else if JLObject(Original) is AnsistringClass then
    Result := UnwrapAnsistring(Wrapped, AnsistringClass(Original))
  else if
    ( Result = nil ) or
    ( ( not JLObject(Original).GetClass.IsArray ) and
      ( not (JLObject(Original) is FpcBaseRecordType) ) ) then
  begin
    Result := UnwrapPointer(Wrapped, Original, PointerLookup);
  end;
end;

function WrapField(
  aRecord: JLObject;
  aField: JLRField;
  anIsPointerType: Boolean;
  PointerLookup: _JUHashTable): JLObject;
var
  FieldType: JLClass;
  JByteArray: array[0 .. 0] of JByte;
  JBooleanArray: array[0 .. 0] of JBoolean;
  JShortArray: array[0 .. 0] of JShort;
  JIntArray: array[0 .. 0] of JInt;
  JLongArray: array[0 .. 0] of JLong;
  JCharArray: array[0 .. 0] of JChar;
  JFloatArray: array[0 .. 0] of JFloat;
  JDoubleArray: array[0 .. 0] of JDouble;
  JLEnumArray: array[0 .. 0] of JLEnum;
  IsAccessible: Boolean;
begin
  Result := nil;
  FieldType := aField.GetType;
  IsAccessible := aField.IsAccessible;
  aField.SetAccessible(True);

  if anIsPointerType then
    Result := WrapPointer(aField.Get(aRecord), PointerLookup)
  else if JLClass(JLEnum).IsAssignableFrom(FieldType) then
  begin
    JLEnumArray[0] := JLEnum(aField.Get(aRecord));
    Result := AsObject(JLEnumArray);
  end
  else if FieldType.IsPrimitive then
  begin
    Result := nil;
    case shortstring(FieldType.GetName) of
      'byte':
      begin
        JByteArray[0] := aField.GetByte(aRecord);
        Result := AsObject(JByteArray);
      end;
      'boolean':
      begin
        JBooleanArray[0] := aField.GetBoolean(aRecord);
        Result := AsObject(JBooleanArray);
      end;
      'short':
      begin
        JShortArray[0] := aField.GetShort(aRecord);
        Result := AsObject(JShortArray);
      end;
      'int':
      begin
        JIntArray[0] := aField.GetInt(aRecord);
        Result := AsObject(JIntArray);
      end;
      'long':
      begin
        JLongArray[0] := aField.GetLong(aRecord);
        Result := AsObject(JLongArray);
      end;
      'char':
      begin
        JCharArray[0] := aField.GetChar(aRecord);
        Result := AsObject(JCharArray);
      end;
      'float':
      begin
        JFloatArray[0] := aField.GetFloat(aRecord);
        Result := AsObject(JFloatArray);
      end;
      'double':
      begin
        JDoubleArray[0] := aField.GetDouble(aRecord);
        Result := AsObject(JDoubleArray);
      end
    else
      begin
        if not IsAccessible then
          aField.SetAccessible(False);
        raise JLException.Create('Unknown primitive type ' + FieldType.GetName + '.');
      end
    end
  end
  else if JLClass(JUEnumSet).IsAssignableFrom(FieldType) then
  begin
    Result := aField.Get(aRecord);
    Result := WrapEnumSet(Result, MeasureRecordField(aRecord, aField, False));
  end
  else if JLClass(FpcBitSet).IsAssignableFrom(FieldType) then
  begin
    Result := aField.Get(aRecord);
    Result := WrapBitSet(Result, MeasureRecordField(aRecord, aField, False));
  end
  else if JLClass(ShortstringClass).IsAssignableFrom(FieldType) then
  begin
    Result := aField.Get(aRecord);
    Result := WrapShortstring(Result)
  end
  else
    Result := aField.Get(aRecord);

  if not IsAccessible then
    aField.SetAccessible(False);

  if Result = nil then
    raise JLException.Create(
      'Cannot get value of the field ' + aField.GetDeclaringClass.GetName + '.' + aField.GetName);
end;

procedure UnwrapField(
  aRecord: JLObject;
  aField: JLRField;
  anIsPointerType: Boolean;
  Wrapped: JLObject;
  PointerLookup: _JUHashTable);
var
  FieldType: JLClass;
  Original: JLObject;
  IsAccessible: Boolean;
begin
  FieldType := aField.GetType;
  IsAccessible := aField.IsAccessible;
  aField.SetAccessible(True);

  if anIsPointerType then
  begin
    Original := aField.Get(aRecord);
    Original := UnwrapPointer(Wrapped, Original, PointerLookup);
    aField.&Set(aRecord, Original);
  end
  else if JLClass(JLEnum).IsAssignableFrom(FieldType) then
    aField.&Set(aRecord, Arr1JLEnum(Wrapped)[0])
  else if JLClass(JUEnumSet).IsAssignableFrom(FieldType) then
  begin
    Original := aField.Get(aRecord);
    Original := UnwrapEnumSet(Wrapped, JUEnumSet(Original));
    aField.&Set(aRecord, Original);
  end
  else if JLClass(FpcBitSet).IsAssignableFrom(FieldType) then
  begin
    Original := aField.Get(aRecord);
    Original := UnwrapBitSet(Wrapped, FpcBitSet(Original));
    aField.&Set(aRecord, Original);
  end
  else if JLClass(ShortstringClass).IsAssignableFrom(FieldType) then
  begin
    Original := aField.Get(aRecord);
    Original := UnwrapShortstring(Wrapped, ShortstringClass(Original));
    aField.&Set(aRecord, Original);
  end
  else if FieldType.IsPrimitive then
    case shortstring(FieldType.GetName) of
      'byte': aField.SetByte(aRecord, Arr1JByte(Wrapped)[0]);
      'boolean': aField.SetBoolean(aRecord, Arr1JBoolean(Wrapped)[0]);
      'short': aField.SetShort(aRecord, Arr1JShort(Wrapped)[0]);
      'int': aField.SetInt(aRecord, Arr1JInt(Wrapped)[0]);
      'long': aField.SetLong(aRecord, Arr1JLong(Wrapped)[0]);
      'char': aField.SetChar(aRecord, Arr1JChar(Wrapped)[0]);
      'float': aField.SetFloat(aRecord, Arr1JFloat(Wrapped)[0]);
      'double': aField.SetFloat(aRecord, Arr1JDouble(Wrapped)[0]);
    else
      begin
        if not IsAccessible then
          aField.SetAccessible(False);
        raise JLException.Create('Unknown primitive type ' + FieldType.GetName + '.');
      end
    end
  else
    aField.&Set(aRecord, Wrapped);

  if not IsAccessible then
    aField.SetAccessible(False);
end;

function WrapQWord(anArray: JLObject; anIndex: LongInt): QWord;
var
  ComponentType: JLClass;
begin
  ComponentType := anArray.GetClass.GetComponentType;

  Result := 0;
  if JLClass(JLEnum).IsAssignableFrom(ComponentType) then
    Result := QWord(FpcEnumValueObtainable(Arr1JLEnum(anArray)[anIndex]).FpcOrdinal)
  else
    case shortstring(ComponentType.GetName) of
      'byte': Result := QWord(Arr1JByte(anArray)[anIndex]);
      'boolean': Result := QWord(Ord(Arr1JBoolean(anArray)[anIndex]));
      'short': Result := QWord(Arr1JShort(anArray)[anIndex]);
      'int': Result := QWord(Arr1JInt(anArray)[anIndex]);
      'long': Result := QWord(Arr1JLong(anArray)[anIndex]);
      'char': Result := QWord(Ord(Arr1JChar(anArray)[anIndex]));
      'float': Result := QWord(Longword(Arr1JFloat(anArray)[anIndex]));
      'double': Result := QWord(Arr1JDouble(anArray)[anIndex])
    else
      raise JLException.Create('Unknown primitive type ' + ComponentType.GetName + '.');
    end;
end;

procedure UnwrapQWord(anArray: JLObject; anIndex: LongInt; Wrapped: QWord);
var
  ComponentType: JLClass;
begin
  ComponentType := anArray.GetClass.GetComponentType;

  if JLClass(JLEnum).IsAssignableFrom(ComponentType) then
    Arr1JLEnum(anArray)[anIndex] := FpcEnumValueObtainable(Arr1JLEnum(anArray)[anIndex]).FpcGenericValueOf(Wrapped)
  else
    case shortstring(ComponentType.GetName) of
      'byte': Arr1JByte(anArray)[anIndex] := JByte(Wrapped);
      'boolean': Arr1JBoolean(anArray)[anIndex] := Boolean(Wrapped);
      'short': Arr1JShort(anArray)[anIndex] := JShort(Wrapped);
      'int': Arr1JInt(anArray)[anIndex] := JInt(Wrapped);
      'long': Arr1JLong(anArray)[anIndex] := JLong(Wrapped);
      'char': Arr1JChar(anArray)[anIndex] := JChar(Wrapped);
      'float': Arr1JFloat(anArray)[anIndex] := JLFloat.IntBitsToFloat(JInt(Longword(Wrapped)));
      'double': Arr1JDouble(anArray)[anIndex] := JLDouble.LongBitsToDouble(JLong(Wrapped))
    else
      raise JLException.Create('Unknown primitive type ' + ComponentType.GetName + '.');
    end;
end;
