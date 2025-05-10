{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ This file helps us treat a java object as a stream of bytes. We can read
  bytes from any position and write bytes to any position. This is the
  foundation for memory related functions such as move or fill. }

type
  TDataWindow = class
    { The window is the start and end of the range
      of bytes to which we want to read or write.
      We skip fields in a record, or items in an
      array, or bytes in a primitive until we
      reach the starting offset. Then we read or
      write until there are no more bytes available.
      The window is changed by reference so that all
      serializers know how many bytes remain. }
  public
    ByteOffset: LongInt;
    BytesAvailable: LongInt;
  end;

function NewDataWindow(aByteOffset: LongInt; aBytesAvailable: LongInt): TDataWindow;
begin
  Result := TDataWindow.Create;
  Result.ByteOffset := aByteOffset;
  Result.BytesAvailable := aBytesAvailable;
end;

type
  ISerializer = interface
    { this interface knows how to read or write bytes to a java type }
    function IsAny: Boolean;
    procedure Next;
    function Peek: Byte;
    function Take: Byte;
    procedure &Set(aByte: Byte);
    procedure Put(aByte: Byte);
    procedure Load(anObject: JLObject);
  end;

  TByteEnumerator = record
  private
    FSerializer: ISerializer;
    FCurrent: Byte;
  public
    function MoveNext: Boolean;
    property Current: Byte read FCurrent;
  end;

operator Enumerator(aSerializer: ISerializer): TByteEnumerator;
begin
  Result.FSerializer := aSerializer;
end;

function TByteEnumerator.MoveNext: Boolean;
begin
  Result := FSerializer.IsAny;
  if Result then
    FCurrent := FSerializer.Take;
end;

function NewSerializer(
  anObject: JLObject;
  aSize: LongInt;
  aWindow: TDataWindow;
  aPointerLookup: _JUHashTable): ISerializer; forward;

type
  TByteArraySerializer = class(JLObject, ISerializer)
    { a byte array wrapped as a serializer }
  private
    FArray: Arr1JByte;
    FIndex: LongInt;
    FWindow: TDataWindow;
  public
    constructor Create(aByteArray: Arr1JByte; aWindow: TDataWindow);
    procedure Load(aByteArray: JLObject);
    function IsAny: Boolean;
    procedure Next;
    function Peek: Byte;
    function Take: Byte;
    procedure &Set(aByte: Byte);
    procedure Put(aByte: Byte);
  end;

constructor TByteArraySerializer.Create(aByteArray: Arr1JByte; aWindow: TDataWindow);
begin
  FArray := aByteArray;
  FWindow := aWindow;
  FIndex := FWindow.ByteOffset;
  FWindow.ByteOffset := 0;
end;

function TByteArraySerializer.IsAny: Boolean;
begin
  Result :=
    ( FWindow.BytesAvailable <> 0 ) and
    ( FIndex <> Length(FArray) );
end;

procedure TByteArraySerializer.Load(aByteArray: JLObject);
begin
  FArray := Arr1JByte(aByteArray);
  FIndex := 0;
end;

procedure TByteArraySerializer.Next;
begin
  if not IsAny then
    raise JLException.Create(
      'Byte array serializer cannot move to the next byte, as the serializer is empty.');

  Inc(FIndex);
  FWindow.BytesAvailable := FWindow.BytesAvailable - 1;
end;

function TByteArraySerializer.Peek: Byte;
begin
  Result := Byte(FArray[FIndex])
end;

function TByteArraySerializer.Take: Byte;
begin
  Result := Peek;
  Next
end;

procedure TByteArraySerializer.&Set(aByte: Byte);
begin
  FArray[FIndex] := JByte(aByte)
end;

procedure TByteArraySerializer.Put(aByte: Byte);
begin
  &Set(aByte);
  Next
end;

