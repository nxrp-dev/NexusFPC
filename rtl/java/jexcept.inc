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


Function RaiseList : PExceptObject;
begin
  RaiseList:=ExceptObjectStack;
end;


{ This routine is called only from fpc_raiseexception, which uses ExceptTryLevel
  flag to guard against repeated exceptions which can occur due to corrupted stack
  or heap. }
function PushExceptObject(Obj : TObject; AnAddr : CodePointer; AFrame : Pointer): PExceptObject;
var
  Newobj : PExceptObject;
  _ExceptObjectStack : ^PExceptObject;
  framebufsize,
  framecount  : PtrInt;
  frames      : array of CodePointer;
  prev_frame,
  curr_frame  : Pointer;
  curr_addr   : CodePointer;
  ExceptObjectRec : TExceptObject;
  index : longint;
begin
{$ifdef excdebug}
  writeln ('In PushExceptObject');
{$endif}
  NewObj:=@ExceptObjectRec;
  ExceptObjectStack:=NewObj;

  NewObj^.FObject:=Obj;
  NewObj^.Addr:=AnAddr;

  if assigned(AFrame) then
    begin
      NewObj^.refcount:=0;

      { Backtrace }
      curr_frame:=AFrame;
      curr_addr:=AnAddr;
      frames:=nil;
      framecount:=0;
      framebufsize:=0;
      framecount:=length(Arr1JLStackTraceElement(AFrame))-1;
      setlength(frames,framecount);
      for index:=0 to framecount-1 do
        frames[index]:=Arr1JLStackTraceElement(AFrame)[index+1];
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
procedure fpc_RaiseException (Obj : TObject; AnAddr : CodePointer; AFrame : Pointer);[Public, Alias : 'FPC_RAISEEXCEPTION'];
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
  DoUnhandledException;
end;
{$endif FPC_SYSTEM_HAS_RAISEEXCEPTION}


Procedure SysInitExceptions;
{
  Initialize exceptionsupport
}
begin
  ExceptObjectstack:=Nil;
  ExceptAddrStack:=Nil;
end;

