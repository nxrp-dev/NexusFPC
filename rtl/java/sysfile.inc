{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

function do_isdevice(Handle: THandle): Boolean;
begin
  Result := (Handle is _JIPrintStream);
end;

procedure do_close(Handle: THandle);
const
  FileNotOpen = 103;
begin
  try
    _JIRandomAccessFile(Handle).Close;
  except on JIIOException do
    InOutRes := FileNotOpen;
  end
end;

procedure do_erase(P: unicodestring; PChangeable: Boolean);
var
  IsDelete: Boolean;
const
  FileNotFound = 2;
  AccessDenied = 5;
begin
  DoDirSeparators(P);
  try
    IsDelete := _JIFile.Create(P).Delete;
    if not IsDelete then
      InOutRes := FileNotFound;
  except on _JLSecurityException do
    InOutRes := AccessDenied;
  end;
end;

procedure do_rename(
  P1: unicodestring;
  P2: unicodestring;
  P1Changeable: Boolean;
  P2Changeable: Boolean);
var
  IsRename: Boolean;
const
  FileNotFound = 2;
  AccessDenied = 5;
begin
  DoDirSeparators(P1);
  DoDirSeparators(P2);
  try
    IsRename := _JIFile.Create(P1).RenameTo(_JIFile.Create(P2));
    if not IsRename then
      InOutRes := FileNotFound;
  except on _JLSecurityException do
    InOutRes := AccessDenied;
  end;
end;

function do_write(Handle: THandle; const Buf; Count: LongInt): LongInt;
var
  ByteArray: Arr1JByte;
  ByteCount: LongInt;
  IsWriteDirectlyFromByteArray: Boolean;
begin
  Result := 0;
  if (JLObject(Buf) <> nil) and (Count > 0) then
  begin
    ByteArray := nil;
    IsWriteDirectlyFromByteArray := (JLObject(Buf).GetClass = AsObject(ByteArray).GetClass);
    if IsWriteDirectlyFromByteArray then
      ByteArray := Arr1JByte(Buf)
    else
    begin
      SetLength(ByteArray, Count);
      Move(Buf, ByteArray, Count);
    end;
    if Handle is _JIPrintStream then
    begin
      _JIPrintStream(Handle).Write(ByteArray, 0, Count);
      Result := Count;
    end
    else if Handle is _JIRandomAccessFile then
    begin
      _JIRandomAccessFile(Handle).Write(ByteArray, 0, Count);
      Result := Count;
    end;
  end;
end;

function do_read(Handle: THandle; var Buf; Offset, Count: LongInt): LongInt;
const
  NoMoreData = -1;
var
  ByteArray: Arr1JByte;
  ByteCount: LongInt;
  BufObject: JLObject;
  IsReadDirectlyIntoByteArray: Boolean;
begin
  Result := 0;
  if (JLObject(Buf) <> nil) and (Count > 0) then
  begin
    ByteArray := nil;
    IsReadDirectlyIntoByteArray := (JLObject(Buf).GetClass = AsObject(ByteArray).GetClass);
    if IsReadDirectlyIntoByteArray then
      ByteArray := Arr1JByte(Buf)
    else
      SetLength(ByteArray, Count);
    if Handle is _JIInputStream then
    begin
      Result := _JIInputStream(Handle).Read(ByteArray, Offset, Count);
      if Result = NoMoreData then
        Result := 0;
    end
    else if Handle is _JIRandomAccessFile then
    begin
      Result := _JIRandomAccessFile(Handle).Read(ByteArray, Offset, Count);
      if Result = NoMoreData then
        Result := 0;
    end;
    if (Result <> 0) and (not IsReadDirectlyIntoByteArray) then
    begin
      BufObject := JLObject(Buf);
      Move(ByteArray, BufObject, Result);
      Buf := BufObject;
    end;
  end;
end;

function do_read(Handle: THandle; var Buf; Count: LongInt): LongInt;
var
  BufObject: JLObject;
begin
  BufObject := JLObject(Buf);
  Result := do_read(Handle, BufObject, 0, Count);
  Buf := BufObject;
end;

function do_filepos(Handle: THandle): Int64;
const
  FileNotOpen = 103;
  SeekErrorOnDisk = 156;
begin
  Result := 0;
  try
    Result := _JIRandomAccessFile(Handle).GetChannel.Position;
  except
    on _JNCClosedChannelException do
      InOutRes := FileNotOpen;
    on JIIOException do
      InOutRes := SeekErrorOnDisk;
  end;
end;

procedure do_seek(Handle: THandle; Pos: Int64);
const
  SeekErrorOnDisk = 156;
begin
  try
    _JIRandomAccessFile(Handle).Seek(Pos);
  except on JIIOException do
    InOutRes := SeekErrorOnDisk;
  end;
end;

function do_seekend(Handle: THandle): Int64;
const
  SeekErrorOnDisk = 156;
begin
  Result := 0;
  try
    Result := _JIRandomAccessFile(Handle).Length;
    _JIRandomAccessFile(Handle).Seek(Result);
  except on JIIOException do
    InOutRes := SeekErrorOnDisk;
  end;
end;

function do_filesize(Handle: THandle): Int64;
const
  AccessDenied = 5;
begin
  Result := 0;
  try
    Result := _JIRandomAccessFile(Handle).Length;
  except on JIIOException do
    InOutRes := AccessDenied;
  end;
end;

procedure do_truncate(Handle: THandle; Pos: Int64);
const
  AccessDenied = 5;
begin
  try
    _JIRandomAccessFile(Handle).SetLength(Pos);
  except on JIIOException do
    InOutRes := AccessDenied;
  end;
end;

procedure do_open(var Handle: JLObject; var Mode: LongInt; P: unicodestring; Flags: LongInt);
const
  AppendFlag = $100;
  TruncateFlag = $1000;
  NoAutoCloseFlag = $10000;
  NoFlag = $0;
  WriteFlag = $1;
  ReadWriteFlag = $2;
  FileNotFound = 2;
  AccessDenied = 5;
  FileNotAssigned = 102;
var
  ModeString: unicodestring;
begin
  DoDirSeparators(P);
  ModeString := '';

  if (InOutRes = 0) and ((Flags and NoAutoCloseFlag) = 0) then
  begin
    case Mode of
      fmInput,
      fmOutput,
      fmInOut: do_close(Handle);
      fmClosed: // Do nothing
    else
      InOutRes := FileNotAssigned;
    end;
  end;

  if (InOutRes = 0) and ((Flags and TruncateFlag) = 0) and (P <> '') and (not _JIFile.Create(P).Exists) then
    InOutRes := FileNotFound;

  if InOutRes = 0 then
  begin
    Handle := UnusedHandle;

    if P = '' then
    begin
      case Mode of
        fmInput: Handle := StdInputHandle;
        fmInOut,
        fmOutput,
        fmAppend: Handle := StdOutputHandle;
      end;
    end
    else
    begin
      case ( Flags and %11 ) of
        NoFlag: Mode := fmInput;
        WriteFlag: Mode := fmOutput;
        ReadWriteFlag: Mode := fmInOut;
      end;

      if Mode = fmInput then
        ModeString := 'r'
      else
        ModeString := 'rw';

      if P = '' then
      begin
        case Mode of
          fmInput: Handle := StdInputHandle;
          fmInOut,
          fmOutput,
          fmAppend: Handle := StdOutputHandle;
        end;

        if Mode = fmAppend then
          Mode := fmOutput;
      end
      else
      begin
        try
          Handle := _JIRandomAccessFile.Create(P, ModeString);
        except
          on _JIFileNotFoundException do
            InOutRes := FileNotFound;
          on _JLSecurityException do
            InOutRes := AccessDenied;
        end;

        if (InOutRes = 0) and ((Flags and TruncateFlag) <> 0) then
          do_truncate(Handle, 0);

        if (InOutRes = 0) and ((Flags and AppendFlag) <> 0) then
        begin
          do_seekend(Handle);
          Mode := fmOutput;
        end;

        if InOutRes <> 0 then
        begin
          Handle := UnusedHandle;
          Mode := fmClosed;
        end;
      end;
    end;
  end;
end;

procedure do_open(var F: file; P: unicodestring; Flags: LongInt; PChangeable: Boolean);
var
  Handle: JLObject;
  Mode: LongInt;
begin
  Handle := FileRec(F).Handle;
  Mode := FileRec(F).Mode;
  do_open(Handle, Mode, P, Flags);
  FileRec(F).Handle := Handle;
  FileRec(F).Mode := Mode;
end;
