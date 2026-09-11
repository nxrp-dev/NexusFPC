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

unit qsuperbasic;

interface

uses 
  qdos,
  qscreen,
  qclock,
  qmemory;

const
  TIMEOUT = -1;

{$i superbasicfuncs.inc}


implementation


procedure border(chan: Tchanid; aColour: Tql_colour; aWidth: word);
  begin
    sd_bordr(chan, aColour, aWidth, TIMEOUT);
  end;

procedure cursen(chan: Tchanid);
  begin
    sd_cure(chan, TIMEOUT);
  end;

procedure curdis(chan: Tchanid);
  begin
    sd_curs(chan, TIMEOUT);
  end;

procedure at(chan: Tchanid; aDown, aAcross: word);
  begin
    sd_pos(chan, aDown, aAcross, TIMEOUT);
  end;

procedure tab(chan: Tchanid; aColumn: word);
  begin
    sd_tab(chan, aColumn, TIMEOUT);
  end;

procedure paper(chan: Tchanid; aColour: Tql_colour);
  begin
    sd_setpa(chan, aColour, TIMEOUT);
    sd_setst(chan, aColour, TIMEOUT);
  end;

procedure strip(chan: Tchanid; aColour: Tql_colour);
  begin
    sd_setst(chan, aColour, TIMEOUT);
  end;

procedure ink(chan: Tchanid; aColour: Tql_colour);
  begin
    sd_setin(chan, aColour, TIMEOUT);
  end;

procedure under(chan: Tchanid; aState: Tunder_mode);
  begin
    sd_setul(chan, aState, TIMEOUT);
  end;

procedure flash(chan: Tchanid; aState: Tflash_mode);
  begin
    sd_setfl(chan, aState, TIMEOUT);
  end;

procedure csize(chan: Tchanid; aWidth: Tchar_width; aHeight: Tchar_height);
  begin
    sd_setsz(chan, aWidth, aHeight, TIMEOUT);
  end;

procedure over(chan: Tchanid; aMode: Tover_mode);
  begin
    sd_setmd(chan, aMode, TIMEOUT);
  end;

procedure cls(chan: Tchanid; aPart: Tcls_part);
  begin
    Case aPart of  
      CLS_ALL: sd_clear(chan, TIMEOUT);
      CLS_TOP: sd_clrtp(chan, TIMEOUT);
      CLS_BOTTOM: sd_clrbt(chan, TIMEOUT);
      CLS_LINE: sd_clrln(chan, TIMEOUT);
      CLS_RIGHT: sd_clrrt(chan, TIMEOUT);
    else
      {Supplied aPart is invalid, just clear the whole screen.}
      sd_clear(chan, TIMEOUT);
    end; 
  end;

procedure pan(chan: Tchanid; aPart: Tpan_part; aCount: smallint);
  begin
    Case aPart of  
      PAN_ALL: sd_pan(chan, aCount, TIMEOUT);
      PAN_LINE: sd_panln(chan, aCount, TIMEOUT);
      PAN_RIGHT: sd_panrt(chan, aCount, TIMEOUT);
    end; 
  end;

procedure scroll(chan: Tchanid; aPart: Tscroll_part; aCount: smallint);
  begin
    Case aPart of  
      SCROLL_ALL: sd_scrol(chan, aCount, TIMEOUT);
      SCROLL_TOP: sd_scrtp(chan, aCount, TIMEOUT);
      SCROLL_BOTTOM: sd_scrbt(chan, aCount, TIMEOUT);
    end; 
  end;

procedure mode(aMode: Tql_screen_mode; aDevice: Tql_device_mode);
  var
    theMode: Tql_screen_mode;
    theDevice: Tql_device_mode;

  begin
    theMode := aMode;
    theDevice := aDevice;
    mt_dmode(@theMode, @theDevice);
  end;

procedure cursor_new_line(chan: Tchanid);
  begin
    sd_nl(chan, TIMEOUT);
  end;

procedure cursor_up(chan: Tchanid);
  begin
    sd_prow(chan, TIMEOUT);
  end;

procedure cursor_down(chan: Tchanid);
  begin
    sd_nrow(chan, TIMEOUT);
  end;

procedure cursor_left(chan: Tchanid);
  begin
    sd_pcol(chan, TIMEOUT);
  end;

procedure cursor_right(chan: Tchanid);
  begin
    sd_ncol(chan, TIMEOUT);
  end;

procedure cursor_next_line(chan: Tchanid);
  begin
    sd_nl(chan, TIMEOUT);
  end;


