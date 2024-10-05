program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

type
  TVarRec = record
  case Boolean of
  True: (A, B: LongInt);
  False: (C, D, E, F: Word);
  end;

var
  vr: TVarRec;  
begin
  if (@vr.A <> @vr.C) or (@vr.B <> @vr.E) then
    Halt(1);
end.