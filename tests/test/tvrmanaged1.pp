program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

type
  TVarRec = record
  str: String;
  case Boolean of
  True: (A, B: LongInt);
  False: (C, D: Word);
  end;

var
  vr: TVarRec;
begin
  vr.str:='Foo';
  vr.A:=42;
end.
