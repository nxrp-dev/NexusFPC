
type
  TVarRec = record
  case Integer of
  0..10: (A, B: LongInt);
{$StrictVariants On}
  11..20: (C, D, E, F: Word);
{$StrictVariants Off}
  5: (G: Double);
  end;

var
  vr: TVarRec;  
begin
  if (@vr.A <> @vr.C) or (@vr.B <> @vr.E) then
    Halt(1);
end.