{$Mode ObjFpc}
var
  arr: array[0..3] of integer = [
    0:0;
    1:1;
    2:2;
    3:3
  ];
begin
  if arr[0]<>0 then
    halt(1);
  if arr[1]<>1 then
    halt(2);
  if arr[2]<>2 then
    halt(3);
  if arr[3]<>3 then
    halt(4);
  WriteLn('Ok');
end.
