program tw40059;
{$mode objfpc}{$H+}{$inline off}

uses Math;

{ The oracle is the unordered-comparison truth table, not floating arithmetic. }
type
  TTruth = array[0..5] of Boolean;
const
  Names: array[0..5] of string = ('<', '>', '<=', '>=', '=', '<>');
  Unordered: TTruth = (False, False, False, False, False, True);
  Less: TTruth = (True, False, True, False, False, True);
  Greater: TTruth = (False, True, False, True, False, True);
  Equal: TTruth = (False, False, True, True, True, False);
var
  Checks, Failures: LongInt;

procedure Verify(const Width, LabelText: string; const Direct, Negated,
  Wanted: TTruth);
var
  I: LongInt;
begin
  for I := 0 to 5 do
  begin
    Inc(Checks, 3);
    if Direct[I] <> Wanted[I] then
    begin
      Inc(Failures);
      WriteLn('FAIL ', Width, ' ', LabelText, ' ', Names[I],
        ' actual=', Direct[I], ' expected=', Wanted[I]);
    end;
    if Negated[I] <> not Wanted[I] then
    begin
      Inc(Failures);
      WriteLn('FAIL ', Width, ' ', LabelText, ' not(', Names[I],
        ') actual=', Negated[I], ' expected=', not Wanted[I]);
    end;
    if Negated[I] = Direct[I] then
    begin
      Inc(Failures);
      WriteLn('FAIL ', Width, ' ', LabelText, ' ', Names[I],
        ' direct and negated agree: ', Direct[I]);
    end;
  end;
end;

procedure Check32(const LabelText: string; A, B: Single; const Wanted: TTruth);
var
  D, N: TTruth;
begin
  D[0] := A < B; D[1] := A > B; D[2] := A <= B;
  D[3] := A >= B; D[4] := A = B; D[5] := A <> B;
  N[0] := not (A < B); N[1] := not (A > B); N[2] := not (A <= B);
  N[3] := not (A >= B); N[4] := not (A = B); N[5] := not (A <> B);
  Verify('binary32', LabelText, D, N, Wanted);
end;

procedure Check64(const LabelText: string; A, B: Double; const Wanted: TTruth);
var
  D, N: TTruth;
begin
  D[0] := A < B; D[1] := A > B; D[2] := A <= B;
  D[3] := A >= B; D[4] := A = B; D[5] := A <> B;
  N[0] := not (A < B); N[1] := not (A > B); N[2] := not (A <= B);
  N[3] := not (A >= B); N[4] := not (A = B); N[5] := not (A <> B);
  Verify('binary64', LabelText, D, N, Wanted);
end;

function Make32(Bits: LongWord): Single;
begin
  Move(Bits, Result, SizeOf(Result));
end;

function Make64(Bits: QWord): Double;
begin
  Move(Bits, Result, SizeOf(Result));
end;

var
  NaN32: Single;
  NaN64: Double;
  SavedMask: TFPUExceptionMask;
begin
  SavedMask := GetExceptionMask;
  SetExceptionMask(SavedMask + [exInvalidOp]);
  try
    { All-one exponent, quiet bit set, nonzero payload; no NaN constant folding. }
    NaN32 := Make32($7FC00035);
    NaN64 := Make64(QWord($7FF800000000002B));
    Check32('nan,-3', NaN32, -3, Unordered);
    Check32('-3,nan', -3, NaN32, Unordered);
    Check32('nan,0', NaN32, 0, Unordered);
    Check32('0,nan', 0, NaN32, Unordered);
    Check32('nan,7', NaN32, 7, Unordered);
    Check32('7,nan', 7, NaN32, Unordered);
    Check32('nan,nan', NaN32, NaN32, Unordered);
    Check32('-3,7', -3, 7, Less);
    Check32('7,-3', 7, -3, Greater);
    Check32('7,7', 7, 7, Equal);
    Check64('nan,-3', NaN64, -3, Unordered);
    Check64('-3,nan', -3, NaN64, Unordered);
    Check64('nan,0', NaN64, 0, Unordered);
    Check64('0,nan', 0, NaN64, Unordered);
    Check64('nan,7', NaN64, 7, Unordered);
    Check64('7,nan', 7, NaN64, Unordered);
    Check64('nan,nan', NaN64, NaN64, Unordered);
    Check64('-3,7', -3, 7, Less);
    Check64('7,-3', 7, -3, Greater);
    Check64('7,7', 7, 7, Equal);
  finally
    SetExceptionMask(SavedMask);
  end;
  WriteLn('quiet_nan_relations: ', Checks, ' checks, ', Failures, ' failures');
  if Failures <> 0 then Halt(1);
end.
