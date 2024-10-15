program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B, C: Integer;
  end;

var
  r: TMyRec;
begin
  r.A := 42;
  r.B := 32;
  r.C := 1;
  case with r of
  (
    A:1..10,100..200;
    B:1..50
  ): Halt(C);
  (
    A:42;
    B:1..10,20..40
  ): WriteLn('Ok');
  otherwise
    Halt(1);
  end;
end.
