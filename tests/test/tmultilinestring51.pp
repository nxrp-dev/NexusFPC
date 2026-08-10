{ %Fail }
program testjunk4;
// junk added in multi line string with '''
// compilation should fail
{$modeswitch multilinestrings}
var
  s1:string;
begin
  s1:=
 '`''
 a
 '''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>1 then halt(1);
end.
