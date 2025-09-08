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
  d: double;
begin
  r.first := 42;
  r.third := 3.14;
  (i, nil, d) := ...r;
  if i<>42 then
    Halt(1);
  if d<>3.14 then
    Halt(2);
  WriteLn('ok');
end.
