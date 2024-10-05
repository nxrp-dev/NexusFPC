{$mode objfpc}
{$VariantRTTI On}

uses typinfo;

type
  TVarRec = record
  case sel:Byte of
  0..10: (A, B: LongInt);
  11..20: (C, D, E, F: Word);
  21..30: (G: Double);
  end;
var
  vr: TVarRec;
  rd: PRecordData;
begin
  rd := PRecordData(GetTypeData(TypeInfo(TVarRec)));
  vr.sel := 5;
  if rd^.VariantBranch[@vr] <> 0 then
    Halt(1);
  vr.sel := 15;
  if rd^.VariantBranch[@vr] <> 1 then
    Halt(1);
  vr.sel := 25;
  if rd^.VariantBranch[@vr] <> 2 then
    Halt(1);
  WriteLn('Ok')
end.
