{ %FAIL }
program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

generic function testrec<T>(const rec: T): Boolean;
begin
  case rec of
  (
    A: 0..10;
    B: (C: 0..10)
  ): Result:=False;
  (
    A: 15..100;
    B: (C: 0..40)
  ): Result:=True;
  else
    Result:=False;
  end;
end;

type
  TMyRec = record
    A: String;
    B: record
      C: String;
    end;
  end;
var
  r: TMyRec;
begin
  r.A:='Hello';
  r.B.C:='World';
  if not specialize testrec<TMyRec>(r) then
    Halt(1);
  WriteLn('Ok');
end.
