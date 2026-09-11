{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2026 by Norman Dunbar.

    The functions and procedures here match those supplied in
    Sinclair QL's SuperBASIC interpreter.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}


{ FUNCTIONS --------------------------------------------------------------}

function adate(aSeconds: longint): longint;
function date: longint;
//procedure sdate(aYear, aMonth, aDay, aHours, aMinutes, aSeconds: word);
function alchp(aLength: longword): pointer;
function alchp(aLength: longword; aSizeAllocated: pointer): pointer;
function dateStr(theDate: longword): string;
function open(aFilename: PAnsiChar): TChanid;
function open_in(aFilename: PAnsiChar): TChanid;
function open_over(aFilename: PAnsiChar): TChanid;
function open_new(aFilename: PAnsiChar): TChanid;
function open_dir(aFilename: PAnsiChar): TChanid;
function peek(aWhereFrom: PByte): Byte; inline;
function peek_l(aWhereFrom: PLongint): longint; inline;
function peek_w(aWhereFrom: PInteger): Integer; inline;
function respr(aLength: longword): pointer;
function upeek_l(aWhereFrom: PLongword): longword; inline;
function upeek_w(aWhereFrom: PWord): word; inline;

{ PROCEDURES -------------------------------------------------------------}

procedure at(chan: Tchanid; aDown, aAcross: word);
procedure border(chan: Tchanid; aColour: Tql_colour; aWidth: word);
procedure close(chan: Tchanid);
procedure cls(chan: Tchanid; aPart: Tcls_part);
procedure csize(chan: Tchanid; aWidth: Tchar_width; aHeight: Tchar_height);
procedure curdis(chan: Tchanid);
procedure cursen(chan: Tchanid);
procedure cursor_down(chan: Tchanid);
procedure cursor_left(chan: Tchanid);
procedure cursor_new_line(chan: Tchanid);
procedure cursor_next_line(chan: Tchanid);
procedure cursor_right(chan: Tchanid);
procedure cursor_up(chan: Tchanid);
procedure flash(chan: Tchanid; aState: Tflash_mode);
procedure ink(chan: Tchanid; aColour: Tql_colour);
//procedure mode(var aMode: Tql_screen_mode; var aDevice: Tql_device_mode);
procedure mode(aMode: Tql_screen_mode; aDevice: Tql_device_mode);
procedure over(chan: Tchanid; aMode: Tover_mode);
procedure pan(chan: Tchanid; aPart: Tpan_part; aCount: smallint);
procedure paper(chan: Tchanid; aColour: Tql_colour);
procedure poke(aWhereTo: PByte; aValue: Byte); inline;
procedure poke_l(aWhereTo: PLongint; aValue: longint); inline;
procedure poke_w(aWhereTo: PInteger; aValue: Integer); inline;
procedure rechp(aAddress: pointer);
procedure scroll(chan: Tchanid; aPart: Tscroll_part; aCount: smallint);
procedure strip(chan: Tchanid; aColour: Tql_colour);
procedure tab(chan: Tchanid; aColumn: word);
procedure under(chan: Tchanid; aState: Tunder_mode);
procedure window(chan: Tchanid; aWidth, aHeight, aXPos, aYPos: word);
procedure window(chan: Tchanid; aWidth, aHeight, aXPos, aYPos: word; bColour: Tql_colour; bWidth: word);

