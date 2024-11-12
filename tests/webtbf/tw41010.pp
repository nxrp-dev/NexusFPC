{ %FAIL }
{$Mode ObjFpc}{$H+}

type
  TMyRec = class
  public procedure Foo(A: Integer);
  private A: Integer;
  end;

procedure TMyRec.Foo(A: Integer); begin end;

begin
end.

