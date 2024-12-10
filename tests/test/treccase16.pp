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
    A: Integer;
    B: record
      C: Integer;
    end;
  end;
var
  r: TMyRec;
begin
  r.A:=42;
  r.B.C:=32;
  if not specialize testrec<TMyRec>(r) then
    Halt(1);
  WriteLn('Ok');
end.
