{$mode objfpc}
{$VariantRTTI On}
{$CheckVariantAccess On}

type
  TVarRec = record
  case sel:Integer of
  0..10: (A, B: LongInt);
  11..20: (C, D, E, F: Word);
  21..30: (G: Double);
  end;
var
  vr: TVarRec;
  p: PInteger;
begin
  vr.sel:=5;
  p:=@vr.A;
  p^ := 42;
  WriteLn('Ok');
end.
