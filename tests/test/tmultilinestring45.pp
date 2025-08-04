program testimpared;
// impared multi line string with '''
{$modeswitch multilinestrings}
var
  s1:string;
  s2:string;
  s3:string;
begin

  s1:=
 '''
 '''''
;
  s2:=
 '''''
 '''''''
;
s3:=
  '''''''
  '''''''''''''''''''''''''
;
  writeln('>>>',s1,'<<<');
  writeln('>>>',s2,'<<<');
  writeln('>>>',s3,'<<<');
  if length(s1)<>0 then halt(1);
  if length(s2)<>0 then halt(2);
  if length(s3)<>0 then halt(3);
end.
