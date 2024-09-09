{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2011 by Jonas Maebe,
    members of the Free Pascal development team.

    This file implements support infrastructure for records under the JVM

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

  constructor FpcBaseRecordType.create;
    begin
    end;


  function FpcBaseRecordType.clone: JLObject;
    begin
      result:=inherited;
    end;


  function FpcBaseRecordType.newEmpty: FpcBaseRecordType;
    var
      ctor: _JLRConstructor;
      accessible: boolean;
    begin
      ctor:=_JLClass(JLObject(GetClass)).GetConstructor(nil);
      accessible:=ctor.IsAccessible;
      ctor.SetAccessible(True);
      result:=FpcBaseRecordType(ctor.NewInstance(nil));
      if not accessible then
        ctor.SetAccessible(False);
    end;

