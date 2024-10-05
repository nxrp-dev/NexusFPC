{$mode objfpc}
{$VariantRTTI On}
{$CheckVariantAccess On}

uses sysutils;

type
  TVarRec = record
  case sel:Boolean of
  True:(A: record A, B: Integer end);
  False:(B: Integer);
  end;
var
  vr: TVarRec;
begin
  vr.sel:=False;
  try
    vr.A.A:=42;
  except on E: EVariantAccessError do
  begin
    WriteLn('Ok');
    Exit;
  end;
  end;
  Halt(1);
end.
