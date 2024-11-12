{ %RECOMPILE  }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

uses
  TypInfo, uvrrtti11;

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
  if td^.TotalFieldCount <> 4 then
  begin
    WriteLn('Mismatch on TotalFieldCount');
    WriteLn('Expected: ', 4);
    WriteLn('  Actual: ', td^.TotalFieldCount);
    halt(1);
  end;
  if not assigned(td^.VariantInfo) then
  begin
    WriteLn('Missing variant info');
    halt(1);
  end;
  if td^.VariantInfo^.BranchCount <> 2 then
  begin
    WriteLn('Mismatch on BranchCount');
    WriteLn('Expected: ', 2);
    WriteLn('  Actual: ', td^.VariantInfo^.BranchCount);
    halt(1);
  end;
  td:=GetTypeData(td^.VariantInfo^.Branches[0]^.BranchField.TypeRef);
  if td^.TotalFieldCount <> 2 then
  begin
    WriteLn('Mismatch on nested TotalFieldCount');
    WriteLn('Expected: ', 2);
    WriteLn('  Actual: ', td^.TotalFieldCount);
    halt(1);
  end;
  if not assigned(td^.VariantInfo) then
  begin
    WriteLn('Missing nested variant info');
    halt(1);
  end;
  if td^.VariantInfo^.BranchCount <> 2 then
  begin
    WriteLn('Mismatch on nested BranchCount');
    WriteLn('Expected: ', 2);
    WriteLn('  Actual: ', td^.VariantInfo^.BranchCount);
    halt(1);
  end;

  WriteLn('Ok');
end.
