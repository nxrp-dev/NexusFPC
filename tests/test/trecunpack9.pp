{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

type
  TMyRec = record
    first: Integer;
    second: String;
    third: Double;
  end;

var
  r: TMyRec;
begin
  ...r := (42, 'Hello World', 3.14);
  if r.first<>42 then
    Halt(1);
  if r.second<>'Hello World' then
    Halt(2);
  if r.third<>3.14 then
    Halt(3);
  WriteLn('ok');
end.
