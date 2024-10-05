program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

uses
  TypInfo;

type
  TVarRec = record
  case Boolean of
  True: (A, B: LongInt);
  False: (C, D, E, F: Word);
  end;

var
  ti: PTypeInfo;
  td:PTypeData;
  mf: PManagedField;
  r: TVarRec;
begin
  ti:=TypeInfo(TVarRec);
  if ti^.Kind<>tkRecord then
    halt(1);
  td:=GetTypeData(ti);
  mf:=@td^.TotalFieldCount;
  inc(pointer(mf),sizeof(td^.TotalFieldCount));
  if td^.TotalFieldCount <> 6 then
  begin
    WriteLn('Mismatch on TotalFieldCount');
    WriteLn('Expected: ', 4);
    WriteLn('  Actual: ', td^.TotalFieldCount);
    halt(1);
  end;
  if (UIntPtr(@r.A)-UIntPtr(@r)) <> mf[0].FldOffset then
  begin
    WriteLn('Mismatch on A');
    WriteLn('Expected: ', UIntPtr(@r.A)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[0].FldOffset);
    halt(1);
  end;
  if (UIntPtr(@r.B)-UIntPtr(@r)) <> mf[1].FldOffset then
  begin
    WriteLn('Mismatch on B');
    WriteLn('Expected: ', UIntPtr(@r.B)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[1].FldOffset);
    halt(1);
  end;
  if (UIntPtr(@r.C)-UIntPtr(@r)) <> mf[2].FldOffset then
  begin
    WriteLn('Mismatch on C');
    WriteLn('Expected: ', UIntPtr(@r.C)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[2].FldOffset);
    halt(1);
  end;
  if (UIntPtr(@r.D)-UIntPtr(@r)) <> mf[3].FldOffset then
  begin
    WriteLn('Mismatch on D');
    WriteLn('Expected: ', UIntPtr(@r.D)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[3].FldOffset);
    halt(1);
  end;
  if (UIntPtr(@r.E)-UIntPtr(@r)) <> mf[4].FldOffset then
  begin
    WriteLn('Mismatch on E');
    WriteLn('Expected: ', UIntPtr(@r.e)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[4].FldOffset);
    halt(1);
  end;
  if (UIntPtr(@r.F)-UIntPtr(@r)) <> mf[5].FldOffset then
  begin
    WriteLn('Mismatch on F');
    WriteLn('Expected: ', UIntPtr(@r.F)-UIntPtr(@r));
    WriteLn('  Actual: ', mf[5].FldOffset);
    halt(1);
  end;
  WriteLn('Ok');
end.