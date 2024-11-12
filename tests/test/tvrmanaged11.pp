{ %OPT=-Sew }
program managed_variant_test;

{$Mode ObjFPC}{$H+}
{$ModeSwitch AdvancedRecords}
{$VariantRTTI On}
{$ManagedVariants On}
uses heaptrc;
type
  TContainer = record
  vr: record
    case sel:Boolean of
    True: (s:String);
    False: (I: Integer);
    end;
  property Test: Boolean read vr.sel write vr.sel;
  end;
var
  r: TContainer;
begin
  r.vr.sel:=True;
  r.vr.s:='Hello World';
  UniqueString(r.vr.s);
  r.Test:=False;
  if Pointer(r.vr.s)<>nil then
    Halt(1);
  WriteLn('Ok');
end.
