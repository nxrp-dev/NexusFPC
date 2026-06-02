Program strips;

{ Demonstrates the various strip colours available. }

uses
    qdos,
    qscreen,
    qsuperbasic;


var
    thisMode: Tql_screen_mode;
    thisDevice: Tql_device_mode;

procedure doStrips;
var
    thisStrip: Tql_colour;
    ok: string[2];
begin
    paper(StdOutputHandle, QL_BLACK);

    for thisStrip := QL_BLACK to QL_WHITE do
    begin
        if thisStrip > QL_MAGENTA then
	    ink(StdOutputHandle, QL_BLACK)
        else
	    ink(StdOutputHandle, QL_WHITE);

        strip(StdOutputHandle, thisStrip);
	cls(StdOutputHandle, CLS_ALL);
	writeln('Screen mode: ', thisMode);
	writeln('Strip colour: ', thisStrip);
	writeln(#10,#10,'Press ENTER for next strip colour...');
	readln(ok);
    end;
end;


begin
    thisDevice := MODE_TV_PAL;

    thisMode := MODE_8;
    mode(thisMode, thisDevice);
    doStrips;

    thisMode := MODE_4;
    mode(thisMode, thisDevice);
    doStrips;
end.

	
            
