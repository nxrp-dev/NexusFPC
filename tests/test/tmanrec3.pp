{$Mode ObjFpc}{$H+}
{$ModeSwitch AdvancedRecords}

type
  TMyRec = record
    i: Integer;
    class operator :=(const rhs: Integer): TMyRec;
    class operator Copy = nil;
    class operator +(const lhs,rhs: TMyRec): TMyRec;
  end;

class operator TMyRec.:=(const rhs: Integer): TMyRec;
begin
  Result.i:=rhs;
end;

class operator TMyRec.+(const lhs,rhs: TMyRec): TMyRec;
begin
  Result.i:=lhs.i+rhs.i;
end;

var
  r1, r2, r3: TMyRec;
begin
  r1 := 42;
  r2 := 32;
  r3 := r1 + r2;
  if r3.i<>42+32 then
    Halt(1);
  WriteLn('Ok');
end.