(* ------------------------------------------------------------
           TO BE CONTINUED --- NOT YET CORRECT! 
   ------------------------------------------------------------
procedure sdate(year, month, day, hours, minutes, seconds: word);

  const
    secondsPerDay = 24*60*60;
    secondsPerHour = 60*60;
    secondsPerMinute = 60;

  var
    theDays: longint;
    theSeconds: longint;
    leapYear: boolean;
    theYear: word;
    runningDays: array [1..12] of word = (
        0, 31,   59,  90, 123, 151, 
      181, 212, 243, 273, 304, 334);

  begin
    { SMSQ has vector $00D6 to convert params to seconds.
      QDOS doesn't, so here's the manual version.}

      {Is this a leap year? }
      leapYear := (year mod 4) = 0;

      {The QL doesn't cater for century years, but I will!}
      if year mod 100 = 0 then 
        leapYear := leapYear and ((year mod 400) = 0);

      { QL years start in 1961. If the year parameter is 
        prior to 1961, results will be undefined.}
      theYear := year - 1961;

      { Convert to days and add a leap day if the year is leap
        and the month is March onwards.}
      theDays := theYear * 365;
      if leapYear and (month > 2) then
        theDays += 1;

      { Add in running days for the current month.}
      theDays += runningDays[month];

      {Add current day of month.}
      theDays += day;

      {Convert to seconds.}
      theSeconds := (theDays * secondsPerDay) +
                    (hours * secondsPerHour)  +
                    (minutes * secondsPerMinute) +
                    seconds;

      {Finally, set the clock.}
      mt_sclck(theSeconds);
  end;
  ------------------------------------------------------------ *)


function date: longint;
  begin
    date := mt_rclck;
  end;

function adate(aSeconds: longint): longint;
  begin
    adate := mt_aclck(aSeconds);
  end;

{Convert a longword to a dae string.}
function dateStr(theDate: longword): string;
  begin
  end;

{Attempt to allocate resident procedure space.}
function respr(aLength: longword): pointer;
  begin
    respr := mt_alres(aLength);
  end;

{ Allocate common heap space.}
function alchp(aLength: longword): pointer;
  begin
    alchp := mt_alchp(aLength, nil, -1);
  end;

{ Allocate common heap space and return size allocated.}
function alchp(aLength: longword; aSizeAllocated: Pointer): pointer;
  begin
    alchp := mt_alchp(aLength, aSizeAllocated, -1);
  end;

{ Return common heap space.}
procedure rechp(aAddress: pointer);
  begin
    mt_rechp(aAddress);
  end;


procedure poke_l(aWhereTo: PLongint; aValue: longint); inline;
   begin
      aWhereTo^ := aValue;
   end;

function peek_l(aWhereFrom: PLongint): longint; inline;
   begin
      peek_l := aWhereFrom^;
   end;

function upeek_l(aWhereFrom: PLongword): longword; inline;
   begin
      upeek_l := aWhereFrom^;
   end;

procedure poke_w(aWhereTo: PInteger; aValue: Integer); inline;
   begin
      aWhereTo^ := aValue;
   end;

function peek_w(aWhereFrom: PInteger): Integer; inline;
   begin
      peek_w := aWhereFrom^;
   end;

function upeek_w(aWhereFrom: PWord): Word; inline;
   begin
      upeek_w := aWhereFrom^;
   end;

procedure poke(aWhereTo: PByte; aValue: Byte); inline;
   begin
      aWhereTo^ := aValue;
   end;

function peek(aWhereFrom: PByte): Byte; inline;
   begin
      peek := aWhereFrom^;
   end;

{ Private function to do any open type.}
function openPrivate(aFilename: PAnsiChar; aMode: longint): TChanid;
  begin
    openPrivate := io_open(aFilename, aMode);
  end;


{ -----------------------------------------------------------------------------
  These file handling functions CANNOT be used with Pascal's "write" and "read" 
  functions like writeln, readln etc.
  -----------------------------------------------------------------------------}
function open(aFilename: PAnsiChar): TChanid;
  begin
    open := openPrivate(aFilename, Q_OPEN);
  end;

function open_in(aFilename: PAnsiChar): TChanid;
  begin
    open_in := openPrivate(aFilename, Q_OPEN_IN);
  end;

function open_over(aFilename: PAnsiChar): TChanid;
  begin
    open_over := openPrivate(aFilename, Q_OPEN_OVER);
  end;

function open_new(aFilename: PAnsiChar): TChanid;
  begin
    open_new := openPrivate(aFilename, Q_OPEN_NEW);
  end;

function open_dir(aFilename: PAnsiChar): TChanid;
  begin
    open_dir := openPrivate(aFilename, Q_OPEN_DIR);
  end;


{ -----------------------------------------------------------------------------
  The SuperBASIC close function cannot have that name in Pascal as CLOSE is a
  Pascal reserved word. The closeFile procedure must be used to close files 
  opened using any of the SuperBASIC open functions above. 
  -----------------------------------------------------------------------------}
procedure close(chan: Tchanid);
  begin
    io_close(chan);
  end;

{ Internal helper for the Window procedures.}
procedure doWindow(chan: Tchanid; aColour: Tql_colour; aWidth: word; window: PQLRect);
  begin
    sd_wdef(chan, TIMEOUT, Byte(aColour), aWidth, window);
  end;


procedure window(chan: Tchanid; aWidth, aHeight, aXPos, aYPos: word);
  var
    window: PQLRect;

  begin
    with window^ do
    begin
      q_width := aWidth;
      q_height := aHeight;
      q_x := aXPos;
      q_y := aYPos;
    end;

    doWindow(chan, Tql_colour(0), 0, window);
  end;

procedure window(chan: Tchanid; aWidth, aHeight, aXPos, aYPos: word; bColour: Tql_colour; bWidth: word);
  var
    window: PQLRect;

  begin
    with window^ do
    begin
      q_width := aWidth;
      q_height := aHeight;
      q_x := aXPos;
      q_y := aYPos;
    end;

    doWindow(chan, bColour, bWidth, window);
  end;

end.
