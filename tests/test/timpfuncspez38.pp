{ %FAIL }

program timpfuncspez38;

{$mode delphi}
{$modeswitch advancedrecords}
{$modeswitch implicitfunctionspecialization}

type
  TMatrix<T, R, C> = record
    fCoordinates: array[R, C] of Double;
  end;

function mul<T, R, X, C>(A: TMatrix<T, R, X>; B: TMatrix<T, X, C>): TMatrix<T, R, C>;
begin
end;

type
  R1 = 1..3;
  R2 = 1..4;

var
  A: TMatrix<Double, R1, R2>;
  B: TMatrix<Double, R1, R1>;

begin
  mul(A, B);
end.
