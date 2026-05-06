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
  i: Integer;
  s: String;
  d: double;
begin
  r.first := 42;
  r.second := 'Hello World';
  r.third := 3.14;
  (i, s, d) := ...r;
  if i<>42 then
    Halt(1);
  if s<>'Hello World' then
    Halt(2);
  if d<>3.14 then
    Halt(3);
  WriteLn('ok');
end.