type
  TPrimitiveArraySerializer = class(JLObject, ISerializer)
    { for each primitive in an array convert the primitive to a qword and then
      use masking to get or set individual bytes }
  private
    FArray: JLObject;
    FArrayLength: LongInt;
    FItemSize: LongInt;
    FIndex: LongInt;
    FByteIndex: LongInt;
    FWindow: TDataWindow;
    FOriginalValue: QWord;
    FItemValue: QWord;
  public
    constructor Create(
      aPrimitiveArray: JLObject;
      aWindow: TDataWindow;
      anItemSize: LongInt);
    procedure Load(aPrimitiveArray: JLObject);
    function IsAny: Boolean;
    procedure Next;
    function Peek: Byte;
    function Take: Byte;
    procedure &Set(aByte: Byte);
    procedure Put(aByte: Byte);
  end;

constructor TPrimitiveArraySerializer.Create(
  aPrimitiveArray: JLObject;
  aWindow: TDataWindow;
  anItemSize: LongInt);
begin
  FArray := aPrimitiveArray;
  FArrayLength := JLRArray.GetLength(aPrimitiveArray);
  FItemSize := anItemSize;
  FWindow := aWindow;
  FIndex := aWindow.ByteOffset div FItemSize;
  FByteIndex := aWindow.ByteOffset mod FItemSize;
  FWindow.ByteOffset := 0;
  FOriginalValue := WrapQWord(FArray, FIndex);
  FItemValue := FOriginalValue;
end;

function TPrimitiveArraySerializer.IsAny: Boolean;
begin
  Result :=
    ( FWindow.BytesAvailable <> 0 ) and
    ( FIndex <> FArrayLength );
end;

procedure TPrimitiveArraySerializer.Load(aPrimitiveArray: JLObject);
begin
  FArray := aPrimitiveArray;
  FArrayLength := JLRArray.GetLength(aPrimitiveArray);
  FIndex := 0;
  FByteIndex := 0;
  FOriginalValue := WrapQWord(FArray, FIndex);
  FItemValue := FOriginalValue;
end;

procedure TPrimitiveArraySerializer.Next;
begin
  if not IsAny then
    raise JLException.Create(
      'Primitive array serializer cannot move to the next byte, as the serializer is empty.');

  Inc(FByteIndex);
  FWindow.BytesAvailable := FWindow.BytesAvailable - 1;

  if
    ( FItemValue <> FOriginalValue ) and
    ( (FByteIndex = FItemSize) or (FWindow.BytesAvailable = 0) )
  then
    UnwrapQWord(FArray, FIndex, FItemValue);

  if FByteIndex = FItemSize then
  begin
    Inc(FIndex);
    FByteIndex := 0;
    if IsAny then
    begin
      FOriginalValue := WrapQWord(FArray, FIndex);
      FItemValue := FOriginalValue;
    end;
  end;
end;

function TPrimitiveArraySerializer.Peek: Byte;
var
  Mask: QWord;
begin
  if not IsAny then
    raise JLException.Create(
      'Primitive array serializer cannot peek the byte, as the serializer is empty.');

  Mask := QWord($FF) shl (FByteIndex * 8);
  Result := Byte( ( FItemValue and Mask ) shr ( FByteIndex * 8) );
end;

function TPrimitiveArraySerializer.Take: Byte;
begin
  if not IsAny then
    raise JLException.Create(
      'Primitive array serializer cannot take the byte, as the serializer is empty.');

  Result := Peek;
  Next;
end;

procedure TPrimitiveArraySerializer.&Set(aByte: Byte);
var
  Mask: QWord;
begin
  if not IsAny then
    raise JLException.Create(
      'Primitive array serializer cannot set the byte, as the serializer is empty.');

  Mask := not ( QWord($FF) shl (FByteIndex * 8) );
  FItemValue :=
    ( FItemValue and Mask ) or
    ( QWord(aByte) shl (FByteIndex * 8) );
end;

procedure TPrimitiveArraySerializer.Put(aByte: Byte);
begin
  if not IsAny then
    raise JLException.Create(
      'Primitive array serializer cannot put the byte, as the serializer is empty.');

  &Set(aByte);
  Next;
end;

