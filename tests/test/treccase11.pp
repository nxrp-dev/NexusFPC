program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

var
  r: record
    A: Integer;
    B: record
      C: Integer;
      D: Boolean;
    end;
  end;
begin
  r.A := 42;
  r.B.C:=32;
  r.B.D:=False;
  case r of
  (
    A:0..10;
    B:(
      C:0..10;
      D:True
    )
  ): Halt(1);
  (
    A:40..50;
    B:(
      C:30..40;
      D:False
    )
  ): WriteLn('ok');
  end;
end.
