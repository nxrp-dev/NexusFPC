program Project1;
{$Mode objfpc}

var
  f: Extended;
  i: Integer;
begin
  i:=0;
  for f:=1.7 to 10.7 do
    if trunc(f) mod 2 = 0 then
      continue
    else
      inc(i);
  if i<>5 then
    Halt(1);
  WriteLn('Ok');
end.
