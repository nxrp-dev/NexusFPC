{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2026 by Norman Dunbar.

    QDOS low level functions used by the Sinclair QL to perform
    operations affecting memory.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

 {Memory functions for the Sinclair QL.}

unit qmemory;

interface

uses
  qdos;


function mt_alres(aLength: longword): pointer;
function mt_reres: longword;

{function mt_alloc(aLength: longword; aHeadPointer: pointer; aLengthGot: plongword): pointer;}
{procedure mt_lnkfr(aLength: longword; aHeadPointer: pointer; aBaseAddress: longword);}

{ Probably best avoided from Pascal!}
{function mt_albas(size: longword; sizegot: plongword; jobid: Tjobid): pointer;}
{function mt_rebas(size: longword; sizegot: plongword; jobid: Tjobid): pointer;}


implementation

const
  _MT_ALLOC  = $0C;
  _MT_LNKFR  = $0D;
  _MT_ALRES  = $0E;   { TODO}
  _MT_RERES  = $0F;   { TODO}
  _MT_ALBAS = $16;    { Probably best avoided from Pascal!}
  _MT_REBAS = $17;    { Probably best avoided from Pascal!}


{Allocate space in the resident procedure area, if empty. Returns start address or negative error code.}
function mt_alres(aLength: longword): pointer; assembler; nostackframe; public name '_mt_alres';
asm
  movem.l d2-d3/a2-a3,-(sp)
  move.l aLength,d1
  moveq.l #_MT_ALRES,d0
  trap #1
  tst.l d0
  bne @quit     { Return error code.}
  move.l a0,d0  { Return start address.}
@quit:
  movem.l (sp)+,d2-d3/a2-a3
end;


{ Attempts to collapse the entire resident procedure area. Might crash early systems!
  this trap is DANGEROUS to use, and best avoided.}
function mt_reres: longword; assembler; nostackframe; public name '_mt_reres';
asm
  movem.l d2-d3/a2-a3,-(sp)
  moveq.l #_MT_RERES,d0
  trap #1
  movem.l (sp)+,d2-d3/a2-a3
end;


end.
