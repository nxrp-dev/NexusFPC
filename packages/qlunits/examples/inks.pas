Program inks;

{ Demonstrates the various ink colours available. }

uses
    qdos,
    qscreen,
    qsuperbasic;


var
    thisMode: Tql_screen_mode;
    thisDevice: Tql_device_mode;

procedure doInks;
var
    thisInk: Tql_colour;
    ok: string[2];
begin
    paper(StdOutputHandle, QL_BLACK);
    strip(StdOutputHandle, QL_WHITE);

    for thisInk := QL_BLACK to QL_WHITE do
    begin
        if thisInk >= QL_YELLOW then
	    strip(StdOutputHandle, QL_BLACK);

        ink(StdOutputHandle, thisInk);
	cls(StdOutputHandle, CLS_ALL);
	writeln('Screen mode: ', thisMode);
	writeln('Ink colour: ', thisInk);
	writeln(#10,#10,'Press ENTER for next ink colour...');
	readln(ok);
    end;
end;


begin
    thisDevice := MODE_TV_PAL;

    thisMode := MODE_8;
    mode(thisMode, thisDevice);
    doInks;

    thisMode := MODE_4;
    mode(thisMode, thisDevice);
    doInks;
end.

	
            
