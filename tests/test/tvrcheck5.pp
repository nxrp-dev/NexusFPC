{$mode objfpc}
{$VariantRTTI On}
{$CheckVariantAccess On}

type
  TVarRec = record
  case sel:Boolean of
  True:(A: record A, B: Integer end);
  False:(B: Integer);
  end;
var
  vr: TVarRec;
begin
  vr.sel:=True;
  vr.A.A:=42;
  WriteLn(vr.A.A);
  WriteLn('Ok')
end.
