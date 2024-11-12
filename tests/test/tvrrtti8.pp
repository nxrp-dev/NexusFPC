{$mode objfpc}
{$VariantRTTI On}

uses typinfo;

type
  TVarRec = record
  case sel:(Enum1, Enum2, Enum3) of
  Enum1: (A, B: LongInt);
  Enum2: (C, D, E, F: Word);
  Enum3: (G: Double);
  end;
var
  vr: TVarRec;
  rd: PRecordData;
begin
  rd := PRecordData(GetTypeData(TypeInfo(TVarRec)));
  vr.sel := Enum1;
  if rd^.VariantBranch[@vr] <> 0 then
    Halt(1);
  vr.sel := Enum2;
  if rd^.VariantBranch[@vr] <> 1 then
    Halt(1);
  vr.sel := Enum3;
  if rd^.VariantBranch[@vr] <> 2 then
    Halt(1);
  WriteLn('Ok')
end.
