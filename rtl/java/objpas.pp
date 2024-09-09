{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by the Free Pascal development team

    This unit makes Free Pascal as much as possible Delphi compatible

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
{$Mode ObjFpc}
{$I-,S-}
unit objpas;

  {$namespace org.freepascal.rtl}

  interface

    { first, in object pascal, the integer type must be redefined }
    const
       MaxInt  = MaxLongint;
    type
       Integer  = longint;

       { Ansistring are the default }
       PString = PAnsiString;

    {$ifdef FPC_HAS_FEATURE_CLASSES}
    var
       ExceptionClass: TClass; { Exception base class (must actually be Exception, defined in sysutils ) }
    {$endif FPC_HAS_FEATURE_CLASSES}

{****************************************************************************
                             Resource strings.
****************************************************************************}

    { Delphi compatibility }
    type
      { JVM Notes: constructors with the same parameters cause a runtime crash
        (even if the names are different) so we cannot use a string }
      PResStringRec = ^TResStringRec;
      TResStringRec = record
        Value: shortstring;
      end;

  implementation

end.
