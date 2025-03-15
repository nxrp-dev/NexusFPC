{$Mode ObjFpc}

type
  TTestRec = record
    A: TGUID;
  end;

var
  arr: array[0..3] of TTestRec = [
    0..3: (A:'{C5155EB1-724D-4CC2-B4A9-35FC91B5E608}')
  ];

var
  g: TGuid='{C5155EB1-724D-4CC2-B4A9-35FC91B5E608}';
begin
  if arr[0].A<>g then
    halt(1);
  if arr[1].A<>g then
    halt(2);
  if arr[2].A<>g then
    halt(3);
  if arr[3].A<>g then
    halt(4);
  WriteLn('Ok');
end.
