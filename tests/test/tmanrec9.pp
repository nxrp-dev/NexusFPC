{ %FAIL }
{$Mode ObjFpc}{$H+}
{$ModeSwitch AdvancedRecords}

type
  TChild = record
    class operator Copy = nil;
  end;

  TMyRec = record
    c: TChild;
  end;

var
  r1, r2: TMyRec;
begin
  r1 := r2;
end.

