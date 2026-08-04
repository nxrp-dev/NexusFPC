{ Inlining a function that uses `absolute` to alias its Result (or a
  parameter) to a differently-laid-out type must not turn field writes
  into register subset-insert ops against an uninitialized register.
  Previously the non-inlined path was correct but the inlined path
  dropped all fields except the first. }

{$mode delphi}

type
  TFoobar = packed record
    A, B, C: uint16;
  end;

  TA = packed record
    Foobar: TFoobar;
    R: uint16;
  end;

  TB = packed record
    R: uint16;
    Foobar: TFoobar;
  end;

function Convert_Normal(const P: Pointer): Pointer;
var
  LA: TA absolute P;
  LB: TB absolute Result;
begin
  LB.R := LA.R;
  LB.Foobar.A := LA.Foobar.A;
  LB.Foobar.B := LA.Foobar.B;
  LB.Foobar.C := LA.Foobar.C;
end;

function Convert_Inlined(const P: Pointer): Pointer; inline;
var
  LA: TA absolute P;
  LB: TB absolute Result;
begin
  LB.R := LA.R;
  LB.Foobar.A := LA.Foobar.A;
  LB.Foobar.B := LA.Foobar.B;
  LB.Foobar.C := LA.Foobar.C;
end;

var
  P, RNormal, RInlined: Pointer;
begin
  P := Pointer(PtrUInt($1122334455667788));
  RNormal := Convert_Normal(P);
  RInlined := Convert_Inlined(P);
  if RNormal <> RInlined then
    halt(1);
  { Expected byte rotation: [R, A, B, C] = [P[6..7], P[0..1], P[2..3], P[4..5]] }
  if PtrUInt(RInlined) <> PtrUInt($3344556677881122) then
    halt(2);
end.
