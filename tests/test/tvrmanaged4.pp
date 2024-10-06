program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}
uses heaptrc;
type
  TVarRec = record
  case sel:Integer of
  -10..-1: (s:String);
  0..15: (I: Integer);
  end;

var
  vr: TVarRec;
begin
  vr.sel:=-5;
  vr.s:='Hello World';
  UniqueString(vr.s);
  vr.sel:=1;
  if Pointer(vr.s)<>nil then
    Halt(1);
  WriteLn('Ok');
end.
