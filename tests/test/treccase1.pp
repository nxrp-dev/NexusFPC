program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

var
  r: record
    A: Integer;
    B: Extended;
  end;
begin
  r.A := 42;
  r.B := 2.5;
  case r of
  (
    A:0..10;
    B:2.5
  ): Halt(1);
  (
    A:40..50;
    B:2.5
  ): WriteLn('ok');
  end;
end.
