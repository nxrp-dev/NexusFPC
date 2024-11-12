{ %FAIL }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}
uses heaptrc;
type
  TVarRec = record
  case sel:Integer of
  0..10: (I: Integer);
  11..20: (s:String);
  15..18: (D: Double);
  end;

var
  vr: TVarRec;
begin
  vr.sel:=8;
  vr.s:='Hello World';
  UniqueString(vr.s);
  vr.sel+=5;
  if Pointer(vr.s)<>nil then
    Halt(1);
  WriteLn('Ok');
end.
