{%MainUnit sysutils.pp}
{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by Florian Klaempfl
    member of the Free Pascal development team

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{$IFNDEF HAS_GETTICKCOUNT}
function GetTickCount: LongWord;
begin
  Result := LongWord(GetTickCount64);
end;
{$ENDIF}

{$IFNDEF HAS_GETTICKCOUNT64}
function GetTickCount64: QWord;
begin
{$IFDEF FPU_NONE}
  {$IFDEF HAS_SYSTIMERTICK}
  Result := SysTimerTick;
  {$ELSE}
  Result := 0;
  {$ENDIF}
{$ELSE}
  Result := Trunc(Now * 24 * 60 * 60 * 1000);
{$ENDIF}
end;
{$ENDIF}


function Format(const Fmt : string; const Args : array of const): string; unimplemented;
{ placeholder function as format is not implemented }
var
  arr : Arr1JLObject;
  index : longint;
begin
  arr:=nil;
  setlength(arr,length(Args));
  for index:=0 to high(Args) do
    arr[index]:=Args[index].value;
  try
    result:=JLString.format(Fmt,arr);
  except
    result:=Fmt;
  end;
end;


constructor Exception.Create(const msg : string);

  begin
     inherited create(unicodestring(msg));
     fmessage:=msg;
  end;


constructor Exception.CreateFmt(const msg : string; const args : array of const);

  begin
     inherited create(unicodestring(msg));
     fmessage:=Format(msg,args);
  end;




constructor Exception.CreateHelp(const Msg: string; AHelpContext: Longint);

  begin
     inherited create(unicodestring(msg));
     fmessage:=Msg;
     fhelpcontext:=AHelpContext;
  end;


constructor Exception.CreateFmtHelp(const Msg: string; const Args: array of const;
  AHelpContext: Longint);

begin
   inherited create(unicodestring(msg));
   fmessage:=Format(Msg,args);
   fhelpcontext:=AHelpContext;
end;



Function Exception.ToString : RTLString;
begin
  Result:=ClassName+': '+Message;
end;


function Exception.GetBaseException : Exception;
  var
    _ExceptObjectStack : PExceptObject;
  begin
    result:=nil;
    _ExceptObjectStack:=RaiseList;
    While Assigned(_ExceptObjectStack) do
      begin
        result:=Exception(_ExceptObjectStack^.FObject);
        _ExceptObjectStack:=_ExceptObjectStack^.Next;
      end;
  end;

{$push}
{$S-}
Procedure CatchUnhandledException (Obj : TObject; Addr: CodePointer; FrameCount: Longint; Frames: Pointer);[public,alias:'FPC_BREAK_UNHANDLED_EXCEPTION'];
Var
  i : longint;
  hstdout : text;

begin
  if WriteErrorsToStdErr then
    hstdout:=stderr
  else
    hstdout:=stdout;
  Writeln(hstdout,'An unhandled exception occurred at $',HexStr(Addr),':');
  if Obj is exception then
    Writeln(hstdout,Obj.ClassName,': ',Exception(Obj).Message)
  else if Obj is TObject then
    Writeln(hstdout,'Exception object ',Obj.ClassName,' is not of class Exception.')
  else
    Writeln(hstdout,'Exception object is not a valid class.');
{$IFDEF HAS_OSERROR}
 {$IFDEF DEBUG_EXCEPTIONS_LASTOSERROR}
  WriteLn (HStdOut, 'Last OS error detected in the RTL: ', GetLastOSError);
 {$ENDIF DEBUG_EXCEPTIONS_LASTOSERROR}
{$ENDIF HAS_OSERROR}
  Writeln(hstdout,BackTraceStrFunc(Addr));
  if (FrameCount>0) then
    begin
      for i:=0 to FrameCount-1 do
        Writeln(hstdout,BackTraceStrFunc(PCodePointer(Frames)[i]));
    end;
  Writeln(hstdout,'');
end;


Var OutOfMemory : EOutOfMemory;
    InValidPointer : EInvalidPointer;


Procedure RunErrorToExcept (ErrNo : Longint; Address : CodePointer; Frame : Pointer);
var
  E: Exception;
  HS: unicodestring;
begin
  E:=nil;
  Case Errno of
   1,203 : E:=OutOfMemory;
   204 : E:=InvalidPointer;
  else
    case ErrNo of
      200 : E:=EDivByZero.Create(SDivByZero);
      201 : E:=ERangeError.Create(SRangeError);
      202 : E:=EStackOverflow.Create(SStackOverflow);
      205 : E:=EOverflow.Create(SOverflow);
      206 : E:=EUnderflow.Create(SUnderflow);
      207 : E:=EInvalidOp.Create(SInvalidOp);
      208 : E:=EZeroDivide.Create(SZeroDivide);
      210 : E:=EObjectCheck.Create(SObjectCheckError);
      211 : E:=EAbstractError.Create(SAbstractError);
      212 : E:=EExternalException.Create(SExternalException);
      214 : E:=EBusError.Create(SBusError);
      215 : E:=EIntOverflow.Create(SIntOverflow);
      216 : E:=EAccessViolation.Create(SAccessViolation);
      217 : E:=EControlC.Create(SControlC);
      218 : E:=EPrivilege.Create(SPrivilege);
      219 : E:=EInvalidCast.Create(SInvalidCast);
      220 : E:=EVariantError.Create(SInvalidVarCast);
      221 : E:=EVariantError.Create(SInvalidVarOp);
      222 : E:=EVariantError.Create(SDispatchError);
      223 : E:=EVariantError.Create(SVarArrayCreate);
      224 : E:=EVariantError.Create(SVarNotArray);
      225 : E:=EVariantError.Create(SVarArrayBounds);
      227 : E:=EAssertionFailed.Create(SAssertionFailed);
      228 : E:=EIntfCastError.Create(SIntfCastError);
      229 : E:=ESafecallException.Create(SSafecallException);
      231 : E:=EConvertError.Create(SiconvError);
      232 : E:=ENoThreadSupport.Create(SNoThreadSupport);
      233 : E:=ESigQuit.Create(SSigQuit);
      234 : E:=ENoWideStringSupport.Create(SMissingWStringManager);
      235 : E:=ENoDynLibsSupport.Create(SNoDynLibsSupport);
      236 : E:=EThreadError.Create(SThreadError);
    else
      E:=nil;
    end;
    if E=nil then
    begin
     HS:='';
     Case Errno of
       2 : HS:=SFileNotFound;
       3 : HS:=SInvalidFileName;
       4 : HS:=STooManyOpenFiles;
       5 : HS:=SAccessDenied;
       6 : HS:=SInvalidFileHandle;
       15 : HS:=SInvalidDrive;
       100 : HS:=SEndOfFile;
       101 : HS:=SDiskFull;
       102 : HS:=SFileNotAssigned;
       103 : HS:=SFileNotOpen;
       104 : HS:=SFileNotOpenForInput;
       105 : HS:=SFileNotOpenForOutput;
       106 : HS:=SInvalidInput;
     end;
     if HS<>'' then
       E:=EInOutError.Create(HS)
     else
       E:=EInOutError.CreateFmt(SUnknownRunTimeError,[errno]);
     // this routine can be called from FPC_IOCHECK,
     // which clears inoutres and then passes its
     // original value to HandleErrorFrame() (which calls
     // us). So use errno rather than IOResult, and clear
     // InOutRes explicitly in case we can also be called
     // from a place that does not clear InOutRes explicitly
     EInoutError(E).ErrorCode:=errno;
     inoutres:=0;
     end;
  end;
  fpc_RaiseException(E, Address, Frame);
end;

Procedure AssertErrorHandler (Const Msg,FN : ShortString;LineNo:longint; TheAddr : pointer);
Var
  S : String;
begin
  If Msg='' then
    S:=SAssertionFailed
  else
    S:=Msg;
  Raise EAssertionFailed.Createfmt(SAssertError,[S,Fn,LineNo]) // at get_caller_addr(theAddr), get_caller_frame(theAddr);
end;

{$pop} //{$S-} for Error handling functions

Procedure InitExceptions;
{
  Must install uncaught exception handler (ExceptProc)
  and install exceptions for system exceptions or signals.
  (e.g: SIGSEGV -> ESegFault or so.)
}
begin
  ExceptionClass := Exception;
  ExceptProc:=@CatchUnhandledException;
  // Create objects that may have problems when there is no memory.
  OutOfMemory:=EOutOfMemory.Create(SOutOfMemory);
  OutOfMemory.AllowFree:=false;
  InvalidPointer:=EInvalidPointer.Create(SInvalidPointer);
  InvalidPointer.AllowFree:=false;
  AssertErrorProc:=@AssertErrorHandler;
  ErrorProc:=@RunErrorToExcept;
  OnShowException:=Nil;
end;

