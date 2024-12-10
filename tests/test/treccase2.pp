program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B: array of integer;
  end;

var
  r: TMyRec;
begin
  r.A := [];
  r.B := [1,2,3];
  case r of
  (
    A:nil;
    B:nil
  ): Halt(1);
  (
    A: nil
  ): WriteLn('ok');
  end;
end.
