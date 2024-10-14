{ %FAIL }
program Test;

{$Mode ObjFpc}{$H+}
{$ModeSwitch ComplexCase}

type
  TMyClass = class 
  public
    A, FB: Integer;
    property B: Integer write FB;
  end;

var
  c: TMyClass;
begin
  c:=TMyClass.Create;
  c.A := 42;
  c.FB := 32;
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
