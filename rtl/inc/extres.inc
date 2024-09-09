{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2008 by Giulio Bernardi

    Resource support as external files

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
{
  This file implements two kinds of external resource support:
   - one for systems that support the mmap call (usually unix-like oses)
   - one fallback implementation based on pascal files and GetMem/FreeMem
   
  Be sure to define EXTRES_MMAP or EXTRES_GENERIC before including this file!
}
{$IF defined(EXTRES_MMAP) and defined(EXTRES_GENERIC)}
{$FATAL EXTRES_MMAP and EXTRES_GENERIC can't be defined together}
{$ENDIF}

{$IF (not defined(EXTRES_MMAP)) and (not defined(EXTRES_GENERIC))}
{$FATAL EXTRES_MMAP or EXTRES_GENERIC must be defined}
{$ENDIF}

{$IF defined(EXTRES_MMAP) and defined(CPUJVM)}
{$FATAL EXTRES_MMAP is not supported for the CPUJVM target}
{$ENDIF}

const
  FPCRES_MAGIC = 'FPCRES';
  FPCRES_VERSION = 1;
{$IFNDEF CPUJVM}
  {$IFDEF ENDIAN_BIG}
  FPCRES_ENDIAN = 1;
  {$ENDIF}
  {$IFDEF ENDIAN_LITTLE}
  FPCRES_ENDIAN = 2;
  {$ENDIF}
{$ELSE CPUJVM}
  { JVM Notes: endian is only known at runtime (the same file can run on any machine) }
  FPCRES_ENDIAN : longint = 0;
{$ENDIF CPUJVM}
  FPCRES_EXT = '.fpcres';
  FPCRES_NODE_NOT_FOUND = -1;

{$ifdef CPUJVM}
function GetEndian : longint;
  { big endian one is stored as $0100, little endian one is stored as $0001 }
const
  BIG_ENDIAN = 1;
  LITTLE_ENDIAN = 2;
var
  Number : Word;
begin
  Number:=Word(1);
  if (Number and $00FF)=1 then
    GetEndian:=LITTLE_ENDIAN
  else
    GetEndian:=BIG_ENDIAN;
end;
{$endif CPUJVM}

type
  TExtHeader = packed record
    magic : array[0..5] of AnsiChar;//'FPCRES'
    version : byte;             //EXT_CURRENT_VERSION
    endianess : byte;           //EXT_ENDIAN_BIG or EXT_ENDIAN_LITTLE
    count : longword;           //resource count
    nodesize : longword;        //size of header (up to string table, excluded)
    hdrsize  : longword;        //size of header (up to string table, included)
    reserved1 : longword;
    reserved2 : longword;
    reserved3 : longword;
{$if defined(CPUJVM) and defined(ANDROID)}
  const
    FieldOrder='magic,version,endianess,count,nodesize,hdrsize,reserved1,reserved2,reserved3';
{$endif ANDROIDJVM}
  end;
  PExtHeader = ^TExtHeader;

  TResInfoNode = packed record
    nameid : longword;          //name offset / integer ID / languageID
    ncounthandle : longword;    //named sub-entries count/resource handle
    idcountsize : longword;     //id sub-entries count / resource size
    subptr : longword;          //first sub-entry offset
{$if defined(CPUJVM) and defined(ANDROID)}
  const
    FieldOrder='nameid,ncounthandle,idcountsize,subptr';
{$endif ANDROIDJVM}
  end;
  PResInfoNode = ^TResInfoNode;

  {$IFDEF EXTRES_GENERIC}
  {$IFDEF CPUJVM}
  TResData = record
    refcount : longword;
    info : PResInfoNode;
    data : Arr1JByte;
  end;
  PResData = ^TResData;
  {$ENDIF CPUJVM}

  TResHandle = record
    info : PResInfoNode;
    ptr : {$IFNDEF CPUJVM}Pointer{$ELSE}PResData{$ENDIF};
  end;
  PResHandle = ^TResHandle;
  {$ENDIF}

var ResHeader : PExtHeader = nil;
    usedhandles : longword = 0;
    {$IFDEF EXTRES_MMAP}
    fd : integer;
    fd_size : longword;
    reshandles : PPointer = nil;
    {$ENDIF}
    {$IFDEF EXTRES_GENERIC}
    fd : file;
    reshandles : {$IFNDEF CPUJVM}PResHandle{$ELSE}array of TResHandle{$ENDIF} = nil;
    {$IFDEF CPUJVM}
    nodelist : array of TResInfoNode = nil;
    stringtable : _JUHashTable; { each string in the file with its offset as key }
    resourcefilebytes : arr1jbyte;
    {$ENDIF CPUJVM}
    {$ENDIF}

(*****************************************************************************
                             Private Helper Functions
*****************************************************************************)

//resource functions are case insensitive... copied from genstr.inc
function ResStrIComp(Str1, Str2 : PAnsiChar): SizeInt;
var
  counter: SizeInt;
  c1, c2: AnsiChar;
begin
  counter := 0;
  c1 := upcase(str1[counter]);
  c2 := upcase(str2[counter]);
  while c1 = c2 do
  begin
    if (c1 = #0) or (c2 = #0) then break;
    inc(counter);
    c1 := upcase(str1[counter]);
    c2 := upcase(str2[counter]);
  end;
  ResStrIComp := ord(c1) - ord(c2);
end;

{!fixme!}
//function InternalIsIntResource(aStr : PAnsiChar; out aInt : PtrUint) : boolean;
function InternalIsIntResource(aStr : PAnsiChar; var aInt : PtrUint) : boolean;
var i : integer;
    s : shortstring;
    code : word;
begin
{$ifndef CPUJVM}
  InternalIsIntResource:=((PtrUInt(aStr) shr 16)=0);
{$else}
  InternalIsIntResource:=False;
{$endif}

{$ifndef CPUJVM}
  if InternalIsIntResource then aInt:=PtrUInt(aStr)
  else
{$endif}
  begin
    //a string like #number specifies an integer id
    if aStr[0]='#' then
    begin
      i:=1;
      while aStr[i]<>#0 do
        inc(i);
      if i>256 then i:=256;
      s[0]:=chr(i-1);
{$ifndef CPUJVM}
      Move(aStr[1],s[1],i-1);
{$else}
      Move(aStr,1,s,1,i-1);
{$endif}
      Val(s,aInt,code);
      InternalIsIntResource:=code=0;
    end;
  end;
end;

{$IFNDEF CPUJVM}
function GetResInfoPtr(const offset, index : longword) : PResInfoNode; inline;
begin
  GetResInfoPtr:=PResInfoNode(PtrUInt(ResHeader)+offset) + index;
end;

function GetResInfoPtr(const offset : longword) : PResInfoNode; inline;
begin
  GetResInfoPtr:=PResInfoNode(PtrUInt(ResHeader)+offset);
end;
{$ELSE CPUJVM}
function GetResInfoPtr(const offset, index : longword) : PResInfoNode;
var baseindex : longword;
begin
  baseindex:=(offset-sizeof(TExtHeader)) div sizeof(TResInfoNode);
  GetResInfoPtr:=@nodelist[baseindex+index];
end;

function GetResInfoPtr(const offset : longword) : PResInfoNode;
begin
  GetResInfoPtr:=GetResInfoPtr(offset,0);
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
function GetPchar(const offset : longword) : PAnsiChar; inline;
begin
  GetPchar:=PAnsiChar(PtrUInt(ResHeader)+offset);
end;
{$ELSE CPUJVM}
function GetPchar(const offset : longword) : PAnsiChar;
  { get the string we found at this offset from a table prepared at load time }
var
  obj : JLObject;
begin
  obj:=stringtable.Get(JLInteger.Create(offset));
  GetPchar:=PAnsiChar(ansistring(obj));
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
function GetPtr(const offset : longword) : Pointer; inline;
begin
  GetPtr:=Pointer(PtrUInt(ResHeader)+offset);
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
procedure FixResEndian;
var ptr : plongword;
    blockend : plongword;
begin
  //all info nodes reside in a contiguos block of memory.
  //they are all 16 bytes long and made by longwords
  //so, simply swap each longword in the block
  ptr:=GetPtr(sizeof(TExtHeader));
  blockend:=GetPtr(ResHeader^.nodesize);
  while ptr<blockend do
  begin
    ptr^:=SwapEndian(ptr^);
    inc(ptr);
  end;
end;
{$ELSE CPUJVM}
procedure FixResEndian;
var index : longword;
    temp : jbyte;
begin
  index:=sizeof(TExtHeader);
  while index<ResHeader^.nodesize do
  begin
    temp:=resourcefilebytes[index+0];
    resourcefilebytes[index+0]:=resourcefilebytes[index+3];
    resourcefilebytes[index+3]:=temp;
    temp:=resourcefilebytes[index+1];
    resourcefilebytes[index+1]:=resourcefilebytes[index+2];
    resourcefilebytes[index+2]:=temp;
    inc(index,sizeof(longword));
  end;
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
function IntAsName(const id : longword): PAnsiChar;
begin
  IntAsName:=PAnsiChar(id);
end;
{$ELSE CPUJVM}
function IntAsName(const id : longword): PAnsiChar;
var s : ansistring;
begin
  str(id,s);
  s:='#'+s;
  IntAsName:=PAnsiChar(s);
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
function GetExtResPath : PAnsiChar;
var len, i : integer;
    pathstr : shortstring;
begin
  pathstr:=paramstr(0);
  len:=byte(pathstr[0]);
  i:=len;
  //writeln('exe name is ',pathstr);
  //find position of extension
  while (i>0) and (not (pathstr[i] in ['.',DirectorySeparator])) do
    dec(i);
  if (i>0) and (pathstr[i]='.') then dec(i)
  else i:=len;
  pathstr[0]:=Chr(i);
  pathstr:=pathstr+FPCRES_EXT;
  len:=byte(pathstr[0]);
  GetExtResPath:=GetMem(len+1);
  Move(pathstr[1],GetExtResPath[0],len);
  GetExtResPath[len]:=#0;
  //writeln('Resource file is ',GetExtResPath);
end;
{$ELSE CPUJVM}
function GetExtResPath : shortstring;
  { the resource file must be placed at this location inside the jar file }
begin
  result:='org/freepascal/rawresources/application.fpcres';
end;
{$ENDIF CPUJVM}

function BinSearchStr(offset : longword; query : PAnsiChar; left, right : integer)
: longint;
var pivot, res : integer;
    resstr : PAnsiChar;
begin
  BinSearchStr:=FPCRES_NODE_NOT_FOUND;
  while left<=right do
  begin
    pivot:=(left+right) div 2;
    resstr:=GetPchar(GetResInfoPtr(offset,pivot)^.nameid);
    res:=ResStrIComp(resstr,query);
    if res<0 then left:=pivot+1
    else if res>0 then right:=pivot-1
    else
    begin
      BinSearchStr:=offset+(pivot*sizeof(TResInfoNode));
      exit;
    end;
  end;
end;

function BinSearchInt(offset : longword; query : PtrUInt; left, right : integer)
: longint;
var pivot : integer;
begin
  BinSearchInt:=FPCRES_NODE_NOT_FOUND;
  while left<=right do
  begin
    pivot:=(left+right) div 2;
    if GetResInfoPtr(offset,pivot)^.nameid<PtrUInt(query) then left:=pivot+1
    else if GetResInfoPtr(offset,pivot)^.nameid>PtrUInt(query) then right:=pivot-1
    else
    begin
      BinSearchInt:=offset+(pivot*sizeof(TResInfoNode));
      exit;
    end;
  end;
end;

function BinSearchRes(offset : longword; aDesc : PAnsiChar) : longint;
var aID : PtrUint;
    root : PResInfoNode;
begin
  root:=GetResInfoPtr(offset);
  aID:=0;
  if InternalIsIntResource(aDesc,aID) then
    BinSearchRes:=BinSearchInt(root^.subptr,aID,
      root^.ncounthandle,root^.ncounthandle+root^.idcountsize-1)
  else
    BinSearchRes:=BinSearchStr(root^.subptr,aDesc,0,
      root^.ncounthandle-1);
end;

//Returns a pointer to a name node.
function InternalFindResource(ResourceName, ResourceType: PAnsiChar):
 PResInfoNode;
var offset : longint;
begin
  InternalFindResource:=nil;
  if ResHeader=nil then exit;
  offset:=sizeof(TExtHeader);

  offset:=BinSearchRes(offset,ResourceType);
  if offset<>FPCRES_NODE_NOT_FOUND then
    offset:=BinSearchRes(offset,ResourceName);
  if offset<>FPCRES_NODE_NOT_FOUND then
    InternalFindResource:=GetResInfoPtr(offset);
end;

function FindSubLanguage(aPtr : PResInfoNode; aLangID : word; aMask: word) : PResInfoNode;
var offset, i : longword;
begin
  FindSubLanguage:=nil;
  offset:=aPtr^.subptr;
  i:=0;
  while i<aPtr^.idcountsize do
  begin
    if (PtrUInt(GetResInfoPtr(offset,i)^.nameid) and aMask)=(aLangID and aMask) then
    begin
      FindSubLanguage:=GetResInfoPtr(offset,i);
      exit;
    end;
    inc(i);
  end;
end;

{$IFDEF CPUJVM}
function ExtReadResourceFile(P : shortstring) : Arr1JByte;
  { a resource stream cannot return the size of the resource file, cannot skip
    bytes and cannot seek, as a workaround we read the entire stream into memory }
const NoMoreData = -1;
var ResourceStream : _JIInputStream;
    ByteStream : _JIByteArrayOutputStream;
    Buffer : Arr1JByte;
    NumBytesRead : longint;
{$ifdef ANDROID}
    Index : longint;
    ResFile : _JIFile;
    FileList : Arr1JLString;
    Context : _ACContext;
{$endif ANDROID}
begin
  ExtReadResourceFile:=nil;
  ResourceStream:=nil;
{$ifdef ANDROID}
  ResFile:=_JIFile.Create(P);
  Context:=_AAAppGlobals.GetInitialApplication.GetApplicationContext;
  FileList:=Context.GetAssets.List(ResFile.GetParent);
  Index:=0;
  { jlstring equality fails even though the content is equal, we must cast to unicodestring }
  while
    (Index<>Length(FileList)) and
    (unicodestring(FileList[Index])<>unicodestring(ResFile.GetName))
  do
    Inc(Index);
  if Index<>Length(FileList) then
    ResourceStream:=Context.GetAssets.Open(P)
  else
    ResourceStream:=nil;
{$else ANDROID}
  ResourceStream:=_JLThread.CurrentThread.GetContextClassLoader.GetResourceAsStream(P);
{$endif ANDROID}
  if ResourceStream<>nil then
  begin
    Buffer:=nil;
    SetLength(Buffer,4096);
    ByteStream:=_JIByteArrayOutputStream.Create;
    NumBytesRead:=ResourceStream.Read(Buffer,0,Length(Buffer));
    while NumBytesRead<>NoMoreData do
    begin
      ByteStream.Write(Buffer,0,NumBytesRead);
      NumBytesRead:=ResourceStream.Read(Buffer,0,Length(Buffer));
    end;
    ExtReadResourceFile:=ByteStream.ToByteArray;
  end;
end;
{$ENDIF CPUJVM}

{$IFDEF EXTRES_MMAP}
procedure InitResources;
const
  PROT_READ  = 1;
  PROT_WRITE = 2;
var respath : PAnsiChar;
    fdstat : stat;
begin
  respath:=GetExtResPath;
//  writeln('respath ',respath);
  fd:=FpOpen(respath,O_RDONLY,0);
//  writeln('fpopen returned ',fd);
  FreeMem(respath);
  if fd=-1 then exit;
  if FpFStat(fd,fdstat)<>0 then
  begin
//    writeln('fpfstat failed');
    FpClose(fd);
    exit;
  end;
//  writeln('fpfstat suceeded');
  fd_size:=fdstat.st_size;
  ResHeader:=PExtHeader(Fpmmap(nil,fd_size,PROT_READ or PROT_WRITE,
    MAP_PRIVATE,fd,0));
//  writeln('fpmmap returned ',PtrInt(ResHeader));
  if PtrInt(ResHeader)=-1 then
  begin
    FpClose(fd);
    exit;
  end;
  if (ResHeader^.magic<>FPCRES_MAGIC) or
    (ResHeader^.version<>fpcres_version) then
  begin
    FpClose(fd);
    exit;
  end;
//  writeln('magic ok');
  if ResHeader^.endianess<>FPCRES_ENDIAN then
  begin
    ResHeader^.count:=SwapEndian(ResHeader^.count);
    ResHeader^.nodesize:=SwapEndian(ResHeader^.nodesize);
    ResHeader^.hdrsize:=SwapEndian(ResHeader^.hdrsize);
    FixResEndian;
  end;
  reshandles:=GetMem(sizeof(Pointer)*ResHeader^.count);
  FillByte(reshandles^,sizeof(Pointer)*ResHeader^.count,0);
end;

procedure FinalizeResources;
begin
  if ResHeader=nil then exit;
  FreeMem(reshandles);
  Fpmunmap(ResHeader,fd_size);
  FpClose(fd);
end;
{$ENDIF}

{$IFDEF EXTRES_GENERIC}
{$IFNDEF CPUJVM}
procedure InitResources;
var respath : PAnsiChar;
    tmp : longword;
    tmpptr : pbyte;
label ExitErrMem, ExitErrFile, ExitNoErr;
begin
  respath:=GetExtResPath;
//  writeln('respath ',respath);
  Assign(fd,respath);
  FreeMem(respath);
  {$I-}
  Reset(fd,1);
  {$I+}
  if IOResult<>0 then exit;
//  writeln('file opened');
  ResHeader:=GetMem(sizeof(TExtHeader));
  if ResHeader=nil then goto ExitErrFile;
  {$I-}
  BlockRead(fd,ResHeader^,sizeof(TExtHeader),tmp);
  {$I+}
  if (IOResult<>0) or (tmp<>sizeof(TExtHeader)) then goto ExitErrMem;
  if (ResHeader^.magic<>FPCRES_MAGIC) or (ResHeader^.version<>fpcres_version)
    then goto ExitErrMem;
//  writeln('magic ok');
  if ResHeader^.endianess<>FPCRES_ENDIAN then
  begin
    ResHeader^.count:=SwapEndian(ResHeader^.count);
    ResHeader^.nodesize:=SwapEndian(ResHeader^.nodesize);
    ResHeader^.hdrsize:=SwapEndian(ResHeader^.hdrsize);
  end;
  SysReallocMem(ResHeader,ResHeader^.hdrsize);
  if ResHeader=nil then goto ExitErrFile;
  tmpptr:=pbyte(ResHeader);
  inc(tmpptr,sizeof(TExtHeader));
  {$I-}
  BlockRead(fd,tmpptr^,ResHeader^.hdrsize-sizeof(TExtHeader),tmp);
  {$I+}
  if (IOResult<>0) or (tmp<>ResHeader^.hdrsize-sizeof(TExtHeader)) then goto ExitErrMem;
  if ResHeader^.endianess<>FPCRES_ENDIAN then
    FixResEndian;
  reshandles:=GetMem(sizeof(TResHandle)*ResHeader^.count);
  FillByte(reshandles^,sizeof(TResHandle)*ResHeader^.count,0);
  goto ExitNoErr;

  ExitErrMem:
    FreeMem(ResHeader);
    ResHeader:=nil;
  ExitErrFile:
    {$I-}
    Close(fd);
    {$I+}
  ExitNoErr:
end;
{$ELSE CPUJVM}
procedure InitResources;
var rec : TExtHeader;
    iserror : boolean = false;
    datasize,
    index,
    position,
    stop : longint;
    text : AnsistringClass;
begin
  FPCRES_ENDIAN:=GetEndian;
  nodelist:=nil;
  stringtable:=nil;
  ResHandles:=nil;
  datasize:=0;
  position:=0;
  resourcefilebytes:=ExtReadResourceFile(GetExtResPath);
  iserror:=
    (resourcefilebytes=nil) or
    (length(resourcefilebytes)<sizeof(TExtHeader));
  if not iserror then
  begin
    ResHeader:=@rec;
    move(resourcefilebytes,position,ResHeader^,0,sizeof(TExtHeader));
    inc(position,sizeof(TExtHeader));
    iserror:=
      (ResHeader^.magic<>FPCRES_MAGIC) or
      (ResHeader^.version<>FPCRES_VERSION);
  end;
  if not iserror then
  begin
    if (ResHeader^.endianess<>FPCRES_ENDIAN) then
    begin
      ResHeader^.count:=swapendian(ResHeader^.count);
      ResHeader^.nodesize:=swapendian(ResHeader^.nodesize);
      ResHeader^.hdrsize:=swapendian(ResHeader^.hdrsize);
    end;
    iserror:=
      (length(resourcefilebytes)<ResHeader^.hdrsize) or
      (ResHeader^.nodesize>ResHeader^.hdrsize) or
      (ResHeader^.nodesize<sizeof(TExtHeader)) or
      ((ResHeader^.nodesize-sizeof(TExtHeader)) mod sizeof(longword)<>0);
  end;
  if not iserror then
  begin
    if (ResHeader^.endianess<>FPCRES_ENDIAN) then
      FixResEndian;
    setlength(ResHandles,ResHeader^.count);
    datasize:=ResHeader^.nodesize-sizeof(TExtHeader);
    iserror:=
      (datasize<0) or
      (datasize mod sizeof(TResInfoNode)<>0);
  end;
  if not iserror then
  begin
    setlength(nodelist,datasize div sizeof(TResInfoNode));
    move(resourcefilebytes,position,nodelist,0,datasize);
    inc(position,datasize);
    stringtable:=_JUHashTable.Create;
    stop:=position;
    while (not iserror) and (stop<>ResHeader^.hdrsize) do
    begin
      { read each string (terminated with #0) and add it to the stringtable
        with the offset as the key }
      while (stop<>ResHeader^.hdrsize) and (resourcefilebytes[stop]<>0) do
        inc(stop);
      iserror:=(stop=ResHeader^.hdrsize);
      if not iserror then
      begin
        text:=AnsistringClass.Create(stop-position,CP_UTF8);
        for index:=0 to text.length-1 do
          ansistring(Text)[index+1]:=ansichar(resourcefilebytes[position+index]);
        stringtable.put(JLInteger.Create(position),text);
        position:=stop+1;
        stop:=position;
      end;
    end;
  end;
  if iserror then
  begin
    ResHandles:=nil;
    ResHeader:=nil;
    nodelist:=nil;
    stringtable:=nil;
    resourcefilebytes:=nil;
  end;
end;
{$ENDIF CPUJVM}

{$IFNDEF CPUJVM}
procedure FinalizeResources;
begin
  if ResHeader=nil then exit;
  FreeMem(reshandles);
  FreeMem(ResHeader);
  Close(fd);
end;
{$ENDIF CPUJVM}
{$ENDIF}

(*****************************************************************************
                             Public Resource Functions
*****************************************************************************)

Function ExtHINSTANCE : TFPResourceHMODULE;
begin
  ExtHINSTANCE:=0;
end;

function ExtEnumResourceTypes(ModuleHandle : TFPResourceHMODULE; EnumFunc : EnumResTypeProc; lParam : PtrInt) : LongBool;
var ptr : PResInfoNode;
    offset, totn, totid, i : longword;
    pc : PAnsiChar;
begin
  ExtEnumResourceTypes:=False;
  if ResHeader=nil then exit;
  ptr:=GetResInfoPtr(sizeof(TExtHeader));
  totn:=ptr^.ncounthandle;
  totid:=totn+ptr^.idcountsize;
  offset:=ptr^.subptr;
  ptr:=GetResInfoPtr(ptr^.subptr);
  ExtEnumResourceTypes:=true;
  i:=0;
  while i<totn do //named entries
  begin
    pc:=GetPChar(GetResInfoPtr(offset,i)^.nameid);
    if not EnumFunc(ModuleHandle,pc,lParam) then exit;
    inc(i);
  end;
  while i<totid do
  begin
    if not EnumFunc(ModuleHandle,IntAsName(GetResInfoPtr(offset,i)^.nameid),lParam) then exit;
    inc(i);
  end;
end;

function ExtEnumResourceNames(ModuleHandle : TFPResourceHMODULE; ResourceType : {$ifndef CPUJVM}PAnsiChar{$else}ansistring{$endif};
  EnumFunc : EnumResNameProc; lParam : PtrInt) : LongBool;
var ptr : PResInfoNode;
    offset : longint;
    totn, totid, i : longword;
    pc : PAnsiChar;
begin
  ExtEnumResourceNames:=False;
  if ResHeader=nil then exit;

  offset:=BinSearchRes(sizeof(TExtHeader),PAnsiChar(ResourceType));
  if offset=FPCRES_NODE_NOT_FOUND then exit;
  ptr:=GetResInfoPtr(offset);

  totn:=ptr^.ncounthandle;
  totid:=totn+ptr^.idcountsize;
  offset:=ptr^.subptr;
  ptr:=GetResInfoPtr(ptr^.subptr);
  ExtEnumResourceNames:=true;
  i:=0;
  while i<totn do //named entries
  begin
    pc:=GetPChar(GetResInfoPtr(offset,i)^.nameid);
    if not EnumFunc(ModuleHandle,ResourceType,pc,lParam) then exit;
    inc(i);
  end;
  while i<totid do
  begin
    if not EnumFunc(ModuleHandle,ResourceType,IntAsName(GetResInfoPtr(offset,i)^.nameid),lParam) then exit;
    inc(i);
  end;
end;

function ExtEnumResourceLanguages(ModuleHandle : TFPResourceHMODULE; ResourceType, ResourceName : {$ifndef CPUJVM}PAnsiChar{$else}ansistring{$endif};
  EnumFunc : EnumResLangProc; lParam : PtrInt) : LongBool;
var ptr : PResInfoNode;
    offset : longword;
    tot, i : integer;
begin
  ExtEnumResourceLanguages:=False;
  ptr:=InternalFindResource(PAnsiChar(ResourceName),PAnsiChar(ResourceType));
  if ptr=nil then exit;

  tot:=ptr^.idcountsize;
  offset:=ptr^.subptr;
  ptr:=GetResInfoPtr(ptr^.subptr);
  ExtEnumResourceLanguages:=true;
  i:=0;
  while i<tot do
  begin
    if not EnumFunc(ModuleHandle,ResourceType,ResourceName,PtrUInt(GetResInfoPtr(offset,i)^.nameid),lParam) then exit;
    inc(i);
  end;
end;

Function ExtFindResource(ModuleHandle: TFPResourceHMODULE; ResourceName, ResourceType: {$ifndef CPUJVM}PAnsiChar{$else}ansistring{$endif})
: TFPResourceHandle;
var ptr : PResInfoNode;
begin
  ExtFindResource:=0;
  ptr:=InternalFindResource(PAnsiChar(ResourceName),PAnsiChar(ResourceType));
  if ptr=nil then exit;

  //first language id
  ptr:=GetResInfoPtr(ptr^.subptr);
  if ptr^.ncounthandle=0 then
  begin
    {$IFDEF EXTRES_MMAP}
    reshandles[usedhandles]:=ptr;
    {$ENDIF}
    {$IFDEF EXTRES_GENERIC}
    reshandles[usedhandles].info:=ptr;
    {$ENDIF}
    inc(usedhandles);
    ptr^.ncounthandle:=usedhandles;
  end;
  ExtFindResource:=ptr^.ncounthandle;
end;

Function ExtFindResourceEx(ModuleHandle: TFPResourceHMODULE; ResourceType,
  ResourceName: {$ifndef CPUJVM}PAnsiChar{$else}ansistring{$endif}; Language : word): TFPResourceHandle;
const LANG_NEUTRAL = 0;
      LANG_ENGLISH = 9;
var nameptr,ptr : PResInfoNode;
begin
  ExtFindResourceEx:=0;
  nameptr:=InternalFindResource(PAnsiChar(ResourceName),PAnsiChar(ResourceType));
  if nameptr=nil then exit;

  //try exact match
  ptr:=FindSubLanguage(nameptr,Language,$FFFF);
  //try primary language
  if ptr=nil then
    ptr:=FindSubLanguage(nameptr,Language,$3FF);
  //try language neutral
  if ptr=nil then
    ptr:=FindSubLanguage(nameptr,LANG_NEUTRAL,$3FF);
  //try english
  if ptr=nil then
    ptr:=FindSubLanguage(nameptr,LANG_ENGLISH,$3FF);
  //nothing found, return the first one
  if ptr=nil then
    ptr:=GetResInfoPtr(nameptr^.subptr);

  if ptr^.ncounthandle=0 then
  begin
    {$IFDEF EXTRES_MMAP}
    reshandles[usedhandles]:=ptr;
    {$ENDIF}
    {$IFDEF EXTRES_GENERIC}
    reshandles[usedhandles].info:=ptr;
    {$ENDIF}
    inc(usedhandles);
    ptr^.ncounthandle:=usedhandles;
  end;
  ExtFindResourceEx:=ptr^.ncounthandle;
end;

{$IFDEF EXTRES_MMAP}
Function ExtLoadResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): TFPResourceHGLOBAL;
begin
  ExtLoadResource:=0;
  if ResHeader=nil then exit;
  if (ResHandle<=0) or (ResHandle>usedhandles) then exit;
  ExtLoadResource:=TFPResourceHGLOBAL(GetPtr(PResInfoNode(reshandles[ResHandle-1])^.subptr));
end;

Function ExtFreeResource(ResData: TFPResourceHGLOBAL): LongBool;
begin
  ExtFreeResource:=(ResHeader<>nil);
end;

Function ExtSizeofResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): LongWord;
begin
  ExtSizeofResource:=0;
  if ResHeader=nil then exit;
  if (ResHandle<=0) or (ResHandle>usedhandles) then exit;
  ExtSizeofResource:=PResInfoNode(reshandles[ResHandle-1])^.idcountsize;
end;
{$ENDIF}

{$IFDEF EXTRES_GENERIC}
(*
Resource data memory layout:
-2*sizeof(pointer)  Reference count
  -sizeof(pointer)  Pointer to resource info
                 0  Resource data
*)
Function ExtLoadResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): TFPResourceHGLOBAL;
var ptr : {$ifndef CPUJVM}PPtrUInt{$else}PResData{$endif};
    tmp : longword;
{$ifdef CPUJVM}
    rec : TResData;
    available : longint;
{$endif}
begin
  ExtLoadResource:=0;
  if ResHeader=nil then exit;
  if (ResHandle<=0) or (ResHandle>usedhandles) then exit;

  if reshandles[ResHandle-1].ptr=nil then
  begin
{$ifndef CPUJVM}
    {$I-}
    Seek(fd,reshandles[ResHandle-1].info^.subptr);
    {$I+}
    if IOResult<>0 then exit;
    ptr:=GetMem(reshandles[ResHandle-1].info^.idcountsize+2*sizeof(PtrUint));
    if ptr=nil then exit;
    ptr^:=1; //refcount
    inc(ptr);
    ptr^:=PtrUInt(reshandles[ResHandle-1].info); //ptr to resource info
    inc(ptr);
    {$I-}
    BlockRead(fd,ptr^,reshandles[ResHandle-1].info^.idcountsize,tmp);
    {$I+}
    if (IOResult<>0) or (tmp<>reshandles[ResHandle-1].info^.idcountsize) then
    begin
      FreeMem(ptr);
      exit;
    end;
{$else CPUJVM}
    available:=length(resourcefilebytes)-reshandles[ResHandle-1].info^.subptr;
    if reshandles[ResHandle-1].info^.idcountsize>available then exit;
    ptr:=@rec;
    ptr^.data:=nil;
    setlength(ptr^.data,reshandles[ResHandle-1].info^.idcountsize);
    ptr^.refcount:=1;
    ptr^.info:=reshandles[ResHandle-1].info;
    move(
      resourcefilebytes,reshandles[ResHandle-1].info^.subptr,
      ptr^.data,0,
      reshandles[ResHandle-1].info^.idcountsize);
{$endif CPUJVM}
    reshandles[ResHandle-1].ptr:=ptr;
  end
  else
  begin
    ptr:=reshandles[ResHandle-1].ptr;
{$ifndef CPUJVM}
    dec(ptr,2);
    inc(ptr^,1); //increase reference count
{$else CPUJVM}
    ptr^.refcount:=ptr^.refcount+1;
{$endif CPUJVM}
  end;
  ExtLoadResource:={$ifndef CPUJVM}TFPResourceHGLOBAL(reshandles[ResHandle-1].ptr){$else}ResHandle{$endif};
end;

Function ExtFreeResource(ResData: TFPResourceHGLOBAL): LongBool;
var ptrinfo : PResInfoNode;
    ptr : {$ifndef CPUJVM}PPtrUInt{$else}PResData{$endif};
{$ifdef CPUJVM}
    reshandle : TFPResourceHandle;
{$endif}
begin
  ExtFreeResource:=(ResHeader<>nil);
  if not ExtFreeResource then exit;
{$ifndef CPUJVM}
  ptr:=PPtrUInt(ResData);
  dec(ptr,2);
  dec(ptr^); //decrease reference count
{$else}
  reshandle:=ResData;
  ptr:=reshandles[reshandle-1].ptr;
  ptr^.refcount:=ptr^.refcount-1;
{$endif}
  if {$ifndef CPUJVM}ptr^{$else}ptr^.refcount{$endif}=0 then
  begin
{$ifndef CPUJVM}
    inc(ptr);
    ptrinfo:=PResInfoNode(ptr^);
    dec(ptr);
    FreeMem(ptr);
{$else}
    ptrinfo:=ptr^.info;
    ptr^.data:=nil;
{$endif}
    reshandles[ptrinfo^.ncounthandle-1].ptr:=nil;
  end;
  ExtFreeResource:=true;
end;

Function ExtSizeofResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): LongWord;
var ptrinfo : PResInfoNode;
begin
  ExtSizeofResource:=0;
  if ResHeader=nil then exit;
  if (ResHandle<=0) or (ResHandle>usedhandles) then exit;
  ptrinfo:=PResInfoNode(reshandles[ResHandle-1].info);
  ExtSizeofResource:=ptrinfo^.idcountsize;
