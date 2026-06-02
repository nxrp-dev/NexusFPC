{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2026 by Norman Dunbar.

    QDOS low level functions used by the Sinclair QL to perform
    operations affecting the display.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{ Display functions for the Sinclair QL.}

{Set border colour and width.}
function sd_bordr(chan: Tchanid; aColour: Tql_colour; aWidth: word; timeout: Ttimeout): longint; 

{Enable cursor.}
function sd_cure(chan: Tchanid; timeout: Ttimeout): longint; 

{Suppress cursor.}
function sd_curs(chan: Tchanid; timeout: Ttimeout): longint; 

{Position cursor on screen.}
function sd_pos(chan: Tchanid; aDown, aAcross: word; timeout: Ttimeout): longint; 

{Tab cursor on current line.}
function sd_tab(chan: Tchanid; aColumn: word; timeout: Ttimeout): longint; 

{Move to a new line.}
function sd_nl(chan: Tchanid; timeout: Ttimeout): longint; 

{Cursor left.}
function sd_pcol(chan: Tchanid; timeout: Ttimeout): longint; 

{Cursor right.}
function sd_ncol(chan: Tchanid; timeout: Ttimeout): longint; 

{Cursor up.}
function sd_prow(chan: Tchanid; timeout: Ttimeout): longint; 

{Cursor down.}
function sd_nrow(chan: Tchanid; timeout: Ttimeout): longint; 

{Clear top of screen.}
function sd_clrtp(chan: Tchanid; timeout: Ttimeout): longint; 

{Clear bottom of screen.}
function sd_clrbt(chan: Tchanid; timeout: Ttimeout): longint; 

{Clear all of the current line.}
function sd_clrln(chan: Tchanid; timeout: Ttimeout): longint; 

{Clear right of current line, from cursor position.}
function sd_clrrt(chan: Tchanid; timeout: Ttimeout): longint; 

{Scroll entire window.}
function sd_scrol(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; 

{Scroll top of window.}
function sd_scrtp(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; 

{Scroll bottom of window.}
function sd_scrbt(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint;

{Pan entire window.}
function sd_pan(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; 

{Pan cursor line.}
function sd_panln(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; 

{Pan right of cursor line.}
function sd_panrt(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; 

{Set paper colour.}
function sd_setpa(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; 

{Set strip colour.}
function sd_setst(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; 

{Set ink colour.}
function sd_setin(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; 

{Set Flash on/off.}
function sd_setfl(chan: Tchanid; aState: Tflash_mode; timeout: Ttimeout): longint; 

{Set underline on/off.}
function sd_setul(chan: Tchanid; aState: Tunder_mode; timeout: Ttimeout): longint; 

{Set screen write mode.}
function sd_setmd(chan: Tchanid; aMode: Tover_mode; timeout: Ttimeout): longint; 

{Set character height and width.}
function sd_setsz(chan: Tchanid; aWidth: Tchar_width; aHeight: Tchar_height; timeout: Ttimeout): longint; 

{Do pending newline.}
function sd_donl(chan: Tchanid; timeout: Ttimeout): longint; 

