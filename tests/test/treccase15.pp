{ %FAIL }
program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B: Integer;
  end;

var
  r: TMyRec;
  i: Integer;
begin
  r.A := 42;
  r.B := 32;
  i:=42;
  case r of
  (
    A:i;
    B:1..50
  ):;
  end;
end.
