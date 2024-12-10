program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyClass = class 
  public
    A: Integer;
    function getB: Integer;
    property B: Integer read getB;
  end;

function TMyClass.GetB: Integer;
begin
  Result:=32;
end;

var
  c: TMyClass;
begin
  c:=TMyClass.Create;
  c.A := 42;
  case c of
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
