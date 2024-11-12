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
begin
  vr.sel:=5;
  try
    vr.G := 42;
  except on E: EVariantAccessError do
  begin
    WriteLn('Ok');
    Exit;
  end;
  end;
  Halt(1);
end.
