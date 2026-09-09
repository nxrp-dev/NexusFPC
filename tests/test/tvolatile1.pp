{ %opt=-O3 }

{ var-parameter passing through volatile/aligned/unaligned wrappers
  must reach the local var via make_not_regable }
program tvolatile1;
{$mode objfpc}

procedure SetIt(var x: integer);
begin
  x := 42;
end;

procedure SetIt2(var x: integer);
begin
  x := 99;
end;

procedure SetIt3(var x: integer);
begin
  x := 7;
end;

function TestVolatileVar: integer;
var
  a: integer;
begin
  a := 0;
  SetIt(volatile(a));
  result := a;
end;

function TestAlignedVar: integer;
var
  a: integer;
begin
  a := 0;
  SetIt2(aligned(a));
  result := a;
end;

function TestUnalignedVar: integer;
var
  a: integer;
begin
  a := 0;
  SetIt3(unaligned(a));
  result := a;
end;

begin
  if TestVolatileVar <> 42 then
    halt(1);
  if TestAlignedVar <> 99 then
    halt(2);
  if TestUnalignedVar <> 7 then
    halt(3);
end.
