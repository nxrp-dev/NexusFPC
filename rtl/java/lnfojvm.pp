{
    This file is part of the Free Pascal run time library.

    Jvm LineInfo Retriever

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

unit lnfojvm;

{$namespace org.freepascal.rtl}

{$mode objfpc}

interface

function GetLineInfo(addr:codepointer;var func,source:shortstring;var line:longint) : boolean;
function JvmBackTraceStr(addr: CodePointer): shortstring;

implementation

type
  _JLStackTraceElement = class sealed external 'java.lang' name 'StackTraceElement' (JLObject)
  public
    function getFileName(): JLString; overload; virtual;
    function getLineNumber(): jint; overload; virtual;
    function getMethodName(): JLString; overload; virtual;
  end;


function GetLineInfo(addr:codepointer;var func,source:shortstring;var line:longint) : boolean;
var
  element : _JLStacktraceElement;
begin
  func:='';
  source:='';
  line:=0;
  if addr<>nil then
  begin
    element:=_JLStacktraceElement(addr);
    func:=shortstring(element.GetMethodName);
    source:=shortstring(element.GetFileName);
    line:=element.GetLineNumber;
    { the line number is a negative number in some traces }
    if line<0 then
      line:=0;
  end;
  result:=(length(func)<>0) or (length(source)<>0);
end;


{ JVM Notes: taking the address of a function more than once will crash at runtime so we cannot take the address of SysBackTraceStr directly }
function SysBackTraceStrProxy(addr: CodePointer): shortstring;
begin
  result:=SysBackTraceStr(addr);
end;


function JvmBackTraceStr(addr: CodePointer): shortstring;
  { for compatability this function is an almost exact copy of DwarfBackTraceStr }
var
  func,
  source : shortstring;
  hs     : shortstring;
  line   : longint;
  Store  : TBackTraceStrFunc;
  Success : boolean;
begin
  { reset to prevent infinite recursion if problems inside the code }
  Success:=false;
  Store := BackTraceStrFunc;
  BackTraceStrFunc := @SysBackTraceStrProxy;
  func := '';
  source := '';
  line := 0;
  Success:=GetLineInfo(addr, func, source, line);
  { create string }
  JvmBackTraceStr :='  $' + HexStr(addr);
  if Success then
  begin
    if func<>'' then
      JvmBackTraceStr := JvmBackTraceStr + '  ' + func;
    if source<>'' then
    begin
      if func<>'' then
        JvmBackTraceStr := JvmBackTraceStr + ', ';
      if line<>0 then
      begin
        str(line, hs);
        JvmBackTraceStr := JvmBackTraceStr + ' line ' + hs;
      end;
      JvmBackTraceStr := JvmBackTraceStr + ' of ' + source;
    end;
  end;
  BackTraceStrFunc := Store;
end;


initialization
  BackTraceStrFunc:=@JvmBacktraceStr;

end.
