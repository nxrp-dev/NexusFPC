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
{$i jsysutilh.inc}

procedure Sleep(Milliseconds: Cardinal);

implementation

uses sysconst;

{$DEFINE HAS_GETTICKCOUNT64}
{$DEFINE HAS_SLEEP}


{****************************************************************************
                             Import
****************************************************************************}

type
  _JLThread = class external 'java.lang' name 'Thread' (JLObject)
  public
    class procedure sleep(para1: jlong); static; overload;
  end;


{****************************************************************************
                              Time Functions
****************************************************************************}

function GetTickCount64: QWord;
  begin
    result:=JLSystem.NanoTime;
  end;


{*************************************************************************
                                   Sleep
*************************************************************************}

procedure Sleep(Milliseconds: Cardinal);
  begin
    _JLThread.Sleep(Milliseconds);
  end;


{****************************************************************************
                              Cross-Platform Functions
****************************************************************************}

{$i jsysutils.inc}


{****************************************************************************
                              Initialization code
****************************************************************************}

Initialization
  InitExceptions;       { Initialize exceptions. OS independent }

end.
