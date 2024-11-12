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
  td: PTypeData;
  vi: PVariantInfo;
begin
  ti:=TypeInfo(TVarRec);
  if ti^.Kind<>tkRecord then
    halt(1);
  td:=GetTypeData(ti);
  vi:=td^.VariantInfo;
  if not assigned(vi) then
  begin
    WriteLn('VariantInfo not set');
    Halt(1);
  end;
  if vi^.VariantOffset > 0 then
  begin
    WriteLn('Unexpected VariantOffset');
    WriteLn('Expected: 0');
    WriteLn('  Actual: ', vi^.VariantOffset);
    Halt(1);
  end;
  if assigned(vi^.SwitchField) then
  begin
    WriteLn('There should not be a switch field');
    Halt(1);
  end;
  if (vi^.BranchCount <> 2) then
  begin
    WriteLn('Unexpected BranchCount');
    WriteLn('Expected: 2');
    WriteLn('  Actual: ', vi^.BranchCount);
    Halt(1);
  end;
  if vi^.Branches[0]^.LabelCount <> 1 then
  begin
    WriteLn('Unexpected LabelCount');
    WriteLn('Expected: 1');
    WriteLn('  Actual: ', vi^.Branches[0]^.LabelCount);
    Halt(1);
  end;
  if vi^.Branches[0]^.Labels[0,0] <> ord(True) then
  begin
    WriteLn('Unexpected Branch label');
    WriteLn('Expected: ', ord(True));
    WriteLn('  Actual: ', vi^.Branches[0]^.Labels[0,0]);
    Halt(1);
  end;
  if UIntPtr(vi^.Branches[0]^.BranchStart) <> UIntPtr(@td^.TotalFieldCount)+SizeOf(td^.TotalFieldCount) then
  begin
    WriteLn('Unexpected Branch start');
    Halt(1);
  end;
  if vi^.Branches[1]^.LabelCount <> 1 then
  begin
    WriteLn('Unexpected LabelCount');
    WriteLn('Expected: 1');
    WriteLn('  Actual: ', vi^.Branches[1]^.LabelCount);
    Halt(1);
  end;
  if vi^.Branches[1]^.Labels[0,0] <> ord(False) then
  begin
    WriteLn('Unexpected Branch label');
    WriteLn('Expected: ', ord(False));
    WriteLn('  Actual: ', vi^.Branches[1]^.Labels[0,0]);
    Halt(1);
  end;
  if UIntPtr(vi^.Branches[1]^.BranchStart) <> UIntPtr(@td^.TotalFieldCount)+SizeOf(td^.TotalFieldCount)+SizeOf(TManagedField)*2 then
  begin
    WriteLn('Unexpected Branch start');
    Halt(1);
  end;

  WriteLn('Ok');
end.