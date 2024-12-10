{ %FAIL }
program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

generic function testrec<T>(const rec: T): Boolean;
begin
  case rec of
  (
    A: 0..10;
    B: 0..10
  ): Result:=False;
  (
    A: 15..100;
    B: 0..40
  ): Result:=True;
  else
    Result:=False;
  end;
end;

type
  TMyRec = record
    A, B: String;
  end;
var
  r: TMyRec;
begin
  r.A:='Hello';
  r.B:='World';
  if not specialize testrec<TMyRec>(r) then
    Halt(1);
  WriteLn('Ok');
end.
