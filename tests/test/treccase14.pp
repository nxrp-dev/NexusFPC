program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

var
  r: record
    A: Integer;
  case B: Boolean of
    True:(C: Integer);
    False:(D: Double);
  end;
begin
  r.A := 42;
  r.B:=False;
  case r of
  (
    A:0..100;
    B:True
  ): Halt(1);
  (
    A:40..50;
    B:False
  ): WriteLn(r.D);
  end;
  WriteLn('Ok');
end.
