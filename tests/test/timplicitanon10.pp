{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}
{$ModeSwitch nestedprocvars}

procedure Test;
var
  i, j: Integer;
  p: function(x: Integer):Integer is nested;
begin
  j:=2;
  p:=function(x: Integer): Integer is x + j;
  i:=p(1);
  WriteLn(i);
  if (i<>3) then Halt(1);
end;

begin
  Test;
end.
