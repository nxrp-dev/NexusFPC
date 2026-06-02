{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2020-2021 by Karoly Balogh

    Headers to QDOS OS functions used by the Sinclair QL RTL

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{Create a job. Returns new jobid in ?????????????????????????, error code is the result of the function.}
function mt_cjob(aOwnerJob: Tjobid; aCodeSpaceSize, aDataSPaceSize, aStartAddress: longword): longint; 

{ Get job information.}
function mt_jinf(aJobId: Tjobid; aTopJob: Tjobid): longint;

{Remove a job.}
function mt_rjob(aJobId: Tjobid; aErrorCode: longint): longint;

{Find maximum free space for a job.}
function mt_free: longint;

{Set exception table for a job.}
function mt_trapv(aJobId: Tjobid; aAddress: longword): longint;

{Suspend a job.}
function mt_susjb(aJobId: Tjobid; timeout: Ttimeout; aAddressToZero: longword): longint;

{Release a suspended job.}
function mt_reljb(aJobId: Tjobid): longint;

{Activate a job.}
function mt_activ(aJobId: Tjobid; aPriority: byte; timeout: Ttimeout): longint;

{Set a job's priority.}
function mt_prior(aJobId: Tjobid; aPriority: byte): longint;