type
  TObjectArraySerializer = class(JLObject, ISerializer)
    { Create a serializer.
      Load in an item from the array.
      When all the bytes have been processed load in the next item.
      This is for reference types
      (FpcBaseRecordType, ShortstringClass, FpcBitSet, JUEnumSet or JLArray).
      Use TPrimitiveArraySerializer for an array of primitives. }
  private
    FArray: Arr1JLObject;
    FArrayLength: LongInt;
    FItemSize: LongInt;
    FIndex: LongInt;
    FWindow: TDataWindow;
    FItemSerializer: ISerializer;
    FWrappedItem: JLObject;
    FPointerLookup: _JUHashTable;
  public
    constructor Create(
      anObjectArray: JLObject;
      anArraySize: LongInt;
      aWindow: TDataWindow;
      aPointerLookup: _JUHashTable);
    procedure Load(anObjectArray: JLObject);
    function IsAny: Boolean;
    procedure Next;
    function Peek: Byte;
    function Take: Byte;
    procedure &Set(aByte: Byte);
    procedure Put(aByte: Byte);
  end;

constructor TObjectArraySerializer.Create(
  anObjectArray: JLObject;
  anArraySize: LongInt;
  aWindow: TDataWindow;
  aPointerLookup: _JUHashTable);
begin
  FArray := Arr1JLObject(anObjectArray);
  FArrayLength := Length(FArray);
  FItemSize := anArraySize div FArrayLength;
  FIndex := aWindow.ByteOffset div FItemSize;
  FWindow := aWindow;
  FWindow.ByteOffset := aWindow.ByteOffset mod FItemSize;
  FPointerLookup := aPointerLookup;
  FWrappedItem := Wrap(FArray[FIndex], FItemSize, FPointerLookup);
  FItemSerializer := NewSerializer(
    FWrappedItem,
    FItemSize,
    aWindow,
    FPointerLookup);
end;

procedure TObjectArraySerializer.Load(
  anObjectArray: JLObject);
begin
  FArray := Arr1JLObject(anObjectArray);
  FArrayLength := Length(FArray);
  FIndex := 0;
  FWrappedItem := Wrap(FArray[FIndex], FItemSize, FPointerLookup);
  FItemSerializer.Load(FWrappedItem);
end;

function TObjectArraySerializer.IsAny: Boolean;
begin
  Result :=
    ( FWindow.BytesAvailable <> 0 ) and
    ( FIndex <> FArrayLength );
end;

procedure TObjectArraySerializer.Next;
begin
  if not IsAny then
    raise JLException.Create(
      'Object serializer cannot move to the next byte, as the serializer is empty.');

  FItemSerializer.Next;
  if not FItemSerializer.IsAny then
  begin
    FArray[FIndex] := Unwrap(FWrappedItem, FArray[FIndex], FPointerLookup);

    Inc(FIndex);
    if
      ( FWindow.BytesAvailable <> 0 ) and
      ( FIndex <> FArrayLength ) then
    begin
      FWrappedItem := Wrap(FArray[FIndex], FItemSize, FPointerLookup);
      FItemSerializer.Load(FWrappedItem);
    end
    else
      FItemSerializer := nil;
  end;
end;

function TObjectArraySerializer.Peek: Byte;
begin
  if not IsAny then
    raise JLException.Create(
      'Object serializer cannot peek the byte, as the serializer is empty.');

  Result := FItemSerializer.Peek;
end;

function TObjectArraySerializer.Take: Byte;
begin
  if not IsAny then
    raise JLException.Create(
      'Object serializer cannot take the byte, as the serializer is empty.');

  Result := Peek;
  Next;
end;

procedure TObjectArraySerializer.&Set(aByte: Byte);
begin
  if not IsAny then
    raise JLException.Create(
      'Object serializer cannot set the byte, as the serializer is empty.');

  FItemSerializer.&Set(aByte);
end;

procedure TObjectArraySerializer.Put(aByte: Byte);
begin
  if not IsAny then
    raise JLException.Create(
      'Object serializer cannot put the byte, as the serializer is empty.');

  &Set(aByte);
  Next;
end;

