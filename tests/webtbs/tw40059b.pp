program tw40059b;
{$mode objfpc}{$H+}{$inline on}{$B-}
uses Math;
var Checks, Failures, Calls: LongInt;
procedure Check(Actual, Expected: Boolean);
begin
  Inc(Checks);
  if Actual <> Expected then
  begin Inc(Failures); WriteLn('FAIL ', Checks); end;
end;
function LessInline(A, B: Double): Boolean; inline;
begin Result := A < B; end;
function Mark: Boolean;
begin Inc(Calls); Result := True; end;
procedure Probe(A, B: Double; LT, GT, LE, GE: Boolean);
var Value: Boolean;
begin
  Value := False; if not (A < B) then Value := True; Check(Value,not LT);
  Value := False; if not (A > B) then Value := True; Check(Value,not GT);
  Value := False; if not (A <= B) then Value := True; Check(Value,not LE);
  Value := False; if not (A >= B) then Value := True; Check(Value,not GE);
  Check(not LessInline(A,B),not LT);
  Check(not ((A < B) or (A > B)),not (LT or GT));
  Check(not ((A <= B) and (A >= B)),not (LE and GE));
  Calls := 0;
  Check(not ((A < B) and Mark),not LT);
  Check((Calls=1),LT);
end;
procedure ProbeExtended(A, B: Extended; LT, GT, LE, GE: Boolean);
begin
  Check(not (A < B),not LT);
  Check(not (A > B),not GT);
  Check(not (A <= B),not LE);
  Check(not (A >= B),not GE);
end;
var Bits: QWord; N: Double; Saved: TFPUExceptionMask;
begin
  Bits := QWord($7FF800000000002B); Move(Bits,N,SizeOf(N));
  Saved := GetExceptionMask;
  SetExceptionMask(Saved+[exInvalidOp]);
  try
    Probe(N,7,False,False,False,False);
    Probe(7,N,False,False,False,False);
    Probe(N,N,False,False,False,False);
    Probe(-3,7,True,False,True,False);
    Probe(7,-3,False,True,False,True);
    Probe(7,7,False,False,True,True);
    ProbeExtended(N,7,False,False,False,False);
    ProbeExtended(7,N,False,False,False,False);
    ProbeExtended(N,N,False,False,False,False);
    ProbeExtended(-3,7,True,False,True,False);
    ProbeExtended(7,-3,False,True,False,True);
    ProbeExtended(7,7,False,False,True,True);
    Check(not (-3.0 < 7.0),False);
    Check(not (7.0 < -3.0),True);
  finally SetExceptionMask(Saved); end;
  WriteLn('tw40059b: ', Checks, ' checks, ', Failures, ' failures');
  if Failures <> 0 then Halt(1);
end.
