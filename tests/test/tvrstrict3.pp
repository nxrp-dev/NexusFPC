{ %FAIL }
{$StrictVariants On}

type
  TVarRec = record
  case Integer of
  1..10: (A, B: LongInt);
  11..20: (C, D, E, F: Word);
  end;

var
  vr: TVarRec;  
begin
  if (@vr.A <> @vr.C) or (@vr.B <> @vr.E) then
    Halt(1);
end.