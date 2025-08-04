program testalpha3;
// alpha and apostrophes in multi line string with '''
{$modeswitch multilinestrings}
var
  s1:string;
  s2:string;
  s3:string;
begin
  s1:=
 '''
 'a'
 '''
;
  s2:=
 '''''
 ''''b''''
 '''''
;
s3:=
  '''''''
  '''''ab'''''
  '''''''
;
  writeln('>>>',s1,'<<<');
  writeln('>>>',s2,'<<<');
  writeln('>>>',s3,'<<<');
  if length(s1)<>3 then halt(1);
  if length(s2)<>9 then halt(2);
  if length(s3)<>12 then halt(3);
end.
