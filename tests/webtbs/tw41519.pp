{ %NORUN }

{ Empty parens after a member access on a generic type parameter (X) should
  be accepted during generic declaration, just like non-empty parens already
  were. The actual member check happens at specialization time. }

{$mode objfpc}{$H+}
program tw41519;

type
  generic TGen<X> = class
    procedure p;
  end;

procedure TGen.p;
var
  c: X;
begin
  c.AnyMethodOrField1(1);
  c.AnyMethodOrField2();
  c := X.Whatever1;
  c := X.Whatever2();
end;

begin
end.
