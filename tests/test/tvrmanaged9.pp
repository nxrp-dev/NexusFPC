{ %OPT=-Sew }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}
type
  TVarRec = record
  case sel:Boolean of
  True: (s:String);
  False: (I: Integer);
  end;

procedure ref(constref b: Boolean);
begin
  
end;

var
  vr: TVarRec;
begin
  vr:=Default(TVarRec);
  ref(vr.sel);
end.
