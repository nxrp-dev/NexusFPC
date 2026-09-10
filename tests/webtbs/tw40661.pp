{ %NORUN }

program tw40661;

generic procedure proc<T>(a: T; b: byte);
begin
end;

generic procedure proc<T>(a: T);
begin
  specialize proc<T>(a, 0); //project1.lpr(16,1) Error: Internal error 200612311
end;

begin
end.
