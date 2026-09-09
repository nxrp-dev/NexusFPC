{ %opt=-O2 }

{ @volatile(x) must return the address of x, not a temporary copy }
program tw41704;
{$mode objfpc}

var
  a: integer;
  p: pointer;
begin
  p := @volatile(a);
  if p <> @a then
    halt(1);
end.
