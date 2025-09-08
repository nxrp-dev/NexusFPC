{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

var
  i: Integer;
  s: String;
  d: double;
begin
  (i, s, d) := (42, 'Hello World', 3.14);
  if i<>42 then
    Halt(1);
  if s<>'Hello World' then
    Halt(2);
  if d<>3.14 then
    Halt(3);
  WriteLn('ok');
end.
