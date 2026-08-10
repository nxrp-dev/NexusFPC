program testempty2;
// empty multi line string with '''''
{$modeswitch multilinestrings}
var
  s1:string;
  s2:string;
begin
  s1:=
'''''
'''''
;
s2:=
  '''''

  '''''
;
  writeln('>>>',s1,'<<<');
  writeln('>>>',s2,'<<<');
  if length(s1)<>0 then halt(1);
  if length(s2)<>0 then halt(2);
end.
