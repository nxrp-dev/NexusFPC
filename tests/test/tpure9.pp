{ %FAIL }
program tpure9;

function foo(i:longword):shortstring; pure;
var s : shortstring;
      n : longword;
begin
  s:='';
  for n:=1 to i do s:=s +'a';
  //-- not assigning return value - make sure this doesn't cause a crash
end;

begin
  writeln(foo(9));
end.