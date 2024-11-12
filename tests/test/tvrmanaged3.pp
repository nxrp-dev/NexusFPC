program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}
uses heaptrc;
type
  TVarRec = record
  case sel:Boolean of
  True: (s:String);
  False: (I: Integer);
  end;

var
  vr: TVarRec;
begin
  vr.sel:=True;
  vr.s:='Hello World';
  UniqueString(vr.s);
  vr.sel:=False;
  if Pointer(vr.s)<>nil then
    Halt(1);
  WriteLn('Ok');
end.
