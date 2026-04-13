{ %FAIL }

program tgeneric131;

{$mode delphi}

type
  R1 = 1..3;
  R2 = 1..100;

  TVector<C> = record
    X: array[C] of Byte;
  end;

var
  A: TVector<R2>;
  B: TVector<R1>;

begin
  A := B;
end.
