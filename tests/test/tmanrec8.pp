{$Mode ObjFpc}{$H+}
{$ModeSwitch AdvancedRecords}
uses SysUtils;
type
  TMyRec = record
    i: Integer;
    class operator :=(const rhs: Integer): TMyRec;
    class operator AddRef = nil;
  end;

class operator TMyRec.:=(const rhs: Integer): TMyRec;
begin
  Result.i:=rhs;
end;

var
  r1, r2: TMyRec;
begin
  r1 := 42;
  r2 := r1;
  if r2.i<>42 then
    Halt(1);
  WriteLn('Ok');
end.
