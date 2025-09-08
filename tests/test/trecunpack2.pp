{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

type
  TMyRec = record
    second: String;
    third: Double;
  end;

var
  i: integer;
  r: TMyRec;
begin
  (i, ...r) := (42, 'Hello World', 3.14);
  if i<>42 then
    Halt(1);
  if r.second<>'Hello World' then
    Halt(2);
  if r.third<>3.14 then
    Halt(3);
  WriteLn('ok');
end.
