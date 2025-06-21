{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}
{$ModeSwitch functionreferences}
var
  p: reference to function(x: Integer):Int64;

procedure Test;
var
  j: Integer;
begin
  j:=2;
  p:=function(x: Integer) begin result:=x + j end;
end;

var
  i: Integer;
begin
  Test;
  i:=p(1);
  WriteLn(i);
  if (i<>3) then Halt(1);
end.
