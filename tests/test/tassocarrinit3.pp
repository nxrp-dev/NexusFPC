{$Mode ObjFpc}

type
  TTest = (A, B, C, D);

var
  arr: array[TTest] of integer = [
    A:0;
    B..C:1;
    D:3
  ];
begin
  if arr[A]<>0 then
    halt(1);
  if arr[B]<>1 then
    halt(2);
  if arr[C]<>1 then
    halt(3);
  if arr[D]<>3 then
    halt(4);
  WriteLn('Ok');
end.
