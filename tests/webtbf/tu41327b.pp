{%FAIL}
{$mode objfpc}
{$modeswitch advancedrecords}

uses u41327a;

type
  TIntegerWrapper = specialize TTypeWrapper<Integer>;
  THWND = type TIntegerWrapper;
  THandle = type TIntegerWrapper;
  
  
var
  hw: THWND;
  hnd: THandle;
begin
  hw := 0;
  Halt(1);
end. 
