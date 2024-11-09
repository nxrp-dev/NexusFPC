{$Mode ObjFPC}
{$ModeSwitch AdvancedRecords}

type
  TTest = record
    i: Integer;
    class operator Initialize(var rec: TTest);
    class operator Finalize(var rec: TTest);
  end;

var
  InitCtr: Integer = 0;

class operator TTest.Initialize(var rec: TTest);
begin
  WriteLn('Initialize: ', IntPtr(@rec));
  Inc(InitCtr);
end;

class operator TTest.Finalize(var rec: TTest);
begin
  WriteLn('Finalize: ', IntPtr(@rec));
  Dec(InitCtr);
end;

function Test: TTest; begin end;

var
  precount:Integer;
begin
  precount:=InitCtr;
  WriteLn('Before With: ', InitCtr);
  with const T = Test do
  begin
    T.i:=42;
    WriteLn('During With: ', InitCtr);
    if T.i<>42 then
      Halt(1);
  end;
  WriteLn('After With: ', InitCtr);
  if InitCtr<>precount then
    Halt(1);
  WriteLn('Ok');
end.
