{ test c style assignment operators with integer /= }

{$COPERATORS ON}
var
  i : LongInt;
  j : Int64;
begin
  i:=10;
  i /= 2;
  if i<>5 then
    halt(1);

  i:=-5;
  i /= 2;
  if i<>-2 then
    halt(2);

  j:=9;
  j /= 2;
  if j<>4 then
    halt(3);
end.
