{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2026 by Norman Dunbar.

    QDOS low level functions used by the Sinclair QL to perform
    operations affecting job control.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

 {Job functions for the Sinclair QL.}

unit qjobs;

interface

uses
  qdos;


{$i jobsfuncs.inc}


implementation

const
  _MT_CJOB  = $01;
  _MT_JINF  = $02;
  _MT_RJOB  = $04;
  _MT_FREE  = $06;
  _MT_TRAPV = $07;
  _MT_SUSJB = $08;
  _MT_RELJB = $09;
  _MT_ACTIV = $0A;
  _MT_PRIOR = $0B;


{Create a job. Returns new jobid in ?????????????????????????, error code is the result of the function.}
{ Longword = unsigned 32 bit.
  Longint  = signed 32 bit. }
function mt_cjob(aOwnerJob: Tjobid; aCodeSpaceSize, aDataSPaceSize, aStartAddress: longword): longint; assembler; public name '_mt_cjob';
asm
  movem.l d2-d3/d7,-(sp)
  move.l aCodeSpaceSize,d2    {This works.}
  move.l aDataSpaceSize,d3    {Always $002C1928 - BUG.}
  move.l aStartAddress,a1     {Always $00101694 - BUG.}
  move.l aOwnerJob,d1         {This works.}
  moveq.l #_MT_CJOB,d0
  trap #1
  movem.l (sp)+,d2-d3/d7
end;

{ Get job information. TODO:}
function mt_jinf(aJobId: Tjobid; aTopJob: Tjobid): longint; assembler; nostackframe; public name '_mt_jinf';
asm

end;

{Remove a job.}
function mt_rjob(aJobId: Tjobid; aErrorCode: longint): longint; assembler; nostackframe; public name '_mt_rjob';
asm
  movem.l d2-d3/a2-a3,-(sp)
  move.l aErrorCode,d3 
  move.l aJobid,d1
  moveq.l #_MT_RJOB,d0
  trap #1
  move.l d1,d0
  movem.l (sp)+,d2-d3/a2-a3
end;

{Find maximum free space for a job.}
function mt_free: longint; assembler; nostackframe; public name '_mt_free';
asm
  movem.l d2-d3/a2-a3,-(sp)
  moveq.l #_MT_FREE,d0
  trap #1
  move.l d1,d0
  movem.l (sp)+,d2-d3/a2-a3
end;

{Set exception table for a job. TODO:}
function mt_trapv(aJobId: Tjobid; aAddress: longword): longint; assembler; nostackframe; public name '_mt_trapv';
asm
end;

{Suspend a job.}
function mt_susjb(aJobId: Tjobid; timeout: Ttimeout; aAddressToZero: longword): longint; assembler; public name '_mt_susjb';
asm
  move.w timeout,d3
  move.l aJobId,d1
  move.l aAddressToZero,a1
  moveq.l #_MT_SUSJB,d0
  trap #1 
end;

{Release a suspended job.}
function mt_reljb(aJobId: Tjobid): longint; assembler; nostackframe; public name '_mt_reljb';
asm
  move.l aJobId,d1
  moveq.l #_MT_RELJB,d0
  trap #1
end;

{Activate a job.}

function mt_activ(aJobId: Tjobid; aPriority: byte; timeout: Ttimeout): longint; assembler; public name '_mt_activ';
asm
  movem.l d2-d3/a3,-(sp)
  move.b aPriority,d2 
  andi.b #$7F,d2          {0--127 only}
  move.w timeout,d3
  move.l aJobId,d1
  moveq.l #_MT_ACTIV,d0
  trap #1 
  movem.l (sp)+,d2-d3/a3
end;

{Set a job's priority.}
function mt_prior(aJobId: Tjobid; aPriority: byte): longint; assembler; nostackframe; public name '_mt_prior';
asm
  move.b aPriority,d2 
  andi.b #$7F,d2          {0--127 only}
  move.l aJobId,d1
  moveq.l #_MT_PRIOR,d0
  trap #1 
end;


end.
