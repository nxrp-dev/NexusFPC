program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyRec = record
    A, B: Integer;
  end;

var
  counter:Integer;

function getR:TMyRec;
begin
  Inc(Counter);
  result.A := 42;
  result.B := 32;
end;

begin
  Counter:=0;
  case getR of
  (
    A:1..200;
    B:1
  ): Halt(1);
  (
    A:42;
    B:1..10,20..40
  ): ;
  otherwise
    Halt(1);
  end;
  if counter<>1 then
    halt(1);
  WriteLn('Ok');
end.
