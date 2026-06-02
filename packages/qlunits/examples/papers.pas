Program papers;

{ Demonstrates the various paper colours available. }

uses
    qdos,
    qscreen,
    qsuperbasic;


var
    thisMode: Tql_screen_mode;
    thisDevice: Tql_device_mode;

procedure doPapers;
var
    thisPaper: Tql_colour;
    ok: string[2];
begin
    for thisPaper := QL_BLACK to QL_WHITE do
    begin
        if thisPaper > QL_MAGENTA then
	    ink(StdOutputHandle, QL_BLACK)
        else
	    ink(StdOutputHandle, QL_WHITE);

        paper(StdOutputHandle, thisPaper);
	cls(StdOutputHandle, CLS_ALL);
	writeln('Screen mode: ', thisMode);
	writeln('Paper colour: ', thisPaper);
	writeln(#10,#10,'Press ENTER for next paper colour...');
	readln(ok);
    end;
end;


begin
    thisDevice := MODE_TV_PAL;

    thisMode := MODE_8;
    mode(thisMode, thisDevice);
    doPapers;

    thisMode := MODE_4;
    mode(thisMode, thisDevice);
    doPapers;
end.

	
            
