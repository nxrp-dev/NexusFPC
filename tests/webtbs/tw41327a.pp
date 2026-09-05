{ %RECOMPILE }
{$mode objfpc}
{$modeswitch advancedrecords}

uses u41327b;

type
  THandle = type TIntegerWrapper;

var
  hw: THWND;
  hnd: THandle;
begin
  hw := THWND(0);
  hnd := THandle(-1);
  if Integer(hw) <> 0 then Halt(1);
  if Integer(hnd) <> -1 then Halt(2);
  if not (hw=hw) then Halt(3);
  if hw<>hw then Halt(4);
end. 
