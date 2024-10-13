{ %FAIL }
program Test;

{$Mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

type
  TTest = record
    i: Integer;
  end;

operator =(const lhs,rhs: TTest): Boolean;
begin
  Result:=lhs.i=rhs.i;
end;

var
  a, b: TTest;
begin
  a.i:=1;
  b.i:=2;
  if not (a<b) then
    halt(1);
  if not (a<=b) then
    halt(1);
  if (a>b) then
    halt(1);
  if a>=b then
    halt(1);
  if a=b then
    halt(1);
  if not (a<>b) then
    halt(1);
  WriteLn('ok');
end.
