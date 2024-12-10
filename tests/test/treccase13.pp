program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B: String;
  end;

var
  r: TMyRec;
begin
  r.A := 'Hello';
  r.B := 'World';
  case r of
  (
    A:'hello';
    B:'world'
  ): Halt(1);
  (
    A: 'Hello';
    B: 'World'
  ): WriteLn('ok');
  end;
end.
