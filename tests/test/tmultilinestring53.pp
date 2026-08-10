program testjunk6;
// extra spaces added in multi line string with '''
{$modeswitch multilinestrings}
var
  s1:string;
begin
s1:=
{    +------+----- extra spaces }
{    |      |                   }
  '''        
  c
  '''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>1 then halt(1);
end.
