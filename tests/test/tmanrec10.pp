{ %FAIL }
{$Mode ObjFpc}{$H+}
{$ModeSwitch AdvancedRecords}

type
  TChild = record
    class operator AddRef = nil;
  end;

  TMyRec = record
    c: TChild;
  end;

procedure Foo(rec: TMyRec);
begin

end;

begin
end.

