Program csizes;

{ Demonstrates the various character sizes available. }

uses
    qdos,
    qscreen,
    qsuperbasic;

var
    width: Tchar_width;
    height: Tchar_height;

begin
    for width := WIDTH_6 to WIDTH_16 do
    begin
        for height := HEIGHT_10 to HEIGHT_20 do
	begin
	    write('Width: ', width, ', Height: ', height, ': ');
	    csize(StdOutputHandle, width, height);
	    writeln('Hello World!');
            csize(StdOutputHandle, WIDTH_6, HEIGHT_10);
	end;
    end;
end.

	
            
