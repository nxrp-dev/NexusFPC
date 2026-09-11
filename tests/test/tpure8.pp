{ %OPT=-Sew }

program tpure8;

function foo(i:longword):ansistring; pure;
var s : shortstring;
      n : longword;
begin
  s:='';
  for n:=1 to i do s:=s +'a';
  foo:=s; // Make sure assigning to an ansistring result doesn't make the pure function ineligible.
end;

begin
  if (foo(9) <> 'aaaaaaaaa') then
    Halt(1);
  writeln('ok');
end.