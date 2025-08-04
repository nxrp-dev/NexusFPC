{ %Fail }
program testjunk6;
// junk added in multi line string with '''
// compilation should fail
{$modeswitch multilinestrings}
var
  s1:string;
begin
s1:=
  '   '' ``` `` ``` ` ``       ''''
  c
  '''''''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>1 then halt(1);
end.
