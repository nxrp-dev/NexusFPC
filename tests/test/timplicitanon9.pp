{$Mode ObjFPC}
{$ModeSwitch AnonymousFunctions}

procedure SetInt(out i: Integer);
begin
  i:=42;
end;

procedure Test;
var
  i: Integer;
begin
  i:=function begin SetInt(Result) end();
  WriteLn(i);
  if (i<>42) then Halt(1);
end;

begin
  Test;
end.
