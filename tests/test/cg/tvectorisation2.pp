{ %OPT=-O2 -MOBJFPC -Sv }

program tvectorisation2;

type
  TSingleSet = packed record
    X, Y, Z, W: Single
  end align 16;
  
  TDoubleSet = packed record
    X, Y: Double;
  end align 16;
  
function TransferTest(Input: TDoubleSet): TSingleSet; {$ifdef WIN64}vectorcall;{$endif} noinline;
begin
  Result.X := Input.X;
  Result.Y := Input.Y;
  Result.Z := 2.0;
  Result.W := 1.0;
end;

var
  SS: TSingleSet;
  DS: TDoubleSet;
begin
  DS.X := 8.0;
  DS.Y := 4.0;
  
  SS := TransferTest(DS);
  if (SS.X <> 8.0) or (SS.Y <> 4.0) or (SS.Z <> 2.0) or (SS.W <> 1.0) then
    Halt(1);
  WriteLn('ok');
end.