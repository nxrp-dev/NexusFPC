{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ Thread Table }

var
  ThreadTable: _JUCConcurrentHashMap = nil;

function TryGetThread(aThreadHandle: TThreadID; out aThread: _JLThread): Boolean;
var
  Key: JLLong;
begin
  Key := JLLong.Create(aThreadHandle);
  aThread := _JLThread(ThreadTable.Get(Key));
  Result := (aThread <> nil);
end;

{ Thread Class }

type
  TFpcThread = class(_JLThread)
  private
    FParameter: Pointer;
    FThreadFunction: TThreadFunc;
    FExitCode: DWord;
  public
    constructor Create(aParameter: Pointer; aThreadFunction: TThreadFunc);
    property ExitCode: DWord read FExitCode;
    procedure Run; override;
  end;

constructor TFpcThread.Create(aParameter: Pointer; aThreadFunction: TThreadFunc);
var
  Key: JLLong;
begin
  FParameter := aParameter;
  FThreadFunction := aThreadFunction;
  FExitCode := 0;
  Key := JLLong.Create(GetId);
  ThreadTable.Put(Key, Self);
end;

procedure TFpcThread.Run;
begin
  InitThread;
  ThreadId := _JLThread.CurrentThread.GetId;
  FExitCode := FThreadFunction(FParameter);
end;

{ Thread }

function SysBeginThread(
  SA: Pointer;
  StackSize: SizeUInt;
  ThreadFunction: TThreadFunc;
  P: Pointer;
  CreationFlags: DWord): TThreadID;
var
  Thread: TFpcThread;
begin
  IsMultiThread := True;
  Thread := TFpcThread.Create(P, ThreadFunction);
  Result := Thread.GetId;
  Thread.Start;
end;

procedure SysEndThread(ExitCode : DWord);
var
  Thread: _JLThread;
begin
  Thread := _JLThread.CurrentThread;
  if Thread is TFpcThread then
    TFpcThread(Thread).FExitCode := ExitCode;
  Thread.Interrupt;
end;

procedure SysThreadSwitch;
begin
  _JLThread.Yield;
end;

function SysCloseThread(ThreadHandle: TThreadID): DWord;
var
  Thread: _JLThread;
  Key: JLLong;
begin
  Result := Ord(True);
  Key := JLLong.Create(ThreadHandle);
  if ThreadTable.Remove(Key) = nil then
    Result := Ord(False);
end;

function SysWaitForThreadTerminate(ThreadHandle: TThreadID; TimeoutMs: LongInt): DWord;
const
  ThreadDoesNotExist = -1;
  ThreadDidNotExit = -2;
var
  Thread: _JLThread;
  StartNano: JLong;
  TimeoutNano: JLong;
begin
  Result := 0;
  if TryGetThread(ThreadHandle, Thread) then
  begin
    if TimeoutMs > 0 then
    begin
      StartNano := JLSystem.NanoTime;
      TimeoutNano := JLong(TimeoutMs) * 1000 * 1000;
      while (Thread.IsAlive) and (JLSystem.NanoTime - StartNano < TimeoutNano) do
        _JLThread.Sleep(1);
    end
    else
      while Thread.IsAlive do
        _JLThread.Sleep(1);

    if Thread.IsAlive then
      Result := DWord(ThreadDidNotExit)
    else if Thread is TFpcThread then
      Result := TFpcThread(Thread).ExitCode;
  end
  else
    Result := DWord(ThreadDoesNotExist);
end;

function ConvertPriority(
  aSourcePriority: LongInt;
  aMinSource: LongInt;
  aMaxSource: LongInt;
  aMinDestination: LongInt;
  aMaxDestination: LongInt): LongInt;
begin
  Result := Trunc(
    ( ( aSourcePriority - aMinSource ) / ( aMaxSource - aMinSource ) ) *
    ( aMaxDestination - aMinDestination ) ) + aMinDestination;
end;

