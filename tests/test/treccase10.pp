{ %FAIL }
program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

generic function testrec<T>(const rec: T): Boolean;
begin
  case rec of
  (
    A: 'hello';
    B: 'world'
  ): Result:=False;
  (
    A: 'Hello';
    B: 'World'
  ): Result:=True;
  else
    Result:=False;
  end;
end;

type
  TMyRec = record
    A, B: Integer;
  end;
var
  r: TMyRec;
begin
  r.A:=42;
  r.B:=32;
  if not specialize testrec<TMyRec>(r) then
    Halt(1);
  WriteLn('Ok');
end.
