{$Mode ObjFpc}

var
  arr: array[0..3] of array of array[0..1] of integer = [
    0..3: ([0..1:42])
  ];

  
begin
  if arr[0,0,0]<>42 then
    halt(1);
  if arr[1,0,0]<>42 then
    halt(2);
  if arr[1,0,1]<>42 then
    halt(3);
  WriteLn('Ok');
end.
