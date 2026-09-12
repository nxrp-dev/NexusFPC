{ %CPU=aarch64 }
program tcmpsignedmin;
{$mode objfpc}{$H+}{$inline off}

{ Signed integer ordering at the minimum representable value. }
var
  Failures, Checks: LongInt;

procedure Expect(const Width, Path, Relation: string; Value: Int64;
  Actual, Wanted: Boolean);
begin
  Inc(Checks);
  if Actual <> Wanted then
  begin
    Inc(Failures);
    WriteLn('FAIL width=', Width, ' path=', Path, ' value=', Value,
      ' relation=', Relation, ' actual=', Actual, ' expected=', Wanted);
  end;
end;

procedure Constant32(Value: LongInt; IsMinimum: Boolean);
begin
  Expect('32', 'constant', '<', Value, Value < Low(LongInt), False);
  Expect('32', 'constant', '>', Value, Value > Low(LongInt), not IsMinimum);
  Expect('32', 'constant', '<=', Value, Value <= Low(LongInt), IsMinimum);
  Expect('32', 'constant', '>=', Value, Value >= Low(LongInt), True);
  Expect('32', 'constant', '=', Value, Value = Low(LongInt), IsMinimum);
  Expect('32', 'constant', '<>', Value, Value <> Low(LongInt), not IsMinimum);
end;

procedure Runtime32(Value, Threshold: LongInt; IsMinimum: Boolean);
begin
  Expect('32', 'runtime', '<', Value, Value < Threshold, False);
  Expect('32', 'runtime', '>', Value, Value > Threshold, not IsMinimum);
  Expect('32', 'runtime', '<=', Value, Value <= Threshold, IsMinimum);
  Expect('32', 'runtime', '>=', Value, Value >= Threshold, True);
  Expect('32', 'runtime', '=', Value, Value = Threshold, IsMinimum);
  Expect('32', 'runtime', '<>', Value, Value <> Threshold, not IsMinimum);
end;

procedure Constant64(Value: Int64; IsMinimum: Boolean);
begin
  Expect('64', 'constant', '<', Value, Value < Low(Int64), False);
  Expect('64', 'constant', '>', Value, Value > Low(Int64), not IsMinimum);
  Expect('64', 'constant', '<=', Value, Value <= Low(Int64), IsMinimum);
  Expect('64', 'constant', '>=', Value, Value >= Low(Int64), True);
  Expect('64', 'constant', '=', Value, Value = Low(Int64), IsMinimum);
  Expect('64', 'constant', '<>', Value, Value <> Low(Int64), not IsMinimum);
end;

procedure Runtime64(Value, Threshold: Int64; IsMinimum: Boolean);
begin
  Expect('64', 'runtime', '<', Value, Value < Threshold, False);
  Expect('64', 'runtime', '>', Value, Value > Threshold, not IsMinimum);
  Expect('64', 'runtime', '<=', Value, Value <= Threshold, IsMinimum);
  Expect('64', 'runtime', '>=', Value, Value >= Threshold, True);
  Expect('64', 'runtime', '=', Value, Value = Threshold, IsMinimum);
  Expect('64', 'runtime', '<>', Value, Value <> Threshold, not IsMinimum);
end;

procedure More32(Value: LongInt; Index: LongInt);
var B: Boolean; Selected, Wanted: LongInt;
begin
  Expect('32', 'left', '<', Value, Low(LongInt) < Value, Index <> 0);
  Expect('32', 'left', '>', Value, Low(LongInt) > Value, False);
  Expect('32', 'left', '<=', Value, Low(LongInt) <= Value, True);
  Expect('32', 'left', '>=', Value, Low(LongInt) >= Value, Index = 0);
  Expect('32', 'left', '=', Value, Low(LongInt) = Value, Index = 0);
  Expect('32', 'left', '<>', Value, Low(LongInt) <> Value, Index <> 0);
  B := False;
  if Value > Low(LongInt) then B := True;
  Expect('32', 'branch', '>', Value, B, Index <> 0);
  B := False;
  if Value <= Low(LongInt) then B := True;
  Expect('32', 'branch', '<=', Value, B, Index = 0);
  B := False;
  if Low(LongInt) < Value then B := True;
  Expect('32', 'left-branch', '<', Value, B, Index <> 0);
  case Value of
    Low(LongInt)..Low(LongInt)+1: Selected := 1;
    -1..1: Selected := 2;
    High(LongInt): Selected := 3;
    else Selected := 0;
  end;
  if Index < 2 then Wanted := 1
  else if Index < 5 then Wanted := 2
  else Wanted := 3;
  Expect('32', 'case', '=', Value, Selected = Wanted, True);
end;

procedure More64(Value: Int64; Index: LongInt);
var B: Boolean; Selected, Wanted: LongInt;
begin
  Expect('64', 'left', '<', Value, Low(Int64) < Value, Index <> 0);
  Expect('64', 'left', '>', Value, Low(Int64) > Value, False);
  Expect('64', 'left', '<=', Value, Low(Int64) <= Value, True);
  Expect('64', 'left', '>=', Value, Low(Int64) >= Value, Index = 0);
  Expect('64', 'left', '=', Value, Low(Int64) = Value, Index = 0);
  Expect('64', 'left', '<>', Value, Low(Int64) <> Value, Index <> 0);
  B := False;
  if Value > Low(Int64) then B := True;
  Expect('64', 'branch', '>', Value, B, Index <> 0);
  B := False;
  if Value <= Low(Int64) then B := True;
  Expect('64', 'branch', '<=', Value, B, Index = 0);
  B := False;
  if Low(Int64) < Value then B := True;
  Expect('64', 'left-branch', '<', Value, B, Index <> 0);
  case Value of
    Low(Int64)..Low(Int64)+1: Selected := 1;
    -1..1: Selected := 2;
    High(Int64): Selected := 3;
    else Selected := 0;
  end;
  if Index < 2 then Wanted := 1
  else if Index < 5 then Wanted := 2
  else Wanted := 3;
  Expect('64', 'case', '=', Value, Selected = Wanted, True);
end;

const
  Values32: array[0..5] of LongInt = (Low(LongInt), Low(LongInt)+1,
    -1, 0, 1, High(LongInt));
  Values64: array[0..5] of Int64 = (Low(Int64), Low(Int64)+1,
    -1, 0, 1, High(Int64));
var
  I: LongInt;
begin
  for I := 0 to 5 do
  begin
    More32(Values32[I], I);
    More64(Values64[I], I);
    Constant32(Values32[I], I = 0);
    Runtime32(Values32[I], Values32[0], I = 0);
    Constant64(Values64[I], I = 0);
    Runtime64(Values64[I], Values64[0], I = 0);
  end;
  WriteLn('signed_minimum: ', Checks, ' checks, ', Failures, ' failures');
  if Failures <> 0 then Halt(1);
end.
