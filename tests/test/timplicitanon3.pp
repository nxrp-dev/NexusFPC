{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}
{$ModeSwitch functionreferences}
var
  p: reference to function(s: String; x: Integer):Integer;

procedure Test;
var
  j: Integer;
begin
  j:=2;
  p:=function(s;x): Integer begin WriteLn(s); result:=x + j end;
end;

var
  i: Integer;
begin
  Test;
  i:=p('Foo', 1);
  WriteLn(i);
  if (i<>3) then Halt(1);
end.
