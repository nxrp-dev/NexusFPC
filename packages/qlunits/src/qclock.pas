{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2026 by Norman Dunbar.

    QDOS low level functions used by the Sinclair QL to perform
    operations affecting the clock.

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

 {Clock functions for the Sinclair QL.}

unit qclock;

interface

uses
  qdos;


{mt_rclck is not required here. Part of System unit.}

{Set the clock.}
procedure mt_sclck(seconds: longint);

{Adjust the clock. Returns the new time in seconds.}
function mt_aclck(seconds: longint): longint;



implementation

const
  _MT_SCLCK = $14;
  _MT_ACLCK = $15;

procedure mt_sclck(seconds: longint); assembler; nostackframe; public name '_mt_sclck';
asm
  movem.l d2-d3,-(sp)
  move.l seconds, d0
  moveq.l #_MT_SCLCK,d0
  trap #1
  movem.l (sp)+,d2-d3
end;

function mt_aclck(seconds: longint): longint; assembler; nostackframe; public name '_mt_aclck';
asm
  movem.l d2-d3,-(sp)
  move.l seconds, d0
  moveq.l #_MT_ACLCK,d0
  trap #1
  move.l d1,d0
  movem.l (sp)+,d2-d3
end;


end.
