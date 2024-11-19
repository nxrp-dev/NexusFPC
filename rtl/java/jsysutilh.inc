{%MainUnit sysutils.pp}
{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by Florian Klaempfl
    member of the Free Pascal development team

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
{$MACRO ON}
{$IFNDEF FPC_DOTTEDUNITS}
{$DEFINE SUT:=sysutils}
{$DEFINE BU:=baseunix}
{$ELSE}
{$DEFINE SUT:=System.SysUtils}
{$DEFINE BU:=UnixApi.Base}
{$ENDIF}

{ Using inlining for small system functions/wrappers }
{$inline on}
{$define SYSUTILSINLINE}

function GetTickCount: LongWord; deprecated 'Use GetTickCount64 instead';
function GetTickCount64: QWord;

type
   { some helpful data types }

   THandle = System.THandle;

   TProcedure = procedure;

   TFileName = type string;

   TIntegerSet = Set of 0..SizeOf(Integer)*8-1;

   LongRec = packed record
      case Integer of
{$ifdef FPC_LITTLE_ENDIAN}
        0 : (Lo,Hi : Word);
{$else FPC_LITTLE_ENDIAN}
        0 : (Hi,Lo : Word);
{$endif FPC_LITTLE_ENDIAN}
        1 : (Bytes : Array[0..3] of Byte);
   end;

   WordRec = packed record
{$ifdef FPC_LITTLE_ENDIAN}
     Lo,Hi : Byte;
{$else FPC_LITTLE_ENDIAN}
     Hi,Lo : Byte;
{$endif FPC_LITTLE_ENDIAN}
   end;

   Int64Rec = packed record
      case integer of
{$ifdef FPC_LITTLE_ENDIAN}
        0 : (Lo,Hi : Cardinal);
{$else FPC_LITTLE_ENDIAN}
        0 : (Hi,Lo : Cardinal);
{$endif FPC_LITTLE_ENDIAN}
        1 : (Words : Array[0..3] of Word);
        2 : (Bytes : Array[0..7] of Byte);
   end;

   OWordRec = packed record
      case integer of
{$ifdef FPC_LITTLE_ENDIAN}
        0 : (Lo,Hi : QWord);
{$else FPC_LITTLE_ENDIAN}
        0 : (Hi,Lo : QWord);
{$endif FPC_LITTLE_ENDIAN}
        1 : (DWords : Array[0..3] of DWord);
        2 : (Words : Array[0..7] of Word);
        3 : (Bytes : Array[0..15] of Byte);
   end;

   PByteArray = ^TByteArray;
   TByteArray = Array[0..{$ifdef CPU16}32766{$else}32767{$endif}] of Byte;

   PWordarray = ^TWordArray;
   TWordArray = array[0..{$ifdef CPU16}16382{$else}16383{$endif}] of Word;

   TBytes = array of Byte;

   { exceptions }
   Exception = class(TObject)
    private
      fmessage : string;
      fhelpcontext : longint;
    public
      constructor Create(const msg : string);
      constructor CreateFmt(const msg : string; const args : array of const);
      constructor CreateHelp(const Msg: string; AHelpContext: Longint);
      constructor CreateFmtHelp(const Msg: string; const Args: array of const;
        AHelpContext: Longint);
      Function ToString : RTLString; override;

      function GetBaseException : Exception;virtual;

      property HelpContext : longint read fhelpcontext write fhelpcontext;
      property Message : string read fmessage write fmessage;
   end;

   ExceptClass = class of Exception;

   EExternal = class(Exception);

   { integer math exceptions }
   EIntError    = Class(EExternal);
   EDivByZero   = Class(EIntError);
   ERangeError  = Class(EIntError);
   EIntOverflow = Class(EIntError);

   { General math errors }
   EMathError  = Class(EExternal);
   EInvalidOp  = Class(EMathError);
   EZeroDivide = Class(EMathError);
   EOverflow   = Class(EMathError);
   EUnderflow  = Class(EMathError);

   { Run-time and I/O Errors }
   EInOutError = class(Exception)
     public
       ErrorCode : Integer;
   end;

   EHeapMemoryError = class(Exception)
     protected
       AllowFree : boolean;
   end;

   EHeapException = EHeapMemoryError;

   EExternalException = class(EExternal);
   EInvalidPointer  = Class(EHeapMemoryError);
   EOutOfMemory     = Class(EHeapMemoryError);
   EInvalidCast = Class(Exception);
   EVariantError = Class(Exception)
     ErrCode : longint;
   end;

   EAccessViolation = Class(EExternal);
   EBusError = Class(EAccessViolation);
   EPrivilege = class(EExternal);
   EStackOverflow = class(EExternal);
   EControlC = class(EExternal);

   { String conversion errors }
   EConvertError = class(Exception);
   EFormatError = class(Exception);

   { Other errors }
   EAbort           = Class(Exception);
   EAbstractError   = Class(Exception);
   EAssertionFailed = Class(Exception);
   EObjectCheck     = Class(Exception);
   EThreadError     = Class(Exception);
   ESigQuit         = Class(Exception);

   EPropReadOnly = class(Exception);
   EPropWriteOnly = class(Exception);

   EIntfCastError = class(Exception);
   EInvalidContainer = class(Exception);
   EInvalidInsert = class(Exception);

   EPackageError = class(Exception);
   ECFError = class(Exception);

   EOSError = class(Exception)
   public
     ErrorCode: Longint;
   end;

   ESafecallException = class(Exception);
   ENoThreadSupport = Class(Exception);
   ENoWideStringSupport = Class(Exception);
   ENoDynLibsSupport = class(Exception);

   EProgrammerNotFound = class(Exception);

   EMonitor = class(Exception);
   EMonitorLockException = class(EMonitor);
   ENoMonitorSupportException = class(EMonitor);

   EObjectDisposed = class(Exception);

   ENotImplemented = class(Exception);

   EArgumentException = class(Exception);
   EArgumentOutOfRangeException = class(EArgumentException);
   EArgumentNilException = class(EArgumentException);

   EPathTooLongException = class(Exception);
   ENotSupportedException = class(Exception);
   EDirectoryNotFoundException = class(Exception);
   EFileNotFoundException = class(Exception);
   EPathNotFoundException = class(Exception);

   EInOutArgumentException = class(EArgumentException)
   public
     Path: string;
   end;

   EInvalidOpException = class(Exception);

   ENoConstructException = class(Exception);
   EListError = Class(Exception);

   EOperationCancelled = class(Exception);

type
   TOnShowException = Procedure (Msg : ShortString);

Var
   OnShowException : TOnShowException;

{ some packages and unit related constants for compatibility }

const
  pfExeModule = $00000000;
  pfNeverBuild = $00000001;
  pfDesignOnly = $00000002;
  pfRunOnly = $00000004;
  pfIgnoreDupUnits = $00000008;
  pfPackageModule = $40000000;
  pfModuleTypeMask = $C0000000;
  pfV3Produced =  $00000000;
  pfProducerUndefined = $04000000;
  pfBCB4Produced = $08000000;
  pfDelphi4Produced = $0C000000;
  pfLibraryModule = $80000000;
  pfProducerMask = $0C000000;

const
  ufMainUnit     = $01;
  ufPackageUnit  = $02;
  ufWeakUnit     = $04;
  ufOrgWeakUnit  = $08;
  ufImplicitUnit = $10;

  ufWeakPackageUnit = ufPackageUnit or ufWeakUnit;

Type
  TUTF8StringDynArray = Array of UTF8String;

{ Delphi compatibility }

{$IFNDEF HAS_INVALIDHANDLE}
const
  INVALID_HANDLE_VALUE = DWORD(-1);
{$ENDIF}
