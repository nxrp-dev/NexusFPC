program Project1;
{$Mode objfpc}

var
  f: Extended;
  i: Integer;
begin
  i:=0;
  for f:=1.7 to 10.7 do
    inc(i);
  if i<>10 then
    Halt(1);
  WriteLn('Ok');
end.