type
  TRecordSerializer = class(JLObject, ISerializer)
    { Use reflection to discover the fields.
      Create a serializer for the first field.
      When all the bytes have been processed create a
      new serializer and load in the next field. }
  private
    FRecord: JLObject;
    FEmptyRecord: JLObject;
    FWindow: TDataWindow;
    FFieldList: Arr1JLRField;
    FFieldIndex: LongInt;
    FIsPointerType: Boolean;
    FFieldSerializer: ISerializer;
    FWrappedValue: JLObject;
    FPointerLookup: _JUHashTable;
  private
    class function IsEmptyType(aClass: JLClass): Boolean;
  public
    constructor Create(
      aRecord: JLObject;
      aWindow: TDataWindow;
      aPointerLookup: _JUHashTable);
    procedure Load(aRecord: JLObject);
    function IsAny: Boolean;
    procedure Next;
    function Peek: Byte;
    function Take: Byte;
    procedure &Set(aByte: Byte);
    procedure Put(aByte: Byte);
  end;

class function TRecordSerializer.IsEmptyType(aClass: JLClass): Boolean;
  { an empty type is a record having no fields
    or an array of records having no fields }
type
  FpcBaseRecordClass = class of FpcBaseRecordType;
var
  ComponentType: JLClass;
begin
  ComponentType := aClass;
  while ComponentType.IsArray do
    ComponentType := ComponentType.GetComponentType;
  Result :=
    ( JLClass(FpcBaseRecordType).IsAssignableFrom(ComponentType) ) and
    ( Length(FpcBaseRecordClass(ComponentType).GetOrderedFields) = 0 );
end;

constructor TRecordSerializer.Create(
  aRecord: JLObject;
  aWindow: TDataWindow;
  aPointerLookup: _JUHashTable);
type
  FpcBaseRecordClass = class of FpcBaseRecordType;
var
  FieldSize: LongInt;
begin
  FRecord := aRecord;
  FEmptyRecord := FpcBaseRecordType(aRecord).NewEmpty;
  FWindow := aWindow;
  FFieldList := FpcBaseRecordClass(JLObject(aRecord).GetClass).GetOrderedFields;
  FPointerLookup := aPointerLookup;

  FFieldIndex := 0;
  FieldSize := 0;
  FWrappedValue := nil;
  while
    ( FFieldIndex <> Length(FFieldList) ) and
    ( FieldSize <= aWindow.ByteOffset ) do
  begin
    FIsPointerType := GetIsPointerType(FEmptyRecord, FFieldList[FFieldIndex]);
    FieldSize := MeasureRecordField(
      FRecord,
      FFieldList[FFieldIndex],
      FIsPointerType);
    if FieldSize <= aWindow.ByteOffset then
    begin
      Dec(aWindow.ByteOffset, FieldSize);
      Inc(FFieldIndex);
    end;
  end;

  while
    ( FFieldIndex <> Length(FFieldList) ) and
    ( IsEmptyType(FFieldList[FFieldIndex].GetType) ) do
  begin
    Inc(FFieldIndex);
  end;

  FIsPointerType := GetIsPointerType(FEmptyRecord, FFieldList[FFieldIndex]);
  FWrappedValue := WrapField(
    FRecord,
    FFieldList[FFieldIndex],
    FIsPointerType,
    FPointerLookup);
  FieldSize := MeasureRecordField(
    FRecord,
    FFieldList[FFieldIndex],
    FIsPointerType);
  FFieldSerializer := NewSerializer(
    FWrappedValue,
    FieldSize,
    FWindow,
    FPointerLookup);
end;

procedure TRecordSerializer.Load(aRecord: JLObject);
var
  FieldSize: LongInt;
begin
  FRecord := aRecord;
  FFieldIndex := 0;
  FIsPointerType := GetIsPointerType(FEmptyRecord, FFieldList[FFieldIndex]);
  FWrappedValue := WrapField(
    FRecord,
    FFieldList[FFieldIndex],
    FIsPointerType,
    FPointerLookup);
  FieldSize := MeasureRecordField(
    FRecord,
    FFieldList[FFieldIndex],
    FIsPointerType);
  FFieldSerializer := NewSerializer(
    FWrappedValue,
    FieldSize,
    FWindow,
    FPointerLookup);
end;

