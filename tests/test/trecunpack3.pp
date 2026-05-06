{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

type
  TMyRec = record
    second: String;
    third: Double;
  end;
  
  TMyRec2 = record
    first: Integer;
    second: String;
    third: Double;
  end;

var
  i: integer;
  r: TMyRec;
  r2: TMyRec2;
begin
  r2.first:=42;
  r2.second:='Hello World';
  r2.third:=3.14;
  (i, ...r) := ...r2;
  if i<>42 then
    Halt(1);
  if r.second<>'Hello World' then
    Halt(2);
  if r.third<>3.14 then
    Halt(3);
  WriteLn('ok');
end.
