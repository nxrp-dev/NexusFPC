{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

unit SysUtils;

interface

{$MODE objfpc}
{$MODESWITCH OUT}
{ force ansistrings }
{$H+}
{$modeswitch typehelpers}
{$modeswitch advancedrecords}
{$namespace org.freepascal.rtl}

{ Include platform independent interface part }
{$i sysutilh.inc}

{****************************************************************************
                             Resource strings.
****************************************************************************}

operator:=(AString : PShortString): PResStringRec;

implementation

uses sysconst;

{$DEFINE HAS_GETTICKCOUNT64}

{****************************************************************************
                             Resource strings.
****************************************************************************}

operator:=(AString : PShortString): PResStringRec;
  var
    ResStringRec: TResStringRec;
  begin
    ResStringRec.Value:=AString^;
    Result:=@ResStringRec;
  end;

operator:=(AResString : TResStringRec): string;
  begin
    result:=string(AResString.Value);
  end;


{****************************************************************************
                              Time Functions
****************************************************************************}

function GetTickCount64: QWord;
  begin
    result:=JLSystem.NanoTime;
  end;


{****************************************************************************
                              Cross-Platform Functions
****************************************************************************}

{$i sysutils.inc}


{****************************************************************************
                              Initialization code
****************************************************************************}

Initialization
  InitExceptions;       { Initialize exceptions. OS independent }

end.
