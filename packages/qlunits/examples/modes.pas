Program modes;

{ Demonstrates the two screen modes available. }

uses
    qdos,
    qscreen,
    qsuperbasic;


var
    thisMode: Tql_screen_mode;
    thisDevice: Tql_device_mode;
    ok: string[2];

begin
    {Monitor mode 4.}
    thisDevice := MODE_MONITOR;
    thisMode := MODE_4;
    mode(thisMode, thisDevice);
    writeln('Current mode is: ', thisDevice, '-', thisMode);
    write('Press ENTER to change to another mode...');
    readln(ok);

    {PAL TV mode 8.}
    thisDevice := MODE_TV_PAL;
    thisMode := MODE_8;
    mode(thisMode, thisDevice);
    writeln('Current mode is: ', thisDevice, '-', thisMode);
end.

	
            
