{$Mode ObjFPC}
{$ModeSwitch AdvancedRecords}

type
  TTest = record
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
  with Test do
    WriteLn('During With: ', InitCtr);
  WriteLn('After With: ', InitCtr);
  if InitCtr<>precount then
    Halt(1);
  WriteLn('Ok');
end.
