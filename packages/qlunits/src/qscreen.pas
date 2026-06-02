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

 {Screen functions for the Sinclair QL.}

unit qscreen;

interface

uses
  qdos;

{$i superbasictypes.inc}

{$i screenfuncs.inc}


implementation

const
  _SD_EXTOP = $09;
  _SD_PXENQ = $0A;
  _SD_CHENQ = $0B;
  _SD_BORDR = $0C;
  _SD_CURE  = $0E;
  _SD_CURS  = $0F;
  _SD_POS   = $10;
  _SD_TAB   = $11;
  _SD_NL    = $12;
  _SD_PCOL  = $13;
  _SD_NCOL  = $14;
  _SD_PROW  = $15;
  _SD_NROW  = $16;
  _SD_PIXP  = $17;
  _SD_SCROL = $18;
  _SD_SCRTP = $19;
  _SD_SCRBT = $1A;
  _SD_PAN   = $1B;
  _SD_PANLN = $1E;
  _SD_PANRT = $1F;
  _SD_CLRTP = $21;
  _SD_CLRBT = $22;
  _SD_CLRLN = $23;
  _SD_CLRRT = $24;
  _SD_FOUNT = $25;
  _SD_RECOL = $26;
  _SD_SETPA = $27;
  _SD_SETST = $28;
  _SD_SETIN = $29;
  _SD_SETFL = $2A;
  _SD_SETUL = $2B;
  _SD_SETMD = $2C;
  _SD_SETSZ = $2D;
  _SD_FILL  = $2E;
  _SD_DONL  = $2F;
  _SD_POINT = $30;
  _SD_LINE  = $31;
  _SD_ARC   = $32;
  _SD_ELIPS = $33;
  _SD_SCALE = $34;
  _SD_FLOOD = $35;
  _SD_GCUR  = $36;


function sd_bordr(chan: Tchanid; aColour: Tql_colour; aWidth: word; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_bordr';
asm
  movem.l d2-d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aColour,d1
  move.w aWidth,d2
  moveq.l #_SD_BORDR,d0
  trap #3
  movem.l (sp)+,d2-d3
end;

function sd_cure(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_cure';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CURE,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_curs(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_curs';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CURS,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_pos(chan: Tchanid; aDown, aAcross: word; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_pos';
asm
  movem.l d2-d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aDown,d2
  move.w aAcross,d1
  moveq.l #_SD_POS,d0
  trap #3
  movem.l (sp)+,d2-d3
end;

function sd_tab(chan: Tchanid; aColumn: word; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_tab';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aColumn,d1
  moveq.l #_SD_TAB,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_nl(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_nl';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_NL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_pcol(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_pcol';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_PCOL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_ncol(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_ncol';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_NCOL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_prow(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_prow';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_PROW,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_nrow(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_nrow';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_NROW,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_pixp(chan: Tchanid; aRow, aColumn: word; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_pixp';
asm
  movem.l d2-d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aRow,d1
  move.w aColumn,d2
  moveq.l #_SD_PIXP,d0
  trap #3
  movem.l (sp)+,d2-d3
end;

function sd_clrtp(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_clrtp';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CLRTP,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_clrbt(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_clrbt';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CLRBT,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_clrln(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_clrln';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CLRLN,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_clrrt(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_clrrt';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_CLRRT,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_scrol(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_scrol';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_SCROL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_scrtp(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_scrtp';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_SCRTP,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_scrbt(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_scrbt';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_SCRBT,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_pan(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_pan';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_PAN,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_panln(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_panln';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_PANLN,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_panrt(chan: Tchanid; aCount: smallint; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_panrt';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aCount,d1
  moveq.l #_SD_PANRT,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setpa(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setpa';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.b aColour,d1
  moveq.l #_SD_SETPA,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setst(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setst';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.b aColour,d1
  moveq.l #_SD_SETST,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setin(chan: Tchanid; aColour: Tql_colour; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setin';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.b aColour,d1
  moveq.l #_SD_SETIN,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setfl(chan: Tchanid; aState: Tflash_mode; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setfl';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.b aState,d1
  moveq.l #_SD_SETFL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setul(chan: Tchanid; aState: Tunder_mode; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setul';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.b aState,d1
  moveq.l #_SD_SETUL,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setmd(chan: Tchanid; aMode: Tover_mode; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_setmd';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aMode,d1
  moveq.l #_SD_SETMD,d0
  trap #3
  move.l (sp)+,d3
end;

function sd_setsz(chan: Tchanid; aWidth: Tchar_width; aHeight: Tchar_height; timeout: Ttimeout): longint; assembler; public name '_sd_setsz';
asm
  movem.l d2-d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  move.w aWidth,d1
  move.w aHeight,d2
  moveq.l #_SD_SETSZ,d0
  trap #3
  movem.l (sp)+,d2-d3
end;

function sd_donl(chan: Tchanid; timeout: Ttimeout): longint; assembler; nostackframe; public name '_sd_donl';
asm
  move.l d3,-(sp)
  move.w timeout,d3
  move.l chan,a0
  moveq.l #_SD_DONL,d0
  trap #3
  move.l (sp)+,d3
end;



end.
