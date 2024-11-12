{ %FAIL }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}
{$ManagedVariants On}

type
  TVarRec = record
  case Boolean of
  True: (s:String);
  False: (I: Integer);
  end;

begin
end.
