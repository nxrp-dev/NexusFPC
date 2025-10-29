{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}

procedure Test;
var
  i,j: Integer;
begin
  j:=2;
  i:=function(s;x): Integer begin writeln(s); result:=x + j end('Foo',3);
  WriteLn(i);
  if (i<>5) then Halt(1);
end;

begin
  Test;
end.