function SysThreadSetPriority(ThreadHandle: TThreadID; Priority: LongInt): Boolean;
const
  FpcMinPriority = LongInt(-15);
  FpcNormalPriority = LongInt(0);
  FpcMaxPriority = LongInt(+15);
var
  JavaPriority: LongInt;
  Thread: _JLThread;
begin
  if Priority < FpcNormalPriority then
  begin
    JavaPriority := ConvertPriority(
      Priority,
      FpcMinPriority,
      FpcNormalPriority,
      _JLThread.MIN_PRIORITY,
      _JLThread.NORM_PRIORITY);
  end
  else if Priority > FpcNormalPriority then
  begin
    JavaPriority := ConvertPriority(
      Priority,
      FpcNormalPriority,
      FpcMaxPriority,
      _JLThread.NORM_PRIORITY,
      _JLThread.MAX_PRIORITY);
  end
  else
    JavaPriority := _JLThread.NORM_PRIORITY;

  Result := TryGetThread(ThreadHandle, Thread);
  if Result then
    Thread.SetPriority(JavaPriority);
end;

function SysThreadGetPriority(ThreadHandle: TThreadID): LongInt;
const
  FpcMinPriority = LongInt(-15);
  FpcNormalPriority = LongInt(0);
  FpcMaxPriority = LongInt(+15);
var
  Thread: _JLThread;
  JavaPriority: LongInt;
begin
  Result := FpcNormalPriority;
  if TryGetThread(ThreadHandle, Thread) then
  begin
    JavaPriority := Thread.GetPriority;
    if JavaPriority < _JLThread.NORM_PRIORITY then
    begin
      Result := ConvertPriority(
        JavaPriority,
        _JLThread.MIN_PRIORITY,
        _JLThread.NORM_PRIORITY,
        FpcMinPriority,
        FpcNormalPriority);
    end
    else if JavaPriority > _JLThread.NORM_PRIORITY then
    begin
      Result := ConvertPriority(
        JavaPriority,
        _JLThread.NORM_PRIORITY,
        _JLThread.MAX_PRIORITY,
        FpcNormalPriority,
        FpcMaxPriority);
    end;
  end;
end;

function SysGetCurrentThreadId: TThreadID;
begin
  Result := _JLThread.CurrentThread.GetId;
end;

procedure SysSetThreadDebugNameA(ThreadHandle: TThreadID; const ThreadName: ansistring);
var
  Thread: _JLThread;
begin
  if TryGetThread(ThreadHandle, Thread) then
    Thread.SetName(unicodestring(ThreadName));
end;

procedure SysSetThreadDebugNameU(ThreadHandle: TThreadID; const ThreadName: unicodestring);
var
  Thread: _JLThread;
begin
  if TryGetThread(ThreadHandle, Thread) then
    Thread.SetName(ThreadName);
end;

{ Critical Section }

procedure SysInitCriticalSection(var CS: TRTLCriticalSection);
begin
  CS.Handle := _JUCLReentrantLock.Create;
end;

procedure SysDoneCriticalSection(var CS: TRTLCriticalSection);
begin
  CS.Handle := nil;
end;

procedure SysEnterCriticalSection(var CS: TRTLCriticalSection);
begin
  _JUCLReentrantLock(CS.Handle).Lock;
end;

function SysTryEnterCriticalSection(var CS: TRTLCriticalSection): LongInt;
begin
  Result := Ord(_JUCLReentrantLock(CS.Handle).TryLock);
end;

procedure SysLeaveCriticalSection(var CS: TRTLCriticalSection);
begin
  _JUCLReentrantLock(CS.Handle).Unlock;
end;

{ Event }

function SysRTLEventCreate: PRTLEvent;
var
  OuterLock: _JUCLReentrantLock;
  Event: TRTLEvent;
begin
  OuterLock := _JUCLReentrantLock.Create;
  Event.OuterLock := OuterLock;
  Event.Condition := JLObject(
    OuterLock.NewCondition);
  Event.IsSet := False;
  Result := @Event;
end;

