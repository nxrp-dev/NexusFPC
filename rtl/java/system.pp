{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2006 by Florian Klaempfl
    member of the Free Pascal development team.

    System unit for embedded systems

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

Unit System;

{$namespace org.freepascal.rtl}

{*****************************************************************************}
                                    interface
{*****************************************************************************}

{$define FPC_IS_SYSTEM}

{$define DISABLE_NO_THREAD_MANAGER}
{$define FPC_NO_DEFAULT_HEAP}

{$I-,Q-,H-,R-,V-,P+,T+}
{$implicitexceptions off}
{$mode objfpc}
{$modeswitch advancedrecords}

Type
  { Java primitive types }
  jboolean = boolean;
  pjboolean = ^boolean;
  jbyte = shortint;
  pjbyte = ^jbyte;
  jshort = smallint;
  pjshort = ^jshort;
  jint = longint;
  pjint = ^jint;
  jlong = int64;
  pjlong = ^jlong;
  jchar = widechar;
  pjchar = ^jchar;
  jfloat = single;
  pjfloat = ^jfloat;
  jdouble = double;
  pjdouble = ^jdouble;

  Arr1jboolean = array of jboolean;
  Arr1jbyte = array of jbyte;
  Arr1jshort = array of jshort;
  Arr1jint = array of jint;
  Arr1jlong = array of jlong;
  Arr1jchar = array of jchar;
  Arr1jfloat = array of jfloat;
  Arr1jdouble = array of jdouble;

  Arr2jboolean = array of Arr1jboolean;
  Arr2jbyte = array of Arr1jbyte;
  Arr2jshort = array of Arr1jshort;
  Arr2jint = array of Arr1jint;
  Arr2jlong = array of Arr1jlong;
  Arr2jchar = array of Arr1jchar;
  Arr2jfloat = array of Arr1jfloat;
  Arr2jdouble = array of Arr1jdouble;

  Arr3jboolean = array of Arr2jboolean;
  Arr3jbyte = array of Arr2jbyte;
  Arr3jshort = array of Arr2jshort;
  Arr3jint = array of Arr2jint;
  Arr3jlong = array of Arr2jlong;
  Arr3jchar = array of Arr2jchar;
  Arr3jfloat = array of Arr2jfloat;
  Arr3jdouble = array of Arr2jdouble;

const
  maxExitCode = 255;


{ Java base class type }
{$ifdef java}
{$define GOTJAVASYSINCLUDE}
{$i java_sysh.inc}
{$i java_sys.inc}
{$endif}

{$ifdef android}
{$define GOTJAVASYSINCLUDE}
{$i java_sysh_android.inc}
{$i java_sys_android.inc}
{$endif}

{$ifndef GOTJAVASYSINCLUDE}
{$error Missing include file with base Java classes}
{$endif}

  FpcEnumValueObtainable = interface
    function fpcOrdinal: jint;
    function fpcGenericValueOf(__fpc_int: longint): JLEnum;
  end;

{ generic versions are based on FPC/Delphi-style RTTI }
{$define FPC_STR_ENUM_INTERN}

{$i jrech.inc}
{$i jseth.inc}
{$i jpvarh.inc}

{$i jsystemh_types.inc}

{$i jtvarh.inc}
{$i jsstringh.inc}
{$i jdynarrh.inc}
{$i jastringh.inc}
{$i justringh.inc}

{$i jsystemh.inc}
{$i jtconh.inc}

const
{$ifdef FPC_UNICODESTRINGS}
  LineEnding: unicodestring = '';
  DirectorySeparator: WideChar = #0;
  PathSeparator: WideChar = #0;
{$else FPC_UNICODESTRINGS}
  LineEnding: ansistring = '';
  DirectorySeparator: AnsiChar = #0;
  PathSeparator: AnsiChar = #0;
{$endif FPC_UNICODESTRINGS}
  AllowDirectorySeparators: set of AnsiChar = ['\','/'];
  CtrlZMarksEOF: Boolean = False;
  DefaultTextLineBreakStyle: TTextLineBreakStyle = tlbsLF;

{$ifdef FPC_HAS_FEATURE_COMMANDARGS}
var
  argc: longint = 0;
  argv: array of ansistring = nil;
  argvw: array of unicodestring = nil;
{$endif FPC_HAS_FEATURE_COMMANDARGS}

{*****************************************************************************}
                                 implementation
{*****************************************************************************}

type
  _JLStackTraceElement = class sealed external 'java.lang' name 'StackTraceElement' (JLObject)
  public
    function getFileName(): JLString; overload; virtual;
    function getLineNumber(): jint; overload; virtual;
    function getMethodName(): JLString; overload; virtual;
  end;

  _Arr1JLStackTraceElement = array of _JLStackTraceElement;

  _JLThrowable = class external 'java.lang' name 'Throwable' (JLObject)
  public
    function getCause(): _JLThrowable; overload; virtual;
    function getStackTrace(): _Arr1JLStackTraceElement; overload; virtual;
    function getMessage(): JLString; overload; virtual;
  end;

  _JLException = class external 'java.lang' name 'Exception' (_JLThrowable);
  _JLRuntimeException = class external 'java.lang' name 'RuntimeException' (_JLException);
  _JIIOException = class external 'java.io' name 'IOException' (_JLException);
  _JLSecurityException = class external 'java.lang' name 'SecurityException' (_JLRuntimeException);
  _JNCClosedChannelException = class external 'java.nio.channels' name 'ClosedChannelException' (_JIIOException);
  _JIFileNotFoundException = class external 'java.io' name 'FileNotFoundException' (_JIIOException);
  _JLArithmeticException = class external 'java.lang' name 'ArithmeticException' (_JLRuntimeException);
  _JLNullPointerException = class external 'java.lang' name 'NullPointerException' (_JLRuntimeException);
  _JLIndexOutOfBoundsException = class external 'java.lang' name 'IndexOutOfBoundsException' (_JLRuntimeException);
  _JLClassCastException = class external 'java.lang' name 'ClassCastException' (_JLRuntimeException);

  _JIByteArrayOutputStream = class external 'java.io' name 'ByteArrayOutputStream' (JLObject)
  public
    constructor create(); overload;
    procedure write(para1: Arr1jbyte; para2: jint; para3: jint); overload; virtual;
    function toByteArray(): Arr1jbyte; overload; virtual;
  end;

  _JNCFileChannel = class abstract external 'java.nio.channels' name 'FileChannel' (JLObject)
  public
    function truncate(size: jlong): _JNCFileChannel; overload; virtual; abstract;
    function position: jlong; overload; virtual; abstract;
  end;

  _JIRandomAccessFile = class external 'java.io' name 'RandomAccessFile' (JLObject)
  public
    constructor create(aFile: JLString; aMode: JLString); overload;
    function getChannel: _JNCFileChannel; overload; virtual; final;
    function read(b: Arr1jbyte; off: jint; len: jint): jint; overload; virtual;
    procedure write(b: Arr1jbyte; off: jint; len: jint); overload; virtual;
    procedure seek(aPosition: jlong); overload; virtual;
    function length: jlong; external name 'length'; overload; virtual;
    procedure setLength(para1: jlong); overload; virtual;
    procedure close; overload; virtual;
  end;

  _JIFile = class external 'java.io' name 'File' (JLObject)
  public final class var
    fseparatorChar: jchar; external name 'separatorChar';
    fpathSeparatorChar: jchar; external name 'pathSeparatorChar';
  public
    constructor create(para1: JLString); overload;
    function getName(): JLString; overload; virtual;
    function getParent(): JLString; overload; virtual;
    function delete(): jboolean; overload; virtual;
    function mkdir(): jboolean; overload; virtual;
    function renameTo(para1: _JIFile): jboolean; overload; virtual;
    function exists(): jboolean; overload; virtual;
   end;

  _JIPrintStream = class external 'java.io' name 'PrintStream' (JLObject)
  public
    procedure write(buf: Arr1jbyte; off: jint; len: jint); overload; virtual;
    procedure print(para1: JLString);
    procedure println(para1: JLString);
  end;

  _JLSystem = class sealed external 'java.lang' name 'System' (JLObject)
  public final class var
    fout: _JIPrintStream; external name 'out';
    ferr: _JIPrintStream; external name 'err';
  end;

  _JIInputStream = class abstract external 'java.io' name 'InputStream' (JLObject)
  public
    function read(b: Arr1jbyte; off: jint; len: jint): jint; overload; virtual;
  end;

  _JLClassLoader = class abstract external 'java.lang' name 'ClassLoader' (JLObject)
  public
    function getResourceAsStream(name: JLString): _JIInputStream; overload; virtual;
  end;

  _JLThread = class external 'java.lang' name 'Thread' (JLObject)
  public type
    InnerUncaughtExceptionHandler = interface external 'java.lang' name 'UncaughtExceptionHandler'
      procedure uncaughtException(para1: _JLThread; para2: _JLThrowable); overload;
    end;
  public
    class procedure setDefaultUncaughtExceptionHandler(
      para1: _JLThread.InnerUncaughtExceptionHandler); static; overload;
  public const
    MIN_PRIORITY = 1;
    NORM_PRIORITY = 5;
    MAX_PRIORITY = 10;
  public
    class function currentThread(): _JLThread; static; overload;
    class procedure yield(); static; overload;
    class procedure sleep(para1: jlong); static; overload;
    constructor create(); overload;
    procedure start(); overload; virtual;
    procedure run(); overload; virtual;
    procedure interrupt(); overload; virtual;
    function isAlive(): jboolean; overload; virtual; final;
    procedure setPriority(para1: jint); overload; virtual; final;
    function getPriority(): jint; overload; virtual; final;
    procedure setName(para1: JLString); overload; virtual; final;
    function getName(): JLString; overload; virtual; final;
    function getStackTrace(): _Arr1JLStackTraceElement; overload; virtual;
    function getContextClassLoader(): _JLClassLoader; overload; virtual;
    function getId(): jlong; overload; virtual;
  end;

  _JLRuntime = class external 'java.lang' name 'Runtime' (JLObject)
  public
    class function getRuntime(): _JLRuntime; static; overload;
    procedure addShutdownHook(para1: _JLThread); overload; virtual;
    function removeShutdownHook(para1: _JLThread): jboolean; overload; virtual;
  end;

  _JLMRuntimeMXBean = interface external 'java.lang.management' name 'RuntimeMXBean'
    function getName(): JLString; overload;
  end;

  _JLMManagementFactory = class external 'java.lang.management' name 'ManagementFactory' (JLObject)
  public
    class function getRuntimeMXBean(): _JLMRuntimeMXBean; static; overload;
  end;

  _JUCLCondition = interface external 'java.util.concurrent.locks' name 'Condition'
    procedure await(); overload;
    function awaitNanos(nanosTimeout: jlong): jlong; overload;
    procedure signal(); overload;
    procedure signalAll(); overload;
  end;

  _JUCLReentrantLock = class external 'java.util.concurrent.locks' name 'ReentrantLock' (JLObject)
  public
    constructor create(); overload;
    procedure lock(); overload; virtual;
    procedure lockInterruptibly(); overload; virtual;
    function tryLock(): jboolean; overload; virtual;
    procedure unlock(); overload; virtual;
    function newCondition(): _JUCLCondition; overload; virtual;
    function getHoldCount(): jint; overload; virtual;
    function isHeldByCurrentThread(): jboolean; overload; virtual;
    function isLocked(): jboolean; overload; virtual;
    function isFair(): jboolean; overload; virtual; final;
  public
    function hasQueuedThreads(): jboolean; overload; virtual; final;
    function getQueueLength(): jint; overload; virtual; final;
  public
    function hasWaiters(para1: _JUCLCondition): jboolean; overload; virtual;
    function getWaitQueueLength(para1: _JUCLCondition): jint; overload; virtual;
  end;

  _JUHashTable = class external 'java.util' name 'Hashtable' (JLObject)
  public
    constructor create(); overload;
    function containsValue(para1: JLObject): jboolean; overload; virtual;
    function containsKey(para1: JLObject): jboolean; overload; virtual;
    function get(para1: JLObject): JLObject; overload; virtual;
    function put(para1: JLObject; para2: JLObject): JLObject; overload; virtual;
    function remove(para1: JLObject): JLObject; overload; virtual;
  end;

  _JUCConcurrentHashMap = class external 'java.util.concurrent' name 'ConcurrentHashMap' (JLObject)
  public
    constructor create(); overload;
    function get(para1: JLObject): JLObject; overload; virtual;
    function containsKey(para1: JLObject): jboolean; overload; virtual;
    function put(para1: JLObject; para2: JLObject): JLObject; overload; virtual;
    function remove(para1: JLObject): JLObject; overload; virtual;
  end;

  _JLRConstructor = class sealed external 'java.lang.reflect' name 'Constructor' (JLRAccessibleObject)
  public
    function newInstance(para1: Arr1JLObject): JLObject; overload; virtual;
  end;

  _JLClass = class sealed external 'java.lang' name 'Class' (JLObject)
  public
    function getConstructor(para1: Arr1JLClass): _JLRConstructor; overload; virtual;
  end;

{$ifdef ANDROID}

type
  _ACRAssetManager = class sealed external 'android.content.res' name 'AssetManager' (JLObject)
  public
    function list(para1: JLString): Arr1JLString; overload; virtual; final;
    function open(para1: JLString): _JIInputStream; overload; virtual; final;
  end;

  _ACContext = class abstract external 'android.content' name 'Context' (JLObject)
  public
    function getAssets(): _ACRAssetManager; overload; virtual; abstract;
  end;

{$endif ANDROID}

function AsObject(const buf): JLObject;
  { use this function to box any built-in type as a java object }
  begin
    result:=JLObject(buf)
  end;

function min(a,b : longint) : longint;
  begin
     if a<=b then
       min:=a
     else
       min:=b;
  end;

{$i jtcon.inc}
{$i jtvar.inc}
{$i jsstrings.inc}
{$i jastrings.inc}
{$i justrings.inc}
{$i jrec.inc}
{$i jset.inc}
{$i jpvar.inc}
{$i jdynarr.inc}
{$i jsystem.inc}


{*****************************************************************************
                       Misc. System Dependent Functions
*****************************************************************************}

procedure System_exit;
  begin
    JLRuntime.getRuntime.exit(ExitCode);
  end;


procedure randomize;
  begin
    randseed:=JUCalendar.getInstance.getTimeInMillis;
  end;


type
  CopyOutVarModifiedException = class(JLException)
  end;

procedure fpc_var_copyout_mismatch(line,column: longint); compilerproc;
  var
    linestr,columnstr: unicodestring;
  begin
    str(line,linestr);
    str(column,columnstr);
    raise CopyOutVarModifiedException.create('Var parameter ending at line '+linestr+' column '+columnstr+' in the previous stack frame has been modified to a different value than the returned copyback value');
  end;

procedure SetupOSConstants;
var
  os : JLString;
begin
  LineEnding:=JLSystem.GetProperty('line.separator');
  case ansistring(LineEnding) of
    #13#10: DefaultTextLineBreakStyle:=tlbsCRLF;
    #13: DefaultTextLineBreakStyle:=tlbsCR;
  else
    DefaultTextLineBreakStyle:=tlbsLF;
  end;
  DirectorySeparator:=_JIFile.fseparatorChar;
  PathSeparator:=_JIFile.fpathSeparatorChar;
  // some constants are not exposed by java
  os:=JLSystem.GetProperty('os.name').ToLowercase;
  CtrlZMarksEOF:=os.Contains(JLString('windows'));
end;

{$ifdef FPC_HAS_FEATURE_COMMANDARGS}
function TryReadArgument(
  const s: unicodestring;
  var index: longint;
  out first,stop: longint): boolean;
  begin
    first:=index;
    while (first<>length(s)) and (s[first+1]=' ') do
      inc(first);
    if first<>length(s) then
      if (s[first+1]='''') or (s[first+1]='"') then
        begin
          stop:=first+1;
          while (stop<>length(s)) and (s[stop+1]<>s[first+1]) do
            inc(stop);
          inc(first);
          index:=stop;
        end
      else
        begin
          stop:=first;
          while (stop<>length(s)) and (s[stop+1]<>' ') do
            inc(stop);
          index:=stop;
        end;
    result:=(first<>length(s));
  end;

procedure SetupArguments;
  const
    maxArgCount = 128;
  var
    s : unicodestring;
    charIndex,first,stop,argIndex : longint;
    buffer : array[0..maxArgCount-1] of unicodestring;
  begin
    argc:=0;
    argv:=nil;
    argvw:=nil;
    // this property may not be available on every java virtual machine (in which case it will be an empty string)
    s:=JLSystem.GetProperty('sun.java.command');
    if length(s)<>0 then
      begin
        charIndex:=0;
        argIndex:=0;
        while (argIndex<>maxArgCount) and (TryReadArgument(s,charIndex,first,stop)) do
          begin
            buffer[argIndex]:=copy(s,first+1,stop-first);
            inc(argIndex);
          end;
        argc:=argIndex;
        setlength(argv,argc+1);
        setlength(argvw,argc+1);
        for argIndex:=0 to argc-1 do
          begin
            argv[argIndex]:=ansistring(buffer[argIndex]);
            argvw[argIndex]:=buffer[argIndex];
          end;
        // for consistency follow other platforms and add final empty item to argv
        argv[argc]:='';
        argvw[argc]:='';
      end;
  end;

function paramcount: longint;
  begin
    paramcount:=argc-1;
  end;

{$ifdef FPC_UNICODESTRINGS}
function paramstr(l: longint): unicodestring;
  begin
    if (l>=0) and (l<argc) then
      result:=argvw[l]
    else
      result:='';
  end;
{$else FPC_UNICODESTRINGS}
function paramstr(l: longint): ansistring;
  begin
    if (l>=0) and (l<argc) then
      result:=argv[l]
    else
      result:='';
  end;
{$endif FPC_UNICODESTRINGS}
{$endif FPC_HAS_FEATURE_COMMANDARGS}

{*****************************************************************************
                         SystemUnit Initialization
*****************************************************************************}

{$ifdef FPC_HAS_FEATURE_PROCESSES}
{ JVM Notes:
  * no guaranteed standard way to get the process ID, may return zero on some jvm implementations
  * the call to GetRuntimeMXBean().GetName() may randomly and permanently freeze on haiku }
function GetProcessID: SizeUInt;
  var
    name: shortstring;
    index: longint;
  begin
    result:=0;
    name:=shortstring(_JLMManagementFactory.GetRuntimeMXBean.GetName);
    index:=0;
    while (index<>length(name)) and (name[index+1] in ['0'..'9']) do
      begin
        result:=(result*10)+(ord(name[index+1])-ord('0'));
        inc(index);
      end;
    if (index=length(name)) or (name[index+1]<>'@') then
      result:=0;
  end;
{$endif FPC_HAS_FEATURE_PROCESSES}

begin
  InitUnicodeStringManager;
  SetupOSConstants;
  {$ifdef FPC_HAS_FEATURE_COMMANDARGS}
  SetupArguments;
  {$endif FPC_HAS_FEATURE_COMMANDARGS}
  {$ifdef FPC_HAS_FEATURE_CONSOLEIO}
  SysInitStdIO;
  InOutRes:=0;
  {$endif FPC_HAS_FEATURE_CONSOLEIO}
  {$ifdef FPC_HAS_FEATURE_THREADING}
  InitSystemThreads;
  {$endif FPC_HAS_FEATURE_THREADING}
  {$ifdef FPC_HAS_FEATURE_RESOURCES}
  {$ifndef ANDROID}
  { android must initialise resources manually as a reference to the activity is needed }
  InitResources(nil);
  {$endif ANDROID}
  SetResourceManager(ExternalResourceManager);
  {$endif FPC_HAS_FEATURE_RESOURCES}
  InstallShutdownHook;
  InstallExceptionHandler;
end.