function TRecordSerializer.IsAny: Boolean;
begin
  Result :=
    ( FWindow.BytesAvailable <> 0 ) and
    ( FFieldIndex <> Length(FFieldList) );
end;

procedure TRecordSerializer.Next;
var
  FieldType: JLClass;
  FieldSize: LongInt;
begin
  if not IsAny then
    raise JLException.Create(
      'Record serializer cannot move to the next byte, as the serializer is empty.');

  FFieldSerializer.Next;
  if not FFieldSerializer.IsAny then
  begin
    FieldType := FFieldList[FFieldIndex].GetType;
    UnwrapField(
      FRecord,
      FFieldList[FFieldIndex],
      FIsPointerType,
      FWrappedValue,
      FPointerLookup);

    repeat
      Inc(FFieldIndex);
    until
      ( FFieldIndex = Length(FFieldList) ) or
      ( not IsEmptyType(FFieldList[FFieldIndex].GetType) );

    if
      ( FWindow.BytesAvailable <> 0 ) and
      ( FFieldIndex <> Length(FFieldList) ) then
    begin
      FIsPointerType := GetIsPointerType(FEmptyRecord, FFieldList[FFieldIndex]);
      FWrappedValue := WrapField(
        FRecord,
        FFieldList[FFieldIndex],
        FIsPointerType,
        FPointerLookup);
      FieldSize := MeasureRecordField(
        FRecord,
        FFieldList[FFieldIndex],
        FIsPointerType);
      FFieldSerializer := NewSerializer(
        FWrappedValue,
        FieldSize,
        FWindow,
        FPointerLookup);
    end
    else
      FFieldSerializer := nil;
  end
end;

function TRecordSerializer.Peek: Byte;
begin
  if not IsAny then
    raise JLException.Create(
      'Record serializer cannot peek the byte, as the serializer is empty.');

  Result := FFieldSerializer.Peek;
end;

function TRecordSerializer.Take: Byte;
begin
  if not IsAny then
    raise JLException.Create(
      'Record serializer cannot take the byte, as the serializer is empty.');

  Result := Peek;
  Next;
end;

procedure TRecordSerializer.&Set(aByte: Byte);
begin
  if not IsAny then
    raise JLException.Create(
      'Record serializer cannot set the byte, as the serializer is empty.');

  FFieldSerializer.&Set(aByte);
end;

procedure TRecordSerializer.Put(aByte: Byte);
begin
  if not IsAny then
    raise JLException.Create(
      'Record serializer cannot put the byte, as the serializer is empty.');

  &Set(aByte);
  Next;
end;

function NewSerializer(
  anObject: JLObject;
  aSize: LongInt;
  aWindow: TDataWindow;
  aPointerLookup: _JUHashTable): ISerializer;
var
  ComponentType: JLClass;
  JByteArray: Arr1JByte;
begin
  if anObject = nil then
    raise JLException.Create(
      'Cannot create a serializer as the object is nil.');

  if aSize = 0 then
    raise JLException.Create(
      'Cannot create a serializer as the object size is zero.');

  Result := nil;
  JByteArray := nil;

  if anObject.GetClass.IsArray then
  begin
    ComponentType := anObject.GetClass.GetComponentType;

    if anObject.GetClass = AsObject(JByteArray).GetClass then
      Result := TByteArraySerializer.Create(Arr1JByte(anObject), aWindow)
    else if JLClass(JLEnum).IsAssignableFrom(ComponentType) then
      Result := TPrimitiveArraySerializer.Create(anObject, aWindow, aSize div JLRArray.GetLength(anObject))
    else if ComponentType.IsPrimitive then
      Result := TPrimitiveArraySerializer.Create(anObject, aWindow, MeasurePrimitive(ComponentType))
    else
      Result := TObjectArraySerializer.Create(anObject, aSize, aWindow, aPointerLookup);
  end
  else if anObject is FpcBaseRecordType then
    Result := TRecordSerializer.Create(anObject, aWindow, aPointerLookup)
  else
    raise JLException.Create(
      'Cannot create a serializer for the type ' + anObject.GetClass.GetCanonicalName + '.');
end;
