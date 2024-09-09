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
  _JIFile = class external 'java.io' name 'File' (JLObject)
  public
    final class var
      fseparatorChar: jchar; external name 'separatorChar';
      fpathSeparatorChar: jchar; external name 'pathSeparatorChar';
  end;

  _JLRConstructor = class sealed external 'java.lang.reflect' name 'Constructor' (JLRAccessibleObject)
  public
    function newInstance(para1: Arr1JLObject): JLObject; overload; virtual;
  end;

  _JLClass = class sealed external 'java.lang' name 'Class' (JLObject)
  public
    function getConstructor(para1: Arr1JLClass): _JLRConstructor; overload; virtual;
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

begin
  InitUnicodeStringManager;
  SetupOSConstants;
  {$ifdef FPC_HAS_FEATURE_COMMANDARGS}
  SetupArguments;
  {$endif FPC_HAS_FEATURE_COMMANDARGS}
end.

