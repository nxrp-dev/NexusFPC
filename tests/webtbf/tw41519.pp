{ %FAIL }

{ Specializing a generic on a type that does not have the members used in
  the generic body must still error out, even with empty parens. This
  guards the fix in webtbs/tw41519 from silently swallowing unknown members
  at specialization time. }

{$mode objfpc}{$H+}
program tw41519;

type
  generic TGen<X> = class
    procedure p;
  end;

  TFoo = class
  end;

procedure TGen.p;
var
  c: X;
begin
  c.NotHere();
end;

var
  g: specialize TGen<TFoo>;
begin
  g := specialize TGen<TFoo>.Create;
  g.p;
end.
