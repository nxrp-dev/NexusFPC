program tcpstr14;
{$apptype console}
{$mode delphi}{$H+}

type
  t866 = type AnsiString(866);
var
  s866: t866;
begin
  Str(123, s866);
  if StringCodePage(s866) <> 866 then
    begin
      WriteLn('FAILED: Expected 866 but got ', StringCodePage(s866));
      halt(1);
    end;
  WriteLn('ok');
end.
