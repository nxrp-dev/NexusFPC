{$Mode ObjFPC}{$H+}
{$ModeSwitch RecordUnpack}

type
  TIntArray = array[0..1] of integer;

function GetValue: TIntArray;
const
  i: integer = 0;
begin
  inc(i);
  result[0]:=i;
  result[1]:=i+1;
end;

var
  i,j: Integer;
begin
  (i, j) := ...GetValue;
  WriteLn(i, ' ', j);
  if i<>1 then
    Halt(1);
  if j<>2 then
    Halt(2);
  WriteLn('ok');
end.
