{ %FAIL }
{$Mode ObjFpc}{$H+}
{$ModeSwitch AdvancedRecords}

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

procedure Foo(rec: TMyRec);
begin

end;

begin
end.
