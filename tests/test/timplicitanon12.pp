{$Mode ObjFPC}
{$modeswitch anonymousfunctions}
{$modeswitch nestedprocvars}

var
  s: string;
begin
  s := function(a1; b1): string is a1+b1('foo', 'bar');
  s := function(a2; b2): string is a2+b2('foo', 'bar');

  WriteLn(s);
  if s<>'foobar' then
    Halt(1);
end.
