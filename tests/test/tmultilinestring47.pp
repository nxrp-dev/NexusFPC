{ %fail }
program testimpared3;
// even count impared multi line string with '''
// it fails and this is test for it
{$modeswitch multilinestrings}
var
  s1:string;
begin
  s1:=
 '''
 ''''
;
  writeln('>>>',s1,'<<<');
  if length(s1)<>0 then halt(1);
end.
