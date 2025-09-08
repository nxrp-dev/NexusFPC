{ %FAIL }
{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

type
  TMyRec = record
    first: Integer;
    second: String;
  end;

var
  r: TMyRec;
  i: Integer;
  s: String;
  d: double;
begin
  r.first := 42;
  r.second := 'Hello World';
  (i, s, d) := ...r;
  if i<>42 then
    Halt(1);
  if s<>'Hello World' then
    Halt(2);
  WriteLn('ok');
end.
