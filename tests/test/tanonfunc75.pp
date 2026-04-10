{ anonymous function capturing field from with statement (bug #40600) }

program tanonfunc75;

{$mode objfpc}
{$modeswitch anonymousfunctions}
{$modeswitch functionreferences}

type
  TMyClass = class
    field: string;
    constructor Create;
  end;

  TRefProc = reference to procedure;

constructor TMyClass.Create;
begin
end;

procedure Run(p: TRefProc);
begin
  p;
end;

begin
  with TMyClass.Create do begin
    Run(procedure begin
      field := 'value';
    end);

    if field <> 'value' then
      Halt(1);
  end;
end.
