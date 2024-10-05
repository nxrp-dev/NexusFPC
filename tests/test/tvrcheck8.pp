{$mode objfpc}
{$VariantRTTI On}
{$CheckVariantAccess On}

uses sysutils;

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
  vr.sel:=15;
  try
    p:=@vr.A;
    p^ := 42;
  except on E: EVariantAccessError do
  begin
    WriteLn('Ok');
    Exit;
  end;
  end;
  WriteLn('Ok')
end.
