program Test;

{$Mode ObjFPC}{$H+}
{$modeswitch advancedrecords}

type
  TTest1 = record
    i: Integer;
  end;

  TTest2 = type TTest1;

operator <(const lhs: TTest1; const rhs: TTest2): Boolean;
begin
  Result:=lhs.i<rhs.i;
end;

operator <(const lhs: TTest2; const rhs: TTest1): Boolean;
begin
  Result:=lhs.i<rhs.i;
end;

var
  a: TTest1;
  b: TTest2;
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
