program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B: Integer;
  end;

var
  r: TMyRec;
begin
  r.A := 42;
  r.B := 32;
  case r of
  (
    A:1..10,100..200;
    B:1..50
  ): Halt(1);
  (
    A:42;
    B:1..10,20..40
  ): WriteLn('Ok');
  otherwise
    Halt(1);
  end;
end.
