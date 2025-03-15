{$Mode ObjFpc}

type
  TTestRec = record
    A: Integer;
    B: String;
    C: Extended;
  end;

var
  arr: array[0..3] of TTestRec = [
    0..3: (A:42;B:'Hello World';C:3.14)
  ];
begin
  if arr[0].A<>42 then
    halt(1);
  if arr[1].A<>42 then
    halt(2);
  if arr[2].B<>'Hello World' then
    halt(3);
  if arr[3].C<>3.14 then
    halt(4);
  WriteLn('Ok');
end.
