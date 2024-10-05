program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

uses
  TypInfo;

type
  TVarRec = record
  case Boolean of
  True: (A: Integer);
  False: (C, D: Word);
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
  if td^.TotalFieldCount <> 3 then
  begin
    WriteLn('Mismatch on TotalFieldCount');
    WriteLn('Expected: ', 3);
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
  if td^.VariantInfo^.Branches[0]^.BranchStart<>mf then
  begin
    WriteLn('Variant branch start mismatch');
    halt(1);
  end;
  if td^.VariantInfo^.Branches[0]^.BranchStart<>mf then
  begin
    WriteLn('Variant branch 0 start mismatch');
    halt(1);
  end;
  if td^.VariantInfo^.Branches[0]^.BranchEnd<>@mf[1] then
  begin
    WriteLn('Variant branch 0 end mismatch');
    halt(1);
  end;
  if td^.VariantInfo^.Branches[1]^.BranchStart<>@mf[1] then
  begin
    WriteLn('Variant branch 1 start mismatch');
    halt(1);
  end;
  if td^.VariantInfo^.Branches[1]^.BranchEnd<>@mf[td^.TotalFieldCount] then
  begin
    WriteLn('Variant branch 1 end mismatch');
    halt(1);
  end;
  WriteLn('Ok');
end.
