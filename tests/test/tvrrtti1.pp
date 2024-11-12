{ %FAIL }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

type
  TVarRec = record
  case Boolean of
  True: (A, B: LongInt);
  False: (A, B, C, D: Word);
  end;

begin
end.