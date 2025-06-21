{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}
{$ModeSwitch nestedprocvars}

procedure Test;
var
  i, j: Integer;
  p: function(x: Integer):Int64 is nested;
begin
  j:=2;
  p:=function(x:Integer) begin result:=x + j end;
  i:=p(1);
  WriteLn(i);
  if (i<>3) then Halt(1);
end;

begin
  Test;
end.
