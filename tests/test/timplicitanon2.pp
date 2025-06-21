{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}
{$ModeSwitch nestedprocvars}

procedure Test;
var
  i, j: Integer;
  p: function(s: String; x: Integer):Integer is nested;
begin
  j:=2;
  p:=function(s;x): Integer begin WriteLn(s); result:=x + j end;
  i:=p('Foo', 1);
  WriteLn(i);
  if (i<>3) then Halt(1);
end;

begin
  Test;
end.
