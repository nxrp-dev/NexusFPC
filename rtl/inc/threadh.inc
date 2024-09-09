{
    This file is part of the Free Pascal Run time library.
    Copyright (c) 2000 by the Free Pascal development team

    This file contains the OS indenpendend declartions for multi
    threading support in FPC

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

const
{$ifndef FPC_USE_SMALL_DEFAULTSTACKSIZE}
  { includes 16384 bytes margin for stackchecking }
  DefaultStackSize = 4*1024*1024;
{$else i.e. FPC_USE_SMALL_DEFAULTSTACKSIZE}
  { Special value of Default stack size }
  DefaultStackSize = 16 * 1024;
{$endif not FPC_USE_SMALL_DEFAULTSTACKSIZE}

{ every platform can have it's own implementation of GetCPUCount; use the define
  HAS_GETCPUCOUNT to disable the default implementation which simply returns 1 }
function GetCPUCount: LongWord;

property CPUCount: LongWord read GetCPUCount;

type
  PEventState = pointer;
  {$ifndef CPUJVM}
  PRTLEvent   = type pointer;   // Windows=thandle, other=pointer to record.
  {$else}
  TRTLEvent = record
    OuterLock: JLObject;
    Condition: JLObject;
    IsSet: Boolean;
  end;
  PRTLEvent   = ^TRTLEvent;
  {$endif}
  TThreadFunc = function(parameter : pointer) : ptrint;
  trtlmethod  = procedure of object;

  // Function prototypes for TThreadManager Record.
  TInitManagerHandler = Function : boolean;
  TDoneManagerHandler = Function : boolean;
  { JVM Notes: on cpujvm using a "var" or "out" parameter here will crash the compiler (internal error 2018042601) }
  TBeginThreadHandler = Function (sa : Pointer;stacksize : PtrUInt; ThreadFunction : tthreadfunc;p : pointer;creationFlags : dword{$ifndef CPUJVM}; var ThreadId : TThreadID{$endif}) : TThreadID;
  TEndThreadHandler = Procedure (ExitCode : DWord);
  // Used for Suspend/Resume/Kill
  TThreadHandler = Function (threadHandle : TThreadID) : dword;
  TThreadSwitchHandler = Procedure;
  TWaitForThreadTerminateHandler = Function (threadHandle : TThreadID; TimeoutMs : longint) : dword;  {0=no timeout}
  TThreadSetPriorityHandler = Function (threadHandle : TThreadID; Prio: longint): boolean;            {-15..+15, 0=normal}
  TThreadGetPriorityHandler = Function (threadHandle : TThreadID): longint;
  TGetCurrentThreadIdHandler = Function : TThreadID;
  TThreadSetThreadDebugNameHandlerA = procedure(threadHandle: TThreadID; const ThreadName: AnsiString);
{$ifdef FPC_HAS_FEATURE_UNICODESTRINGS}
  TThreadSetThreadDebugNameHandlerU = procedure(threadHandle: TThreadID; const ThreadName: UnicodeString);
{$endif FPC_HAS_FEATURE_UNICODESTRINGS}
  { JVM Notes: on cpujvm using an untyped "var" or "out" parameter here will crash the compiler (internal error 2018042601) }
  TCriticalSectionHandler = Procedure (var cs{$ifdef CPUJVM} : TRTLCriticalSection{$endif});
  TCriticalSectionHandlerTryEnter = function (var cs{$ifdef CPUJVM} : TRTLCriticalSection{$endif}):longint;
  TInitThreadVarHandler = Procedure(var offset : {$ifdef cpu16}word{$else}dword{$endif};size : dword);
  { JVM Notes: on cpujvm mixing a primitive type and a pointer type in the same callback
      will crash the compiler (internal error 2018042601) so we use JLInteger instead of dword }
  TRelocateThreadVarHandler = Function(offset : {$ifdef CPUJVM}JLInteger{$else}{$ifdef cpu16}word{$else}dword{$endif}{$endif}) : pointer;
  TAllocateThreadVarsHandler = Procedure;
  TReleaseThreadVarsHandler = Procedure;
  {$ifndef CPUJVM}
  { JVM Notes: deprecated so not implemented for cpujvm }
  TBasicEventHandler        = procedure(state:peventstate);
  TBasicEventWaitForHandler = function (timeout:cardinal;state:peventstate;FUseComWait : Boolean=False):longint;
  TBasicEventCreateHandler  = function (EventAttributes :Pointer;  AManualReset,InitialState : Boolean;const Name:ansistring):pEventState;
  {$endif}
  TRTLEventHandler          = procedure(AEvent:PRTLEvent);
  TRTLEventHandlerTimeout   = procedure(AEvent:PRTLEvent;timeout : longint);
  TRTLCreateEventHandler    = function:PRTLEvent;
  // semaphores stuff
  TSempahoreInitHandler     = function: Pointer;
  TSemaphoreDestroyHandler  = procedure (const sem: Pointer);
  TSemaphorePostHandler     = procedure (const sem: Pointer);
  TSemaphoreWaitHandler     = procedure (const sem: Pointer);

  // TThreadManager interface.
  { JVM Notes: predeclare the callback type because using the same inline signature more than once will
      cause a verifier crash at runtime (ClassFormatError: Duplicate entry in InnerClasses attribute) }
  TThreadManager = Record
    InitManager            : TInitManagerHandler;
    DoneManager            : TDoneManagerHandler;
    BeginThread            : TBeginThreadHandler;
    EndThread              : TEndThreadHandler;
    SuspendThread          : TThreadHandler;
    ResumeThread           : TThreadHandler;
    KillThread             : TThreadHandler;
    CloseThread            : TThreadHandler;
    ThreadSwitch           : TThreadSwitchHandler;
    WaitForThreadTerminate : TWaitForThreadTerminateHandler;
    ThreadSetPriority      : TThreadSetPriorityHandler;
    ThreadGetPriority      : TThreadGetPriorityHandler;
    GetCurrentThreadId     : TGetCurrentThreadIdHandler;
    SetThreadDebugNameA    : TThreadSetThreadDebugNameHandlerA;
{$ifdef FPC_HAS_FEATURE_UNICODESTRINGS}
    SetThreadDebugNameU    : TThreadSetThreadDebugNameHandlerU;
{$endif FPC_HAS_FEATURE_UNICODESTRINGS}
    InitCriticalSection    : TCriticalSectionHandler;
    DoneCriticalSection    : TCriticalSectionHandler;
    EnterCriticalSection   : TCriticalSectionHandler;
    TryEnterCriticalSection: TCriticalSectionHandlerTryEnter;
    LeaveCriticalSection   : TCriticalSectionHandler;
    InitThreadVar          : TInitThreadVarHandler;
    RelocateThreadVar      : TRelocateThreadVarHandler;
    AllocateThreadVars     : TAllocateThreadVarsHandler;
    ReleaseThreadVars      : TReleaseThreadVarsHandler;
    {$ifndef CPUJVM}
    { JVM Notes: deprecated so not implemented for cpujvm }
    BasicEventCreate       : TBasicEventCreateHandler;      // left in for a while.
    BasicEventDestroy      : TBasicEventHandler;            // we might need BasicEvent
    BasicEventResetEvent   : TBasicEventHandler;            // for a real TEvent
    BasicEventSetEvent     : TBasicEventHandler;
    BasiceventWaitFOr      : TBasicEventWaitForHandler;
    {$endif}
    RTLEventCreate         : TRTLCreateEventHandler;
    RTLEventDestroy        : TRTLEventHandler;
    RTLEventSetEvent       : TRTLEventHandler;
    RTLEventResetEvent     : TRTLEventHandler;
    RTLEventWaitFor        : TRTLEventHandler;
    RTLEventWaitForTimeout : TRTLEventHandlerTimeout;
  end;

{*****************************************************************************
                         Thread Handler routines
*****************************************************************************}


Function GetThreadManager(Out TM : TThreadManager) : Boolean;
Function SetThreadManager(Const NewTM : TThreadManager; Out OldTM : TThreadManager) : Boolean;
Function SetThreadManager(Const NewTM : TThreadManager) : Boolean;
{$ifndef DISABLE_NO_THREAD_MANAGER}
{$endif DISABLE_NO_THREAD_MANAGER}
{ Needs to be exported, so the manager can call it.
  It needs to be exported even if FPC_SECTION_THREADVARS is set as it relocates also the
  heap
}
procedure InitThreadVars(RelocProc : TRelocateThreadVarHandler);
procedure InitThread(stklen:SizeUInt);
procedure DoneThread;

{*****************************************************************************
                         Multithread Handling
*****************************************************************************}

function BeginThread(sa : Pointer;stacksize : SizeUInt;
  ThreadFunction : tthreadfunc;p : pointer;creationFlags : dword;
  var ThreadId : TThreadID) : TThreadID;

{ add some simplfied forms which make lifer easier and porting }
{ to other OSes too ...                                        }
function BeginThread(ThreadFunction : tthreadfunc) : TThreadID;
function BeginThread(ThreadFunction : tthreadfunc;p : pointer) : TThreadID;
function BeginThread(ThreadFunction : tthreadfunc;p : pointer; var ThreadId : TThreadID) : TThreadID;
function BeginThread(ThreadFunction : tthreadfunc;p : pointer;
                     var ThreadId : TThreadID; const stacksize: SizeUInt) : TThreadID;

procedure EndThread(ExitCode : DWord);
procedure EndThread;

{some thread support functions}
procedure FlushThread;
{$ifndef CPUJVM}
{ JVM Notes: there is no api to suspend a jvm thread }
function  SuspendThread (threadHandle : TThreadID) : dword;
{$endif}
{$ifndef CPUJVM}
{ JVM Notes: there is no api to resume a jvm thread }
function  ResumeThread  (threadHandle : TThreadID) : dword;
{$endif}
function  CloseThread   (threadHandle : TThreadID) : dword;
procedure ThreadSwitch;                                                                {give time to other threads}
{$ifndef CPUJVM}
{ JVM Notes: there is no api to kill a jvm thread but also the program will never exit if any
    background thread is still running, consider using a process instead for blocking operations }
function  KillThread (threadHandle : TThreadID) : dword;
{$endif}
function  WaitForThreadTerminate (threadHandle : TThreadID; TimeoutMs : longint) : dword;  {0=no timeout}
function  ThreadSetPriority (threadHandle : TThreadID; Prio: longint): boolean;            {-15..+15, 0=normal}
function  ThreadGetPriority (threadHandle : TThreadID): longint;
function  GetCurrentThreadId : TThreadID;
procedure SetThreadDebugName(threadHandle: TThreadID; const ThreadName: AnsiString);
{$ifdef FPC_HAS_FEATURE_UNICODESTRINGS}
procedure SetThreadDebugName(threadHandle: TThreadID; const ThreadName: UnicodeString);
{$endif FPC_HAS_FEATURE_UNICODESTRINGS}


{ this allows to do a lot of things in MT safe way }
{ it is also used to make the heap management      }
{ thread safe                                      }
procedure InitCriticalSection(out cs : TRTLCriticalSection);
procedure DoneCriticalSection(var cs : TRTLCriticalSection);
procedure EnterCriticalSection(var cs : TRTLCriticalSection);
procedure LeaveCriticalSection(var cs : TRTLCriticalSection);
function  TryEnterCriticalSection(var cs : TRTLCriticalSection):longint;
{$ifndef CPUJVM}
{ JVM Notes: Deprecated so not implemented for cpujvm. }
function  BasicEventCreate(EventAttributes : Pointer; AManualReset,InitialState : Boolean;const Name : ansistring):pEventState;
procedure BasicEventDestroy(state:peventstate);
procedure BasicEventResetEvent(state:peventstate);
procedure BasicEventSetEvent(state:peventstate);
function  BasicEventWaitFor(Timeout : Cardinal;state:peventstate;FUseComWait : Boolean=False) : longint;
{$endif}

function  RTLEventCreate :PRTLEvent;
procedure RTLEventDestroy(state:pRTLEvent);
procedure RTLEventSetEvent(state:pRTLEvent);
procedure RTLEventResetEvent(state:pRTLEvent);
procedure RTLEventWaitFor(state:pRTLEvent);
procedure RTLEventWaitFor(state:pRTLEvent;timeout : longint);

{$ifndef CPUJVM}
{ lazy thread initialization support }
procedure RegisterLazyInitThreadingProc(const proc: TProcedure);
{ do not call LazyInitThreading directly}
procedure LazyInitThreading;
{$endif}
