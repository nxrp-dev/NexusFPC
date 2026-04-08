{ generic type alias for existing record - should not cause IE 2012101001 }
program tgenalias1;

{$mode objfpc}

type
  TPoint = record
    x, y: Integer;
  end;

  generic TAlias<_T> = TPoint;

generic procedure DoSomething<_T>();
begin
end;

var
  p: TPoint;
begin
  specialize DoSomething<specialize TAlias<Integer>>();
  { verify the original type is not corrupted }
  p.x := 1;
  p.y := 2;
  if (p.x <> 1) or (p.y <> 2) then
    halt(1);
end.
