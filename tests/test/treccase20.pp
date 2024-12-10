program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

generic function testrec<T>(const rec: T): Boolean;
begin
  case with rec of
  (
    A: 0..10;
    B: 0..10
  ): Result:=C=0;
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
    A, B, C: Integer;
  end;
var
  r: TMyRec;
begin
  r.A:=42;
  r.B:=32;
  r.C:=1;
  if not specialize testrec<TMyRec>(r) then
    Halt(1);
  WriteLn('Ok');
end.
