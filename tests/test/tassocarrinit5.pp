{$Mode ObjFpc}

type
  TTestRec = bitpacked record
    A: 0..3;
    B: 0..1;
    C: String;
    D: 0..3;
  end;

var
  arr: array[0..3] of TTestRec = [
    0..3: (A:2;B:1;C:'Hello World';D:3)
  ];
begin
  if arr[0].A<>2 then
    halt(1);
  if arr[1].A<>2 then
    halt(2);
  if arr[2].C<>'Hello World' then
    halt(3);
  if arr[3].D<>3 then
    halt(4);
  WriteLn('Ok');
end.
