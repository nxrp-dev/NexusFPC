{%FAIL}
{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}

procedure Test;
var
  i,j: Integer;
begin
  j:=2;
  i:=function(x:Integer) begin if (x>0) then result:=42 else result:='Foo' end(3);
  Writeln(i);
  halt(1);
end;

begin
  Test;
end.
