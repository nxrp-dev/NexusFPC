{$mode objfpc}
{$VariantRTTI On}
{$CheckVariantAccess On}

type
  TVarRec = record
  sel: Integer;
  case Integer of
  0..10: (A, B: LongInt);
  11..20: (C, D, E, F: Word);
  21..30: (G: Double);
  end;
var
  vr: TVarRec;
begin
  vr.sel:=5;
  vr.A := 42;
  vr.G := 32;
  WriteLn('Ok')
end.
