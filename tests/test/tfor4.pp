program Project1;
{$Mode objfpc}

type
  TMyRec = record
    i: Integer;
  end;

operator <=(const rec: TMyRec;avalue:integer): boolean;
begin
  result:=rec.i<=avalue;
end;
operator >=(const rec: TMyRec;avalue:integer): boolean;
begin
  result:=rec.i>=avalue;
end;
operator +(const lhs,rhs: TMyRec): TMyRec;
begin
  result.i:=lhs.i + rhs.i;
end;
operator :=(avalue:integer): TMyRec;
begin
  result.i:=avalue;
end;

var
  r: TMyRec;
  i: Integer;
begin
  i:=0;
  for r:=1 to 10 do
    inc(i);
  if i<>10 then
    Halt(1);
  WriteLn('Ok');
end.
