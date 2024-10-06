program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}
uses heaptrc;
type
  TVarRec = record
  case sel:Integer of
  0..10: (s:String);
  11..20: (I: Integer);
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
