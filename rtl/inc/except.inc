{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by Michael Van Canneyt
    member of the Free Pascal development team

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{****************************************************************************
                                Exception support
****************************************************************************}


{$ifdef FPC_HAS_FEATURE_THREADING}
ThreadVar
{$else FPC_HAS_FEATURE_THREADING}
Var
{$endif FPC_HAS_FEATURE_THREADING}
  ExceptAddrStack   : PExceptAddr;
  ExceptObjectStack : PExceptObject;
  ExceptTryLevel    : ObjpasInt;

{$ifdef FPC_USE_PSABIEH}
{$i psabieh.inc}
{$endif}

Function RaiseList : PExceptObject;
begin
  RaiseList:=ExceptObjectStack;
end;


{$ifndef CPUJVM}
function AcquireExceptionObject: Pointer;
var
  _ExceptObjectStack : PExceptObject;
begin
  _ExceptObjectStack:=ExceptObjectStack;
  If _ExceptObjectStack<>nil then
    begin
      Inc(_ExceptObjectStack^.refcount);
      AcquireExceptionObject := _ExceptObjectStack^.FObject;
    end
  else
    RunError(231);
end;
{$endif CPUJVM}


{$ifndef CPUJVM}
procedure ReleaseExceptionObject;
var
  _ExceptObjectStack : PExceptObject;
begin
  _ExceptObjectStack:=ExceptObjectStack;
  If _ExceptObjectStack <> nil then
    begin
      if _ExceptObjectStack^.refcount > 0 then
        Dec(_ExceptObjectStack^.refcount);
    end
  else
    RunError(231);
end;
{$endif CPUJVM}


{$ifndef CPUJVM}
Function fpc_PushExceptAddr (Ft: {$ifdef CPU16}SmallInt{$else}Longint{$endif};_buf,_newaddr : pointer): PJmp_buf ;
  [Public, Alias : 'FPC_PUSHEXCEPTADDR'];compilerproc;
var
  _ExceptAddrstack : ^PExceptAddr;
begin
{$ifdef excdebug}
  writeln ('In PushExceptAddr');
{$endif}
  _ExceptAddrstack:=@ExceptAddrstack;
  PExceptAddr(_newaddr)^.Next:=_ExceptAddrstack^;
  _ExceptAddrStack^:=PExceptAddr(_newaddr);
  PExceptAddr(_newaddr)^.Buf:=PJmp_Buf(_buf);
  PExceptAddr(_newaddr)^.FrameType:=ft;
  result:=PJmp_Buf(_buf);
end;
{$endif CPUJVM}


{ This routine is called only from fpc_raiseexception, which uses ExceptTryLevel
  flag to guard against repeated exceptions which can occur due to corrupted stack
  or heap. }
function PushExceptObject(Obj : TObject; AnAddr : CodePointer; AFrame : Pointer): PExceptObject;
var
  Newobj : PExceptObject;
  _ExceptObjectStack : ^PExceptObject;
  framebufsize,
  framecount  : PtrInt;
{$ifndef CPUJVM}
  frames      : PCodePointer;
{$else CPUJVM}
  frames      : array of CodePointer;
{$endif CPUJVM}
  prev_frame,
  curr_frame  : Pointer;
  curr_addr   : CodePointer;
{$ifdef CPUJVM}
  ExceptObjectRec : TExceptObject;
  index : longint;
{$endif CPUJVM}
begin
{$ifdef excdebug}
  writeln ('In PushExceptObject');
{$endif}
{$ifndef CPUJVM}
  _ExceptObjectStack:=@ExceptObjectStack;
  NewObj:=AllocMem(sizeof(TExceptObject));
  NewObj^.Next:=_ExceptObjectStack^;
  _ExceptObjectStack^:=NewObj;
{$else}
  NewObj:=@ExceptObjectRec;
  ExceptObjectStack:=NewObj;
{$endif}

  NewObj^.FObject:=Obj;
  NewObj^.Addr:=AnAddr;

{$ifndef CPUJVM}
  if assigned(get_frame) then
{$else CPUJVM}
  if assigned(AFrame) then
{$endif CPUJVM}
    begin
      NewObj^.refcount:=0;

      { Backtrace }
      curr_frame:=AFrame;
      curr_addr:=AnAddr;
      frames:=nil;
      framecount:=0;
      framebufsize:=0;
{$ifndef CPUJVM}
      { The frame pointer of this procedure is used as initial stack bottom value. }
      prev_frame:=get_frame;
      while (framecount<RaiseMaxFrameCount) and (curr_frame > prev_frame) and
            (curr_frame<StackTop) do
        Begin
          prev_frame:=curr_frame;
          get_caller_stackinfo(curr_frame,curr_addr);
          if (curr_addr=nil) or
             (curr_frame=nil) then
            break;
          if (framecount>=framebufsize) then
            begin
              inc(framebufsize,16);
              reallocmem(frames,framebufsize*sizeof(codepointer));
            end;
          frames[framecount]:=curr_addr;
          inc(framecount);
        End;
{$else CPUJVM}
      framecount:=length(Arr1JLStackTraceElement(AFrame))-1;
      setlength(frames,framecount);
      for index:=0 to framecount-1 do
        frames[index]:=Arr1JLStackTraceElement(AFrame)[index+1];
{$endif CPUJVM}
      NewObj^.framecount:=framecount;
      NewObj^.frames:=pcodepointer(frames);
    end;
  Result:=NewObj;
end;

Procedure DoUnHandledException;
var
  _ExceptObjectStack : PExceptObject;
begin
  _ExceptObjectStack:=ExceptObjectStack;
  If (ExceptProc<>Nil) and (_ExceptObjectStack<>Nil) then
    with _ExceptObjectStack^ do
      begin
        TExceptProc(ExceptProc)(FObject,Addr,FrameCount,Frames);
        halt(217)
      end;
  if erroraddr = nil then
    RunError(217)
  else
    Halt(errorcode);
end;

{$ifndef FPC_SYSTEM_HAS_RAISEEXCEPTION}
{ JVM Notes: compiler crash if we add the compilerproc modifier (fatal: internal error 200411171) }
procedure fpc_RaiseException (Obj : TObject; AnAddr : CodePointer; AFrame : Pointer);[Public, Alias : 'FPC_RAISEEXCEPTION']; {$ifndef CPUJVM}compilerproc;{$endif}
var
  _ExceptObjectStack : PExceptObject;
  _ExceptAddrstack : PExceptAddr;
begin
{$ifdef excdebug}
  writeln ('In RaiseException');
{$endif}
  if ExceptTryLevel<>0 then
    Halt(217);
  ExceptTryLevel:=1;
  PushExceptObject(Obj,AnAddr,AFrame);
  { if PushExceptObject causes another exception, the following won't be executed,
    causing halt upon entering this routine recursively. }
  ExceptTryLevel:=0;
{$ifndef CPUJVM}
  _ExceptAddrstack:=ExceptAddrStack;
  If _ExceptAddrStack=Nil then
    DoUnhandledException;
  _ExceptObjectStack:=ExceptObjectStack;
  if (RaiseProc <> nil) and (_ExceptObjectStack <> nil) then
    with _ExceptObjectStack^ do
      RaiseProc(FObject,Addr,FrameCount,Frames);
  longjmp(_ExceptAddrStack^.Buf^,FPC_Exception);
{$else CPUJVM}
  DoUnhandledException;
{$endif CPUJVM}
end;
{$endif FPC_SYSTEM_HAS_RAISEEXCEPTION}


{$ifndef CPUJVM}
Procedure fpc_PopAddrStack;[Public, Alias : 'FPC_POPADDRSTACK']; compilerproc;
var
  hp : ^PExceptAddr;
begin
{$ifdef excdebug}
  writeln ('In Popaddrstack');
{$endif}
  hp:=@ExceptAddrStack;
  If hp^=nil then
    begin
{$ifdef excdebug}
      writeln ('At end of ExceptionAddresStack');
{$endif}
      halt (255);
    end
  else
    begin
      hp^:=hp^^.Next;
    end;
end;
{$endif CPUJVM}


{$ifndef CPUJVM}
function fpc_PopObjectStack : TObject;[Public, Alias : 'FPC_POPOBJECTSTACK']; compilerproc;
var
  hp : PExceptObject;
begin
{$ifdef excdebug}
  writeln ('In PopObjectstack');
{$endif}
  hp:=ExceptObjectStack;
  if hp=nil then
    begin
{$ifdef excdebug}
      writeln ('At end of ExceptionObjectStack');
{$endif}
      halt (1);
    end
  else
    begin
       { we need to return the exception object to dispose it }
       if hp^.refcount = 0 then
         fpc_PopObjectStack:=hp^.FObject
       else
         fpc_PopObjectStack:=nil;
       ExceptObjectStack:=hp^.next;
       if assigned(hp^.frames) then
         freemem(hp^.frames);
       dispose(hp);
       erroraddr:=nil;
    end;
end;
{$endif CPUJVM}


{$ifndef CPUJVM}
{ this is for popping exception objects when a second exception is risen }
{ in an except/on                                                        }
function fpc_PopSecondObjectStack : TObject;[Public, Alias : 'FPC_POPSECONDOBJECTSTACK']; compilerproc;
var
  hp,_ExceptObjectStack : PExceptObject;
begin
{$ifdef excdebug}
  writeln ('In PopObjectstack');
{$endif}
  _ExceptObjectStack:=ExceptObjectStack;
  If not(assigned(_ExceptObjectStack)) or
     not(assigned(_ExceptObjectStack^.next)) then
    begin
{$ifdef excdebug}
      writeln ('At end of ExceptionObjectStack');
{$endif}
      halt (1);
    end
  else
    begin
      if _ExceptObjectStack^.next^.refcount=0 then
        { we need to return the exception object to dispose it if refcount=0 }
        fpc_PopSecondObjectStack:=_ExceptObjectStack^.next^.FObject
      else
        fpc_PopSecondObjectStack:=nil;
      hp:=_ExceptObjectStack^.next;
      _ExceptObjectStack^.next:=hp^.next;
      if assigned(hp^.frames) then
        freemem(hp^.frames);
      dispose(hp);
    end;
end;
{$endif CPUJVM}

{$ifndef CPUJVM}
{$ifndef FPC_SYSTEM_HAS_RERAISE}
Procedure fpc_ReRaise;[Public, Alias : 'FPC_RERAISE']; compilerproc;
var
  _ExceptAddrStack : PExceptAddr;
begin
{$ifdef excdebug}
  writeln ('In reraise');
{$endif}
  _ExceptAddrStack:=ExceptAddrStack;
  If _ExceptAddrStack=Nil then
    DoUnHandledException;
  ExceptObjectStack^.refcount := 0;
  longjmp(_ExceptAddrStack^.Buf^,FPC_Exception);
end;
{$endif FPC_SYSTEM_HAS_RERAISE}
{$endif CPUJVM}

{$ifndef CPUJVM}
function Internal_PopSecondObjectStack : TObject; external name 'FPC_POPSECONDOBJECTSTACK';
function Internal_PopObjectStack: TObject; external name 'FPC_POPOBJECTSTACK';
procedure Internal_Reraise; external name 'FPC_RERAISE';
{$endif CPUJVM}

{$ifndef CPUJVM}
Function fpc_Catches(Objtype : TClass) : TObject;[Public, Alias : 'FPC_CATCHES']; compilerproc;
var
  _ExceptObjectStack : PExceptObject;
begin
  _ExceptObjectStack:=ExceptObjectStack;
  If _ExceptObjectStack=Nil then
   begin
{$ifdef excdebug}
     Writeln ('Internal error.');
{$endif}
     halt (255);
   end;
  if Not ((Objtype = TClass(CatchAllExceptions)) or
         (_ExceptObjectStack^.FObject is ObjType)) then
    fpc_Catches:=Nil
  else
    begin
      // catch !
      fpc_Catches:=_ExceptObjectStack^.FObject;
      { this can't be done, because there could be a reraise (PFV)
       PopObjectStack;

       Also the PopAddrStack shouldn't be done, we do it now
       immediatly in the exception handler (FK)
      PopAddrStack; }
    end;
end;
{$endif CPUJVM}

Procedure SysInitExceptions;
{
  Initialize exceptionsupport
}
begin
  ExceptObjectstack:=Nil;
  ExceptAddrStack:=Nil;
end;


{$ifndef CPUJVM}
{$ifndef FPC_SYSTEM_HAS_DONEEXCEPTION}
procedure fpc_doneexception;[public,alias:'FPC_DONEEXCEPTION'] compilerproc;
begin
  Internal_PopObjectStack.Free;
end;
{$endif FPC_SYSTEM_HAS_DONEEXCEPTION}
{$endif CPUJVM}

{$ifndef CPUJVM}
{$ifndef FPC_SYSTEM_HAS_RAISENESTED}
procedure fpc_raise_nested;[public,alias:'FPC_RAISE_NESTED']compilerproc;
begin
  Internal_PopSecondObjectStack.Free;
  Internal_Reraise;
end;
{$endif FPC_SYSTEM_HAS_RAISENESTED}
{$endif CPUJVM}

{$ifndef CPUJVM}
{$ifndef FPC_SYSTEM_HAS_SAFECALLHANDLER}
function fpc_safecallhandler(obj: TObject): HResult; [public,alias:'FPC_SAFECALLHANDLER']; compilerproc;
var
  raiselist: PExceptObject;
  adr: CodePointer;
  exc: TObject;
begin
  raiselist:=ExceptObjectStack;
  if Assigned(raiseList) then
    adr:=raiseList^.Addr
  else
    adr:=nil;
  exc:=Internal_PopObjectStack;
  if Assigned(obj) and Assigned(exc) then
    result:=obj.SafeCallException(exc,adr)
  else
    result:=E_UNEXPECTED;
  exc.Free;
end;
{$endif FPC_SYSTEM_HAS_SAFECALLHANDLER}
{$endif CPUJVM}

