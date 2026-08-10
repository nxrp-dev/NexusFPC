program testspace;
// space in multi line string with '''
// this is fine for command line compiler,
// but impossible upon save or edit for Textmode IDE
{$modeswitch multilinestrings}
var
  s1:string;
begin
s1:=
{ +----------- space in multi line string }
{ |                                       }
  '''
   
  '''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>1 then halt(1);
  if (length(s1)=1) and (s1[1]<>' ') then halt(2);
end.
