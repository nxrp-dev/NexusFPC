{ %OPT=-O2 -MOBJFPC -Sv }

program tvectorisation1;

type
  TSingleSet = packed record
    X, Y, Z, W: Single
  end align 16;
  
  TDoubleSet = packed record
    X, Y: Double;
  end align 16;
  
function TransferTest(Input: TSingleSet): TDoubleSet; {$ifdef WIN64}vectorcall;{$endif} noinline;
begin
  Result.X := Input.X;
  Result.Y := Input.Y;
end;

var
  SS: TSingleSet;
  DS: TDoubleSet;
begin
  SS.X := 8.0;
  SS.Y := 4.0;
  SS.Z := 2.0;
  SS.W := 1.0;
  
  DS := TransferTest(SS);
  if (DS.X <> 8.0) or (DS.Y <> 4.0) then
    Halt(1);
  WriteLn('ok');
end.