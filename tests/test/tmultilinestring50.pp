{ %Fail }
program testjunk3;
// junk comment added in multi line string with '''
// it is failing to compile, but it should be tested for
{$modeswitch multilinestrings}
var
  s1:string;
begin

  s1:=
 '''{comment not allowd here}
 '''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>0 then halt(1);
end.
