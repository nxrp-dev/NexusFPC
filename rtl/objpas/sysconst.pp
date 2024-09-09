{
    This file is part of the Free Pascal run time library.
    Copyright (c) 2003 by Florian Klaempfl
    member of the Free Pascal development team

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}
{$mode objfpc}
{$IFNDEF FPC_DOTTEDUNITS}
unit SysConst;
{$ENDIF FPC_DOTTEDUNITS}

{$namespace org.freepascal.rtl}

interface

{ JVM Notes: cpujvm does not support resourcestring (error: this language feature is not supported on managed vm targets) }
{ JVM Notes: cpujvm cannot take the address of an ansistring or unicodestring (error: illegal expression) }
{ JVM Notes: cpujvm cannot take the address of an untyped constant (error: can't take the address of constant expressions) }
{ JVM Notes: cpujvm LineEnding is a variable set at runtime (same compiled bytecode can run on different operating systems) }

{$ifdef FPC_HAS_FEATURE_ANSISTRINGS}
{$H+}
{$ifndef CPUJVM}
resourcestring
{$else CPUJVM}
const
{$endif}
{$else FPC_HAS_FEATURE_ANSISTRINGS}
const
{$endif FPC_HAS_FEATURE_ANSISTRINGS}

{ from old str*.inc files }
  SListIndexError        {$ifdef CPUJVM}: shortstring{$endif} = 'List index (%d) out of bounds';
  SParamIsNegative       {$ifdef CPUJVM}: shortstring{$endif} = 'Parameter "%s" cannot be negative.';
  SListCapacityError     {$ifdef CPUJVM}: shortstring{$endif} = 'List capacity (%d) exceeded.';
  SAbortError            {$ifdef CPUJVM}: shortstring{$endif} = 'Operation aborted';
  SAbstractError         {$ifdef CPUJVM}: shortstring{$endif} = 'Abstract method called';
  SAccessDenied          {$ifdef CPUJVM}: shortstring{$endif} = 'Access denied';
  SAccessViolation       {$ifdef CPUJVM}: shortstring{$endif} = 'Access violation';
  SArgumentMissing       {$ifdef CPUJVM}: shortstring{$endif} = 'Missing argument in format "%s"';
  SAssertError           {$ifdef CPUJVM}: shortstring{$endif} = '%s (%s, line %d)';
  SAssertionFailed       {$ifdef CPUJVM}: shortstring{$endif} = 'Assertion failed';
  SBusError              {$ifdef CPUJVM}: shortstring{$endif} = 'Bus error or misaligned data access';
  SCannotCreateEmptyDir  {$ifdef CPUJVM}: shortstring{$endif} = 'Cannot create empty directory';
  SControlC              {$ifdef CPUJVM}: shortstring{$endif} = 'Control-C hit';
  SDiskFull              {$ifdef CPUJVM}: shortstring{$endif} = 'Disk Full';
  SDispatchError         {$ifdef CPUJVM}: shortstring{$endif} = 'No variant method call dispatch';
  SDivByZero             {$ifdef CPUJVM}: shortstring{$endif} = 'Division by zero';
  SEndOfFile             {$ifdef CPUJVM}: shortstring{$endif} = 'Read past end of file';
  SErrPosToBigForLongint {$ifdef CPUJVM}: shortstring{$endif} = 'File position %d too big to fit in 32-bit integer; Use Int64 overload instead';
  SErrInvalidDateMonthWeek {$ifdef CPUJVM}: shortstring{$endif} = 'Year %d, month %d, Week %d and day %d is not a valid date.';
  SerrInvalidHourMinuteSecMsec {$ifdef CPUJVM}: shortstring{$endif} = '%d:%d:%d.%d is not a valid time specification';
  SErrInvalidDateWeek    {$ifdef CPUJVM}: shortstring{$endif} = '%d %d %d is not a valid dateweek';
  SErrInvalidDayOfWeek   {$ifdef CPUJVM}: shortstring{$endif} = '%d is not a valid day of the week';
  SErrInvalidDayOfWeekInMonth {$ifdef CPUJVM}: shortstring{$endif} = 'Year %d Month %d NDow %d DOW %d is not a valid date';
  SErrInvalidDayOfYear   {$ifdef CPUJVM}: shortstring{$endif} = 'Year %d does not have a day number %d';
  SErrInvalidTimeStamp   {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid date/timestamp : "%s"';
  SInvalidJulianDate            {$ifdef CPUJVM}: shortstring{$endif} = '%f Julian cannot be represented as a DateTime';
  SErrIllegalDateFormatString   {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is not a valid date format string';
  SErrInvalidTimeFormat  {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is not a valid time';
  SExceptionErrorMessage {$ifdef CPUJVM}: shortstring{$endif} = 'Exception at %p: %s';
  SExceptionStack        {$ifdef CPUJVM}: shortstring{$endif} = 'Exception stack error';
  SExecuteProcessFailed  {$ifdef CPUJVM}: shortstring{$endif} = 'Failed to execute "%s", error code: %d';
  SExternalException     {$ifdef CPUJVM}: shortstring{$endif} = 'External exception %x';
  SFileNotAssigned       {$ifdef CPUJVM}: shortstring{$endif} = 'File not assigned';
  SFileNotFound          {$ifdef CPUJVM}: shortstring{$endif} = 'File not found';
  SFileNotOpen           {$ifdef CPUJVM}: shortstring{$endif} = 'File not open';
  SFileNotOpenForInput   {$ifdef CPUJVM}: shortstring{$endif} = 'File not open for input';
  SFileNotOpenForOutput  {$ifdef CPUJVM}: shortstring{$endif} = 'File not open for output';
  SInValidFileName       {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid filename';
  SIntOverflow           {$ifdef CPUJVM}: shortstring{$endif} = 'Arithmetic overflow';
  SIntfCastError         {$ifdef CPUJVM}: shortstring{$endif} = 'Interface not supported';
  SInvalidArgIndex       {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid argument index in format "%s"';
  SInvalidBCD            {$ifdef CPUJVM}: shortstring{$endif} = '%x is an invalid BCD value';
  SInvalidBoolean        {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is not a valid boolean.';
  SInvalidCast           {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid type cast';
  SinvalidCurrency       {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid currency: "%s"';
  SInvalidDateTime       {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is not a valid date/time value.';
  SInvalidDateTimeFloat  {$ifdef CPUJVM}: shortstring{$endif} = '%f is not a valid date/time value.';
  SInvalidDrive          {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid drive specified';
  SInvalidFileHandle     {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid file handle';
  SInvalidFloat          {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is an invalid float';
  SInvalidFormat         {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid format specifier : "%s"';
  SInvalidGUID           {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is not a valid GUID value';
  SInvalidInput          {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid input';
  SInvalidInteger        {$ifdef CPUJVM}: shortstring{$endif} = '"%s" is an invalid integer';
  SInvalidOp             {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid floating point operation';
  SInvalidPointer        {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid pointer operation';
  SInvalidVarCast        {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant type cast';
  SInvalidVarNullOp      {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid NULL variant operation';
  SInvalidVarOp          {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant operation';
  SInvalidBinaryVarOp    {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant operation %s %s %s';
  SInvalidUnaryVarOp     {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant operation %s %s';
  SInvalidVarOpWithHResultWithPrefix {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant operation (%s%.8x)'+LineEnding+'%s';
  SNoError               {$ifdef CPUJVM}: shortstring{$endif} = 'No error.';
  SNoThreadSupport       {$ifdef CPUJVM}: shortstring{$endif} = 'Threads not supported. Recompile program with thread driver.';
  SNoDynLibsSupport      {$ifdef CPUJVM}: shortstring{$endif} = 'Dynamic libraries not supported. Recompile program with dynamic library driver.';
  SMissingWStringManager {$ifdef CPUJVM}: shortstring{$endif} = 'Widestring manager not available. Recompile program with appropriate manager.';
  SSigQuit               {$ifdef CPUJVM}: shortstring{$endif} = 'SIGQUIT signal received.';
  SObjectCheckError      {$ifdef CPUJVM}: shortstring{$endif} = 'Object reference is Nil or VMT is damaged';
  SOSError               {$ifdef CPUJVM}: shortstring{$endif} = 'System error, (OS Code %d):'+LineEnding+'%s';
  SOutOfMemory           {$ifdef CPUJVM}: shortstring{$endif} = 'Out of memory';
  SOverflow              {$ifdef CPUJVM}: shortstring{$endif} = 'Floating point overflow';
  SPrivilege             {$ifdef CPUJVM}: shortstring{$endif} = 'Privileged instruction';
  SRangeError            {$ifdef CPUJVM}: shortstring{$endif} = 'Range check error';
  SStackOverflow         {$ifdef CPUJVM}: shortstring{$endif} = 'Stack overflow or stack misalignment';
  SSafecallException     {$ifdef CPUJVM}: shortstring{$endif} = 'Exception in safecall method';
  SiconvError            {$ifdef CPUJVM}: shortstring{$endif} = 'iconv error';
  SThreadError           {$ifdef CPUJVM}: shortstring{$endif} = 'Thread error';
  SSeekFailed            {$ifdef CPUJVM}: shortstring{$endif} = 'Seek operation failed';

  STooManyOpenFiles      {$ifdef CPUJVM}: shortstring{$endif} = 'Too many open files';
  SUnKnownRunTimeError   {$ifdef CPUJVM}: shortstring{$endif} = 'Unknown Run-Time error : %3.3d';
  SUnderflow             {$ifdef CPUJVM}: shortstring{$endif} = 'Floating point underflow';
  SUnkOSError            {$ifdef CPUJVM}: shortstring{$endif} = 'An operating system call failed.';
  SUnknown               {$ifdef CPUJVM}: shortstring{$endif} = 'Unknown run-time error code: ';
  SUnknownErrorCode      {$ifdef CPUJVM}: shortstring{$endif} = 'Unknown error code: %d';
  SVarArrayBounds        {$ifdef CPUJVM}: shortstring{$endif} = 'Variant array bounds error';
  SVarArrayCreate        {$ifdef CPUJVM}: shortstring{$endif} = 'Variant array cannot be created';
  SVarArrayLocked        {$ifdef CPUJVM}: shortstring{$endif} = 'Variant array locked';
  SVarBadType            {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid variant type';
  SVarInvalid            {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid argument';
  SVarInvalid1           {$ifdef CPUJVM}: shortstring{$endif} = 'Invalid argument: %s';
  SVarNotArray           {$ifdef CPUJVM}: shortstring{$endif} = 'Variant doesn''t contain an array';
  SVarNotImplemented     {$ifdef CPUJVM}: shortstring{$endif} = 'Operation not supported';
  SVarOutOfMemory        {$ifdef CPUJVM}: shortstring{$endif} = 'Variant operation ran out memory';
  SVarOverflow           {$ifdef CPUJVM}: shortstring{$endif} = 'Variant overflow';
  SVarParamNotFound      {$ifdef CPUJVM}: shortstring{$endif} = 'Variant Parameter not found';
  SVarTypeAlreadyUsedWithPrefix {$ifdef CPUJVM}: shortstring{$endif} = 'Custom variant type (%s%.4x) already used by %s';
  SVarTypeConvertOverflow       {$ifdef CPUJVM}: shortstring{$endif} = 'Overflow while converting variant of type (%s) into type (%s)';
  SVarTypeCouldNotConvert       {$ifdef CPUJVM}: shortstring{$endif} = 'Could not convert variant of type (%s) into type (%s)';
  SVarTypeNotUsableWithPrefix   {$ifdef CPUJVM}: shortstring{$endif} = 'Custom variant type (%s%.4x) is not usable';
  SVarTypeOutOfRangeWithPrefix  {$ifdef CPUJVM}: shortstring{$endif} = 'Custom variant type (%s%.4x) is out of range';
  SVarTypeRangeCheck1           {$ifdef CPUJVM}: shortstring{$endif} = 'Range check error for variant of type (%s)';
  SVarTypeRangeCheck2           {$ifdef CPUJVM}: shortstring{$endif} = 'Range check error while converting variant of type (%s) into type (%s)';
  SVarTypeTooManyCustom         {$ifdef CPUJVM}: shortstring{$endif} = 'Too many custom variant types have been registered';
  SVarUnexpected                {$ifdef CPUJVM}: shortstring{$endif} = 'Unexpected variant error';
  SZeroDivide                   {$ifdef CPUJVM}: shortstring{$endif} = 'Floating point division by zero';

  SFallbackError                = 'An error, whose error code is larger than can be returned to the OS, has occurred';

  SNoToolserver                 = 'Toolserver is not installed, cannot execute Tool';

  SNotValidCodePageName         = '%s is not a valid code page name';
  SInvalidCount                 = 'invalid count [%d]';
  SCharacterIndexOutOfBounds    = 'character index out of bounds [%d]';
  SInvalidDestinationArray      = 'invalid destination array';
  SInvalidDestinationIndex      = 'invalid destination index [%d]';

  SNoArrayMatch                 = 'Can''t match any allowed value at pattern position %d, string position %d.';
  SNoCharMatch                  = 'Mismatch char "%s" <> "%s" at pattern position %d, string position %d.';
  SHHMMError                    = 'mm in a sequence hh:mm is interpreted as minutes. No longer versions allowed! (Position : %d).' ;
  SFullpattern                  = 'Couldn''t match entire pattern string. Input too short at pattern position %d.';
  SPatternCharMismatch          = 'Pattern mismatch char "%s" at position %d.';
  SAMPMError                    = 'Hour >= 13 not allowed in AM/PM mode.';
  SErrListIndexExt              = 'List index out of bounds (%d): %s object range is 0..%d';
  SListIndexErrorEmptyReason = '%s is empty';
  SListIndexErrorRangeReason = '%s object range is 0..%d';

  SShortMonthNameJan = 'Jan';
  SShortMonthNameFeb = 'Feb';
  SShortMonthNameMar = 'Mar';
  SShortMonthNameApr = 'Apr';
  SShortMonthNameMay = 'May';
  SShortMonthNameJun = 'Jun';
  SShortMonthNameJul = 'Jul';
  SShortMonthNameAug = 'Aug';
  SShortMonthNameSep = 'Sep';
  SShortMonthNameOct = 'Oct';
  SShortMonthNameNov = 'Nov';
  SShortMonthNameDec = 'Dec';

  SLongMonthNameJan = 'January';
  SLongMonthNameFeb = 'February';
  SLongMonthNameMar = 'March';
  SLongMonthNameApr = 'April';
  SLongMonthNameMay = 'May';
  SLongMonthNameJun = 'June';
  SLongMonthNameJul = 'July';
  SLongMonthNameAug = 'August';
  SLongMonthNameSep = 'September';
  SLongMonthNameOct = 'October';
  SLongMonthNameNov = 'November';
  SLongMonthNameDec = 'December';

  SShortDayNameMon = 'Mon';
  SShortDayNameTue = 'Tue';
  SShortDayNameWed = 'Wed';
  SShortDayNameThu = 'Thu';
  SShortDayNameFri = 'Fri';
  SShortDayNameSat = 'Sat';
  SShortDayNameSun = 'Sun';

  SLongDayNameMon = 'Monday';
  SLongDayNameTue = 'Tuesday';
  SLongDayNameWed = 'Wednesday';
  SLongDayNameThu = 'Thursday';
  SLongDayNameFri = 'Friday';
  SLongDayNameSat = 'Saturday';
  SLongDayNameSun = 'Sunday';

const
   // Do not localize
   HexDigits: array[0..15] of AnsiChar = '0123456789ABCDEF';
   HexDigitsW: array[0..15] of widechar = '0123456789ABCDEF';

Function GetRunError(Errno : Word) : String;

Implementation

Function GetRunError(Errno : Word) : String;

begin
  Case Errno Of
     0  : Result:=SNoError;
     1  : Result:=SOutOfMemory;
     2  : Result:=SFileNotFound;
     3  : Result:=SInvalidFileName;
     4  : Result:=STooManyOpenFiles;
     5  : Result:=SAccessDenied;
     6  : Result:=SInvalidFileHandle;
     15 : Result:=SInvalidDrive;
     100 : Result:=SEndOfFile;
     101 : Result:=SDiskFull;
     102 : Result:=SFileNotAssigned;
     103 : Result:=SFileNotOpen;
     104 : Result:=SFileNotOpenForInput;
     105 : Result:=SFileNotOpenForOutput;
     106 : Result:=SInvalidInput;
     200 : Result:=SDivByZero;
     201 : Result:=SRangeError;
     203 : Result:=SOutOfMemory;
     204 : Result:=SInvalidPointer;
     205 : Result:=SOverFlow;
     206 : Result:=SUnderFlow;
     207 : Result:=SInvalidOp;
     211 : Result:=SAbstractError;
     214 : Result:=SBusError;
     215 : Result:=SIntOverFlow;
     216 : Result:=SAccessViolation;
     217 : Result:=SPrivilege;
     218 : Result:=SControlC;
     219 : Result:=SInvalidCast;
     220 : Result:=SInvalidVarCast;
     221 : Result:=SInvalidVarOp;
     222 : Result:=SDispatchError;
     223 : Result:=SVarArrayCreate;
     224 : Result:=SVarNotArray;
     225 : Result:=SVarArrayBounds;
     227 : Result:=SAssertionFailed;
     228 : Result:=SExternalException;
     229 : Result:=SIntfCastError;
     230 : Result:=SSafecallException;
     231 : Result:=SExceptionStack;
     232 : Result:=SNoThreadSupport;
     234 : Result:=SMissingWStringManager;
     235 : Result:=SNoDynLibsSupport;

     255 : Result:=SFallbackError;

     {Error codes larger than 255 cannot be returned as an exit code to the OS,
      for some OS's. If this happens, error 255 is returned instead.
      Errors for which it is important that they can be distinguished,
      shall be below 255}

     {Error in the range 900 - 999 is considered platform specific}

     900 : Result:=SNoToolserver;    {Mac OS specific}

  end;
  If length(Result)=0 then
    begin
      Str(Errno:3,Result);
      Result:=SUnknown+Result;
    end;
end;

end.