procedure SysRTLEventSetEvent(AEvent: PRTLEvent);
begin
  _JUCLReentrantLock(AEvent^.OuterLock).Lock;
  AEvent^.IsSet := True;
  _JUCLCondition(AEvent^.Condition).SignalAll;
  _JUCLReentrantLock(AEvent^.OuterLock).Unlock;
end;

procedure SysRTLEventDestroy(AEvent: PRTLEvent);
begin
  SysRTLEventSetEvent(AEvent);
  _JLThread.Sleep(1);
  AEvent^.Condition := nil;
  AEvent^.OuterLock := nil;
end;

procedure SysRTLEventResetEvent(AEvent: PRTLEvent);
begin
  AEvent^.IsSet := False;
end;

procedure SysRTLEventWaitFor(AEvent: PRTLEvent);
begin
  _JUCLReentrantLock(AEvent^.OuterLock).Lock;
  if not AEvent^.IsSet then
    _JUCLCondition(AEvent^.Condition).Await;
  _JUCLReentrantLock(AEvent^.OuterLock).Unlock;
end;

procedure SysRTLEventWaitForTimeout(AEvent: PRTLEvent; Timeout: LongInt);
begin
  _JUCLReentrantLock(AEvent^.OuterLock).Lock;
  if not AEvent^.IsSet then
    _JUCLCondition(AEvent^.Condition).AwaitNanos(JLong(Timeout) * 1000 * 1000);
  _JUCLReentrantLock(AEvent^.OuterLock).Unlock;
end;

{ Thread Manager }

var
  JvmThreadManager: TThreadManager;

procedure InitSystemThreads; public name '_FPC_InitSystemThreads';
begin
  JvmThreadManager.InitManager := nil;
  JvmThreadManager.DoneManager := nil;
  JvmThreadManager.BeginThread := @SysBeginThread;
  JvmThreadManager.EndThread := @SysEndThread;
  JvmThreadManager.SuspendThread := nil;
  JvmThreadManager.ResumeThread := nil;
  JvmThreadManager.ThreadSwitch := @SysThreadSwitch;
  JvmThreadManager.CloseThread := @SysCloseThread;
  JvmThreadManager.WaitForThreadTerminate := @SysWaitForThreadTerminate;
  JvmThreadManager.ThreadSetPriority := @SysThreadSetPriority;
  JvmThreadManager.ThreadGetPriority := @SysThreadGetPriority;
  JvmThreadManager.GetCurrentThreadId := @SysGetCurrentThreadId;
  JvmThreadManager.SetThreadDebugNameA := @SysSetThreadDebugNameA;
  JvmThreadManager.SetThreadDebugNameU := @SysSetThreadDebugNameU;
  JvmThreadManager.InitCriticalSection := @SysInitCriticalSection;
  JvmThreadManager.DoneCriticalSection := @SysDoneCriticalSection;
  JvmThreadManager.EnterCriticalSection := @SysEnterCriticalSection;
  JvmThreadManager.TryEnterCriticalSection := @SysTryEnterCriticalSection;
  JvmThreadManager.LeaveCriticalSection := @SysLeaveCriticalSection;
  JvmThreadManager.InitThreadVar := nil;
  JvmThreadManager.RelocateThreadVar := nil;
  JvmThreadManager.AllocateThreadVars := nil;
  JvmThreadManager.ReleaseThreadVars := nil;
  JvmThreadManager.RTLEventCreate := @SysRTLEventCreate;
  JvmThreadManager.RTLEventDestroy := @SysRTLEventDestroy;
  JvmThreadManager.RTLEventSetEvent := @SysRTLEventSetEvent;
  JvmThreadManager.RTLEventResetEvent := @SysRTLEventResetEvent;
  JvmThreadManager.RTLEventWaitFor := @SysRTLEventWaitFor;
  JvmThreadManager.RTLEventWaitForTimeout := @SysRTLEventWaitForTimeout;

  ThreadTable := _JUCConcurrentHashMap.Create;
  ThreadID := _JLThread.CurrentThread.GetId;
  SetThreadManager(JvmThreadManager);
end;