end;
{$ENDIF}

Function ExtLockResource(ResData: {$ifndef CPUJVM}TFPResourceHGLOBAL{$else}JLInteger{$endif}): Pointer;
{$ifdef CPUJVM}
var reshandle : TFPResourceHandle;
{$endif}
begin
  ExtLockResource:=Nil;
  if ResHeader=nil then exit;
{$ifndef CPUJVM}
  ExtLockResource:=Pointer(ResData);
{$else}
  reshandle:=ResData.IntValue;
  ExtLockResource:=Pointer(ResHandles[reshandle-1].Ptr^.Data);
{$endif}
end;

Function ExtUnlockResource(ResData: TFPResourceHGLOBAL): LongBool;
begin
  ExtUnlockResource:=(ResHeader<>nil);
end;

const
  ExternalResourceManager : TResourceManager =
  (
    HINSTANCEFunc : @ExtHINSTANCE;
    EnumResourceTypesFunc : @ExtEnumResourceTypes;
    EnumResourceNamesFunc : @ExtEnumResourceNames;
    EnumResourceLanguagesFunc : @ExtEnumResourceLanguages;
    FindResourceFunc : @ExtFindResource;
    FindResourceExFunc : @ExtFindResourceEx;
    LoadResourceFunc : @ExtLoadResource;
    SizeofResourceFunc : @ExtSizeofResource;
    LockResourceFunc : @ExtLockResource;
    UnlockResourceFunc : @ExtUnlockResource;
    FreeResourceFunc : @ExtFreeResource;
  );
