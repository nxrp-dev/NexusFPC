{$ifdef Delphi}
const fpmkunitsrc : array[0..1501] of string[240]=(
{$else Delphi}
const fpmkunitsrc : array[0..1501,1..240] of char=(
{$endif Delphi}
  '{'#013#010+
  '    This file is part of the Free Pascal Makefile Package'#013#010+
  #013#010+
  '    Implementation of fpmake classes and functions'#013#010+
  #013#010+
  '    Copyright (c) 2007 by the freepascal team'#013#010+
  #013#010+
  '    See the file COPYING.FPC, included in this distribution,'#013#010+
  '    for det','ails about the copyright.'#013#010+
  #013#010+
  '    This program is distributed in the hope that it will be useful,'#013+
  #010+
  '    but WITHOUT ANY WARRANTY; without even the implied warranty of'#013+
  #010+
  '    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.'#013#010+
  #013#010+
  ' *************','******************************************************'+
  '***}'#013#010+
  #013#010+
  'unit fpMkUnit;'#013#010+
  #013#010+
  '{$Mode objfpc}'#013#010+
  '{$H+}'#013#010+
  '{$inline on}'#013#010+
  '{$MODESWITCH TYPEHELPERS}'#013#010+
  '{$modeswitch advancedrecords}'#013#010+
  #013#010+
  '{ For target or cpu dependent dependencies also add an overload',' wher'+
  'e you'#013#010+
  '  can pass only a set of cpus. This is disabled for now because it cre'+
  'ates'#013#010+
  '  an error in the compiler with overload choosing }'#013#010+
  '{ define cpu_only_overloads}'#013#010+
  #013#010+
  'Interface'#013#010+
  #013#010+
  '{$ifdef CPULLVM}'#013#010+
  '  {$define LLVM_INTERFACE_PROBLEM}'#013#010,
  '{$endif CPULLVM}'#013#010+
  '{$IFDEF GO32V2}'#013#010+
  ' {$DEFINE NO_UNIT_PROCESS}'#013#010+
  ' {$DEFINE NO_THREADING}'#013#010+
  '{$ENDIF GO32V2}'#013#010+
  #013#010+
  '{$IFDEF NDS}'#013#010+
  ' {$DEFINE NO_THREADING}'#013#010+
  '{$ENDIF NDS}'#013#010+
  #013#010+
  '{$IFDEF NETBSD}'#013#010+
  ' { NetBSD pthreads are not yet working, try to use fpmake wit','hout th'+
  'reads }'#013#010+
  '  {$DEFINE NO_THREADING}'#013#010+
  '{$ENDIF NETBSD}'#013#010+
  #013#010+
  '{ $define NO_UNIT_PROCESS}'#013#010+
  '{ $define NO_TAR_SUPPORT}'#013#010+
  '{ $define NO_UNIT_ZIPPER}'#013#010+
  #013#010+
  '{$ifndef NO_UNIT_PROCESS}'#013#010+
  '  {$define HAS_UNIT_PROCESS}'#013#010+
  '{$endif NO_UNIT_PROCESS}'#013#010+
  #013#010+
  '{$ifndef N','O_UNIT_ZIPPER}'#013#010+
  '  {$define HAS_UNIT_ZIPPER}'#013#010+
  '{$endif NO_UNIT_ZIPPER}'#013#010+
  #013#010+
  '{$ifndef NO_TAR_SUPPORT}'#013#010+
  '  {$define HAS_TAR_SUPPORT}'#013#010+
  '{$endif NO_TAR_SUPPORT}'#013#010+
  #013#010+
  '{$ifdef unix}'#013#010+
  '  {$ifdef HAS_TAR_SUPPORT}'#013#010+
  '    {$define CREATE_TAR_FILE}'#013#010+
  '  {$endif HA','S_TAR_SUPPORT}'#013#010+
  '{$endif unix}'#013#010+
  #013#010+
  '{$IFDEF FPC_DOTTEDUNITS}'#013#010+
  'uses'#013#010+
  '  System.Types,'#013#010+
  '{$ifdef Unix}'#013#010+
  '  UnixApi.Base,'#013#010+
  '{$endif Unix}'#013#010+
  '{$ifdef Windows}'#013#010+
  '  WinApi.Windows,'#013#010+
  '{$endif Windows}'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '{$ifdef Unix}'#013#010+
  '  UnixApi.CThread','s,'#013#010+
  '{$endif Unix}'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  System.SysUtils, System.Classes'#013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  ,System.Process'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  '{$ifdef HAS_TAR_SUPPORT}'#013#010+
  '  ,Libx.Libtar'#013#010+
  '{$endif HAS_TAR_SUPPORT}'#013#010+
  '{$ifdef HAS_UNIT_ZIPPE','R}'#013#010+
  '  ,System.ZLib.Zipper, System.ZLib.Zstream'#013#010+
  '{$endif HAS_UNIT_ZIPPER}'#013#010+
  '  ;'#013#010+
  '{$ELSE FPC_DOTTEDUNITS}'#013#010+
  'uses'#013#010+
  '  Types,'#013#010+
  '{$ifdef UNIX}'#013#010+
  '  BaseUnix,'#013#010+
  '{$endif UNIX}'#013#010+
  '{$ifdef WINDOWS}'#013#010+
  '  windows,'#013#010+
  '{$endif WINDOWS}'#013#010+
  '  SysUtils, Classes'#013#010+
  '{$ifdef ','HAS_UNIT_PROCESS}'#013#010+
  '  ,process'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  '{$ifdef HAS_TAR_SUPPORT}'#013#010+
  '  ,libtar'#013#010+
  '{$endif HAS_TAR_SUPPORT}'#013#010+
  '{$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '  ,zipper, zstream'#013#010+
  '{$endif HAS_UNIT_ZIPPER}'#013#010+
  '  ;'#013#010+
  '{$ENDIF FPC_DOTTEDUNITS}'#013#010+
  #013#010+
  '{$IF DECLARED(','VOLATILE)}'#013#010+
  '{$DEFINE HAVE_VOLATILE}'#013#010+
  '{$ENDIF}'#013#010+
  #013#010+
  'Type'#013#010+
  '{$IF NOT DECLARED(RTLString)}'#013#010+
  '  RTLString = AnsiString;'#013#010+
  '{$ENDIF}'#013#010+
  #013#010+
  '{$IF SIZEOF(CHAR)=1}'#013#010+
  '  TRTLStringDynArray = TStringDynArray;'#013#010+
  '{$ENDIF}'#013#010+
  #013#010+
  '  TFileType = (ftSource,ftUnit,ftObject,','ftResource,ftExecutable,ftSt'+
  'aticLibrary,'#013#010+
  '               ftSharedLibrary);'#013#010+
  '  TFileTypes = set of TFileType;'#013#010+
  #013#010+
  '  // Please keep this order, see OSCPUSupported below'#013#010+
  '  TCpu=(cpuNone,'#013#010+
  '    i386,m68k,powerpc,sparc,x86_64,arm,powerpc64,avr,ar','meb,'#013#010+
  '    mips,mipsel,mips64,mips64el,jvm,i8086,aarch64,wasm32,sparc64,riscv'+
  '32,riscv64,xtensa,z80,loongarch64'#013#010+
  '  );'#013#010+
  '  TCPUS = Set of TCPU;'#013#010+
  #013#010+
  '  // Please keep this order, see OSCPUSupported below'#013#010+
  '  TOS=(osNone,'#013#010+
  '    linux,go32v2,win32,obs','olete_os2,freebsd,beos,netbsd,'#013#010+
  '    obsolete_amiga,atari, solaris, qnx, obsolete_netware, openbsd,wdos'+
  'x,'#013#010+
  '    palmos,macosclassic,darwin,obsolete_emx,watcom,obsolete_morphos,ob'+
  'solete_netwlibc,'#013#010+
  '    win64,wince,gba,nds,embedded,symbian,haiku',',iphonesim,'#013#010+
  '    aix,java,android,nativent,msdos,wii,obsolete_aros,dragonfly,'#013#010+
  '    win16,freertos,zxspectrum,msxdos,ios,amstradcpc,sinclairql,'#013#010+
  '    wasip1,human68k,ps1,wasip1threads,wasip2'#013#010+
  '  );'#013#010+
  '  TOSes = Set of TOS;'#013#010+
  #013#010+
  '  TCompilerMode = (','cmFPC,cmTP,cmObjFPC,cmDelphi,cmMacPas,cmDelphiUni'+
  'code);'#013#010+
  '  TCompilerModes = Set of TCompilerMode;'#013#010+
  #013#010+
  '  TInstallMode = (imInstall, imUnInstall);'#013#010+
  #013#010+
  '  TTargetType = (ttProgram,ttUnit,ttImplicitUnit,ttCleanOnlyUnit,ttExa'+
  'mpleUnit,ttExampleProgr','am,ttSharedLibrary);'#013#010+
  '  TTargetTypes = set of TTargetType;'#013#010+
  #013#010+
  '  TTargetState = (tsNeutral,tsConsidering,tsNoCompile,tsCompiled,tsIns'+
  'talled,tsNotFound);'#013#010+
  '  TTargetStates = Set of TTargetState;'#013#010+
  #013#010+
  '  TSourceType = (stDoc,stSrc,stExample,stTest',');'#013#010+
  '  TSourceTypes = set of TSourceType;'#013#010+
  #013#010+
  '  TVerboseLevel = (vlError,vlWarning,vlInfo,vldebug,vlCommand);'#013#010+
  '  TVerboseLevels = Set of TVerboseLevel;'#013#010+
  #013#010+
  '  TCommandAt = (caBeforeCompile,caAfterCompile,'#013#010+
  '                caBeforeInstall,caAfte','rInstall,'#013#010+
  '                caBeforeArchive,caAfterArchive,'#013#010+
  '                caBeforeClean,caAfterClean,'#013#010+
  '                caBeforeDownload,caAfterDownload);'#013#010+
  #013#010+
  '  TDependencyType = (depPackage,depImplicitPackage,depUnit,depInclude)'+
  ';'#013#010+
  '  TDepen','dencyTypes = set of TDependencyType;'#013#010+
  #013#010+
  '  TLogEvent = Procedure (Level : TVerboseLevel; Const Msg : String) of'+
  ' Object;'#013#010+
  '  TNotifyProcEvent = procedure(Sender: TObject);'#013#010+
  #013#010+
  '  TRunMode = (rmCompile,rmBuild,rmInstall,rmBuildInstall,rmArchive,r','m'+
  'Clean,rmDistClean,rmManifest,rmZipInstall,rmPkgList,rmUnInstall,rmInfo'+
  ');'#013#010+
  #013#010+
  '  TBuildMode = (bmOneByOne, bmBuildUnit{, bmSkipImplicitUnits});'#013#010+
  '  TBuildModes = set of TBuildMode;'#013#010+
  '  TProcessPackageResult = (ppHandled, ppDelayed);'#013#010+
  '  TCheckDe','pendencyResult = (cdAvailable, cdNotAvailable, cdNotYetAva'+
  'ilable);'#013#010+
  #013#010+
  '  { TCompileTarget }'#013#010+
  #013#010+
  '  TCompileTarget = record'#013#010+
  '    OS : TOS;'#013#010+
  '    CPU : TCPU;'#013#010+
  '    Subtarget : String;'#013#010+
  '  Private'#013#010+
  '    Function GetAsString : String;'#013#010+
  '    Procedure S','etAsString(const aValue : String);'#013#010+
  '  Public'#013#010+
  '    Function Equals(const aValue : TCompileTarget) : Boolean;'#013#010+
  '    Function ToString(aLimit83: Boolean): String;'#013#010+
  '    // Full target. if you need the 8.3 version, use ToString instead.'+
  #013#010+
  '    Prop','erty AsString : String Read GetAsString Write SetAsString;'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  'Const'#013#010+
  '  // Aliases'#013#010+
  '  Amd64 = X86_64;'#013#010+
  '  PPC = PowerPC;'#013#010+
  '  PPC64 = PowerPC64;'#013#010+
  '  DOS = Go32v2;'#013#010+
  '  MacOSX = Darwin;'#013#010+
  #013#010+
  '  AllOSes = [Low(TOS)..High(TOS)]-[obsolete_os2,obs','olete_amiga,obsol'+
  'ete_netware,obsolete_emx,obsolete_morphos,obsolete_netwlibc,obsolete_a'+
  'ros];'#013#010+
  '  AllCPUs = [Low(TCPU)..High(TCPU)];'#013#010+
  '  AllUnixOSes  = [Linux,FreeBSD,NetBSD,OpenBSD,Darwin,QNX,BeOS,Solaris'+
  ',Haiku,iphonesim,ios,aix,Android,drago','nfly];'#013#010+
  '  AllBSDOSes      = [FreeBSD,NetBSD,OpenBSD,Darwin,iphonesim,ios,drago'+
  'nfly];'#013#010+
  '  AllWindowsOSes  = [Win32,Win64,WinCE];'#013#010+
  '  AllLimit83fsOses = [go32v2,watcom,msdos,win16,atari,human68k];'#013#010+
  '  AllWebAssemblyOSes = [wasip1, wasip1threads,',' wasip2];'#013#010+
  #013#010+
  '  AllSmartLinkLibraryOSes = [Linux,msdos,win16,palmos]; // OSes that u'+
  'se .a library files for smart-linking'#013#010+
  '  AllImportLibraryOSes = AllWindowsOSes + [watcom,go32v2,macosclassic,'+
  'nativent,msdos,win16];'#013#010+
  #013#010+
  '  { This table is kept',' OS,Cpu because it is easier to maintain (PFV)'+
  ' }'#013#010+
  '  OSCPUSupported : array[TOS,TCpu] of boolean = ('#013#010+
  '    { os          none   i386   m68k   ppc    sparc  x86_64 arm    ppc'+
  '64  avr    armeb  mips   mipsel mips64 mips64el jvm    i8086 aarch64 ',
  'wasm32 sparc64 riscv32 riscv64  xtensa z80,   loongarch64}'#013#010+
  '    { none }    ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, fa','lse, false),'#013#010+
  '    { linux }   ( false, true,  true,  true,  true,  true,  true,  tru'+
  'e,  false, true , true , true , true , true ,   false, false, true , f'+
  'alse, true ,  true ,  true,    true , false, true),'#013#010+
  '    { go32v2 }  ( false, true,  f','alse, false, false, false, false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { win32 }   ( false, true,  false, false, false, false, false, fal'+
  'se, false',', false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '{ obsolete_os2 }( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, ','false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { freebsd } ( false, true,  false, false, false, true,  false, tru'+
  'e,  false, false, false, false, false, false,   false, false, true , f'+
  'alse, false,  false,  false,   ','false, false, false),'#013#010+
  '    { beos }    ( false, true,  false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '    { netbsd }  ( false',', true,  true,  true,  true,  true,  true,  f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { obsolete_amiga }   ( false, false, false, false, false, false, ',
  'false, false, false, false, false, false, false, false,   false, false'+
  ', false, false, false,  false,  false,   false, false, false),'#013#010+
  '    { atari }   ( false, false, true,  false, false, false, false, fal'+
  'se, false, false, false, false, fals','e, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { solaris } ( false, true,  false, false, true,  true,  false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,','  false,  false,   false, false, false),'#013#010+
  '    { qnx }     ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '{ ob','solete_netware } ( false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false, false,   false, false, f'+
  'alse, false, false,  false,  false,   false, false, false),'#013#010+
  '    { openbsd } ( false, true,  false, false,',' false, true,  false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { wdosx }   ( false, true,  false, false, false, false, false, fal'+
  'se, false, false, fal','se, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { palmos }  ( false, false, true,  false, false, false, true,  fal'+
  'se, false, false, false, false, false, false,   false, false, false',','+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '{ macosclassic }( false, false, true,  true,  false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, false',', false),'#013#010+
  '    { darwin }  ( false, true,  false, true,  false, true,  false,  tr'+
  'ue, false, false, false, false, false, false,   false, false, true , f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '{ obsolete_emx }( false, false, fal','se, false, false, false, false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { watcom }  ( false, true,  false, false, false ,false, false, fal'+
  'se, false, ','false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { obsolete_morphos } ( false, false, false, false, false, false, f'+
  'alse, false, false, false, false, false, false, false,   ','false, fals'+
  'e, false, false, false,  false,  false,   false, false, false),'#013#010+
  '{ obsolete_netwlibc }( false, false, false, false, false, false, false'+
  ', false, false, false, false, false, false, false,   false, false, fal'+
  'se, false, false,  false',',  false,   false, false, false),'#013#010+
  '    { win64   } ( false, false, false, false, false, true,  false, fal'+
  'se, false, false, false, false, false, false,   false, false, true,  f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '    { wince','    }( false, true,  false, false, false, false, true,  f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { gba    }  ( false, false, false, false, false, fals','e, true,  f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { nds    }  ( false, false, false, false, false, false, true,  fal'+
  'se, false, false, false, false, f','alse, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { embedded }( false, true,  true,  true,  true,  true,  true,  tru'+
  'e,  true,  true , false, true,  false, false,    false, true , true , '+
  'true,  fa','lse,  true,   true,   true,  true,  false),'#013#010+
  '    { symbian } ( false, true,  false, false, false, false, true,  fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  ' ','   { haiku }   ( false, true,  false, false, false, true,  false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { iphonesim}( false, true,  false, false, f','alse, true,  false, f'+
  'alse, false, false, false, false, false, false,   false, false, true ,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { aix    }  ( false, false, false, true,  false, false, false, tru'+
  'e,  false, false, false',', false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { java }    ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   true , false, false, ',
  'false, false,  false,  false,   false, false, false),'#013#010+
  '    { android } ( false, true,  false, false, false, true,  true,  fal'+
  'se, false, false, false, true,  false, false,   true , false, true,  f'+
  'alse, false,  false,  false,   false, false, ','false),'#013#010+
  '    { nativent }( false, true,  false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '    { msdos }   ( false, false, false',', false, false, false, false, f'+
  'alse, false, false, false, false, false, false,   false, true , false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { wii }     ( false, false, false, true , false, false, false, fal'+
  'se, false, fa','lse, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { obsolete_aros }    ( false, false, false, false, false, false, f'+
  'alse, false, false, false, false, false, false, false,   fa','lse, fals'+
  'e, false, false, false,  false,  false,   false, false, false),'#013#010+
  '    { dragonfly}( false, false, false, false, false, true,  false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  fals','e,   false, false, false),'#013#010+
  '    { win16 }   ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, true , false, f'+
  'alse, false,  false,  false,   false, false, false),'#013#010+
  '    { freertos }( ','false, false, false, false, false, false, true,  f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  true,   false,   true , false, false),'#013#010+
  '    {zxspectrum}( false, false, false, false, false, false, fals','e, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, true,  false),'#013#010+
  '    { msxdos }  ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, f','alse,   false, false, false,'+
  ' false, false,  false,  false,   false, true,  false),'#013#010+
  '    { ios }     ( false, false, false, false, false, false,  true, fal'+
  'se, false, false, false, false, false, false,   false, false, true , f'+
  'alse, false,  fa','lse,  false,   false, false, false),'#013#010+
  '    {amstradcpc}( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, f'+
  'alse, false,  false,  false,   false, true,  false),'#013#010+
  '    {sin','clairql}( false, false, true,  false, false, false, false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { wasip1 }  ( false, false, false, false, false, f','alse, false, f'+
  'alse, false, false, false, false, false, false,   false, false, false,'+
  ' true,  false,  false,  false,   false, false, false),'#013#010+
  '    { human68k }( false, false, true,  false, false, false, false, fal'+
  'se, false, false, false, false',', false, false,   false, false, false,'+
  ' false, false,  false,  false,   false, false, false),'#013#010+
  '    { ps1 }     ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, true,  false, false,   false, false, false, f'+
  'alse, ','false,  false,  false,   false, false, false),'#013#010+
  ' {wasip1threads}( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, t'+
  'rue,  false,  false,  false,   false, false, false),',#013#010+
  '    { wasip2 }  ( false, false, false, false, false, false, false, fal'+
  'se, false, false, false, false, false, false,   false, false, false, t'+
  'rue,  false,  false,  false,   false, false, false)'#013#010+
  '  );'#013#010+
  #013#010+
  '  // Useful'#013#010+
  '  UnitExt = '#039'.ppu'#039';'#013#010+
  '  P','PUExt  = UnitExt;'#013#010+
  '  PasExt  = '#039'.pas'#039';'#013#010+
  '  PPExt   = '#039'.pp'#039';'#013#010+
  '  IncExt  = '#039'.inc'#039';'#013#010+
  '  ObjExt  = '#039'.o'#039';'#013#010+
  '  LTOExt  = '#039'.bc'#039';'#013#010+
  '  RstExt  = '#039'.rst'#039';'#013#010+
  '  RsjExt  = '#039'.rsj'#039';'#013#010+
  '  LibExt  = '#039'.a'#039';'#013#010+
  '  SharedLibExt = '#039'.so'#039';'#013#010+
  '  WasiSharedLibExt = '#039#039';'#013#010+
  '  DyLibE','xt = '#039'.dylib'#039';'#013#010+
  '  DLLExt  = '#039'.dll'#039';'#013#010+
  '  AIXSharedLibExt = '#039'.a'#039';'#013#010+
  '  ExeExt  = '#039'.exe'#039';'#013#010+
  '  WasiExeExt  = '#039'.wasm'#039';'#013#010+
  '  DbgExt  = '#039'.dbg'#039';'#013#010+
  '  ZipExt  = '#039'.zip'#039';'#013#010+
  '  FpmkExt = '#039'.fpm'#039';'#013#010+
  #013#010+
  '  FPMakePPFile = '#039'fpmake.pp'#039';'#013#010+
  '  ManifestFile = '#039'manifest.xml'#039';'#013,#010+
  '  PkgListFileBase = '#039'pkg-'#039';'#013#010+
  '  PkgListFileExt = '#039'.lst'#039';'#013#010+
  #013#010+
  '  DirNotFound = '#039'<dirnotfound>'#039';'#013#010+
  #013#010+
  '  UnitTargets = [ttUnit,ttImplicitUnit,ttCleanOnlyUnit,ttExampleUnit];'+
  #013#010+
  '  ProgramTargets = [ttProgram,ttExampleProgram,ttSharedLibrary];'#013#010+
  #013#010+
  '  De','faultMessages = [vlError,vlWarning,vlCommand];'#013#010+
  '  AllMessages = [vlError,vlWarning,vlCommand,vlInfo];'#013#010+
  #013#010+
  'Type'#013#010+
  '  TTargets = Class;'#013#010+
  '  TBuildEngine = Class;'#013#010+
  #013#010+
  '  { TNamedItem }'#013#010+
  #013#010+
  '  TNamedItem = Class(TCollectionItem)'#013#010+
  '  private'#013#010+
  '    FName: ','String;'#013#010+
  '    procedure SetName(const AValue: String);virtual;'#013#010+
  '  Public'#013#010+
  '    property Name : String Read FName Write SetName;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TNamedCollection }'#013#010+
  #013#010+
  '  TNamedCollection = Class(TCollection)'#013#010+
  '  private'#013#010+
  '    FUniqueNames: Boolean',';'#013#010+
  '  private'#013#010+
  '    function GetItem(Index: Integer): TNamedItem;'#013#010+
  '    procedure SetItem(Index: Integer; AValue: TNamedItem);'#013#010+
  '  Public'#013#010+
  '    Function IndexOfName(const AName : String) : Integer;'#013#010+
  '    Function ItemByName(const AName : String) ',': TNamedItem;'#013#010+
  '    Property UniqueNames : Boolean Read FUniqueNames;'#013#010+
  '    property Items[Index: Integer]: TNamedItem read GetItem write SetI'+
  'tem;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TNamedItemList }'#013#010+
  #013#010+
  '  TNamedItemList = Class(TFPList)'#013#010+
  '  private'#013#010+
  '    function G','etNamedItem(Index : Integer): TNamedItem;'#013#010+
  '    procedure SetNamedItem(Index : Integer; const AValue: TNamedItem);'+
  #013#010+
  '  public'#013#010+
  '    Function IndexOfName(const AName : String) : Integer;'#013#010+
  '    Function ItemByName(const ANAme : String) : TNamedIt','em;'#013#010+
  '    Property NamedItems[Index : Integer] : TNamedItem Read GetNamedIte'+
  'm Write SetNamedItem; default;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TCommand }'#013#010+
  '  TCommand = Class(TNamedItem)'#013#010+
  '  private'#013#010+
  '    FAfterCommand: TNotifyEvent;'#013#010+
  '    FBeforeCommand: TNotifyEve','nt;'#013#010+
  '    FCommand: String;'#013#010+
  '    FCommandAt: TCommandAt;'#013#010+
  '    FDestFile: String;'#013#010+
  '    FIgnoreResult: Boolean;'#013#010+
  '    FOptions: TStrings;'#013#010+
  '    FSourceFile: String;'#013#010+
  '    Function GetOptions : TStrings;'#013#010+
  '    Procedure SetOptions(Const Value : TSt','rings);'#013#010+
  '  Public'#013#010+
  '    Destructor Destroy; override;'#013#010+
  '    Function HaveOptions : Boolean;'#013#010+
  '    Function CmdLineOptions : String;'#013#010+
  '    Procedure ParseOptions(S : String);'#013#010+
  '    Property SourceFile : String Read FSourceFile Write FSourceFile;'#013,
  #010+
  '    Property DestFile : String Read FDestFile Write FDestFile;'#013#010+
  '    Property Command : String Read FCommand Write FCommand;'#013#010+
  '    Property Options : TStrings Read GetOptions Write SetOptions;'#013#010+
  '    Property At : TCommandAt Read FCommandAt Wr','ite FCommandAt;'#013#010+
  '    Property IgnoreResult : Boolean Read FIgnoreResult Write FIgnoreRe'+
  'sult;'#013#010+
  '    Property BeforeCommand : TNotifyEvent Read FBeforeCommand Write FB'+
  'eforeCommand;'#013#010+
  '    Property AfterCommand : TNotifyEvent Read FAfterCommand W','rite FA'+
  'fterCommand;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TCommands }'#013#010+
  #013#010+
  '  { TCommandEnumerator }'#013#010+
  #013#010+
  '  TCommandEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TCommand;'#013#010+
  '    property Current: TCommand read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  TC','ommands = Class(TNamedCollection)'#013#010+
  '  private'#013#010+
  '    FDefaultAt: TCommandAt;'#013#010+
  '    function GetCommand(const Dest : String): TCommand;'#013#010+
  '    function GetCommandItem(Index : Integer): TCommand;'#013#010+
  '    procedure SetCommandItem(Index : Integer; const',' AValue: TCommand'+
  ');'#013#010+
  '  Public'#013#010+
  '    Function AddCommand(Const Cmd : String) : TCommand;'#013#010+
  '    Function AddCommand(Const Cmd,Options : String) : TCommand;'#013#010+
  '    Function AddCommand(Const Cmd,Options,Dest,Source : String) : TCom'+
  'mand;'#013#010+
  '    Functi','on AddCommand(At : TCommandAt; Const Cmd : String) : TComm'+
  'and;'#013#010+
  '    Function AddCommand(At : TCommandAt; Const Cmd,Options : String) :'+
  ' TCommand;'#013#010+
  '    Function AddCommand(At : TCommandAt; Const Cmd,Options, Dest,Sourc'+
  'e : String) : TCommand;'#013,#010+
  '    Function GetEnumerator : TCommandEnumerator;'#013#010+
  '    Property CommandItems[Index : Integer] : TCommand Read GetCommandI'+
  'tem Write SetCommandItem;'#013#010+
  '    Property Commands[Dest : String] : TCommand Read GetCommand; defau'+
  'lt;'#013#010+
  '    Property Defa','ultAt : TCommandAt Read FDefaultAt Write FDefaultAt'+
  ';'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TFPVersion }'#013#010+
  #013#010+
  '  TFPVersion = Class(TPersistent)'#013#010+
  '  private'#013#010+
  '    FMajor,'#013#010+
  '    FMinor,'#013#010+
  '    FMicro,'#013#010+
  '    FBuild    : Integer;'#013#010+
  '    function GetAsString: String;'#013#010+
  '    functi','on GetEmpty: Boolean;'#013#010+
  '    procedure SetAsString(const AValue: String);'#013#010+
  '  Public'#013#010+
  '   Procedure Clear;'#013#010+
  '   Procedure Assign(Source : TPersistent); override;'#013#010+
  '   Function CompareVersion(AVersion : TFPVersion) : Integer;'#013#010+
  '   Function SameVers','ion(AVersion : TFPVersion) : Boolean;'#013#010+
  '   Property AsString : String Read GetAsString Write SetAsString;'#013#010+
  '   Property Empty : Boolean Read GetEmpty;'#013#010+
  '  Published'#013#010+
  '   Property Major : Integer Read FMajor Write FMajor;'#013#010+
  '   Property Minor : In','teger Read FMinor Write FMinor;'#013#010+
  '   Property Micro : Integer Read FMicro Write FMicro;'#013#010+
  '   Property Build : Integer Read FBuild Write FBuild;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TConditionalString }'#013#010+
  '  TConditionalString = Class(TCollectionItem)'#013#010+
  '  private'#013#010+
  '   ',' FOSes   : TOSes;'#013#010+
  '    FCPUs   : TCPUs;'#013#010+
  '    FValue  : String;'#013#010+
  '    procedure SetValue(const Value: String);'#013#010+
  '  Public'#013#010+
  '    Procedure Assign(aSource : TPersistent); override;'#013#010+
  '    Function Match (aCPU : TCPU; aOS : TOS) : Boolean;'#013#010+
  '    Func','tion Match (const aValue : String; aCPU : TCPU; aOS : TOS) :'+
  ' Boolean;'#013#010+
  '    Property Value : String Read FValue Write SetValue;'#013#010+
  '    Property OSes  : TOSes Read FOSes Write FOSes;'#013#010+
  '    Property CPUs : TCPUs Read FCPUS Write FCPUs;'#013#010+
  '  end;'#013#010+
  #013,#010+
  '  TConditionalStringClass = class of TConditionalString;'#013#010+
  #013#010+
  '  { TConditionalStrings }'#013#010+
  #013#010+
  '  TConditionalStrings = Class(TCollection)'#013#010+
  '  private'#013#010+
  '    function GetConditionalString(Index : Integer): TConditionalString'+
  ';'#013#010+
  '    procedure SetCondi','tionalString(Index : Integer; const AValue: TC'+
  'onditionalString);'#013#010+
  '  Public'#013#010+
  '    Procedure AddList(aList : TConditionalStrings);'#013#010+
  '    Function IndexOf(Value : String; aCPU : TCPU; aOS : TOS) : Integer'+
  ';'#013#010+
  '    Function Find(Value : String; aCPU',' : TCPU; aOS : TOS) : TConditi'+
  'onalString;'#013#010+
  '    Function Add(Const Value : String) : TConditionalString;inline; ov'+
  'erload;'#013#010+
  '    Function Add(Const Value : String;const OSes:TOSes) : TConditional'+
  'String;inline; overload;'#013#010+
  '{$ifdef cpu_only_overl','oads}'#013#010+
  '    Function Add(Const Value : String;const CPUs:TCPUs) : TConditional'+
  'String;inline; overload;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function Add(Const Value : String;const CPUs:TCPUs;const OSes:TOSe'+
  's) : TConditionalString; overload;'#013#010+
  '  ','  Property ConditionalStrings[Index : Integer] : TConditionalStrin'+
  'g Read GetConditionalString Write SetConditionalString; default;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TConditionalDestString }'#013#010+
  #013#010+
  '  TConditionalDestString = Class(TConditionalString)'#013#010+
  '  private'#013#010+
  ' ','   FDestPath: string;'#013#010+
  '  public'#013#010+
  '    Procedure Assign(aSource : TPersistent); override;'#013#010+
  '    property DestPath: string read FDestPath write FDestPath;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  TConditionalDestStringClass = class of TConditionalDestString;'#013#010+
  #013#010+
  '  { TCondi','tionalDestStrings }'#013#010+
  #013#010+
  '  TConditionalDestStrings = Class(TConditionalStrings)'#013#010+
  '  private'#013#010+
  '    function GetConditionalString(Index : Integer): TConditionalDestSt'+
  'ring;'#013#010+
  '    procedure SetConditionalString(Index : Integer; AValue: TCondition'+
  'alD','estString);'#013#010+
  '  public'#013#010+
  '    Constructor Create(AClass:TConditionalDestStringClass);'#013#010+
  '    Function Add(Const Value : String; ADestPath: String) : TCondition'+
  'alDestString;inline;'#013#010+
  '    Function Add(Const Value : String;const OSes:TOSes; ADestPat','h: S'+
  'tring) : TConditionalDestString;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function Add(Const Value : String;const CPUs:TCPUs; ADestPath: Str'+
  'ing) : TConditionalDestString;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function Add(Const Value',' : String;const CPUs:TCPUs;const OSes:TO'+
  'Ses; ADestPath: String) : TConditionalDestString;'#013#010+
  '    Property ConditionalStrings[Index : Integer] : TConditionalDestStr'+
  'ing Read GetConditionalString Write SetConditionalString; default;'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  ' ',' { TNotifyEventCollection }'#013#010+
  #013#010+
  '  TNotifyEventAction = (neaBeforeCompile, neaAfterCompile, neaBeforeIn'+
  'stall, neaAfterInstall,'#013#010+
  '                        neaBeforeClean, neaAfterClean, neaBeforeArchiv'+
  'e, neaAfterArchive,'#013#010+
  '                       ',' neaBeforeManifest, neaAfterManifest, neaBefo'+
  'rePkgList, neaAfterPkgList,'#013#010+
  '                        neaBeforeUnInstall, neaAfterUnInstall,'#013#010+
  '                        neaBeforeCreateBuildEngine, neaAfterCreateBuil'+
  'dengine);'#013#010+
  #013#010+
  '  TNotifyEventActio','nSet = set of TNotifyEventAction;'#013#010+
  #013#010+
  '  TNotifyEventItem = class(TCollectionItem)'#013#010+
  '  private'#013#010+
  '    FOnAction: TNotifyEventAction;'#013#010+
  '    FOnEvent: TNotifyEvent;'#013#010+
  '    FOnProcEvent: TNotifyProcEvent;'#013#010+
  '  public'#013#010+
  '    property OnAction: TNotifyEvent','Action read FOnAction write FOnAc'+
  'tion;'#013#010+
  '    property OnEvent: TNotifyEvent read FOnEvent write FOnEvent;'#013#010+
  '    property OnProcEvent: TNotifyProcEvent read FOnProcEvent write FOn'+
  'ProcEvent;'#013#010+
  '    procedure CallEvent(Sender: TObject);'#013#010+
  '  end;'#013#010+
  #013,#010+
  '  { TNotifyEventEnumerator }'#013#010+
  #013#010+
  '  TNotifyEventEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TNotifyEventItem;'#013#010+
  '    property Current: TNotifyEventItem read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  TNotifyEventCollection = ','class(TCollection)'#013#010+
  '  private'#013#010+
  '    FSupportedActionSet: TNotifyEventActionSet;'#013#010+
  '  public'#013#010+
  '    constructor create(ASupportedActionSet: TNotifyEventActionSet);'#013+
  #010+
  '    Function GetEnumerator : TNotifyEventEnumerator;'#013#010+
  '    procedure AppendEvent(A','nAction: TNotifyEventAction; AnEvent: TNo'+
  'tifyEvent);'#013#010+
  '    procedure AppendProcEvent(AnACtion: TNotifyEventAction; AnProcEven'+
  't: TNotifyProcEvent);'#013#010+
  '    procedure CallEvents(AnAction: TNotifyEventAction; Sender: TObject'+
  ');'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TDict','ionary }'#013#010+
  #013#010+
  '  TReplaceFunction = Function (Const AName,Args : String) : String of '+
  'Object;'#013#010+
  #013#010+
  '  TDictionary = Class(TComponent)'#013#010+
  '  private'#013#010+
  '    FList : TStringList;'#013#010+
  '    Procedure ClearItem(Idx : Integer);'#013#010+
  '  Public'#013#010+
  '    Constructor Create(A','Owner : TComponent); override;'#013#010+
  '    Destructor Destroy;override;'#013#010+
  '    Procedure AddVariable(const AName,Value : String);'#013#010+
  '    Procedure AddFunction(const AName : String; FReplacement : TReplac'+
  'eFunction);'#013#010+
  '    Procedure RemoveItem(const ANam','e : String);'#013#010+
  '    Function GetValue(AName : String) : String;'#013#010+
  '    Function GetValue(const AName,Args : String) : String; virtual;'#013+
  #010+
  '    Function ReplaceStrings(Const ASource : String; Const MaxDepth: In'+
  'teger = 10) : String; virtual;'#013#010+
  '    Fu','nction Substitute(Const Source : String; const Macros : Array '+
  'of string) : String; virtual;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TPackageDictionary }'#013#010+
  #013#010+
  '  TPackageDictionary = Class(TDictionary)'#013#010+
  '  private'#013#010+
  '    FMasterDictionary: TDictionary;'#013#010+
  '  Public'#013#010+
  '    Func','tion GetValue(const AName,Args : String) : String; override;'+
  #013#010+
  '    property MasterDictionary: TDictionary read FMasterDictionary writ'+
  'e FMasterDictionary;'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  { TDependency }'#013#010+
  '  TDependency = Class(TConditionalString)'#013#010+
  '  private'#013#010+
  ' ','   FDependencyType : TDependencyType;'#013#010+
  '    // Package, Unit'#013#010+
  '    FTarget : TObject;'#013#010+
  '    FVersion : TFPVersion;'#013#010+
  '    FRequireChecksum : Cardinal;'#013#010+
  '    // Filenames, Includes'#013#010+
  '    FTargetFileName : String;'#013#010+
  '    Function GetVersion : string;'#013,#010+
  '    Procedure SetVersion(const V : string);'#013#010+
  '  Public'#013#010+
  '    Constructor Create(aCollection : TCollection);override;'#013#010+
  '    Procedure Assign(aSource : TPersistent);  override;'#013#010+
  '    Destructor Destroy;override;'#013#010+
  '    Property Target : TObject Re','ad FTarget Write FTarget;'#013#010+
  '    Property DependencyType : TDependencyType Read FDependencyType;'#013+
  #010+
  '    Property TargetFileName : String Read FTargetFileName Write FTarge'+
  'tFileName;'#013#010+
  '    Property Version : String Read GetVersion Write SetVersion',';'#013#010+
  '    Property RequireChecksum : Cardinal Read FRequireChecksum Write FR'+
  'equireChecksum;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  TResourceFile = Class(TConditionalString);'#013#010+
  #013#010+
  '  { TPackageVariant }'#013#010+
  #013#010+
  '  TPackage = Class;'#013#010+
  '  TPackageVariant = class(TNamedItem)'#013#010+
  '  priva','te'#013#010+
  '    FOptions: TStrings;'#013#010+
  '    FTargets: TTargets;'#013#010+
  '    FIncludePath: TConditionalStrings;'#013#010+
  '    FSourcePath: TConditionalStrings;'#013#010+
  '  public'#013#010+
  '    constructor Create(ACollection: TCollection); override;'#013#010+
  '    destructor Destroy; override;'#013#010+
  ' ','   Procedure AddOption(const aValue : string);'#013#010+
  '    property Options: TStrings read FOptions;'#013#010+
  '    Property IncludePath : TConditionalStrings Read FIncludePath;'#013#010+
  '    Property SourcePath : TConditionalStrings Read FSourcePath;'#013#010+
  '    property ','Targets: TTargets read FTargets;'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  { TPackageVariantEnumerator }'#013#010+
  #013#010+
  '  TPackageVariantEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TPackageVariant;'#013#010+
  '    property Current: TPackageVariant read Get','Current;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TPackageVariants }'#013#010+
  #013#010+
  '  TPackageVariants = class(TNamedCollection)'#013#010+
  '  private'#013#010+
  '    FActivePackageVariantName: string;'#013#010+
  '    FAutoAddToPackage: boolean;'#013#010+
  '    FDefaultPackageVariantName: string;'#013#010+
  '    FIsInheritable: boo','lean;'#013#010+
  '    FMasterPackage: TPackage;'#013#010+
  '    FName: string;'#013#010+
  '    function GetActivePackageVariant: TPackageVariant;'#013#010+
  '    function GetDefaultPackageVariant: TPackageVariant;'#013#010+
  '    procedure SetActivePackageVariantName(AValue: string);'#013#010+
  '    proce','dure SetDefaultPackageVariantName(AValue: string);'#013#010+
  '  public'#013#010+
  '    function Add(AName: String): TPackageVariant; overload; virtual;'#013+
  #010+
  '    Function GetEnumerator :  TPackageVariantEnumerator;'#013#010+
  '    property Name: string read FName write FName;'#013,#010+
  '    property MasterPackage: TPackage read FMasterPackage;'#013#010+
  '    property DefaultPackageVariant: TPackageVariant read GetDefaultPac'+
  'kageVariant;'#013#010+
  '    property ActivePackageVariant: TPackageVariant read GetActivePacka'+
  'geVariant;'#013#010+
  '    property D','efaultPackageVariantName: string read FDefaultPackageV'+
  'ariantName write SetDefaultPackageVariantName;'#013#010+
  '    property ActivePackageVariantName: string read FActivePackageVaria'+
  'ntName write SetActivePackageVariantName;'#013#010+
  '    property IsInheritabl','e: boolean read FIsInheritable;'#013#010+
  '    property AutoAddToPackage: boolean read FAutoAddToPackage;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TDependencyEnumerator }'#013#010+
  #013#010+
  '  TDependencyEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TDependency',';'#013#010+
  '    property Current: TDependency read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TDependencies }'#013#010+
  #013#010+
  '  TDependencies = Class(TConditionalStrings)'#013#010+
  '  Private'#013#010+
  '    function GetDependency(Index : Integer): TDependency;'#013#010+
  '    procedure SetDependency(Index : ','Integer; const AValue: TDependen'+
  'cy);'#013#010+
  '  Public'#013#010+
  '    Function Add(Const Value : String) : TDependency;inline;'#013#010+
  '    Function Add(Const Value : String;const OSes:TOSes) : TDependency;'+
  'inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function Add(Const',' Value : String;const CPUs:TCPUs) : TDependenc'+
  'y;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function Add(Const Value : String;const CPUs:TCPUs;const OSes:TOSe'+
  's) : TDependency;'#013#010+
  '    Function AddUnit(Const Value : String) : TDependency;inline;'#013,#010+
  '    Function AddUnit(Const Value : String;const OSes:TOSes) : TDepende'+
  'ncy;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function AddUnit(Const Value : String;const CPUs:TCPUs) : TDepende'+
  'ncy;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function Ad','dUnit(Const Value : String;const CPUs:TCPUs;const OSe'+
  's:TOSes) : TDependency;'#013#010+
  '    Function AddInclude(Const Value : String) : TDependency;inline;'#013+
  #010+
  '    Function AddInclude(Const Value : String;const OSes:TOSes) : TDepe'+
  'ndency;inline;'#013#010+
  '{$ifdef',' cpu_only_overloads}'#013#010+
  '    Function AddInclude(Const Value : String;const CPUs:TCPUs) : TDepe'+
  'ndency;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function AddInclude(Const Value : String;const CPUs:TCPUs;const OS'+
  'es:TOSes) : TDependency;'#013#010+
  '    Fun','ction GetEnumerator :  TDependencyEnumerator;'#013#010+
  '    Property Dependencies[Index : Integer] : TDependency Read GetDepen'+
  'dency Write SetDependency; default;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TResourceFiles }'#013#010+
  #013#010+
  '  TResourceFiles = Class(TConditionalStrings)'#013#010+
  '  pub','lic'#013#010+
  '    Procedure GetInstallFiles(AList : TStrings; const APrefixU, APrefi'+
  'xB : String; ACPU:TCPU; AOS : TOS); virtual;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TTarget }'#013#010+
  #013#010+
  '  TTarget = Class(TNamedItem)'#013#010+
  '  private'#013#010+
  '    FInstall : Boolean;'#013#010+
  '    FAfterClean: TNotifyE','vent;'#013#010+
  '    FAfterCompile: TNotifyEvent;'#013#010+
  '    FBeforeClean: TNotifyEvent;'#013#010+
  '    FBeforeCompile: TNotifyEvent;'#013#010+
  '    FCPUs: TCPUs;'#013#010+
  '    FIsFPMakePlugin: Boolean;'#013#010+
  '    FOSes: TOSes;'#013#010+
  '    FMode: TCompilerMode;'#013#010+
  '    FResourceStrings: Boolean;'#013#010+
  '   ',' FObjectPath,'#013#010+
  '    FUnitPath,'#013#010+
  '    FIncludePath : TConditionalStrings;'#013#010+
  '    FSubTargets: TRTLStringDynArray;'#013#010+
  '    FDependencies : TDependencies;'#013#010+
  '    FResourceFiles : TResourceFiles;'#013#010+
  '    FCommands : TCommands;'#013#010+
  '    FDirectory: String;'#013#010+
  '   ',' FExtension: String;'#013#010+
  '    FExeName : String;'#013#010+
  '    FTargetSourceFileName : String;'#013#010+
  '    FFileType: TFileType;'#013#010+
  '    FOptions: TStrings;'#013#010+
  '    FFPCTarget: String;'#013#010+
  '    FTargetState: TTargetState;'#013#010+
  '    FTargetType: TTargetType;'#013#010+
  '    function Get','Options: TStrings;'#013#010+
  '    procedure SetOptions(const AValue: TStrings);'#013#010+
  '  Protected'#013#010+
  '    Function GetSourceFileName : String; virtual;'#013#010+
  '    Function GetUnitFileName : String; virtual;'#013#010+
  '    function GetUnitLibFileName(AOS: TOS): String; virtu','al;'#013#010+
  '    Function GetObjectFileName : String; virtual;'#013#010+
  '    Function GetLTOFileName : String; virtual;'#013#010+
  '    Function GetBinFileBase: String;'#013#010+
  '    function GetRSTFileName : String; Virtual;'#013#010+
  '    function GetRSJFileName : String; Virtual;'#013#010+
  '  ','  function GetImportLibFileName(AOS : TOS) : String; Virtual;'#013#010+
  '    Function GetProgramFileName(AOS : TOS) : String; Virtual;'#013#010+
  '    Function GetProgramDebugFileName(AOS : TOS) : String; Virtual;'#013+
  #010+
  '    Function GetLibraryFileName(AOS : TOS) : S','tring; Virtual;'#013#010+
  '    Function GetLibraryDebugFileName(AOS : TOS) : String; Virtual;'#013+
  #010+
  '  Public'#013#010+
  '    Constructor Create(ACollection : TCollection); override;'#013#010+
  '    Destructor Destroy; override;'#013#010+
  '    procedure AssignTo(Dest: TPersistent); overr','ide;'#013#010+
  '    Function  GetOutputFileName (AOs : TOS) : String; Virtual;'#013#010+
  '    Function HaveOptions : Boolean;'#013#010+
  '    Procedure AddOption(const aValue : string);'#013#010+
  '    Function SubTargetAllowed(Const aSubTarget : String) : Boolean;'#013+
  #010+
  '    Function Su','bTargetsAsString: String;'#013#010+
  '    procedure SetName(const AValue: String);override;'#013#010+
  '    procedure SetExeName(const AValue: String);'#013#010+
  '    // Deprecated API'#013#010+
  '    Procedure GetCleanFiles(List : TStrings; const APrefixU, APrefixB '+
  ': String; ACPU:T','CPU; AOS : TOS; const aSubTarget : String); virtual;'+
  ' deprecated '#039'use TcompileTarget instead'#039';'#013#010+
  '    Procedure GetArchiveFiles(List : TStrings; ACPU:TCPU; AOS : TOS); '+
  'virtual; deprecated '#039'use TcompileTarget instead'#039';'#013#010+
  '    Procedure GetInstall','Files(List : TStrings; const APrefixU, APref'+
  'ixB : String; ACPU:TCPU; AOS : TOS; const aSubTarget : String); virtua'+
  'l; deprecated '#039'use TcompileTarget instead'#039';'#013#010+
  '    Procedure GetCleanFiles(List : TStrings; const APrefixU, APrefixB '+
  ': String; c','onst aTarget : TcompileTarget); virtual;'#013#010+
  '    Procedure GetInstallFiles(List : TStrings; const APrefixU, APrefix'+
  'B : String; const aTarget : TCompileTarget); virtual;'#013#010+
  '    Procedure GetArchiveFiles(List : TStrings; const aTarget : TCompil'+
  'eTa','rget); virtual;'#013#010+
  '    Property Dependencies : TDependencies Read FDependencies;'#013#010+
  '    Property ResourceFiles: TResourceFiles read FResourceFiles;'#013#010+
  '    Property Commands : TCommands Read FCommands;'#013#010+
  '    Property State : TTargetState Read FTarg','etState;'#013#010+
  '    Property TargetType : TTargetType Read FTargetType Write FTargetTy'+
  'pe;'#013#010+
  '    Property OSes : TOSes Read FOSes Write FOSes;'#013#010+
  '    Property CPUs : TCPUs Read FCPUs Write FCPUs;'#013#010+
  '    Property SubTargets : TRTLStringDynArray Read FSu','bTargets Write '+
  'FSubTargets;'#013#010+
  '    Property Mode : TCompilerMode Read FMode Write FMode;'#013#010+
  '    Property Options : TStrings Read GetOptions Write SetOptions;'#013#010+
  '    Property SourceFileName: String Read GetSourceFileName ;'#013#010+
  '    Property UnitFileNa','me : String Read GetUnitFileName;'#013#010+
  '    Property ObjectFileName : String Read GetObjectFileName;'#013#010+
  '    Property LTOFileName : String Read GetLTOFileName;'#013#010+
  '    Property RSTFileName : String Read GetRSTFileName;'#013#010+
  '    Property RSJFileName : Stri','ng Read GetRSJFileName;'#013#010+
  '    Property FPCTarget : String Read FFPCTarget Write FFPCTarget;'#013#010+
  '    Property Extension : String Read FExtension Write FExtension;'#013#010+
  '    Property FileType : TFileType Read FFileType Write FFileType;'#013#010+
  '    Property D','irectory : String Read FDirectory Write FDirectory;'#013+
  #010+
  '    Property ResourceStrings : Boolean Read FResourceStrings Write FRe'+
  'sourceStrings;'#013#010+
  '    Property Install : Boolean Read FInstall Write FInstall;'#013#010+
  '    Property TargetSourceFileName: Stri','ng Read FTargetSourceFileName'+
  ';'#013#010+
  '    Property ObjectPath : TConditionalStrings Read FObjectPath;'#013#010+
  '    Property UnitPath : TConditionalStrings Read FUnitPath;'#013#010+
  '    Property IncludePath : TConditionalStrings Read FIncludePath;'#013#010+
  '    Property Is','FPMakePlugin : Boolean read FIsFPMakePlugin write FIs'+
  'FPMakePlugin;'#013#010+
  '    // Events.'#013#010+
  '    Property BeforeCompile : TNotifyEvent Read FBeforeCompile Write FB'+
  'eforeCompile;'#013#010+
  '    Property AfterCompile : TNotifyEvent Read FAfterCompile Write FAft'+
  'e','rCompile;'#013#010+
  '    Property BeforeClean : TNotifyEvent Read FBeforeClean Write FBefor'+
  'eClean;'#013#010+
  '    Property AfterClean : TNotifyEvent Read FAfterClean Write FAfterCl'+
  'ean;'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  { TTargetEnumerator }'#013#010+
  #013#010+
  '  TTargetEnumerator = Class(TCollec','tionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TTarget;'#013#010+
  '    property Current: TTarget read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TTargets }'#013#010+
  #013#010+
  '  TTargets = Class(TNamedCollection)'#013#010+
  '  private'#013#010+
  '    function GetTargetItem(Index : Integer): TTarget;',#013#010+
  '    function GetTarget(const AName : String): TTarget;'#013#010+
  '    procedure SetTargetItem(Index : Integer; const AValue: TTarget);'#013+
  #010+
  '  Public'#013#010+
  '    Function AddUnit(Const AUnitName : String) : TTarget;inline;'#013#010+
  '    Function AddUnit(Const AUnitName',' : String;const OSes:TOSes) : TT'+
  'arget;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function AddUnit(Const AUnitName : String;const CPUs:TCPUs) : TTar'+
  'get;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function AddUnit(Const AUnitName : String;const ','CPUs:TCPUs;const'+
  ' OSes:TOSes) : TTarget;'#013#010+
  '    Function AddImplicitUnit(Const AUnitName : String;InstallUnit:bool'+
  'ean=true) : TTarget;inline;'#013#010+
  '    Function AddImplicitUnit(Const AUnitName : String;const OSes:TOSes'+
  ';InstallUnit:boolean=true) : T','Target;inline;'#013#010+
  '    Function AddImplicitUnit(Const AUnitName : String;const CPUs:TCPUs'+
  ';InstallUnit:boolean=true) : TTarget;inline;'#013#010+
  '    Function AddImplicitUnit(Const AUnitName : String;const CPUs:TCPUs'+
  ';const OSes:TOSes;InstallUnit:boolean=','true) : TTarget;'#013#010+
  '    Function AddProgram(Const AProgramName : String) : TTarget;inline;'+
  #013#010+
  '    Function AddProgram(Const AProgramName : String;const OSes:TOSes) '+
  ': TTarget;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function AddProgram(Const AP','rogramName : String;const CPUs:TCPUs'+
  ') : TTarget;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function AddProgram(Const AProgramName : String;const CPUs:TCPUs;c'+
  'onst OSes:TOSes) : TTarget;'#013#010+
  '    Function AddLibrary(Const ALibraryName : String) : ','TTarget;inlin'+
  'e;'#013#010+
  '    Function AddLibrary(Const ALibraryName : String;const OSes:TOSes) '+
  ': TTarget;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function AddLibrary(Const ALibraryName : String;const CPUs:TCPUs) '+
  ': TTarget;inline;'#013#010+
  '{$endif cpu_only','_overloads}'#013#010+
  '    Function AddLibrary(Const ALibraryName : String;const CPUs:TCPUs;c'+
  'onst OSes:TOSes) : TTarget;'#013#010+
  '    Function AddExampleUnit(Const AUnitName : String) : TTarget;inline'+
  ';'#013#010+
  '    Function AddExampleUnit(Const AUnitName : String;co','nst OSes:TOSe'+
  's) : TTarget;inline;'#013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  '    Function AddExampleUnit(Const AUnitName : String;const CPUs:TCPUs)'+
  ' : TTarget;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function AddExampleUnit(Const AUnitName : String;cons','t CPUs:TCPU'+
  's;const OSes:TOSes) : TTarget;'#013#010+
  '    Function AddExampleProgram(Const AProgramName : String) : TTarget;'+
  'inline;'#013#010+
  '    Function AddExampleProgram(Const AProgramName : String;const OSes:'+
  'TOSes) : TTarget;inline;'#013#010+
  '{$ifdef cpu_only_overl','oads}'#013#010+
  '    Function AddExampleProgram(Const AProgramName : String;const CPUs:'+
  'TCPUs) : TTarget;inline;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  '    Function AddExampleProgram(Const AProgramName : String;const CPUs:'+
  'TCPUs;const OSes:TOSes) : TTarget;'#013#010+
  '  ','  Function GetEnumerator : TTargetEnumerator;'#013#010+
  '    Property Targets[AName : String] : TTarget Read GetTarget; default'+
  ';'#013#010+
  '    Property TargetItems[Index : Integer] : TTarget Read GetTargetItem'+
  ' Write SetTargetItem;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TSource }'#013#010+
  #013#010,
  '  TSource = Class(TNamedItem)'#013#010+
  '  private'#013#010+
  '    FSourceType : TSourceType;'#013#010+
  '    FInstallSourcePath : string;'#013#010+
  '    function GetInstallSourcePath: string;'#013#010+
  '  Public'#013#010+
  '    Constructor Create(ACollection : TCollection); override;'#013#010+
  '    Destructor D','estroy; override;'#013#010+
  '    Procedure GetInstallFiles(List : TStrings); virtual;'#013#010+
  '    property SourceType : TSourceType read FSourceType;'#013#010+
  '    property InstallSourcePath : string read GetInstallSourcePath;'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  '  { TSources }'#013#010+
  #013#010+
  '  { TSourc','eEnumerator }'#013#010+
  #013#010+
  '  TSourceEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010+
  '    function GetCurrent: TSource;'#013#010+
  '    property Current: TSource read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  TSources = Class(TNamedCollection)'#013#010+
  '  private'#013#010+
  '    function GetSou','rceItem(Index : Integer): TSource;'#013#010+
  '    procedure SetSourceItem(Index : Integer; const AValue: TSource);'#013+
  #010+
  '  public'#013#010+
  '    Function AddDoc(const AFiles : String) : TSource;'#013#010+
  '    Function AddDoc(const AFiles : String; AInstallSourcePath : Strin',
  'g) : TSource;'#013#010+
  '    Function AddSrc(const AFiles : String) : TSource;'#013#010+
  '    Function AddExample(const AFiles : String) : TSource;'#013#010+
  '    Function AddExample(const AFiles : String; AInstallSourcePath : St'+
  'ring) : TSource;'#013#010+
  '    Function AddTest(co','nst AFiles : String) : TSource;'#013#010+
  '    Function GetEnumerator : TSourceEnumerator;'#013#010+
  '    procedure AddDocFiles(const AFileMask, ASearchPathPrefix: string; '+
  'Recursive: boolean = False; AInstallSourcePath : String = '#039#039');'#013+
  #010+
  '    procedure AddSrcFile','s(const AFileMask, ASearchPathPrefix: string'+
  '; Recursive: boolean = False);'#013#010+
  '    procedure AddExampleFiles(const AFileMask, ASearchPathPrefix: stri'+
  'ng; Recursive: boolean = False; AInstallSourcePath : String = '#039#039')'+
  ';'#013#010+
  '    procedure AddTestFiles','(const AFileMask, ASearchPathPrefix: strin'+
  'g; Recursive: boolean = False);'#013#010+
  '    Property SourceItems[Index : Integer] : TSource Read GetSourceItem'+
  ' Write SetSourceItem;default;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TPackage }'#013#010+
  #013#010+
  '  TPackage = Class(TNamedItem)'#013#010+
  '  pr','ivate'#013#010+
  '    FAfterArchive: TNotifyEvent;'#013#010+
  '    FAfterArchiveProc: TNotifyProcEvent;'#013#010+
  '    FAfterClean: TNotifyEvent;'#013#010+
  '    FAfterCleanProc: TNotifyProcEvent;'#013#010+
  '    FAfterCompile: TNotifyEvent;'#013#010+
  '    FAfterCompileProc: TNotifyProcEvent;'#013#010+
  '    FAfte','rInstall: TNotifyEvent;'#013#010+
  '    FAfterInstallProc: TNotifyProcEvent;'#013#010+
  '    FAfterManifest: TNotifyEvent;'#013#010+
  '    FAfterManifestProc: TNotifyProcEvent;'#013#010+
  '    FAfterPkgList: TNotifyEvent;'#013#010+
  '    FAfterPkgListProc: TNotifyProcEvent;'#013#010+
  '    FBeforeArchive:',' TNotifyEvent;'#013#010+
  '    FBeforeArchiveProc: TNotifyProcEvent;'#013#010+
  '    FBeforeClean: TNotifyEvent;'#013#010+
  '    FBeforeCleanProc: TNotifyProcEvent;'#013#010+
  '    FBeforeCompile: TNotifyEvent;'#013#010+
  '    FBeforeCompileProc: TNotifyProcEvent;'#013#010+
  '    FBeforeInstall: TNotifyEv','ent;'#013#010+
  '    FBeforeInstallProc: TNotifyProcEvent;'#013#010+
  '    FBeforeManifest: TNotifyEvent;'#013#010+
  '    FBeforeManifestProc: TNotifyProcEvent;'#013#010+
  '    FBeforePkgList: TNotifyEvent;'#013#010+
  '    FBeforePkgListProc: TNotifyProcEvent;'#013#010+
  '    FBuildMode: TBuildMode;'#013#010+
  '    ','FFlags: TStrings;'#013#010+
  '    FIsFPMakeAddIn: boolean;'#013#010+
  '    FNamespaceMap: String;'#013#010+
  '    FSubTargets: TRTLStringDynArray;'#013#010+
  '    FSupportBuildModes: TBuildModes;'#013#010+
  '    FUnitPath,'#013#010+
  '    FObjectPath,'#013#010+
  '    FIncludePath,'#013#010+
  '    FSourcePath,'#013#010+
  '    FExamplePath',','#013#010+
  '    FTestPath,'#013#010+
  '    FCleanFiles   : TConditionalStrings;'#013#010+
  '    FInstallFiles : TConditionalDestStrings;'#013#010+
  '    FDependencies : TDependencies;'#013#010+
  '    FCPUs: TCPUs;'#013#010+
  '    FOSes: TOSes;'#013#010+
  '    FTargetState: TTargetState;'#013#010+
  '    FTargets: TTargets;'#013#010+
  ' ','   FSources: TSources;'#013#010+
  '    FDirectory: String;'#013#010+
  '    FOptions: TStrings;'#013#010+
  '    FTransmitOptions: TStrings;'#013#010+
  '    FFileName: String;'#013#010+
  '    FShortName: String; { Used to generate the short 8.3 zip file name'+
  ', must be 4 characters at most }'#013#010+
  '    F','Author: String;'#013#010+
  '    FLicense: String;'#013#010+
  '    FHomepageURL: String;'#013#010+
  '    FDownloadURL: String;'#013#010+
  '    FVersion: TFPVersion;'#013#010+
  '    FEmail : String;'#013#010+
  '    FNeedLibC : Boolean;'#013#010+
  '    FCommands : TCommands;'#013#010+
  '    FDescriptionFile : String;'#013#010+
  '    FDescri','ption : String;'#013#010+
  '    FInstalledChecksum : Cardinal;'#013#010+
  '    FUnitsOutputDir: String;'#013#010+
  '    FPackageUnitInstallDir: String;'#013#010+
  '    // Cached directory of installed packages'#013#010+
  '    FUnitDir : String;'#013#010+
  '    FUnitConfigFileName : String;'#013#010+
  '    // Used by',' buildunits'#013#010+
  '    FBUTargets: TTargets;'#013#010+
  '    FBUTarget: TTarget;'#013#010+
  '    // Used to identify if package is being processed by a thread'#013#010+
  '    FProcessing : boolean;'#013#010+
  '    // Dictionary'#013#010+
  '    FDictionary : TDictionary;'#013#010+
  '    // Is set when all source','files are found'#013#010+
  '    FAllFilesResolved: boolean;'#013#010+
  '    FPackageVariants: TFPList;'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '    FResolveDirsCS: TRTLCriticalSection;'#013#010+
  '{$endif}'#013#010+
  '    procedure ChangePaths(Aliases: TStrings; aTarget: TCompileTarget);'+
  #013#010+
  '    Functi','on GetDescription : string;'#013#010+
  '    function GetDictionary: TDictionary;'#013#010+
  '    Function GetFileName : string;'#013#010+
  '    Function GetShortName : string;'#013#010+
  '    function GetOptions: TStrings;'#013#010+
  '    function GetTransmitOptions: TStrings;'#013#010+
  '    Function Get','Version : string;'#013#010+
  '    procedure SetOptions(const AValue: TStrings);'#013#010+
  '    procedure SetTransmitOptions(AValue: TStrings);'#013#010+
  '    Procedure SetVersion(const V : string);'#013#010+
  '    procedure TransformAliases(Aliases: TStrings);'#013#010+
  '  Protected'#013#010+
  '    pro','cedure SetName(const AValue: String);override;'#013#010+
  '    procedure SaveUnitConfigToStringList(Const AStringList: TStrings;A'+
  'CPU:TCPU;AOS:TOS); virtual;'#013#010+
  '    property Dictionary: TDictionary read GetDictionary;'#013#010+
  '    property PackageVariantsList: T','FPList read FPackageVariants;'#013+
  #010+
  '  Public'#013#010+
  '    constructor Create(ACollection: TCollection); override;'#013#010+
  '    destructor destroy; override;'#013#010+
  '    Function HaveOptions : Boolean;'#013#010+
  '    // Deprecated'#013#010+
  '    Function  GetUnitsOutputDir(ACPU:TCPU; AOS ',': TOS; const aSubTarg'+
  'et : String ):String; deprecated '#039'use TCompileTarget version inste'+
  'ad'#039';'#013#010+
  '    Function  GetUnitConfigOutputFilename(ACPU:TCPU; AOS : TOS; const '+
  'aSubTarget : String):String; deprecated '#039'use TCompileTarget versio'+
  'n instead'#039';',#013#010+
  '    Function  GetBinOutputDir(ACPU:TCPU; AOS : TOS; const aSubTarget :'+
  ' String) : String; deprecated '#039'use TCompileTarget version instead'#039+
  ';'#013#010+
  '    Procedure GetCleanFiles(List : TStrings; ACPU:TCPU; AOS : TOS; con'+
  'st aSubTarget : String); virt','ual; deprecated '#039'use TCompileTarget'+
  ' version instead'#039';'#013#010+
  '    Procedure GetArchiveFiles(List : TStrings; ACPU:TCPU; AOS : TOS); '+
  'virtual;deprecated '#039'use TCompileTarget version instead'#039';'#013#010+
  #013#010+
  '    Function  GetUnitsOutputDir(const aTarget : TCompil','eTarget):Stri'+
  'ng;'#013#010+
  '    Function  GetUnitConfigOutputFilename(const aTarget : TCompileTarg'+
  'et):String;'#013#010+
  '    Procedure InheritPackageVariantsFromDependency(ADependencyPackage:'+
  ' TPackage);'#013#010+
  '    Function  GetPackageVariantsByName(AName: string): T','PackageVaria'+
  'nts;'#013#010+
  '    Procedure SetUnitsOutputDir(AValue: string);'#013#010+
  '    Function  GetPackageUnitInstallDir(ACPU:TCPU; AOS : TOS; const aSu'+
  'bTarget : String):String;'#013#010+
  '    Procedure SetPackageUnitInstallDir(AValue: string);'#013#010+
  '    Function  GetB','inOutputDir(const aTarget : TCompileTarget) : Stri'+
  'ng;'#013#010+
  '    Procedure GetCleanFiles(List : TStrings; const aTarget : TCompileT'+
  'arget); virtual;'#013#010+
  '    procedure GetInstallFiles(List: TStrings;Types : TTargetTypes; con'+
  'st aTarget : TCompileTarget','); virtual;'#013#010+
  '    procedure GetInstallSourceFiles(List: TStrings; SourceTypes : TSou'+
  'rceTypes; TargetTypes : TTargetTypes); virtual;'#013#010+
  '    Procedure GetArchiveFiles(List : TStrings; aTarget : TCompileTarge'+
  't); virtual;'#013#010+
  '    Procedure GetArchive','SourceFiles(List : TStrings); virtual;'#013#010+
  '    Procedure GetManifest(Manifest : TStrings);'#013#010+
  '    Procedure ListPackage(PkgList : TStrings);'#013#010+
  '    Procedure AddPackageVariant(APackageVariant: TPackageVariants);'#013+
  #010+
  '    procedure ApplyPackageVariantT','oCompilerOptions(ACompilerOptions:'+
  ' tstrings);'#013#010+
  '    procedure SetDefaultPackageVariant;'#013#010+
  '    procedure LoadUnitConfigFromFile(Const AFileName: String);'#013#010+
  '    procedure SaveUnitConfigToFile(Const AFileName: String;ACPU:TCPU;A'+
  'OS:TOS);'#013#010+
  '    proc','edure EnterResolveDirsCS;'#013#010+
  '    procedure LeaveResolveDirsCS;'#013#010+
  '    Function AddTargetsFromDir(const aDirectory : String; const aMask '+
  ': String = '#039#039') : longint;'#013#010+
  '    // applies namespaces if map is set'#013#010+
  '    procedure ApplyNameSpaces(aEngine : ','TBuildEngine; aFileName : st'+
  'ring; aTarget : TCompileTarget);'#013#010+
  '    procedure ApplyNameSpaces(aEngine : TBuildEngine; aTarget : TCompi'+
  'leTarget);'#013#010+
  '    Function SubTargetAllowed(Const aSubTarget : String) : Boolean;'#013+
  #010+
  '    Property Version : Stri','ng Read GetVersion Write SetVersion;'#013#010+
  '    Property FileName : String Read GetFileName Write FFileName;'#013#010+
  '    Property ShortName : String Read GetShortName Write FShortName;'#013+
  #010+
  '    Property HomepageURL : String Read FHomepageURL Write FHomepage','U'+
  'RL;'#013#010+
  '    Property DownloadURL : String Read FDownloadURL Write FDownloadURL'+
  ';'#013#010+
  '    Property Email : String Read FEmail Write FEmail;'#013#010+
  '    Property Author : String Read FAuthor Write FAuthor;'#013#010+
  '    Property License : String Read FLicense Writ','e FLicense;'#013#010+
  '    Property Directory : String Read FDirectory Write FDirectory;'#013#010+
  '    Property Description : String Read GetDescription Write FDescripti'+
  'on;'#013#010+
  '    Property DescriptionFile : String Read FDescriptionFile Write FDes'+
  'criptionFile;'#013#010,
  '    Property InstalledChecksum : Cardinal Read FInstalledChecksum Writ'+
  'e FInstalledChecksum;'#013#010+
  '    Property IsFPMakeAddIn: boolean read FIsFPMakeAddIn write FIsFPMak'+
  'eAddIn;'#013#010+
  '    Property SupportBuildModes: TBuildModes read FSupportBuildModes ','w'+
  'rite FSupportBuildModes;'#013#010+
  '    Property BuildMode: TBuildMode read FBuildMode;'#013#010+
  '    Property Flags: TStrings read FFlags;'#013#010+
  '    Property PackageVersion: TFPVersion read FVersion;'#013#010+
  '    // Options which are passed to the compiler for packages ','which d'+
  'epend on'#013#010+
  '    // this package.'#013#010+
  '    Property TransmitOptions: TStrings Read GetTransmitOptions Write S'+
  'etTransmitOptions;'#013#010+
  '    // Compiler options.'#013#010+
  '    Property OSes : TOSes Read FOSes Write FOSes;'#013#010+
  '    Property CPUs : TCPUs Read FCP','Us Write FCPUs;'#013#010+
  '    Property SubTargets : TRTLStringDynArray Read FSubTargets Write FS'+
  'ubTargets;'#013#010+
  '    Property NeedLibC : Boolean Read FNeedLibC Write FNeedLibC;'#013#010+
  '    Property Options: TStrings Read GetOptions Write SetOptions;'#013#010+
  '    Proper','ty UnitPath : TConditionalStrings Read FUnitPath;'#013#010+
  '    Property ObjectPath : TConditionalStrings Read FObjectPath;'#013#010+
  '    Property IncludePath : TConditionalStrings Read FIncludePath;'#013#010+
  '    Property SourcePath : TConditionalStrings Read FSourc','ePath;'#013#010+
  '    Property ExamplePath : TConditionalStrings Read FExamplePath;'#013#010+
  '    Property TestPath : TConditionalStrings Read FTestPath;'#013#010+
  '    // Targets and dependencies'#013#010+
  '    Property InstallFiles : TConditionalDestStrings Read FInstallFiles'+
  ';',#013#010+
  '    Property CleanFiles : TConditionalStrings Read FCleanFiles;'#013#010+
  '    Property Dependencies : TDependencies Read FDependencies;'#013#010+
  '    Property Commands : TCommands Read FCommands;'#013#010+
  '    Property State : TTargetState Read FTargetState Write F','TargetSta'+
  'te;'#013#010+
  '    Property Targets : TTargets Read FTargets;'#013#010+
  '    Property Sources : TSources Read FSources;'#013#010+
  '    Property UnitDir : String Read FUnitDir Write FUnitDir;'#013#010+
  '    Property UnitConfigFileName: String read FUnitConfigFileName writ',
  'e FUnitConfigFileName;'#013#010+
  '    Property NamespaceMap : String Read FNamespaceMap Write FNameSpace'+
  'Map;'#013#010+
  '    // events'#013#010+
  '    Property BeforeCompile : TNotifyEvent Read FBeforeCompile Write FB'+
  'eforeCompile;'#013#010+
  '    Property BeforeCompileProc : TNotify','ProcEvent Read FBeforeCompil'+
  'eProc write FBeforeCompileProc;'#013#010+
  '    Property AfterCompile : TNotifyEvent Read FAfterCompile Write FAft'+
  'erCompile;'#013#010+
  '    Property AfterCompileProc : TNotifyProcEvent Read FAfterCompilePro'+
  'c Write FAfterCompileProc;'#013,#010+
  '    Property BeforeInstall : TNotifyEvent Read FBeforeInstall Write FB'+
  'eforeInstall;'#013#010+
  '    Property BeforeInstallProc : TNotifyProcEvent Read FBeforeInstallP'+
  'roc Write FBeforeInstallProc;'#013#010+
  '    Property AfterInstall : TNotifyEvent Read FAfterI','nstall Write FA'+
  'fterInstall;'#013#010+
  '    Property AfterInstallProc : TNotifyProcEvent Read FAfterInstallPro'+
  'c Write FAfterInstallProc;'#013#010+
  '    Property BeforeClean : TNotifyEvent Read FBeforeClean Write FBefor'+
  'eClean;'#013#010+
  '    Property BeforeCleanProc : TNo','tifyProcEvent Read FBeforeCleanPro'+
  'c Write FBeforeCleanProc;'#013#010+
  '    Property AfterClean : TNotifyEvent Read FAfterClean Write FAfterCl'+
  'ean;'#013#010+
  '    Property AfterCleanProc : TNotifyProcEvent Read FAfterCleanProc Wr'+
  'ite FAfterCleanProc;'#013#010+
  '    Propert','y BeforeArchive : TNotifyEvent Read FBeforeArchive Write '+
  'FBeforeArchive;'#013#010+
  '    Property BeforeArchiveProc : TNotifyProcEvent Read FBeforeArchiveP'+
  'roc Write FBeforeArchiveProc;'#013#010+
  '    Property AfterArchive : TNotifyEvent Read FAfterArchive Write',' FA'+
  'fterArchive;'#013#010+
  '    Property AfterArchiveProc : TNotifyProcEvent Read FAfterArchivePro'+
  'c Write FAfterArchiveProc;'#013#010+
  '    Property BeforeManifest : TNotifyEvent Read FBeforeManifest Write '+
  'FBeforeManifest;'#013#010+
  '    Property BeforeManifestProc : TNo','tifyProcEvent Read FBeforeManif'+
  'estProc Write FBeforeManifestProc;'#013#010+
  '    Property AfterManifest : TNotifyEvent Read FAfterManifest Write FA'+
  'fterManifest;'#013#010+
  '    Property AfterManifestProc : TNotifyProcEvent Read FAfterManifestP'+
  'roc Write FAfterMa','nifestProc;'#013#010+
  '    Property BeforePkgList : TNotifyEvent Read FBeforePkgList Write FB'+
  'eforePkgList;'#013#010+
  '    Property BeforePkgListProc : TNotifyProcEvent Read FBeforePkgListP'+
  'roc Write FBeforePkgListProc;'#013#010+
  '    Property AfterPkgList : TNotifyEvent ','Read FAfterPkgList Write FA'+
  'fterPkgList;'#013#010+
  '    Property AfterPkgListProc : TNotifyProcEvent Read FAfterPkgListPro'+
  'c Write FAfterPkgListProc;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TPackageEnumerator }'#013#010+
  #013#010+
  '  TPackageEnumerator = Class(TCollectionEnumerator)'#013#010+
  '  public'#013#010,
  '    function GetCurrent: TPackage;'#013#010+
  '    property Current: TPackage read GetCurrent;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TPackages }'#013#010+
  #013#010+
  '  TPackages = Class(TNamedCollection)'#013#010+
  '  private'#013#010+
  '    function GetPackage(const AName : String): TPackage;'#013#010+
  '    function GetPa','ckageItem(AIndex : Integer): TPackage;'#013#010+
  '    procedure SetPackageItem(AIndex : Integer; const AValue: TPackage)'+
  ';'#013#010+
  '  Public'#013#010+
  '    Function AddPackage(Const AName : String) : TPackage;'#013#010+
  '    Function GetEnumerator : TPackageEnumerator;'#013#010+
  '    Prop','erty Packages[AName : String] : TPackage Read GetPackage ; D'+
  'efault;'#013#010+
  '    Property PackageItems[AIndex : Integer] : TPackage Read GetPackage'+
  'Item Write SetPackageItem;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TCustomDefaults }'#013#010+
  #013#010+
  '  TCustomDefaults = Class(TPersistent)',#013#010+
  '  Private'#013#010+
  '    FArchive: String;'#013#010+
  '    FBuildMode: TBuildMode;'#013#010+
  '    FBuildTarget: TCompileTarget;'#013#010+
  '    FCompiler: String;'#013#010+
  '    FCopy: String;'#013#010+
  '    FFPUnitSourcePath: String;'#013#010+
  '    FIgnoreInvalidOptions: Boolean;'#013#010+
  '    FInstallExamples: Boole','an;'#013#010+
  '    FMkDir: String;'#013#010+
  '    FMove: String;'#013#010+
  '    FNamespaces: Boolean;'#013#010+
  '    FOptions: TStrings;'#013#010+
  '    FCompileTarget : TCompileTarget;'#013#010+
  '    FSourceTarget : TCompileTarget;'#013#010+
  '    FMode : TCompilerMode;'#013#010+
  '    FCompilerDate : String;'#013#010+
  '    FCompi','lerVersion : String;'#013#010+
  '    FFullCompilerVersion : String;'#013#010+
  '    FPrefix: String;'#013#010+
  '    FBaseInstallDir,'#013#010+
  '    FUnitInstallDir,'#013#010+
  '    FUnitConfigFilesInstallDir,'#013#010+
  '    FBinInstallDir,'#013#010+
  '    FLibInstallDir,'#013#010+
  '    FDocInstallDir,'#013#010+
  '    FExamplesInstall','Dir : String;'#013#010+
  '    FSearchPath: TStrings;'#013#010+
  '    FSkipAllPrograms: boolean;'#013#010+
  '    FSkipCrossPrograms: boolean;'#013#010+
  '    FThreadsAmount: integer;'#013#010+
  '    FRemoveTree: String;'#013#010+
  '    FRemoveDir: String;'#013#010+
  '    FRemove: String;'#013#010+
  '    FUnixPaths: Boolean;'#013#010+
  '  ','  FNoFPCCfg: Boolean;'#013#010+
  '    FUseEnvironment: Boolean;'#013#010+
  '    FZipPrefix: String;'#013#010+
  '    FExplicitOSNone: Boolean;'#013#010+
  '    FUnitOutputDirectory: String;'#013#010+
  '    function GetTarget: String;'#013#010+
  '    function SafeExpandFileName(const AFileName: string): stri','ng;'#013+
  #010+
  '    function GetBuildCPU: TCpu;'#013#010+
  '    function GetBuildOS: TOS;'#013#010+
  '    function GetBuildString: String;'#013#010+
  '    function GetFPUnitSourcePath: String;'#013#010+
  '    function GetLocalUnitDir: String;'#013#010+
  '    function GetGlobalUnitDir: String;'#013#010+
  '    functio','n GetBaseInstallDir: String;'#013#010+
  '    function GetBinInstallDir: String;'#013#010+
  '    function GetLibInstallDir: String;'#013#010+
  '    function GetCompiler: String;'#013#010+
  '    function GetDocInstallDir: String;'#013#010+
  '    function GetExamplesInstallDir: String;'#013#010+
  '    functi','on GetOptions: TStrings;'#013#010+
  '    function GetPrefix: String;'#013#010+
  '    function GetSearchPath: TStrings;'#013#010+
  '    function GetUnitInstallDir: String;'#013#010+
  '    function GetUnitConfigFilesInstallDir: String;'#013#010+
  '    procedure SetCompileTarget(AValue: TCompileTa','rget);'#013#010+
  '    procedure SetLocalUnitDir(const AValue: String);'#013#010+
  '    procedure SetGlobalUnitDir(const AValue: String);'#013#010+
  '    procedure IntSetBaseInstallDir(const AValue: String);'#013#010+
  '    procedure SetBaseInstallDir(const AValue: String);'#013#010+
  '    proc','edure SetCPU(const AValue: TCPU);'#013#010+
  '    procedure SetOptions(const AValue: TStrings);'#013#010+
  '    procedure SetOS(const AValue: TOS);'#013#010+
  '    procedure SetPrefix(const AValue: String);'#013#010+
  '    procedure SetSearchPath(AValue: TStrings);'#013#010+
  '    procedure Set','SubTarget(AValue: String);'#013#010+
  '    procedure SetTarget(const AValue: String);'#013#010+
  '    procedure SetUnitInstallDir(const AValue: String);'#013#010+
  '    procedure SetUnitConfigFilesInstallDir(const AValue: String);'#013#010+
  '    procedure SetZipPrefix(AValue: String',');'#013#010+
  '  Protected'#013#010+
  '    procedure RecalcTarget;'#013#010+
  '    Function CmdLineOptions : String;'#013#010+
  '  Public'#013#010+
  '    Constructor Create;'#013#010+
  '    Destructor Destroy; override;'#013#010+
  '    Procedure InitDefaults; virtual;'#013#010+
  '    Function HaveOptions: Boolean;'#013#010+
  '    Procedu','re AddOption(const aValue : string);'#013#010+
  '    function IsBuildDifferentFromTarget: boolean;'#013#010+
  '    procedure CompilerDefaults; virtual;'#013#010+
  '    Procedure LocalInit(Const AFileName : String);'#013#010+
  '    Procedure LoadFromFile(Const AFileName : String);'#013#010+
  '  ','  Procedure SaveToFile(Const AFileName : String);'#013#010+
  '    procedure SaveToStream(S : TStream);virtual;'#013#010+
  '    procedure LoadFromStream(S : TStream);virtual;'#013#010+
  '    // Compile Information'#013#010+
  #013#010+
  '    Property CompileTarget : TCompileTarget Read FCompile','Target Writ'+
  'e SetCompileTarget;'#013#010+
  '    Property Target : String Read GetTarget Write SetTarget;'#013#010+
  '    Property OS : TOS Read FCompileTarget.OS Write SetOS;'#013#010+
  '    Property CPU : TCPU Read FCompileTarget.CPU Write SetCPU;'#013#010+
  '    Property SubTarget :',' String Read FCompileTarget.SubTarget Write '+
  'SetSubTarget;'#013#010+
  '    Property SourceOS : TOS Read FSourceTarget.OS;'#013#010+
  '    Property SourceCPU : TCPU Read FSourceTarget.CPU;'#013#010+
  '    Property CompilerVersion : String read FCompilerVersion;'#013#010+
  '    Property',' CompilerDate : String read FCompilerDate;'#013#010+
  '    Property FullCompilerVersion : String read FFullCompilerVersion;'#013+
  #010+
  '    Property ExplicitOSNone: Boolean read FExplicitOSNone Write FExpli'+
  'citOSNone;'#013#010+
  '    Property BuildString : String read GetBu','ildString;'#013#010+
  '    Property BuildTarget : TCompileTarget Read FBuildTarget;'#013#010+
  '    Property BuildOS : TOS read GetBuildOS;'#013#010+
  '    Property BuildCPU : TCpu read GetBuildCPU;'#013#010+
  '    Property Mode : TCompilerMode Read FMode Write FMode;'#013#010+
  '    Property U','nixPaths : Boolean Read FUnixPaths Write FUnixPaths;'#013+
  #010+
  '    Property Options : TStrings Read GetOptions Write SetOptions;    /'+
  '/ Default compiler options.'#013#010+
  '    Property NoFPCCfg : Boolean Read FNoFPCCfg Write FNoFPCCfg;'#013#010+
  '    // When ThreadsAmo','unt is specified, #threadsamount# worker-threa'+
  'ds are'#013#010+
  '    // created. When such a worker-thread is ready all worker-threads '+
  'are evaluated'#013#010+
  '    // to see if there are idle threads (there is always at least one '+
  'such thread.)'#013#010+
  '    // To each i','dle thread a package is assigned which has to be com'+
  'piled for the'#013#010+
  '    // current target and for which all dependencies are compiled earl'+
  'ier.'#013#010+
  '    // When no package is available the thread remains idle until anot'+
  'her thread'#013#010+
  '    // has fini','shed it'#039's task. Compilation stops when all packag'+
  'es are compiled'#013#010+
  '    // or when an error occurs.'#013#010+
  '    //'#013#010+
  '    // When ThreadsAmount is not specified (-1), all packages are comp'+
  'iled on by one.'#013#010+
  '    // Dependencies are compiled recursively. ','When a package is alre'+
  'ady compiled'#013#010+
  '    // (because some other package was depending on it) the package is'+
  ' skipped.'#013#010+
  '    // When the last package in the list is compiled, the compilation '+
  'stops.'#013#010+
  '    Property ThreadsAmount : integer Read FTh','readsAmount Write FThre'+
  'adsAmount;'#013#010+
  '    // paths etc.'#013#010+
  '    Property LocalUnitDir : String Read GetLocalUnitDir Write SetLocal'+
  'UnitDir;'#013#010+
  '    Property GlobalUnitDir : String Read GetGlobalUnitDir Write SetGlo'+
  'balUnitDir;'#013#010+
  '    property UnitOutput','Directory: String read FUnitOutputDirectory w'+
  'rite FUnitOutputDirectory;'#013#010+
  '    // The SearchPath contains a list of directories in which packages'+
  ' are'#013#010+
  '    // installed. Packages are searched for in order of this list.'#013+
  #010+
  '    Property SearchPath',': TStrings read GetSearchPath write SetSearch'+
  'Path;'#013#010+
  '    Property Prefix : String Read GetPrefix Write SetPrefix;'#013#010+
  '    Property ZipPrefix : String Read FZipPrefix Write SetZipPrefix;'#013+
  #010+
  '    Property BaseInstallDir : String Read GetBaseInstallD','ir Write Se'+
  'tBaseInstallDir;'#013#010+
  '    Property UnitInstallDir : String Read GetUnitInstallDir Write SetU'+
  'nitInstallDir;'#013#010+
  '    Property UnitConfigFilesInstallDir : String Read GetUnitConfigFile'+
  'sInstallDir Write SetUnitConfigFilesInstallDir;'#013#010+
  '    Pr','operty BinInstallDir : String Read GetBinInstallDir Write FBin'+
  'InstallDir;'#013#010+
  '    Property LibInstallDir : String Read GetLibInstallDir Write FLibIn'+
  'stallDir;'#013#010+
  '    Property DocInstallDir : String Read GetDocInstallDir Write FDocIn'+
  'stallDir;'#013#010+
  '   ',' Property ExamplesInstallDir : String Read GetExamplesInstallDir '+
  'Write FExamplesInstallDir;'#013#010+
  '    Property FPUnitSourcePath: String read GetFPUnitSourcePath Write F'+
  'FPUnitSourcePath;'#013#010+
  #013#010+
  '    // Command tools. If not set, internal commands  wil','l be used.'#013+
  #010+
  '    Property Compiler : String Read GetCompiler Write FCompiler; // Co'+
  'mpiler. Defaults to fpc'#013#010+
  '    Property Copy : String Read FCopy Write FCopy;             // copy'+
  ' $(FILES) to $(DEST)'#013#010+
  '    Property Move : String Read FMove Wri','te FMove;             // Mo'+
  've $(FILES) to $(DEST)'#013#010+
  '    Property Remove : String Read FRemove Write FRemove;       // Dele'+
  'te $(FILES)'#013#010+
  '    Property RemoveDir : String Read FRemoveDir Write FRemoveDir;     '+
  '  // Delete $(FILES)'#013#010+
  '    Property R','emoveTree : String Read FRemoveTree Write FRemoveTree;'+
  '       // removes $(DIRECTORY)'#013#010+
  '    Property MkDir : String Read FMkDir write FMkDir;          // Make'+
  ' $(DIRECTORY)'#013#010+
  '    Property Archive : String Read FArchive Write FArchive;    // zip',
  ' $(ARCHIVE) $(FILESORDIRS)'#013#010+
  '    // Misc'#013#010+
  '    Property UseEnvironment : Boolean read FUseEnvironment write FUseE'+
  'nvironment;'#013#010+
  '    Property IgnoreInvalidOptions: Boolean read FIgnoreInvalidOptions '+
  'write FIgnoreInvalidOptions;'#013#010+
  '    Property Bui','ldMode: TBuildMode read FBuildMode write FBuildMode;'+
  #013#010+
  '    Property Namespaces : Boolean Read FNamespaces Write FNameSpaces;'#013+
  #010+
  '    // Installation options'#013#010+
  '    Property InstallExamples: Boolean read FInstallExamples write FIns'+
  'tallExamples;'#013#010+
  ' ','   Property SkipCrossPrograms: boolean read FSkipCrossPrograms writ'+
  'e FSkipCrossPrograms;'#013#010+
  '    Property SkipAllPrograms: boolean read FSkipAllPrograms write FSki'+
  'pAllPrograms;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TBasicDefaults }'#013#010+
  #013#010+
  '  TBasicDefaults = Class(TCusto','mDefaults)'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TFPCDefaults }'#013#010+
  #013#010+
  '  TFPCDefaults = Class(TCustomDefaults)'#013#010+
  '  public'#013#010+
  '    procedure CompilerDefaults; override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TBuildEngine }'#013#010+
  '  TCopyFileProc = procedure(const APackage: TPackage; Const ASourceFil'+
  'eN','ame, ADestFileName : String) of object;'#013#010+
  #013#010+
  '  TBuildEngine = Class(TComponent)'#013#010+
  '  private'#013#010+
  '    // general variables'#013#010+
  '    FCompiler : String;'#013#010+
  '    FStartDir : String;'#013#010+
  '    FForceCompile : Boolean;'#013#010+
  '    FListMode : Boolean;'#013#010+
  '    FVerbose : boo','lean;'#013#010+
  '    FInteractive : boolean;'#013#010+
  '    FProgressMax : integer;'#013#010+
  '    FProgressCount : integer;'#013#010+
  '    FIndentCount : integer;'#013#010+
  '    FExternalPackages : TPackages;'#013#010+
  '    // Events'#013#010+
  '    FOnLog: TLogEvent;'#013#010+
  '    FNotifyEventCollection: TNotifyEvent','Collection;'#013#010+
  '    FOnCopyFile: TCopyFileProc;'#013#010+
  '    FOnFinishCopy: TNotifyEvent;'#013#010+
  #013#010+
  '    FCachedlibcPath: string;'#013#010+
  '    GCCLibWarningIssued : boolean;'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '    FGeneralCriticalSection: TRTLCriticalSection;'#013#010+
  '{$endif NO_THREAD','ING}'#013#010+
  '{$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '    FZipper: TZipper;'#013#010+
  '    FGZFileStream: TGZFileStream;'#013#010+
  '{$endif HAS_UNIT_ZIPPER}'#013#010+
  '{$ifdef HAS_TAR_SUPPORT}'#013#010+
  '    FTarWriter: TTarWriter;'#013#010+
  '{$endif HAS_TAR_SUPPORT}'#013#010+
  '    procedure AddFileToArchive(const APacka','ge: TPackage; Const ASour'+
  'ceFileName, ADestFileName : String);'#013#010+
  '    procedure FinishArchive(Sender: TObject);'#013#010+
  '  Protected'#013#010+
  '    Procedure Error(const Msg : String);'#013#010+
  '    Procedure Error(const Fmt : String; const Args : Array of const);'#013+
  #010+
  '    ','// Internal copy/delete/move/archive/mkdir files'#013#010+
  '    Function  SysDirectoryExists(const ADir:string):Boolean;'#013#010+
  '    Function  SysFileExists(const AFileName:string):Boolean;'#013#010+
  '    Procedure SysCopyFile(Const Src,Dest : String); virtual;'#013#010+
  '    ','Procedure SysMoveFile(Const Src,Dest : String); virtual;'#013#010+
  '    Procedure SysDeleteFile(Const AFileName : String); virtual;'#013#010+
  '    Procedure SysDeleteDirectory(Const ADirectoryName : String); virtu'+
  'al;'#013#010+
  '    Procedure SysDeleteTree(Const ADirecto','ryName : String); virtual;'+
  #013#010+
  '    Procedure SysArchiveFiles(List : TStrings; Const AFileName : Strin'+
  'g); virtual;'#013#010+
  '    procedure LogIndent;'#013#010+
  '    procedure LogUnIndent;'#013#010+
  '    Procedure EnterDir(ADir : String);'#013#010+
  '    Function GetCompiler : String;',#013#010+
  '    Function InstallPackageFiles(APAckage : TPackage; tt : TTargetType'+
  's; Const Dest : String; Const InstallMode: TInstallMode):Boolean;'#013#010+
  '    Procedure InstallUnitConfigFile(APAckage : TPackage; Const Dest : '+
  'String);'#013#010+
  '    function GetUnitC','onfigFilesInstallDir(ABaseDir: string): String;'+
  #013#010+
  #013#010+
  '    Function InstallPackageSourceFiles(APAckage : TPackage; stt : TSou'+
  'rceTypes; ttt : TTargetTypes; Const Dest : String; Const InstallMode: '+
  'TInstallMode):Boolean;'#013#010+
  '    Function FileNewer(co','nst Src,Dest : String) : Boolean;'#013#010+
  '    Procedure LogSearchPath(APackage: TPackage;const ASearchPathName:s'+
  'tring;Path:TConditionalStrings; ACPU:TCPU;AOS:TOS);'#013#010+
  '    Function FindFileInPath(APackage: TPackage; Path:TConditionalStrin'+
  'gs; const AF','ileName:String; var FoundPath:String;ACPU:TCPU;AOS:TOS):'+
  'Boolean;'#013#010+
  #013#010+
  '    procedure GetDirectoriesFromFilelist(const AFileList, ADirectoryLi'+
  'st: TStringList);'#013#010+
  '    procedure AddPackageMacrosToDictionary(const APackage: TPackage; A'+
  'Dictionary: T','Dictionary);'#013#010+
  '    //package commands'#013#010+
  '    function  GetUnitDir(APackage:TPackage):String;'#013#010+
  '    procedure ResolvePackagePaths(APackage:TPackage);'#013#010+
  '    procedure AddDependencyPaths(L: TStrings; DependencyType: TDepende'+
  'ncyType; ATarget: TTarge','t);'#013#010+
  '    procedure AddDependencyUnitPaths(L:TStrings;APackage: TPackage);'#013+
  #010+
  '    procedure AddDependencyTransmittedOptions(Args: TStrings; APackage'+
  ': TPackage);'#013#010+
  #013#010+
  '  Public'#013#010+
  '    Constructor Create(AOwner : TComponent); override;'#013#010+
  '    destructo','r Destroy;override;'#013#010+
  '    function AddPathPrefix(APackage: TPackage; APath: string): string;'+
  #013#010+
  #013#010+
  '    property Verbose : boolean read FVerbose write FVerbose;'#013#010+
  '    property Interactive : boolean read FInteractive write FInteractiv'+
  'e;'#013#010+
  '    Proce','dure ResolveFileNames(APackage : TPackage; ACPU:TCPU;AOS:TO'+
  'S;DoChangeDir:boolean=true; WarnIfNotFound:boolean=true);'#013#010+
  '    Procedure ClearResolvedFileNames(APackage : TPackage);'#013#010+
  #013#010+
  '    // Public Copy/delete/Move/Archive/Mkdir Commands.'#013#010+
  '    ','Procedure ExecuteCommand(const Cmd : String; const Args : TStrin'+
  'gs; Env: TStrings = nil; IgnoreError : Boolean = False); virtual;'#013#010+
  '    Function GetExecuteCommandOutput(const Cmd : String; const Args : '+
  'TStrings; Env: TStrings = nil; IgnoreEr','ror : Boolean = False) : stri'+
  'ng; virtual;'#013#010+
  '    procedure CmdCopyFiles(List: TStrings; const DestDir: String; APac'+
  'kage: TPackage);'#013#010+
  '    Procedure CmdCreateDir(const DestDir : String);'#013#010+
  '    Procedure CmdMoveFiles(List : TStrings; Const DestDi','r : String);'+
  #013#010+
  '    Procedure CmdDeleteFiles(List : TStrings);'#013#010+
  '    procedure CmdDeleteDestFiles(List: TStrings; const DestDir: String'+
  ');'#013#010+
  '    Procedure CmdArchiveFiles(List : TStrings; Const ArchiveFile : Str'+
  'ing);'#013#010+
  '    Procedure CmdRenameFile','(const SourceName, DestName : String);'#013+
  #010+
  '    Procedure CmdRemoveDirs(List: TStrings);'#013#010+
  '    Procedure CmdRemoveTrees(List: TStrings);'#013#010+
  '    Procedure ExecuteCommands(Commands : TCommands; At : TCommandAt; A'+
  'Package: TPackage = nil);'#013#010+
  '    // Dep','endency commands'#013#010+
  '    Function  DependencyOK(ADependency : TDependency) : Boolean;'#013#010+
  '    // Target commands'#013#010+
  '    Function  GetCompilerCommand(APackage : TPackage; ATarget : TTarge'+
  't; Env: TStrings) : String; deprecated '#039'use TStrings version'#039';',
  #013#010+
  '    Function  TargetOK(ATarget : TTarget; ACPU: TCPU; AOS: TOS; const '+
  'aSubTarget : String) : Boolean; deprecated '#039'use TCompileTarget ver'+
  'sion'#039';'#013#010+
  '    Function  TargetInstallOK(ATarget : TTarget; ACPU:TCPU; AOS : TOS;'+
  ' const aSubTarget : Stri','ng) : Boolean; deprecated '#039'use TCompileT'+
  'arget version'#039';'#013#010+
  '    Procedure GetCompilerCommand(Args: TStrings; APackage : TPackage; '+
  'ATarget : TTarget; Env: TStrings);'#013#010+
  '    Function  TargetOK(ATarget : TTarget; const aCompileTarget : TComp'+
  'ileTarg','et) : Boolean;'#013#010+
  '    Function  TargetInstallOK(ATarget : TTarget; const aCompileTarget '+
  ': TCompileTarget) : Boolean;'#013#010+
  '    Function  NeedsCompile(APackage:TPackage; ATarget : TTarget) : Boo'+
  'lean;'#013#010+
  '    Procedure Compile(APackage:TPackage; ATarge','t : TTarget);  virtua'+
  'l;'#013#010+
  '    Procedure MaybeCompile(APackage:TPackage; ATarget: TTarget);'#013#010+
  '    Procedure CompileDependencies(APackage:TPackage; ATarget: TTarget)'+
  ';'#013#010+
  '    // Package commands'#013#010+
  '{    Function  GetPackageDir(APackage : TPackage; A','bsolutePath : Boo'+
  'lean = False) : String;'#013#010+
  '    Function  GetUnitsOutputDir(APackage : TPackage; AbsolutePath : Bo'+
  'olean = False) : String;'#013#010+
  '    Function  GetBinOutputDir(APackage : TPackage; AbsolutePath : Bool'+
  'ean = False) : String;  }'#013#010+
  '    F','unction  PackageOK(APackage : TPackage) : Boolean; virtual;'#013+
  #010+
  '    Procedure DoBeforeCompile(APackage : TPackage);virtual;'#013#010+
  '    Procedure DoAfterCompile(APackage : TPackage);virtual;'#013#010+
  '    Procedure DoBeforeInstall(APackage : TPackage);virtual',';'#013#010+
  '    Procedure DoAfterInstall(APackage : TPackage);virtual;'#013#010+
  '    Procedure DoBeforeArchive(APackage : TPackage);virtual;'#013#010+
  '    Procedure DoAfterArchive(APackage : TPackage);virtual;'#013#010+
  '    Procedure DoBeforeClean(APackage : TPackage);virtual',';'#013#010+
  '    Procedure DoAfterClean(APackage : TPackage);virtual;'#013#010+
  '    Function  NeedsCompile(APackage : TPackage) : Boolean; virtual;'#013+
  #010+
  '    Procedure Compile(APackage : TPackage);'#013#010+
  '    Procedure MaybeCompile(APackage:TPackage);'#013#010+
  '    Function Read','yToCompile(APackage:TPackage) : Boolean;'#013#010+
  '    Procedure Install(APackage : TPackage; AnArchiveFiles: boolean);'#013+
  #010+
  '    Procedure UnInstall(APackage : TPackage);'#013#010+
  '    Procedure Archive(APackage : TPackage);'#013#010+
  '    Procedure PkgList(PkgList: TStri','ngs; APackage : TPackage);'#013#010+
  '    Procedure Clean(APackage : TPackage; AllTargets: boolean);'#013#010+
  '    procedure Clean(APackage: TPackage; const aTarget: TCompileTarget)'+
  ';'#013#010+
  '    Procedure CompileDependencies(APackage : TPackage);'#013#010+
  '    function Check','Dependencies(APackage : TPackage; ErrorOnFailure: '+
  'boolean): TCheckDependencyResult;'#013#010+
  '    Function  CheckExternalPackage(Const APackageName, ForPackageName '+
  ': String; ErrorOnFailure: boolean):TPackage;'#013#010+
  '    procedure CreateOutputDir(APackage:',' TPackage);'#013#010+
  '    // Packages commands'#013#010+
  '    Procedure Compile(Packages : TPackages);'#013#010+
  '    Procedure Install(Packages : TPackages);'#013#010+
  '    Procedure UnInstall(Packages : TPackages);'#013#010+
  '    Procedure ZipInstall(Packages : TPackages);'#013#010+
  '    Procedur','e Archive(Packages : TPackages);'#013#010+
  '    procedure Manifest(Packages: TPackages; Package: TPackage);'#013#010+
  '    procedure PkgList(Packages: TPackages);'#013#010+
  '    Procedure Clean(Packages : TPackages; AllTargets: boolean);'#013#010+
  #013#010+
  '    Procedure Log(Level : TVe','rboseLevel; Msg : String);'#013#010+
  '    Procedure Log(Level : TVerboseLevel; Fmt : String; const Args : Ar'+
  'ray Of Const);'#013#010+
  #013#010+
  '    Property ListMode : Boolean Read FListMode Write FListMode;'#013#010+
  '    Property ForceCompile : Boolean Read FForceCompile Writ','e FForceC'+
  'ompile;'#013#010+
  '    Property ExternalPackages: TPackages Read FExternalPackages;'#013#010+
  '    Property StartDir: String Read FStartDir;'#013#010+
  #013#010+
  '    // Events'#013#010+
  '    Property NotifyEventCollection: TNotifyEventCollection read FNotif'+
  'yEventCollection;'#013#010+
  '   ',' Property OnLog : TLogEvent Read FOnLog Write FOnlog;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TCustomInstaller }'#013#010+
  #013#010+
  '  TCustomInstaller = Class(TComponent)'#013#010+
  '  private'#013#010+
  '    FBuildEngine: TBuildEngine;'#013#010+
  '    FPackages: TPackages;'#013#010+
  '    FRunMode: TRunMode;'#013#010+
  '    FListMode',' : Boolean;'#013#010+
  '    FInteractive : boolean;'#013#010+
  '    FLogLevels : TVerboseLevels;'#013#010+
  '    FFPMakeOptionsString: string;'#013#010+
  '    FPackageVariantSettings: TStrings;'#013#010+
  '    FPackageVariants: TFPList;'#013#010+
  '    FNotifyEventCollection: TNotifyEventCollection;'#013#010+
  '  Pr','otected'#013#010+
  '    Procedure Log(Level : TVerboseLevel; Const Msg : String);'#013#010+
  '    Procedure CreatePackages; virtual;'#013#010+
  '    Procedure FreePackages; virtual;'#013#010+
  '    function GetPackages: TPackages; virtual;'#013#010+
  '    Procedure CheckPackages; virtual;'#013#010+
  '    ','// needs build engine !'#013#010+
  '    procedure CheckNameSpaces; virtual;'#013#010+
  '    Procedure CreateBuildEngine; virtual;'#013#010+
  '    Procedure Error(const Msg : String);'#013#010+
  '    Procedure Error(const Fmt : String; const Args : Array of const);'#013+
  #010+
  '    Procedure Anal','yzeOptions;'#013#010+
  '    Procedure Usage(const FMT : String; const Args : Array of const);'#013+
  #010+
  '    Procedure Compile(Force : Boolean); virtual;'#013#010+
  '    Procedure Clean(AllTargets: boolean); virtual;'#013#010+
  '    Procedure Install(ForceBuild : Boolean); virtual;'#013,#010+
  '    Procedure UnInstall; virtual;'#013#010+
  '    Procedure ZipInstall; virtual;'#013#010+
  '    Procedure Archive; virtual;'#013#010+
  '    Procedure Manifest; virtual;'#013#010+
  '    Procedure PkgList; virtual;'#013#010+
  '    Procedure Info; virtual;'#013#010+
  '    procedure AddAutoPackageVariantsTo','Package(APackage: TPackage); v'+
  'irtual;'#013#010+
  '  Public'#013#010+
  '    Constructor Create(AOwner : TComponent); override;'#013#010+
  '    Destructor destroy; override;'#013#010+
  '    Function AddPackage(Const AName : String) : TPackage;'#013#010+
  '    Function AddPackageVariant(AName: str','ing; AIsInheritable: boolea'+
  'n; AutoAddToPackage: Boolean = false): TPackageVariants;'#013#010+
  '    Function AddPackageFromDir(Const AName : String; const aDirectory '+
  ': String; const aMask : string = '#039#039') : TPackage;'#013#010+
  '    Function Run : Boolean;'#013#010+
  '    Pr','operty FPMakeOptionsString: string read FFPMakeOptionsString;'#013+
  #010+
  '    Property BuildEngine : TBuildEngine Read FBuildEngine;'#013#010+
  '    //files in package'#013#010+
  '    Property Packages : TPackages Read GetPackages;'#013#010+
  '    Property RunMode : TRunMode Read FRu','nMode;'#013#010+
  '    Property ListMode : Boolean Read FListMode;'#013#010+
  '    Property NotifyEventCollection : TNotifyEventCollection read FNoti'+
  'fyEventCollection;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TFPCInstaller }'#013#010+
  '  TFPCInstaller = class(TCustomInstaller)'#013#010+
  '  public'#013#010+
  '    Const','ructor Create(AOwner : TComponent); override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TBasicInstaller }'#013#010+
  '  TBasicInstaller = class(TCustomInstaller)'#013#010+
  '    Constructor Create(AOwner : TComponent); override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TValueItem }'#013#010+
  #013#010+
  '  TValueItem = Class(TObject)',#013#010+
  '  Private'#013#010+
  '    FValue : String;'#013#010+
  '  Public'#013#010+
  '    Constructor Create(AValue : String);'#013#010+
  '    Property Value : String Read FValue;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  { TFunctionItem }'#013#010+
  #013#010+
  '  TFunctionItem = Class(TObject)'#013#010+
  '  Private'#013#010+
  '    FFunc : TReplaceFunction;'#013#010+
  '  ','public'#013#010+
  '    Constructor Create(AFunc : TReplaceFunction);'#013#010+
  '    Property Func : TReplaceFunction Read FFunc;'#013#010+
  '  end;'#013#010+
  #013#010+
  '{$ifndef NO_THREADING}'#013#010+
  #013#010+
  '  { TCompileWorkerThread }'#013#010+
  #013#010+
  '  TCompileWorkerThread = class(TThread)'#013#010+
  '  private'#013#010+
  '    FBuildEng','ine: TBuildEngine;'#013#010+
  '    FCompilationOK: boolean;'#013#010+
  '    FDone: boolean;'#013#010+
  '    FErrorMessage: string;'#013#010+
  '    FWorkerPrefix: string;'#013#010+
  '    FNotifyMainThreadEvent: PRTLEvent;'#013#010+
  '    FNotifyStartTask: PRTLEvent;'#013#010+
  '    FPackage: TPackage;'#013#010+
  '  protected'#013#010+
  ' ','   procedure execute; override;'#013#010+
  '    property Done: boolean read FDone;'#013#010+
  '    property APackage: TPackage read FPackage write FPackage;'#013#010+
  '    property CompilationOK: boolean read FCompilationOK;'#013#010+
  '    property NotifyStartTask: PRTLEvent read F','NotifyStartTask;'#013#010+
  '    property ErrorMessage: string read FErrorMessage;'#013#010+
  '  public'#013#010+
  '    constructor Create(ABuildEngine: TBuildEngine; NotifyMainThreadEve'+
  'nt: PRTLEvent); virtual;'#013#010+
  '    destructor Destroy; override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '{$endif NO_THREA','DING}'#013#010+
  #013#010+
  '  { TfpmPlugin }'#013#010+
  #013#010+
  '  TfpmPlugin = class'#013#010+
  '  protected'#013#010+
  '    function GetName: string; virtual;'#013#010+
  '  public'#013#010+
  '    property Name: string read GetName;'#013#010+
  #013#010+
  '    procedure BeforeResolvePackagePath(ABuildEngine: TBuildEngine; APa'+
  'ckage: TPacka','ge; out AContinue: Boolean); virtual;'#013#010+
  '    procedure ResolvePackagePath(ABuildEngine: TBuildEngine; APackage:'+
  ' TPackage; SearchDirectory: string; out AContinue: Boolean); virtual;'#013+
  #010+
  '    procedure AfterResolvePackagePath(ABuildEngine: TBuildEn','gine; AP'+
  'ackage: TPackage; out AContinue: Boolean); virtual;'#013#010+
  '  end;'#013#010+
  '  TfpmPluginClass = class of TfpmPlugin;'#013#010+
  #013#010+
  '  { TfpmPluginManager }'#013#010+
  #013#010+
  '  TfpmPluginManager = class(TfpmPlugin)'#013#010+
  '  private'#013#010+
  '    FPlugins: array of TfpmPlugin;'#013#010+
  '  public'#013#010+
  '  ','  destructor Destroy; override;'#013#010+
  '    procedure RegisterPlugin(APlugin: TfpmPluginClass);'#013#010+
  #013#010+
  '    procedure BeforeResolvePackagePath(ABuildEngine: TBuildEngine; APa'+
  'ckage: TPackage; out AContinue: Boolean); override;'#013#010+
  '    procedure ResolvePack','agePath(ABuildEngine: TBuildEngine; APackag'+
  'e: TPackage; SearchPath: string; out AContinue: Boolean); override;'#013+
  #010+
  '    procedure AfterResolvePackagePath(ABuildEngine: TBuildEngine; APac'+
  'kage: TPackage; out AContinue: Boolean); override;'#013#010+
  '  end;',#013#010+
  #013#010+
  '  { TfpmResolvePackagePathsPlugin }'#013#010+
  #013#010+
  '  TfpmResolvePackagePathsPlugin = class(TfpmPlugin)'#013#010+
  '  private'#013#010+
  '    procedure ResolveUnitConfigFilenameForBasePath(ABuildEngine: TBuil'+
  'dEngine; APackage: TPackage; ABasePath: string;'#013#010+
  '      out ACon','tinue: Boolean);'#013#010+
  '  public'#013#010+
  '    procedure BeforeResolvePackagePath(ABuildEngine: TBuildEngine; APa'+
  'ckage: TPackage; out AContinue: Boolean); override;'#013#010+
  '    procedure ResolvePackagePath(ABuildEngine: TBuildEngine; APackage:'+
  ' TPackage; SearchPa','th: string;'#013#010+
  '      out AContinue: Boolean); override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  ECollectionError = Class(Exception);'#013#010+
  '  EDictionaryError = Class(Exception);'#013#010+
  '  EInstallerError = Class(Exception);'#013#010+
  #013#010+
  '  TInstallerClass = Class of TCustomInstaller;'#013#010+
  '  TDic','tionaryClass = Class of TDictionary;'#013#010+
  '  TPackageDictionaryClass = Class of TPackageDictionary;'#013#010+
  #013#010+
  'Type'#013#010+
  '  TArchiveEvent = Procedure (Const AFileName : String; List : TStrings'+
  ') of Object;'#013#010+
  '  TArchiveProc = Procedure (Const AFileName : String','; List : TString'+
  's);'#013#010+
  #013#010+
  'Var'#013#010+
  '  DictionaryClass : TDictionaryClass = TDictionary;'#013#010+
  '  PackageDictionaryClass : TPackageDictionaryClass = TPackageDictionar'+
  'y;'#013#010+
  '  OnArchiveFiles : TArchiveEvent = Nil;'#013#010+
  '  ArchiveFilesProc : TArchiveProc = Nil;'#013#010+
  #013#010,
  '  Defaults : TCustomDefaults; // Set by installer.'#013#010+
  '  GlobalDictionary : TDictionary;'#013#010+
  #013#010+
  #013#010+
  'Function CurrentOS : String;'#013#010+
  'Function CurrentCPU : String;'#013#010+
  #013#010+
  'Function Installer(InstallerClass: TInstallerClass) : TCustomInstaller'+
  '; overload;'#013#010+
  'Fun','ction Installer : TCustomInstaller; overload;'#013#010+
  #013#010+
  'Function OSToString(OS: TOS) : String;'#013#010+
  'Function OSesToString(OSes: TOSes) : String;'#013#010+
  'Function CPUToString(CPU: TCPU) : String;'#013#010+
  'Function CPUSToString(CPUS: TCPUS) : String;'#013#010+
  'Function StringT','oOS(const S : String) : TOS;'#013#010+
  'function IsDifferentFromBuild(ACpu: TCPU; AOs: TOs): boolean;'#013#010+
  '//Function StringToOSes(const S : String) : TOSes;'#013#010+
  'Function StringToCPU(const S : String) : TCPU;'#013#010+
  'Function StringToCPUS(const S : String) : TCPUS',';'#013#010+
  'Function ModeToString(Mode: TCompilerMode) : String;'#013#010+
  'Function StringToMode(const S : String) : TCompilerMode;'#013#010+
  'Function MakeTargetString(const aTarget : TCompileTarget; aLimit83 : B'+
  'oolean) : String;'#013#010+
  'Function MakeTargetString(const aTar','get : TCompileTarget) : String;'#013+
  #010+
  'Function MakeTargetString(CPU : TCPU;OS: TOS; aSubTarget : String = '#039+
  #039') : String;'#013#010+
  'Procedure StringToCPUOS(const S : String; Var CPU : TCPU; Var OS: TOS)'+
  ';'#013#010+
  'Function FixPath (const APath : String) : String; i','nline; deprecated'+
  ' '#039'Use the overload with AIsDir instead'#039';'#013#010+
  'Function FixPath (const APath : String; AIsDir : Boolean) : String;'#013+
  #010+
  'Function IsRelativePath(const APath : String) : boolean;'#013#010+
  'Procedure ChangeDir(const APath : String);'#013#010+
  'Procedure ','SplitCommand(Const Cmd : String; out Exe,Options : String)'+
  ';'#013#010+
  'Procedure AddCustomFpmakeCommandlineOption(const ACommandLineOption, H'+
  'elpMessage : string);'#013#010+
  'Function GetCustomFpmakeCommandlineOptionValue(const ACommandLineOptio'+
  'n : string) : st','ring;'#013#010+
  'Function AddProgramExtension(const ExecutableName: string; AOS : TOS) '+
  ': string;'#013#010+
  'Function AddLibraryExtension(const LibraryName: string; AOS : TOS) : s'+
  'tring;'#013#010+
  'Function GetImportLibraryFilename(const UnitName: string; AOS : TOS) :'+
  ' str','ing;'#013#010+
  #013#010+
  'procedure SearchFiles(AFileName, ASearchPathPrefix: string; Recursive:'+
  ' boolean; var List: TStrings);'#013#010+
  'function GetDefaultLibGCCDir(CPU : TCPU;OS: TOS; out ErrorMessage: str'+
  'ing): string;'#013#010+
  #013#010+
  'function GetPluginManager: TfpmPluginManage','r;'#013#010+
  #013#010+
  'Implementation'#013#010+
  #013#010+
  '{$IFDEF FPC_DOTTEDUNITS}'#013#010+
  'uses System.TypInfo, System.RtlConsts;'#013#010+
  '{$ELSE FPC_DOTTEDUNITS}'#013#010+
  'uses typinfo, rtlconsts;'#013#010+
  '{$ENDIF FPC_DOTTEDUNITS}'#013#010+
  #013#010+
  'const'#013#010+
  '{$ifdef CREATE_TAR_FILE}'#013#010+
  '  {$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '  ArchiveE','xtension = '#039'.tar.gz'#039';'#013#010+
  '  {$else }'#013#010+
  '  ArchiveExtension = '#039'.tar'#039';'#013#010+
  '  {$endif HAS_UNIT_ZIPPER}'#013#010+
  '{$else CREATE_TAR_FILE}'#013#010+
  '  ArchiveExtension = '#039'.zip'#039';'#013#010+
  '{$endif CREATE_TAR_FILE}'#013#010+
  #013#010+
  'var'#013#010+
  '  GPluginManager: TfpmPluginManager;'#013#010+
  #013#010+
  #013#010+
  '{----------------','- from strutils ---------------------}'#013#010+
  #013#010+
  'function FindPart(const HelpWilds, inputStr: string): Integer;'#013#010+
  'var'#013#010+
  '  i, J: Integer;'#013#010+
  '  Diff: Integer;'#013#010+
  'begin'#013#010+
  '  Result:=0;'#013#010+
  '  i:=Pos('#039'?'#039',HelpWilds);'#013#010+
  '  if (i=0) then'#013#010+
  '    Result:=Pos(HelpWilds, in','putStr)'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    Diff:=Length(inputStr) - Length(HelpWilds);'#013#010+
  '    for i:=0 to Diff do'#013#010+
  '      begin'#013#010+
  '      for J:=1 to Length(HelpWilds) do'#013#010+
  '        if (inputStr[i + J] = HelpWilds[J]) or (HelpWilds[J] = '#039'?'#039+
  ') then'#013#010+
  '          b','egin'#013#010+
  '          if (J=Length(HelpWilds)) then'#013#010+
  '            begin'#013#010+
  '            Result:=i+1;'#013#010+
  '            Exit;'#013#010+
  '            end;'#013#010+
  '          end'#013#010+
  '        else'#013#010+
  '          Break;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function isWild(inputStr, Wilds: s','tring; ignoreCase: Boolean): Boole'+
  'an;'#013#010+
  #013#010+
  ' function SearchNext(var Wilds: string): Integer;'#013#010+
  #013#010+
  ' begin'#013#010+
  '   Result:=Pos('#039'*'#039', Wilds);'#013#010+
  '   if Result>0 then'#013#010+
  '     Wilds:=Copy(Wilds,1,Result - 1);'#013#010+
  ' end;'#013#010+
  #013#010+
  'var'#013#010+
  '  CWild, CinputWord: Integer; { cou','nter for positions }'#013#010+
  '  i, LenHelpWilds: Integer;'#013#010+
  '  MaxinputWord, MaxWilds: Integer; { Length of inputStr and Wilds }'#013+
  #010+
  '  HelpWilds: string;'#013#010+
  'begin'#013#010+
  '  if Wilds = inputStr then begin'#013#010+
  '    Result:=True;'#013#010+
  '    Exit;'#013#010+
  '  end;'#013#010+
  '  repeat { delete '#039,'**'#039', because '#039'**'#039' = '#039'*'#039' }'#013+
  #010+
  '    i:=Pos('#039'**'#039', Wilds);'#013#010+
  '    if i > 0 then'#013#010+
  '      Wilds:=Copy(Wilds, 1, i - 1) + '#039'*'#039' + Copy(Wilds, i + 2, '+
  'Maxint);'#013#010+
  '  until i = 0;'#013#010+
  '  if Wilds = '#039'*'#039' then begin { for fast end, if Wilds only '#039+
  '*'#039' }'#013#010+
  '    Result:=Tru','e;'#013#010+
  '    Exit;'#013#010+
  '  end;'#013#010+
  '  MaxinputWord:=Length(inputStr);'#013#010+
  '  MaxWilds:=Length(Wilds);'#013#010+
  '  if ignoreCase then begin { upcase all letters }'#013#010+
  '    inputStr:=AnsiUpperCase(inputStr);'#013#010+
  '    Wilds:=AnsiUpperCase(Wilds);'#013#010+
  '  end;'#013#010+
  '  if (MaxWilds = 0) o','r (MaxinputWord = 0) then begin'#013#010+
  '    Result:=False;'#013#010+
  '    Exit;'#013#010+
  '  end;'#013#010+
  '  CinputWord:=1;'#013#010+
  '  CWild:=1;'#013#010+
  '  Result:=True;'#013#010+
  '  repeat'#013#010+
  '    if inputStr[CinputWord] = Wilds[CWild] then begin { equal letters '+
  '}'#013#010+
  '      { goto next letter }'#013#010+
  '      inc','(CWild);'#013#010+
  '      inc(CinputWord);'#013#010+
  '      Continue;'#013#010+
  '    end;'#013#010+
  '    if Wilds[CWild] = '#039'?'#039' then begin { equal to '#039'?'#039' }'#013+
  #010+
  '      { goto next letter }'#013#010+
  '      inc(CWild);'#013#010+
  '      inc(CinputWord);'#013#010+
  '      Continue;'#013#010+
  '    end;'#013#010+
  '    if Wilds[CWild] = '#039'*'#039' ','then begin { handling of '#039'*'#039+
  ' }'#013#010+
  '      HelpWilds:=Copy(Wilds, CWild + 1, MaxWilds);'#013#010+
  '      i:=SearchNext(HelpWilds);'#013#010+
  '      LenHelpWilds:=Length(HelpWilds);'#013#010+
  '      if i = 0 then begin'#013#010+
  '        { no '#039'*'#039' in the rest, compare the ends }'#013#010+
  '      ','  if HelpWilds = '#039#039' then Exit; { '#039'*'#039' is the last'+
  ' letter }'#013#010+
  '        { check the rest for equal Length and no '#039'?'#039' }'#013#010+
  '        for i:=0 to LenHelpWilds - 1 do begin'#013#010+
  '          if (HelpWilds[LenHelpWilds - i] <> inputStr[MaxinputWord - i'+
  ']) and'#013#010,
  '            (HelpWilds[LenHelpWilds - i]<> '#039'?'#039') then'#013#010+
  '          begin'#013#010+
  '            Result:=False;'#013#010+
  '            Exit;'#013#010+
  '          end;'#013#010+
  '        end;'#013#010+
  '        Exit;'#013#010+
  '      end;'#013#010+
  '      { handle all to the next '#039'*'#039' }'#013#010+
  '      inc(CWild, 1 + LenHel','pWilds);'#013#010+
  '      i:=FindPart(HelpWilds, Copy(inputStr, CinputWord, Maxint));'#013#010+
  '      if i= 0 then begin'#013#010+
  '        Result:=False;'#013#010+
  '        Exit;'#013#010+
  '      end;'#013#010+
  '      CinputWord:=i + LenHelpWilds;'#013#010+
  '      Continue;'#013#010+
  '    end;'#013#010+
  '    Result:=False;'#013#010+
  '  ','  Exit;'#013#010+
  '  until (CinputWord > MaxinputWord) or (CWild > MaxWilds);'#013#010+
  '  { no completed evaluation }'#013#010+
  '  if CinputWord <= MaxinputWord then Result:=False;'#013#010+
  '  if (CWild <= MaxWilds) and (Wilds[MaxWilds] <> '#039'*'#039') then Res'+
  'ult:=False;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Fu','nction IndexText(S: String; aList : Array of string) : Integer;'#013+
  #010+
  #013#010+
  'begin'#013#010+
  '  Result:=Length(aList)-1;'#013#010+
  '  While (Result>=0) and not SameText(aList[Result],S) do'#013#010+
  '    dec(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'type'#013#010+
  '  TUnsortedDuplicatesStringList = class(TStrin','gList)'#013#010+
  '  public'#013#010+
  '    function Add(const S: string): Integer; override;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  TUnsortedCompilerOptionsStringList = class(TStringList)'#013#010+
  '  public'#013#010+
  '    constructor Create;'#013#010+
  '  end;'#013#010+
  #013#010+
  'var'#013#010+
  '  CustomFpmakeCommandlineOptions: TStrings;'#013#010+
  '  C','ustomFpMakeCommandlineValues: TStrings;'#013#010+
  #013#010+
  '{$ifdef NO_THREADING}'#013#010+
  'var'#013#010+
  '{$else NO_THREADING}'#013#010+
  'threadvar'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  GPathPrefix : string;'#013#010+
  '  GLogPrefix  : string;'#013#010+
  #013#010+
  'ResourceString'#013#010+
  '  SErrInvalidCPU        = '#039'Invalid CPU name "','%s"'#039';'#013#010+
  '  SErrInvalidOS         = '#039'Invalid OS name "%s"'#039';'#013#010+
  '  SErrInvalidMode       = '#039'Invalid compiler mode "%s"'#039';'#013#010+
  '  SErrInvalidTarget     = '#039'Invalid compiler target "%s"'#039';'#013#010+
  '  SErrNameExists        = '#039'Name "%s" already exists in the collect',
  'ion.'#039';'#013#010+
  '  SErrNoSuchName        = '#039'Could not find item with name "%s" in t'+
  'he collection.'#039';'#013#010+
  '  SErrInValidArgument   = '#039'Invalid command-line argument at positi'+
  'on %d: %s'#039';'#013#010+
  '  SErrNeedArgument      = '#039'Option at position %d (%s) needs an arg'+
  'ume','nt'#039';'#013#010+
  '  SErrNoPackagesDefined = '#039'No action possible: No packages were de'+
  'fined.'#039';'#013#010+
  '  SErrInstaller         = '#039'The installer encountered the following'+
  ' error:'#039';'#013#010+
  '  SErrDepUnknownTarget  = '#039'Unknown target for unit "%s" in depende'+
  'ncies for %s in',' package %s'#039';'#013#010+
  '  SErrExternalCommandFailed = '#039'External command "%s" failed with e'+
  'xit code %d. Console output:'#039'+LineEnding+'#039'%s'#039';'#013#010+
  '  SErrExtCommandNotFound= '#039'External command "%s" not found'#039';'#013+
  #010+
  '  SErrCreatingDirectory = '#039'Failed to create direc','tory "%s"'#039';'+
  #013#010+
  '  SErrDeletingFile      = '#039'Failed to delete file "%s"'#039';'#013#010+
  '  SErrRemovingDirectory = '#039'Failed to remove directory "%s"'#039';'#013+
  #010+
  '  SErrMovingFile        = '#039'Failed to move file "%s" to "%s"'#039';'#013+
  #010+
  '  SErrCopyingFile       = '#039'Failed to copy fil','e "%s" to "%s"'#039';'+
  #013#010+
  '  SErrChangeDirFailed   = '#039'Failed to enter directory "%s"'#039';'#013+
  #010+
  '  SErrNoArchiveSupport  = '#039'This binary contains no archive support'+
  '. Please recompile with archive support'#039';'#013#010+
  '  SErrNoDictionaryItem  = '#039'No item called "%s" in th','e dictionary'+
  #039';'#013#010+
  '  {$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  SErrInvalidFPCInfo    = '#039'Compiler returns invalid information, c'+
  'heck if fpc -iV works'#039';'#013#010+
  '  {$ENDIF}'#013#010+
  '  SErrDependencyNotFound = '#039'Could not find unit directory for depe'+
  'ndency package "%s" requir','ed for package "%s"'#039';'#013#010+
  '  SErrAlreadyInitialized = '#039'Installer can only be initialized once'+
  #039';'#013#010+
  '  SErrInvalidState      = '#039'Invalid state for target %s'#039';'#013#010+
  '  SErrCouldNotCompile   = '#039'Could not compile target %s from packag'+
  'e %s'#039';'#013#010+
  '  SErrUnsupport','edBuildmode = '#039'Package does not support this buil'+
  'dmode'#039';'#013#010+
  '  SErrPackVarNotExist   = '#039'There is no package variant with the na'+
  'me "%s"'#039';'#013#010+
  '  SErrEventNotSupported = '#039'Unsupported event type'#039';'#013#010+
  '  SErrorPkgNotInstalled = '#039'Package "%s" is not insta','lled, can no'+
  't uninstall.'#039';'#013#010+
  '  SErrBuildUnitCompilation = '#039'Compilation of "%s" failed'#039';'#013+
  #010+
  '  SErrExpectPkgVariant  = '#039'The Package-variant on the command-line'+
  ' position %d (%s) should have at least one item'#039';'#013#010+
  #013#010+
  '  SWarnCircularTargetDependency =',' '#039'Warning: Circular dependency '+
  'detected when compiling target %s with target %s'#039';'#013#010+
  '  SWarnCircularPackageDependency = '#039'Warning: Circular dependency d'+
  'etected when compiling package %s with package %s'#039';'#013#010+
  '  SWarnFailedToSetTime    = '#039'Warning: ','Failed to set timestamp on'+
  ' file "%s"'#039';'#013#010+
  '  SWarnFailedToGetTime    = '#039'Warning: Failed to get timestamp from'+
  ' file "%s"'#039';'#013#010+
  '  SWarnSourceFileNotFound  = '#039'Warning: Source file "%s" from packa'+
  'ge %s not found for %s'#039';'#013#010+
  '  SWarnIncludeFileNotFound =',' '#039'Warning: Include file "%s" from pa'+
  'ckage %s not found for %s'#039';'#013#010+
  '  SWarnDepUnitNotFound     = '#039'Warning: Dependency on unit %s is no'+
  't supported for %s'#039';'#013#010+
  '  SWarnTargetDependsOnPackage = '#039'Warning: Target %s of package %s '+
  'depends on another pa','ckage (%s). These kind of dependencies are not '+
  'processed'#039';'#013#010+
  '  SWarnDependOnOtherPlatformPackage = '#039'Warning: Package %s depends'+
  ' on package %s which is not available for the %s platform'#039';'#013#010+
  '  SWarnStartCompilingPackage = '#039'Start compiling packa','ge %s for t'+
  'arget %s.'#039';'#013#010+
  '  SWarnCompilingPackagecompleteProgress = '#039'[%3.0f%%] Compiled pack'+
  'age %s'#039';'#013#010+
  '  SWarnCompilingPackagecomplete = '#039'Compiled package %s'#039';'#013#010+
  '  SWarnInstallationPackagecomplete = '#039'Installation package %s for '+
  'target %s succee','ded'#039';'#013#010+
  '  SWarnCanNotGetAccessRights = '#039'Warning: Failed to copy access-rig'+
  'hts from file %s'#039';'#013#010+
  '  SWarnCanNotSetAccessRights = '#039'Warning: Failed to copy access-rig'+
  'hts to file %s'#039';'#013#010+
  '  SWarnCanNotGetFileAge = '#039'Warning: Failed to get FileAge for %','s'+
  #039';'#013#010+
  '  SWarnExtCommandNotFound = '#039'Warning: External command "%s" not fo'+
  'und but "%s" is older then "%s"'#039';'#013#010+
  '  SWarnDuplicatePackage = '#039'Warning: Package %s is already added. U'+
  'sing the existing package'#039';'#013#010+
  '  SWarngccNotFound        = '#039'Could not ','find gcc'#039';'#013#010+
  '  SWarncrossgccNotFound   = '#039'Could not find gcc for cross-configur'+
  'ation'#039';'#013#010+
  '  SWarngcclibpath         = '#039'Warning: Unable to determine the libg'+
  'cc path.'#039';'#013#010+
  '{$IFNDEF HAS_UNIT_PROCESS}'#013#010+
  '  SWarnNoFCLProcessSupport= '#039'No FCL-Process sup','port'#039';'#013#010+
  '{$ENDIF}'#013#010+
  '  SWarnRetryRemDirectory     = '#039'Failed to remove directory "%s". R'+
  'etry after a short delay'#039';'#013#010+
  '  SWarnRetryDeleteFile       = '#039'Failed to remove file "%s". Retry '+
  'after a short delay'#039';'#013#010+
  '  SWarnCombinedPathAndUDir= '#039'Warning: B','etter do not combine the '+
  'SearchPath and Global/Local-UnitDir parameters'#039';'#013#010+
  '  SWarnRemovedNonEmptyDirectory = '#039'Warning: Removed non empty dire'+
  'ctory "%s"'#039';'#013#010+
  #013#010+
  '  SInfoPackageAlreadyProcessed = '#039'Package %s is already processed'#039+
  ';'#013#010+
  '  SInfoSkipPac','kageTargetProgress = '#039'[%3.0f%%] Skipped package %s'+
  ' which has been disabled for target %s'#039';'#013#010+
  '  SInfoSkipPackageTarget = '#039'Skipped package %s which has been disa'+
  'bled for target %s'#039';'#013#010+
  '  SInfoCompilingTarget    = '#039'Compiling target %s'#039';'#013#010+
  '  SInfoE','xecutingCommand   = '#039'Executing command "%s %s"'#039';'#013+
  #010+
  '  SInfoCreatingOutputDir  = '#039'Creating output dir "%s"'#039';'#013#010+
  '  SInfoInstallingPackage  = '#039'Installing package %s'#039';'#013#010+
  '  SInfoUnInstallingPackage= '#039'Uninstalling package %s'#039';'#013#010+
  '  SInfoArchivingPackage','   = '#039'Archiving package %s in "%s"'#039';'#013+
  #010+
  '  SInfoCleaningPackage    = '#039'Cleaning package %s'#039';'#013#010+
  '  SInfoCleanPackagecomplete = '#039'Clean of package %s completed'#039';'+
  #013#010+
  '  SInfoManifestPackage    = '#039'Creating manifest for package %s'#039';'+
  #013#010+
  '  SInfoPkgListPackage','    = '#039'Adding package %s to the package lis'+
  't'#039';'#013#010+
  '  SInfoCopyingFile        = '#039'Copying file "%s" to "%s"'#039';'#013#010+
  '  SInfoDeletedFile        = '#039'Deleted file "%s"'#039';'#013#010+
  '  SInfoRemovedDirectory   = '#039'Removed directory "%s"'#039';'#013#010+
  '  SInfoSourceNewerDest    = '#039,'Source file "%s" (%s) is newer than '+
  'destination "%s" (%s).'#039';'#013#010+
  '  SInfoDestDoesNotExist   = '#039'Destination file "%s" does not exist.'+
  #039';'#013#010+
  '  SInfoFallbackBuildmode  = '#039'Buildmode not supported by package, f'+
  'alling back to one by one unit compilation',#039';'#013#010+
  '  SInfoFallbackBuildmodeBU= '#039'Buildmode not supported by package, f'+
  'alling back to compilation using a buildunit'#039';'#013#010+
  '  SInfoDirectoryNoPackage = '#039'Found directory "%s" while searching '+
  'for package "%s" which does not contain a package'#039';'#013#010+
  '  S','InfoSrcDirectoryNoPkg  = '#039'Found source-directory "%s" while s'+
  'earching for package "%s" but the package is not compiled or has the w'+
  'rong name'#039';'#013#010+
  #013#010+
  '  SDbgComparingFileTimes    = '#039'Comparing file "%s" time "%s" to "%'+
  's" time "%s".'#039';'#013#010+
  '  SDbgCompi','lingDependenciesOfTarget = '#039'Compiling dependencies of'+
  ' target %s'#039';'#013#010+
  '  SDbgResolvingSourcesOfTarget = '#039'Resolving filenames of target %s'+
  ' for %s'#039';'#013#010+
  '  SDbgResolvedSourceFile    = '#039'Resolved source file %s to "%s"'#039+
  ';'#013#010+
  '  SDbgSourceAlreadyResolved = ',#039'Source file of %s has been resolved'+
  ' earlier'#039';'#013#010+
  '  SDbgResolvedIncludeFile   = '#039'Resolved include file %s to "%s"'#039+
  ';'#013#010+
  '  SDbgOutputNotYetAvailable = '#039'Output file %s not available'#039';'#013+
  #010+
  '  SDbgDependencyOnUnit      = '#039'Dependency of %s on unit %s'#039';'#013+
  #010,
  '  SDbgDependencyUnitRecompiled = '#039'Dependent unit %s is being recom'+
  'piled'#039';'#013#010+
  '  SDbgMustCompile           = '#039'Must compile %s. (%s)'#039';'#013#010+
  '  SDbgSkippingTargetWrongCPU = '#039'Skipping target %s, different CPU '+
  '(%s)'#039';'#013#010+
  '  SDbgSkippingTargetWrongOS  = '#039'Ski','pping target %s, different OS'+
  ' (%s)'#039';'#013#010+
  '  SDbgSkippingTargetWrongSubTarget  = '#039'Skipping target %s, differe'+
  'nt Subtarget (allowed: %s)'#039';'#013#010+
  '  SDbgTargetIsNotAUnitOrProgram = '#039'Skipping Target %s, not an unit'+
  ' or program'#039';'#013#010+
  '  SDbgConsideringTarget  ','   = '#039'Considering target %s'#039';'#013#010+
  '  SDbgConsideringPackage    = '#039'Considering package %s'#039';'#013#010+
  '  SDbgSearchExtDepPath      = '#039'Search path for external dependency'+
  ' %s'#039';'#013#010+
  '  SDbgExternalDependency    = '#039'External dependency %s found in "%s'+
  '"'#039';'#013#010+
  '  SDbgBu','ildEngineArchiving  = '#039'Build engine archiving'#039';'#013#010+
  '  SDbgBuildEngineGenerateManifests = '#039'Build engine generating mani'+
  'fests'#039';'#013#010+
  '  SDbgBuildEngineGeneratePkgList = '#039'Build engine generating packag'+
  'e list'#039';'#013#010+
  '  SDbgBuildEngineCleaning   = '#039'Build eng','ine cleaning'#039';'#013#010+
  '  SDbgGenerating            = '#039'Generating "%s"'#039';'#013#010+
  '  SDbgLoading               = '#039'Loading "%s"'#039';'#013#010+
  '  SDbgFound                 = '#039'Found'#039';'#013#010+
  '  SDbgNotFound              = '#039'Not Found'#039';'#013#010+
  '  SDbgDirectoryExists       = '#039'Directory "%','s" %s'#039';'#013#010+
  '  SDbgFileExists            = '#039'File "%s" %s'#039';'#013#010+
  '  SDbgArchivingFile         = '#039'Archiving "%s"'#039';'#013#010+
  '  SDbgSearchPath            = '#039'Using %s path "%s"'#039';'#013#010+
  '  SDbgEnterDir              = '#039'Entering directory "%s"'#039';'#013#010+
  '  SDbgPackageChecksumCha','nged = '#039'Package %s depends on the %s pac'+
  'kage which has been modified'#039';'#013#010+
  '  SDbgFileDoesNotExist      = '#039'File "%s" does not exist'#039';'#013#010+
  '  SDbgDirectoryDoesNotExist = '#039'Directory "%s" does not exist'#039';'+
  #013#010+
  '  SDbgDirectoryNotEmpty     = '#039'Directory "%s"',' is not empty. Will'+
  ' not remove'#039';'#013#010+
  '  SDbgGenerateBuildUnit     = '#039'Generate build-unit %s'#039';'#013#010+
  '  SDbgBuildUnitFailure      = '#039'Generate build-unit %s failed'#039';'+
  #013#010+
  '  SDbgForcedCompile         = '#039'Forced compile'#039';'#013#010+
  '  SDbgOutputDoesNotExist    = '#039'Outpu','t file does not exist'#039';'#013+
  #010+
  '  SDbgNewerSource           = '#039'Source file is newer then output fi'+
  'le'#039';'#013#010+
  '  SDbgNewerInclude          = '#039'The include file %s is newer then o'+
  'utput file'#039';'#013#010+
  '  SDbgDependencyRecompiled  = '#039'The unit %s where this unit depe','n'+
  'ds on is recompiled'#039';'#013#010+
  '  SDbgPackageDepRecompiled  = '#039'The package %s where this package d'+
  'epends on is recompiled'#039';'#013#010+
  '  SDbgTargetHasToBeCompiled = '#039'At least one of the targets in the '+
  'package has to be compiled.'#039';'#013#010+
  '  SDbgDeletedFile         ','  = '#039'Recursively deleted file "%s"'#039+
  ';'#013#010+
  '  SDbgRemovedDirectory      = '#039'Recursively removed directory "%s"'#039+
  ';'#013#010+
  '  SDbgUnregisteredResource  = '#039'Adding resource file "%s", which is'+
  ' not registered.'#039';'#013#010+
  '  SDbgSearchingDir          = '#039'Searching dir  %','s.'#039';'#013#010+
  #013#010+
  '  // Help messages for usage'#013#010+
  '  SValue              = '#039'Value'#039';'#013#010+
  '  SHelpUsage          = '#039'Usage: %s command [options]'#039';'#013#010+
  '  SHelpCommand        = '#039'Where command is one of the following:'#039+
  ';'#013#010+
  '  SHelpCompile        = '#039'Compile all units in',' the package(s).'#039+
  ';'#013#010+
  '  SHelpBuild          = '#039'Build all units in the package(s).'#039';'#013+
  #010+
  '  SHelpInstall        = '#039'Install all units in the package(s).'#039';'+
  #013#010+
  '  SHelpBuildInstall   = '#039'Build and install all units in the packag'+
  'e(s).'#039';'#013#010+
  '  SHelpUnInstall ','     = '#039'Uninstall the package(s).'#039';'#013#010+
  '  SHelpClean          = '#039'Clean (remove) all generated files in the'+
  ' package(s) for current CPU-OS target.'#039';'#013#010+
  '  SHelpDistclean      = '#039'Clean (remove) all generated files in the'+
  ' package(s) for all targets.'#039,';'#013#010+
  '  SHelpArchive        = '#039'Create archive (zip) with all units in th'+
  'e package(s).'#039';'#013#010+
  '  SHelpHelp           = '#039'This message.'#039';'#013#010+
  '  SHelpManifest       = '#039'Create a manifest suitable for import in '+
  'repository.'#039';'#013#010+
  '  SHelpPkgList        = '#039'Create',' list of all packages suitable fo'+
  'r FPC installer.'#039';'#013#010+
  '  SHelpZipInstall     = '#039'Install all units in the package(s) into '+
  'an archive.'#039';'#013#010+
  '  SHelpCmdOptions     = '#039'Where options is one or more of the follo'+
  'wing:'#039';'#013#010+
  '  SHelpCPU            = '#039'Compil','e for indicated CPU.'#039';'#013#010+
  '  SHelpOS             = '#039'Compile for indicated OS'#039';'#013#010+
  '  SHelpSubTarget      = '#039'Compile for indicated subtarget'#039';'#013+
  #010+
  '  SHelpTarget         = '#039'Compile for indicated target, string in t'+
  'he form CPU-OS(-subtarget)'#039';'#013#010+
  '  SHelp','List           = '#039'list commands instead of actually execu'+
  'ting them.'#039';'#013#010+
  '  SHelpPrefix         = '#039'Use indicated prefix directory for all co'+
  'mmands.'#039';'#013#010+
  '  SHelpNoFPCCfg       = '#039'Compiler will not use fpc.cfg'#039';'#013#010+
  '  SHelpBaseInstallDir = '#039'Use indic','ated directory as base install'+
  ' dir.'#039';'#013#010+
  '  SHelpLocalUnitDir   = '#039'Use indicated directory as local (user) u'+
  'nit dir.'#039';'#013#010+
  '  SHelpOutpuUnitDir   = '#039'Use indicated directory to save the compi'+
  'led units.'#039';'#013#010+
  '  SHelpGlobalUnitDir  = '#039'Use indicated dire','ctory as global unit '+
  'dir.'#039';'#013#010+
  '  SHelpSearchPath     = '#039'Add search directory for packages.'#039';'#013+
  #010+
  '  SHelpUnitInstallDir = '#039'Use indicated directory to install units '+
  'into.'#039';'#013#010+
  '  SHelpCompiler       = '#039'Use indicated binary as compiler'#039';'#013+
  #010+
  '  SHelpConfi','g         = '#039'Use indicated config file when compilin'+
  'g.'#039';'#013#010+
  '  SHelpOptions        = '#039'Pass extra options to the compiler.'#039';'+
  #013#010+
  '  SHelpVerbose        = '#039'Be verbose when working.'#039';'#013#010+
  '  SHelpDebug          = '#039'Add debug information when working.'#039';'+
  #013#010+
  ' ',' SHelpInteractive    = '#039'Allow to interact with child processes'#039+
  ';'#013#010+
  '  SHelpInstExamples   = '#039'Install the example-sources.'#039';'#013#010+
  '  SHelpSkipCrossProgs = '#039'Skip programs when cross-compiling/instal'+
  'ling'#039';'#013#010+
  '  SHelpSkipAllProgs   = '#039'Skip all programs ','even if native-compil'+
  'ing/installing'#039';'#013#010+
  '  SHelpIgnoreInvOpt   = '#039'Ignore further invalid options.'#039';'#013+
  #010+
  '  sHelpFPUnitSrcPath  = '#039'Sourcepath to replace in fpunits.cfg on i'+
  'nstallation.'#039';'#013#010+
  '  sHelpThreads        = '#039'Enable the indicated amount of wor','ker t'+
  'hreads.'#039';'#013#010+
  '  {$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  sHelpUseEnvironment = '#039'Use environment to pass options to compil'+
  'er.'#039';'#013#010+
  '  {$endif}'#013#010+
  '  SHelpUseBuildUnit   = '#039'Compile package in Build-unit mode.'#039';'+
  #013#010+
  '  sHelpZipPrefix      = '#039'Use indicated prefix ','for generated arch'+
  'ives.'#039';'#013#010+
  '  sHelpPackageVariant1= '#039'To add a package-variant to all packages:'+
  #039';'#013#010+
  '  sHelpPackageVariant2= '#039' +[variantname]+=[variant1],<variant2>,..'+
  '.'#039';'#013#010+
  '  sHelpPackageVariant3= '#039'To add a package-variant to all packages '+
  'which ','other packages will inherit:'#039';'#013#010+
  '  sHelpPackageVariant4= '#039' +[variantname]*=[variant1],<variant2>,..'+
  '.'#039';'#013#010+
  '  sHelpPackageVariant5= '#039'To add specific options for one package-v'+
  'ariant:'#039';'#013#010+
  '  sHelpPackageVariant6= '#039' --options_[variantname]_[variant1]','=Val'+
  'ue'#039';'#013#010+
  '  SSwitchingToBuildUnitCompilation = '#039'Switching to buildunit compi'+
  'lation of package %s'#039';'#013#010+
  #013#010+
  #013#010+
  'Const'#013#010+
  '  // Keys for Defaults file. Do not localize.'#013#010+
  '  KeyCompiler = '#039'Compiler'#039';'#013#010+
  '  KeyArchive  = '#039'Archive'#039';'#013#010+
  '  KeyCopy     = '#039'Copy'#039';'#013#010,
  '  KeyMkDir    = '#039'MkDir'#039';'#013#010+
  '  KeyMove     = '#039'Move'#039';'#013#010+
  '  KeyRemove   = '#039'Remove'#039';'#013#010+
  '  KeyRemoveDir= '#039'RemoveDir'#039';'#013#010+
  '  KeyRemoveTree= '#039'RemoveTree'#039';'#013#010+
  '  KeyOptions  = '#039'Options'#039';'#013#010+
  '  KeyCPU      = '#039'CPU'#039';'#013#010+
  '  KeyOS       = '#039'OS'#039';'#013#010+
  '  KeySubTargets = '#039'SubTar','gets'#039';'#013#010+
  '  KeyMode     = '#039'Mode'#039';'#013#010+
  '  KeyPrefix   = '#039'Prefix'#039';'#013#010+
  '  KeyTarget   = '#039'Target'#039';'#013#010+
  '  KeyNoFPCCfg = '#039'NoFPCCfg'#039';'#013#010+
  '  KeyUseEnv   = '#039'UseEnv'#039';'#013#010+
  '  KeyPluginUnits        = '#039'PluginUnits'#039';'#013#010+
  '  KeyLocalUnitDir       = '#039'LocalUnitDir'#039';'#013#010+
  '  KeyGlobalU','nitDir      = '#039'GlobalUnitDir'#039';'#013#010+
  '  KeyBaseInstallDir     = '#039'BaseInstallDir'#039';'#013#010+
  '  KeyUnitInstallDir     = '#039'UnitInstallDir'#039';'#013#010+
  '  KeyBinInstallDir      = '#039'BinInstallDir'#039';'#013#010+
  '  KeyLibInstallDir      = '#039'LibInstallDir'#039';'#013#010+
  '  KeyDocInstallDir      = '#039'Doc','InstallDir'#039';'#013#010+
  '  KeyExamplesInstallDir = '#039'ExamplesInstallDir'#039';'#013#010+
  '  KeyInstallExamples    = '#039'InstallExamples'#039';'#013#010+
  '  KeySkipCrossPrograms  = '#039'SkipCrossPrograms'#039';'#013#010+
  '  KeySkipAllPrograms    = '#039'SkipAllPrograms'#039';'#013#010+
  '  // Keys for unit config'#013#010+
  '  KeyName ','    = '#039'Name'#039';'#013#010+
  '  KeyVersion  = '#039'Version'#039';'#013#010+
  '  KeyChecksum = '#039'Checksum'#039';'#013#010+
  '  KeyNeedLibC = '#039'NeedLibC'#039';'#013#010+
  '  KeyDepends  = '#039'Depends'#039';'#013#010+
  '  KeyFlags    = '#039'Flags'#039';'#013#010+
  '  KeyTransmit = '#039'TransmitOptions'#039';'#013#010+
  '  KeyAddIn    = '#039'FPMakeAddIn'#039';'#013#010+
  '  KeySourcePath =',' '#039'SourcePath'#039';'#013#010+
  '  KeyFPMakeOptions = '#039'FPMakeOptions'#039';'#013#010+
  '  KeyPackageVar = '#039'PackageVariant_'#039';'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                Helpers'#013#010+
  '*************************','*******************************************'+
  '********}'#013#010+
  #013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  'function ExecuteFPC(Verbose, Interactive: boolean; const aCompiler: st'+
  'ring; const Args: TStrings; const Env: TStrings; ConsoleOutput: TMemor'+
  'yStream): integer',';'#013#010+
  'var'#013#010+
  '  P: TProcess;'#013#010+
  '  BytesRead: longint;'#013#010+
  #013#010+
  '  function ReadFromStream(const ReadFromStdErr: boolean): longint;'#013+
  #010+
  #013#010+
  '  type'#013#010+
  '    TMessages = (mCompiling, mLinking);'#013#010+
  #013#010+
  '  var'#013#010+
  '    //ifdef the MsgNum so it contains the correct message numbe','rs fo'+
  'r each compiler version.'#013#010+
  '    MsgNum : array [TMessages] of integer = (3104, 9015);'#013#010+
  #013#010+
  '    n,available: longint;'#013#010+
  '    BuffPos: longint;'#013#010+
  '    sLine: string;'#013#010+
  '    ch: AnsiChar;'#013#010+
  '    msg: TMessages;'#013#010+
  '    ipos: integer;'#013#010+
  '    snum: string;'#013,#010+
  '  begin'#013#010+
  #013#010+
  '    // try reading it'#013#010+
  '    if ReadFromStdErr then'#013#010+
  '      begin'#013#010+
  '        available:=P.Stderr.NumBytesAvailable;'#013#010+
  '        // make sure we have room'#013#010+
  '        if (bytesRead + Available > ConsoleOutput.Size) then'#013#010+
  '          ConsoleOu','tput.SetSize(BytesRead + Available);'#013#010+
  '        n := P.Stderr.Read((ConsoleOutput.Memory + BytesRead)^, availa'+
  'ble);'#013#010+
  '      end'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '        available:=P.Output.NumBytesAvailable;'#013#010+
  '        // make sure we have room'#013#010+
  '        ','if (bytesRead + Available > ConsoleOutput.Size) then'#013#010+
  '          ConsoleOutput.SetSize(BytesRead + Available);'#013#010+
  '        n := P.Output.Read((ConsoleOutput.Memory + BytesRead)^, availa'+
  'ble);'#013#010+
  '      end;'#013#010+
  '    if n > 0 then'#013#010+
  '    begin'#013#010+
  '      Inc(','BytesRead, n);'#013#010+
  #013#010+
  '      sLine := '#039#039';'#013#010+
  '      BuffPos := ConsoleOutput.Position;'#013#010+
  '      ch:=#0;'#013#010+
  '      //read lines from the stream'#013#010+
  '      repeat'#013#010+
  '        ConsoleOutput.Read(ch,1);'#013#010+
  #013#010+
  '        if ch in [#10, #13] then'#013#010+
  '        begin'#013#010+
  '         ',' if Interactive then'#013#010+
  '            System.Writeln(output)'#013#010+
  '          else if Verbose then'#013#010+
  '            installer.log(vlInfo,sLine)'#013#010+
  '          else'#013#010+
  '            begin'#013#010+
  '              for msg := Low(TMessages) to High(TMessages) do'#013#010+
  '           ','   begin'#013#010+
  '                snum := Format('#039'(%d)'#039', [MsgNum[msg]]);'#013#010+
  '                ipos := Pos(snum, sLine);'#013#010+
  '                if ipos = 1 then'#013#010+
  '                  installer.log(vlCommand,'#039'      '#039'+ Copy(sLine'+
  ', ipos + Length(snum), Length(sLine',') - ipos - Length(snum) + 1));'#013+
  #010+
  '              end;'#013#010+
  '            end;'#013#010+
  '          if (LineEnding=#13#10) and (ch=#13) and'#013#010+
  '             (ConsoleOutput.Position<BytesRead) then'#013#010+
  '            begin'#013#010+
  '              ConsoleOutput.Read(ch,1);'#013#010+
  '     ','         if ch=#10 then'#013#010+
  '                sLine:='#039#039#013#010+
  '              else'#013#010+
  '                begin'#013#010+
  '                  if Interactive then'#013#010+
  '                    begin'#013#010+
  '                      System.Write(output,ch);'#013#010+
  '                    end'#013#010+
  '      ','            else'#013#010+
  '                    sLine:=ch;'#013#010+
  '                end;'#013#010+
  '            end'#013#010+
  '          else'#013#010+
  '            sLine := '#039#039';'#013#010+
  '          BuffPos := ConsoleOutput.Position;'#013#010+
  '        end'#013#010+
  '        else'#013#010+
  '        begin'#013#010+
  '          if Interact','ive then'#013#010+
  '            System.Write(output,ch)'#013#010+
  '          else'#013#010+
  '            sLine := sLine + ch;'#013#010+
  '        end;'#013#010+
  #013#010+
  '      until ConsoleOutput.Position >= BytesRead;'#013#010+
  #013#010+
  '      // keep partial lines, unlessin interactive mode'#013#010+
  '      if not Intera','ctive then'#013#010+
  '        ConsoleOutput.Position := BuffPos'#013#010+
  '        // Flush for interactive mode'#013#010+
  '      else if n > 0 then'#013#010+
  '        System.Flush(output);'#013#010+
  '    end;'#013#010+
  #013#010+
  '    Result := n;'#013#010+
  '  end;'#013#010+
  #013#010+
  'begin'#013#010+
  '  result := -1;'#013#010+
  '  BytesRead := 0;'#013#010+
  '  P :=',' TProcess.Create(nil);'#013#010+
  '  try'#013#010+
  '    P.Executable:=aCompiler;'#013#010+
  '    P.Parameters:=Args;'#013#010+
  '    if assigned(Env) then'#013#010+
  '      P.Environment.Assign(Env);'#013#010+
  #013#010+
  '    if Interactive then'#013#010+
  '      P.Options := [poUsePipes,poPassInput]'#013#010+
  '    else'#013#010+
  '      P.Opt','ions := [poUsePipes];'#013#010+
  #013#010+
  '    P.Execute;'#013#010+
  '    while P.Running do'#013#010+
  '      begin'#013#010+
  '        // Only call ReadFromStream if Data from corresponding stream'#013+
  #010+
  '        // is already available, otherwise, on  linux, the read call'#013+
  #010+
  '        // is blockin','g, and thus it is not possible to be sure to ha'+
  'ndle'#013#010+
  '        // big data amounts bboth on output and stderr pipes. PM.'#013#010+
  '        if P.Output.NumBytesAvailable > 0 then'#013#010+
  '          ReadFromStream(false)'#013#010+
  '        else if P.StdErr.NumBytesAvaila','ble > 0 then'#013#010+
  '          ReadFromStream(true)'#013#010+
  '        else'#013#010+
  '      // no data, wait 100 ms'#013#010+
  '          Sleep(100);'#013#010+
  '      end;'#013#010+
  #013#010+
  '    // read last part'#013#010+
  '    repeat'#013#010+
  '    until ReadFromStream(false)=0;'#013#010+
  #013#010+
  '    // read stderr'#013#010+
  '    // JvdS: Note t','hat this way stderr is added to the end of the st'+
  'ream. But I'#013#010+
  '    // see no way showing the stderr output at the place it was actual'+
  'ly written'#013#010+
  '    repeat'#013#010+
  '    until ReadFromStream(true)=0;'#013#010+
  '    ConsoleOutput.SetSize(BytesRead);'#013#010+
  #013#010+
  '    resu','lt := P.ExitStatus;'#013#010+
  '  finally'#013#010+
  '    P.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  #013#010+
  'function IsDirectoryEmpty(const directory : string) : boolean;'#013#010+
  'var'#013#010+
  '  searchRec: TSearchRec;'#013#010+
  '  SearchResult: longint;'#013#010+
  'begin'#013#010+
  '  result := true;'#013#010+
  '  Sea','rchResult := FindFirst(IncludeTrailingPathDelimiter(directory)+'+
  'AllFilesMask, faAnyFile+faSymLink, searchRec);'#013#010+
  '  try'#013#010+
  '    while SearchResult=0 do'#013#010+
  '      begin'#013#010+
  '        if (searchRec.Name<>'#039'.'#039') and (searchRec.Name<>'#039'..'#039+
  ') then'#013#010+
  '           beg','in'#013#010+
  '             result := false;'#013#010+
  '             break;'#013#010+
  '           end;'#013#010+
  '        SearchResult := FindNext(searchRec);'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    {$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.FindClose(searchRe'+
  'c);'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'functio','n ParsecompilerOutput(M: TMemoryStream; Verbose: boolean): an'+
  'sistring;'#013#010+
  'type'#013#010+
  '  TParseCompilerOutputState = (cosBeginOfLine, cosSearchColon, cosPars'+
  'eNumber, cosOther);'#013#010+
  #013#010+
  'var'#013#010+
  '  presult: PAnsiChar;'#013#010+
  '  state: TParseCompilerOutputState;'#013#010+
  '  ch',': AnsiChar;'#013#010+
  '  eolchar: AnsiChar;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  m.Seek(0, soBeginning);'#013#010+
  '  setlength(Result,M.Size);'#013#010+
  #013#010+
  '  if verbose then'#013#010+
  '    begin'#013#010+
  '      m.Read(Result[1],M.Size);'#013#010+
  '      Exit;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  presult := @Result[1];'#013#010+
  '  eolchar',' := RightStr(LineEnding,1)[1];'#013#010+
  '  m.Seek(0,soBeginning);'#013#010+
  '  state := cosBeginOfLine;'#013#010+
  '  while m.Position<m.Size do'#013#010+
  '    begin'#013#010+
  '      ch := AnsiChar(m.ReadByte);'#013#010+
  '      case state of'#013#010+
  '        cosBeginOfLine:'#013#010+
  '          begin'#013#010+
  '            if ','ch='#039'('#039' then'#013#010+
  '              state := cosParseNumber'#013#010+
  '            else if ch='#039' '#039' then'#013#010+
  '              begin'#013#010+
  '                presult^ := ch;'#013#010+
  '                inc(presult);'#013#010+
  '              end'#013#010+
  '            else'#013#010+
  '              begin'#013#010+
  '            ','    presult^ := ch;'#013#010+
  '                inc(presult);'#013#010+
  '                state := cosSearchColon;'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '        cosParseNumber:'#013#010+
  '          begin'#013#010+
  '            if ch='#039')'#039' then'#013#010+
  '              begin'#013#010+
  '              state',' := cosOther;'#013#010+
  '              // Omit the space behind the number'#013#010+
  '              ch := AnsiChar(m.ReadByte);'#013#010+
  '              assert(ch='#039' '#039');'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '        cosOther:'#013#010+
  '          begin'#013#010+
  '            presult^ := ch;'#013,#010+
  '            inc(presult);'#013#010+
  '            if ch=eolchar then'#013#010+
  '              state := cosBeginOfLine;'#013#010+
  '          end;'#013#010+
  '        cosSearchColon:'#013#010+
  '          begin'#013#010+
  '            presult^ := ch;'#013#010+
  '            inc(presult);'#013#010+
  '            if (ch='#039':'#039') or',' (ch=eolchar) then'#013#010+
  '              state := cosBeginOfLine;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  setlength(Result,presult-@result[1]);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function QuoteXML(S : String) : string;'#013#010+
  #013#010+
  '  Procedure W(Var J : Integer; Var R : String; T :',' String);'#013#010+
  '  Var'#013#010+
  '    I: integer;'#013#010+
  '  begin'#013#010+
  '    If J+Length(T)>Length(R) then'#013#010+
  '      SetLength(R,J+Length(T));'#013#010+
  '    For I:=1 to Length(t) do'#013#010+
  '      begin'#013#010+
  '      R[J]:=T[i];'#013#010+
  '      If I<Length(T) then'#013#010+
  '        Inc(J);'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010,
  'const'#013#010+
  '  QuotStr = '#039'&quot;'#039';'#013#010+
  '  AmpStr = '#039'&amp;'#039';'#013#010+
  '  ltStr = '#039'&lt;'#039';'#013#010+
  '  gtStr = '#039'&gt;'#039';'#013#010+
  'Var'#013#010+
  '  I,J : Integer;'#013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  SetLength(Result,Length(S));'#013#010+
  '  J:=0;'#013#010+
  '  For I:=1 to Length(S) do'#013#010+
  '    begin'#013#010+
  '    Inc(J);'#013#010+
  '    case S[i]',' of'#013#010+
  '      '#039'"'#039': W(j,Result,QuotStr);'#013#010+
  '      '#039'&'#039': W(J,Result,AmpStr);'#013#010+
  '      '#039'<'#039': W(J,Result,ltStr);'#013#010+
  '      '#039'>'#039': W(J,Result,gtStr);'#013#010+
  '      // Escape whitespace using CharRefs to be consistent with W3 spe'+
  'c X 3.3.3'#013#010+
  '       #9: w(J,Result,'#039'&#x9',';'#039');'#013#010+
  '{      #10: wrtStr('#039'&#xA;'#039');'#013#010+
  '       #13: wrtStr('#039'&#xD;'#039');}'#013#010+
  '    else'#013#010+
  '      Result[J]:=S[i];'#013#010+
  '    end;'#013#010+
  '    If (J=Length(Result)) and (I<Length(S)) then'#013#010+
  '      SetLength(Result,J+Length(S)-I);'#013#010+
  '    end;'#013#010+
  '  If J<>Length(Result) then'#013#010,
  '    SetLength(Result,J);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function maybequoted(const s:string):string;'#013#010+
  'const'#013#010+
  '  {$IF DEFINED(MSWINDOWS)}'#013#010+
  '    FORBIDDEN_CHARS = ['#039'!'#039', '#039'@'#039', '#039'#'#039', '#039'$'#039+
  ', '#039'%'#039', '#039'^'#039', '#039'&'#039', '#039'*'#039', '#039'('#039', '#039+
  ')'#039','#013#010+
  '                       '#039'{'#039', '#039'}'#039', '#039#039#039#039', '#039'`'+
  #039', '#039'~'#039'];',#013#010+
  '  {$ELSE}'#013#010+
  '    FORBIDDEN_CHARS = ['#039'!'#039', '#039'@'#039', '#039'#'#039', '#039'$'#039+
  ', '#039'%'#039', '#039'^'#039', '#039'&'#039', '#039'*'#039', '#039'('#039', '#039+
  ')'#039','#013#010+
  '                       '#039'{'#039', '#039'}'#039', '#039#039#039#039', '#039':'+
  #039', '#039'\'#039', '#039'`'#039', '#039'~'#039'];'#013#010+
  '  {$ENDIF}'#013#010+
  'var'#013#010+
  '  s1 : string;'#013#010+
  '  i  : integer;'#013#010+
  '  quoted : boolean;'#013#010+
  'begin'#013#010+
  '  quoted:=fals','e;'#013#010+
  '  s1:='#039'"'#039';'#013#010+
  '  for i:=1 to length(s) do'#013#010+
  '   begin'#013#010+
  '     case s[i] of'#013#010+
  '       '#039'"'#039' :'#013#010+
  '         begin'#013#010+
  '           quoted:=true;'#013#010+
  '           s1:=s1+'#039'\"'#039';'#013#010+
  '         end;'#013#010+
  '       '#039' '#039','#013#010+
  '       #128..#255 :'#013#010+
  '         begin'#013#010+
  '           quoted:=tr','ue;'#013#010+
  '           s1:=s1+s[i];'#013#010+
  '         end;'#013#010+
  '       else begin'#013#010+
  '         if s[i] in FORBIDDEN_CHARS then'#013#010+
  '           quoted:=True;'#013#010+
  '         s1:=s1+s[i];'#013#010+
  '       end;'#013#010+
  '     end;'#013#010+
  '   end;'#013#010+
  '  if quoted then'#013#010+
  '    maybequoted:=s1+'#039'"'#039#013#010+
  '  else'#013#010+
  ' ','   maybequoted:=s;'#013#010+
  'end;'#013#010+
  #013#010+
  'Procedure GetSubTargetDirs(aBaseDir : String; aList : TStrings);'#013#010+
  #013#010+
  'Var'#013#010+
  '  Info : TSearchRec;'#013#010+
  '  aDir : string;'#013#010+
  #013#010+
  'begin'#013#010+
  '  aDir:=ExtractFileDir(aBaseDir);'#013#010+
  '  if FindFirst(aBaseDir+'#039'-*'#039',faDirectory,Info)=0 then'#013#010,
  '    try'#013#010+
  '      Repeat'#013#010+
  '        if (Info.Attr and faDirectory)=faDirectory then'#013#010+
  '          aList.Add(aDir+Info.Name);'#013#010+
  '      until (FindNext(Info)<>0);'#013#010+
  '    finally'#013#010+
  '      FindClose(Info);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'Function GetSubTargetDirs(aBaseDi','r : String) : TStringDynArray;'#013#010+
  #013#010+
  'Var'#013#010+
  '  L : Tstrings;'#013#010+
  #013#010+
  'begin'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    GetSubTargetDirs(aBaseDir,L);'#013#010+
  '    Result:=L.ToStringArray;'#013#010+
  '  finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  #013#010+
  'end;'#013#010+
  #013#010+
  'procedure ReadIniFile(Const AFileNa','me: String;L:TStrings);'#013#010+
  'Var'#013#010+
  '  F : TFileStream;'#013#010+
  '  Line : String;'#013#010+
  '  I,P,PC : Integer;'#013#010+
  'begin'#013#010+
  '  // On some file systems and when using a large number of parallel ma'+
  'ke'#013#010+
  '  // processes, the lock from the creation of the ini file may not yet',
  #013#010+
  '  // have been released even though the file has been closed already'#013+
  #010+
  '  F:=TFileStream.Create(AFileName,fmOpenRead or fmShareDenyNone);'#013#010+
  '  Try'#013#010+
  '    L.LoadFromStream(F);'#013#010+
  '    // Fix lines.'#013#010+
  '    For I:=L.Count-1 downto 0 do'#013#010+
  '      begin'#013#010+
  '  ','      Line:=L[I];'#013#010+
  '        P:=Pos('#039'='#039',Line);'#013#010+
  '        PC:=Pos('#039';'#039',Line);  // Comment line.'#013#010+
  '        If (P=0) or ((PC<>0) and (PC<P)) then'#013#010+
  '          L.Delete(I)'#013#010+
  '        else'#013#010+
  '          L[i]:=Trim(System.Copy(Line,1,P-1)+'#039'='#039'+Trim(System.C'+
  'op','y(Line,P+1,Length(Line)-P)));'#013#010+
  '      end;'#013#010+
  '  Finally'#013#010+
  '    F.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '// Callback for Sysutils getapplicationname.'#013#010+
  'Function GetFPMakeName : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:='#039'fpmake'#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Function CurrentOS : String;'#013#010+
  #013#010+
  'beg','in'#013#010+
  '  Result:=OSToString(Defaults.OS);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function CurrentCPU : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=CPUToString(Defaults.CPU);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function OSToString(OS: TOS) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=LowerCase(GetenumName(TypeInfo(TOS),Ord(OS)));'#013,#010+
  'end;'#013#010+
  #013#010+
  'Function OSesToString(OSes: TOSes) : String;'#013#010+
  #013#010+
  'var'#013#010+
  '  i: TOS;'#013#010+
  '  Tmp: String;'#013#010+
  '  First: boolean;'#013#010+
  #013#010+
  'begin'#013#010+
  '  { can'#039't use SetToString, there are more than 32 OSes }'#013#010+
  '  First:=true;'#013#010+
  '  Result:='#039#039';'#013#010+
  '  for i in OSes do'#013#010+
  '    begin'#013#010+
  '   ','   if not First then'#013#010+
  '        Result:=Result+'#039','#039#013#010+
  '      else'#013#010+
  '        First:=false;'#013#010+
  '      Str(i,Tmp);'#013#010+
  '      Result:=Result+Tmp;'#013#010+
  '    end;'#013#010+
  '  Result:=LowerCase(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function CPUToString(CPU: TCPU) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:','=LowerCase(GetenumName(TypeInfo(TCPU),Ord(CPU)));'#013#010+
  'end;'#013#010+
  #013#010+
  'Function CPUSToString(CPUS: TCPUS) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=LowerCase(SetToString(PTypeInfo(TypeInfo(TCPUS)),Integer(CPU'+
  'S),False));'#013#010+
  'end;'#013#010+
  #013#010+
  'Function StringToOS(const S : Strin','g) : TOS;'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  I:=GetEnumValue(TypeInfo(TOS),S);'#013#010+
  '  if (I=-1) then'#013#010+
  '    Raise EInstallerError.CreateFmt(SErrInvalidOS,[S]);'#013#010+
  '  Result:=TOS(I);'#013#010+
  'end;'#013#010+
  #013#010+
  '(*'#013#010+
  'Function StringToOSes(const S : String) : TOSes;'#013#010+
  #013#010+
  'be','gin'#013#010+
  '  Result:=TOSes(StringToSet(PTypeInfo(TypeInfo(TOSes)),S));'#013#010+
  'end;'#013#010+
  '*)'#013#010+
  #013#010+
  'function IsDifferentFromBuild(ACpu: TCPU; AOs: TOs): boolean;'#013#010+
  'begin'#013#010+
  '  result := (AOs<>Defaults.BuildOS) or (ACpu<>Defaults.BuildCPU);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function StringTo','CPU(const S : String) : TCPU;'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  I:=GetEnumValue(TypeInfo(TCPU),S);'#013#010+
  '  if (I=-1) then'#013#010+
  '    Raise EInstallerError.CreateFmt(SErrInvalidCPU,[S]);'#013#010+
  '  Result:=TCPU(I);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function StringToCPUS(const S : Str','ing) : TCPUS;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=TCPUS(StringToSet(PTypeInfo(TypeInfo(TCPUS)),S));'#013#010+
  'end;'#013#010+
  #013#010+
  'Function ModeToString(Mode: TCompilerMode) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=LowerCase(GetenumName(TypeInfo(TCompilerMode),Ord(Mode)));'#013+
  #010+
  '  Delete(Resul','t,1,2);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function StringToMode(const S : String) : TCompilerMode;'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  I:=GetEnumValue(TypeInfo(TCompilerMode),S);'#013#010+
  '  if (I=-1) then'#013#010+
  '    Raise EInstallerError.CreateFmt(SErrInvalidMode,[S]);'#013#010+
  '  Result:','=TCompilerMode(I);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Function MakeTargetString(const aTarget : TCompileTarget; aLimit83 : B'+
  'oolean) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=aTarget.ToString(aLimit83);'#013#010+
  'end;'#013#010+
  #013#010+
  'Function MakeTargetString(const aTarget : TCompileTarget) : Strin','g;'#013+
  #010+
  #013#010+
  'begin'#013#010+
  '  Result:=aTarget.ToString((Defaults.BuildOS in AllLimit83fsOses) or ('+
  'aTarget.OS in AllLimit83fsOses));'#013#010+
  'end;'#013#010+
  #013#010+
  'Function MakeTargetString(CPU : TCPU;OS: TOS; aSubTarget : String = '#039+
  #039') : String;'#013#010+
  #013#010+
  'var'#013#010+
  '  CT : TCompileTarget;'#013#010,
  #013#010+
  'begin'#013#010+
  '  CT.CPU:=CPU;'#013#010+
  '  CT.OS:=OS;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result := MakeTargetString (CT);'#013#010+
  'end;'#013#010+
  #013#010+
  'function MakeZipSuffix(const aTarget : TCompileTarget; ALimit83: boole'+
  'an) : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  case aTarget.OS of'#013#010+
  '    go32v2: ','result := '#039'dos'#039';'#013#010+
  '    watcom: result := '#039'wat'#039';'#013#010+
  '    osNone:'#013#010+
  '      begin'#013#010+
  '        if ALimit83 then'#013#010+
  '          result := '#039'src'#039#013#010+
  '        else'#013#010+
  '          result := '#039'.source'#039#013#010+
  '      end'#013#010+
  '  else'#013#010+
  '    result := '#039'.'#039' + MakeTargetString(aTarget,ALim','it83);'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function MakeZipSuffix(CPU : TCPU;OS: TOS; aSubTarget : String; ALimit'+
  '83: boolean) : String;'#013#010+
  #013#010+
  'var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.CPU:=CPU;'#013#010+
  '  CT.OS:=OS;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result:=MakeZipSuffix','(CT,aLimit83);'#013#010+
  'end;'#013#010+
  #013#010+
  'function MakeZipSuffix(CPU : TCPU;OS: TOS; aSubTarget : String ='#039#039+
  ' ) : String;'#013#010+
  #013#010+
  'var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.CPU:=CPU;'#013#010+
  '  CT.OS:=OS;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result := MakeZipSuffix (CT,(Defaul','ts.BuildOS in AllLimit83fsOses)'+
  ' or (OS in AllLimit83fsOses));'#013#010+
  'end;'#013#010+
  #013#010+
  'Procedure StringToCPUOS(const S : String; Var CPU : TCPU; Var OS: TOS)'+
  ';'#013#010+
  #013#010+
  'Var'#013#010+
  '  P : integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  P:=Pos('#039'-'#039',S);'#013#010+
  '  If (P=0) then'#013#010+
  '    Raise EInstallerError.Cre','ateFmt(SErrInvalidTarget,[S]);'#013#010+
  '  CPU:=StringToCPU(Copy(S,1,P-1));'#013#010+
  '  OS:=StringToOs(Copy(S,P+1,Length(S)-P));'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Procedure ResolveDependencies(L : TDependencies; P : TNamedCollection)'+
  ';'#013#010+
  'Var'#013#010+
  '  I,J : Integer;'#013#010+
  '  C : TDependency;'#013#010+
  'be','gin'#013#010+
  '  If Assigned(L) then'#013#010+
  '    For I:=0 to L.Count-1 do'#013#010+
  '      begin'#013#010+
  '        C:=L[i];'#013#010+
  '        if C.DependencyType in [depPackage,depUnit] then'#013#010+
  '          begin'#013#010+
  '            J:=P.IndexOfName(C.Value);'#013#010+
  '            If J<>-1 then'#013#010+
  '         ','     C.Target:=P.Items[J];'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '//function AddConditionalStrings(APackage: TPackage; Dest : TStrings; '+
  'Src : TConditionalStrings;const aSubTarget : String; ACPU:TCPU;AOS:TOS'+
  '; Const APrefix : String='#039#039') : Int','eger ;'#013#010+
  'function AddConditionalStrings(APackage: TPackage; Dest : TStrings; Sr'+
  'c : TConditionalStrings; const aTarget : TCompileTarget; Const APrefix'+
  ' : String='#039#039') : Integer ;'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  C : TConditionalString;'#013#010+
  '  D : TPackageDic','tionary;'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  Result:=0;'#013#010+
  '  D := PackageDictionaryClass.Create(nil);'#013#010+
  '  D.MasterDictionary := APackage.Dictionary;'#013#010+
  '  try'#013#010+
  '    D.AddVariable('#039'CPU'#039',CPUToString(aTarget.CPU));'#013#010+
  '    D.AddVariable('#039'OS'#039',OSToString(aTarget.OS)',');'#013#010+
  '    D.AddVariable('#039'SUBTARGET'#039',aTarget.SubTarget);'#013#010+
  '    For I:=0 to Src.Count-1 do'#013#010+
  '      begin'#013#010+
  '        C:=Src[I];'#013#010+
  '        if (aTarget.CPU in C.CPUs) and (aTarget.OS in C.OSes) then'#013+
  #010+
  '          begin'#013#010+
  '            If (APrefix<>'#039#039') then'#013#010,
  '              S:=APrefix+C.Value'#013#010+
  '            else'#013#010+
  '              S:=C.Value;'#013#010+
  '            S := D.ReplaceStrings(s);'#013#010+
  '            if C is TConditionalDestString then'#013#010+
  '              begin'#013#010+
  '                // If a destination path is given, o','mit the path of '+
  'the sourcefile'#013#010+
  '                if TConditionalDestString(c).DestPath='#039#039' then'#013+
  #010+
  '                  Dest.values[S] :=  D.ReplaceStrings(IncludeTrailingP'+
  'athDelimiter(TConditionalDestString(c).DestPath))+S'#013#010+
  '                else'#013#010,
  '                  Dest.values[S] :=  D.ReplaceStrings(IncludeTrailingP'+
  'athDelimiter(TConditionalDestString(c).DestPath)+APrefix+ExtractFileNa'+
  'me(C.Value));'#013#010+
  '              end'#013#010+
  '            else'#013#010+
  '              Dest.Add(S);'#013#010+
  '            Inc(Resu','lt);'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    D.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function FileListToString(List : TStrings; const APrefix : String) : S'+
  'tring;'#013#010+
  'Var'#013#010+
  '  I : integer;'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  For I:=0 to List.Count-1 d','o'#013#010+
  '    begin'#013#010+
  '      If (I>0) then'#013#010+
  '        Result:=Result+'#039' '#039';'#013#010+
  '      S:=APrefix+List[i];'#013#010+
  '      If (Pos('#039' '#039',S)<>0) then'#013#010+
  '        S:='#039'"'#039'+S+'#039'"'#039';'#013#010+
  '      Result:=Result+S;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'Procedure PrependFileListWithString(List : TStrings;',' const APrefix :'+
  ' String);'#013#010+
  'Var'#013#010+
  '  I : integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  For I:=0 to List.Count-1 do'#013#010+
  '    List[i]:=APrefix+List[i];'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  #013#010+
  'function FixPath (const APath : String) : String;'#013#010+
  'begin'#013#010+
  '  Result := FixPath(APath, False);'#013#010+
  'end;'#013#010+
  #013#010+
  'functio','n FixPath (const APath : String; AIsDir : Boolean) : String;'#013+
  #010+
  'Var'#013#010+
  '  P : PChar;'#013#010+
  'begin'#013#010+
  '  Result:=APath;'#013#010+
  '  If (result<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      UniqueString(Result);'#013#010+
  '      P:=PChar(Result);'#013#010+
  '      While (P^<>#0) do'#013#010+
  '        begin'#013#010+
  '     ','     If P^ in ['#039'/'#039','#039'\'#039'] then'#013#010+
  '            P^:=PathDelim;'#013#010+
  '          Inc(P);'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  '  if AIsDir and (Result <> '#039#039') then'#013#010+
  '    Result := IncludeTrailingPathDelimiter(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  'function IsRelativePath(const APath: Stri','ng): boolean;'#013#010+
  'begin'#013#010+
  '  if APath='#039#039' then'#013#010+
  '    result := true'#013#010+
  '{$ifdef unix}'#013#010+
  '  else if APath[1] in AllowDirectorySeparators then'#013#010+
  '    result := false'#013#010+
  '{$else}'#013#010+
  '  else if ExtractFileDrive(APath)<>'#039#039' then'#013#010+
  '    result := false'#013#010+
  '{$endif}'#013#010+
  '  els','e'#013#010+
  '    result := true;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure ChangeDir(const APath : String);'#013#010+
  'begin'#013#010+
  '  if Not SetCurrentDir(APath) then'#013#010+
  '    Raise EInstallerError.CreateFmt(SErrChangeDirFailed,[APath]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure SearchFiles(AFileName, ASearchPath','Prefix: string; Recursiv'+
  'e: boolean; var List: TStrings);'#013#010+
  #013#010+
  '  procedure AddRecursiveFiles(const SearchDir, FileMask: string; Recur'+
  'sive: boolean);'#013#010+
  '  var'#013#010+
  '    Info : TSearchRec;'#013#010+
  '  begin'#013#010+
  '    if assigned(Installer) then'#013#010+
  '      Installer.Log(','VlDebug,Format(SDbgSearchingDir,[SearchDir]));'#013+
  #010+
  '    if FindFirst(SearchDir+AllFilesMask,faAnyFile and faDirectory,Info'+
  ')=0 then'#013#010+
  '    begin'#013#010+
  '      repeat'#013#010+
  '          if ((Info.Attr and faDirectory) = faDirectory) and (Info.Nam'+
  'e <> '#039'.'#039') and (In','fo.Name <> '#039'..'#039') and (Recursive) th'+
  'en'#013#010+
  '            AddRecursiveFiles(SearchDir + Info.Name + PathDelim, FileM'+
  'ask, Recursive);'#013#010+
  '          if ((Info.Attr and faDirectory) <> faDirectory) and IsWild(I'+
  'nfo.Name, FileMask, FileNameCaseSensitive) ','then'#013#010+
  '            List.Add(SearchDir + Info.Name);'#013#010+
  '      until FindNext(Info)<>0;'#013#010+
  '    end;'#013#010+
  '    {$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.FindClose(Info);'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  'var'#013#010+
  '  CurrDir,'#013#010+
  '  BasePath: string;'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  if I','sRelativePath(AFileName) and (ASearchPathPrefix<>'#039#039') the'+
  'n'#013#010+
  '    AFileName := IncludeTrailingPathDelimiter(ASearchPathPrefix) + AFi'+
  'leName;'#013#010+
  #013#010+
  '  BasePath := ExtractFilePath(ExpandFileName(AFileName));'#013#010+
  #013#010+
  '  AddRecursiveFiles(BasePath, ExtractFi','leName(AFileName), Recursive)'+
  ';'#013#010+
  #013#010+
  '  CurrDir:=GetCurrentDir;'#013#010+
  '  for i := 0 to Pred(List.Count) do'#013#010+
  '    List[i] := ExtractRelativepath(IncludeTrailingPathDelimiter(Includ'+
  'eTrailingPathDelimiter(CurrDir)+ASearchPathPrefix), List[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  'C','onst'#013#010+
  '  WhiteSpace = [#9,#10,#13,'#039' '#039'];'#013#010+
  '  QuoteChars = ['#039#039#039#039','#039'"'#039'];'#013#010+
  #013#010+
  'procedure SplitCommand(const Cmd : String; out Exe, Options : String);'+
  #013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  InQuote : Boolean;'#013#010+
  '  LastQuote : AnsiChar;'#013#010+
  '  S : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  S:','=Trim(Cmd);'#013#010+
  '  InQuote:=False;'#013#010+
  '  LastQuote:=#0;'#013#010+
  '  I:=1;'#013#010+
  '  While (I<=Length(S)) and (Inquote or not (S[I] in whiteSpace)) do'#013+
  #010+
  '    begin'#013#010+
  '    If S[i] in QuoteChars then'#013#010+
  '      begin'#013#010+
  '      InQuote:=Not (S[i]=LastQuote);'#013#010+
  '      If InQuote t','hen'#013#010+
  '         LastQuote:=S[i]'#013#010+
  '       else'#013#010+
  '         LastQuote:=#0;'#013#010+
  '      end;'#013#010+
  '    Inc(I);'#013#010+
  '    end;'#013#010+
  '  Exe:=Copy(S,1,I-1);'#013#010+
  '  Delete(S,1,I);'#013#010+
  '  Options:=Trim(S);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure AddCustomFpmakeCommandlineOption(const ACommandLineOptio','n,'+
  ' HelpMessage : string);'#013#010+
  'begin'#013#010+
  '  if not assigned(CustomFpmakeCommandlineOptions) then'#013#010+
  '    CustomFpmakeCommandlineOptions := TUnsortedCompilerOptionsStringLi'+
  'st.Create;'#013#010+
  '  CustomFpmakeCommandlineOptions.Values[ACommandLineOption]:=HelpMes','s'+
  'age;'#013#010+
  'end;'#013#010+
  #013#010+
  'function GetCustomFpmakeCommandlineOptionValue(const ACommandLineOptio'+
  'n: string): string;'#013#010+
  'begin'#013#010+
  '  if not assigned(CustomFpMakeCommandlineValues) then'#013#010+
  '    result := '#039#039#013#010+
  '  else'#013#010+
  '    result := CustomFpMakeCommandlineValues.Va','lues[ACommandLineOptio'+
  'n];'#013#010+
  'end;'#013#010+
  #013#010+
  'function AddProgramExtension(const ExecutableName: string; AOS : TOS):'+
  ' string;'#013#010+
  'begin'#013#010+
  '  if AOS in [Go32v2,Win32,Win64,Wince,Watcom] then'#013#010+
  '    Result:=ExecutableName+ExeExt'#013#010+
  '  else if AOS in [wasip1,wasip1','threads,wasip2] then'#013#010+
  '    Result:=ExecutableName+WasiExeExt'#013#010+
  '  else'#013#010+
  '    Result:=ExecutableName;'#013#010+
  'end;'#013#010+
  #013#010+
  'function AddLibraryExtension(const LibraryName: string; AOS : TOS): st'+
  'ring;'#013#010+
  'begin'#013#010+
  '  if AOS in [Go32v2,Win32,Win64,Wince,Watcom] then',#013#010+
  '    Result:=LibraryName+DLLExt'#013#010+
  '  else if aOS in [darwin,macosclassic,iphonesim,ios] then'#013#010+
  '    Result:=LibraryName+DyLibExt'#013#010+
  '  else if aOS = Aix then'#013#010+
  '    Result:=LibraryName+AIXSharedLibExt'#013#010+
  '  else if AOS in [wasip1,wasip1threads,wasip2]',' then'#013#010+
  '    Result:=LibraryName+WasiSharedLibExt'#013#010+
  '  else'#013#010+
  '    Result:=LibraryName+SharedLibExt;'#013#010+
  'end;'#013#010+
  #013#010+
  'function GetImportLibraryFilename(const UnitName: string; AOS: TOS): s'+
  'tring;'#013#010+
  'begin'#013#010+
  '  if AOS in [go32v2,watcom] then'#013#010+
  '    Result := '#039'li','bimp'#039'+UnitName'#013#010+
  '  else if AOS in [macosclassic] then'#013#010+
  '    Result := '#039'lib'#039'+UnitName'#013#010+
  '  else'#013#010+
  '    Result := '#039'libimp'#039'+UnitName;'#013#010+
  '  Result := Result + LibExt;'#013#010+
  'end;'#013#010+
  #013#010+
  'Function OptionListToString(L : TStrings) : String;'#013#010+
  #013#010+
  'var'#013#010+
  '  I : Integer;'#013#010,
  '  S : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  For I:=0 to L.Count-1 do'#013#010+
  '    begin'#013#010+
  '    If (Result<>'#039#039') then'#013#010+
  '      Result:=Result+'#039' '#039';'#013#010+
  '    S:=L[I];'#013#010+
  '    If (Pos('#039' '#039',S)<>0) or (S='#039#039') then'#013#010+
  '      Result:= Result + '#039'"'#039'+S+'#039'"'#039#013#010+
  '    else'#013#010+
  '      Resul','t:= Result + S;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'Function OptionsToStringList(S : String) : TStrings;'#013#010+
  #013#010+
  'Var'#013#010+
  '  P : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=Nil;'#013#010+
  '  If (S='#039#039') then'#013#010+
  '    Exit;'#013#010+
  '  Result:=TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  Repeat'#013#010+
  '    P:=Pos','('#039' '#039',S);'#013#010+
  '    If P=0 then'#013#010+
  '      P:=Length(S)+1;'#013#010+
  '    Result.Add(Copy(S,1,P-1));'#013#010+
  '    Delete(S,1,P);'#013#010+
  '    S:=Trim(S);'#013#010+
  '  Until Length(S)=0;'#013#010+
  '  If Result.Count=0 then'#013#010+
  '    FreeAndNil(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '{ function ','GetCompilerInfo'#013#010+
  '  used both for gcc and Free Pascal compiler'#013#010+
  '  returns stdout output of Acompiler with AOptions parameters'#013#010+
  '  If ReadStdErr is True, return stderr output if stdout is empty'#013#010+
  '  If EmptyIfStdErr, return empty string if stder','r output is not empt'+
  'y }'#013#010+
  #013#010+
  'function GetCompilerInfo(const ACompiler:string; Args : TStrings; Read'+
  'StdErr: boolean;EmptyIfStdErr : boolean):ansistring;'#013#010+
  #013#010+
  'const'#013#010+
  '  BufSize = 1024;'#013#010+
  'Type'#013#010+
  '  TBufType = array [0..BufSize - 1] of AnsiChar;'#013#010+
  #013#010+
  'var',#013#010+
  '  Proc: TProcess;'#013#010+
  '  Buf: TBufType;'#013#010+
  '  ErrorBuf: TBufType;'#013#010+
  '  Count, ErrorCount: longint;'#013#010+
  #013#010+
  #013#010+
  'begin'#013#010+
  '  buf:=Default(TBufType);'#013#010+
  '  ErrorBuf:=Default(TBufType);'#013#010+
  '  Proc:=TProcess.Create(Nil);'#013#010+
  '  try'#013#010+
  '    Proc.Executable:=ACompiler;'#013#010+
  '    Pr','oc.Parameters:=Args;'#013#010+
  '    Proc.Options:=[poUsePipes,poWaitOnExit];'#013#010+
  '    Proc.execute;'#013#010+
  '    Count:=Proc.output.read(buf,BufSize);'#013#010+
  '    if (count=0) and ReadStdErr then'#013#010+
  '      Count:=Proc.Stderr.read(buf,BufSize)'#013#010+
  '    else if EmptyIfStdErr th','en'#013#010+
  '      begin'#013#010+
  '        ErrorCount:=Proc.StdErr.read(ErrorBuf,BufSize);'#013#010+
  '        if (ErrorCount>0) then'#013#010+
  '          begin'#013#010+
  '            Result:='#039#039';'#013#010+
  '            exit;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    Proc.Free;'#013#010+
  '  end;'#013#010+
  '  SetLengt','h(Result,Count);'#013#010+
  '  Move(Buf,Result[1],Count);'#013#010+
  'end;'#013#010+
  #013#010+
  '// Convenience function'#013#010+
  #013#010+
  'function GetCompilerInfo(const ACompiler:string; aOptions : Array of S'+
  'tring; ReadStdErr: boolean;EmptyIfStdErr : boolean):ansistring;'#013#010+
  #013#010+
  'Var'#013#010+
  '  Args : TStrin','gs;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Args:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    Args.AddStrings(aOptions);'#013#010+
  '    Result:=GetCompilerInfo(aCompiler,Args,ReadStdErr,EmptyIfStdErr);'#013+
  #010+
  '  finally'#013#010+
  '    Args.Free;'#013#010+
  '  end;'#013#010+
  #013#010+
  'end;'#013#010+
  #013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  #013#010+
  'function GetD','efaultLibGCCDir(CPU : TCPU;OS: TOS; out ErrorMessage: s'+
  'tring): string;'#013#010+
  #013#010+
  'var'#013#010+
  '  CrossPrefix: Ansistring;'#013#010+
  '  UseBinutilsPrefix: boolean;'#013#010+
  '  SourceOS : TOS;'#013#010+
  '  SourceCPU : TCPU;'#013#010+
  #013#010+
  '  function Get4thWord(const AString: Ansistring): Ansistring',';'#013#010+
  '  var p: PAnsiChar;'#013#010+
  '      spacecount: integer;'#013#010+
  '      StartWord: PAnsiChar;'#013#010+
  '  begin'#013#010+
  '    result:='#039#039';'#013#010+
  '    if length(AString)>6 then'#013#010+
  '      begin'#013#010+
  '      p := @AString[1];'#013#010+
  '      spacecount:=0;'#013#010+
  '      StartWord:=nil;'#013#010+
  '      while (not (p','^ in [#0,#10,#13])) and ((p^<>'#039' '#039') or (St'+
  'artWord=nil)) do'#013#010+
  '        begin'#013#010+
  '        if p^='#039' '#039' then'#013#010+
  '          begin'#013#010+
  '          inc(spacecount);'#013#010+
  '          if spacecount=3 then StartWord:=p+1;'#013#010+
  '          end;'#013#010+
  '        inc(p);'#013#010+
  '        end;'#013#010+
  '  ','    if StartWord<>nil then'#013#010+
  '        begin'#013#010+
  '        SetLength(result,p-StartWord);'#013#010+
  '        move(StartWord^,result[1],p-StartWord);'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '        result := '#039#039';'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  function GetGccDirArch(const ACpuTyp','e : AnsiString; GCCParams: TSt'+
  'rings) : Ansistring;'#013#010+
  #013#010+
  '  var ExecResult: Ansistring;'#013#010+
  '      libgccFilename: Ansistring;'#013#010+
  '      GccExecutable: string;'#013#010+
  '      Parms : TStrings;'#013#010+
  #013#010+
  '  begin'#013#010+
  '    result := '#039#039';'#013#010+
  '    Parms:=TStringList.Create;'#013#010+
  '   ',' try'#013#010+
  '    GccExecutable := ExeSearch(AddProgramExtension(CrossPrefix+'#039'gc'+
  'c'#039', OS),{$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.GetEnviron'+
  'mentVariable('#039'PATH'#039'));'#013#010+
  '    if not(FileExists(GccExecutable)) then'#013#010+
  '      GccExecutable := ExeSearch(A','ddProgramExtension(CrossPrefix+'#039+
  'gnu-gcc'#039', OS),{$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.GetE'+
  'nvironmentVariable('#039'PATH'#039'));'#013#010+
  '    if not(FileExists(GccExecutable)) and (CrossPrefix='#039'i386-linux'+
  '-'#039') then'#013#010+
  '      GccExecutable := ExeSearch(Add','ProgramExtension('#039'i686-linux'+
  '-gnu-gcc'#039', OS),{$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}Sysutils.Get'+
  'EnvironmentVariable('#039'PATH'#039'));'#013#010+
  '    if FileExists(GccExecutable) then'#013#010+
  '      begin'#013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '      Parms.Add('#039'-v'#039');'#013#010+
  '      Parms.','AddStrings(GCCParams);'#013#010+
  '      ExecResult:=GetCompilerInfo(GccExecutable,Parms, True, True);'#013+
  #010+
  '      libgccFilename:=Get4thWord(ExecResult);'#013#010+
  '      // Use IsRelativePath to check if the 4th word is an (absolute) '+
  'path.'#013#010+
  '      // This depends o','n the language settings. In English the 4th w'+
  'ord is'#013#010+
  '      // empty, if this particular gcc version does not return the lib'+
  'gcc-'#013#010+
  '      // filename on -v. But in other languages (e.g. Dutch) it may be'+
  ' another'#013#010+
  '      // word.'#013#010+
  '      if IsRela','tivePath(libgccFilename) then'#013#010+
  '        libgccFilename:='#039#039';'#013#010+
  '      if libgccFilename='#039#039' then'#013#010+
  '        begin'#013#010+
  '        Parms[0]:='#039'--print-libgcc-file-name'#039';'#013#010+
  '        libgccFilename:=GetCompilerInfo(GccExecutable,Parms, False, Tr'+
  'ue);'#013#010+
  '        e','nd;'#013#010+
  '      result := ExtractFileDir(libgccFilename);'#013#010+
  '{$else HAS_UNIT_PROCESS}'#013#010+
  '      ErrorMessage := SWarnNoFCLProcessSupport;'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  '      end'#013#010+
  '    else if UseBinutilsPrefix then'#013#010+
  '      ErrorMessage := SWarncrossgccNo','tFound'#013#010+
  '    else'#013#010+
  '      ErrorMessage := SWarngccNotFound;'#013#010+
  #013#010+
  '    finally'#013#010+
  '      Parms.Free;'#013#010+
  '    end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  function GetGccDirArch(const ACpuType : String; GCCParams: Array of '+
  'String) : string;'#013#010+
  '  var'#013#010+
  '    Args : TStrings;'#013#010+
  #013#010+
  '  begin',#013#010+
  '    Args:=TStringList.Create;'#013#010+
  '    try'#013#010+
  '      Args.AddStrings(GCCParams);'#013#010+
  '      Result:=GetGCCDirArch(aCPUType,Args);'#013#010+
  '    finally'#013#010+
  '      Args.Free;'#013#010+
  '    end;'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  'begin'#013#010+
  '  result := '#039#039';'#013#010+
  '  ErrorMessage:='#039#039';'#013#010+
  '  if assigned(Defaul','ts) then'#013#010+
  '    begin'#013#010+
  '      SourceOS:=Defaults.SourceOS;'#013#010+
  '      SourceCPU:=Defaults.SourceCPU;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      SourceOS:=StringToOS({$I %FPCTARGETOS%});'#013#010+
  '      SourceCPU:=StringToCPU({$I %FPCTARGETCPU%});'#013#010+
  '    end;'#013#010+
  #013#010+
  '  Us','eBinutilsPrefix:=(SourceOS<>OS);'#013#010+
  '  if (SourceCPU<>CPU) then'#013#010+
  '    begin'#013#010+
  '      { we need to accept 32<->64 conversion }'#013#010+
  '      { expect for OpenBSD which does not allow this }'#013#010+
  '      if not('#013#010+
  '         ((SourceCPU=aarch64) and (CPU=arm)) or'#013,#010+
  '         ((SourceCPU=powerpc64) and (CPU=powerpc)) or'#013#010+
  '         ((SourceCPU=x86_64) and (CPU=i386)) or'#013#010+
  '         ((SourceCPU=riscv64) and (CPU=riscv32)) or'#013#010+
  '         ((SourceCPU=sparc64) and (CPU=sparc)) or'#013#010+
  '         ((CPU=aarch64) and (So','urceCPU=arm)) or'#013#010+
  '         ((CPU=powerpc64) and (SourceCPU=powerpc)) or'#013#010+
  '         ((CPU=x86_64) and (SourceCPU=i386)) or'#013#010+
  '         ((CPU=riscv64) and (SourceCPU=riscv32)) or'#013#010+
  '         ((CPU=sparc64) and (SourceCPU=sparc))'#013#010+
  '         ) or (So','urceOS=openbsd) then'#013#010+
  '        UseBinutilsPrefix:=true;'#013#010+
  '    end;'#013#010+
  '  if {$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.GetEnvironmentVar'+
  'iable('#039'BINUTILSPREFIX'#039')<>'#039#039' then'#013#010+
  '    CrossPrefix:={$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.GetEn',
  'vironmentVariable('#039'BINUTILSPREFIX'#039')'#013#010+
  '  else if not UseBinutilsPrefix then'#013#010+
  '    CrossPrefix:='#039#039#013#010+
  '  else'#013#010+
  '    CrossPrefix:=CPUToString(CPU)+'#039'-'#039'+OSToString(OS)+'#039'-'#039+
  ';'#013#010+
  '  if OS in [freebsd, openbsd, dragonfly] then'#013#010+
  '    begin'#013#010+
  '      if CrossPrefi','x='#039#039' then'#013#010+
  '        result := '#039'/usr/local/lib'#039#013#010+
  '    end'#013#010+
  '  else if OS = netbsd then'#013#010+
  '    begin'#013#010+
  '      if CrossPrefix='#039#039' then'#013#010+
  '        result := '#039'/usr/pkg/lib'#039#013#010+
  '    end'#013#010+
  '  else if OS = linux then'#013#010+
  '    case CPU of'#013#010+
  '      i386:         result :','= GetGccDirArch('#039'cpui386'#039',['#039'-'+
  'm32'#039']);'#013#010+
  '      x86_64:       result := GetGccDirArch('#039'cpux86_64'#039',['#039'-'+
  'm64'#039']);'#013#010+
  '      powerpc:      result := GetGccDirArch('#039'cpupowerpc'#039',['#039+
  '-m32'#039']);'#013#010+
  '      powerpc64:    result := GetGccDirArch('#039'cpupowerpc64'#039',['#039+
  '-m64',#039']);'#013#010+
  '      arm:          result := GetGccDirArch('#039'cpuarm'#039',['#039'-ma'+
  'rm'#039','#039'-march=armv2'#039']);'#013#010+
  '      aarch64:      result := GetGccDirArch('#039'cpuaarch64'#039',['#039+
  '-march=aarch64'#039','#039'-mcmodel=large'#039']);'#013#010+
  '      m68k:         result := GetGccDirArch('#039'cpum68k'#039',['#039'-',
  'march=68020'#039']);'#013#010+
  '      mips:         result := GetGccDirArch('#039'cpumips'#039',['#039'-m'+
  'ips32'#039','#039'-EB'#039','#039'-mabi=32'#039']);'#013#010+
  '      mipsel:       result := GetGccDirArch('#039'cpumipsel'#039',['#039'-'+
  'mips32'#039','#039'-EL'#039','#039'-mabi=32'#039']);'#013#010+
  '      mips64el:     result := GetGccDirArch('#039'cpum','ipsel'#039',['#039+
  '-mips64'#039','#039'-EL'#039','#039'-mabi=64'#039']);'#013#010+
  '      mips64:       result := GetGccDirArch('#039'cpumipsel'#039',['#039'-'+
  'mips64'#039','#039'-EB'#039','#039'-mabi=64'#039']);'#013#010+
  '      riscv32:      result := GetGccDirArch('#039'cpuriscv32'#039',['#039+
  '-march=rv32imafdc'#039']);'#013#010+
  '      riscv64:      result := G','etGccDirArch('#039'cpuriscv64'#039',['#039+
  '-march=rv64imafdc'#039']);'#013#010+
  '      sparc:        result := GetGccDirArch('#039'cpusparc'#039',['#039'-'+
  'm32'#039']);'#013#010+
  '      sparc64:      result := GetGccDirArch('#039'cpusparc64'#039',['#039+
  '-m64'#039']);'#013#010+
  '      xtensa:       result := GetGccDirArch('#039'cpuxtens','a'#039',[]);'+
  #013#010+
  '      loongarch64:  result := GetGccDirArch('#039'cpuloongarch64'#039',['+
  ']);'#013#010+
  '    else'#013#010+
  '      ; // avoid compiler warning'#013#010+
  '    end {case}'#013#010+
  '  else if OS = darwin then'#013#010+
  '    case CPU of'#013#010+
  '      i386:     result := GetGccDirArch('#039'cpui386'#039',['#039'-arch'#039,
  ', '#039'i386'#039']);'#013#010+
  '      x86_64:   result := GetGccDirArch('#039'cpux86_64'#039',['#039'-arc'+
  'h'#039','#039'x86_64'#039']);'#013#010+
  '      powerpc:  result := GetGccDirArch('#039'cpupowerpc'#039',['#039'-ar'+
  'ch'#039','#039'ppc'#039']);'#013#010+
  '      powerpc64:result := GetGccDirArch('#039'cpupowerpc64'#039',['#039'-'+
  'arch'#039','#039'ppc64'#039']);'#013#010+
  '     ',' { this target uses clang }'#013#010+
  '      aarch64:  result := '#039#039#013#010+
  '    else'#013#010+
  '      ; // Avoid compiler warning'#013#010+
  '    end; {case}'#013#010+
  'end;'#013#010+
  #013#010+
  'function GetPluginManager: TfpmPluginManager;'#013#010+
  'begin'#013#010+
  '  if not assigned(GPluginManager) then'#013#010+
  '    GPluginManage','r := TfpmPluginManager.Create;'#013#010+
  '  Result := GPluginManager;'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TConditionalDestString }'#013#010+
  #013#010+
  'procedure TConditionalDestString.Assign(aSource: TPersistent);'#013#010+
  #013#010+
  'Var'#013#010+
  '  CDS : TConditionalDestString absolute aSource;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if aSourc','e is TConditionalDestString then'#013#010+
  '    begin'#013#010+
  '    FDestPath:=CDS.DestPath;'#013#010+
  '    end;'#013#010+
  '  inherited Assign(aSource);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TDependencyEnumerator }'#013#010+
  #013#010+
  'function TDependencyEnumerator.GetCurrent: TDependency;'#013#010+
  'begin'#013#010+
  '  Result:=TDependency(in','herited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TCompileTarget }'#013#010+
  #013#010+
  'function TCompileTarget.GetAsString: String;'#013#010+
  'begin'#013#010+
  '  Result:=ToString(False);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCompileTarget.SetAsString(const aValue: String);'#013#010+
  #013#010+
  'var'#013#010+
  '  P :  Integer;'#013#010+
  '  aTarget : st','ring;'#013#010+
  #013#010+
  'begin'#013#010+
  '  aTarget:=aValue;'#013#010+
  '  P:=Pos('#039'-'#039',aTarget);'#013#010+
  '  If (P=0) then'#013#010+
  '    OS:=StringToOS(aTarget)'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    CPU:=StringToCPU(System.Copy(aTarget,1,P-1));'#013#010+
  '    Delete(aTarget,1,P);'#013#010+
  '    P:=Pos('#039'-'#039',aTarget);'#013#010+
  '    if P=0 t','hen'#013#010+
  '      OS:=StringToOS(aTarget)'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '      OS:=StringToOS(System.Copy(aTarget,1,P-1));'#013#010+
  '      Delete(aTarget,1,P);'#013#010+
  '      SubTarget:=aTarget;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCompileTarget.Equals(const aValue: ','TCompileTarget): Boolea'+
  'n;'#013#010+
  'begin'#013#010+
  '  Result:=(OS=aValue.OS) and (CPU=aValue.CPU) and (Subtarget=aValue.Su'+
  'bTarget);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCompileTarget.ToString(aLimit83: Boolean): String;'#013#010+
  'begin'#013#010+
  '  if ALimit83 then'#013#010+
  '    Result := OSToString(OS)',#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    Result:=CPUToString(CPU)+'#039'-'#039'+OSToString(OS);'#013#010+
  '    if SubTarget<>'#039#039' then'#013#010+
  '      Result:=Result+'#039'-'#039'+LowerCase(SubTarget);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TPackageEnumerator }'#013#010+
  #013#010+
  'function TPackageEnumerator.GetCurrent: TPackage;'#013,#010+
  'begin'#013#010+
  '  Result:=TPackage(Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TCommandEnumerator }'#013#010+
  #013#010+
  'function TCommandEnumerator.GetCurrent: TCommand;'#013#010+
  'begin'#013#010+
  '  Result:= TCommand(Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TNotifyEventEnumerator }'#013#010+
  #013#010+
  'function TNotif','yEventEnumerator.GetCurrent: TNotifyEventItem;'#013#010+
  'begin'#013#010+
  '  Result:= TNotifyEventItem( Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TPackageVariantEnumerator }'#013#010+
  #013#010+
  'function TPackageVariantEnumerator.GetCurrent: TPackageVariant;'#013#010+
  'begin'#013#010+
  '  Result:= TPackage','Variant( Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TTargetEnumerator }'#013#010+
  #013#010+
  'function TTargetEnumerator.GetCurrent: TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=TTarget(Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TSourceEnumerator }'#013#010+
  #013#010+
  'function TSourceEnumerator.GetCurrent: TSou','rce;'#013#010+
  'begin'#013#010+
  '  Result:=TSource(Inherited GetCurrent);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{ TResourceFiles }'#013#010+
  #013#010+
  'procedure TResourceFiles.GetInstallFiles(AList: TStrings; const APrefi'+
  'xU, APrefixB: String; ACPU: TCPU; AOS: TOS);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  R : TResourceF','ile;'#013#010+
  'begin'#013#010+
  '  For I:=0 to Count-1 do'#013#010+
  '    begin'#013#010+
  '    R:=Tobject(Items[I]) as TResourceFile;'#013#010+
  '    if (ACPU in R.CPUs) and (AOS in R.OSes) then'#013#010+
  '      AList.Add(ConcatPaths([APrefixU, R.Value]));'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TfpmResolvePackagePathsP','lugin }'#013#010+
  #013#010+
  'procedure TfpmResolvePackagePathsPlugin.ResolveUnitConfigFilenameForBa'+
  'sePath('#013#010+
  '  ABuildEngine: TBuildEngine; APackage: TPackage; ABasePath: string;'#013+
  #010+
  '  out AContinue: Boolean);'#013#010+
  'var'#013#010+
  '  IsPackageSourceLocation: boolean;'#013#010+
  '  ASubDir:',' string;'#013#010+
  '  AnUnitConfigFilename: string;'#013#010+
  '  PackageBaseDir: string;'#013#010+
  'begin'#013#010+
  '  if APackage.State=tsNotFound then'#013#010+
  '    // When the state is tsNotFound, the package is not part of this f'+
  'pmake, and only the package-name is known.'#013#010+
  '    // In th','is case search for the package-name.'#013#010+
  '    // This is not right for packages where the package-name and direc'+
  'tory name of the source-files are'#013#010+
  '    // not the same. We don'#039't have a better option, though.'#013#010+
  '    ASubDir:=APackage.Name'#013#010+
  '  else'#013#010,
  '    ASubDir:=APackage.Directory;'#013#010+
  #013#010+
  '  IsPackageSourceLocation:=ABuildEngine.SysFileExists(IncludeTrailingP'+
  'athDelimiter(IncludeTrailingPathDelimiter(ABasePath)+ASubDir)+FPMakePP'+
  'File);'#013#010+
  '  if IsPackageSourceLocation then'#013#010+
  '    begin'#013#010+
  '      Pack','ageBaseDir:=IncludeTrailingPathDelimiter(IncludeTrailingPa'+
  'thDelimiter(ABasePath)+ASubDir);'#013#010+
  '      AnUnitConfigFileName:=PackageBaseDir+APackage.GetUnitConfigOutpu'+
  'tFilename(Defaults.CompileTarget);'#013#010+
  '      PackageBaseDir:=IncludeTrailingPathD','elimiter(PackageBaseDir+AP'+
  'ackage.GetUnitsOutputDir(Defaults.CompileTarget));'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      PackageBaseDir:=IncludeTrailingPathDelimiter(ABasePath);'#013#010+
  '      AnUnitConfigFileName:=IncludeTrailingPathDelimiter(ABuildEngine.',
  'GetUnitConfigFilesInstallDir(ABasePath))+APackage.Name+FpmkExt;'#013#010+
  '      PackageBaseDir:=IncludeTrailingPathDelimiter(IncludeTrailingPath'+
  'Delimiter(ABasePath)+APackage.GetUnitsOutputDir(Defaults.CompileTarget'+
  '))+APackage.Name;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  if',' (PackageBaseDir<>'#039#039') and ABuildEngine.SysDirectoryExists('+
  'PackageBaseDir) then'#013#010+
  '    begin'#013#010+
  '      AnUnitConfigFilename:=APackage.Dictionary.ReplaceStrings(AnUnitC'+
  'onfigFilename);'#013#010+
  '      if ABuildEngine.SysFileExists(AnUnitConfigFilename) then',#013#010+
  '        APackage.UnitConfigFileName:=AnUnitConfigFilename'#013#010+
  '      else'#013#010+
  '        begin'#013#010+
  '          // To avoid that directories which do not contain installed '+
  'packages'#013#010+
  '          // check that there is an unit-configfile, or Packages.fpc f'+
  'il','e. (The'#013#010+
  '          // latter to detect packages compiled using old style Makefi'+
  'le'#039's, like'#013#010+
  '          // the rtl). These directories which are not packages may ex'+
  'ist in'#013#010+
  '          // Lazarus-source-repositories.'#013#010+
  '          if not ABuildEngin','e.SysFileExists(ConcatPaths([PackageBase'+
  'Dir, '#039'Package.fpc'#039'])) then'#013#010+
  '            begin'#013#010+
  '              if IsPackageSourceLocation then'#013#010+
  '                begin'#013#010+
  '                // There is no way that I know of to confirm that a di'+
  'rectory'#013#010+
  '    ','            // contains the compiled sources of the rtl. So we n'+
  'eed a'#013#010+
  '                // workaround. This test is skipped in case of the rtl'+
  '.'#013#010+
  '                if APackage.Name<>'#039'rtl'#039' then'#013#010+
  '                  begin'#013#010+
  '                  Install','er.Log(vlInfo,Format(SInfoSrcDirectoryNoPkg'+
  ',[PackageBaseDir, APackage.Name]));'#013#010+
  '                  Exit;'#013#010+
  '                  end;'#013#010+
  '                end'#013#010+
  '              else'#013#010+
  '                begin'#013#010+
  '                Installer.Log(vlInfo,Format(SIn','foDirectoryNoPackage,'+
  '[PackageBaseDir, APackage.Name]));'#013#010+
  '                Exit;'#013#010+
  '                end;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  #013#010+
  '      APackage.UnitDir:=PackageBaseDir;'#013#010+
  '      AContinue := False;'#013#010+
  #013#010+
  '      if IsPackageSourceLocation t','hen'#013#010+
  '        // Set the state to tsNoCompile and not tsCompiled. Because pa'+
  'ckages'#013#010+
  '        // in the tsCompiled state trigger a rebuild of packages that '+
  'depend'#013#010+
  '        // on it.'#013#010+
  '        APackage.FTargetState:=tsNoCompile'#013#010+
  '      else if no','t (APackage.FTargetState in [tsCompiled, tsNoCompile'+
  ']) then'#013#010+
  '        APackage.FTargetState:=tsInstalled;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    AContinue := True;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmResolvePackagePathsPlugin.BeforeResolvePackagePath(ABuil'+
  'dEngine: TBuild','Engine;'#013#010+
  '  APackage: TPackage; out AContinue: Boolean);'#013#010+
  'begin'#013#010+
  '  if (APackage.State in [tsCompiled, tsNoCompile, tsInstalled]) then'#013+
  #010+
  '    ResolveUnitConfigFilenameForBasePath(ABuildEngine, APackage, ABuil'+
  'dEngine.StartDir, AContinue)'#013#010+
  '  else',#013#010+
  '    AContinue := True;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmResolvePackagePathsPlugin.ResolvePackagePath(ABuildEngin'+
  'e: TBuildEngine;'#013#010+
  '  APackage: TPackage; SearchPath: string; out AContinue: Boolean);'#013+
  #010+
  'begin'#013#010+
  '  ResolveUnitConfigFilenameForBasePath(ABui','ldEngine, APackage, Searc'+
  'hPath, AContinue)'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TfpmPlugin }'#013#010+
  #013#010+
  'function TfpmPlugin.GetName: string;'#013#010+
  'begin'#013#010+
  '  Result := ClassName;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPlugin.BeforeResolvePackagePath(ABuildEngine: TBuildEngi'+
  'ne; APackage: TPackage;',#013#010+
  '  out AContinue: Boolean);'#013#010+
  'begin'#013#010+
  '  AContinue := True;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPlugin.ResolvePackagePath(ABuildEngine: TBuildEngine; AP'+
  'ackage: TPackage;'#013#010+
  '  SearchDirectory: string; out AContinue: Boolean);'#013#010+
  'begin'#013#010+
  '  AContinue := True;'#013#010+
  'en','d;'#013#010+
  #013#010+
  'procedure TfpmPlugin.AfterResolvePackagePath(ABuildEngine: TBuildEngin'+
  'e; APackage: TPackage;'#013#010+
  '  out AContinue: Boolean);'#013#010+
  'begin'#013#010+
  '  AContinue := True;'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TfpmPluginManager }'#013#010+
  #013#010+
  'destructor TfpmPluginManager.Destroy;'#013#010+
  'var'#013#010+
  '  i: I','nteger;'#013#010+
  'begin'#013#010+
  '  for i := 0 to High(FPlugins) do'#013#010+
  '    FPlugins[i].Free;'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPluginManager.RegisterPlugin(APlugin: TfpmPluginClass);'#013+
  #010+
  'begin'#013#010+
  '  SetLength(FPlugins, Length(FPlugins)+1);'#013#010+
  '  FPlugins[hig','h(FPlugins)] := APlugin.Create;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPluginManager.BeforeResolvePackagePath(ABuildEngine: TBu'+
  'ildEngine; APackage: TPackage;'#013#010+
  '  out AContinue: Boolean);'#013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  'begin'#013#010+
  '  for i := 0 to high(FPlugins) do'#013#010+
  '    beg','in'#013#010+
  '      FPlugins[i].BeforeResolvePackagePath(ABuildEngine, APackage, ACo'+
  'ntinue);'#013#010+
  '      if not AContinue then'#013#010+
  '        Exit;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPluginManager.ResolvePackagePath(ABuildEngine: TBuildEng'+
  'ine; APackage: TPackage;',#013#010+
  '  SearchPath: string; out AContinue: Boolean);'#013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  'begin'#013#010+
  '  for i := 0 to high(FPlugins) do'#013#010+
  '    begin'#013#010+
  '      FPlugins[i].ResolvePackagePath(ABuildEngine, APackage, SearchPat'+
  'h, AContinue);'#013#010+
  '      if not AContinue then'#013#010+
  '  ','      Exit;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TfpmPluginManager.AfterResolvePackagePath(ABuildEngine: TBui'+
  'ldEngine; APackage: TPackage;'#013#010+
  '  out AContinue: Boolean);'#013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  'begin'#013#010+
  '  for i := 0 to high(FPlugins) do'#013#010+
  '    begin'#013#010+
  '      F','Plugins[i].AfterResolvePackagePath(ABuildEngine, APackage, AC'+
  'ontinue);'#013#010+
  '      if not AContinue then'#013#010+
  '        Exit;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'constructor TPackageVariant.Create(ACollection: TCollection);'#013#010+
  'begin'#013#010+
  '  inherited Create(ACollection);'#013#010+
  '  ','FTargets := TTargets.Create(TTarget);'#013#010+
  '  FOptions := TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  FIncludePath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FSourcePath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  'end;'#013#010+
  #013#010+
  'destru','ctor TPackageVariant.Destroy;'#013#010+
  'begin'#013#010+
  '  FOptions.Free;'#013#010+
  '  FTargets.Free;'#013#010+
  '  FIncludePath.Free;'#013#010+
  '  FSourcePath.Free;'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackageVariant.AddOption(const aValue: string);'#013#010+
  'begin'#013#010+
  '  Options.Add(aValue);'#013#010+
  'en','d;'#013#010+
  #013#010+
  '{ TPackageVariants }'#013#010+
  #013#010+
  'procedure TPackageVariants.SetDefaultPackageVariantName(AValue: string'+
  ');'#013#010+
  'begin'#013#010+
  '  if FDefaultPackageVariantName=AValue then Exit;'#013#010+
  '  if not assigned(ItemByName(avalue)) then'#013#010+
  '    raise exception.CreateFmt(SErr','PackVarNotExist,[AValue]);'#013#010+
  '  FDefaultPackageVariantName:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackageVariants.GetActivePackageVariant: TPackageVariant;'#013+
  #010+
  'begin'#013#010+
  '  result := ItemByName(ActivePackageVariantName) as TPackageVariant;'#013+
  #010+
  'end;'#013#010+
  #013#010+
  'function TP','ackageVariants.GetDefaultPackageVariant: TPackageVariant;'+
  #013#010+
  'begin'#013#010+
  '  result := ItemByName(DefaultPackageVariantName) as TPackageVariant;'#013+
  #010+
  'end;'#013#010+
  #013#010+
  'procedure TPackageVariants.SetActivePackageVariantName(AValue: string)'+
  ';'#013#010+
  'begin'#013#010+
  '  if FActivePac','kageVariantName=AValue then Exit;'#013#010+
  '  if not assigned(ItemByName(avalue)) then'#013#010+
  '    raise exception.CreateFmt(SErrPackVarNotExist,[AValue]);'#013#010+
  '  FActivePackageVariantName:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackageVariants.Add(AName: String): TPackag','eVariant;'#013#010+
  'begin'#013#010+
  '  result := self.add as TPackageVariant;'#013#010+
  '  result.Name := AName;'#013#010+
  '  if FDefaultPackageVariantName='#039#039' then'#013#010+
  '    FDefaultPackageVariantName:=AName;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackageVariants.GetEnumerator: TPackageVariantEnumerator',';'#013+
  #010+
  'begin'#013#010+
  '  Result:= TPackageVariantEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{ TConditionalDestStrings }'#013#010+
  #013#010+
  'function TConditionalDestStrings.GetConditionalString(Index : Integer)'+
  ': TConditionalDestString;'#013#010+
  'begin'#013#010+
  '  Result:=TConditionalDestString(','Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TConditionalDestStrings.SetConditionalString(Index : Integer'+
  '; AValue: TConditionalDestString);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  'constructor TConditionalDestStrings.Create(AClass: TConditionalDestStr',
  'ingClass);'#013#010+
  'begin'#013#010+
  '  inherited Create(AClass);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TConditionalDestStrings.Add(const Value: String; ADestPath: S'+
  'tring): TConditionalDestString;'#013#010+
  'begin'#013#010+
  '  Result:=Add(Value, AllCPUs, AllOSes, ADestPath);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCond','itionalDestStrings.Add(const Value: String; const OSes'+
  ': TOSes; ADestPath: String): TConditionalDestString;'#013#010+
  'begin'#013#010+
  '  Result:=Add(Value, AllCPUs, OSes, ADestPath);'#013#010+
  'end;'#013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TConditionalDestStrings.Add(Co','nst Value : String;const CPUs'+
  ':TCPUs; ADestPath: String) : TConditionalDestString;inline;'#013#010+
  'begin'#013#010+
  '  Result:=Add(Value, CPUs, AllOSes, ADestPath);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TConditionalDestStrings.Add(const Value: Strin','g; const CPUs'+
  ': TCPUs; const OSes: TOSes; ADestPath: String): TConditionalDestString'+
  ';'#013#010+
  'var'#013#010+
  '  ACondString: TConditionalDestString;'#013#010+
  'begin'#013#010+
  '  ACondString := inherited Add(Value,CPUs,OSes) as TConditionalDestStr'+
  'ing;'#013#010+
  '  ACondString.DestPath:=AD','estPath;'#013#010+
  '  Result:=ACondString;'#013#010+
  'end;'#013#010+
  #013#010+
  '{ TPackageDictionary }'#013#010+
  #013#010+
  'function TPackageDictionary.GetValue(const AName, Args: String): Strin'+
  'g;'#013#010+
  'Var'#013#010+
  '  O : TObject;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  I:=Flist.IndexOf(AName);'#013#010+
  '  If (I=-1) then'#013#010+
  '    begi','n'#013#010+
  '      if assigned(MasterDictionary) then'#013#010+
  '        result := MasterDictionary.GetValue(AName,Args)'#013#010+
  '      else'#013#010+
  '        result := GlobalDictionary.GetValue(AName,Args);'#013#010+
  '      Exit;'#013#010+
  '    end;'#013#010+
  '  O:=Flist.Objects[I];'#013#010+
  '  If O is TValueItem ','then'#013#010+
  '    Result:=TValueItem(O).FValue'#013#010+
  '  else'#013#010+
  '    Result:=TFunctionItem(O).FFunc(AName,Args);'#013#010+
  'end;'#013#010+
  #013#010+
  '{$ifndef NO_THREADING}'#013#010+
  #013#010+
  '{ TCompileWorkerThread }'#013#010+
  #013#010+
  'constructor TCompileWorkerThread.Create(ABuildEngine: TBuildEngine; No'+
  'tifyMainThr','eadEvent: PRTLEvent);'#013#010+
  'begin'#013#010+
  '  inherited Create(true);'#013#010+
  '  FNotifyStartTask := RTLEventCreate;'#013#010+
  '  FBuildEngine := ABuildEngine;'#013#010+
  '  FNotifyMainThreadEvent:=NotifyMainThreadEvent;'#013#010+
  '  Start;'#013#010+
  'end;'#013#010+
  #013#010+
  'destructor TCompileWorkerThread.Destroy;'#013#010+
  'b','egin'#013#010+
  '  RTLeventdestroy(FNotifyStartTask);'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCompileWorkerThread.execute;'#013#010+
  '  procedure RaiseMainEvent;'#013#010+
  '  begin'#013#010+
  '    { Make sure all of our results are committed before we set (F)Done'+
  ' to true.'#013#010+
  '      ','While RTLeventSetEvent implies a barrier, once the main thread'+
  ' is notified'#013#010+
  '      it will walk over all threads and look for those that have Done='+
  'true -> it'#013#010+
  '      can look at a thread between that thread setting FDone to true a'+
  'nd it'#013#010+
  '     ',' calling RTLEventSetEvent }'#013#010+
  '    WriteBarrier;'#013#010+
  '    FDone:=true;'#013#010+
  '    RTLeventSetEvent(FNotifyMainThreadEvent);'#013#010+
  '  end;'#013#010+
  'begin'#013#010+
  '  if not Terminated then'#013#010+
  '    RaiseMainEvent;'#013#010+
  '  while not Terminated do'#013#010+
  '    begin'#013#010+
  '    RTLeventWaitFor(FNotify','StartTask,500);'#013#010+
  '    if not FDone then'#013#010+
  '      begin'#013#010+
  '      { synchronise with ReadWriteBarrier in mainthread for same reaso'+
  'n as above }'#013#010+
  '      ReadWriteBarrier;'#013#010+
  '      FBuildEngine.log(vlInfo,FWorkerPrefix+'#039'Compiling: '#039'+APac'+
  'kage.Name);'#013#010+
  '   ','   FCompilationOK:=false;'#013#010+
  '      try'#013#010+
  '        FBuildEngine.Compile(APackage);'#013#010+
  '        FCompilationOK:=true;'#013#010+
  '        FBuildEngine.log(vlInfo,FWorkerPrefix+'#039'Done compiling: '#039+
  '+APackage.Name);'#013#010+
  '        RaiseMainEvent;'#013#010+
  '      except'#013#010+
  '        o','n E: Exception do'#013#010+
  '          begin'#013#010+
  '            FErrorMessage := FWorkerPrefix+'#039'Failed compiling: '#039+
  '+APackage.Name+'#039': '#039'+E.Message;'#013#010+
  '            FBuildEngine.log(vlInfo,FErrorMessage);'#013#010+
  '            RaiseMainEvent;'#013#010+
  '          end;'#013#010+
  '      end;'#013,#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{$endif NO_THREADING}'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                           TUnsortedDuplicatesStringList'#013#010+
  '***********************************************','*********************'+
  '********}'#013#010+
  #013#010+
  'function TUnsortedDuplicatesStringList.Add(const S: string): Integer;'#013+
  #010+
  #013#010+
  'begin'#013#010+
  '  result := IndexOf(S);'#013#010+
  '  If result > -1 then'#013#010+
  '    Case DUplicates of'#013#010+
  '      DupAccept,'#013#010+
  '      DupIgnore : Exit;'#013#010+
  '      DupEr','ror : Error(SDuplicateString,0)'#013#010+
  '    end;'#013#010+
  '  inherited Add(S);'#013#010+
  'end;'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                           TUnsortedCompilerOptionsStringList'#013#010+
  '**************************','******************************************'+
  '********}'#013#010+
  #013#010+
  'constructor  TUnsortedCompilerOptionsStringList.Create;'#013#010+
  'begin'#013#010+
  '  Inherited Create;'#013#010+
  '  Duplicates:=DupAccept;'#013#010+
  'end;'#013#010+
  #013#010+
  '{*****************************************************************','**'+
  '*********'#013#010+
  '                                TNamedItem'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'procedure TNamedItem.SetName(const AValue: String);'#013#010+
  #013#010+
  'begin'#013#010+
  '  if FName=AValue then exit;'#013#010+
  '  With TNa','medCollection(Collection) do'#013#010+
  '    If UniqueNames then'#013#010+
  '      If (IndexOfName(AVAlue)<>-1) then'#013#010+
  '        Raise ECollectionError.CreateFmt(SErrNameExists,[AValue]);'#013+
  #010+
  '  FName:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{***********************************************','********************'+
  '*********'#013#010+
  '                                TNamedCollection'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TNamedCollection.GetItem(Index: Integer): TNamedItem;'#013#010+
  'begin'#013#010+
  '  resul','t := TNamedItem(inherited getItem(index));'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TNamedCollection.SetItem(Index: Integer; AValue: TNamedItem)'+
  ';'#013#010+
  'begin'#013#010+
  '  inherited SetItem(Index, AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TNamedCollection.IndexOfName(const AName: String): Int','eger;'+
  #013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=Count-1;'#013#010+
  '  While (Result>=0) and (CompareText(TNamedItem(Items[Result]).FName,A'+
  'Name)<>0) do'#013#010+
  '    Dec(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TNamedCollection.ItemByName(const AName: String): TNamedItem;'+
  #013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013,#010+
  #013#010+
  'begin'#013#010+
  '  I:=IndexOfName(AName);'#013#010+
  '  If (I=-1) Then'#013#010+
  '    Raise ECollectionError.CreateFmt(SErrNoSuchName,[AName]);'#013#010+
  '  Result:=TNamedItem(Items[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  ' ','                            TNamedItemList'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TNamedItemList.GetNamedItem(Index : Integer): TNamedItem;'#013+
  #010+
  'begin'#013#010+
  '  Result:=TNamedItem(Items[Index]);'#013#010+
  'end',';'#013#010+
  #013#010+
  #013#010+
  'procedure TNamedItemList.SetNamedItem(Index : Integer; const AValue: T'+
  'NamedItem);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TNamedItemList.IndexOfName(const AName: String): Integer;'#013+
  #010+
  'begin'#013#010+
  '  Result:=Count-1;'#013#010+
  '  While (Resu','lt>=0) and (CompareText(GetNamedItem(Result).Name,AName'+
  ')<>0) do'#013#010+
  '    Dec(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TNamedItemList.ItemByName(const ANAme: String): TNamedItem;'#013+
  #010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  I:=IndexOfName(AName);'#013#010+
  '  If (I=-1) Then'#013#010+
  '    R','aise ECollectionError.CreateFmt(SErrNoSuchName,[AName]);'#013#010+
  '  Result:=TNamedItem(Items[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                TTargets'#013#010+
  '******************','**************************************************'+
  '********}'#013#010+
  #013#010+
  'function TTargets.GetTargetItem(Index : Integer): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=TTarget(Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.GetTarget(const AName : String): TTarget;'#013#010+
  'begin',#013#010+
  '  Result:=TTarget(ItemByName(AName));'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TTargets.SetTargetItem(Index : Integer; const AValue: TTarge'+
  't);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTargets.AddUnit(const AUnitName: String): TTarget;'#013#010+
  'begin'#013#010+
  '  Res','ult:=AddUnit(AUnitName,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddUnit(const AUnitName: String; const OSes: TOSes):'+
  ' TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddUnit(AUnitName,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TTargets','.AddUnit(Const AUnitName : String;const CPUs:TCPUs)'+
  ' : TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddUnit(AUnitName,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddUnit(const AUnitName: String; const CPUs: TCPUs;'#013+
  #010+
  '  const OSes: T','OSes): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=AUnitName;'#013#010+
  '  Result.TargetType:=TTUnit;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSes:=OSes;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddImplicitUnit(const AUnitName: String; InstallUnit'+
  ': boolea','n'#013#010+
  '  ): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddImplicitUnit(AUnitName,AllCPUs,AllOSes,InstallUnit);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddImplicitUnit(const AUnitName: String; const OSes:'+
  ' TOSes;'#013#010+
  '  InstallUnit: boolean): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddImpl','icitUnit(AUnitName,AllCPUs,OSes,InstallUnit);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddImplicitUnit(const AUnitName: String; const CPUs:'+
  ' TCPUs;'#013#010+
  '  InstallUnit: boolean): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddImplicitUnit(AUnitName,CPUs,AllOSes,InstallUnit);',#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddImplicitUnit(const AUnitName: String; const CPUs:'+
  ' TCPUs;'#013#010+
  '  const OSes: TOSes; InstallUnit: boolean): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=AUnitName;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSe','s:=OSes;'#013#010+
  '  if InstallUnit then'#013#010+
  '    Result.TargetType:=TTImplicitUnit'#013#010+
  '  else'#013#010+
  '    Result.TargetType:=TTCleanOnlyUnit;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddProgram(const AProgramName: String): TTarget;'#013+
  #010+
  'begin'#013#010+
  '  Result:=AddProgram(AProgramName,','AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddProgram(const AProgramName: String; const OSes: T'+
  'OSes'#013#010+
  '  ): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddProgram(AProgramName,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TTargets.AddPro','gram(Const AProgramName : String;const CPUs:'+
  'TCPUs) : TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddProgram(AProgramName,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddProgram(const AProgramName: String; const CPUs: T'+
  'CPUs;'#013#010+
  '  co','nst OSes: TOSes): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=AProgramName;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSes:=OSes;'#013#010+
  '  Result.TargetType:=ttProgram;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddLibrary(const ALibraryName: String): TTa','rget;'#013+
  #010+
  'begin'#013#010+
  '  Result:=AddLibrary(ALibraryName,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddLibrary(const ALibraryName: String; const OSes: T'+
  'OSes'#013#010+
  '  ): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddLibrary(ALibraryName,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifd','ef cpu_only_overloads}'#013#010+
  'Function TTargets.AddLibrary(Const ALibraryName : String;const CPUs:TC'+
  'PUs) : TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddLibrary(ALibraryName,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddLibrary(cons','t ALibraryName: String; const CPUs:'+
  ' TCPUs;'#013#010+
  '  const OSes: TOSes): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=ALibraryName;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSes:=OSes;'#013#010+
  '  Result.TargetType:=ttSharedLibrary;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'functio','n TTargets.AddExampleUnit(const AUnitName: String): TTarget;'#013+
  #010+
  'begin'#013#010+
  '  Result:=AddExampleUnit(AUnitName,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddExampleUnit(const AUnitName: String; const OSes: '+
  'TOSes'#013#010+
  '  ): TTarget;'#013#010+
  'begin'#013#010+
  '  Result',':=AddExampleUnit(AUnitName,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TTargets.AddExampleUnit(Const AUnitName : String;const CPUs:T'+
  'CPUs) : TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddExampleUnit(AUnitName,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endi','f cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddExampleUnit(const AUnitName: String; const CPUs: '+
  'TCPUs;'#013#010+
  '  const OSes: TOSes): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=AUnitName;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSes:=OSes;',#013#010+
  '  Result.TargetType:=ttExampleUnit;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddExampleProgram(const AProgramName: String): TTarg'+
  'et;'#013#010+
  'begin'#013#010+
  '  Result:=AddExampleProgram(AProgramName,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddExampleProgram(con','st AProgramName: String;'#013#010+
  '  const OSes: TOSes): TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddExampleProgram(AProgramName,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TTargets.AddExampleProgram(Const AProgramName : String;const '+
  'CPUs:TCPU','s) : TTarget;'#013#010+
  'begin'#013#010+
  '  Result:=AddExampleProgram(AProgramName,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TTargets.AddExampleProgram(const AProgramName: String;'#013#010+
  '  const CPUs: TCPUs; const OSes: TOSes): TTarget;'#013#010+
  'begin'#013,#010+
  '  Result:=Add as TTarget;'#013#010+
  '  Result.Name:=AProgramName;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  '  Result.OSes:=OSes;'#013#010+
  '  Result.TargetType:=ttExampleProgram;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTargets.GetEnumerator: TTargetEnumerator;'#013#010+
  'begin'#013#010+
  '  Result:= TTargetEnumerator.C','reate(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                TSources'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TSour','ces.GetSourceItem(Index : Integer): TSource;'#013#010+
  'begin'#013#010+
  '  Result:=TSource(Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TSources.SetSourceItem(Index : Integer; const AValue: TSourc'+
  'e);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TSources.AddDoc (','const AFiles : String) : TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TSource;'#013#010+
  '  Result.Name:=AFiles;'#013#010+
  '  Result.FSourceType:=stDoc;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TSources.AddDoc(const AFiles: String; AInstallSourcePath: Str'+
  'ing): TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add ','as TSource;'#013#010+
  '  Result.Name:=AFiles;'#013#010+
  '  Result.FInstallSourcePath:=AInstallSourcePath;'#013#010+
  '  Result.FSourceType:=stDoc;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TSources.AddSrc(const AFiles : String) : TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TSource;'#013#010+
  '  Result.Name:=AFil','es;'#013#010+
  '  Result.FSourceType:=stSrc;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TSources.AddExample(const AFiles : String) : TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TSource;'#013#010+
  '  Result.Name:=AFiles;'#013#010+
  '  Result.FSourceType:=stExample;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TSources.AddExample(co','nst AFiles: String; AInstallSourcePat'+
  'h: String): TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TSource;'#013#010+
  '  Result.Name:=AFiles;'#013#010+
  '  Result.FInstallSourcePath:=AInstallSourcePath;'#013#010+
  '  Result.FSourceType:=stExample;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TSources.AddTest(con','st AFiles : String) : TSource;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TSource;'#013#010+
  '  Result.Name:=AFiles;'#013#010+
  '  Result.FSourceType:=stTest;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TSources.GetEnumerator: TSourceEnumerator;'#013#010+
  'begin'#013#010+
  '  Result:=TSourceEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010,
  'procedure TSources.AddDocFiles(const AFileMask, ASearchPathPrefix: str'+
  'ing; Recursive: boolean; AInstallSourcePath: String);'#013#010+
  'var'#013#010+
  '  List : TStrings;'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  List := TStringList.Create;'#013#010+
  '  SearchFiles(AFileMask, ASearchPathP','refix, Recursive, List);'#013#010+
  '  for i:= 0 to Pred(List.Count) do'#013#010+
  '    AddDoc(List[i], AInstallSourcePath);'#013#010+
  '  List.Free;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TSources.AddSrcFiles(const AFileMask, ASearchPathPrefix: str'+
  'ing; Recursive: boolean);'#013#010+
  'var'#013#010+
  '  List : T','Strings;'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  List := TStringList.Create;'#013#010+
  '  SearchFiles(AFileMask, ASearchPathPrefix, Recursive, List);'#013#010+
  '  for i:= 0 to Pred(List.Count) do'#013#010+
  '    AddSrc(List[i]);'#013#010+
  '  List.Free;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TSources.AddExampleFil','es(const AFileMask, ASearchPathPrefi'+
  'x: string; Recursive: boolean; AInstallSourcePath: String);'#013#010+
  'var'#013#010+
  '  List : TStrings;'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  List := TStringList.Create;'#013#010+
  '  SearchFiles(AFileMask, ASearchPathPrefix, Recursive, List);'#013#010+
  '  ','for i:= 0 to Pred(List.Count) do'#013#010+
  '    AddExample(List[i], AInstallSourcePath);'#013#010+
  '  List.Free;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TSources.AddTestFiles(const AFileMask, ASearchPathPrefix: st'+
  'ring; Recursive: boolean);'#013#010+
  'var'#013#010+
  '  List : TStrings;'#013#010+
  '  i: integer;',#013#010+
  'begin'#013#010+
  '  List := TStringList.Create;'#013#010+
  '  SearchFiles(AFileMask, ASearchPathPrefix, Recursive, List);'#013#010+
  '  for i:= 0 to Pred(List.Count) do'#013#010+
  '    AddTest(List[i]);'#013#010+
  '  List.Free;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*****************************************************','**************'+
  '*********'#013#010+
  '                             TPackage'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'constructor TPackage.Create(ACollection: TCollection);'#013#010+
  'begin'#013#010+
  '  inherited Create(ACollection);',#013#010+
  '  FVersion:=TFPVersion.Create;'#013#010+
  '  FTargets:=TTargets.Create(TTarget);'#013#010+
  '  FSources:=TSources.Create(TSource);'#013#010+
  '  FDependencies:=TDependencies.Create(TDependency);'#013#010+
  '  FInstallFiles:=TConditionalDestStrings.Create(TConditionalDestString'+
  ');'#013#010+
  ' ',' FCleanFiles:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FUnitPath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FObjectPath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FIncludePath:=TConditionalStrings.Create(TConditi','onalString);'#013#010+
  '  FSourcePath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FExamplePath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FTestPath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FCommands:=TCommands.Create(TComm','and);'#013#010+
  '  FUnitsOutputDir:='#039'units'#039'+PathDelim+'#039'$(target)'#039'+PathD'+
  'elim;'#013#010+
  '  FPackageVariants:=TFPList.Create;'#013#010+
  '  FCPUs:=AllCPUs;'#013#010+
  '  FOSes:=AllOSes;'#013#010+
  '  FInstalledChecksum:=$ffffffff;'#013#010+
  '  FFlags := TStringList.Create;'#013#010+
  '  // Implicit dependency on RT','L'#013#010+
  '  FDependencies.Add('#039'rtl'#039');'#013#010+
  '  FSupportBuildModes:=[bmBuildUnit, bmOneByOne];'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  InitCriticalSection(FResolveDirsCS);'#013#010+
  '{$endif}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TPackage.destroy;'#013#010+
  #013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  DoneCriti','calSection(FResolveDirsCS);'#013#010+
  '{$endif}'#013#010+
  '  FreeAndNil(FDictionary);'#013#010+
  '  FreeAndNil(FDependencies);'#013#010+
  '  FreeAndNil(FInstallFiles);'#013#010+
  '  FreeAndNil(FCleanFiles);'#013#010+
  '  FreeAndNil(FIncludePath);'#013#010+
  '  FreeAndNil(FSourcePath);'#013#010+
  '  FreeAndNil(FExamplePath);'#013,#010+
  '  FreeAndNil(FTestPath);'#013#010+
  '  FreeAndNil(FCommands);'#013#010+
  '  FreeAndNil(FObjectPath);'#013#010+
  '  FreeAndNil(FUnitPath);'#013#010+
  '  FreeAndNil(FSources);'#013#010+
  '  FreeAndNil(FTargets);'#013#010+
  '  FreeAndNil(FVersion);'#013#010+
  '  FreeAndNil(FOptions);'#013#010+
  '  FreeAndNil(FTransmitOptions);'#013#010,
  '  FreeAndNil(FFlags);'#013#010+
  '  FreeAndNil(FPackageVariants);'#013#010+
  '  FreeAndNil(FBUTargets);'#013#010+
  '  inherited destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.HaveOptions: Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=(FOptions<>Nil);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetUnitsOutputDir(ACPU: T','CPU; AOS: TOS; const aSub'+
  'Target: String): String;'#013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result:=GetUnitsOutputDir(CT);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackage.SetName(const AValue: Str','ing);'#013#010+
  'begin'#013#010+
  '  inherited SetName(AValue);'#013#010+
  '  // RTL should not have any dependencies'#013#010+
  '  if AValue='#039'rtl'#039' then'#013#010+
  '    FDependencies.Clear;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackage.GetUnitsOutputDir(const aTarget: TCompileTarget): St'+
  'ring;'#013#010+
  'begin'#013#010+
  '  result:','=FixPath(Dictionary.Substitute(FUnitsOutputDir,'#013#010+
  '     ['#039'CPU'#039',CPUToString(aTarget.CPU),'#013#010+
  '      '#039'OS'#039', OSToString(aTarget.OS),'#013#010+
  '      '#039'SUBTARGET'#039',aTarget.SubTarget,'#013#010+
  '      '#039'target'#039',MakeTargetString(aTarget)]),'#013#010+
  '      False);'#013#010+
  'end;'#013#010+
  #013#010+
  'function ','TPackage.GetUnitConfigOutputFilename(ACPU: TCPU; AOS: TOS; '+
  'const aSubTarget: String): String;'#013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result:=GetUnitConfigOutputFilename(CT);'#013#010+
  'en','d;'#013#010+
  #013#010+
  'function TPackage.GetUnitConfigOutputFilename(const aTarget: TCompileT'+
  'arget'#013#010+
  '  ): String;'#013#010+
  'begin'#013#010+
  '  result:=FixPath(Dictionary.Substitute(Name+'#039'-$(target)'#039'+Fpmk'+
  'Ext,['#013#010+
  '    '#039'CPU'#039',CPUToString(aTarget.CPU),'#013#010+
  '    '#039'OS'#039',OSToString(aTarget.OS','),'#013#010+
  '    '#039'SUBTARGET'#039',aTarget.SubTarget,'#013#010+
  '    '#039'target'#039',MakeTargetString(atarget)]), False);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.InheritPackageVariantsFromDependency(ADependencyPac'+
  'kage: TPackage);'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  '  APackageVariants: TPackageVaria','nts;'#013#010+
  'begin'#013#010+
  '  for i := 0 to ADependencyPackage.FPackageVariants.Count-1 do'#013#010+
  '    begin'#013#010+
  '      APackageVariants := TPackageVariants(ADependencyPackage.FPackage'+
  'Variants[i]);'#013#010+
  '      if APackageVariants.IsInheritable then'#013#010+
  '        begin'#013#010+
  '      ','  if not assigned(GetPackageVariantsByName(APackageVariants.Na'+
  'me)) then'#013#010+
  '          begin'#013#010+
  '          FPackageVariants.Add(APackageVariants);'#013#010+
  '          end;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetPackageVariantsByName(AName: s','tring): TPackageV'+
  'ariants;'#013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  'begin'#013#010+
  '  result := nil;'#013#010+
  '  for i := 0 to FPackageVariants.Count-1 do'#013#010+
  '    if SameText(TPackageVariants(FPackageVariants.Items[i]).Name, ANam'+
  'e) then'#013#010+
  '      begin'#013#010+
  '      result := TPackageVariant','s(FPackageVariants.Items[i]);'#013#010+
  '      break;'#013#010+
  '      end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetUnitsOutputDir(AValue: string);'#013#010+
  'begin'#013#010+
  '  if AValue<>'#039#039' then'#013#010+
  '    FUnitsOutputDir:=IncludeTrailingPathDelimiter(AValue)'#013#010+
  '  else'#013#010+
  '    FUnitsOutputDir:='#039#039';',#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetPackageUnitInstallDir(ACPU: TCPU; AOS: TOS; const'+
  ' aSubTarget : String): String;'#013#010+
  'begin'#013#010+
  '  result:=FixPath(Dictionary.Substitute(FPackageUnitInstallDir,['#039'C'+
  'PU'#039',CPUToString(ACPU),'#039'OS'#039',OSToString(AOS),'#039'SUBTARGET'#039+
  ',','aSubTarget,'#039'target'#039',MakeTargetString(ACPU,AOS,aSubTarget)])'+
  ', False);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetPackageUnitInstallDir(AValue: string);'#013#010+
  'begin'#013#010+
  '  if AValue<>'#039#039' then'#013#010+
  '    FPackageUnitInstallDir:=IncludeTrailingPathDelimiter(AValue)'#013#010+
  '  els','e'#013#010+
  '    FPackageUnitInstallDir:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{function TPackage.GetBinOutputDir(ACPU: TCPU; AOS: TOS; const aSubTar'+
  'get : String): String;'#013#010+
  #013#010+
  'begin'#013#010+
  #013#010+
  'end;}'#013#010+
  #013#010+
  'function TPackage.GetBinOutputDir(const aTarget : TCompileTarget): Str'+
  'ing;'#013#010+
  'begi','n'#013#010+
  '  Result:='#039'bin'#039'+PathDelim+MakeTargetString(aTarget);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetBinOutputDir(ACPU: TCPU; AOS: TOS; const aSubTarg'+
  'et: String'#013#010+
  '  ): String;'#013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Su','btarget:=aSubTarget;'#013#010+
  '  Result:=GetBinOutputDir(CT);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackage.GetCleanFiles(List: TStrings; ACPU:TCPU; AOS : TOS;'+
  ' const aSubTarget : String);'#013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT','.Subtarget:=aSubTarget;'#013#010+
  '  GetCleanFiles(List,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.GetCleanFiles(List: TStrings; const aTarget: TCompi'+
  'leTarget);'#013#010+
  'Var'#013#010+
  '  OB,OU : String;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  OB:=IncludeTrailingPathDelimiter(GetBinOutputDir(','aTarget));'#013#010+
  '  if Not DirectoryExists(OB) then'#013#010+
  '    OB:='#039#039';'#013#010+
  '  OU:=IncludeTrailingPathDelimiter(GetUnitsOutputDir(aTarget));'#013#010+
  '  if not DirectoryExists(OU) then'#013#010+
  '    OU:='#039#039';'#013#010+
  '  List.Add(GetUnitConfigOutputFilename(aTarget));'#013#010+
  '  List.Add(Manif','estFile);'#013#010+
  '  AddConditionalStrings(Self, List,CleanFiles,aTarget);'#013#010+
  '  For I:=0 to FTargets.Count-1 do'#013#010+
  '    FTargets.TargetItems[I].GetCleanFiles(List, OU, OB, aTarget);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackage.GetInstallFiles(List: TStrings;Types : TT','argetTyp'+
  'es;const aTarget : TCompileTarget);'#013#010+
  'Var'#013#010+
  '  OB,OU : String;'#013#010+
  '  I : Integer;'#013#010+
  '  T : TTarget;'#013#010+
  'begin'#013#010+
  '  if Types=[] then'#013#010+
  '    AddConditionalStrings(Self, List,InstallFiles,aTarget)'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      OB:=IncludeTrailingPathDeli','miter(GetBinOutputDir(Defaults.Comp'+
  'ileTarget));'#013#010+
  '      OU:=IncludeTrailingPathDelimiter(GetUnitsOutputDir(Defaults.Comp'+
  'ileTarget));'#013#010+
  '      For I:=0 to FTargets.Count-1 do'#013#010+
  '        begin'#013#010+
  '          T:=FTargets.TargetItems[I];'#013#010+
  '          if (','T.TargetType in Types) and Installer.BuildEngine.Targe'+
  'tInstallOK(T, aTarget) then'#013#010+
  '            T.GetInstallFiles(List, OU, OB, aTarget);'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackage.GetInstallSourceFiles(List: TStrings; SourceTypes',' '+
  ': TSourceTypes; TargetTypes : TTargetTypes);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  S : TSource;'#013#010+
  '  T : TTarget;'#013#010+
  'begin'#013#010+
  '  For I:=0 to FSources.Count-1 do'#013#010+
  '    begin'#013#010+
  '      S:=FSources.SourceItems[I];'#013#010+
  '      if (S.SourceType in SourceTypes) then'#013#010+
  '       ',' S.GetInstallFiles(List);'#013#010+
  '    end;'#013#010+
  '  For I:=0 to FTargets.Count-1 do'#013#010+
  '    begin'#013#010+
  '      T:=FTargets.TargetItems[I];'#013#010+
  '      if (T.TargetType in TargetTypes) then'#013#010+
  '        T.GetArchiveFiles(List,Defaults.CPU,Defaults.OS);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010,
  'procedure TPackage.GetArchiveFiles(List: TStrings; aTarget: TCompileTa'+
  'rget);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  // Targets only'#013#010+
  '  For I:=0 to FTargets.Count-1 do'#013#010+
  '    FTargets.TargetItems[I].GetArchiveFiles(List,aTarget.CPU,aTarget.O'+
  'S);'#013#010+
  'end;'#013,#010+
  #013#010+
  #013#010+
  'procedure TPackage.GetArchiveFiles(List: TStrings; ACPU:TCPU; AOS : TO'+
  'S);'#013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:='#039#039';'#013#010+
  '  GetArchiveFiles(List,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.GetArchiveS','ourceFiles(List: TStrings);'#013#010+
  'var'#013#010+
  '  i : integer;'#013#010+
  'begin'#013#010+
  '  for i := 0 to Sources.Count-1 do'#013#010+
  '    List.Add(Sources[i].Name);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetDescription: string;'#013#010+
  'Var'#013#010+
  '  FN : String;'#013#010+
  '  L : TStringList;'#013#010+
  'begin'#013#010+
  '  If (FDescripti','on<>'#039#039') then'#013#010+
  '    Result:=FDescription'#013#010+
  '  else'#013#010+
  '    If (FDescriptionFile<>'#039#039') then'#013#010+
  '      begin'#013#010+
  '        // Always relative to binary name.'#013#010+
  '        FN:=ExtractFilePath(ParamStr(0));'#013#010+
  '        FN:=FN+FDescriptionFile;'#013#010+
  '        If FileExists(','FN) then'#013#010+
  '          begin'#013#010+
  '            L:=TStringList.Create;'#013#010+
  '            Try'#013#010+
  '              L.LoadFromFile(FN);'#013#010+
  '              Result:=L.Text;'#013#010+
  '            Finally'#013#010+
  '              L.Free;'#013#010+
  '            end;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  'end;',#013#010+
  #013#010+
  'function TPackage.GetDictionary: TDictionary;'#013#010+
  'begin'#013#010+
  '  if not assigned(FDictionary) then'#013#010+
  '    FDictionary:=PackageDictionaryClass.Create(Nil);'#013#010+
  '  result := FDictionary;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackage.GetVersion: string;'#013#010+
  'begin'#013#010+
  '  result:','=FVersion.AsString;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetOptions(const AValue: TStrings);'#013#010+
  'begin'#013#010+
  '  If (AValue=Nil) or (AValue.Count=0) then'#013#010+
  '    FreeAndNil(Foptions)'#013#010+
  '  else'#013#010+
  '    Options.Assign(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetTransmitOpt','ions(AValue: TStrings);'#013#010+
  'begin'#013#010+
  '  If (AValue=Nil) or (AValue.Count=0) then'#013#010+
  '    FreeAndNil(FTransmitOptions)'#013#010+
  '  else'#013#010+
  '    TransmitOptions.Assign(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetVersion(const V: string);'#013#010+
  'begin'#013#010+
  '  FVersion.AsString:=','V;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackage.GetFileName: string;'#013#010+
  'begin'#013#010+
  '  If (FFileName<>'#039#039') then'#013#010+
  '    Result:=FFileName'#013#010+
  '  else'#013#010+
  '    if not FVersion.Empty and not'#013#010+
  '      ((Defaults.OS in AllLimit83fsOses) or (Defaults.BuildOS in AllLi'+
  'mit83fsOses)) th','en'#013#010+
  '      Result := Name + '#039'-'#039' + FVersion.AsString'#013#010+
  '    else'#013#010+
  '      Result := ShortName;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackage.GetShortName: string;'#013#010+
  'begin'#013#010+
  '  if FShortName<>'#039#039' then'#013#010+
  '    result := FShortName'#013#010+
  '  else'#013#010+
  '    result := Name;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'f','unction TPackage.GetOptions: TStrings;'#013#010+
  'begin'#013#010+
  '  If (FOptions=Nil) then'#013#010+
  '    FOptions:=TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  Result:=FOptions;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.GetTransmitOptions: TStrings;'#013#010+
  'begin'#013#010+
  '  If (FTransmitOptions=N','il) then'#013#010+
  '    FTransmitOptions:=TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  Result:=FTransmitOptions;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.GetManifest(Manifest: TStrings);'#013#010+
  #013#010+
  '  procedure AddOSes(const AIndent:string;AOSes:TOSes);'#013#010+
  '  var'#013#010+
  '    IOS :',' TOS;'#013#010+
  '  begin'#013#010+
  '    if (AOSes=AllOSes) then'#013#010+
  '      exit;'#013#010+
  '    Manifest.Add(AIndent+'#039'<oses>'#039');'#013#010+
  '    for IOS:=low(TOSes) to high(TOSes) do'#013#010+
  '      if IOS in AOSes then'#013#010+
  '        Manifest.Add(Format(AIndent+'#039' <os name="%s"/>'#039',[OSToSt'+
  'ring(IOS)]))',';'#013#010+
  '    Manifest.Add(AIndent+'#039'</oses>'#039');'#013#010+
  '  end;'#013#010+
  #013#010+
  '  procedure AddCPUs(const AIndent:string;ACPUs:TCPUs);'#013#010+
  '  var'#013#010+
  '    ICPU : TCPU;'#013#010+
  '  begin'#013#010+
  '    if (ACPUs=AllCPUs) then'#013#010+
  '      exit;'#013#010+
  '    Manifest.Add(AIndent+'#039'<cpus>'#039');'#013#010+
  '    for ICPU:=low(TC','PUs) to high(TCPUs) do'#013#010+
  '      if ICPU in ACPUs then'#013#010+
  '        Manifest.Add(Format(AIndent+'#039' <cpu name="%s"/>'#039',[CPUTo'+
  'String(ICPU)]));'#013#010+
  '    Manifest.Add(AIndent+'#039'</cpus>'#039');'#013#010+
  '  end;'#013#010+
  #013#010+
  '  procedure AddSubTargets(const AIndent:string;aSubTargets:','TRTLStrin'+
  'gDynArray);'#013#010+
  '  var'#013#010+
  '    S : String;'#013#010+
  '  begin'#013#010+
  '    if (Length(aSubTargets)=0) then'#013#010+
  '      exit;'#013#010+
  '    Manifest.Add(AIndent+'#039'<subtargets>'#039');'#013#010+
  '    for S in aSubTargets do'#013#010+
  '      Manifest.Add(Format(AIndent+'#039' <subtarget name="%s"/>'#039',[S'+
  ']','));'#013#010+
  '    Manifest.Add(AIndent+'#039'</subtargets>'#039');'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  function GetXMLVersionString(sMajor, sMinor, sMicro, sBuild: integer'+
  '): string;'#013#010+
  '  begin'#013#010+
  '    Result := '#039'<version'#039';'#013#010+
  '    if sMajor <> -1 then'#013#010+
  '      Result := Result + '#039' major="'#039,' + IntToStr(sMajor) + '#039+
  '"'#039';'#013#010+
  '    if sMinor <> -1 then'#013#010+
  '      Result := Result + '#039' minor="'#039' + IntToStr(sMinor) + '#039'"'+
  #039';'#013#010+
  '    if sMicro <> -1 then'#013#010+
  '      Result := Result + '#039' micro="'#039' + IntToStr(sMicro) + '#039'"'+
  #039';'#013#010+
  '    if sBuild <> -1 then'#013#010+
  '      Re','sult := Result + '#039' build="'#039' + IntToStr(sBuild) + '#039+
  '"'#039';'#013#010+
  #013#010+
  '    Result := Result + '#039'/>'#039';'#013#010+
  '  end;'#013#010+
  #013#010+
  'Var'#013#010+
  '  S : String;'#013#010+
  '  i : Integer;'#013#010+
  '  D : TDependency;'#013#010+
  'begin'#013#010+
  '  With Manifest do'#013#010+
  '    begin'#013#010+
  '    Add(Format('#039'<package name="%s">'#039',[QuoteXml(Na','me)]));'#013+
  #010+
  #013#010+
  '    Add('#039' '#039' + GetXMLVersionString(FVersion.Major,FVersion.Mino'+
  'r,FVersion.Micro,FVersion.Build));'#013#010+
  '    AddOSes('#039' '#039',OSes);'#013#010+
  '    AddCPUs('#039' '#039',CPUs);'#013#010+
  '    AddSubTargets('#039' '#039',SubTargets);'#013#010+
  '    Add(Format('#039' <filename>%s</filename>'#039',[Quot','eXml(FileName'+
  ' + MakeZipSuffix(cpuNone, osNone) + ZipExt)]));'#013#010+
  '    Add(Format('#039' <author>%s</author>'#039',[QuoteXml(Author)]));'#013+
  #010+
  '    Add(Format('#039' <license>%s</license>'#039',[QuoteXml(License)]));'+
  #013#010+
  '    if HomepageURL<>'#039#039' then'#013#010+
  '      Add(Format('#039' <home','pageurl>%s</homepageurl>'#039',[QuoteXml('+
  'HomepageURL)]));'#013#010+
  '    if DownloadURL<>'#039#039' then'#013#010+
  '      Add(Format('#039' <downloadurl>%s</downloadurl>'#039',[QuoteXml(Do'+
  'wnloadURL)]));'#013#010+
  '    Add(Format('#039' <email>%s</email>'#039',[QuoteXMl(Email)]));'#013#010+
  '    S:=Description;'#013#010,
  '    If (S<>'#039#039') then'#013#010+
  '      Add(Format('#039' <description>%s</description>'#039',[QuoteXML(S)'+
  ']));'#013#010+
  '    If (Dependencies.Count>0) then'#013#010+
  '      begin'#013#010+
  '        Add('#039' <dependencies>'#039');'#013#010+
  '        for I:=0 to Dependencies.Count-1 do'#013#010+
  '          begin'#013#010+
  '       ','     D:=Dependencies[i];'#013#010+
  '            Add('#039'  <dependency>'#039');'#013#010+
  '            Add(Format('#039'   <package packagename="%s"/>'#039',[Quote'+
  'XML(D.Value)]));'#013#010+
  '            if not D.FVersion.Empty then'#013#010+
  '              Add('#039'   '#039' + GetXMLVersionString(D.FVersion','.Maj'+
  'or,D.FVersion.Minor,D.FVersion.Micro,D.FVersion.Build));'#013#010+
  '            AddOSes('#039'   '#039',D.OSes);'#013#010+
  '            AddCPUs('#039'   '#039',D.CPUs);'#013#010+
  '            Add('#039'  </dependency>'#039');'#013#010+
  '          end;'#013#010+
  '        Add('#039' </dependencies>'#039');'#013#010+
  '      end;'#013#010+
  '    Add','('#039'</package>'#039');'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.ListPackage(PkgList: TStrings);'#013#010+
  #013#010+
  '  function GetArchiveName (const APackage: TPackage; ALimit83: boolean'+
  '): string;'#013#010+
  '  begin'#013#010+
  '{ Special hack to allow both long and short source files bei','ng recog'+
  'nized }'#013#010+
  '    if ALimit83 and (Defaults.ZipPrefix = '#039'units-'#039') then'#013#010+
  '      result := '#039'u'#039#013#010+
  '    else'#013#010+
  '      result := Defaults.ZipPrefix;'#013#010+
  '    if ALimit83 then'#013#010+
  '      result := result + APackage.ShortName'#013#010+
  '    else'#013#010+
  '      result := resu','lt + APackage.Name;'#013#010+
  '    result := result + MakeZipSuffix(Defaults.CPU, Defaults.OS, '#039#039+
  ', ALimit83);'#013#010+
  '  end;'#013#010+
  #013#010+
  'Var'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '{  if OSes = AllOSes then'#013#010+
  '    Exit;}'#013#010+
  '  if  ('#013#010+
  '       ('#013#010+
  '        ((OSes = AllOSes) or (Defaults.OS in',' OSes)) and'#013#010+
  '        ((CPUs = AllCPUs) or (Defaults.CPU in CPUs))'#013#010+
  '       )'#013#010+
  '       or'#013#010+
  '       ('#013#010+
  '         (Defaults.OS = osNone) and (Defaults.CPU = cpuNone)'#013#010+
  '       )'#013#010+
  '      )'#013#010+
  '      and'#013#010+
  '       ((Defaults.SubTarget='#039#039') or SubTargetAllowe','d(Defaults.S'+
  'ubTarget))'#013#010+
  '     then'#013#010+
  '    begin'#013#010+
  '      if Defaults.OS = osNone then'#013#010+
  '        PkgList.Add (Format ('#039'# Source %d'#039', [Succ (PkgList.Cou'+
  'nt div 2)]))'#013#010+
  '      else {if OSes <> AllOSes then}'#013#010+
  '        PkgList.Add (Format ('#039'# '#039' + OSToStri','ng(Defaults.OS) '+
  '+ '#039' %d'#039', [Succ (PkgList.Count div 2)]));'#013#010+
  '      S := '#039'package='#039' + GetArchiveName (Self, false) + Archive'+
  'Extension;'#013#010+
  '      if ((ShortName <> Name) or (Defaults.ZipPrefix = '#039'units-'#039+
  ')) and'#013#010+
  '             ((Defaults.OS in AllLimi','t83fsOSes) or (Defaults.OS = os'+
  'None)) then'#013#010+
  '        S := S + '#039'['#039' + GetArchiveName (Self, true) + ArchiveEx'+
  'tension + '#039']'#039';'#013#010+
  '      S := S + '#039','#039' + Description;'#013#010+
  '      PkgList.Add(S);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.AddPackageVariant(APack','ageVariant: TPackageVarian'+
  'ts);'#013#010+
  'begin'#013#010+
  '  if not assigned(APackageVariant.FMasterPackage) then'#013#010+
  '    APackageVariant.FMasterPackage := Self;'#013#010+
  '  FPackageVariants.Add(APackageVariant);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.ApplyPackageVariantToCompilerOp','tions(ACompilerOpt'+
  'ions: tstrings);'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  '  PackageVariants: TPackageVariants;'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  for i := 0 to FPackageVariants.Count-1 do'#013#010+
  '    begin'#013#010+
  '    PackageVariants := TPackageVariants(FPackageVariants.Items[i]);'#013,
  #010+
  '    for S in PackageVariants.ActivePackageVariant.Options do'#013#010+
  '      ACompilerOptions.Add(S);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SetDefaultPackageVariant;'#013#010+
  'var'#013#010+
  '  i,j: integer;'#013#010+
  '  PackageVariants: TPackageVariants;'#013#010+
  'begin'#013#010+
  '  for i := 0 t','o FPackageVariants.Count-1 do'#013#010+
  '    begin'#013#010+
  '    PackageVariants := TPackageVariants(FPackageVariants.Items[i]);'#013+
  #010+
  '    if Installer.FPackageVariantSettings.Values[PackageVariants.Name]<'+
  '>'#039#039' then'#013#010+
  '      PackageVariants.ActivePackageVariantName:= ','Installer.FPackageV'+
  'ariantSettings.Values[PackageVariants.Name]'#013#010+
  '    else'#013#010+
  '      PackageVariants.ActivePackageVariantName:= PackageVariants.Defau'+
  'ltPackageVariantName;'#013#010+
  '    IncludePath.AddList(PackageVariants.ActivePackageVariant.IncludePa'+
  'th)',';'#013#010+
  '    SourcePath.AddList(PackageVariants.ActivePackageVariant.SourcePath'+
  ');'#013#010+
  '    Dictionary.AddVariable(PackageVariants.Name,PackageVariants.Active'+
  'PackageVariantName);'#013#010+
  '    SetUnitsOutputDir(IncludeTrailingPathDelimiter(FUnitsOutputDir)+'#039+
  '$(',#039'+PackageVariants.name+'#039')'#039');'#013#010+
  '    SetPackageUnitInstallDir(FixPath(FPackageUnitInstallDir, True)+'#039+
  '$('#039'+PackageVariants.Name+'#039')'#039');'#013#010+
  '    // Do not add targets f the package is inherited'#013#010+
  '    if PackageVariants.MasterPackage=Self then'#013#010+
  '      fo','r j := 0 to PackageVariants.ActivePackageVariant.Targets.cou'+
  'nt -1 do'#013#010+
  '        targets.add.assign(PackageVariants.ActivePackageVariant.Target'+
  's.items[j]);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackage.LoadUnitConfigFromFile(const AFileName: String)',';'#013+
  #010+
  'var'#013#010+
  '  L,L2 : TStrings;'#013#010+
  '  VOS : TOS;'#013#010+
  '  VCPU : TCPU;'#013#010+
  '  i,k : Integer;'#013#010+
  '  DepChecksum : Cardinal;'#013#010+
  '  DepName : String;'#013#010+
  '  D : TDependency;'#013#010+
  '  PackageVariantsStr: string;'#013#010+
  '  PackageVarName: string;'#013#010+
  '  pv: TPackageVariants;'#013#010+
  '  AnIsInherit','able: boolean;'#013#010+
  'begin'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '    ReadIniFile(AFileName,L);'#013#010+
  '    With L do'#013#010+
  '      begin'#013#010+
  '        Version:=Values[KeyVersion];'#013#010+
  '        InstalledChecksum:=Cardinal(StrToInt64Def(Values[KeyChecksum],'+
  '$ffffffff));'#013#010+
  '   ','     VCPU:=StringToCPU(Values[KeyCPU]);'#013#010+
  '        VOS:=StringToOS(Values[KeyOS]);'#013#010+
  '        SubTargets:=Values[KeySubTargets].Split(RTLString('#039' '#039')'+
  ', TStringSplitOptions.ExcludeEmpty);'#013#010+
  '        OSes:=[VOS];'#013#010+
  '        CPUs:=[VCPU];'#013#010+
  '        L2:=T','StringList.Create;'#013#010+
  '        L2.CommaText:=Values[KeyDepends];'#013#010+
  '        for i:=0 to L2.Count-1 do'#013#010+
  '          begin'#013#010+
  '            DepName:=L2[i];'#013#010+
  '            k:=Pos('#039'|'#039',DepName);'#013#010+
  '            if k>0 then'#013#010+
  '              begin'#013#010+
  '                ','DepChecksum:=StrToInt(Copy(DepName,k+1,Length(DepNam'+
  'e)-k));'#013#010+
  '                DepName:=Copy(DepName,1,k-1);'#013#010+
  '              end'#013#010+
  '            else'#013#010+
  '              DepChecksum:=$ffffffff;'#013#010+
  '            D:=Dependencies.Add(DepName,CPUs,OSes);'#013#010+
  '   ','         D.RequireChecksum:=DepChecksum;'#013#010+
  '          end;'#013#010+
  '        FreeAndNil(L2);'#013#010+
  '        NeedLibC:=Upcase(Values[KeyNeedLibC])='#039'Y'#039';'#013#010+
  '        IsFPMakeAddIn:=Upcase(Values[KeyAddIn])='#039'Y'#039';'#013#010+
  '        Flags.DelimitedText:=Values[KeyFlags];'#013#010+
  '   ','     if Values[KeyTransmit]<>'#039#039' then'#013#010+
  '          TransmitOptions.DelimitedText:=Values[KeyTransmit];'#013#010+
  '        i := 1;'#013#010+
  '        repeat'#013#010+
  '        PackageVariantsStr:=Values[KeyPackageVar+inttostr(i)];'#013#010+
  '        if PackageVariantsStr<>'#039#039' then'#013#010+
  '  ','        begin'#013#010+
  '            k := pos('#039':'#039',PackageVariantsStr);'#013#010+
  '            if k > 0 then'#013#010+
  '              begin'#013#010+
  '                PackageVarName:=copy(PackageVariantsStr,1,k-1);'#013#010+
  '                if PackageVarName[Length(PackageVarName)]='#039'*'#039' '+
  'the','n'#013#010+
  '                  begin'#013#010+
  '                  SetLength(PackageVarName,Length(PackageVarName)-1);'#013+
  #010+
  '                  AnIsInheritable:=true;'#013#010+
  '                  end'#013#010+
  '                else'#013#010+
  '                  AnIsInheritable:=false;'#013#010+
  '           ','     PackageVariantsStr:=copy(PackageVariantsStr,k+1,leng'+
  'th(PackageVariantsStr)-k);'#013#010+
  '                pv := Installer.AddPackageVariant(PackageVarName, AnIs'+
  'Inheritable);'#013#010+
  '                AddPackageVariant(pv);'#013#010+
  #013#010+
  '                k := pos('#039','#039,',PackageVariantsStr);'#013#010+
  '                while k>0 do'#013#010+
  '                  begin'#013#010+
  '                    PackageVarName:=copy(PackageVariantsStr,1,k-1);'#013+
  #010+
  '                    PackageVariantsStr:=copy(PackageVariantsStr,k+1,le'+
  'ngth(PackageVariantsStr',')-k);'#013#010+
  '                    pv.Add(PackageVarName);'#013#010+
  '                    k := pos('#039','#039',PackageVariantsStr);'#013#010+
  '                  end;'#013#010+
  '                pv.Add(PackageVariantsStr);'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '        inc(i);'#013#010+
  '        unt','il PackageVariantsStr='#039#039';'#013#010+
  #013#010+
  '      end;'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.SaveUnitConfigToStringList(const AStringList: TStri'+
  'ngs; ACPU: TCPU; AOS: TOS);'#013#010+
  'Var'#013#010+
  '  Subs,Deps : String;'#013#010+
  '  i,j : integer;'#013#010+
  '  D : TDepende','ncy;'#013#010+
  '  p : TPackage;'#013#010+
  '  PackageVariants : TPackageVariants;'#013#010+
  '  PackageVariantsStr: string;'#013#010+
  '  s: string;'#013#010+
  'begin'#013#010+
  '  with AStringList do'#013#010+
  '    begin'#013#010+
  '      Values[KeyName]:=Name;'#013#010+
  '      Values[KeyVersion]:=Version;'#013#010+
  '      // TODO Generate che','cksum based on PPUs'#013#010+
  '      InstalledChecksum:=DateTimeToFileDate(Now);'#013#010+
  '      Values[KeyChecksum]:=IntToStr(InstalledChecksum);'#013#010+
  '      Values[KeyCPU]:=CPUToString(ACPU);'#013#010+
  '      Values[KeyOS]:=OSToString(AOS);'#013#010+
  '      Subs:='#039#039';'#013#010+
  '      For S i','n SubTargets do'#013#010+
  '        begin'#013#010+
  '        if Subs<>'#039#039' then'#013#010+
  '          Subs:=Subs+'#039' '#039';'#013#010+
  '        Subs:=Subs+S;'#013#010+
  '        end;'#013#010+
  '      Values[KeySubTargets]:=Subs;'#013#010+
  '      //Installer;'#013#010+
  '      Values[KeySourcePath]:=IncludeTrailingPathDelimiter(Incl','udeTra'+
  'ilingPathDelimiter(Installer.BuildEngine.FStartDir)+Directory);'#013#010+
  '      Values[KeyFPMakeOptions]:=trim(Installer.FPMakeOptionsString);'#013+
  #010+
  '      Deps:='#039#039';'#013#010+
  '      for i:=0 to Dependencies.Count-1 do'#013#010+
  '        begin'#013#010+
  '          D:=Dependencie','s[i];'#013#010+
  '          if (ACPU in D.CPUs) and (AOS in D.OSes) then'#013#010+
  '            begin'#013#010+
  '              if Deps<>'#039#039' then'#013#010+
  '                Deps:=Deps+'#039','#039';'#013#010+
  '              Deps:=Deps+D.Value;'#013#010+
  '              P:=TPackage(D.Target);'#013#010+
  '              if ass','igned(P) and (P.InstalledChecksum<>$ffffffff) th'+
  'en'#013#010+
  '                Deps:=Deps+'#039'|'#039'+IntToStr(P.InstalledChecksum);'#013+
  #010+
  '            end;'#013#010+
  '        end;'#013#010+
  '      Values[KeyDepends]:=Deps;'#013#010+
  '      if Flags.Count>0 then'#013#010+
  '        Values[KeyFlags]:=Flags','.DelimitedText;'#013#010+
  '      if TransmitOptions.Count>0 then'#013#010+
  '        Values[KeyTransmit]:=TransmitOptions.DelimitedText;'#013#010+
  '      if NeedLibC then'#013#010+
  '        Values[KeyNeedLibC]:='#039'Y'#039#013#010+
  '      else'#013#010+
  '        Values[KeyNeedLibC]:='#039'N'#039';'#013#010+
  '      if IsFPMakeA','ddIn then'#013#010+
  '        Values[KeyAddIn]:='#039'Y'#039#013#010+
  '      else'#013#010+
  '        Values[KeyAddIn]:='#039'N'#039';'#013#010+
  #013#010+
  '      s := '#039#039';'#013#010+
  '      for i := 0 to FTargets.Count-1 do'#013#010+
  '        begin'#013#010+
  '          if FTargets.TargetItems[i].IsFPMakePlugin then'#013#010+
  '            begin'#013#010+
  '   ','           if s <> '#039#039' then'#013#010+
  '                s := s + '#039','#039';'#013#010+
  '              s := s + FTargets.TargetItems[i].Name;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '      if s<>'#039#039' then'#013#010+
  '        Values[KeyPluginUnits]:=s;'#013#010+
  #013#010+
  '      for i := 0 to FPackageVariants','.Count-1 do'#013#010+
  '        begin'#013#010+
  '          PackageVariants := TPackageVariants(FPackageVariants.Items[i'+
  ']);'#013#010+
  '          PackageVariantsStr:=PackageVariants.Name;'#013#010+
  '          if PackageVariants.IsInheritable then'#013#010+
  '            PackageVariantsStr:=Pac','kageVariantsStr+'#039'*'#039';'#013#010+
  '          PackageVariantsStr := PackageVariantsStr +'#039':'#039'+Packag'+
  'eVariants.DefaultPackageVariantName;'#013#010+
  '          for j := 0 to PackageVariants.Count-1 do'#013#010+
  '            if not sametext(PackageVariants.Items[j].Name, Package','Va'+
  'riants.DefaultPackageVariantName) then'#013#010+
  '              PackageVariantsStr:=PackageVariantsStr+'#039','#039'+Packa'+
  'geVariants.Items[j].Name;'#013#010+
  '          values[KeyPackageVar+inttostr(i+1)] := PackageVariantsStr;'#013+
  #010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedu','re TPackage.SaveUnitConfigToFile(const AFileName: String; ACP'+
  'U: TCPU;'#013#010+
  '  AOS: TOS);'#013#010+
  'Var'#013#010+
  '  F : TFileStream;'#013#010+
  '  L : TStringList;'#013#010+
  'begin'#013#010+
  '  F:=TFileStream.Create(AFileName,fmCreate or fmShareDenyNone);'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    S','aveUnitConfigToStringList(L,ACPU,AOS);'#013#010+
  '    L.SaveToStream(F);'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '    F.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.EnterResolveDirsCS;'#013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '   EnterCriticalSection(FResolveDirsCS);'#013#010+
  '{$endif}'#013#010,
  'end;'#013#010+
  #013#010+
  'procedure TPackage.LeaveResolveDirsCS;'#013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '   LeaveCriticalSection(FResolveDirsCS);'#013#010+
  '{$endif}'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackage.AddTargetsFromDir(const aDirectory: String; const aM'+
  'ask: String): longint;'#013#010+
  'var'#013#010+
  '  ','lMasks : Array of string;'#013#010+
  '  lMask : string;'#013#010+
  '  lDir,lFile : string;'#013#010+
  '  lInfo : TSearchRec;'#013#010+
  'begin'#013#010+
  '  if aDirectory='#039#039' then'#013#010+
  '    lDir:='#039'./'#039#013#010+
  '  else'#013#010+
  '    lDir:=IncludeTrailingPathDelimiter(aDirectory);'#013#010+
  '  if not DirectoryExists(lDir) then'#013#010+
  ' ','   Exit(-1);'#013#010+
  '  if aMask='#039#039' then'#013#010+
  '    lMasks:=['#039'*.pp'#039','#039'*.pas'#039','#039'*.lpr'#039']'#013#010+
  '  else'#013#010+
  '    lMasks:=aMask.Split(['#039';'#039']);'#013#010+
  '  Result:=0;'#013#010+
  '  for lMask in lMasks do'#013#010+
  '    begin'#013#010+
  '    if FindFirst(lDir+lMask,0,lInfo)=0 then'#013#010+
  '      try'#013#010+
  '        repeat'#013#010+
  '    ','      lFile:=ldir+lInfo.Name;'#013#010+
  '          if SameFileName(ExtractFileExt(lInfo.Name),'#039'.lpr'#039') t'+
  'hen'#013#010+
  '            Targets.AddProgram(lFile)'#013#010+
  '          else'#013#010+
  '            // Todo: add some detection for program/unit'#013#010+
  '            Targets.AddUnit(l','File);'#013#010+
  '          Installer.Log(vlInfo,Format('#039'Adding unit %s to targets o'+
  'f %s'#039',[lFile,Name]));'#013#010+
  '          Inc(Result);'#013#010+
  '        until FindNext(lInfo)<>0;'#013#010+
  '      finally'#013#010+
  '        FindClose(lInfo)'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  if Result>0 then'#013#010+
  ' ','   begin'#013#010+
  '    Installer.Log(vlInfo, Format(SSwitchingToBuildUnitCompilation, [Na'+
  'me]));'#013#010+
  '    Defaults.BuildMode:=bmBuildUnit;'#013#010+
  '    FSupportBuildModes:=[bmBuildUnit];'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.ChangePaths(Aliases : TStrings; aTarg','et : TCompil'+
  'eTarget);'#013#010+
  #013#010+
  'var'#013#010+
  '  aDir,aDest, S, aLine : string;'#013#010+
  '  aPath,aOp : Char;'#013#010+
  '  P : integer;'#013#010+
  '  CS : TConditionalString;'#013#010+
  '  CSL : TConditionalStrings;'#013#010+
  #013#010+
  'begin'#013#010+
  '  for S in Aliases do'#013#010+
  '    begin'#013#010+
  '    aLine:=Trim(S);'#013#010+
  '    P:=Pos('#039'}'#039',aL','ine);'#013#010+
  '    if Not (Copy(aLine,1,1)='#039'{'#039') and (Copy(aLine,4,1)='#039':'#039+
  ') and (P<>0) then'#013#010+
  '      Continue;'#013#010+
  '    aPath:=aLine[2];'#013#010+
  '    aOp:=aLine[3];'#013#010+
  '    aDir:= ExtractFileDir(Copy(aLine, 5, P - 5));'#013#010+
  '    P:=Pos('#039'='#039',aLine);'#013#010+
  '    if (P>0) then'#013#010+
  '    ','  aDest:=Copy(aLine,P+1);'#013#010+
  '    CSL:=Nil;'#013#010+
  '    Case aPath of'#013#010+
  '      '#039's'#039' : CSL:=SourcePath;'#013#010+
  '      '#039'i'#039' : CSL:=IncludePath;'#013#010+
  '      '#039'u'#039' : CSL:=UnitPath;'#013#010+
  '    end;'#013#010+
  '    if Assigned(CSL) then'#013#010+
  '      Case aOp of'#013#010+
  '        '#039'*'#039' :'#013#010+
  '          if aDest<','>'#039#039' then'#013#010+
  '              begin'#013#010+
  '              CS:=CSL.Find(aDir,aTarget.Cpu,aTarget.OS);'#013#010+
  '              if Assigned(CS) then'#013#010+
  '                CS.Value:=aDest;'#013#010+
  '              end;'#013#010+
  '        '#039'-'#039':'#013#010+
  '            begin'#013#010+
  '            CS:=CSL.Find(aDi','r,aTarget.Cpu,aTarget.OS);'#013#010+
  '            if Assigned(CS) then'#013#010+
  '              CS.Free;'#013#010+
  '            end;'#013#010+
  '        '#039'+'#039':'#013#010+
  '            begin'#013#010+
  '            CS:=CSL.Find(aDir,aTarget.Cpu,aTarget.OS);'#013#010+
  '            if Assigned(CS) then'#013#010+
  '             ',' CSL.Add(aDir,[aTarget.Cpu],[aTarget.OS]);'#013#010+
  '            end;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.TransformAliases(Aliases : TStrings);'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : integer;'#013#010+
  '  N,V : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '{$IFDEF WINDOWS}'#013#010+
  '  for I := 0 to Pred(Al','iases.Count) do'#013#010+
  '    Aliases[I] := FixPath(Aliases[I]);'#013#010+
  '{$ENDIF}'#013#010+
  #013#010+
  '  For I:=Aliases.Count-1 downto 0 do'#013#010+
  '    if pos('#039'='#039',Aliases[i])>0 then'#013#010+
  '    begin'#013#010+
  '      Aliases.GetNameValue(I,N,V);'#013#010+
  #013#010+
  '      if not N.StartsWith('#039'{'#039') then'#013#010+
  '      begin'#013,#010+
  '        N:=ExtractFileName(N);'#013#010+
  '        V:=ExtractFileName(V);'#013#010+
  '        Aliases.Add(N+'#039'='#039'+V);'#013#010+
  '        N:=ChangeFileExt(N,'#039#039');'#013#010+
  '        V:=ChangeFileExt(V,'#039#039');'#013#010+
  '        Aliases.Add(N+'#039'='#039'+V);'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackag','e.ApplyNameSpaces(aEngine: TBuildEngine; aFileName:'+
  ' string; aTarget : TCompileTarget);'#013#010+
  #013#010+
  'Var'#013#010+
  '  Aliases : TStrings;'#013#010+
  '  T : TTarget;'#013#010+
  '  D : TDependency;'#013#010+
  '  CS : TConditionalString;'#013#010+
  '  aDir, aUnitFileName, aNameSpaced, aNamespacedFile, aUnit','Name : str'+
  'ing;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if not FileExists(aFileName) then'#013#010+
  '    Raise EInstallerError.CreateFmt('#039'No namespace definition file:'+
  ' %s'#039',[aFilename]);'#013#010+
  '  Aliases:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    Aliases.LoadFromFile(aFileName);'#013#010+
  '    TransFormAl','iases(Aliases);'#013#010+
  '    // Modify Targets'#013#010+
  '    For T in Targets do'#013#010+
  '      begin'#013#010+
  '      if (T.TargetType in [ttUnit,ttImplicitUnit,ttCleanOnlyUnit,ttExa'+
  'mpleUnit]) then'#013#010+
  '        begin'#013#010+
  '        aUnitFileName:=T.TargetSourceFileName;'#013#010+
  '        aNam','espacedFile:=Aliases.Values[aUnitFileName];'#013#010+
  '        if aNamespacedFile<>'#039#039' then'#013#010+
  '          begin'#013#010+
  '          aUnitName:=ExtractFileName(aNameSpacedFile);'#013#010+
  '          T.Name:=aUnitName;'#013#010+
  '          T.FTargetSourceFileName:=aNameSpacedFile;'#013#010+
  '  ','        end;'#013#010+
  '        aDir:=ExtractFilePath(aUnitFileName);'#013#010+
  '        CS:=IncludePath.Find(aDir,aTarget.CPU,aTarget.OS);'#013#010+
  '        if Not Assigned(CS) then'#013#010+
  '          IncludePath.Add(aDir,[aTarget.CPU],[aTarget.OS]);'#013#010+
  '        end;'#013#010+
  '      // D','ependencies of target, regardless of type'#013#010+
  '      For D in T.Dependencies do'#013#010+
  '        if (D.DependencyType=depUnit) then'#013#010+
  '          begin'#013#010+
  '          aUnitName:=ExtractFileName(D.Value);'#013#010+
  '          aNamespaced:=Aliases.Values[aUnitName];'#013#010+
  '   ','       if aNameSpaced<>'#039#039' then'#013#010+
  '            D.Value:=aNameSpaced;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '    ChangePaths(Aliases,aTarget);'#013#010+
  '    // manipulate Paths'#013#010+
  '  finally'#013#010+
  '    Aliases.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TPackage.ApplyNameSpaces(aEng','ine: TBuildEngine; aTarget : '+
  'TCompileTarget);'#013#010+
  #013#010+
  'Var'#013#010+
  '  aFileName : string;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if NamespaceMap='#039#039' then'#013#010+
  '    exit;'#013#010+
  '  aFileName:=NameSpaceMap;'#013#010+
  '  if Directory<>'#039#039' then'#013#010+
  '    aFileName:=IncludeTrailingPathDelimiter(Directory)+aFileNam','e;'#013+
  #010+
  '  ApplyNameSpaces(aEngine,aFileName,aTarget);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackage.SubTargetAllowed(const aSubTarget: String): Boolean;'+
  #013#010+
  'begin'#013#010+
  '  Result:=(Length(FSubTargets)=0);'#013#010+
  '  if not Result then'#013#010+
  '    Result:=IndexText(aSubTarget,FSubTarge','ts)<>-1;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                              TPackages'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TPackage','s.GetPackage(const AName : String): TPackage;'#013#010+
  'begin'#013#010+
  '  Result:=TPackage(ItemByName(AName))'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackages.GetPackageItem(AIndex : Integer): TPackage;'#013#010+
  'begin'#013#010+
  '  Result:=TPackage(Items[AIndex]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TPackages.Se','tPackageItem(AIndex : Integer; const AValue: T'+
  'Package);'#013#010+
  'begin'#013#010+
  '  Items[AIndex]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TPackages.AddPackage(const AName: String): TPackage;'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  i := IndexOfName(AName);'#013#010+
  '  if i > -1 then'#013#010+
  '    ','begin'#013#010+
  '    result := PackageItems[i];'#013#010+
  '    Installer.Log(vlWarning,Format(SWarnDuplicatePackage,[AName]))'#013+
  #010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    Result:=Add as TPackage;'#013#010+
  '    Result.Name:=AName;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TPackages.GetEnumerator',': TPackageEnumerator;'#013#010+
  'begin'#013#010+
  '  Result:= TPackageEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                             TCustomDefaults'#013#010+
  '******************************','**************************************'+
  '********}'#013#010+
  #013#010+
  'procedure TCustomDefaults.SetCPU(const AValue: TCPU);'#013#010+
  'begin'#013#010+
  '  FCompileTarget.CPU:=AValue;'#013#010+
  '  GlobalDictionary.AddVariable('#039'CPU'#039',CPUToString(FCompileTarge'+
  't.CPU));'#013#010+
  '  RecalcTarget;'#013#010+
  'end;'#013#010+
  #013,#010+
  'procedure TCustomDefaults.SetOptions(const AValue: TStrings);'#013#010+
  'begin'#013#010+
  '  If (AValue=Nil) or (AValue.Count=0) then'#013#010+
  '    FreeAndNil(Foptions)'#013#010+
  '  else'#013#010+
  '    Options.Assign(AValue)'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetBaseInstallDir: String;'#013#010,
  'begin'#013#010+
  '  If (FBaseInstallDir<>'#039#039') then'#013#010+
  '    Result:=FBaseInstallDir'#013#010+
  '  else'#013#010+
  '    if UnixPaths then'#013#010+
  '      Result:=Prefix +'#039'lib'#039' + PathDelim + '#039'fpc'#039' + Path'+
  'Delim + FCompilerVersion + PathDelim'#013#010+
  '    else'#013#010+
  '      Result:=Prefix;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'funct','ion TCustomDefaults.GetBinInstallDir: String;'#013#010+
  'begin'#013#010+
  '  If (FBinInstallDir<>'#039#039') then'#013#010+
  '    Result:=FBinInstallDir'#013#010+
  '  else'#013#010+
  '    If UnixPaths then'#013#010+
  '      Result:=Prefix+'#039'bin'#039#013#010+
  '    else'#013#010+
  '      Result:=BaseInstallDir+'#039'bin'#039'+pathdelim+MakeTargetSt','rin'+
  'g(Defaults.cpu, Defaults.OS);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetLibInstallDir: String;'#013#010+
  'begin'#013#010+
  '  If (FLibInstallDir<>'#039#039') then'#013#010+
  '    Result:=FLibInstallDir'#013#010+
  '  else'#013#010+
  '    If UnixPaths then'#013#010+
  '      Result:=Prefix+'#039'lib'#039#013#010+
  '    else'#013#010+
  '      Resu','lt:=BaseInstallDir+'#039'bin'#039'+pathdelim+MakeTargetStrin'+
  'g(Defaults.cpu, Defaults.OS);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetCompiler: String;'#013#010+
  'begin'#013#010+
  '  If (FCompiler<>'#039#039') then'#013#010+
  '    Result:=FCompiler'#013#010+
  '  else'#013#010+
  '    Result:='#039'fpc'#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'functio','n TCustomDefaults.GetDocInstallDir: String;'#013#010+
  'begin'#013#010+
  '  If (FDocInstallDir<>'#039#039') then'#013#010+
  '    Result:=FDocInstallDir'#013#010+
  '  else if (Defaults.BuildOS=freebsd) or (Defaults.BuildOS=dragonfly) t'+
  'hen'#013#010+
  '    Result:=Prefix+'#039'share'#039'+PathDelim+'#039'doc'#039'+PathDelim+',
  #039'fpc-$(CompilerVersion)'#039'+PathDelim+'#039'$(PackageName)'#039#013#010+
  '  else If UnixPaths then'#013#010+
  '    Result:=Prefix+'#039'share'#039'+PathDelim+'#039'doc'#039'+PathDelim+'#039+
  'fpc-$(CompilerVersion)'#039'+PathDelim+'#039'$(PackageName)'#039#013#010+
  '  else'#013#010+
  '    Result:=BaseInstallDir+'#039'doc'#039'+PathDelim+'#039'$(P','ackageNam'+
  'e)'#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetExamplesInstallDir: String;'#013#010+
  'begin'#013#010+
  '  If (FExamplesInstallDir<>'#039#039') then'#013#010+
  '    Result:=FExamplesInstallDir'#013#010+
  '  else if (Defaults.BuildOS=freebsd) or (Defaults.BuildOS=dragonfly) t'+
  'hen'#013#010+
  '    Re','sult:=Prefix+'#039'share'#039'+PathDelim+'#039'examples'#039'+Path'+
  'Delim+'#039'fpc-$(CompilerVersion)'#039'+PathDelim+'#039'$(PackageName)'#039+
  '+PathDelim+'#039'examples'#039#013#010+
  '  else If UnixPaths then'#013#010+
  '    Result:=Prefix+'#039'share'#039'+PathDelim+'#039'doc'#039'+PathDelim+'#039+
  'fpc-$(CompilerVersion)'#039'+PathDelim+',#039'$(PackageName)'#039'+PathDel'+
  'im+'#039'examples'#039#013#010+
  '  else'#013#010+
  '    Result:=BaseInstallDir+'#039'examples'#039'+PathDelim+'#039'$(Package'+
  'Name)'#039';'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetOptions: TStrings;'#013#010+
  'begin'#013#010+
  '  If (FOptions=Nil) then'#013#010+
  '    FOptions:=TUnsortedCompilerOption','sStringList.Create;'#013#010+
  '  Result:=FOptions;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetPrefix: String;'#013#010+
  'begin'#013#010+
  '  // Use ExpandFileName to support ~/ expansion'#013#010+
  '  if FPrefix<>'#039#039' then'#013#010+
  '    Result:=IncludeTrailingPathDelimiter(ExpandFileName(FPrefix)',')'#013+
  #010+
  '  else'#013#010+
  '    Result:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetSearchPath: TStrings;'#013#010+
  'begin'#013#010+
  '  Result := FSearchPath;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetUnitInstallDir: String;'#013#010+
  'begin'#013#010+
  '  result := FUnitInstallDir;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function',' TCustomDefaults.GetUnitConfigFilesInstallDir: String;'#013#010+
  'begin'#013#010+
  '  result := FUnitConfigFilesInstallDir;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.SetCompileTarget(AValue: TCompileTarget);'#013+
  #010+
  'begin'#013#010+
  '  if FCompileTarget.Equals(AValue) then Exit;'#013#010+
  '  FCo','mpileTarget:=AValue;'#013#010+
  '  RecalcTarget;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomDefaults.GetLocalUnitDir: String;'#013#010+
  'begin'#013#010+
  '  if FSearchPath.Count>0 then'#013#010+
  '    Result:=FSearchPath[0]'#013#010+
  '  else'#013#010+
  '    Result:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetFPUnitSourceP','ath: String;'#013#010+
  'begin'#013#010+
  '  If (FFPUnitSourcePath='#039#039') or (FFPUnitSourcePath='#039'0'#039') t'+
  'hen'#013#010+
  '    result := FFPUnitSourcePath'#013#010+
  '  else'#013#010+
  '    Result:=FixPath(FFPUnitSourcePath, True);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.SafeExpandFileName(const AFileName: s','tring)'+
  ': string;'#013#010+
  'begin'#013#010+
  '  if AFileName<>'#039#039' then'#013#010+
  '    Result:=IncludeTrailingPathDelimiter(ExpandFileName(AFileName))'#013+
  #010+
  '  else'#013#010+
  '    Result:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetTarget: String;'#013#010+
  'begin'#013#010+
  '  Result:=FCompileTarget.AsString;'#013#010+
  'e','nd;'#013#010+
  #013#010+
  'function TCustomDefaults.GetBuildCPU: TCpu;'#013#010+
  'begin'#013#010+
  '  Result:=FBuildTarget.CPU;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetBuildOS: TOS;'#013#010+
  'begin'#013#010+
  '  Result:=FBuildTarget.OS;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetBuildString: String;'#013#010+
  'begin'#013#010+
  ' ',' result := MakeTargetString(BuildCPU, BuildOS);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.GetGlobalUnitDir: String;'#013#010+
  'begin'#013#010+
  '  if FSearchPath.Count>1 then'#013#010+
  '    Result:=FSearchPath[1]'#013#010+
  '  else'#013#010+
  '    Result:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetL','ocalUnitDir(const AValue: String);'#013+
  #010+
  'begin'#013#010+
  '  // Use ExpandFileName to support ~/ expansion'#013#010+
  '  if FSearchPath.Count=0 then'#013#010+
  '    FSearchPath.Add(SafeExpandFileName(AValue))'#013#010+
  '  else'#013#010+
  '    FSearchPath[0]:=SafeExpandFileName(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'p','rocedure TCustomDefaults.SetGlobalUnitDir(const AValue: String);'#013+
  #010+
  'begin'#013#010+
  '  // Use ExpandFileName to support ~/ expansion'#013#010+
  '  if FSearchPath.Count<2 then'#013#010+
  '    begin'#013#010+
  '      if FSearchPath.Count<1 then'#013#010+
  '        FSearchPath.Add('#039#039');'#013#010+
  '      FSear','chPath.Add(SafeExpandFileName(AValue));'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    FSearchPath[1]:=SafeExpandFileName(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.IntSetBaseInstallDir(const AValue: String);'#013+
  #010+
  'begin'#013#010+
  '  if AValue<>'#039#039' then'#013#010+
  '    FBaseInstallDir:=Incl','udeTrailingPathDelimiter(AValue)'#013#010+
  '  else'#013#010+
  '    FBaseInstallDir:='#039#039';'#013#010+
  '  GlobalDictionary.AddVariable('#039'baseinstalldir'#039',BaseInstallDir'+
  ');'#013#010+
  '  GlobalDictionary.AddVariable('#039'bininstalldir'#039',BinInstallDir);'+
  #013#010+
  '  GlobalDictionary.AddVariable('#039'libinstall','dir'#039',LibInstallDir'+
  ');'#013#010+
  '  BinInstallDir:='#039#039';'#013#010+
  '  LibInstallDir:='#039#039';'#013#010+
  '  ExamplesInstallDir:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetBaseInstallDir(const AValue: String);'#013+
  #010+
  'begin'#013#010+
  '  // There must be a possibility to skip ExpandFileName. So th','at the'+
  ' files'#013#010+
  '  // can be written into an archive with a relative path.'#013#010+
  '  if AValue<>'#039#039' then'#013#010+
  '    // Use ExpandFileName to support ~/ expansion'#013#010+
  '    IntSetBaseInstallDir(ExpandFileName(AValue))'#013#010+
  '  else'#013#010+
  '    IntSetBaseInstallDir(AValue);'#013#010+
  'e','nd;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetOS(const AValue: TOS);'#013#010+
  'begin'#013#010+
  '  FCompileTarget.OS:=AValue;'#013#010+
  '  GlobalDictionary.AddVariable('#039'OS'#039',OSToString(FCompileTarget.'+
  'OS));'#013#010+
  '  Recalctarget;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetPrefix(const AVa','lue: String);'#013#010+
  'begin'#013#010+
  '  if FPrefix=AValue then exit;'#013#010+
  '  FPrefix:=AValue;'#013#010+
  '  GlobalDictionary.AddVariable('#039'prefix'#039',Prefix);'#013#010+
  '  GlobalDictionary.AddVariable('#039'bininstalldir'#039',BinInstallDir);'+
  #013#010+
  '  GlobalDictionary.AddVariable('#039'libinstalldir'#039',LibIn','stallDir'+
  ');'#013#010+
  '  BaseInstallDir:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.SetSearchPath(AValue: TStrings);'#013#010+
  'begin'#013#010+
  '  FSearchPath.Assign(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.SetSubTarget(AValue: String);'#013#010+
  'begin'#013#010+
  '  if FCompileTarget.SubTarg','et=AValue then Exit;'#013#010+
  '  FCompileTarget.SubTarget:=Lowercase(AValue);'#013#010+
  '  RecalcTarget;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetTarget(const AValue: String);'#013#010+
  'Var'#013#010+
  '  aTarget : String;'#013#010+
  'begin'#013#010+
  '  aTarget:=aValue;'#013#010+
  '  if Target<>aTarget then'#013#010+
  '   ',' begin'#013#010+
  '    FCompileTarget.AsString:=aValue;'#013#010+
  '    GlobalDictionary.AddVariable('#039'CPU'#039',CPUToString(CPU));'#013#010+
  '    GlobalDictionary.AddVariable('#039'OS'#039',OSToString(OS));'#013#010+
  '    GlobalDictionary.AddVariable('#039'SUBTARGET'#039',SubTarget);'#013#010+
  '    GlobalDictionary.','AddVariable('#039'target'#039',Target);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.SetUnitInstallDir(const AValue: String);'#013+
  #010+
  'begin'#013#010+
  '  if AValue<>'#039#039' then'#013#010+
  '    FUnitInstallDir:=AValue'#013#010+
  '  else'#013#010+
  '    FUnitInstallDir:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefa','ults.SetUnitConfigFilesInstallDir(const AValue:'+
  ' String);'#013#010+
  'begin'#013#010+
  '  FUnitConfigFilesInstallDir:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SetZipPrefix(AValue: String);'#013#010+
  'begin'#013#010+
  '  if FZipPrefix=AValue then Exit;'#013#010+
  '  FZipPrefix:=AValue;'#013#010+
  'end;',#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.RecalcTarget;'#013#010+
  'begin'#013#010+
  '  GlobalDictionary.AddVariable('#039'target'#039',Target);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.CmdLineOptions: String;'#013#010+
  'begin'#013#010+
  '  If Haveoptions then'#013#010+
  '    Result:=OptionListToString(FOptions);'#013#010+
  'end;'#013,#010+
  #013#010+
  #013#010+
  'constructor TCustomDefaults.Create;'#013#010+
  'begin'#013#010+
  '  FSearchPath:=TStringList.Create;'#013#010+
  '  InitDefaults;'#013#010+
  '  FBuildTarget.OS:= StringToOS({$I %FPCTARGETOS%});'#013#010+
  '  FBuildTarget.CPU:= StringToCPU({$I %FPCTARGETCPU%});'#013#010+
  '  FBuildTarget.SubTarget:='#039#039';',#013#010+
  'end;'#013#010+
  #013#010+
  'destructor TCustomDefaults.Destroy;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FOptions);'#013#010+
  '  FreeAndNil(FSearchPath);'#013#010+
  '  inherited;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.InitDefaults;'#013#010+
  'begin'#013#010+
  '{$ifdef unix}'#013#010+
  '  UnixPaths:=True;'#013#010+
  '{$else}'#013#010+
  '  UnixPaths:=Fals','e;'#013#010+
  '{$endif}'#013#010+
  '  FNoFPCCfg:=False;'#013#010+
  '  FCompileTarget.CPU:=cpuNone;'#013#010+
  '  FCompileTarget.OS:=osNone;'#013#010+
  '  FCompileTarget.Subtarget:='#039#039';'#013#010+
  '  FUnitInstallDir:='#039'$(baseinstalldir)units/$(target)/$(packagename'+
  ')'#039';'#013#010+
  '  FUnitConfigFilesInstallDir:='#039'fpmkinst','/$(target)'#039';'#013#010+
  '  FBuildMode:=bmOneByOne;'#013#010+
  '  FThreadsAmount:=-1;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.HaveOptions: Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=Assigned(FOptions);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomDefaults.AddOption(const aValue: string);'#013#010+
  'begin'#013#010+
  '  Optio','ns.Add(aValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomDefaults.IsBuildDifferentFromTarget: boolean;'#013#010+
  'begin'#013#010+
  '  result := IsDifferentFromBuild(CPU,OS);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.LocalInit(const AFileName: String);'#013#010+
  'Var'#013#010+
  '  FN : String;'#013#010+
  'begin'#013#010+
  ' ',' FN:=AFileName;'#013#010+
  '  If (FN='#039#039') then'#013#010+
  '    begin'#013#010+
  '    // Environment variable.'#013#010+
  '    FN:={$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.GetEnvironment'+
  'Variable('#039'FPMAKECFG'#039');'#013#010+
  '    If (FN<>'#039#039') then'#013#010+
  '      If not FileExists(FN) then'#013#010+
  '        FN:='#039,#039';'#013#010+
  '    // User config file fpmake.cfg'#013#010+
  '    If (FN='#039#039') then'#013#010+
  '      begin'#013#010+
  '      FN:=GetAppConfigFile(False);'#013#010+
  '      If Not FileExists(FN) then'#013#010+
  '        FN:='#039#039';'#013#010+
  '      end;'#013#010+
  '    // Global config file fpmake.cfg'#013#010+
  '    If (FN='#039#039') then'#013#010+
  '      be','gin'#013#010+
  '      FN:=GetAppConfigFile(True);'#013#010+
  '      If Not FileExists(FN) then'#013#010+
  '        FN:='#039#039';'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  If (FN<>'#039#039') and FileExists(FN) then'#013#010+
  '    LoadFromFile(FN);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.CompilerDefaults;'#013#010+
  #013#010+
  'var'#013#010+
  '  i','nfoSL : TStringList;'#013#010+
  #013#010+
  #013#010+
  'begin'#013#010+
  '  infosl:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    infosl.Delimiter:='#039' '#039';'#013#010+
  '    if (CPU=cpuNone) or'#013#010+
  '       ((OS=osNone) and not ExplicitOSNone) or'#013#010+
  '       (FCompilerVersion='#039#039') then'#013#010+
  '    begin'#013#010+
  '{$ifdef HAS_UNIT_PROCE','SS}'#013#010+
  '      // Detect compiler version/target from -i option'#013#010+
  '        infosl.DelimitedText:=GetCompilerInfo(GetCompiler,['#039'-iVTPT'+
  'O'#039'],False, True);'#013#010+
  '        if infosl.Count<>3 then'#013#010+
  '          Raise EInstallerError.Create(SErrInvalidFPCInfo);'#013#010,
  '        if FCompilerVersion='#039#039' then'#013#010+
  '          FCompilerVersion:=infosl[0];'#013#010+
  '        if CPU=cpuNone then'#013#010+
  '          CPU:=StringToCPU(infosl[1]);'#013#010+
  '        if (OS=osNone) and not ExplicitOSNone then'#013#010+
  '          OS:=StringToOS(infosl[2]);'#013#010+
  #013#010+
  '{$','else HAS_UNIT_PROCESS}'#013#010+
  '      // Defaults taken from compiler used to build fpmake'#013#010+
  '      if CPU=cpuNone then'#013#010+
  '        CPU:=StringToCPU({$I %FPCTARGETCPU%});'#013#010+
  '      if (OS=osNone) and not ExplicitOSNone then'#013#010+
  '        OS:=StringToOS({$I %FPC','TARGETOS%});'#013#010+
  '      if FCompilerVersion='#039#039' then'#013#010+
  '        FCompilerVersion:={$I %FPCVERSION%};'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  '    end;'#013#010+
  '  if (FSourceTarget.OS=osNone) then'#013#010+
  '    begin'#013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '      // Detect compiler version/','target from -i option'#013#010+
  '      infosl.DelimitedText:=GetCompilerInfo(GetCompiler,['#039'-iDWSPSO'+
  #039'], False, True);'#013#010+
  '      if infosl.Count<>4 then'#013#010+
  '        Raise EInstallerError.Create(SErrInvalidFPCInfo);'#013#010+
  '      FCompilerDate:=infosl[0];'#013#010+
  '      FFu','llCompilerVersion:=infosl[1];'#013#010+
  '      FSourceTarget.CPU:=StringToCPU(infosl[2]);'#013#010+
  '      FSourceTarget.OS:=StringToOS(infosl[3]);'#013#010+
  '{$else HAS_UNIT_PROCESS}'#013#010+
  '      // Defaults taken from compiler used to build fpmake'#013#010+
  '      FSourceTarget.CPU:=','StringToCPU({$I %FPCTARGETCPU%});'#013#010+
  '      FSourceTarget.OS:=StringToOS({$I %FPCTARGETOS%});'#013#010+
  '      FFullCompilerVersion:={$I %FPCFULLVERSION%};'#013#010+
  '      FCompilerDate:={$I %FPCDATE%};'#013#010+
  '{$endif HAS_UNIT_PROCESS}'#013#010+
  '    end;'#013#010+
  '  finally'#013#010+
  '    infosl','.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.LoadFromFile(const AFileName: String);'#013#010+
  'Var'#013#010+
  '  F : TFileStream;'#013#010+
  'begin'#013#010+
  '  F:=TFileStream.Create(AFileName,fmOpenRead or fmShareDenyNone);'#013#010+
  '  Try'#013#010+
  '    LoadFromStream(F);'#013#010+
  '  Finally'#013#010+
  '    F.F','ree;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SaveToFile(const AFileName: String);'#013#010+
  'Var'#013#010+
  '  F : TFileStream;'#013#010+
  'begin'#013#010+
  '  F:=TFileStream.Create(AFileName,fmCreate or fmShareDenyNone);'#013#010+
  '  Try'#013#010+
  '    SaveToStream(F);'#013#010+
  '  Finally'#013#010+
  '    F.Free;'#013#010+
  '  ','end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.SaveToStream(S : TStream);'#013#010+
  'Var'#013#010+
  '  L : TStringList;'#013#010+
  'begin'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    With L do'#013#010+
  '      begin'#013#010+
  '      Values[KeyArchive]:=FArchive;'#013#010+
  '      Values[KeyCompiler]:=FCompiler;'#013#010+
  ' ','     Values[KeyCopy]:=FCopy;'#013#010+
  '      Values[KeyMkDir]:=FMkDir;'#013#010+
  '      Values[KeyMove]:=FMove;'#013#010+
  '      Values[KeyOptions]:=CmdLineOptions;'#013#010+
  '      Values[KeyCPU]:=CPUToString(CPU);'#013#010+
  '      Values[KeyOS]:=OSToString(OS);'#013#010+
  '      Values[KeyMode]:=M','odeToString(FMode);'#013#010+
  '      Values[KeyLocalUnitDir]:=LocalUnitDir;'#013#010+
  '      Values[KeyGlobalUnitDir]:=GlobalUnitDir;'#013#010+
  '      Values[KeyPrefix]:=FPrefix;'#013#010+
  '      Values[KeyBaseInstallDir]:=FBaseInstallDir;'#013#010+
  '      Values[KeyUnitInstallDir]:=FUnitI','nstallDir;'#013#010+
  '      Values[KeyBinInstallDir]:=FBinInstallDir;'#013#010+
  '      Values[KeyLibInstallDir]:=FLibInstallDir;'#013#010+
  '      Values[KeyDocInstallDir]:=FDocInstallDir;'#013#010+
  '      Values[KeyExamplesInstallDir]:=FExamplesInstallDir;'#013#010+
  '      Values[KeyRemove',']:=FRemove;'#013#010+
  '      Values[KeyRemoveDir]:=FRemoveDir;'#013#010+
  '      Values[KeyRemoveTree]:=FRemoveTree;'#013#010+
  '      Values[KeyTarget]:=Target;'#013#010+
  '      if FNoFPCCfg then'#013#010+
  '        Values[KeyNoFPCCfg]:='#039'Y'#039';'#013#010+
  '      if FUseEnvironment then'#013#010+
  '        Values[Key','UseEnv]:='#039'Y'#039';'#013#010+
  '      if FInstallExamples then'#013#010+
  '          Values[KeyInstallExamples]:='#039'Y'#039';'#013#010+
  '      if FSkipCrossPrograms then'#013#010+
  '        Values[KeySkipCrossPrograms]:='#039'Y'#039';'#013#010+
  '      if FSkipAllPrograms then'#013#010+
  '        Values[KeySkipAllPrograms]:='#039'Y'#039,';'#013#010+
  '      end;'#013#010+
  '    L.SaveToStream(S);'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomDefaults.LoadFromStream(S: TStream);'#013#010+
  'Var'#013#010+
  '  L : TStrings;'#013#010+
  '  Line : String;'#013#010+
  '  I,P,PC : Integer;'#013#010+
  'begin'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '   ',' L.LoadFromStream(S);'#013#010+
  '    // Fix lines.'#013#010+
  '    For I:=L.Count-1 downto 0 do'#013#010+
  '      begin'#013#010+
  '      Line:=L[I];'#013#010+
  '      P:=Pos('#039'='#039',Line);'#013#010+
  '      PC:=Pos('#039';'#039',Line);  // Comment line.'#013#010+
  '      If (P=0) or ((PC<>0) and (PC<P)) then'#013#010+
  '        L.Delete(I',')'#013#010+
  '      else'#013#010+
  '        L[i]:=Trim(System.Copy(Line,1,P-1)+'#039'='#039'+Trim(System.Cop'+
  'y(Line,P+1,Length(Line)-P)));'#013#010+
  '      end;'#013#010+
  '    With L do'#013#010+
  '      begin'#013#010+
  '      FArchive:=Values[KeyArchive];'#013#010+
  '      FCompiler:=Values[KeyCompiler];'#013#010+
  '      FCopy:=Val','ues[KeyCopy];'#013#010+
  '      FMkDir:=Values[KeyMkDir];'#013#010+
  '      FMove:=Values[KeyMove];'#013#010+
  '      FRemove:=Values[KeyRemove];'#013#010+
  '      FRemoveDir:=Values[KeyRemoveDir];'#013#010+
  '      FRemoveTree:=Values[KeyRemoveTree];'#013#010+
  '      Self.Options:=OptionsToStringList(Va','lues[KeyOptions]);'#013#010+
  '      Line:=Values[KeyCPU];'#013#010+
  '      If (Line<>'#039#039') then'#013#010+
  '        FCompileTarget.CPU:=StringToCPU(Line);'#013#010+
  '      Line:=Values[KeyOS];'#013#010+
  '      If (Line<>'#039#039') then'#013#010+
  '        FCompileTarget.OS:=StringToOS(Line);'#013#010+
  '      Line:=Value','s[KeyMode];'#013#010+
  '      If (Line<>'#039#039') then'#013#010+
  '        FMode:=StringToMode(Line);'#013#010+
  '      LocalUnitDir:=Values[KeyLocalUnitDir];'#013#010+
  '      GlobalUnitDir:=Values[KeyGlobalUnitDir];'#013#010+
  '      FPrefix:=Values[KeyPrefix];'#013#010+
  '      FBaseInstallDir:=Values[KeyBas','eInstallDir];'#013#010+
  '      FUnitInstallDir:=Values[KeyUnitInstallDir];'#013#010+
  '      FBinInstallDir:=Values[KeyBinInstallDir];'#013#010+
  '      FLibInstallDir:=Values[KeyLibInstallDir];'#013#010+
  '      FDocInstallDir:=Values[KeyDocInstallDir];'#013#010+
  '      FExamplesInstallDir:=','Values[KeyExamplesInstallDir];'#013#010+
  '      FInstallExamples:=(Upcase(Values[KeyInstallExamples])='#039'Y'#039+
  ');'#013#010+
  '      FSkipCrossPrograms:=(Upcase(Values[KeySkipCrossPrograms])='#039'Y'+
  #039');'#013#010+
  '      FSkipAllPrograms:=(Upcase(Values[KeySkipAllPrograms])='#039'Y'#039+
  ');'#013#010+
  '   ','   FNoFPCCfg:=(Upcase(Values[KeyNoFPCCfg])='#039'Y'#039');'#013#010+
  '      FUseEnvironment:=(Upcase(Values[KeyUseEnv])='#039'Y'#039');'#013#010+
  #013#010+
  '      GlobalDictionary.AddVariable('#039'target'#039',Target);'#013#010+
  '      GlobalDictionary.AddVariable('#039'baseinstalldir'#039',BaseInstal'+
  'lDir);'#013#010+
  '      G','lobalDictionary.AddVariable('#039'prefix'#039',Prefix);'#013#010+
  '      GlobalDictionary.AddVariable('#039'bininstalldir'#039',BinInstallD'+
  'ir);'#013#010+
  '      GlobalDictionary.AddVariable('#039'libinstalldir'#039',LibInstallD'+
  'ir);'#013#010+
  '      end;'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{**','*****************************************************************'+
  '*********'#013#010+
  '                             TFPCDefaults'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'procedure TFPCDefaults.CompilerDefaults;',#013#010+
  'var'#013#010+
  '  BD : String;'#013#010+
  'begin'#013#010+
  '  inherited CompilerDefaults;'#013#010+
  #013#010+
  '  // Use the same algorithm as the compiler, see options.pas'#013#010+
  '{$ifdef Unix}'#013#010+
  '  BD:=FixPath(GetEnvironmentVariable('#039'FPCDIR'#039'), False);'#013#010+
  '  if BD='#039#039' then'#013#010+
  '    begin'#013#010+
  '      BD:='#039'/usr','/local/lib/fpc/'#039'+FCompilerVersion;'#013#010+
  '      if not DirectoryExists(BD) and'#013#010+
  '         DirectoryExists('#039'/usr/lib/fpc/'#039'+FCompilerVersion) the'+
  'n'#013#010+
  '        BD:='#039'/usr/lib/fpc/'#039'+FCompilerVersion;'#013#010+
  '    end;'#013#010+
  '{$else unix}'#013#010+
  '  BD:=FixPath({$IFDEF FPC_DOTT','EDUNITS}System.{$ENDIF}SysUtils.GetEnv'+
  'ironmentVariable('#039'FPCDIR'#039'), False);'#013#010+
  '  if BD='#039#039' then'#013#010+
  '    begin'#013#010+
  '      BD:=ExtractFilePath(FCompiler)+'#039'..'#039';'#013#010+
  '      if not(DirectoryExists(BD+'#039'/units'#039')) and'#013#010+
  '         not(DirectoryExists(BD+'#039'/rtl'#039')) then',#013#010+
  '        BD:=FBaseInstallDir+'#039'..'#039';'#013#010+
  '    end;'#013#010+
  '{$endif unix}'#013#010+
  #013#010+
  '  // Where to install by default'#013#010+
  '  if (FBaseInstallDir='#039#039') and (FPrefix='#039#039') then'#013#010+
  '    BaseInstallDir:=BD;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************','**********'+
  '*********'#013#010+
  '                            TCustomInstaller'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'constructor TCustomInstaller.Create(AOwner: TComponent);'#013#010+
  'begin'#013#010+
  '  Inherited;'#013#010+
  '  FPackageVar','iantSettings := TStringList.Create;'#013#010+
  '  FPackageVariants := TFPList.Create;'#013#010+
  '  GlobalDictionary:=DictionaryClass.Create(Nil);'#013#010+
  '  AnalyzeOptions;'#013#010+
  '  GlobalDictionary.AddVariable('#039'baseinstalldir'#039',Defaults.BaseI'+
  'nstallDir);'#013#010+
  '  GlobalDictionary.A','ddVariable('#039'bininstalldir'#039',Defaults.BinI'+
  'nstallDir);'#013#010+
  '  GlobalDictionary.AddVariable('#039'libinstalldir'#039',Defaults.LibIns'+
  'tallDir);'#013#010+
  '  GlobalDictionary.AddVariable('#039'Target'#039',Defaults.Target);'#013#010+
  '  GlobalDictionary.AddVariable('#039'BuildString'#039',Defaults.B','uildS'+
  'tring);'#013#010+
  '  GlobalDictionary.AddVariable('#039'Prefix'#039',Defaults.Prefix);'#013#010+
  '  GlobalDictionary.AddVariable('#039'CompilerVersion'#039',Defaults.Comp'+
  'ilerVersion);'#013#010+
  '  FNotifyEventCollection := TNotifyEventCollection.create([neaBeforeCo'+
  'mpile, neaAfterCompi','le, neaBeforeClean, neaAfterClean,'#013#010+
  '                                                           neaBeforeIn'+
  'stall, neaAfterInstall, neaBeforeArchive, neaAfterArchive,'#013#010+
  '                                                           neaBeforeMa'+
  'nife','st, neaAfterManifest, neaBeforePkgList, neaAfterPkgList,'#013#010+
  '                                                           neaBeforeUn'+
  'Install, neaAfterUnInstall,'#013#010+
  '                                                           neaBeforeCr'+
  'eateBuildEngi','ne, neaAfterCreateBuildengine]);'#013#010+
  '  CreatePackages;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TCustomInstaller.destroy;'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  FreePackages;'#013#010+
  '  FreeAndNil(Defaults);'#013#010+
  '  FreeAndNil(GlobalDictionary);'#013#010+
  '  FreeAndNil(FPackageVariantSettings)',';'#013#010+
  '  for i := 0 to FPackageVariants.Count-1 do'#013#010+
  '    begin'#013#010+
  '    if TPackageVariants(FPackageVariants.Items[i]).Owner=Self then'#013+
  #010+
  '      TPackageVariants(FPackageVariants.Items[i]).Free;'#013#010+
  '    end;'#013#010+
  '  FreeAndNil(FPackageVariants);'#013#010+
  '  FreeAndNil(','FNotifyEventCollection);'#013#010+
  '  inherited destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomInstaller.GetPackages: TPackages;'#013#010+
  'begin'#013#010+
  '  result := FPackages;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.Log(Level: TVerboseLevel; const Msg: String'+
  ');'#013#010+
  'begin'#013#010+
  '  If (Level i','n FLogLevels) or (ListMode and (level=vlCommand)) then'#013+
  #010+
  '    begin'#013#010+
  '    Writeln(StdOut, Msg);'#013#010+
  '    Flush(StdOut);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.CreatePackages;'#013#010+
  'begin'#013#010+
  '  FPackages:=TPackages.Create(TPackage);'#013#010+
  'end;'#013#010+
  #013#010+
  'proce','dure TCustomInstaller.FreePackages;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FPackages);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.CreateBuildEngine;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeCreateBuildEngine, Self);'#013+
  #010+
  '  FBuildEngine:=TBuildEngine.Create','(Self);'#013#010+
  '//  FBuildEngine.Defaults:=Defaults;'#013#010+
  '  FBuildEngine.ListMode:=FListMode;'#013#010+
  '  FBuildEngine.FInteractive:=FInteractive;'#013#010+
  '  FBuildEngine.Verbose := (vlInfo in FLogLevels) or (vlDebug in FLogLe'+
  'vels);'#013#010+
  '  FBuildEngine.OnLog:=@Self.Log;'#013#010,
  '  NotifyEventCollection.CallEvents(neaAfterCreateBuildengine, Self);'#013+
  #010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Error(const Msg: String);'#013#010+
  'begin'#013#010+
  '  Raise EInstallerError.Create(Msg);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Error(const Fmt: String;',' const Args: arra'+
  'y of const);'#013#010+
  'begin'#013#010+
  '  Raise EInstallerError.CreateFmt(Fmt,Args);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCustomInstaller.AddPackage(const AName: String): TPackage;'#013+
  #010+
  'begin'#013#010+
  '  result:=Packages.AddPackage(AName);'#013#010+
  '  AddAutoPackageVariantsToPack','age(result);'#013#010+
  #013#010+
  '  if Defaults.UnitOutputDirectory <> '#039#039' then'#013#010+
  '    Result.FUnitsOutputDir := IncludeTrailingPathDelimiter(Defaults.Un'+
  'itOutputDirectory) + Result.FUnitsOutputDir;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomInstaller.AddPackageVariant(AName: str','ing;'#013#010+
  '  AIsInheritable: boolean; AutoAddToPackage: Boolean): TPackageVariant'+
  's;'#013#010+
  'begin'#013#010+
  '  result := TPackageVariants.Create(TPackageVariant);'#013#010+
  '  result.Name:=AName;'#013#010+
  '  result.FIsInheritable:=AIsInheritable;'#013#010+
  '  result.FAutoAddToPackage:=AutoA','ddToPackage;'#013#010+
  '  FPackageVariants.Add(result);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomInstaller.AddPackageFromDir(const AName: String; const'+
  ' aDirectory: String; const aMask: string): TPackage;'#013#010+
  'begin'#013#010+
  '  Result:=AddPackage(aName);'#013#010+
  '  if Result.AddTargetsFr','omDir(aDirectory,aMask)<=0 then'#013#010+
  '    Result.Free'#013#010+
  '  else'#013#010+
  '    Result.Dependencies.Clear;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.AnalyzeOptions;'#013#010+
  #013#010+
  '  Function CheckOption(Index : Integer;const Short,Long : String; AddT'+
  'oOptionString: boolean = f','alse): Boolean;'#013#010+
  '  var'#013#010+
  '    O : String;'#013#010+
  '  begin'#013#010+
  '    O:=Paramstr(Index);'#013#010+
  '    Result:=(O='#039'-'#039'+short) or (O='#039'--'#039'+long) or (copy(O,'+
  '1,Length(Long)+3)=('#039'--'#039'+long+'#039'='#039'));'#013#010+
  '    if AddToOptionString and Result then'#013#010+
  '      FFPMakeOptionsString := FF','PMakeOptionsString+'#039' '#039'+O;'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  '  Function CheckBuildOptionSetValue(Index: Integer): boolean;'#013#010+
  '  var'#013#010+
  '    O : String;'#013#010+
  '    BuildModeName: string;'#013#010+
  '    P: integer;'#013#010+
  '    C: string;'#013#010+
  '    PV: TPackageVariants;'#013#010+
  '    SL: TStringList;'#013#010+
  '  begi','n'#013#010+
  '    O:=Paramstr(Index);'#013#010+
  '    result := O[1]='#039'+'#039';'#013#010+
  '    if result then'#013#010+
  '      begin'#013#010+
  '      P:=Pos('#039'='#039',Paramstr(Index));'#013#010+
  '      If (P=0) then'#013#010+
  '        Error(SErrNeedArgument,[Index,O])'#013#010+
  '      else'#013#010+
  '        begin'#013#010+
  '        BuildModeName:=copy','(o,2,P-2);'#013#010+
  '        Delete(O,1,P);'#013#010+
  #013#010+
  '        c := RightStr(BuildModeName,1);'#013#010+
  '        if (c = '#039'*'#039') or (c = '#039'+'#039') then'#013#010+
  '          begin'#013#010+
  '          // Add a new package-variant'#013#010+
  '          BuildModeName := copy(BuildModeName, 1, length(BuildMo','deNa'+
  'me) -1);'#013#010+
  '          PV := AddPackageVariant(BuildModeName, (C = '#039'*'#039'), Tr'+
  'ue);'#013#010+
  '          SL := TStringList.Create;'#013#010+
  '          try'#013#010+
  '            SL.CommaText := O;'#013#010+
  '            if SL.Count=0 then'#013#010+
  '              Error(SErrExpectPkgVariant,[','Index,ParamStr(Index)]);'#013+
  #010+
  '            for P := 0 to SL.Count -1 do'#013#010+
  '              begin'#013#010+
  '              PV.Add(SL.ValueFromIndex[P]);'#013#010+
  '              end;'#013#010+
  '            FPackageVariantSettings.Values[BuildModeName] := SL.ValueF'+
  'romIndex[0];'#013#010+
  '  ','        finally'#013#010+
  '            SL.Free;'#013#010+
  '          end;'#013#010+
  '          end'#013#010+
  '        else'#013#010+
  '          begin'#013#010+
  '          // Set the value of the package-variant.'#013#010+
  '          FPackageVariantSettings.Values[BuildModeName] := O;'#013#010+
  '          end;'#013#010+
  '        ','end;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  Function CheckCustomOption(Index : Integer; out CustOptName: string)'+
  ': Boolean;'#013#010+
  '  var'#013#010+
  '    O : String;'#013#010+
  '    i : integer;'#013#010+
  '  begin'#013#010+
  '    result := false;'#013#010+
  '    CustOptName:='#039#039';'#013#010+
  '    O:=Paramstr(Index);'#013#010+
  '    if cop','y(O,1,2)<>'#039'--'#039' then'#013#010+
  '      Exit;'#013#010+
  '    i := pos('#039'='#039',O);'#013#010+
  '    if i=0 then'#013#010+
  '      Exit;'#013#010+
  '    O:=copy(O,3,i-3);'#013#010+
  '    CustOptName:=O;'#013#010+
  '    Result:=CustomFpmakeCommandlineOptions.IndexOfName(O)>-1;'#013#010+
  '    if Result then FFPMakeOptionsString := FFPM','akeOptionsString+'#039+
  ' '#039'+Paramstr(Index);'#013#010+
  '  end;'#013#010+
  #013#010+
  #013#010+
  '  Function CheckCommand(Index : Integer;const Short,Long : String): Bo'+
  'olean;'#013#010+
  '  var'#013#010+
  '    O : String;'#013#010+
  '  begin'#013#010+
  '    O:=Paramstr(Index);'#013#010+
  '    Result:=(O='#039'-'#039'+short) or (O=long);'#013#010+
  '  end;'#013#010+
  #013#010+
  '  F','unction OptionArg(Var Index : Integer; AddToOptionString: boolean'+
  ' = false) : String;'#013#010+
  '  Var'#013#010+
  '    P : Integer;'#013#010+
  '  begin'#013#010+
  '    if (Length(ParamStr(Index))>1) and (Paramstr(Index)[2]<>'#039'-'#039+
  ') then'#013#010+
  '      begin'#013#010+
  '      If Index<ParamCount then'#013#010+
  '    ','    begin'#013#010+
  '        Inc(Index);'#013#010+
  '        Result:=Paramstr(Index);'#013#010+
  '        if AddToOptionString then'#013#010+
  '          FFPMakeOptionsString := FFPMakeOptionsString+'#039' '#039'+Res'+
  'ult;'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '        Error(SErrNeedArgument,[Index,ParamStr','(Index)]);'#013#010+
  '      end'#013#010+
  '    else If length(ParamStr(Index))>2 then'#013#010+
  '      begin'#013#010+
  '      P:=Pos('#039'='#039',Paramstr(Index));'#013#010+
  '      If (P=0) then'#013#010+
  '        Error(SErrNeedArgument,[Index,ParamStr(Index)])'#013#010+
  '      else'#013#010+
  '        begin'#013#010+
  '        Result:=Par','amstr(Index);'#013#010+
  '        Delete(Result,1,P);'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  function SplitSpaces(var SplitString: string) : string;'#013#010+
  '  var i : integer;'#013#010+
  '  begin'#013#010+
  '    i := pos('#039' '#039',SplitString);'#013#010+
  '    if i > 0 then'#013#010+
  '      begin'#013#010+
  '        ','result := copy(SplitString,1,i-1);'#013#010+
  '        delete(SplitString,1,i);'#013#010+
  '      end'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '        result := SplitString;'#013#010+
  '        SplitString:='#039#039';'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  Function CheckPackageVariantOptionSetValue(Index: Inte','ger): boolea'+
  'n;'#013#010+
  '  var'#013#010+
  '    O : String;'#013#010+
  '    OptionName: string;'#013#010+
  '    I,J: integer;'#013#010+
  '    P: Integer;'#013#010+
  '    PV: TPackageVariants;'#013#010+
  '  begin'#013#010+
  '    result := false;'#013#010+
  '    O:=Paramstr(Index);'#013#010+
  '    if copy(O,1,2)<>'#039'--'#039' then'#013#010+
  '      Exit;'#013#010+
  '    P:=Pos('#039,'='#039',Paramstr(Index));'#013#010+
  '    if P > 0 then'#013#010+
  '      begin'#013#010+
  '      OptionName:=copy(o,3,P-3);'#013#010+
  '      Delete(O,1,P);'#013#010+
  '      for I := 0 to FPackageVariants.Count -1 do'#013#010+
  '        begin'#013#010+
  '        PV := TObject(FPackageVariants.Items[I]) as TPackageVaria','nts'+
  ';'#013#010+
  '        for J := 0 to PV.Count-1 do'#013#010+
  '          begin'#013#010+
  '          if OptionName = '#039'options_'#039'+PV.Name+'#039'_'#039'+PV.It'+
  'ems[J].Name then'#013#010+
  '            begin'#013#010+
  '            result := true;'#013#010+
  '            while O <> '#039#039' do'#013#010+
  '              (PV.Items[J] as ','TPackageVariant).AddOption(SplitSpaces'+
  '(O));'#013#010+
  '            end;'#013#010+
  '          end;'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  DefaultsFileName : string;'#013#010+
  '  OptString : string;'#013#010+
  '  CustOptName : string;'#013#010+
  '  UnitDirSet: Boolean;'#013#010+
  '  ','SearchPathSet: Boolean;'#013#010+
  'begin'#013#010+
  '  I:=0;'#013#010+
  '  FListMode:=False;'#013#010+
  '  UnitDirSet:=False;'#013#010+
  '  SearchPathSet:=False;'#013#010+
  '  FLogLevels:=DefaultMessages;'#013#010+
  '  While (I<ParamCount) do'#013#010+
  '    begin'#013#010+
  '    Inc(I);'#013#010+
  '    if CheckOption(I,'#039'v'#039','#039'verbose'#039') then'#013#010+
  '      ','FLogLevels:=AllMessages'#013#010+
  '    else if CheckOption(I,'#039'I'#039','#039'interactive'#039') then'#013#010+
  '      FInteractive:=true'#013#010+
  '    else if CheckOption(I,'#039'd'#039','#039'debug'#039') then'#013#010+
  '      FLogLevels:=AllMessages+[vlDebug]'#013#010+
  '    else if CheckCommand(I,'#039'm'#039','#039'compile'#039') then'#013#010+
  '    ','  FRunMode:=rmCompile'#013#010+
  '    else if CheckCommand(I,'#039'b'#039','#039'build'#039') then'#013#010+
  '      FRunMode:=rmBuild'#013#010+
  '    else if CheckCommand(I,'#039'i'#039','#039'install'#039') then'#013#010+
  '      FRunMode:=rmInstall'#013#010+
  '    else if CheckCommand(I,'#039'bi'#039','#039'buildinstall'#039') then'#013+
  #010+
  '      FRunMode:=r','mBuildInstall'#013#010+
  '    else if CheckCommand(I,'#039'zi'#039','#039'zipinstall'#039') then'#013+
  #010+
  '      FRunMode:=rmZipInstall'#013#010+
  '    else if CheckCommand(I,'#039'c'#039','#039'clean'#039') then'#013#010+
  '      FRunMode:=rmClean'#013#010+
  '    else if CheckCommand(I,'#039'dc'#039','#039'distclean'#039') then'#013#010+
  '      FRunMode:=rmDis','tClean'#013#010+
  '    else if CheckCommand(I,'#039'a'#039','#039'archive'#039') then'#013#010+
  '      FRunMode:=rmarchive'#013#010+
  '    else if CheckCommand(I,'#039'M'#039','#039'manifest'#039') then'#013#010+
  '      FRunMode:=rmManifest'#013#010+
  '    else if CheckCommand(I,'#039'l'#039','#039'pkglist'#039') then'#013#010+
  '      FRunMode:=rmPkgList'#013#010+
  '    e','lse if CheckCommand(I,'#039'u'#039','#039'uninstall'#039') then'#013+
  #010+
  '      FRunMode:=rmUnInstall'#013#010+
  '    else if CheckCommand(I,'#039'in'#039','#039'info'#039') then'#013#010+
  '      FRunMode:=rmInfo'#013#010+
  '    else if CheckOption(I,'#039'h'#039','#039'help'#039') then'#013#010+
  '      Usage('#039#039',[])'#013#010+
  '    else if Checkoption(I,'#039'C'#039','#039'c','pu'#039') then'#013#010+
  '      Defaults.CPU:=StringToCPU(OptionArg(I))'#013#010+
  '    else if Checkoption(I,'#039'O'#039','#039'os'#039') then'#013#010+
  '      begin'#013#010+
  '        Defaults.OS:=StringToOS(OptionArg(I));'#013#010+
  '        Defaults.ExplicitOSNone := OptionArg(I) = OSToString(osNone);'#013+
  #010+
  '      en','d'#013#010+
  '    else if Checkoption(I,'#039't'#039','#039'target'#039') then'#013#010+
  '      Defaults.Target:=OptionArg(I)'#013#010+
  '    else if Checkoption(I,'#039's'#039','#039'subtarget'#039') then'#013#010+
  '      Defaults.SubTarget:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'lc'#039','#039'list-commands'#039') then'#013+
  #010+
  '      FList','Mode:=True'#013#010+
  '    else if Checkoption(I,'#039'P'#039','#039'prefix'#039') then'#013#010+
  '      Defaults.Prefix:=OptionArg(I)'#013#010+
  '    else if Checkoption(I,'#039'n'#039','#039'nofpccfg'#039') then'#013#010+
  '      Defaults.NoFPCCfg:=true'#013#010+
  '    else if Checkoption(I,'#039'zp'#039','#039'zipprefix'#039') then'#013#010+
  '      Defaults.Z','ipPrefix:=OptionArg(I)'#013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '    else if Checkoption(I,'#039'e'#039','#039'useenv'#039') then'#013#010+
  '      Defaults.UseEnvironment:=true'#013#010+
  '{$endif}'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '    else if CheckOption(I,'#039'T'#039','#039'threads'#039') then'#013#010+
  '      Defaults.ThreadsAmo','unt:=StrToIntDef(OptionArg(I),-1)'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '    else if CheckOption(I,'#039'B'#039','#039'baseinstalldir'#039') then'#013+
  #010+
  '      Defaults.BaseInstallDir:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'BI'#039','#039'bininstalldir'#039') then'#013+
  #010+
  '      Defaults.BinInstallDir:','=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'LI'#039','#039'libinstalldir'#039') then'#013+
  #010+
  '      Defaults.LibInstallDir:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'U'#039','#039'unitinstalldir'#039') then'#013+
  #010+
  '      Defaults.UnitInstallDir:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'U','L'#039','#039'localunitdir'#039') then'#013+
  #010+
  '      begin'#013#010+
  '        UnitDirSet:=true;'#013#010+
  '        // Do not warn against the combination of SearchPath and'#013#010+
  '        // localunitdir when they are the same. (This is done to be ab'+
  'le'#013#010+
  '        // to call both older and n','ewer versions of fpmake)'#013#010+
  '        if SearchPathSet and (Defaults.LocalUnitDir<>OptionArg(I)) the'+
  'n'#013#010+
  '          Log(vlWarning,SWarnCombinedPathAndUDir);'#013#010+
  '        Defaults.LocalUnitDir:=OptionArg(I)'#013#010+
  '      end'#013#010+
  '    else if CheckOption(I,'#039'UG'#039','#039'g','lobalunitdir'#039') then'+
  #013#010+
  '      begin'#013#010+
  '        UnitDirSet:=true;'#013#010+
  '        // Do not warn against the combination of SearchPath and'#013#010+
  '        // localunitdir when they are the same. (This is done to be ab'+
  'le'#013#010+
  '        // to call both older and newer',' versions of fpmake)'#013#010+
  '        if SearchPathSet and (Defaults.GlobalUnitDir<>OptionArg(I)) th'+
  'en'#013#010+
  '          Log(vlWarning,SWarnCombinedPathAndUDir);'#013#010+
  '        Defaults.GlobalUnitDir:=OptionArg(I)'#013#010+
  '      end'#013#010+
  '    else if CheckOption(I,'#039'UO'#039','#039'uni','toutputdir'#039') then'+
  #013#010+
  '      Defaults.UnitOutputDirectory := OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'sp'#039','#039'searchpath'#039') then'#013#010+
  '      begin'#013#010+
  '        SearchPathSet:=true;'#013#010+
  '        if UnitDirSet then'#013#010+
  '          Log(vlWarning,SWarnCombinedPathAndUDi','r);'#013#010+
  '        Defaults.SearchPath.Add(OptionArg(I, true));'#013#010+
  '      end'#013#010+
  '    else if CheckOption(I,'#039'o'#039','#039'options'#039', true) then'#013+
  #010+
  '      begin'#013#010+
  '        OptString := OptionArg(I, true);'#013#010+
  '        while OptString <> '#039#039' do'#013#010+
  '          Defaults.AddOption','(SplitSpaces(OptString));'#013#010+
  '      end'#013#010+
  '    else if CheckOption(I,'#039'r'#039','#039'compiler'#039') then'#013#010+
  '      Defaults.Compiler:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'f'#039','#039'config'#039') then'#013#010+
  '      DefaultsFileName:=OptionArg(I)'#013#010+
  '    else if CheckOption(I,'#039'ie'#039',',#039'installexamples'#039') then'+
  #013#010+
  '      Defaults.InstallExamples:=true'#013#010+
  '    else if CheckOption(I,'#039'sap'#039','#039'skipallprograms'#039') the'+
  'n'#013#010+
  '      Defaults.SkipAllPrograms:=true'#013#010+
  '    else if CheckOption(I,'#039'scp'#039','#039'skipcrossprograms'#039') t'+
  'hen'#013#010+
  '      Defaults.SkipCros','sPrograms:=true'#013#010+
  '    else if CheckOption(I,'#039'bu'#039','#039'buildunit'#039') then'#013#010+
  '      Defaults.BuildMode:=bmBuildUnit'#013#010+
  '    else if CheckOption(I,'#039'io'#039','#039'ignoreinvalidoption'#039', '+
  'true) then'#013#010+
  '      Defaults.IgnoreInvalidOptions:=true'#013#010+
  '    else if CheckCommand(','I,'#039'ns'#039','#039'namespaces'#039') then'#013+
  #010+
  '      Defaults.Namespaces:=True'#013#010+
  '    else if CheckOption(I,'#039'fsp'#039','#039'fpunitsrcpath'#039') then'#013+
  #010+
  '      Defaults.FPUnitSourcePath:=OptionArg(I)'#013#010+
  '    else if assigned(CustomFpmakeCommandlineOptions) and CheckCustomOp'+
  'tion(I,C','ustOptName) then'#013#010+
  '      begin'#013#010+
  '      if not assigned(CustomFpMakeCommandlineValues) then'#013#010+
  '        CustomFpMakeCommandlineValues := TUnsortedCompilerOptionsStrin'+
  'gList.Create;'#013#010+
  '      CustomFpMakeCommandlineValues.Values[CustOptName]:=OptionAr','g(I'+
  ', true)'#013#010+
  '      end'#013#010+
  '    else if (not CheckBuildOptionSetValue(I)) and (not CheckPackageVar'+
  'iantOptionSetValue(I))'#013#010+
  '      and (not Defaults.IgnoreInvalidOptions) then'#013#010+
  '      begin'#013#010+
  '      Usage(SErrInValidArgument,[I,ParamStr(I)]);'#013#010+
  '      e','nd;'#013#010+
  '    end;'#013#010+
  '  If DefaultsFileName<>'#039#039' then'#013#010+
  '    Defaults.LocalInit(DefaultsFileName);'#013#010+
  '  Defaults.CompilerDefaults;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Usage(const FMT: String; const Args: array '+
  'of const);'#013#010+
  #013#010+
  '  Procedure LogCmd(const L','C,Msg : String);'#013#010+
  '  begin'#013#010+
  '    Log(vlInfo,Format('#039'  %-12s    %s'#039',[LC,MSG]));'#013#010+
  '  end;'#013#010+
  #013#010+
  '  Procedure LogOption(const C,LC,Msg : String);'#013#010+
  '  begin'#013#010+
  '    Log(vlInfo,Format('#039'  -%s    --%-16s %s'#039',[C,LC,MSG]));'#013#010+
  '  end;'#013#010+
  #013#010+
  '  Procedure LogArgOption(','const C,LC,Msg : String);'#013#010+
  '  begin'#013#010+
  '    if trim(c)='#039#039' then'#013#010+
  '      Log(vlInfo,Format('#039'       --%-20s %s'#039',[LC+'#039'='#039'+SV'+
  'alue,MSG]))'#013#010+
  '    else'#013#010+
  '      Log(vlInfo,Format('#039'  -%s    --%-20s %s'#039',[C,LC+'#039'='#039+
  '+SValue,MSG]));'#013#010+
  '  end;'#013#010+
  #013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  'b','egin'#013#010+
  '  // Force the Usage to be displayed'#013#010+
  '  Include(FLogLevels,vlInfo);'#013#010+
  '  If (FMT<>'#039#039') then'#013#010+
  '    Log(vlInfo,Format(Fmt,Args));'#013#010+
  '  Log(vlInfo,Format(SHelpUsage,[Paramstr(0)]));'#013#010+
  '  Log(vlInfo,SHelpCommand);'#013#010+
  '  LogCmd('#039'compile'#039',SHelpCompile',');'#013#010+
  '  LogCmd('#039'build'#039',SHelpBuild);'#013#010+
  '  LogCmd('#039'install'#039',SHelpInstall);'#013#010+
  '  LogCmd('#039'buildinstall'#039',SHelpBuildInstall);'#013#010+
  '  LogCmd('#039'uninstall'#039',SHelpUnInstall);'#013#010+
  '  LogCmd('#039'clean'#039',SHelpClean);'#013#010+
  '  LogCmd('#039'distclean'#039',SHelpDistclean);'#013#010+
  '  LogCmd('#039'archiv','e'#039',SHelpArchive);'#013#010+
  '  LogCmd('#039'manifest'#039',SHelpManifest);'#013#010+
  '  LogCmd('#039'zipinstall'#039',SHelpZipInstall);'#013#010+
  '  LogCmd('#039'pkglist'#039',SHelpPkgList);'#013#010+
  '  Log(vlInfo,SHelpCmdOptions);'#013#010+
  '  LogOption('#039'h'#039','#039'help'#039',SHelpHelp);'#013#010+
  '  LogOption('#039'lc'#039','#039'list-commands'#039',SHelpLi','st);'#013#010+
  '  LogOption('#039'n'#039','#039'nofpccfg'#039',SHelpNoFPCCfg);'#013#010+
  '  LogOption('#039'v'#039','#039'verbose'#039',SHelpVerbose);'#013#010+
  '  LogOption('#039'd'#039','#039'debug'#039',SHelpDebug);'#013#010+
  '  LogOption('#039'I'#039','#039'interactive'#039',SHelpInteractive);'#013#010+
  '{$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  LogOption('#039'e'#039', '#039'useenv'#039', sHelpU','seEnvironment);'#013+
  #010+
  '{$endif}'#013#010+
  '  LogOption('#039'ie'#039','#039'installexamples'#039',SHelpInstExamples);'+
  #013#010+
  '  LogOption('#039'bu'#039','#039'buildunit'#039',SHelpUseBuildUnit);'#013#010+
  '  LogOption('#039'sap'#039','#039'skipallprograms'#039',SHelpSkipAllProgs)'+
  ';'#013#010+
  '  LogOption('#039'scp'#039','#039'skipcrossprograms'#039',SHelpSkipCro','ss'+
  'Progs);'#013#010+
  '  LogOption('#039'io'#039','#039'ignoreinvalidoption'#039',SHelpIgnoreInvO'+
  'pt);'#013#010+
  '  LogArgOption('#039'C'#039','#039'cpu'#039',SHelpCPU);'#013#010+
  '  LogArgOption('#039'O'#039','#039'os'#039',SHelpOS);'#013#010+
  '  LogArgOption('#039's'#039','#039'subtarget'#039',SHelpSubTarget);'#013#010+
  '  LogArgOption('#039't'#039','#039'target'#039',SHelpTarget);'#013#010+
  '  Log','ArgOption('#039'P'#039','#039'prefix'#039',SHelpPrefix);'#013#010+
  '  LogArgOption('#039'B'#039','#039'baseinstalldir'#039',SHelpBaseInstalldi'+
  'r);'#013#010+
  '  LogArgOption('#039'BI'#039','#039'bininstalldir'#039',SHelpBaseInstalldi'+
  'r);'#013#010+
  '  LogArgOption('#039'LI'#039','#039'libinstalldir'#039',SHelpBaseInstalldi'+
  'r);'#013#010+
  '  LogArgOption('#039'UL'#039','#039'loca','lunitdir'#039',SHelpLocalUnitdir'+
  ');'#013#010+
  '  LogArgOption('#039'UO'#039','#039'unitoutputdir'#039',SHelpOutpuUnitDir)'+
  ';'#013#010+
  '  LogArgOption('#039'UG'#039','#039'globalunitdir'#039',SHelpGlobalUnitdir'+
  ');'#013#010+
  '  LogArgOption('#039'sp'#039','#039'searchpath'#039',SHelpSearchPath);'#013+
  #010+
  '  LogArgOption('#039'U'#039','#039'unitinstalldir'#039',SHelpU','nitInstall'+
  'Dir);'#013#010+
  '  LogArgOption('#039'r'#039','#039'compiler'#039',SHelpCompiler);'#013#010+
  '  LogArgOption('#039'f'#039','#039'config'#039',SHelpConfig);'#013#010+
  '  LogArgOption('#039'o'#039','#039'options'#039',SHelpOptions);'#013#010+
  '  LogArgOption('#039'fsp'#039', '#039'fpunitsrcpath'#039', sHelpFPUnitSrcP'+
  'ath);'#013#010+
  '  LogArgOption('#039'zp'#039', '#039'zippr','efix'#039', sHelpZipPrefix);'#013+
  #010+
  '{$ifndef NO_THREADING}'#013#010+
  '  LogArgOption('#039'T'#039', '#039'threads'#039', sHelpThreads);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  if assigned(CustomFpmakeCommandlineOptions) then for i  := 0 to Cust'+
  'omFpmakeCommandlineOptions.Count-1 do'#013#010+
  '    LogArgOp','tion('#039' '#039',CustomFpmakeCommandlineOptions.Names[i]'+
  ',CustomFpmakeCommandlineOptions.ValueFromIndex[i]);'#013#010+
  '  Log(vlInfo, sHelpPackageVariant1);'#013#010+
  '  Log(vlInfo, sHelpPackageVariant2);'#013#010+
  '  Log(vlInfo, sHelpPackageVariant3);'#013#010+
  '  Log(vlInfo, sHelpPackag','eVariant4);'#013#010+
  '  Log(vlInfo, sHelpPackageVariant5);'#013#010+
  '  Log(vlInfo, sHelpPackageVariant6);'#013#010+
  '  Log(vlInfo,'#039#039');'#013#010+
  #013#010+
  '  If (FMT<>'#039#039') then'#013#010+
  '    halt(1)'#013#010+
  '  else'#013#010+
  '    halt(0);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.Info;'#013#010+
  'Var Cpu : TCpu;'#013#010+
  '    OS  : TOS;'#013,#010+
  #013#010+
  'begin'#013#010+
  '  Write('#039'CPU_TARGET='#039');'#013#010+
  '  for cpu:=succ(low(cpu)) to high(tcpu) do // skip NONE'#013#010+
  '    begin'#013#010+
  '       write(cputostring(cpu));'#013#010+
  '       if cpu<>high(tcpu) then'#013#010+
  '       write('#039','#039');'#013#010+
  '    end;'#013#010+
  '  writeln;'#013#010+
  '  Write('#039'OS_TARGET='#039');'#013#010+
  '  for ','OS:=succ(low(TOS)) to high(tOS) do // skip NONE'#013#010+
  '    begin'#013#010+
  '       write(OStostring(os));'#013#010+
  '       if os<>high(tos) then'#013#010+
  '       write('#039','#039');'#013#010+
  '    end;'#013#010+
  '  writeln;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.Compile(Force: Boolean);'#013#010+
  'begin'#013#010+
  '  FNotify','EventCollection.CallEvents(neaBeforeCompile, Self);'#013#010+
  '  FBuildEngine.ForceCompile:=Force;'#013#010+
  '  FBuildEngine.Compile(Packages);'#013#010+
  '  FNotifyEventCollection.CallEvents(neaAfterCompile, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Clean(AllTargets:',' boolean);'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeClean, Self);'#013#010+
  '  BuildEngine.Clean(Packages, AllTargets);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterClean, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Install(ForceBuild : Bo','olean);'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeInstall, self);'#013#010+
  '  BuildEngine.ForceCompile := ForceBuild;'#013#010+
  '  BuildEngine.Install(Packages);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterInstall, self);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomI','nstaller.ZipInstall;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeInstall, self);'#013#010+
  '  BuildEngine.ZipInstall(Packages);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterInstall, self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.UnInstall;'#013#010+
  'begi','n'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeUnInstall, self);'#013#010+
  '  BuildEngine.UnInstall(Packages);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterUnInstall, self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Archive;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollectio','n.CallEvents(neaBeforeArchive, self);'#013#010+
  '  BuildEngine.Archive(Packages);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterArchive, self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.Manifest;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeManifest',', self);'#013#010+
  '  BuildEngine.Manifest(Packages, nil);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterManifest, self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCustomInstaller.PkgList;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforePkgList, self);'#013#010+
  '  BuildEngine.','PkgList(Packages);'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterPkgList, self);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.AddAutoPackageVariantsToPackage(APackage: T'+
  'Package);'#013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  '  PV: TPackageVariants;'#013#010+
  'begin'#013#010+
  '  for i := 0 to FPa','ckageVariants.Count-1 do'#013#010+
  '    begin'#013#010+
  '    PV := TObject(FPackageVariants.Items[i]) as TPackageVariants;'#013#010+
  '    if PV.AutoAddToPackage then'#013#010+
  '      APackage.AddPackageVariant(PV);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCustomInstaller.CheckPackages;'#013#010+
  'beg','in'#013#010+
  '  If (Packages.Count=0) then'#013#010+
  '    Error(SErrNoPackagesDefined);'#013#010+
  '  // Check for other obvious errors ?'#013#010+
  'end;'#013#010+
  #013#010+
  'Procedure TCustomInstaller.CheckNameSpaces;'#013#010+
  #013#010+
  'Var'#013#010+
  '  P : TPackage;'#013#010+
  #013#010+
  'begin'#013#010+
  '  for P in Packages do'#013#010+
  '    if P.NamespaceMap<','>'#039#039' then'#013#010+
  '      begin'#013#010+
  '      BuildEngine.ResolveFileNames(P,Defaults.CPU,Defaults.OS,True,Tru'+
  'e);'#013#010+
  '      P.ApplyNameSpaces(BuildEngine,Defaults.CompileTarget);'#013#010+
  '      end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCustomInstaller.Run: Boolean;'#013#010+
  #013#010+
  #013#010+
  'begin'#013#010+
  '  Result',':=True;'#013#010+
  '  try'#013#010+
  '    CheckPackages;'#013#010+
  '    CreateBuildEngine;'#013#010+
  '    if Defaults.Namespaces then'#013#010+
  '      CheckNameSpaces;'#013#010+
  '    Case RunMode of'#013#010+
  '      rmCompile : Compile(False);'#013#010+
  '      rmBuild   : Compile(True);'#013#010+
  '      rmInstall : Install(False);',#013#010+
  '      rmBuildInstall: Install(True);'#013#010+
  '      rmZipInstall : ZipInstall;'#013#010+
  '      rmArchive : Archive;'#013#010+
  '      rmClean    : Clean(False);'#013#010+
  '      rmDistClean: Clean(True);'#013#010+
  '      rmManifest : Manifest;'#013#010+
  '      rmPkgList : PkgList;'#013#010+
  '      rmUnIns','tall : UnInstall;'#013#010+
  '      rmInfo      : Info;'#013#010+
  '    end;'#013#010+
  '  except'#013#010+
  '    On E : Exception do'#013#010+
  '      begin'#013#010+
  '      Log(vlError,SErrInstaller);'#013#010+
  '      Log(vlError,E.Message);'#013#010+
  '      DumpExceptionBacktrace(stderr);'#013#010+
  '      Result:=False;'#013#010+
  '      end',';'#013#010+
  '  end;'#013#010+
  '  // Force returning an exitcode to the shell'#013#010+
  '  if not Result then'#013#010+
  '    ExitCode:=1;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                TFPCInstaller'#013#010+
  '****','****************************************************************'+
  '********}'#013#010+
  #013#010+
  'constructor TFPCInstaller.Create(AOwner: TComponent);'#013#010+
  'begin'#013#010+
  '  if assigned(Defaults) then'#013#010+
  '    Error(SErrAlreadyInitialized);'#013#010+
  '  Defaults:=TFPCDefaults.Create;'#013#010+
  ' ',' inherited Create(AOwner);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                 TBasicInstaller'#013#010+
  '**********************************************************************'+
  '***','***}'#013#010+
  #013#010+
  'constructor TBasicInstaller.Create(AOwner: TComponent);'#013#010+
  'begin'#013#010+
  '  if assigned(Defaults) then'#013#010+
  '    Error(SErrAlreadyInitialized);'#013#010+
  '  Defaults:=TBasicDefaults.Create;'#013#010+
  '  inherited Create(AOwner);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{**************************','*****************************************'+
  '*********'#013#010+
  '                                 TBuildEngine'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'constructor TBuildEngine.Create(AOwner: TComponent);'#013#010+
  'begin'#013,#010+
  '  inherited Create(AOwner);'#013#010+
  '  // Maybe this should be the current directory ?'#013#010+
  '  // Or have it as a command-line option.'#013#010+
  '  // Would allow to put all '#039'installers'#039' in one dir and call t'+
  'hem'#013#010+
  '  // With --start-dir=/path/to/sources.'#013#010+
  '  FStart','Dir:=includeTrailingPathDelimiter(GetCurrentDir);'#013#010+
  '  FExternalPackages:=TPackages.Create(TPackage);'#013#010+
  '  FIndentCount:=0;'#013#010+
  '  FNotifyEventCollection := TNotifyEventCollection.create([neaAfterCom'+
  'pile, neaBeforeCompile, neaAfterInstall, neaBefor','eInstall,'#013#010+
  '                                                           neaAfterCle'+
  'an, neaBeforeClean, neaAfterArchive, neaBeforeArchive,'#013#010+
  '                                                           neaAfterMan'+
  'ifest, neaBeforeManifest, neaAfte','rPkgList, neaBeforePkgList,'#013#010+
  '                                                           neaBeforeUn'+
  'Install, neaAfterUnInstall]);'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  InitCriticalSection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'dest','ructor TBuildEngine.Destroy;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FExternalPackages);'#013#010+
  '  FreeAndNil(FNotifyEventCollection);'#013#010+
  '  If FIndentCount<>0 then'#013#010+
  '    Log(vlDebug,Format('#039'Log level at exit is %d'#039',[FIndentCount'+
  ']));'#013#010+
  #013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  DoneCri','ticalsection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  #013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.AddFileToArchive(const APackage: TPackage; cons'+
  't ASourceFileName, ADestFileName: String);'#013#010+
  #013#010+
  '  function GetArchiveName: st','ring;'#013#010+
  '  begin'#013#010+
  '    result := Defaults.ZipPrefix;'#013#010+
  '    if Defaults.BuildOS in AllLimit83fsOses then'#013#010+
  '      result := result + APackage.ShortName'#013#010+
  '    else'#013#010+
  '      result := result + APackage.Name;'#013#010+
  '    result := result + MakeZipSuffix(Defaul','ts.CPU, Defaults.OS);'#013+
  #010+
  '  end;'#013#010+
  #013#010+
  '{$ifdef UNIX}'#013#010+
  'var'#013#010+
  '  FileStat: stat;'#013#010+
  '{$endif UNIX}'#013#010+
  'begin'#013#010+
  '{$ifdef CREATE_TAR_FILE}'#013#010+
  '  {$ifdef HAS_TAR_SUPPORT}'#013#010+
  '  if not assigned(FTarWriter) then'#013#010+
  '    begin'#013#010+
  '    {$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '      FGZFileSt','ream := TGZFileStream.create(GetArchiveName + Archive'+
  'Extension, gzopenwrite);'#013#010+
  '      try'#013#010+
  '        FTarWriter := TTarWriter.Create(FGZFileStream);'#013#010+
  '      except'#013#010+
  '        FGZFileStream.Free;'#013#010+
  '      end;'#013#010+
  '    {$else}'#013#010+
  '    FTarWriter := TTarWri','ter.Create(GetArchiveName + ArchiveExtensio'+
  'n);'#013#010+
  '    {$endif HAS_UNIT_ZIPPER}'#013#010+
  '    FTarWriter.Permissions := [tpReadByOwner, tpWriteByOwner, tpReadBy'+
  'Group, tpReadByOther];'#013#010+
  '    FTarWriter.UserName := '#039'root'#039';'#013#010+
  '    FTarWriter.GroupName := '#039'roo','t'#039';'#013#010+
  '    end;'#013#010+
  '{$ifdef unix}'#013#010+
  '  filestat:=Default(stat);'#013#010+
  '  if (FpStat(ASourceFileName, FileStat) = 0) and (FileStat.st_mode and'+
  ' S_IXUSR = S_IXUSR) then'#013#010+
  '    begin'#013#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions + [tpExecuteByGro'+
  'up];'#013,#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions + [tpExecuteByOwn'+
  'er];'#013#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions + [tpExecuteByOth'+
  'er];'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions - [tpE','xecuteByG'+
  'roup];'#013#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions - [tpExecuteByOwn'+
  'er];'#013#010+
  '    FTarWriter.Permissions := FTarWriter.Permissions - [tpExecuteByOth'+
  'er];'#013#010+
  '    end;'#013#010+
  '{$endif unix}'#013#010+
  '  FTarWriter.AddFile(ASourceFileName, ADestFil','eName);'#013#010+
  '  {$endif HAS_TAR_SUPPORT}'#013#010+
  '{$else CREATE_TAR_FILE}'#013#010+
  '  {$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '  if not assigned(FZipper) then'#013#010+
  '    begin'#013#010+
  '      FZipper := TZipper.Create;'#013#010+
  '      FZipper.FileName := GetArchiveName + ArchiveExtension;'#013#010+
  '    end;'#013#010,
  #013#010+
  '  FZipper.Entries.AddFileEntry(ASourceFileName, ADestFileName);'#013#010+
  '  {$endif HAS_UNIT_ZIPPER}'#013#010+
  '{$ENDIF CREATE_TAR_FILE}'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.FinishArchive(Sender: TObject);'#013#010+
  'begin'#013#010+
  '  {$ifdef HAS_TAR_SUPPORT}'#013#010+
  '  if assigned(FTarWr','iter) then'#013#010+
  '    begin'#013#010+
  '      FreeAndNil(FTarWriter);'#013#010+
  '      {$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '      FGZFileStream.Free;'#013#010+
  '      {$endif HAS_UNIT_ZIPPER}'#013#010+
  '    end;'#013#010+
  '  {$endif HAS_TAR_SUPPORT}'#013#010+
  '  {$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '  if assigned(FZipper) then'#013#010,
  '    begin'#013#010+
  '      try'#013#010+
  '        FZipper.ZipAllFiles;'#013#010+
  '        FZipper.Clear;'#013#010+
  '      finally'#013#010+
  '        FreeAndNil(FZipper);'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  {$endif HAS_UNIT_ZIPPER}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Error(const Msg: String);'#013#010+
  'begin'#013#010+
  '  ','Raise EInstallerError.Create(Msg);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Error(const Fmt: String; const Args: array of c'+
  'onst);'#013#010+
  'begin'#013#010+
  '  Raise EInstallerError.CreateFmt(Fmt,Args);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.GetExecuteCommandOutput(const C','md : String; co'+
  'nst Args : TStrings; Env: TStrings = nil; IgnoreError : Boolean = Fals'+
  'e) : string;'#013#010+
  'Var'#013#010+
  '  E : Integer;'#013#010+
  '  cmdLine: string;'#013#010+
  '  ConsoleOutput: TMemoryStream;'#013#010+
  '  s: string;'#013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  cmdLine:='#039#039';'#013#010+
  '  if Args.Count','<>0 then'#013#010+
  '    for s in Args do'#013#010+
  '      cmdLine := cmdline + '#039' '#039' + S;'#013#010+
  '  Log(vlInfo,SInfoExecutingCommand,[Cmd,CmdLine]);'#013#010+
  '  if ListMode then'#013#010+
  '    Log(vlCommand,'#039'%s %s'#039',[Cmd,CmdLine])'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      // We should check cmd for space','s, and move all after first sp'+
  'ace to args.'#013#010+
  '      ConsoleOutput := TMemoryStream.Create;'#013#010+
  '      try'#013#010+
  '        if Interactive then'#013#010+
  '          Log(vlInfo,'#039'Starting "%s" "%s" interactively'#039',[Cmd,C'+
  'mdLine]);'#013#010+
  '        {$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  ','      E:=ExecuteFPC(Verbose, Interactive, cmd, args, env, ConsoleO'+
  'utput);'#013#010+
  '        {$else}'#013#010+
  '        E:=ExecuteProcess(cmd,args.ToStringArray);'#013#010+
  '        {$endif}'#013#010+
  '        If (E<>0) and (not IgnoreError) then'#013#010+
  '          begin'#013#010+
  '            s :','= ParsecompilerOutput(ConsoleOutput,Verbose);'#013#010+
  '            cmdLine:=cmd+'#039' '#039'+cmdLine;'#013#010+
  '            Error(SErrExternalCommandFailed,[cmdLine,E,s]);'#013#010+
  '          end;'#013#010+
  '      finally'#013#010+
  '        ConsoleOutput.Seek(0, soBeginning);'#013#010+
  '        SetLength','(Result,ConsoleOutput.Size);'#013#010+
  '        ConsoleOutput.Read(Result[1],ConsoleOutput.Size);'#013#010+
  '        ConsoleOutput.Free;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.ExecuteCommand(const Cmd : String; const Args :'+
  ' TStrings;  Env: TStri','ngs = nil; IgnoreError : Boolean = False);'#013+
  #010+
  'begin'#013#010+
  '  GetExecuteCommandOutput(Cmd,Args,Env,IgnoreError);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.SysDirectoryExists(const ADir: string): Boolean;'+
  #013#010+
  'begin'#013#010+
  '  result:={$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF','}SysUtils.DirectoryE'+
  'xists(ADir);'#013#010+
  '  if result then'#013#010+
  '    Log(vlDebug,SDbgDirectoryExists,[ADir,SDbgFound])'#013#010+
  '  else'#013#010+
  '    Log(vlDebug,SDbgDirectoryExists,[ADir,SDbgNotFound]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.SysFileExists(const AFileName: str','ing): Boolea'+
  'n;'#013#010+
  'begin'#013#010+
  '  // Writeln('#039'Testing : '#039',aFileName);'#013#010+
  '  result:={$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.FileExists(A'+
  'FileName);'#013#010+
  '  if result then'#013#010+
  '    Log(vlDebug,SDbgFileExists,[AFileName,SDbgFound])'#013#010+
  '  else'#013#010+
  '    Log(vlDebug',',SDbgFileExists,[AFileName,SDbgNotFound]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.SysCopyFile(const Src, Dest: String);'#013#010+
  'Var'#013#010+
  '  D,S : String;'#013#010+
  '  Fin,FOut : TFileStream;'#013#010+
  '  Count : Int64;'#013#010+
  '  A : Integer;'#013#010+
  '{$ifdef UNIX}'#013#010+
  '  FileStat: stat;'#013#010+
  '{$endif',' UNIX}'#013#010+
  'begin'#013#010+
  '  { First delete file on Darwin OS to avoid codesign issues }'#013#010+
  '  if (Defaults.SourceOS=Darwin) then'#013#010+
  '    begin'#013#010+
  '      D:=IncludeTrailingPathDelimiter(Dest);'#013#010+
  '      If DirectoryExists(D) then'#013#010+
  '        begin'#013#010+
  '          D:=D+Ext','ractFileName(Src);'#013#010+
  '          if FileExists(D) then'#013#010+
  '            SysDeleteFile(D);'#013#010+
  '       end'#013#010+
  '     else if FileExists(Dest) then'#013#010+
  '       SysDeleteFile(Dest);'#013#010+
  '    end;'#013#010+
  '  Log(vlInfo,SInfoCopyingFile,[Src,Dest]);'#013#010+
  '  FIn:=TFileStream.Create','(Src,fmopenRead or fmShareDenyNone);'#013#010+
  '  Try'#013#010+
  '    D:=IncludeTrailingPathDelimiter(Dest);'#013#010+
  '    If DirectoryExists(D) then'#013#010+
  '      S:=D+ExtractFileName(Src)'#013#010+
  '    else'#013#010+
  '      S:=Dest;'#013#010+
  '    FOut:=TFileStream.Create(S,fmCreate or fmShareDenyNone);',#013#010+
  '    Try'#013#010+
  '      Count:=Fout.CopyFrom(FIn,0);'#013#010+
  '      If (Count<>Fin.Size) then'#013#010+
  '        Error(SErrCopyingFile,[Src,S]);'#013#010+
  '    Finally'#013#010+
  '      FreeAndNil(Fout);'#013#010+
  '    end;'#013#010+
  '    A:=FileGetDate(FIn.Handle);'#013#010+
  '    If (A=-1) then'#013#010+
  '      log(vlWarnin','g,SWarnFailedToGetTime,[Src])'#013#010+
  '    else'#013#010+
  '      if FileSetDate(S,A)<>0 then'#013#010+
  '        Log(vlWarning,SWarnFailedToSetTime,[S]);'#013#010+
  '{$ifdef UNIX}'#013#010+
  '    // Copy the file-access rights on Unix, especially the executable-'+
  'bit'#013#010+
  '    filestat:=Default(st','at);'#013#010+
  '    if FpStat(Src,FileStat) <> 0 then'#013#010+
  '      Log(vlWarning,SWarnCanNotGetAccessRights,[Src])'#013#010+
  '    else'#013#010+
  '      if FpChmod(s,FileStat.st_mode) <> 0 then'#013#010+
  '        Log(vlWarning,SWarnCanNotSetAccessRights,[S]);'#013#010+
  '{$endif UNIX}'#013#010+
  '  finally'#013#010,
  '    FreeAndNil(Fin);'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.SysMoveFile(const Src, Dest: String);'#013#010+
  'Var'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  If DirectoryExists(IncludeTrailingPathDelimiter(Dest)) then'#013#010+
  '    S:=IncludeTrailingPathDelimiter(Dest)+Extrac','tFileName(Src)'#013#010+
  '  else'#013#010+
  '    S:=Dest;'#013#010+
  '  If Not RenameFile(Src,S) then'#013#010+
  '    begin'#013#010+
  '      Try'#013#010+
  '        SysCopyFile(Src,S);'#013#010+
  '        SysDeleteFile(Src);'#013#010+
  '      Except'#013#010+
  '        On E : Exception Do'#013#010+
  '          Error(SErrMovingFile,[Src,S]);'#013#010+
  '    ','  end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.SysDeleteFile(const AFileName: String);'#013#010+
  'var retries : integer;'#013#010+
  '    res : boolean;'#013#010+
  'begin'#013#010+
  '  if not FileExists(AFileName) then'#013#010+
  '    Log(vldebug,SDbgFileDoesNotExist,[AFileName])'#013#010+
  '  else'#013#010+
  ' ','   begin'#013#010+
  '      retries := 2;'#013#010+
  '      res := {$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.DeleteFil'+
  'e(AFileName);'#013#010+
  '      while not res and (retries>0) do'#013#010+
  '        begin'#013#010+
  '           log(vlWarning, SWarnRetryDeleteFile, [AFileName]);'#013#010+
  '      ','     sleep(5000);'#013#010+
  '           dec(retries);'#013#010+
  '           res := {$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}SysUtils.Dele'+
  'teFile(AFileName);'#013#010+
  '        end;'#013#010+
  '     if not res then'#013#010+
  '       Error(SErrDeletingFile,[AFileName])'#013#010+
  '     else'#013#010+
  '       Log(vlI','nfo,SInfoDeletedFile,[AFileName]);'#013#010+
  '   end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.SysDeleteDirectory(const ADirectoryName: String'+
  ');'#013#010+
  'begin'#013#010+
  '  if not DirectoryExists(ADirectoryName) then'#013#010+
  '    Log(vldebug,SDbgDirectoryDoesNotExist,[ADirectoryName])',#013#010+
  '  else if not IsDirectoryEmpty(ADirectoryName) then'#013#010+
  '    Log(vldebug,SDbgDirectoryNotEmpty,[ADirectoryName])'#013#010+
  '  else If Not RemoveDir(ADirectoryName) then'#013#010+
  '    Error(SErrRemovingDirectory,[ADirectoryName])'#013#010+
  '  else'#013#010+
  '    Log(vlInfo,SInfoRem','ovedDirectory,[ADirectoryName]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.SysDeleteTree(const ADirectoryName: String);'#013+
  #010+
  #013#010+
  '  function IntRemoveTree(const ADirectoryName: String) : boolean;'#013#010+
  '{$ifdef MSWINDOWS}'#013#010+
  '  { pulling in shellapi with all it de','pendent units and packages mak'+
  'es things too'#013#010+
  '    complicated so just add the constants here }'#013#010+
  '  const'#013#010+
  '    FO_DELETE                = $0003;'#013#010+
  '    FOF_SILENT               = $0004;'#013#010+
  '    FOF_NOCONFIRMATION       = $0010;'#013#010+
  '{$endif MSWINDOWS}'#013,#010+
  '  var'#013#010+
  '    retries: integer;'#013#010+
  '{$ifdef MSWINDOWS}'#013#010+
  '    SHFileOpStruct: TSHFileOpStruct;'#013#010+
  '    DirBuf: array[0..MAX_PATH+1] of TCHAR;'#013#010+
  '{$else MSWINDOWS}'#013#010+
  '    searchRec: TSearchRec;'#013#010+
  '    SearchResult: longint;'#013#010+
  '    s: string;'#013#010+
  '{$endif MSWINDOW','S}'#013#010+
  #013#010+
  '  begin'#013#010+
  '    result := true;'#013#010+
  '{$ifdef MSWINDOWS}'#013#010+
  '    retries:=2;'#013#010+
  '    try'#013#010+
  '      FillChar(SHFileOpStruct, Sizeof(SHFileOpStruct), 0);'#013#010+
  '      FillChar(DirBuf, Sizeof(DirBuf), 0);'#013#010+
  '      StrPCopy(DirBuf, ADirectoryName);'#013#010+
  '      with SH','FileOpStruct do'#013#010+
  '      begin'#013#010+
  '        pFrom := @DirBuf;'#013#010+
  '        wFunc := FO_DELETE;'#013#010+
  '        fFlags := FOF_NOCONFIRMATION or FOF_SILENT;'#013#010+
  '      end;'#013#010+
  '      Result := SHFileOperation(SHFileOpStruct) = 0;'#013#010+
  '    except'#013#010+
  '      Result := False;'#013,#010+
  '    end;'#013#010+
  '    while not result and (retries>0) do'#013#010+
  '      begin'#013#010+
  '        log(vlWarning, SWarnRetryRemDirectory, [ADirectoryName]);'#013#010+
  '        sleep(5000);'#013#010+
  '        dec(retries);'#013#010+
  '        result := SHFileOperation(SHFileOpStruct) = 0;;'#013#010+
  '      ','end;'#013#010+
  #013#010+
  '{$else MSWINDOWS}'#013#010+
  '    SearchResult := FindFirst(IncludeTrailingPathDelimiter(ADirectoryN'+
  'ame)+AllFilesMask, faAnyFile+faSymLink, searchRec);'#013#010+
  '    try'#013#010+
  '      while SearchResult=0 do'#013#010+
  '        begin'#013#010+
  '          if (searchRec.Name<>'#039'.'#039') ','and (searchRec.Name<>'#039+
  '..'#039') then'#013#010+
  '             begin'#013#010+
  '               s := IncludeTrailingPathDelimiter(ADirectoryName)+searc'+
  'hRec.Name;'#013#010+
  '               if (searchRec.Attr and faDirectory)=faDirectory then'#013+
  #010+
  '                 begin'#013#010+
  '            ','       if not IntRemoveTree(s) then'#013#010+
  '                     result := false;'#013#010+
  '                 end'#013#010+
  '               else if not DeleteFile(s) then'#013#010+
  '                 result := False'#013#010+
  '               else'#013#010+
  '                 log(vldebug, SDbgDelete','dFile, [s]);'#013#010+
  '             end;'#013#010+
  '          SearchResult := FindNext(searchRec);'#013#010+
  '        end;'#013#010+
  '    finally'#013#010+
  '      FindClose(searchRec);'#013#010+
  '    end;'#013#010+
  #013#010+
  '    // There were reports of RemoveDir failing due to locking-problems'+
  '. To solve'#013#010+
  '    // th','ese the RemoveDir is tried three times, with a delay of 5 s'+
  'econds. See'#013#010+
  '    // bug 21868'#013#010+
  '    retries := 2;'#013#010+
  '    result := RemoveDir(ADirectoryName);'#013#010+
  '    while not result and (retries>0) do'#013#010+
  '      begin'#013#010+
  '        log(vlWarning, SWarnRetryRe','mDirectory, [ADirectoryName]);'#013+
  #010+
  '        sleep(5000);'#013#010+
  '        dec(retries);'#013#010+
  '        result := RemoveDir(ADirectoryName);'#013#010+
  '      end;'#013#010+
  #013#010+
  '{$endif WINDOWS}'#013#010+
  #013#010+
  '    if result then'#013#010+
  '      log(vldebug, SDbgRemovedDirectory, [ADirectoryName]);'#013#010+
  '  ','end;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if not DirectoryExists(ADirectoryName) then'#013#010+
  '    Log(vldebug,SDbgDirectoryDoesNotExist,[ADirectoryName])'#013#010+
  '  else If Not IntRemoveTree(ADirectoryName) then'#013#010+
  '    Error(SErrRemovingDirectory,[ADirectoryName])'#013#010+
  '  else'#013#010+
  '    Log(','vlInfo,SInfoRemovedDirectory,[ADirectoryName]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.SysArchiveFiles(List: TStrings; const AFileName'+
  ': String);'#013#010+
  'begin'#013#010+
  '  If Not (Assigned(OnArchivefiles) or Assigned(ArchiveFilesProc)) then'+
  #013#010+
  '    Raise EInstaller','Error.Create(SErrNoArchiveSupport);'#013#010+
  '  If Assigned(ArchiveFilesProc) then'#013#010+
  '    ArchiveFilesProc(AFileName,List)'#013#010+
  '  else'#013#010+
  '    OnArchiveFiles(AFileName,List);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.LogIndent;'#013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  Ente','rCriticalSection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  Inc(FIndentCount);'#013#010+
  '  if not (vlDebug in Installer.FLogLevels) then'#013#010+
  '    GLogPrefix:=GLogPrefix+'#039'  '#039#013#010+
  '  else'#013#010+
  '    GLogPrefix:=IntToStr(FIndentCount)+'#039'> '#039';'#013#010+
  '{$ifndef NO_THR','EADING}'#013#010+
  '  LeaveCriticalSection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.LogUnIndent;'#013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  EnterCriticalSection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  Dec(F','IndentCount);'#013#010+
  '  if not (vlDebug in Installer.FLogLevels) then'#013#010+
  '    Delete(GLogPrefix,1,2)'#013#010+
  '  else'#013#010+
  '    GLogPrefix:=IntToStr(FIndentCount)+'#039'> '#039';'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  LeaveCriticalSection(FGeneralCriticalSection);'#013#010+
  '{$endif NO_THREADING','}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Log(Level: TVerboseLevel; Msg: String);'#013#010+
  'begin'#013#010+
  '  If Assigned(FOnLog) then'#013#010+
  '    begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '      EnterCriticalSection(FGeneralCriticalSection);'#013#010+
  '      try'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '     ',' if (Level in [vlInfo,vlDebug])'#013#010+
  '         or (ListMode and (level=vlCommand)) then'#013#010+
  '        FOnLog(Level,GLogPrefix+Msg)'#013#010+
  '      else'#013#010+
  '        FOnLog(Level,Msg);'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '      finally'#013#010+
  '        LeaveCriticalSection(FGeneralCr','iticalSection);'#013#010+
  '      end;'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Log(Level: TVerboseLevel; Fmt: String;const Arg'+
  's: array of const);'#013#010+
  'begin'#013#010+
  '  Log(Level,Format(Fmt,Args));'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Enter','Dir(ADir: String);'#013#010+
  'Var'#013#010+
  '  D : String;'#013#010+
  'begin'#013#010+
  '  D:=FStartDir;'#013#010+
  '  D:=D+ADir;'#013#010+
  '  Log(vlDebug,SDbgEnterDir,[D]);'#013#010+
  '  If Not SetCurrentDir(D) then'#013#010+
  '    Error(SErrChangeDirFailed,[D]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.CmdCopyFiles(List: TString','s; const DestDir: S'+
  'tring;'#013#010+
  '  APackage: TPackage);'#013#010+
  #013#010+
  'Var'#013#010+
  '  Args : TStrings;'#013#010+
  '  I : Integer;'#013#010+
  '  DestFileName : String;'#013#010+
  'begin'#013#010+
  '  // When the files should be written to an archive, add them'#013#010+
  '  if assigned(FOnCopyFile) then'#013#010+
  '    begin'#013#010+
  '      ','For I:=0 to List.Count-1 do'#013#010+
  '        if List.Names[i]<>'#039#039' then'#013#010+
  '          begin'#013#010+
  '            if IsRelativePath(list.ValueFromIndex[i]) then'#013#010+
  '              DestFileName:=DestDir+list.ValueFromIndex[i]'#013#010+
  '            else'#013#010+
  '              DestFil','eName:=list.ValueFromIndex[i];'#013#010+
  '            FOnCopyFile(APackage, AddPathPrefix(APackage, List.Names[i'+
  ']), DestFileName);'#013#010+
  '          end'#013#010+
  '        else'#013#010+
  '          FOnCopyFile(APackage, AddPathPrefix(APackage, List[i]), Dest'+
  'Dir+ExtractFileName','(List[i]));'#013#010+
  '      Exit;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Copy the files to their new location on disk'#013#010+
  '  CmdCreateDir(DestDir);'#013#010+
  '  If (Defaults.Copy<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      Args:=TStringList.Create;'#013#010+
  '      try'#013#010+
  '        Args.Assign(List);'#013#010+
  '        Pre','pendFileListWithString(Args, IncludeTrailingPathDelimiter'+
  '(GPathPrefix));'#013#010+
  '        Args.Add(DestDir);'#013#010+
  '        ExecuteCommand(Defaults.Copy,Args);'#013#010+
  '      finally'#013#010+
  '        Args.Free;'#013#010+
  '      end;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    For I:=0 to List.Count-1 ','do'#013#010+
  '      if List.Names[i]<>'#039#039' then'#013#010+
  '        begin'#013#010+
  '          if IsRelativePath(list.ValueFromIndex[i]) then'#013#010+
  '            DestFileName:=DestDir+list.ValueFromIndex[i]'#013#010+
  '          else'#013#010+
  '            DestFileName:=list.ValueFromIndex[i];'#013#010+
  '     ','     CmdCreateDir(ExtractFilePath(DestFileName));'#013#010+
  '          SysCopyFile(AddPathPrefix(APackage, List.Names[i]),DestFileN'+
  'ame)'#013#010+
  '        end'#013#010+
  '      else if List[i]<>'#039#039' then'#013#010+
  '        SysCopyFile(AddPathPrefix(APackage, List[i]), DestDir);'#013#010+
  'end',';'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.CmdCreateDir(const DestDir: String);'#013#010+
  #013#010+
  'Var'#013#010+
  '  Args : TStrings;'#013#010+
  #013#010+
  'begin'#013#010+
  '  If (Defaults.MkDir<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '    Args:=TstringList.Create;'#013#010+
  '    try'#013#010+
  '      Args.Append('#039'-p'#039'); // Same effect as forcedirec','tories'#013+
  #010+
  '      Args.Append(DestDir);'#013#010+
  '      ExecuteCommand(Defaults.MkDir,Args);'#013#010+
  '    finally'#013#010+
  '      Args.Free;'#013#010+
  '    end;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    If not ForceDirectories(DestDir) then'#013#010+
  '      Error(SErrCreatingDirectory,[DestDir]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'p','rocedure TBuildEngine.CmdMoveFiles(List: TStrings; const DestDir: S'+
  'tring);'#013#010+
  'Var'#013#010+
  '  Args : TStrings;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  CmdCreateDir(DestDir);'#013#010+
  '  If (Defaults.Move<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      Args:=TStringList.Create;'#013#010+
  '      try'#013#010+
  '    ','    Args.Assign(List);'#013#010+
  '        Args.Add(DestDir);'#013#010+
  '        ExecuteCommand(Defaults.Move,Args);'#013#010+
  '      finally'#013#010+
  '        Args.Free;'#013#010+
  '      end;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    For I:=0 to List.Count-1 do'#013#010+
  '      SysMoveFile(List[i],DestDir);'#013#010+
  'end;'#013#010+
  #013#010+
  #013,#010+
  'procedure TBuildEngine.CmdDeleteFiles(List: TStrings);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  If (Defaults.Remove<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '    ExecuteCommand(Defaults.Remove,List);'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    For I:=0 to List.Count-1 do'#013#010+
  '      SysDeleteFil','e(List[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.CmdDeleteDestFiles(List: TStrings; const DestDi'+
  'r: String'#013#010+
  '  );'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  DeleteFileName : String;'#013#010+
  'begin'#013#010+
  '  // Delete files from their location on disk'#013#010+
  '  For I:=0 to List.Count-1 ','do'#013#010+
  '    begin'#013#010+
  '      if List.Names[i]<>'#039#039' then'#013#010+
  '        begin'#013#010+
  '          if IsRelativePath(list.ValueFromIndex[i]) then'#013#010+
  '            DeleteFileName:=DestDir+list.ValueFromIndex[i]'#013#010+
  '          else'#013#010+
  '            DeleteFileName:=list.ValueFromI','ndex[i];'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '        DeleteFileName:=DestDir+ExtractFileName(list[i]);'#013#010+
  '      SysDeleteFile(DeleteFileName);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.CmdArchiveFiles(List: TStrings; const ArchiveFi'+
  'le: String'#013#010+
  '  );'#013#010,
  #013#010+
  'Var'#013#010+
  '  P : Integer;'#013#010+
  '  CmdLine : Array of String;'#013#010+
  '  i : integer;'#013#010+
  '  S,Cmd : String;'#013#010+
  #013#010+
  '  Files,Args : TStrings;'#013#010+
  #013#010+
  'begin'#013#010+
  '  If (Defaults.Archive='#039#039') then'#013#010+
  '    SysArchiveFiles(List,ArchiveFile)'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      Files:=Nil;'#013#010+
  '     ',' Args:=TStringList.Create;'#013#010+
  '      try'#013#010+
  '        Files:=TStringList.Create;'#013#010+
  '        Files.Assign(List);'#013#010+
  '        PrependFileListWithString(Files,IncludeTrailingPathDelimiter(G'+
  'PathPrefix));'#013#010+
  '        CmdLine:=Defaults.Archive.Split(RTLString('#039,' '#039'),'#039'"'+
  #039','#039'"'#039');'#013#010+
  '        Cmd:=CmdLine[0];'#013#010+
  '        For I:=1 to Length(CmdLine)-1 do'#013#010+
  '          begin'#013#010+
  '          S:=CmdLine[i];'#013#010+
  '          P:=Pos('#039'$(FILESORDIRS)'#039',S);'#013#010+
  '          if (P<>0) then'#013#010+
  '            Args.AddStrings(Files)'#013#010+
  '          els','e'#013#010+
  '            Args.Append(GlobalDictionary.Substitute(S,['#039'ARCHIVE'#039+
  ',ArchiveFile]));'#013#010+
  '          end;'#013#010+
  '        ExecuteCommand(Cmd,Args);'#013#010+
  '      finally'#013#010+
  '        List.Free;'#013#010+
  '        Args.Free;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEng','ine.CmdRenameFile(const SourceName, DestName: Str'+
  'ing);'#013#010+
  #013#010+
  'var'#013#010+
  '  Args: TStrings;'#013#010+
  #013#010+
  'begin'#013#010+
  '  If (Defaults.Move<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      Args:=TstringList.Create;'#013#010+
  '      try'#013#010+
  '        Args.Add(SourceName);'#013#010+
  '        Args.Add(DestName);'#013#010+
  '   ','     ExecuteCommand(Defaults.Move,Args);'#013#010+
  '      finally'#013#010+
  '        Args.Free;'#013#010+
  '      end;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    SysMoveFile(SourceName,DestName);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.CmdRemoveDirs(List: TStrings);'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010,
  '  If (Defaults.RemoveDir<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      ExecuteCommand(Defaults.RemoveDir,List);'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    For I:=0 to List.Count-1 do'#013#010+
  '      SysDeleteDirectory(List[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.CmdRemoveTrees(List: TString','s);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  If (Defaults.RemoveTree<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      ExecuteCommand(Defaults.RemoveTree,List);'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    For I:=0 to List.Count-1 do'#013#010+
  '      SysDeleteTree(List[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine','.FileNewer(const Src, Dest: String): Boolean;'#013+
  #010+
  #013#010+
  'Var'#013#010+
  '  DS,DD : Longint;'#013#010+
  '  D1,D2 : TDateTime;'#013#010+
  #013#010+
  'begin'#013#010+
  '  DS:=FileAge(Src);'#013#010+
  '  { Return false if file not found or not accessible }'#013#010+
  '  if DS=-1 then'#013#010+
  '    begin'#013#010+
  '      Log(vlWarning,SWarnCanNo','tGetFileAge,[Src]);'#013#010+
  '      Result:=false;'#013#010+
  '      exit;'#013#010+
  '    end;'#013#010+
  '  DD:=FileAge(Dest);'#013#010+
  '  { Return true if dest file not found or not accessible }'#013#010+
  '  if DD=-1 then'#013#010+
  '    begin'#013#010+
  '      Result:=True;'#013#010+
  '      exit;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  D1:=FileDateToDa','teTime(DS);'#013#010+
  '  D2:=FileDateToDateTime(DD);'#013#010+
  '  Log(vlDebug,SDbgComparingFileTimes,[Src,DateTimeToStr(D1),Dest,DateT'+
  'imeToStr(D2)]);'#013#010+
  '  Result:=D1>D2;'#013#010+
  '  If Result then'#013#010+
  '    Log(vlInfo,SInfoSourceNewerDest,[Src,DateTimeToStr(D1),Dest,DateTi'+
  'meT','oStr(D2)]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.ExecuteCommands(Commands: TCommands; At: TComma'+
  'ndAt; APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  C : TCommand;'#013#010+
  '  I : Integer;'#013#010+
  '  Opts,Cmd : String;'#013#010+
  '  Args : TStrings;'#013#010+
  '  CmdLine : Array of String;'#013#010+
  '  E : Boo','lean;'#013#010+
  '  ADictionary: TDictionary;'#013#010+
  '  SourceFile, DestFile: string;'#013#010+
  'begin'#013#010+
  '  For I:=0 to Commands.Count-1 do'#013#010+
  '    begin'#013#010+
  '      C:=Commands.CommandItems[i];'#013#010+
  '      if (C.At=At) then'#013#010+
  '        begin'#013#010+
  '          E:=True;'#013#010+
  #013#010+
  '          if assigne','d(APackage) then'#013#010+
  '            ADictionary := APackage.Dictionary'#013#010+
  '          else'#013#010+
  '            ADictionary := GlobalDictionary;'#013#010+
  '          SourceFile := ADictionary.ReplaceStrings(C.SourceFile);'#013#010+
  '          DestFile := ADictionary.ReplaceStri','ngs(C.DestFile);'#013#010+
  '          if IsRelativePath(SourceFile) then'#013#010+
  '            SourceFile := AddPathPrefix(APackage,SourceFile);'#013#010+
  '          if IsRelativePath(DestFile) then'#013#010+
  '            DestFile := AddPathPrefix(APackage,DestFile);'#013#010+
  #013#010+
  '        ','  Cmd:=C.Command;'#013#010+
  '          If (ExtractFilePath(Cmd)='#039#039') then'#013#010+
  '            Cmd:=ExeSearch(Cmd,{$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}'+
  'SysUtils.GetEnvironmentvariable('#039'PATH'#039'));'#013#010+
  #013#010+
  '          If (SourceFile<>'#039#039') and (DestFile<>'#039#039')  then'#013+
  #010+
  '     ','       begin'#013#010+
  '              if not FileExists(DestFile) then'#013#010+
  '                Log(vlInfo,SInfoDestDoesNotExist,[DestFile])'#013#010+
  '              else'#013#010+
  '                begin'#013#010+
  '                E:=FileNewer(SourceFile, DestFile);'#013#010+
  '                if E',' and (cmd = '#039#039') then'#013#010+
  '                  begin'#013#010+
  '                  log(vlWarning,SWarnExtCommandNotFound,[C.Command,Des'+
  'tFile,SourceFile]);'#013#010+
  '                  E := False;'#013#010+
  '                  end;'#013#010+
  '                end;'#013#010+
  '            end;'#013#010+
  '       ','   If E then'#013#010+
  '            begin'#013#010+
  '            if Cmd = '#039#039' then'#013#010+
  '              error(SErrExtCommandNotFound,[C.Command]);'#013#010+
  #013#010+
  '            If Assigned(C.BeforeCommand) then'#013#010+
  '              C.BeforeCommand(C);'#013#010+
  '            Opts:=ADictionary.Subst','itute(C.CmdLineOptions,['#039'SOUR'+
  'CE'#039',SourceFile,'#039'DEST'#039',DestFile]);'#013#010+
  '            CmdLine:=Opts.Split(['#039' '#039'],'#039'"'#039','#039'"'#039')'+
  ';'#013#010+
  '            Args:=TstringList.Create;'#013#010+
  '            try'#013#010+
  '              Args.AddStrings(CmdLine);'#013#010+
  '              Log(vlCommand,SI','nfoExecutingCommand,[Cmd,Opts]);'#013#010+
  '              ExecuteCommand(Cmd,Args,nil,C.IgnoreResult);'#013#010+
  '            finally'#013#010+
  '              Args.Free;'#013#010+
  '            end;'#013#010+
  '            If Assigned(C.AfterCommand) then'#013#010+
  '              C.AfterCommand(C);'#013#010+
  ' ','           end;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.LogSearchPath(APackage: TPackage; const ASearch'+
  'PathName: string; Path: TConditionalStrings; ACPU: TCPU; AOS: TOS);'#013+
  #010+
  'var'#013#010+
  '  S : String;'#013#010+
  '  I : Integer;'#013#010+
  '  C : TConditi','onalString;'#013#010+
  'begin'#013#010+
  '  S:='#039#039';'#013#010+
  '  for i:=0 to Path.Count-1 do'#013#010+
  '    begin'#013#010+
  '      C:=Path[I];'#013#010+
  '      if (ACPU in C.CPUs) and (AOS in C.OSes) then'#013#010+
  '        begin'#013#010+
  '          if S<>'#039#039' then'#013#010+
  '            S:=S+PathSeparator;'#013#010+
  '          S:=S+APackage.','Dictionary.ReplaceStrings(C.Value)'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  '  if S<>'#039#039' then'#013#010+
  '    Log(vlDebug,SDbgSearchPath,[ASearchPathName,S]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.FindFileInPath(APackage: TPackage;'#013#010+
  '  Path: TConditionalStrings; const AFileN','ame: String; var FoundPath:'+
  ' String;'#013#010+
  '  ACPU: TCPU; AOS: TOS): Boolean;'#013#010+
  'var'#013#010+
  '  I : Integer;'#013#010+
  '  C : TConditionalString;'#013#010+
  'begin'#013#010+
  '  Result:=false;'#013#010+
  '  for i:=0 to Path.Count-1 do'#013#010+
  '    begin'#013#010+
  '      C:=Path[I];'#013#010+
  '      if (ACPU in C.CPUs) and (AOS',' in C.OSes) then'#013#010+
  '        begin'#013#010+
  '          FoundPath:=IncludeTrailingPathDelimiter(APackage.Dictionary.'+
  'ReplaceStrings(C.Value));'#013#010+
  '          if FileExists(AddPathPrefix(APackage,FoundPath+AFileName)) t'+
  'hen'#013#010+
  '            begin'#013#010+
  '              re','sult:=true;'#013#010+
  '              exit;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  '  FoundPath:='#039#039';'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.GetDirectoriesFromFilelist(const AFileList, ADi'+
  'rectoryList: TStringList);'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  '  s: string;'#013#010+
  'begin'#013,#010+
  '  ADirectoryList.Sorted:=true;'#013#010+
  '  ADirectoryList.Duplicates:=dupIgnore;'#013#010+
  '  for i := 0 to AFileList.Count-1 do'#013#010+
  '    begin'#013#010+
  '      s := ExtractFileDir(AFileList.Strings[i]);'#013#010+
  '      if s <> '#039#039' then'#013#010+
  '        ADirectoryList.Add(s);'#013#010+
  '    end;'#013#010+
  'en','d;'#013#010+
  #013#010+
  'procedure TBuildEngine.AddPackageMacrosToDictionary(const APackage: TP'+
  'ackage; ADictionary: TDictionary);'#013#010+
  'begin'#013#010+
  '  APackage.Dictionary.AddVariable('#039'UNITSOUTPUTDIR'#039',AddPathPref'+
  'ix(APackage,APackage.GetUnitsOutputDir(Defaults.CompileTarg','et)));'#013+
  #010+
  '  APackage.Dictionary.AddVariable('#039'BINOUTPUTDIR'#039',AddPathPrefix'+
  '(APackage,APackage.GetBinOutputDir(Defaults.CompileTarget)));'#013#010+
  '  APackage.Dictionary.AddVariable('#039'PACKAGEVERSION'#039',APackage.Ve'+
  'rsion);'#013#010+
  '  APackage.Dictionary.AddVariable('#039'P','ACKAGEDIRECTORY'#039',APackag'+
  'e.Directory);'#013#010+
  '  APackage.Dictionary.AddVariable('#039'PackageName'#039',APackage.Name)'+
  ';'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.ResolveFileNames(APackage: TPackage; ACPU: TCPU'+
  ';'#013#010+
  '  AOS: TOS; DoChangeDir: boolean; WarnIfNotFound: boole','an);'#013#010+
  #013#010+
  '  procedure FindMainSource(T:TTarget);'#013#010+
  '  var'#013#010+
  '    SD,SF  : String;'#013#010+
  '  begin'#013#010+
  '    LogSearchPath(APackage,'#039'package source'#039',APackage.SourcePat'+
  'h,ACPU,AOS);'#013#010+
  '    SD:=APackage.Dictionary.ReplaceStrings(T.Directory);'#013#010+
  '    SF:=APackage.Dic','tionary.ReplaceStrings(T.SourceFileName);'#013#010+
  '    if SD='#039#039' then'#013#010+
  '      FindFileInPath(APackage,APackage.SourcePath,SF,SD,ACPU,AOS);'#013+
  #010+
  '    if SD<>'#039#039' then'#013#010+
  '      SD:=IncludeTrailingPathDelimiter(SD);'#013#010+
  '    T.FTargetSourceFileName:=SD+SF;'#013#010+
  '    if F','ileExists(AddPathPrefix(APackage,T.TargetSourceFileName)) th'+
  'en'#013#010+
  '      Log(vlDebug,SDbgResolvedSourceFile,[T.SourceFileName,T.TargetSou'+
  'rceFileName])'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '        if WarnIfNotFound then'#013#010+
  '          Log(vlWarning,SWarnSourceF','ileNotFound,[T.SourceFileName,AP'+
  'ackage.Name,MakeTargetString(ACPU,AOS)]);'#013#010+
  '        APackage.FAllFilesResolved:=false;'#013#010+
  '        T.FTargetSourceFileName:='#039#039';'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  procedure FindIncludeSources(T:TTarget);'#013#010+
  '  var'#013#010+
  '    SD,SF ',' : String;'#013#010+
  '    D : TDependency;'#013#010+
  '    j : integer;'#013#010+
  '  begin'#013#010+
  '    LogSearchPath(APackage,'#039'target include'#039',T.IncludePath,ACPU'+
  ',AOS);'#013#010+
  '    LogSearchPath(APackage,'#039'package include'#039',APackage.IncludeP'+
  'ath,ACPU,AOS);'#013#010+
  '    for j:=0 to T.Dependencies.','Count-1 do'#013#010+
  '      begin'#013#010+
  '        D:=T.Dependencies[j];'#013#010+
  '        if (D.DependencyType=depInclude) then'#013#010+
  '          begin'#013#010+
  '            if D.TargetFileName<>'#039#039' then'#013#010+
  '              Log(vlDebug,SDbgSourceAlreadyResolved,[D.Value])'#013#010+
  '            el','se if (ACPU in D.CPUs) and (AOS in D.OSes) then'#013#010+
  '              begin'#013#010+
  '                if ExtractFilePath(D.Value)='#039#039' then'#013#010+
  '                  begin'#013#010+
  '                    SF:=APAckage.Dictionary.ReplaceStrings(D.Value);'#013+
  #010+
  '                    SD',':='#039#039';'#013#010+
  '                    // first check the target specific path'#013#010+
  '                    if not FindFileInPath(APackage, T.IncludePath,SF,S'+
  'D,ACPU,AOS) then'#013#010+
  '                      FindFileInPath(APackage, APackage.IncludePath,SF'+
  ',SD,ACPU,AOS);',#013#010+
  '                     if SD<>'#039#039' then'#013#010+
  '                       SD:=IncludeTrailingPathDelimiter(SD);'#013#010+
  '                     D.TargetFileName:=SD+SF;'#013#010+
  '                  end'#013#010+
  '                else'#013#010+
  '                  D.TargetFileName:=D.Value;'#013#010+
  ' ','               if FileExists(AddPathPrefix(APackage,D.TargetFileNam'+
  'e)) then'#013#010+
  '                  Log(vlDebug,SDbgResolvedIncludeFile,[D.Value,D.Targe'+
  'tFileName])'#013#010+
  '                else'#013#010+
  '                  begin'#013#010+
  '                    if WarnIfNotF','ound then'#013#010+
  '                      Log(vlWarning,SWarnIncludeFileNotFound,[D.Value,'+
  ' APackage.Name, MakeTargetString(ACPU,AOS)]);'#013#010+
  '                    APackage.FAllFilesResolved:=false;'#013#010+
  '                    D.TargetFileName:='#039#039';'#013#010+
  '             ','     end;'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  procedure FindExampleSource(T:TTarget);'#013#010+
  '  var'#013#010+
  '    SD,SF  : String;'#013#010+
  '  begin'#013#010+
  '    LogSearchPath(APackage,'#039'package example'#039',APackage.ExampleP'+
  'ath,ACPU,AOS);'#013#010+
  '    SD:=APac','kage.Dictionary.ReplaceStrings(T.Directory);'#013#010+
  '    SF:=APackage.Dictionary.ReplaceStrings(T.SourceFileName);'#013#010+
  '    if SD='#039#039' then'#013#010+
  '      FindFileInPath(APackage, APackage.ExamplePath,SF,SD,ACPU,AOS);'#013+
  #010+
  '    if SD<>'#039#039' then'#013#010+
  '      SD:=IncludeTrail','ingPathDelimiter(SD);'#013#010+
  '    T.FTargetSourceFileName:=SD+SF;'#013#010+
  '    if FileExists(AddPathPrefix(APackage,T.TargetSourceFileName)) then'+
  #013#010+
  '      Log(vlDebug,SDbgResolvedSourceFile,[T.SourceFileName,T.TargetSou'+
  'rceFileName])'#013#010+
  '    else'#013#010+
  '      begin'#013#010,
  '        if WarnIfNotFound then'#013#010+
  '          Log(vlWarning,SWarnSourceFileNotFound,[T.SourceFileName, APa'+
  'ckage.Name, MakeTargetString(ACPU,AOS)]);'#013#010+
  '        T.FTargetSourceFileName:='#039#039';'#013#010+
  '        APackage.FAllFilesResolved:=false;'#013#010+
  '      end;'#013#010+
  ' ',' end;'#013#010+
  #013#010+
  'var'#013#010+
  '  T : TTarget;'#013#010+
  '  i : Integer;'#013#010+
  'begin'#013#010+
  '  if not((ACPU in APackage.CPUs) and (AOS in APackage.OSes)) then'#013#010+
  '    exit;'#013#010+
  '  if APackage.FAllFilesResolved then'#013#010+
  '    Exit;'#013#010+
  '  APackage.FAllFilesResolved:=true;'#013#010+
  '  try'#013#010+
  '    if DoChangeD','ir and (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := APackage.Directory;'#013#010+
  '    APackage.Dictionary.AddVariable('#039'CPU'#039',CPUToString(ACPU));'#013+
  #010+
  '    APackage.Dictionary.AddVariable('#039'OS'#039',OSToString(AOS));'#013+
  #010+
  '    For I:=0 to APackage.Targets.Coun','t-1 do'#013#010+
  '      begin'#013#010+
  '        T:=APackage.FTargets.TargetItems[I];'#013#010+
  '        if (ACPU in T.CPUs) and (AOS in T.OSes) then'#013#010+
  '          begin'#013#010+
  '            // Debug information'#013#010+
  '            Log(vlDebug,SDbgResolvingSourcesOfTarget,[T.Name,MakeTar','g'+
  'etString(ACPU,AOS)]);'#013#010+
  '            try'#013#010+
  '              LogIndent;'#013#010+
  #013#010+
  '              case T.TargetType of'#013#010+
  '                ttProgram,'#013#010+
  '                ttSharedLibrary,'#013#010+
  '                ttUnit,'#013#010+
  '                ttImplicitUnit :'#013#010+
  '              ','    begin'#013#010+
  '                    if T.FTargetSourceFileName<>'#039#039' then'#013#010+
  '                      Log(vlDebug,SDbgSourceAlreadyResolved,[T.Name])'#013+
  #010+
  '                    else'#013#010+
  '                      FindMainSource(T);'#013#010+
  '                    if T.Dependen','cies.Count>0 then'#013#010+
  '                      FindIncludeSources(T);'#013#010+
  '                  end;'#013#010+
  '                ttExampleUnit,'#013#010+
  '                ttExampleProgram :'#013#010+
  '                  begin'#013#010+
  '                    if T.FTargetSourceFileName<>'#039#039' then'#013#010+
  ' ','                     Log(vlDebug,SDbgSourceAlreadyResolved,[T.Name]'+
  ')'#013#010+
  '                    else'#013#010+
  '                      FindExampleSource(T);'#013#010+
  '                  end;'#013#010+
  '                ttCleanOnlyUnit: // not sure about this one ?'#013#010+
  '            ','      ; // Avoid compiler warning'#013#010+
  '              end;'#013#010+
  '            finally'#013#010+
  '              LogUnIndent;'#013#010+
  '            end;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    If DoChangeDir and (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := '#039#039';'#013,#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.ClearResolvedFileNames(APackage: TPackage);'#013+
  #010+
  #013#010+
  '  procedure ClearResolvedFileNamesForDependencies(ADependencies: TDepe'+
  'ndencies);'#013#010+
  '  var'#013#010+
  '    I: Integer;'#013#010+
  '    D: TDependency;'#013#010+
  '  begin'#013#010+
  '    For I:=0 to A','Dependencies.Count-1 do'#013#010+
  '      begin'#013#010+
  '        D := ADependencies[I];'#013#010+
  '        D.TargetFileName:='#039#039';'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  'var'#013#010+
  '  T : TTarget;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  APackage.FAllFilesResolved:=false;'#013#010+
  '  ClearResolvedFileNamesForDependen','cies(APackage.Dependencies);'#013#010+
  '  For I:=0 to APackage.Targets.Count-1 do'#013#010+
  '    begin'#013#010+
  '      T:=APackage.FTargets.TargetItems[I];'#013#010+
  '      T.FTargetSourceFileName:='#039#039';'#013#010+
  '      ClearResolvedFileNamesForDependencies(T.Dependencies);'#013#010+
  '    end;'#013#010+
  'end;',#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.ResolvePackagePaths(APackage:TPackage);'#013#010+
  #013#010+
  'var'#013#010+
  '  i: Integer;'#013#010+
  '  Continue: Boolean;'#013#010+
  'begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  APackage.EnterResolveDirsCS;'#013#010+
  '  try'#013#010+
  '{$endif}'#013#010+
  '    if APackage.UnitDir='#039#039' then'#013#010+
  '      begin'#013#010,
  '        Log(vldebug, SDbgSearchExtDepPath, [APackage.Name]);'#013#010+
  '        GetPluginManager.BeforeResolvePackagePath(Self, APackage, Cont'+
  'inue);'#013#010+
  '        if Continue then'#013#010+
  '          begin'#013#010+
  '          for I := 0 to Defaults.SearchPath.Count-1 do'#013#010+
  ' ','           begin'#013#010+
  '              if Defaults.SearchPath[i]<>'#039#039' then'#013#010+
  '                GetPluginManager.ResolvePackagePath(Self, APackage, De'+
  'faults.SearchPath[i], Continue);'#013#010+
  '              if not Continue then'#013#010+
  '                Break'#013#010+
  '         ','   end;'#013#010+
  #013#010+
  '          if Continue then'#013#010+
  '            GetPluginManager.AfterResolvePackagePath(Self, APackage, C'+
  'ontinue);'#013#010+
  '          end;'#013#010+
  #013#010+
  '        if APackage.UnitDir = '#039#039' then'#013#010+
  '          APackage.UnitDir := DirNotFound'#013#010+
  '      end;'#013#010+
  '{$ifndef',' NO_THREADING}'#013#010+
  '  finally'#013#010+
  '    APackage.LeaveResolveDirsCS;'#013#010+
  '  end;'#013#010+
  '{$endif}'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.GetUnitDir(APackage:TPackage):String;'#013#010+
  'begin'#013#010+
  '  ResolvePackagePaths(APackage);'#013#010+
  '  // Special error marker to prevent searches in ','case of error'#013#010+
  '  if APackage.UnitDir=DirNotFound then'#013#010+
  '    Result:='#039#039#013#010+
  '  else'#013#010+
  '    Result:=APackage.UnitDir;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.AddDependencyPaths(L: TStrings; DependencyType:'+
  ' TDependencyType; ATarget: TTarget);'#013#010+
  'Var'#013#010+
  '  I : I','nteger;'#013#010+
  '  D : TDependency;'#013#010+
  '  SD : String;'#013#010+
  'begin'#013#010+
  '  For I:=0 to ATarget.Dependencies.Count-1 do'#013#010+
  '    begin'#013#010+
  '      D:=ATarget.Dependencies[i];'#013#010+
  '      if (D.DependencyType=DependencyType) and'#013#010+
  '         (Defaults.CPU in D.CPUs) and (Defaults','.OS in D.OSes) then'#013+
  #010+
  '        begin'#013#010+
  '          SD:=ExcludeTrailingPathDelimiter(ExtractFilePath(D.TargetFil'+
  'eName));'#013#010+
  '          if SD<>'#039#039' then'#013#010+
  '            L.Add(SD);'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.AddDependencyUnit','Paths(L:TStrings;APackage: T'+
  'Package);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  D : TDependency;'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  For I:=0 to APackage.Dependencies.Count-1 do'#013#010+
  '    begin'#013#010+
  '      D:=APackage.Dependencies[i];'#013#010+
  '      if (D.DependencyType','=depPackage) and'#013#010+
  '         (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'#013+
  #010+
  '        begin'#013#010+
  '          P:=TPackage(D.Target);'#013#010+
  '          If Assigned(P) then'#013#010+
  '            begin'#013#010+
  '              // Already processed?'#013#010+
  '              S:=G','etUnitDir(P);'#013#010+
  '              if L.IndexOf(S)=-1 then'#013#010+
  '                begin'#013#010+
  '                  // Add this package and then dependencies'#013#010+
  '                  L.Add(S);'#013#010+
  '                  AddDependencyUnitPaths(L,P);'#013#010+
  '                end;'#013#010+
  '   ','         end;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{$ifdef NO_THREADING}'#013#010+
  'var'#013#010+
  '{$else NO_THREADING}'#013#010+
  'threadvar'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  GHandledRecursiveDependencies: TStrings;'#013#010+
  #013#010+
  'procedure TBuildEngine.AddDependencyTransmittedOptions(Args: TS','tring'+
  's; APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  D : TDependency;'#013#010+
  '  IsRootLevel: Boolean;'#013#010+
  'begin'#013#010+
  '  if not Assigned(GHandledRecursiveDependencies) then'#013#010+
  '    begin'#013#010+
  '      GHandledRecursiveDependencies := TStringList.Cre','ate;'#013#010+
  '      IsRootLevel := True;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    IsRootLevel := False;'#013#010+
  #013#010+
  '  try'#013#010+
  '    For I:=0 to APackage.Dependencies.Count-1 do'#013#010+
  '      begin'#013#010+
  '        D:=APackage.Dependencies[i];'#013#010+
  '        if (D.DependencyType=depPackage) and'#013#010+
  '      ','     (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'+
  #013#010+
  '          begin'#013#010+
  '            P:=TPackage(D.Target);'#013#010+
  '            If Assigned(P) then'#013#010+
  '              begin'#013#010+
  '                // Already processed?'#013#010+
  '                if GHandledRec','ursiveDependencies.IndexOf(P.Name)=-1 '+
  'then'#013#010+
  '                  begin'#013#010+
  '                    GHandledRecursiveDependencies.Add(P.Name);'#013#010+
  '                    AddDependencyTransmittedOptions(Args,P);'#013#010+
  '                    Args.AddStrings(P.Transmi','tOptions);'#013#010+
  '                  end;'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    if IsRootLevel then'#013#010+
  '      FreeAndNil(GHandledRecursiveDependencies);'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.AddPathPrefix(APackage: TPackage','; APath: strin'+
  'g): string;'#013#010+
  'begin'#013#010+
  '  if IsRelativePath(APath) and (GPathPrefix<>'#039#039') then'#013#010+
  '    result := IncludeTrailingPathDelimiter(GPathPrefix) + APath'#013#010+
  '  else'#013#010+
  '    result := APath;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.GetCompilerCommand(APack','age: TPackage; ATarget'+
  ': TTarget;'#013#010+
  '  Env: TStrings): String;'#013#010+
  #013#010+
  'var'#013#010+
  '  Args : TStringList;'#013#010+
  '  i : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  Args:=TStringList.Create;'#013#010+
  '  try'#013#010+
  '    Args:=TStringList.Create;'#013#010+
  '    Args.Duplicates:=dupIgnore;'#013#010+
  '    GetCo','mpilerCommand(Args,aPackage,aTarget,Env);'#013#010+
  '    // Convert to string'#013#010+
  '    if Defaults.UseEnvironment and assigned(Env) then'#013#010+
  '      Result:='#039'!FPCEXTCMD'#039' // Result is in environment.'#013#010+
  '    else'#013#010+
  '      for i:=0 to Args.Count-1 do'#013#010+
  '        Result',':=Result+'#039' '#039'+Args[i];'#013#010+
  '    Delete(result,1,1);'#013#010+
  '  finally'#013#010+
  '    Args.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.GetCompilerCommand(Args: TStrings; APackage: TP'+
  'ackage;'#013#010+
  '  ATarget: TTarget; Env: TStrings);'#013#010+
  #013#010+
  'Var'#013#010+
  '  L : TUnsortedDuplicate','sStringList;'#013#010+
  '  s : string;'#013#010+
  '  ExtCmd,ErrS: string;'#013#010+
  '  i : Integer;'#013#010+
  'begin'#013#010+
  '  if ATarget.TargetSourceFileName = '#039#039' then'#013#010+
  '    Error(SErrCouldNotCompile,[ATarget.Name, APackage.Name]);'#013#010+
  #013#010+
  '  //compiler configuration'#013#010+
  '  if Defaults.NoFPCCfg the','n'#013#010+
  '    Args.Add('#039'-n'#039');'#013#010+
  #013#010+
  '  // Target OS'#013#010+
  '  Args.Add('#039'-T'#039'+OSToString(Defaults.OS));'#013#010+
  #013#010+
  '  // Target CPU.'#013#010+
  '  // This setting is only applicable when '#039'fpc'#039' is used as com'+
  'piler-executable.'#013#010+
  '  if ExtractFileName(GetCompiler) = '#039'fpc'#039' then'#013#010+
  '    Ar','gs.Add('#039'-P'#039'+CPUToString(Defaults.CPU));'#013#010+
  #013#010+
  '  // Subtarget'#013#010+
  '  if (Defaults.SubTarget<>'#039#039') then'#013#010+
  '    Args.Add('#039'-t'#039'+Defaults.SubTarget);'#013#010+
  #013#010+
  '  // Compile mode'#013#010+
  '  If ATarget.Mode<>cmFPC then'#013#010+
  '    Args.Add('#039'-M'#039'+ModeToString(ATarget.Mode))'#013#010+
  '  else',' If Defaults.Mode<>cmFPC then'#013#010+
  '    Args.Add('#039'-M'#039'+ModeToString(Defaults.Mode));'#013#010+
  '  // Output file paths'#013#010+
  '  If ATarget.TargetType in ProgramTargets then'#013#010+
  '    Args.Add('#039'-FE'#039'+AddPathPrefix(APackage,APackage.GetBinOutpu'+
  'tDir(Defaults.CompileTarge','t)));'#013#010+
  '  Args.Add('#039'-FU'#039'+AddPathPrefix(APackage,APackage.GetUnitsOutpu'+
  'tDir(Defaults.CompileTarget)));'#013#010+
  '  // Object Path'#013#010+
  '  L:=TUnsortedDuplicatesStringList.Create;'#013#010+
  '  L.Duplicates:=dupIgnore;'#013#010+
  '  AddConditionalStrings(APackage, L,APackage.Obj','ectPath, Defaults.Co'+
  'mpileTarget);'#013#010+
  '  AddConditionalStrings(APackage, L,ATarget.ObjectPath, Defaults.Compi'+
  'leTarget);'#013#010+
  '  for i:=0 to L.Count-1 do'#013#010+
  '    Args.Add('#039'-Fo'#039'+AddPathPrefix(APackage,L[i]));'#013#010+
  '  FreeAndNil(L);'#013#010+
  '  // Unit Dirs'#013#010+
  '  L:=TUnso','rtedDuplicatesStringList.Create;'#013#010+
  '  L.Duplicates:=dupIgnore;'#013#010+
  '  AddDependencyUnitPaths(L,APackage);'#013#010+
  '  AddDependencyPaths(L,depUnit,ATarget);'#013#010+
  '  AddConditionalStrings(APackage, L,APackage.UnitPath,Defaults.Compile'+
  'Target);'#013#010+
  '  AddConditionalS','trings(APackage, L,ATarget.UnitPath,Defaults.Compil'+
  'eTarget);'#013#010+
  '  for i:=0 to L.Count-1 do'#013#010+
  '    Args.Add('#039'-Fu'#039'+AddPathPrefix(APackage,L[i]));'#013#010+
  '  FreeAndNil(L);'#013#010+
  '  // Include Path'#013#010+
  '  L:=TUnsortedDuplicatesStringList.Create;'#013#010+
  '  L.Duplicates:=du','pIgnore;'#013#010+
  '  AddDependencyPaths(L,depInclude,ATarget);'#013#010+
  '  AddConditionalStrings(APackage, L,APackage.IncludePath, Defaults.Com'+
  'pileTarget);'#013#010+
  '  AddConditionalStrings(APackage, L,ATarget.IncludePath, Defaults.Comp'+
  'ileTarget);'#013#010+
  '  for i:=0 to L.Co','unt-1 do'#013#010+
  '    Args.Add('#039'-Fi'#039'+AddPathPrefix(APackage,L[i]));'#013#010+
  '  FreeAndNil(L);'#013#010+
  #013#010+
  '  // libc-linker path (always for Linux, since required for LLVM and S'+
  'EH; this does not'#013#010+
  '  // force the linking of anything by itself, but just adds a search d',
  'irectory)'#013#010+
  '  // Do not add it if -Xd option is used'#013#010+
  '  if (APackage.NeedLibC or (Defaults.OS=linux)) and'#013#010+
  '     ((not Defaults.HaveOptions) or (Defaults.Options.IndexOf('#039'-Xd'+
  #039')=-1)) then'#013#010+
  '    begin'#013#010+
  '      if FCachedlibcPath='#039#039' then'#013#010+
  '        b','egin'#013#010+
  #013#010+
  '          s:=GetDefaultLibGCCDir(Defaults.CPU, Defaults.OS,ErrS);'#013#010+
  '          if s='#039#039' then'#013#010+
  '            begin'#013#010+
  '              if (ErrS<>'#039#039') and not (GCCLibWarningIssued) then'#013+
  #010+
  '                Log(vlWarning, SWarngcclibpath +'#039' '#039'+ErrS);',#013+
  #010+
  '             GCCLibWarningIssued:=True;'#013#010+
  '           end'#013#010+
  '          else'#013#010+
  '            begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '              EnterCriticalsection(FGeneralCriticalSection);'#013#010+
  '              { prevent FCachedlibcPath getting freed by thr','ead 2 wh'+
  'ile thread 1 is'#013#010+
  '                concatenating it to -Fl below }'#013#010+
  '              try'#013#010+
  '                if {$IFDEF HAVE_VOLATILE}volatile{$ENDIF}(FCachedlibcP'+
  'ath)='#039#039' then'#013#010+
  '                  begin'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '               ','     FCachedlibcPath:=s;'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '                  end;'#013#010+
  '              finally'#013#010+
  '                LeaveCriticalsection(FGeneralCriticalSection);'#013#010+
  '              end;'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '            end;'#013#010+
  '        end'#013#010+
  '     ',' else'#013#010+
  '        { make sure we don'#039't access the contents of the string bef'+
  'ore they'#039've been'#013#010+
  '          synchronised from the thread that wrote them; the critical s'+
  'ection there'#013#010+
  '          acts as a read/write barrier }'#013#010+
  '        ReadBarrier;'#013#010+
  '{','$ifdef NO_THREADING}'#013#010+
  '      Args.Add('#039'-Fl'#039'+FCachedlibcPath);'#013#010+
  '{$ELSE}'#013#010+
  '      Args.Add('#039'-Fl'#039'+{$IFDEF HAVE_VOLATILE}volatile{$ENDIF}(FC'+
  'achedlibcPath));'#013#010+
  '{$ENDIF}'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Custom options which are added by dependencies'#013#010+
  '  AddDependenc','yTransmittedOptions(Args, APackage);'#013#010+
  #013#010+
  '  // Custom Options'#013#010+
  '  If (Defaults.HaveOptions) then'#013#010+
  '    Args.AddStrings(Defaults.Options);'#013#010+
  #013#010+
  '  APackage.ApplyPackageVariantToCompilerOptions(Args);'#013#010+
  #013#010+
  '  If (APackage.HaveOptions) then'#013#010+
  '    Args.Ad','dStrings(APackage.Options);'#013#010+
  '  If (ATarget.HaveOptions) then'#013#010+
  '    Args.AddStrings(ATarget.Options);'#013#010+
  #013#010+
  '  {$ifdef HAS_UNIT_PROCESS}'#013#010+
  '  // Force the compiler-output to be easy parseable'#013#010+
  '  if not Verbose then'#013#010+
  '    args.Add('#039'-viq'#039');'#013#010+
  '  {$endif','}'#013#010+
  #013#010+
  '  // Convert to string'#013#010+
  '  ExtCmd:='#039#039';'#013#010+
  '  for i:=0 to Args.Count-1 do'#013#010+
  '    ExtCmd:=ExtCmd+'#039' '#039'+maybequoted(APackage.Dictionary.Replace'+
  'Strings(Args[i]));'#013#010+
  '  Delete(ExtCmd,1,1);'#013#010+
  #013#010+
  '  if Defaults.UseEnvironment and assigned(Env) then'#013#010+
  '    b','egin'#013#010+
  '      env.Values['#039'FPCEXTCMD'#039'] := ExtCmd;'#013#010+
  '      // Make sure that this process'#039' environment variables are pa'+
  'ssed to the'#013#010+
  '      // compiler'#039's environment'#013#010+
  '      for i := 0 to GetEnvironmentVariableCount-1 do'#013#010+
  '        env.Add(GetEnviron','mentString(i));'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Replace strings'#013#010+
  '  for I:=0 to Args.Count-1 do'#013#010+
  '    Args[i]:=APackage.Dictionary.ReplaceStrings(Args[i]);'#013#010+
  '  // Add Filename to compile'#013#010+
  '  Args.Add(AddPathPrefix(APackage,ATarget.TargetSourceFileName));'#013#010+
  'en','d;'#013#010+
  #013#010+
  'function TBuildEngine.TargetOK(ATarget: TTarget; ACPU: TCPU; AOS: TOS;'+
  #013#010+
  '  const aSubTarget: String): Boolean;'#013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result:=TargetOK(aTa','rget,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.GetCompiler: String;'#013#010+
  'Var'#013#010+
  '  S : String;'#013#010+
  'begin'#013#010+
  '  // Cache in FCompiler for speed.'#013#010+
  '  If (FCompiler='#039#039') then'#013#010+
  '    begin'#013#010+
  '    FCompiler:=Defaults.Compiler;'#013#010+
  '    If (ExtractFilePath(FCompiler)='#039#039') t','hen'#013#010+
  '      begin'#013#010+
  '      S:=ExeSearch(FCompiler,{$IFDEF FPC_DOTTEDUNITS}System.{$ENDIF}Sy'+
  'sUtils.GetEnvironmentVariable('#039'PATH'#039'));'#013#010+
  '      If (S<>'#039#039') then'#013#010+
  '         FCompiler:=S;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  Result:=FCompiler;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure ','TBuildEngine.CreateOutputDir(APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  D : String;'#013#010+
  '  i: integer;'#013#010+
  'begin'#013#010+
  '  //create a units directory'#013#010+
  '  D:=AddPathPrefix(APackage,APackage.GetUnitsOutputDir(Defaults.Compil'+
  'eTarget));'#013#010+
  '  If not SysDirectoryExists(D) then',#013#010+
  '    begin'#013#010+
  '      Log(vlInfo,SInfoCreatingOutputDir,[D]);'#013#010+
  '      CmdCreateDir(D);'#013#010+
  '    end;'#013#010+
  #013#010+
  '  //also create a bin directory for programtargets'#013#010+
  '  For i := 0 to Pred(APackage.Targets.Count) do'#013#010+
  '    begin'#013#010+
  '      if APackage.Targets.Target','Items[i].TargetType in (ProgramTarge'+
  'ts-[ttExampleProgram]) then'#013#010+
  '        begin'#013#010+
  '          D:=AddPathPrefix(APackage,APackage.GetBinOutputDir(Defaults.'+
  'CompileTarget));'#013#010+
  '          If not SysDirectoryExists(D) then'#013#010+
  '            begin'#013#010+
  '        ','      Log(vlInfo,SInfoCreatingOutputDir,[D]);'#013#010+
  '              CmdCreateDir(D);'#013#010+
  '            end;'#013#010+
  '          //do not continue loop, directory is made anyway'#013#010+
  '          break;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.Dependenc','yOK(ADependency: TDependency): Boolea'+
  'n;'#013#010+
  'begin'#013#010+
  '  Result:=(Defaults.CPU in ADependency.CPUs) and (Defaults.OS in ADepe'+
  'ndency.OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.TargetOK(ATarget: TTarget; const aCompileTarget '+
  ': TCompileTarget): Boolean;'#013#010,
  #013#010+
  #013#010+
  'begin'#013#010+
  '  if (ATarget.TargetType in ProgramTargets) and'#013#010+
  '     (Defaults.SkipAllPrograms or'#013#010+
  '      (Defaults.SkipCrossPrograms and'#013#010+
  '       IsDifferentFromBuild(aCOmpileTarget.CPU, aCOmpileTarget.OS))) t'+
  'hen'#013#010+
  '    result := False'#013#010+
  '  else'#013#010+
  '  ','  Result:=(aCompileTarget.CPU in ATarget.CPUs)'#013#010+
  '            and (aCompileTarget.OS in ATarget.OSes)'#013#010+
  '            and aTarget.SubTargetAllowed(aCompileTarget.SubTarget);'#013+
  #010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.TargetInstallOK(ATarget: TTarget; ACPU: ','TCPU; '+
  'AOS: TOS;'#013#010+
  '  const aSubTarget: String): Boolean;'#013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  Result:=TargetInstallOK(aTarget,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.TargetInstallOK','(ATarget: TTarget;'#013#010+
  '  const aCompileTarget: TCompileTarget): Boolean;'#013#010+
  'begin'#013#010+
  '  result := TargetOK(ATarget, aCompileTarget) and ATarget.Install;'#013+
  #010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.PackageOK(APackage: TPackage): Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=(Def','aults.CPU in APackage.CPUs) and (Defaults.OS in APacka'+
  'ge.OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoBeforeCompile(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  ExecuteCommands(APackage.Commands,caBeforeCompile);'#013#010+
  '  If Assigned(APackage.BeforeCompile) then',#013#010+
  '    APackage.BeforeCompile(APackage);'#013#010+
  '  If Assigned(APackage.BeforeCompileProc) then'#013#010+
  '    APackage.BeforeCompileProc(APackage);'#013#010+
  '  // It could be that files that weren'#039't found before are availabl'+
  'e now.'#013#010+
  '  ResolveFileNames(APackage,Defaul','ts.CPU,Defaults.OS,false,true);'#013+
  #010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoAfterCompile(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  If Assigned(APackage.AfterCompile) then'#013#010+
  '    APackage.AfterCompile(APackage);'#013#010+
  '  If Assigned(APackage.AfterCompileProc) then'#013#010+
  '  ','  APackage.AfterCompileProc(APackage);'#013#010+
  '  ExecuteCommands(APackage.Commands,caAfterCompile);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.NeedsCompile(APackage: TPackage; ATarget: TTarge'+
  't'#013#010+
  '  ): Boolean;'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  D : TDependency;'#013#010+
  '  T : T','Target;'#013#010+
  '  OD,OFN,TFN : String;'#013#010+
  '  CompileReason: String;'#013#010+
  'begin'#013#010+
  '  Result:=False;'#013#010+
  #013#010+
  '  // Forced recompile?'#013#010+
  '  if FForceCompile then'#013#010+
  '    begin'#013#010+
  '    Result:=true;'#013#010+
  '    CompileReason:=SDbgForcedCompile;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // For now examples ar','e not compiled at all'#013#010+
  '  if ATarget.TargetType in [ttExampleUnit, ttExampleProgram] then'#013#010+
  '    Exit;'#013#010+
  #013#010+
  '  // Files which should not be compiled on this target can not trigger'+
  ' a compile.'#013#010+
  '  if not TargetOK(ATarget, Defaults.CompileTarget) the','n'#013#010+
  '    Exit;'#013#010+
  #013#010+
  '  // Check output file'#013#010+
  '  if not result then'#013#010+
  '    begin'#013#010+
  '      if ATarget.TargetType in ProgramTargets then'#013#010+
  '        OD:=APackage.GetBinOutputDir(Defaults.CompileTarget)'#013#010+
  '      else'#013#010+
  '        OD:=APackage.GetUnitsOutputDir(De','faults.CompileTarget);'#013#010+
  '      If (OD<>'#039#039') then'#013#010+
  '        OD:=IncludeTrailingPathDelimiter(OD);'#013#010+
  '      OFN:=AddPathPrefix(APackage, OD+ATarget.GetOutPutFileName(Defaul'+
  'ts.OS));'#013#010+
  '      Result:=Not FileExists(OFN);'#013#010+
  '      if Result then'#013#010+
  '       ',' begin'#013#010+
  '        CompileReason:=SDbgOutputDoesNotExist;'#013#010+
  '        Log(vlDebug,SDbgOutputNotYetAvailable,[OFN]);'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Check main source, only if the TargetSourceFileName is found'#013#010+
  '  If not Result and (ATarget.TargetS','ourceFileName<>'#039#039') then'#013+
  #010+
  '    begin'#013#010+
  '      TFN := AddPathPrefix(APackage,ATarget.TargetSourceFileName);'#013+
  #010+
  '      if FileExists(TFN) then'#013#010+
  '        Result:=FileNewer(TFN,OFN);'#013#010+
  '      if Result then'#013#010+
  '        CompileReason:=SDbgNewerSource;'#013#010+
  '    e','nd;'#013#010+
  #013#010+
  '  // Check unit and include dependencies'#013#010+
  '  If not Result then'#013#010+
  '    begin'#013#010+
  '      ResolveDependencies(ATarget.Dependencies,ATarget.Collection as T'+
  'Targets);'#013#010+
  '      I:=0;'#013#010+
  '      for i:=0 to ATarget.Dependencies.Count-1 do'#013#010+
  '        begin',#013#010+
  '          D:=ATarget.Dependencies[i];'#013#010+
  '          if (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'+
  #013#010+
  '            begin'#013#010+
  '              case D.DependencyType of'#013#010+
  '                depUnit :'#013#010+
  '                  begin'#013#010+
  '                ','    T:=TTarget(D.Target);'#013#010+
  '                    If (T=Nil) then'#013#010+
  '                      Error(SErrDepUnknownTarget,[D.Value, ATarget.Nam'+
  'e, APackage.Name]);'#013#010+
  '                    // If a dependent package is compiled we always ne'+
  'ed to recompile',#013#010+
  '                    Log(vldebug, SDbgDependencyOnUnit, [ATarget.Name,T'+
  '.Name]);'#013#010+
  '                    Result:=(T.State=tsCompiled);'#013#010+
  '                    if Result then'#013#010+
  '                      begin'#013#010+
  '                      Log(vldebug, SDbgDep','endencyUnitRecompiled, [T.'+
  'Name]);'#013#010+
  '                      CompileReason:=Format(SDbgDependencyRecompiled,['+
  'T.Name]);'#013#010+
  '                      end;'#013#010+
  '                  end;'#013#010+
  '                depInclude :'#013#010+
  '                  begin'#013#010+
  '                 ','   if D.TargetFileName<>'#039#039' then'#013#010+
  '                      begin'#013#010+
  '                        TFN:=AddPathPrefix(APackage,D.TargetFileName);'+
  #013#010+
  '                        Result:=FileNewer(TFN,OFN);'#013#010+
  '                        if result then'#013#010+
  '             ','             CompileReason:=Format(SDbgNewerInclude,[D.'+
  'TargetFileName]);'#013#010+
  '                      end;'#013#010+
  '                  end;'#013#010+
  '                depPackage :'#013#010+
  '                  begin'#013#010+
  '                    log(vlWarning,SWarnTargetDependsOnPacka','ge,[ATarg'+
  'et.Name, APackage.Name, d.Value]);'#013#010+
  '                  end;'#013#010+
  '                depImplicitPackage:'#013#010+
  '                  ; // Avoid compiler warning'#013#010+
  '              end;'#013#010+
  '              if result then'#013#010+
  '                break;'#013#010+
  '            e','nd;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  if result then'#013#010+
  '    Log(vlDebug,SDbgMustCompile,[ATarget.Name, CompileReason]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Compile(APackage: TPackage; ATarget: TTarget);'#013+
  #010+
  'Var'#013#010+
  '  Env : TStrings;'#013#010+
  '  Args : TStrings;'#013#010+
  ' ',' FN : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Log(vlInfo,SInfoCompilingTarget,[ATarget.Name]);'#013#010+
  '  Args:=nil;'#013#010+
  '  Env:=nil;'#013#010+
  '  try'#013#010+
  '    LogIndent;'#013#010+
  '    ExecuteCommands(ATarget.Commands,caBeforeCompile);'#013#010+
  '    If Assigned(ATarget.BeforeCompile) then'#013#010+
  '      ATarget','.BeforeCompile(ATarget);'#013#010+
  '    if (APackage.BuildMode=bmBuildUnit) and not (ATarget.TargetType in'+
  ' [ttProgram,ttSharedLibrary,ttExampleProgram]) then'#013#010+
  '      begin'#013#010+
  '        begin'#013#010+
  '        FN:=ExtractFileName(ATarget.TargetSourceFileName);'#013#010+
  '   ','     if IndexText(ExtractFileExt(FN),['#039'.pp'#039','#039'.pas'#039+
  ','#039'lpr'#039'])<>-1 then'#013#010+
  '          FN:=ChangeFileExt(FN,'#039#039');'#013#010+
  '        APackage.FBUTarget.Dependencies.AddUnit(FN).FTargetFileName:=A'+
  'Target.TargetSourceFileName;'#013#010+
  '        end;'#013#010+
  '      end'#013#010+
  '    else'#013,#010+
  '      begin'#013#010+
  '      Args:=TstringList.Create;'#013#010+
  '      if Defaults.UseEnvironment then'#013#010+
  '        Env:=TStringList.Create;'#013#010+
  '      GetCompilerCommand(Args,APackage,ATarget,Env);'#013#010+
  '      ExecuteCommand(GetCompiler,Args,Env);'#013#010+
  '      If Assigned(ATa','rget.AfterCompile) then'#013#010+
  '        ATarget.AfterCompile(ATarget);'#013#010+
  '      ExecuteCommands(ATarget.Commands,caAfterCompile);'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    LogUnIndent;'#013#010+
  '    Args.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.CompileDependencies(','APackage:TPackage; ATarge'+
  't: TTarget);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  T : TTarget;'#013#010+
  '  D : TDependency;'#013#010+
  'begin'#013#010+
  '  Log(vlDebug, Format(SDbgCompilingDependenciesOfTarget, [ATarget.Name'+
  ']));'#013#010+
  '  try'#013#010+
  '  LogIndent;'#013#010+
  '  For I:=0 to ATarget.Dependencies.Count','-1 do'#013#010+
  '    begin'#013#010+
  '      D:=ATarget.Dependencies[i];'#013#010+
  '      if (D.DependencyType=depPackage) then'#013#010+
  '        log(vlWarning,SWarnTargetDependsOnPackage,[ATarget.Name, APack'+
  'age.Name, d.Value])'#013#010+
  '      else if (D.DependencyType=depUnit) and'#013#010+
  '     ','    (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'#013+
  #010+
  '        begin'#013#010+
  '          T:=TTarget(D.Target);'#013#010+
  '          if Assigned(T) and (T<>ATarget) then'#013#010+
  '            begin'#013#010+
  '              if TargetOK(T, Defaults.CompileTarget) then'#013#010+
  '   ','             begin'#013#010+
  '                  // We don'#039't need to compile implicit units, they'+
  ' are only'#013#010+
  '                  // used for dependency checking'#013#010+
  '                  if (T.TargetType<>ttImplicitUnit) then'#013#010+
  '                    begin'#013#010+
  '       ','               case T.State of'#013#010+
  '                        tsNeutral :'#013#010+
  '                          MaybeCompile(APackage,T);'#013#010+
  '                        tsConsidering :'#013#010+
  '                          Log(vlWarning,SWarnCircularTargetDependency,'+
  '[ATarge','t.Name,T.Name]);'#013#010+
  '                        tsNoCompile,tsCompiled,tsInstalled,tsNotFound:'+
  #013#010+
  '                          ; // Avoid compiler warning'#013#010+
  '                      end;'#013#010+
  '                    end;'#013#010+
  '                end'#013#010+
  '              else'#013#010,
  '                Log(vlWarning, Format(SWarnDepUnitNotFound, [T.Name, M'+
  'akeTargetString(Defaults.CPU,Defaults.OS)]));'#013#010+
  '            end'#013#010+
  '          else'#013#010+
  '            Error(SErrDepUnknownTarget,[D.Value, ATarget.Name, APackag'+
  'e.Name]);'#013#010+
  '        e','nd;'#013#010+
  '    end;'#013#010+
  '  finally'#013#010+
  '  LogUnIndent;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.MaybeCompile(APackage: TPackage; ATarget: TTarg'+
  'et);'#013#010+
  'begin'#013#010+
  '  if ATarget.State<>tsNeutral then'#013#010+
  '    Error(SErrInvalidState,[ATarget.Name]);'#013#010+
  '  Log(vlDebug, F','ormat(SDbgConsideringTarget, [ATarget.Name]));'#013#010+
  '  try'#013#010+
  '  LogIndent;'#013#010+
  '  ATarget.FTargetState:=tsConsidering;'#013#010+
  '  ResolveDependencies(ATarget.Dependencies,ATarget.Collection as TTarg'+
  'ets);'#013#010+
  '  CompileDependencies(APackage, ATarget);'#013#010+
  '  if NeedsC','ompile(APackage, ATarget) then'#013#010+
  '    begin'#013#010+
  '      Compile(APackage,ATarget);'#013#010+
  '      ATarget.FTargetState:=tsCompiled;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    ATarget.FTargetState:=tsNoCompile;'#013#010+
  '  finally'#013#010+
  '  LogUnIndent;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngin','e.NeedsCompile(APackage: TPackage): Boolean;'#013+
  #010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  D : TDependency;'#013#010+
  '  CompileReason: string;'#013#010+
  'begin'#013#010+
  '  Result:=False;'#013#010+
  #013#010+
  '  // Forced recompile?'#013#010+
  '  if FForceCompile then'#013#010+
  '    begin'#013#010+
  '    Result:=true;'#013#010+
  '    ','CompileReason:=SDbgForcedCompile;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Recompile because of Package Dependencies?'#013#010+
  '  if not Result then'#013#010+
  '    begin'#013#010+
  '       I:=0;'#013#010+
  '       For I:=0 to APackage.Dependencies.Count-1 do'#013#010+
  '         begin'#013#010+
  '           D:=APackage.Depen','dencies[i];'#013#010+
  '           if (D.DependencyType=depPackage) and'#013#010+
  '              (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) the'+
  'n'#013#010+
  '             begin'#013#010+
  '               P:=TPackage(D.Target);'#013#010+
  '               if Assigned(P) then'#013#010+
  '          ','       begin'#013#010+
  '                   Result:=(P.State=tsCompiled);'#013#010+
  '                   if Result then'#013#010+
  '                     begin'#013#010+
  '                     CompileReason:=Format(SDbgPackageDepRecompiled,[P'+
  '.Name]);'#013#010+
  '                     break;'#013#010+
  '    ','                 end;'#013#010+
  '                 end;'#013#010+
  '             end;'#013#010+
  '         end;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  // Recompile a Target of this package?'#013#010+
  '  If Not Result then'#013#010+
  '    begin'#013#010+
  '      GPathPrefix := APackage.Directory;'#013#010+
  '      try'#013#010+
  '        for i:=0 to ','APackage.Targets.Count-1 do'#013#010+
  '          begin'#013#010+
  '            Result:=NeedsCompile(APackage,APackage.Targets.TargetItems'+
  '[i]);'#013#010+
  '            if Result then'#013#010+
  '              begin'#013#010+
  '              CompileReason:=Format(SDbgTargetHasToBeCompiled,[APack','a'+
  'ge.Targets.TargetItems[i].Name]);'#013#010+
  '              break;'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '      Finally'#013#010+
  '        GPathPrefix := '#039#039';'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  if result then'#013#010+
  '    Log(vlDebug,SDbgMustCompile,[APackage.Name, CompileReason',']);'#013+
  #010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.CheckExternalPackage(const APackageName,'#013#010+
  '  ForPackageName: String; ErrorOnFailure: boolean): TPackage;'#013#010+
  'var'#013#010+
  '  S : String;'#013#010+
  '  F : String;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  // Already checked?'#013#010+
  '  I:=ExternalPack','ages.IndexOfName(APackageName);'#013#010+
  '  if I<>-1 then'#013#010+
  '    begin'#013#010+
  '      result:=ExternalPackages.PackageItems[I];'#013#010+
  '      exit;'#013#010+
  '    end;'#013#010+
  '  // Create new external package'#013#010+
  '  Result:=ExternalPackages.AddPackage(APackageName);'#013#010+
  '  Result.FTargetSta','te:=tsNotFound;'#013#010+
  '  // Load unit config'#013#010+
  '  S:=GetUnitDir(Result);'#013#010+
  '  if S<>'#039#039' then'#013#010+
  '    begin'#013#010+
  '      Log(vldebug, SDbgExternalDependency, [APackageName,S]);'#013#010+
  '      // Load unit config if it exists'#013#010+
  '      F:=result.UnitConfigFileName;'#013#010+
  '      ','if (F<>'#039#039') then'#013#010+
  '        begin'#013#010+
  '          Log(vlDebug, Format(SDbgLoading, [F]));'#013#010+
  '          Result.LoadUnitConfigFromFile(F);'#013#010+
  '          result.SetDefaultPackageVariant;'#013#010+
  '          result.UnitDir:=ConcatPaths([result.UnitDir,Result.GetPack','a'+
  'geUnitInstallDir(Defaults.CPU, Defaults.OS, Defaults.SubTarget)]);'#013+
  #010+
  '        end;'#013#010+
  '      // Check recursive implicit dependencies'#013#010+
  '      CompileDependencies(Result);'#013#010+
  '    end'#013#010+
  '  else if ErrorOnFailure then'#013#010+
  '    Error(SErrDependencyNotFound,','[APackageName,ForPackageName]);'#013+
  #010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.CompileDependencies(APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  D : TDependency;'#013#010+
  'begin'#013#010+
  '  For I:=0 to APackage.Dependencies.Count-1 do'#013#010+
  '    begin'#013#010+
  '      D:','=APackage.Dependencies[i];'#013#010+
  '      if (D.DependencyType=depPackage) and'#013#010+
  '         (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'#013+
  #010+
  '        begin'#013#010+
  '          P:=TPackage(D.Target);'#013#010+
  '          If Assigned(P) then'#013#010+
  '            begin'#013#010+
  ' ','             if (Defaults.CPU in P.CPUs) and (Defaults.OS in P.OSes'+
  ') then'#013#010+
  '                begin'#013#010+
  '                  case P.State of'#013#010+
  '                    tsNeutral :'#013#010+
  '                      MaybeCompile(P);'#013#010+
  '                    tsConsidering ',':'#013#010+
  '                      Log(vlWarning,SWarnCircularPackageDependency,[AP'+
  'ackage.Name,P.Name]);'#013#010+
  '                    tsNoCompile,tsCompiled,tsInstalled,tsNotFound:'#013+
  #010+
  '                      ; // avoid compiler warning'#013#010+
  '                  end;'#013#010+
  ' ','               end'#013#010+
  '              else'#013#010+
  '                Log(vlWarning,SWarnDependOnOtherPlatformPackage,[APack'+
  'age.Name, D.Value, MakeTargetString(Defaults.CPU, Defaults.OS)]);'#013#010+
  '            end'#013#010+
  '          else'#013#010+
  '            begin'#013#010+
  '           ','   D.Target:=CheckExternalPackage(D.Value, APackage.Name,'+
  ' true);'#013#010+
  '              P:=TPackage(D.Target);'#013#010+
  '            end;'#013#010+
  '          if (D.RequireChecksum<>$ffffffff) and (D.RequireChecksum<>0)'+
  ' and'#013#010+
  '             (P.InstalledChecksum<>$ffffff','ff) and'#013#010+
  '             (P.InstalledChecksum<>D.RequireChecksum) then'#013#010+
  '            Log(vlWarning,SDbgPackageChecksumChanged,[APackage.Name, P'+
  '.Name]);'#013#010+
  '          APackage.InheritPackageVariantsFromDependency(P);'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010,
  #013#010+
  'function TBuildEngine.CheckDependencies(APackage: TPackage; ErrorOnFai'+
  'lure: boolean): TCheckDependencyResult;'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  D : TDependency;'#013#010+
  'begin'#013#010+
  '  result := cdAvailable;'#013#010+
  '  For I:=0 to APackage.Dependencies.','Count-1 do'#013#010+
  '    begin'#013#010+
  '      D:=APackage.Dependencies[i];'#013#010+
  '      if (D.DependencyType=depPackage) and'#013#010+
  '         (Defaults.CPU in D.CPUs) and (Defaults.OS in D.OSes) then'#013+
  #010+
  '        begin'#013#010+
  '          P:=TPackage(D.Target);'#013#010+
  '          If Assigne','d(P) then'#013#010+
  '            begin'#013#010+
  '              if (Defaults.CPU in P.CPUs) and (Defaults.OS in P.OSes) '+
  'then'#013#010+
  '                begin'#013#010+
  '                  case P.State of'#013#010+
  '                    tsNeutral :'#013#010+
  '                      result := cdNotYetAva','ilable;'#013#010+
  '                    tsConsidering :'#013#010+
  '                      Log(vlWarning,SWarnCircularPackageDependency,[AP'+
  'ackage.Name,P.Name]);'#013#010+
  '                    tsNoCompile,tsCompiled,tsInstalled,tsNotFound:'#013+
  #010+
  '                      ; // Avoid ','compiler warning'#013#010+
  '                  end;'#013#010+
  '                end'#013#010+
  '              else'#013#010+
  '                Log(vlWarning,SWarnDependOnOtherPlatformPackage,[APack'+
  'age.Name, D.Value, MakeTargetString(Defaults.CPU, Defaults.OS)]);'#013#010+
  '            end'#013#010+
  '   ','       else'#013#010+
  '            begin'#013#010+
  '              D.Target:=CheckExternalPackage(D.Value, APackage.Name, E'+
  'rrorOnFailure);'#013#010+
  '              P:=TPackage(D.Target);'#013#010+
  '            end;'#013#010+
  '          if (D.RequireChecksum<>$ffffffff) and'#013#010+
  '             (P.','InstalledChecksum<>$ffffffff) and'#013#010+
  '             (P.InstalledChecksum<>D.RequireChecksum) then'#013#010+
  '            Log(vldebug,SDbgPackageChecksumChanged,[APackage.Name, P.N'+
  'ame]);'#013#010+
  '          APackage.InheritPackageVariantsFromDependency(P);'#013#010+
  '      ','  end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Compile(APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  T : TTarget;'#013#010+
  '  I : Integer;'#013#010+
  '  aPath,UC: string;'#013#010+
  '  RegenerateUnitconfigFile: boolean;'#013#010+
  '  BUName: string;'#013#010+
  #013#010+
  '  procedure CompileBuildUnit;'#013#010+
  '  var'#013#010+
  '    ','I: Integer;'#013#010+
  '    T: TTarget;'#013#010+
  '    L: TStrings;'#013#010+
  '    F: Text;'#013#010+
  '    Dep : TDependency;'#013#010+
  '    aUnitName, aUnitSourceDir : string;'#013#010+
  '    CompilationFailed: Boolean;'#013#010+
  #013#010+
  '  begin'#013#010+
  '    if (APackage.FBUTarget.Dependencies.Count>0) then'#013#010+
  '      begin'#013#010+
  ' ','       Log(vldebug, Format(SDbgGenerateBuildUnit, [APackage.FBUTarg'+
  'et.Name]));'#013#010+
  '        aPath:=AddPathPrefix(APackage,APackage.GetUnitsOutputDir(Defau'+
  'lts.CompileTarget));'#013#010+
  '        system.Assign(F,IncludeTrailingPathDelimiter(apath)+APackage','.'+
  'FBUTarget.FTargetSourceFileName);'#013#010+
  '        Rewrite(F);'#013#010+
  '        writeln(F,'#039'unit '#039' + APackage.FBUTarget.Name +'#039';'#039+
  ');'#013#010+
  '        writeln(F,'#039'interface'#039');'#013#010+
  '        writeln(F,'#039'uses'#039');'#013#010+
  '        for i := 0 to APackage.FBUTarget.Dependencies.Count-1 ','do'#013+
  #010+
  '          begin'#013#010+
  '            if i<>0 then'#013#010+
  '              write(F,'#039','#039');'#013#010+
  '            Dep:=APackage.FBUTarget.Dependencies.Dependencies[i];'#013#010+
  '            aUnitName:=Dep.Value;'#013#010+
  #009'    aUnitSourceDir:=ExtractFileDir(Dep.TargetFileName);'#013#010+
  '    ','        if aUnitSourceDir='#039#039' then'#013#010+
  '              APackage.UnitPath.Add('#039'.'#039')'#013#010+
  '            else'#013#010+
  '              APackage.UnitPath.Add(aUnitSourceDir);'#013#010+
  '            writeln(F,aUnitName);'#013#010+
  '          end;'#013#010+
  '        writeln(F,'#039';'#039');'#013#010+
  '        writeln','(F,'#039'implementation'#039');'#013#010+
  '        writeln(F,'#039'end.'#039');'#013#010+
  #013#010+
  '        system.close(F);'#013#010+
  #013#010+
  '        APackage.FBuildMode:=bmOneByOne;'#013#010+
  '        Compilationfailed:=false;'#013#010+
  '        APackage.FBUTarget.FTargetSourceFileName:=IncludeTrailingPathD'+
  'elimiter(APa','ckage.GetUnitsOutputDir(Defaults.CompileTarget))+APackag'+
  'e.FBUTarget.FTargetSourceFileName;'#013#010+
  '        try'#013#010+
  '          try'#013#010+
  '            Compile(APackage,APackage.FBUTarget);'#013#010+
  '          except'#013#010+
  '            on E: Exception do'#013#010+
  '              begin',#013#010+
  '                Log(vlError,E.Message);'#013#010+
  '                Compilationfailed:=true;'#013#010+
  '              end;'#013#010+
  '          end;'#013#010+
  '        finally'#013#010+
  '          if CompilationFailed then'#013#010+
  '            begin'#013#010+
  '              Log(vlDebug,Format(SDbgBuildUnit','Failure,[APackage.FBUT'+
  'arget.FTargetSourceFileName]));'#013#010+
  '              // Raise failure exception again.'#013#010+
  '              Error(SErrBuildUnitCompilation,[APackage.FBUTarget.FTarg'+
  'etSourceFileName]);'#013#010+
  '            end'#013#010+
  '          else'#013#010+
  '            ','begin'#013#010+
  '            // Delete temporary build-unit files'#013#010+
  '            L := TStringList.Create;'#013#010+
  '            try'#013#010+
  '              aPath:=AddPathPrefix(APackage,APackage.GetUnitsOutputDir'+
  '(Defaults.CompileTarget));'#013#010+
  '              APackage.FBUTarg','et.GetCleanFiles(L,IncludeTrailingPath'+
  'Delimiter(aPath),'#039#039',Defaults.CompileTarget);'#013#010+
  '              L.Add(AddPathPrefix(APackage,APackage.FBUTarget.FTargetS'+
  'ourceFileName));'#013#010+
  '              CmdDeleteFiles(L);'#013#010+
  '            finally'#013#010+
  '             ',' L.Free;'#013#010+
  '            end;'#013#010+
  '          end;'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  #013#010+
  '    For I:=0 to APackage.Targets.Count-1 do'#013#010+
  '      begin'#013#010+
  '        T:=APackage.Targets.TargetItems[i];'#013#010+
  '        if (T.TargetType = ttUnit) and (TargetOK(T, Defaults.Comp','ile'+
  'Target)) then'#013#010+
  '          begin'#013#010+
  '            If Assigned(T.AfterCompile) then'#013#010+
  '              T.AfterCompile(T);'#013#010+
  '            ExecuteCommands(T.Commands,caAfterCompile);'#013#010+
  '          end'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  procedure ProcessCompileTarge','t;'#013#010+
  '  begin'#013#010+
  '    if TargetOK(T, Defaults.CompileTarget) then'#013#010+
  '      begin'#013#010+
  '        if T.State=tsNeutral then'#013#010+
  '          MaybeCompile(APackage,T);'#013#010+
  '        // If a target is compiled, re-generate the UnitConfigFile'#013+
  #010+
  '        if T.FTargetState','<>tsNoCompile then'#013#010+
  '          RegenerateUnitconfigFile:= True;'#013#010+
  '      end'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '        if not(Defaults.CPU in T.CPUs) then'#013#010+
  '          Log(vldebug, Format(SDbgSkippingTargetWrongCPU, [T.Name, CPU'+
  'sToString(T.CPUs)]));'#013#010+
  '    ','    if not(Defaults.OS in T.OSes) then'#013#010+
  '          Log(vldebug, Format(SDbgSkippingTargetWrongOS, [T.Name, OSes'+
  'ToString(T.OSes)]));'#013#010+
  '        if (Defaults.SubTarget<>'#039#039') and not T.SubTargetAllowed(D'+
  'efaults.SubTarget) then'#013#010+
  '          Log(vldeb','ug, Format(SDbgSkippingTargetWrongSubTarget, [T.N'+
  'ame, T.SubTargetsAsString]));'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  'begin'#013#010+
  '  log(vlWarning,SWarnStartCompilingPackage,[APackage.Name, Defaults.Ta'+
  'rget]);'#013#010+
  #013#010+
  '  case Defaults.BuildMode of'#013#010+
  '    bmOneByOne:  beg','in'#013#010+
  '                   if (bmOneByOne in APackage.SupportBuildModes) then'#013+
  #010+
  '                     APackage.FBuildMode:=bmOneByOne'#013#010+
  '                   else if bmBuildUnit in APackage.SupportBuildModes t'+
  'hen'#013#010+
  '                     begin'#013#010+
  '        ','               log(vlInfo,SInfoFallbackBuildmodeBU);'#013#010+
  '                       APackage.FBuildMode:=bmBuildUnit;'#013#010+
  '                     end'#013#010+
  '                   else'#013#010+
  '                     raise exception.create(SErrUnsupportedBuildmode);'+
  #013#010+
  '     ','            end;'#013#010+
  '    bmBuildUnit: begin'#013#010+
  '                   // When bmBuildUnit is supported by the package use'+
  ' a buildunit.'#013#010+
  '                   // Unless there is only one target and bmOneByOne i'+
  's also supported'#013#010+
  '                   if (bm','BuildUnit in APackage.SupportBuildModes) an'+
  'd'#013#010+
  '                      not ((APackage.Targets.Count=1) and (bmOneByOne '+
  'in APackage.SupportBuildModes)) then'#013#010+
  '                     APackage.FBuildMode:=bmBuildUnit'#013#010+
  '                   else if bmOn','eByOne in APackage.SupportBuildModes '+
  'then'#013#010+
  '                     begin'#013#010+
  '                       log(vlInfo,SInfoFallbackBuildmode);'#013#010+
  '                       APackage.FBuildMode:=bmOneByOne'#013#010+
  '                     end'#013#010+
  '                   else'#013#010+
  '  ','                   raise exception.create(SErrUnsupportedBuildmode'+
  ');'#013#010+
  '                 end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  GPathPrefix:=APackage.Directory;'#013#010+
  '  Try'#013#010+
  '    CreateOutputDir(APackage);'#013#010+
  '    AddPackageMacrosToDictionary(APackage, APackage.Dictionary',');'#013+
  #010+
  '    DoBeforeCompile(APackage);'#013#010+
  '    RegenerateUnitconfigFile:=False;'#013#010+
  '    if APackage.BuildMode=bmBuildUnit then'#013#010+
  '      begin'#013#010+
  '        APackage.FBUTargets := TTargets.Create(TTarget);'#013#010+
  '        if (Defaults.BuildOS in AllLimit83fsOses) o','r'#013#010+
  '           (Defaults.OS in AllLimit83fsOses) then'#013#010+
  '          BUName := '#039'BUnit.pp'#039#013#010+
  '        else'#013#010+
  '          BUName := '#039'BuildUnit_'#039'+StringReplace(APackage.Name,'#039+
  '-'#039','#039'_'#039',[rfReplaceAll])+'#039'.pp'#039';'#013#010+
  '        APackage.FBUTarget := APackage.FBUTarge','ts.AddUnit(BUName);'#013+
  #010+
  '        APackage.FBUTarget.FTargetSourceFileName := APackage.FBUTarget'+
  '.SourceFileName;'#013#010+
  '      end;'#013#010+
  '    For I:=0 to APackage.Targets.Count-1 do'#013#010+
  '      begin'#013#010+
  '        T:=APackage.Targets.TargetItems[i];'#013#010+
  '        case T.T','argetType of'#013#010+
  '        ttUnit:'#013#010+
  '          begin'#013#010+
  '            ProcessCompileTarget;'#013#010+
  '          end;'#013#010+
  '        ttSharedLibrary,'#013#010+
  '        ttProgram:'#013#010+
  '          begin // do nothing, are compiled later'#013#010+
  '          end;'#013#010+
  '        else'#013#010+
  '          log(','vldebug, SDbgTargetIsNotAUnitOrProgram,[T.Name]);'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  #013#010+
  '    if APackage.BuildMode=bmBuildUnit then'#013#010+
  '      CompileBuildUnit;'#013#010+
  #013#010+
  '    FreeAndNil(APackage.FBUTarget);'#013#010+
  #013#010+
  '    For I:=0 to APackage.Targets.Count-1 do'#013#010+
  '      ','begin'#013#010+
  '        T:=APackage.Targets.TargetItems[i];'#013#010+
  '        if T.TargetType in [ttProgram,ttSharedLibrary] then'#013#010+
  '          begin'#013#010+
  '            ProcessCompileTarget;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  #013#010+
  '    if RegenerateUnitconfigFile then'#013#010+
  '      b','egin'#013#010+
  '        UC:=AddPathPrefix(APackage, APackage.GetUnitConfigOutputFilena'+
  'me(Defaults.CompileTarget));'#013#010+
  '        Log(vlInfo, Format(SDbgGenerating, [UC]));'#013#010+
  '        APackage.SaveUnitConfigToFile(UC,Defaults.CPU,Defaults.OS);'#013+
  #010+
  '      end;'#013#010+
  #013,#010+
  '    DoAfterCompile(APackage);'#013#010+
  '  Finally'#013#010+
  '    GPathPrefix:='#039#039';'#013#010+
  '  end;'#013#010+
  '  inc(FProgressCount);'#013#010+
  '  if FProgressMax>0 then'#013#010+
  '    log(vlWarning,SWarnCompilingPackagecompleteProgress,[(FProgressCou'+
  'nt)/FProgressMax * 100, APackage.Name])'#013#010+
  '  else',#013#010+
  '    log(vlWarning,SWarnCompilingPackagecomplete,[APackage.Name]);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.MaybeCompile(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  if ReadyToCompile(APackage) then'#013#010+
  '    begin'#013#010+
  '      Compile(APackage);'#013#010+
  '      APackage.FTargetSta','te:=tsCompiled;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.ReadyToCompile(APackage: TPackage) : Boolean;'#013+
  #010+
  'begin'#013#010+
  '  result := False;'#013#010+
  '  if APackage.State in [tsCompiled, tsNoCompile] then'#013#010+
  '    begin'#013#010+
  '      Log(vlInfo,SInfoPackageAlreadyProcess','ed,[APackage.Name]);'#013#010+
  '      Exit;'#013#010+
  '    end;'#013#010+
  '  if APackage.State<>tsNeutral then'#013#010+
  '    Error(SErrInvalidState,[APackage.Name]);'#013#010+
  '  Log(vlDebug,SDbgConsideringPackage,[APackage.Name]);'#013#010+
  '  try'#013#010+
  '  LogIndent;'#013#010+
  '  if Defaults.ThreadsAmount=-1 then',#013#010+
  '    APackage.FTargetState:=tsConsidering;'#013#010+
  '  ResolveDependencies(APackage.Dependencies,(APackage.Collection as TP'+
  'ackages));'#013#010+
  '  // When multiple threads are used, delay the compilation of the pack'+
  'age when'#013#010+
  '  // there are unsolved dependenc','ies. When no threads are used, comp'+
  'ile all'#013#010+
  '  // dependencies.'#013#010+
  #013#010+
  '  if Defaults.ThreadsAmount=-1 then'#013#010+
  '    CompileDependencies(APackage)'#013#010+
  '  else if CheckDependencies(APackage, true)=cdNotYetAvailable then'#013+
  #010+
  '    begin'#013#010+
  '      log(vlInfo,'#039'Delay','ing package '#039'+apackage.name);'#013#010+
  '      //LogUnIndent; Done in Finally below'#013#010+
  '      result := False;'#013#010+
  '      Exit;'#013#010+
  '    end;'#013#010+
  '  APackage.SetDefaultPackageVariant;'#013#010+
  #013#010+
  '  ResolveFileNames(APackage,Defaults.CPU,Defaults.OS,True,False);'#013#010+
  '  If NeedsC','ompile(APackage) then'#013#010+
  '    result := True'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      APackage.FTargetState:=tsNoCompile;'#013#010+
  '      inc(FProgressCount);'#013#010+
  '    end;'#013#010+
  '  finally'#013#010+
  '  LogUnIndent;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TBuildEngine.InstallPackageFiles(APAckage: ','TPackage; tt: TT'+
  'argetTypes;'#013#010+
  '  const Dest: String; const InstallMode: TInstallMode): Boolean;'#013#010+
  'Var'#013#010+
  '  List : TStringList;'#013#010+
  'begin'#013#010+
  '  Result:=False;'#013#010+
  '  List:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '    APackage.GetInstallFiles(List,tt,Defaults.CompileTar','get);'#013#010+
  '    if (List.Count>0) then'#013#010+
  '      begin'#013#010+
  '        Result:=True;'#013#010+
  '        case InstallMode of'#013#010+
  '          imInstall:   CmdCopyFiles(List,Dest,APackage);'#013#010+
  '          imUnInstall: CmdDeleteDestFiles(List,Dest);'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  ' ',' Finally'#013#010+
  '    List.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.GetUnitConfigFilesInstallDir(ABaseDir: string): '+
  'String;'#013#010+
  'begin'#013#010+
  '  result := FixPath(ABaseDir,True)+Defaults.UnitConfigFilesInstallDir;'+
  #013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.InstallUn','itConfigFile(APAckage: TPackage; con'+
  'st Dest: String);'#013#010+
  'Var'#013#010+
  '  List : TStringList;'#013#010+
  '  ConfigFileName: String;'#013#010+
  '  ConfigFileContent: TStrings;'#013#010+
  '  Index: integer;'#013#010+
  'begin'#013#010+
  '  ConfigFileName:=APackage.GetUnitConfigOutputFilename(Defaults.Compil'+
  'eT','arget);'#013#010+
  '  List:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '    if Defaults.FPUnitSourcePath<>'#039#039' then'#013#010+
  '      begin'#013#010+
  '        ConfigFileContent := TStringList.Create;'#013#010+
  '        try'#013#010+
  '          ConfigFileContent.LoadFromFile(AddPathPrefix(APAckage, Confi'+
  'gFileN','ame));'#013#010+
  '          if Defaults.FPUnitSourcePath='#039'0'#039' then'#013#010+
  '            begin'#013#010+
  '              Index := ConfigFileContent.IndexOfName(KeySourcePath);'#013+
  #010+
  '              if Index > -1 then'#013#010+
  '                ConfigFileContent.Delete(Index)'#013#010+
  '           ',' end'#013#010+
  '          else'#013#010+
  '            ConfigFileContent.Values[KeySourcePath] := Defaults.FPUnit'+
  'SourcePath;'#013#010+
  '          ConfigFileContent.SaveToFile(AddPathPrefix(APAckage, ConfigF'+
  'ileName));'#013#010+
  '        finally'#013#010+
  '          ConfigFileContent.Free;'#013#010+
  ' ','       end;'#013#010+
  '      end;'#013#010+
  '    List.Values[ConfigFileName] := APAckage.Name + FpmkExt;'#013#010+
  '    CmdCopyFiles(List,Dest,APackage);'#013#010+
  '  Finally'#013#010+
  '    List.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TBuildEngine.InstallPackageSourceFiles(APAckage: TPackage;'#013+
  #010+
  '  s','tt: TSourceTypes; ttt: TTargetTypes; const Dest: String;'#013#010+
  '  const InstallMode: TInstallMode): Boolean;'#013#010+
  'Var'#013#010+
  '  List : TStringList;'#013#010+
  'begin'#013#010+
  '  Result:=False;'#013#010+
  '  List:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '    APackage.GetInstallSourceFiles(List,stt,ttt',');'#013#010+
  '    if (List.Count>0) then'#013#010+
  '      begin'#013#010+
  '        Result:=True;'#013#010+
  '        case InstallMode of'#013#010+
  '          imInstall:   CmdCopyFiles(List,Dest,APackage);'#013#010+
  '          imUnInstall: CmdDeleteDestFiles(List,Dest);'#013#010+
  '        end;'#013#010+
  '      end;'#013#010+
  '  Fi','nally'#013#010+
  '    List.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoBeforeInstall(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  ExecuteCommands(APackage.Commands,caBeforeInstall);'#013#010+
  '  If Assigned(APackage.BeforeInstall) then'#013#010+
  '    APackage.BeforeInstall(APack','age);'#013#010+
  '  If Assigned(APackage.BeforeInstallProc) then'#013#010+
  '    APackage.BeforeInstallProc(APackage);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoAfterInstall(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  If Assigned(APackage.AfterInstall) then'#013#010+
  '    APackage.AfterInst','all(APackage);'#013#010+
  '  If Assigned(APackage.AfterInstallProc) then'#013#010+
  '    APackage.AfterInstallProc(APackage);'#013#010+
  '  ExecuteCommands(APackage.Commands,caAfterInstall);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Install(APackage: TPackage; AnArchiveFiles: boo'+
  'l','ean);'#013#010+
  'Var'#013#010+
  '  D : String;'#013#010+
  '  B : Boolean;'#013#010+
  'begin'#013#010+
  '  If (Apackage.State<>tsCompiled) then'#013#010+
  '    MaybeCompile(APackage);'#013#010+
  '  Log(vlCommand,SInfoInstallingPackage,[APackage.Name]);'#013#010+
  '  if AnArchiveFiles then'#013#010+
  '    FinishArchive(APackage);'#013#010+
  '  try'#013#010,
  '    If (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := APackage.Directory;'#013#010+
  '    if AnArchiveFiles then'#013#010+
  '      begin'#013#010+
  '        FOnCopyFile:=@AddFileToArchive;'#013#010+
  '        FOnFinishCopy:=@FinishArchive;'#013#010+
  '      end;'#013#010+
  '    DoBeforeInstall(APacka','ge);'#013#010+
  '    // units'#013#010+
  '    B:=false;'#013#010+
  '    AddPackageMacrosToDictionary(APackage, APackage.Dictionary);'#013#010+
  '    GlobalDictionary.AddVariable('#039'unitinstalldir'#039', FixPath(APa'+
  'ckage.Dictionary.ReplaceStrings(Defaults.UnitInstallDir), False));'#013+
  #010+
  '    Globa','lDictionary.AddVariable('#039'packageunitinstalldir'#039',APa'+
  'ckage.GetPackageUnitInstallDir(Defaults.CPU,Defaults.OS, Defaults.SubT'+
  'arget));'#013#010+
  #013#010+
  '    D:=FixPath(Defaults.Prefix,true);'#013#010+
  '    // This is to install the TPackage.Installfiles, which are not r','e'+
  'lated to any'#013#010+
  '    // target'#013#010+
  '    if InstallPackageFiles(APackage,[],D, imInstall) then'#013#010+
  '      B:=true;'#013#010+
  '    D:=FixPath(APackage.Dictionary.ReplaceStrings(Defaults.UnitInstall'+
  'Dir), True)+ExcludeLeadingPathDelimiter(APackage.GetPackageUnitIn','sta'+
  'llDir(Defaults.CPU,Defaults.OS, Defaults.SubTarget));'#013#010+
  '    if InstallPackageFiles(APackage,[ttUnit, ttImplicitUnit],D, imInst'+
  'all) then'#013#010+
  '      B:=true;'#013#010+
  '    // By default do not install the examples. Maybe add an option for'+
  ' this later'#013#010+
  '  ','  //if InstallPackageFiles(APAckage,ttExampleUnit,D) then'#013#010+
  '    //  B:=true;'#013#010+
  '    // Unit (dependency) configuration if there were units installed'#013+
  #010+
  '    D:=FixPath(APackage.Dictionary.ReplaceStrings(GetUnitConfigFilesIn'+
  'stallDir(Defaults.BaseI','nstallDir)), True);'#013#010+
  '    if B then'#013#010+
  '      InstallUnitConfigFile(APackage,D);'#013#010+
  '    // Programs'#013#010+
  '    D:=IncludeTrailingPathDelimiter(Defaults.BinInstallDir);'#013#010+
  '    InstallPackageFiles(APAckage,[ttProgram],D, imInstall);'#013#010+
  '    // Shared librarie','s'#013#010+
  '    D:=IncludeTrailingPathDelimiter(Defaults.LibInstallDir);'#013#010+
  '    InstallPackageFiles(APAckage,[ttSharedLibrary],D, imInstall);'#013#010+
  '    //InstallPackageFiles(APAckage,ttExampleProgram,D);'#013#010+
  '    // Documentation'#013#010+
  '    D:=FixPath(APackage.Dicti','onary.ReplaceStrings(Defaults.DocInstal'+
  'lDir), True);'#013#010+
  '    InstallPackageSourceFiles(APackage,[stDoc],[],D, imInstall);'#013#010+
  '    // Examples'#013#010+
  '    if Defaults.InstallExamples then'#013#010+
  '      begin'#013#010+
  '        D:=FixPath(APackage.Dictionary.ReplaceString','s(Defaults.Examp'+
  'lesInstallDir), True);'#013#010+
  '        InstallPackageSourceFiles(APackage,[stExample],[ttExampleProgr'+
  'am,ttExampleUnit],D, imInstall);'#013#010+
  '      end;'#013#010+
  '    // Done.'#013#010+
  '    APackage.FTargetState:=tsInstalled;'#013#010+
  '    DoAfterInstall(APackage);',#013#010+
  '    if AnArchiveFiles then'#013#010+
  '      begin'#013#010+
  '      FOnCopyFile:=nil;'#013#010+
  '      FOnFinishCopy:=nil;'#013#010+
  '      end;'#013#010+
  '  Finally'#013#010+
  '    If (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := '#039#039';'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.UnInstall(APackag','e: TPackage);'#013#010+
  'Var'#013#010+
  '  D : String;'#013#010+
  'begin'#013#010+
  '  CheckDependencies(APackage, False);'#013#010+
  '  ResolvePackagePaths(APackage);'#013#010+
  '  APackage.SetDefaultPackageVariant;'#013#010+
  '  If (Apackage.State<>tsInstalled) then'#013#010+
  '    begin'#013#010+
  '    Error(SErrorPkgNotInstalled,[AP','ackage.Name]);'#013#010+
  '    exit;'#013#010+
  '    end;'#013#010+
  '  Log(vlCommand,SInfoUnInstallingPackage,[APackage.Name]);'#013#010+
  #013#010+
  '  //DoBeforeUnInstall(APackage);'#013#010+
  #013#010+
  '  // units'#013#010+
  '  AddPackageMacrosToDictionary(APackage, APackage.Dictionary);'#013#010+
  '  GlobalDictionary.AddVariabl','e('#039'unitinstalldir'#039', FixPath(APa'+
  'ckage.Dictionary.ReplaceStrings(Defaults.UnitInstallDir), False));'#013+
  #010+
  '  GlobalDictionary.AddVariable('#039'packageunitinstalldir'#039',APackag'+
  'e.GetPackageUnitInstallDir(Defaults.CPU,Defaults.OS, Defaults.SubTarge'+
  't));'#013#010+
  #013#010+
  ' ',' D:=FixPath(Defaults.Prefix,true);'#013#010+
  '  // This is to uninstall the TPackage.Installfiles, which are not rel'+
  'ated to any'#013#010+
  '  // target'#013#010+
  '  InstallPackageFiles(APackage,[],D,imUnInstall);'#013#010+
  '  D:=FixPath(APackage.Dictionary.ReplaceStrings(Defaults.','UnitInstall'+
  'Dir), True)+APackage.GetPackageUnitInstallDir(Defaults.CPU,Defaults.OS'+
  ', Defaults.SubTarget);'#013#010+
  '  InstallPackageFiles(APackage,[ttUnit, ttImplicitUnit],D, imUnInstall'+
  ');'#013#010+
  '  SysDeleteDirectory(D);'#013#010+
  #013#010+
  '  // Unit (dependency) configurat','ion'#013#010+
  '  D:=FixPath(APackage.Dictionary.ReplaceStrings(GetUnitConfigFilesInst'+
  'allDir(Defaults.BaseInstallDir)), True);'#013#010+
  '  SysDeleteFile(D+APackage.Name+FpmkExt);'#013#010+
  #013#010+
  '  // Programs'#013#010+
  '  D:=IncludeTrailingPathDelimiter(Defaults.BinInstallDir);'#013#010+
  '  I','nstallPackageFiles(APAckage,[ttProgram],D, imUnInstall);'#013#010+
  '  SysDeleteDirectory(D);'#013#010+
  '  // Libraries'#013#010+
  '  D:=IncludeTrailingPathDelimiter(Defaults.LibInstallDir);'#013#010+
  '  InstallPackageFiles(APAckage,[ttSharedLibrary],D, imUnInstall);'#013#010+
  '  SysDeleteDi','rectory(D);'#013#010+
  '  // Documentation'#013#010+
  '  D:=FixPath(APackage.Dictionary.ReplaceStrings(Defaults.DocInstallDir'+
  '), True);'#013#010+
  '  InstallPackageSourceFiles(APackage,[stDoc],[],D, imUnInstall);'#013#010+
  '  SysDeleteDirectory(D);'#013#010+
  '  // Examples'#013#010+
  '  if Defaults.Insta','llExamples then'#013#010+
  '    begin'#013#010+
  '      D:=FixPath(APackage.Dictionary.ReplaceStrings(Defaults.ExamplesI'+
  'nstallDir), True);'#013#010+
  '      InstallPackageSourceFiles(APackage,[stExample],[ttExampleProgram'+
  ',ttExampleUnit],D, imUnInstall);'#013#010+
  '      SysDeleteDir','ectory(D);'#013#010+
  '    end;'#013#010+
  '  // Done.'#013#010+
  '  APackage.FTargetState:=tsNeutral;'#013#010+
  #013#010+
  '  //DoAfterUnInstall(APackage);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoBeforeArchive(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  ExecuteCommands(APackage.Commands,caBeforeArchive);'#013#010+
  ' ',' If Assigned(APackage.BeforeArchive) then'#013#010+
  '    APackage.BeforeArchive(APackage);'#013#010+
  '  If Assigned(APackage.BeforeArchiveProc) then'#013#010+
  '    APackage.BeforeArchiveProc(APackage);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoAfterArchive(APackage: TPackage)',';'#013#010+
  'begin'#013#010+
  '  If Assigned(APackage.AfterArchive) then'#013#010+
  '    APackage.AfterArchive(APackage);'#013#010+
  '  If Assigned(APackage.AfterArchiveProc) then'#013#010+
  '    APackage.AfterArchiveProc(APackage);'#013#010+
  '  ExecuteCommands(APackage.Commands,caAfterArchive);'#013#010+
  'end;'#013#010,
  #013#010+
  #013#010+
  'procedure TBuildEngine.Archive(APackage: TPackage);'#013#010+
  'Var'#013#010+
  '  L : TStringList;'#013#010+
  '  A : String;'#013#010+
  '  i: integer;'#013#010+
  '  ICPU : TCPU;'#013#010+
  '  IOS  : TOS;'#013#010+
  '  aTarget : TCompileTarget;'#013#010+
  '{$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '  ZipFile: TZipper;'#013#010+
  '{$endif HAS_UNIT_ZIPP','ER}'#013#010+
  'begin'#013#010+
  '  A:=Defaults.ZipPrefix + APackage.FileName + MakeZipSuffix(cpuNone, o'+
  'sNone) + ZipExt;'#013#010+
  '  Log(vlInfo,SInfoArchivingPackage,[APackage.Name,A]);'#013#010+
  '  try'#013#010+
  '    If (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := APackage.Directory',';'#013#010+
  '    DoBeforeArchive(Apackage);'#013#010+
  '    AddPackageMacrosToDictionary(APackage, APackage.Dictionary);'#013#010+
  '    L:=TStringList.Create;'#013#010+
  '    L.Sorted:=true;'#013#010+
  '    L.Duplicates:=dupIgnore;'#013#010+
  '    Try'#013#010+
  '      // Add fpmake.pp & manifest.xml always'#013#010+
  '     ',' L.Add(FPMakePPFile);'#013#010+
  '      L.Add(ManifestFile);'#013#010+
  '      //get all files from all targets'#013#010+
  '      for ICPU:=Low(TCPU) to high(TCPU) do'#013#010+
  '        for IOS:=Low(TOS) to high(TOS) do'#013#010+
  '          if OSCPUSupported[IOS,ICPU] then'#013#010+
  '            begin'#013,#010+
  '              aTarget.OS:=IOS;'#013#010+
  '              aTarget.CPU:=ICPU;'#013#010+
  '              aTarget.Subtarget:='#039#039';'#013#010+
  '            // Make sure that the package is resolved for each target'#013+
  #010+
  '              ClearResolvedFileNames(APackage);'#013#010+
  '              R','esolveFileNames(APackage,ICPU,IOS,false);'#013#010+
  '              APackage.GetArchiveFiles(L,aTarget);'#013#010+
  '            end;'#013#010+
  '      //from sources'#013#010+
  '      APackage.GetArchiveSourceFiles(L);'#013#010+
  #013#010+
  '      //show all files'#013#010+
  '      for i := 0 to L.Count-1 do'#013#010+
  '   ','     Log(vlDebug, Format(SDbgArchivingFile, [L[i]]));'#013#010+
  #013#010+
  '{$ifdef HAS_UNIT_ZIPPER}'#013#010+
  '      if not Assigned(ArchiveFilesProc) then'#013#010+
  '        begin'#013#010+
  '          ZipFile := TZipper.Create;'#013#010+
  '          try'#013#010+
  '            ZipFile.FileName:=A;'#013#010+
  '         ','   A := APackage.Dictionary.ReplaceStrings(Defaults.FPrefix'+
  ');'#013#010+
  '            if A <> '#039#039' then'#013#010+
  '              A:=IncludeTrailingPathDelimiter(A);'#013#010+
  '            for i := 0 to L.Count-1 do'#013#010+
  '              begin'#013#010+
  '                ZipFile.Entries.AddF','ileEntry(AddPathPrefix(APackage,'+
  ' L[i]), A+L[i]);'#013#010+
  '              end;'#013#010+
  '            ZipFile.ZipAllFiles;'#013#010+
  '          finally'#013#010+
  '            ZipFile.Free;'#013#010+
  '          end;'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '{$endif HAS_UNIT_ZIPPER}'#013#010+
  '        CmdArchiveFiles','(L,A);'#013#010+
  '    Finally'#013#010+
  '      L.Free;'#013#010+
  '    end;'#013#010+
  '    DoAfterArchive(Apackage);'#013#010+
  '  Finally'#013#010+
  '    If (APackage.Directory<>'#039#039') then'#013#010+
  '      GPathPrefix := '#039#039';'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.DoBeforeClean(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  Ex','ecuteCommands(APackage.Commands,caBeforeClean);'#013#010+
  '  If Assigned(APackage.BeforeClean) then'#013#010+
  '    APackage.BeforeClean(APackage);'#013#010+
  '  If Assigned(APackage.BeforeCleanProc) then'#013#010+
  '    APackage.BeforeCleanProc(APackage);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuil','dEngine.DoAfterClean(APackage: TPackage);'#013#010+
  'begin'#013#010+
  '  If Assigned(APackage.AfterClean) then'#013#010+
  '    APackage.AfterClean(APackage);'#013#010+
  '  If Assigned(APackage.AfterCleanProc) then'#013#010+
  '    APackage.AfterCleanProc(APackage);'#013#010+
  '  ExecuteCommands(APackage.C','ommands,caAfterClean);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Clean(APackage: TPackage; AllTargets: boolean);'+
  #013#010+
  'var'#013#010+
  '  ACPU: TCpu;'#013#010+
  '  AOS: TOS;'#013#010+
  '  aTarget : TCompileTarget;'#013#010+
  '  DirectoryList : TStringList;'#013#010+
  '  aDir : string;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if not AllT','argets and (not(Defaults.OS in APackage.OSes) or'#013#010+
  '     not (Defaults.CPU in APackage.CPUs))  then'#013#010+
  '    exit;'#013#010+
  '  aTarget:=Default(TCompileTarget);'#013#010+
  '  Log(vlInfo,SInfoCleaningPackage,[APackage.Name]);'#013#010+
  '  try'#013#010+
  '    If (APackage.Directory<>'#039#039') t','hen'#013#010+
  '      EnterDir(APackage.Directory);'#013#010+
  '    // Check for inherited options (packagevariants) from other packag'+
  'es'#013#010+
  '    if (Defaults.OS in APackage.OSes) and (Defaults.CPU in APackage.CP'+
  'Us) then'#013#010+
  '      begin'#013#010+
  '        ResolveDependencies(APa','ckage.Dependencies, (APackage.Collect'+
  'ion as TPackages));'#013#010+
  '        CheckDependencies(APackage, False);'#013#010+
  '        APackage.SetDefaultPackageVariant;'#013#010+
  '      end;'#013#010+
  '    DoBeforeClean(Apackage);'#013#010+
  '    AddPackageMacrosToDictionary(APackage, APackage','.Dictionary);'#013+
  #010+
  '    if AllTargets then'#013#010+
  '      begin'#013#010+
  '        // Remove the unit-and bin-directories completely. This is saf'+
  'er in case of files'#013#010+
  '        // being renamed and such. See also bug 19655'#013#010+
  '        DirectoryList := TStringList.Creat','e;'#013#010+
  '        try'#013#010+
  '          for ACPU:=low(TCpu) to high(TCpu) do if ACPU<>cpuNone then'#013+
  #010+
  '            for AOS:=low(TOS) to high(TOS) do if AOS<>osNone then'#013#010+
  '              begin'#013#010+
  '                aTarget.OS:=aOS;'#013#010+
  '                aTarget.CPU:=aC','PU;'#013#010+
  '                if OSCPUSupported[AOS,ACPU] and (AOS in APackage.OSes)'+
  ' and'#013#010+
  '                   (ACPU in APackage.CPUs) then'#013#010+
  '                  begin'#013#010+
  '                    // First perform a normal clean, to be sure that a'+
  'll files'#013#010+
  '     ','               // which are not in the units- or bin-dir are cl'+
  'eaned. (like'#013#010+
  '                    // the .fpm file)'#013#010+
  '                    aTarget.SubTarget:=Defaults.SubTarget;'#013#010+
  '                    Clean(APackage, aTarget);'#013#010+
  '                 ','   aTarget.SubTarget:='#039#039';'#013#010+
  '                    DirectoryList.Add(ExtractFileDir(APackage.GetUnits'+
  'OutputDir(aTarget)));'#013#010+
  '                    // We don'#039't know the full list of subtargets. '+
  'So we detect existing CPU-OS-NN directories.'#013#010+
  '        ','            For aDir in GetSubTargetDirs(APackage.GetUnitsOu'+
  'tputDir(aTarget)) do'#013#010+
  '                      DirectoryList.Add(aDir);'#013#010+
  '                    DirectoryList.Add(ExtractFileDir(APackage.GetBinOu'+
  'tputDir(aTarget)));'#013#010+
  '                   ',' For aDir in GetSubTargetDirs(APackage.GetUnitsOu'+
  'tputDir(aTarget)) do'#013#010+
  '                      DirectoryList.Add(aDir);'#013#010+
  '                  end;'#013#010+
  '              end;'#013#010+
  '          CmdRemoveTrees(DirectoryList);'#013#010+
  '        finally'#013#010+
  '          Director','yList.Free;'#013#010+
  '        end;'#013#010+
  '      end'#013#010+
  '    else'#013#010+
  '      Clean(APackage, Defaults.CompileTarget);'#013#010+
  '    DoAfterClean(Apackage);'#013#010+
  '  Finally'#013#010+
  '    log(vlInfo, SInfoCleanPackagecomplete, [APackage.Name]);'#013#010+
  '    If (APackage.Directory<>'#039#039') then'#013#010+
  '    ','  EnterDir('#039#039');'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.Clean(APackage: TPackage; const aTarget : TComp'+
  'ileTarget);'#013#010+
  'Var'#013#010+
  '  List,List2 : TStringList;'#013#010+
  '  DirectoryList : TStringList;'#013#010+
  '  RemainingList : TStrings;'#013#010+
  '  i : longint;'#013#010+
  'begin'#013#010+
  '  List',':=TUnsortedDuplicatesStringList.Create;'#013#010+
  '  List.Duplicates:=DupIgnore;'#013#010+
  '  try'#013#010+
  '    List.Add(APackage.GetUnitConfigOutputFilename(aTarget));'#013#010+
  '    APackage.GetCleanFiles(List,aTarget);'#013#010+
  '    if (List.Count>0) then'#013#010+
  '      begin'#013#010+
  '      CmdDelete','Files(List);'#013#010+
  '      DirectoryList:=TUnsortedDuplicatesStringList.Create;'#013#010+
  '      DirectoryList.Duplicates:=DupIgnore;'#013#010+
  '      try'#013#010+
  '        GetDirectoriesFromFilelist(List,DirectoryList);'#013#010+
  '        CmdRemoveDirs(DirectoryList);'#013#010+
  #013#010+
  '        Direc','toryList.Clear;'#013#010+
  '        if DirectoryExists(APackage.GetBinOutputDir(aTarget)) then'#013+
  #010+
  '          DirectoryList.Add(APackage.GetBinOutputDir(aTarget));'#013#010+
  '        if DirectoryExists(APackage.GetUnitsOutputDir(aTarget)) then'#013+
  #010+
  '          DirectoryL','ist.Add(APackage.GetUnitsOutputDir(aTarget));'#013+
  #010+
  '        CmdRemoveDirs(DirectoryList);'#013#010+
  #013#010+
  '        DirectoryList.Clear;'#013#010+
  #013#010+
  '        { force directory removal for units and bin dir if it ends wit'+
  'h /$fpc_target }'#013#010+
  '        if DirectoryExists(APack','age.GetBinOutputDir(aTarget)) and'#013+
  #010+
  '           (MakeTargetString(aTarget)=ExtractFileName(ExcludeTrailingP'+
  'athDelimiter(APackage.GetBinOutputDir(aTarget)))) then'#013#010+
  '          begin'#013#010+
  '            Installer.Log(vlWarning,Format(SWarnRemovedNonEmpt','yDirec'+
  'tory,[APackage.Directory+APackage.GetBinOutputDir(aTarget)]));'#013#010+
  '            DirectoryList.Add(APackage.GetBinOutputDir(aTarget));'#013#010+
  '            RemainingList := TStringList.Create;'#013#010+
  '            List2:=TStringList.Create;'#013#010+
  '            S','earchFiles(AllFilesMask, APackage.GetBinOutputDir(aTarg'+
  'et), true, RemainingList);'#013#010+
  '            for i:=0 to RemainingList.Count-1 do'#013#010+
  '              begin'#013#010+
  '                if ExtractFileExt(Remaininglist[i])=PPUExt then'#013#010+
  '                  Ins','taller.log(vlDebug,format('#039'File %s still pr'+
  'esent, add corresponding entry to fpmake'#039',[RemainingList[i]]))'#013+
  #010+
  '                else'#013#010+
  '                  Installer.log(vlDebug,format('#039'File %s still pres'+
  'ent'#039',[RemainingList[i]]));'#013#010+
  '                L','ist2.Add(IncludeTrailingPathDelimiter(APackage.GetU'+
  'nitsOutputDir(aTarget))+Remaininglist[i]);'#013#010+
  '              end;'#013#010+
  '            CmdDeleteFiles(List2);'#013#010+
  '            List2.Free;'#013#010+
  '            RemainingList.Free;'#013#010+
  '            CmdRemoveTrees(Dire','ctoryList);'#013#010+
  '            DirectoryList.Clear;'#013#010+
  '          end;'#013#010+
  '        if DirectoryExists(APackage.GetUnitsOutputDir(aTarget)) and'#013+
  #010+
  '           (MakeTargetString(aTarget)=ExtractFileName(ExcludeTrailingP'+
  'athDelimiter(APackage.GetUnitsOutputDi','r(aTarget)))) then'#013#010+
  '          begin'#013#010+
  '            Installer.Log(vlWarning,Format(SWarnRemovedNonEmptyDirecto'+
  'ry,[APackage.Directory+APackage.GetUnitsOutputDir(aTarget)]));'#013#010+
  '            DirectoryList.Add(APackage.GetUnitsOutputDir(aTarget));'#013+
  #010,
  '            RemainingList := TStringList.Create;'#013#010+
  '            List2:=TStringList.Create;'#013#010+
  '            SearchFiles(AllFilesMask, APackage.GetUnitsOutputDir(aTarg'+
  'et), true, RemainingList);'#013#010+
  '            for i:=0 to RemainingList.Count-1 do'#013#010+
  '  ','            begin'#013#010+
  '                if ExtractFileExt(Remaininglist[i])=PPUExt then'#013#010+
  '                  Installer.log(vlDebug,format('#039'File %s still pres'+
  'ent, add corresponding entry to fpmake'#039',[RemainingList[i]]))'#013#010+
  '                else'#013#010+
  '      ','            Installer.log(vlDebug,format('#039'File %s still pr'+
  'esent'#039',[RemainingList[i]]));'#013#010+
  '                List2.Add(IncludeTrailingPathDelimiter(APackage.GetUni'+
  'tsOutputDir(aTarget))+RemainingList[i]);'#013#010+
  '              end;'#013#010+
  '            CmdDelet','eFiles(List2);'#013#010+
  '            List2.free;'#013#010+
  '            RemainingList.Free;'#013#010+
  '            CmdRemoveTrees(DirectoryList);'#013#010+
  '            DirectoryList.Clear;'#013#010+
  '          end;'#013#010+
  '        { Also remove units/ or bin/ directory if empty }'#013#010+
  '        if Is','DirectoryEmpty(ExtractFileDir(ExcludeTrailingPathDelimi'+
  'ter(APackage.GetBinOutputDir(aTarget)))) then'#013#010+
  '          DirectoryList.Add(ExtractFileDir(ExcludeTrailingPathDelimite'+
  'r(APackage.GetBinOutputDir(aTarget))));'#013#010+
  '        if IsDirectoryEmpty','(ExtractFileDir(ExcludeTrailingPathDelimi'+
  'ter(APackage.GetUnitsOutputDir(aTarget)))) then'#013#010+
  '          DirectoryList.Add(ExtractFileDir(ExcludeTrailingPathDelimite'+
  'r(APackage.GetUnitsOutputDir(aTarget))));'#013#010+
  '        CmdRemoveDirs(DirectoryList);',#013#010+
  '      finally'#013#010+
  '        DirectoryList.Free;'#013#010+
  '      end;'#013#010+
  '      end;'#013#010+
  '  Finally'#013#010+
  '    List.Free;'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.PkgList(PkgList: TStrings; APackage: TPackage);'+
  #013#010+
  'begin'#013#010+
  '  Log(vlInfo, Format(SInfoPkgListPackage,[APac','kage.Name]));'#013#010+
  '  APackage.ListPackage(PkgList);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Compile(Packages: TPackages);'#013#010+
  #013#010+
  '  function IsReadyToCompile(APackage:TPackage): boolean;'#013#010+
  '  begin'#013#010+
  '    result := False;'#013#010+
  '    if not APackage.FProcessing and ','(APackage.State=tsNeutral) then'#013+
  #010+
  '      begin'#013#010+
  '        if PackageOK(APackage) then'#013#010+
  '          result := ReadyToCompile(APackage)'#013#010+
  '        else'#013#010+
  '          begin'#013#010+
  '            inc(FProgressCount);'#013#010+
  '            log(vlInfo,SInfoSkipPackageTargetP','rogress,[(FProgressCou'+
  'nt)/FProgressMax * 100, APackage.Name, Defaults.Target]);'#013#010+
  '            APackage.FTargetState:=tsNoCompile;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  'Var'#013#010+
  '  I : integer;'#013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  Thr, ThreadCount : Intege','r;'#013#010+
  '  Finished : boolean;'#013#010+
  '  ErrorState: boolean;'#013#010+
  '  ErrorMessage: string;'#013#010+
  '  NotifyThreadWaiting : PRTLEvent;'#013#010+
  '  Threads : array of TCompileWorkerThread;'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '  P : TPackage;'#013#010+
  #013#010+
  '{$ifndef NO_THREADING}'#013#010+
  '  procedure Proces','sThreadResult(ATHread: TCompileWorkerThread);'#013#010+
  '  var'#013#010+
  '    StartI: integer;'#013#010+
  '    CompilePackage: TPackage;'#013#010+
  '    PackageAvailable: boolean;'#013#010+
  '  begin'#013#010+
  '    if AThread.Done then'#013#010+
  '      begin'#013#010+
  '        { synchronise with the WriteBarrier in the th','read (-> ReadBa'+
  'rrier), and prevent'#013#010+
  '          any writes we do here afterwards to be reordered before that'+
  ' (so the compile'#013#010+
  '          thread won'#039't see these writes either -> also WriteBarrie'+
  'r) }'#013#010+
  '        ReadWriteBarrier;'#013#010+
  '        if assign','ed(AThread.APackage) then'#013#010+
  '          begin'#013#010+
  '            // The thread has completed compiling the package'#013#010+
  '            if AThread.CompilationOK then'#013#010+
  '              AThread.APackage.FTargetState:=tsCompiled'#013#010+
  '            else // A problem occ','urred, stop the compilation'#013#010+
  '              begin'#013#010+
  '              ErrorState:=true;'#013#010+
  '              ErrorMessage:='#039'Error inside worker thread for packag'+
  'e '#039'+Athread.APackage.Name+'#039': '#039'+AThread.ErrorMessage;'#013#010+
  '              Finished:=true;'#013#010+
  '      ','        end;'#013#010+
  '            AThread.APackage := nil;'#013#010+
  '          end;'#013#010+
  '        StartI := I;'#013#010+
  #013#010+
  '        CompilePackage := nil;'#013#010+
  '        PackageAvailable:=false;'#013#010+
  '        repeat'#013#010+
  '        if IsReadyToCompile(Packages.PackageItems[i]) then'#013#010+
  '      ','    CompilePackage := Packages.PackageItems[i];'#013#010+
  '        if not (Packages.PackageItems[i].State in [tsCompiled, tsNoCom'+
  'pile]) then'#013#010+
  '          PackageAvailable:=true;'#013#010+
  '        inc(I);'#013#010+
  '        if I=packages.Count then'#013#010+
  '          i := 0;'#013#010+
  '   ','     until Assigned(CompilePackage) or (I=StartI);'#013#010+
  '        if Assigned(CompilePackage) then'#013#010+
  '          begin'#013#010+
  '          // Instruct thread to compile package'#013#010+
  '          AThread.APackage := CompilePackage;'#013#010+
  '          AThread.APackage.FProce','ssing := true;'#013#010+
  '          { Commit changes before setting FDone to false, because the '+
  'threads'#013#010+
  '            only wait for an event 500ms at a time and hence way wake '+
  'up'#013#010+
  '            and see that FDone=false before the event is sent and the '+
  'c','hanges'#013#010+
  '            are all committed by the event code }'#013#010+
  '          WriteBarrier;'#013#010+
  '          AThread.FDone:=False;'#013#010+
  '          RTLeventSetEvent(AThread.NotifyStartTask);'#013#010+
  '          end;'#013#010+
  '        if not PackageAvailable then'#013#010+
  '          Finis','hed := True;'#013#010+
  '      end;'#013#010+
  '  end;'#013#010+
  #013#010+
  '{$endif NO_THREADING}'#013#010+
  #013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeCompile, Self);'#013#010+
  '  FProgressMax:=Packages.Count;'#013#010+
  '  FProgressCount:=0;'#013#010+
  #013#010+
  '  if Defaults.ThreadsAmount<0 then'#013#010+
  '    begin'#013#010+
  '      /','/ Do not use any threading to compile the packages'#013#010+
  '      For I:=0 to Packages.Count-1 do'#013#010+
  '        begin'#013#010+
  '          P:=Packages.PackageItems[i];'#013#010+
  '          If PackageOK(P) then'#013#010+
  '            MaybeCompile(P)'#013#010+
  '          else'#013#010+
  '            begin',#013#010+
  '            inc(FProgressCount);'#013#010+
  '            log(vlInfo,SInfoSkipPackageTargetProgress,[(FProgressCount'+
  ')/FProgressMax * 100, P.Name, Defaults.Target]);'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '{$ifndef NO_THREADING}'#013#010,
  '      // Use worker-threads to compile the packages'#013#010+
  '      ErrorState := False;'#013#010+
  '      Finished := False;'#013#010+
  '      I := 0;'#013#010+
  '      ThreadCount:=0;'#013#010+
  '      // This event is set by the worker-threads to notify the main/th'+
  'is thread'#013#010+
  '      // that ','a package finished it'#039's task.'#013#010+
  '      NotifyThreadWaiting := RTLEventCreate;'#013#010+
  '      Threads:=[];'#013#010+
  '      SetLength(Threads,Defaults.ThreadsAmount);'#013#010+
  '      try'#013#010+
  '        // Create all worker-threads'#013#010+
  '        try'#013#010+
  '          for Thr:=0 to Default','s.ThreadsAmount-1 do'#013#010+
  '            begin'#013#010+
  '              Threads[Thr] := TCompileWorkerThread.Create(self,NotifyT'+
  'hreadWaiting);'#013#010+
  '              if assigned(Threads[Thr]) then'#013#010+
  '                begin'#013#010+
  '                  inc(ThreadCount);'#013#010+
  '       ','           Threads[Thr].FWorkerPrefix:=Format('#039'(%d/%d) '#039+
  ',[Thr,Defaults.ThreadsAmount]);'#013#010+
  '                end;'#013#010+
  '            end;'#013#010+
  '        except'#013#010+
  '          on E: Exception do'#013#010+
  '            begin'#013#010+
  '              ErrorMessage := E.Message;'#013#010+
  '    ','          ErrorState:=true;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '        try'#013#010+
  '          // When a thread notifies this thread that it is ready, loop'+
  ' on all'#013#010+
  '          // threads to check their state and if possible assign a new'+
  ' package'#013#010+
  '       ','   // to them to compile.'#013#010+
  '          while not Finished do'#013#010+
  '            begin'#013#010+
  '              RTLeventWaitFor(NotifyThreadWaiting);'#013#010+
  '              RTLeventResetEvent(NotifyThreadWaiting);'#013#010+
  '              for Thr:=0 to Defaults.ThreadsAmount-1',' do'#013#010+
  '                if assigned(Threads[Thr]) and not Finished then'#013#010+
  '                  ProcessThreadResult(Threads[Thr]);'#013#010+
  '            end;'#013#010+
  '        except'#013#010+
  '          on E: Exception do'#013#010+
  '            begin'#013#010+
  '              if not ErrorState t','hen'#013#010+
  '                ErrorMessage := E.Message;'#013#010+
  '              ErrorState:=true;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '        try'#013#010+
  '          // Compilation finished or aborted. Wait for all threads to '+
  'end.'#013#010+
  '          for thr:=0 to Defaults.Thre','adsAmount-1 do'#013#010+
  '            if assigned(Threads[Thr]) then'#013#010+
  '              begin'#013#010+
  '                Threads[Thr].Terminate;'#013#010+
  '                RTLeventSetEvent(Threads[Thr].NotifyStartTask);'#013#010+
  '                Threads[Thr].WaitFor;'#013#010+
  '              ','end;'#013#010+
  '        except'#013#010+
  '          on E: Exception do'#013#010+
  '            begin'#013#010+
  '              if not ErrorState then'#013#010+
  '                ErrorMessage := E.Message;'#013#010+
  '              ErrorState:=true;'#013#010+
  '            end;'#013#010+
  '        end;'#013#010+
  '      finally'#013#010+
  '       ',' RTLeventdestroy(NotifyThreadWaiting);'#013#010+
  '        for thr:=0 to Defaults.ThreadsAmount-1 do'#013#010+
  '          if assigned(Threads[Thr]) then'#013#010+
  '            begin'#013#010+
  '              Threads[Thr].Free;'#013#010+
  '              dec(ThreadCount);'#013#010+
  '            end;'#013#010+
  '   ','   end;'#013#010+
  '    if ErrorState then'#013#010+
  '      raise Exception.Create(ErrorMessage);'#013#010+
  '{$endif NO_THREADING}'#013#010+
  '    end;'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterCompile, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Install(Packages: TPackages);'#013#010+
  'Var'#013#010,
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeInstall, Self);'#013#010+
  '  For I:=0 to Packages.Count-1 do'#013#010+
  '    begin'#013#010+
  '      P:=Packages.PackageItems[i];'#013#010+
  '      If PackageOK(P) then'#013#010+
  '        begin'#013#010+
  '          Inst','all(P, False);'#013#010+
  '          log(vlWarning, SWarnInstallationPackagecomplete, [P.Name, De'+
  'faults.Target]);'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '        log(vlInfo,SInfoSkipPackageTarget,[P.Name, Defaults.Target]);'#013+
  #010+
  '    end;'#013#010+
  '  NotifyEventCollection.CallEv','ents(neaAfterInstall, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBuildEngine.ZipInstall(Packages: TPackages);'#013#010+
  #013#010+
  'var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  #013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeInstall, Self);'#013#010+
  #013#010+
  '  if Defaults.UnixPaths then'#013#010+
  '   ',' Defaults.IntSetBaseInstallDir('#039'lib/fpc/'#039' + Defaults.FCom'+
  'pilerVersion+ '#039'/'#039')'#013#010+
  '  else'#013#010+
  '    Defaults.IntSetBaseInstallDir('#039#039');'#013#010+
  #013#010+
  '  try'#013#010+
  '    For I:=0 to Packages.Count-1 do'#013#010+
  '      begin'#013#010+
  '        P:=Packages.PackageItems[i];'#013#010+
  '        If Package','OK(P) then'#013#010+
  '          begin'#013#010+
  '            Install(P, True);'#013#010+
  '            log(vlWarning, SWarnInstallationPackagecomplete, [P.Name, '+
  'Defaults.Target]);'#013#010+
  '          end'#013#010+
  '        else'#013#010+
  '          log(vlInfo,SInfoSkipPackageTarget,[P.Name, Defaults','.Target'+
  ']);'#013#010+
  '      end;'#013#010+
  '  finally'#013#010+
  '    FinishArchive(P);'#013#010+
  '  end;'#013#010+
  #013#010+
  '  NotifyEventCollection.CallEvents(neaAfterInstall, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.UnInstall(Packages: TPackages);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  'begin'#013#010+
  ' ',' NotifyEventCollection.CallEvents(neaBeforeUnInstall, Self);'#013#010+
  '  For I:=0 to Packages.Count-1 do'#013#010+
  '    begin'#013#010+
  '      P:=Packages.PackageItems[i];'#013#010+
  '      UnInstall(P);'#013#010+
  '    end;'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterUnInstall, Self);'#013#010+
  'end',';'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Archive(Packages: TPackages);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeArchive, Self);'#013#010+
  '  Log(vlDebug, SDbgBuildEngineArchiving);'#013#010+
  '  For I:=0 to Packages.Count-1',' do'#013#010+
  '    begin'#013#010+
  '      P:=Packages.PackageItems[i];'#013#010+
  '      // Force generation of manifest.xml, this is required for the re'+
  'pository'#013#010+
  '      Manifest(nil, P);'#013#010+
  '      Archive(P);'#013#010+
  '    end;'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterArchive, Se','lf);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.Manifest(Packages: TPackages; Package: TPackage'+
  ');'#013#010+
  'Var'#013#010+
  '  L : TStrings;'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  '  FN: string;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeManifest, Self);'#013#010+
  '  Log(vlDeb','ug, SDbgBuildEngineGenerateManifests);'#013#010+
  #013#010+
  '  L:=TStringList.Create;'#013#010+
  '  Try'#013#010+
  '    Log(vlDebug, Format(SDbgGenerating, [ManifestFile]));'#013#010+
  '    L.Add('#039'<?xml version="1.0"?>'#039');'#013#010+
  '    L.Add('#039'<packages>'#039');'#013#010+
  '    if assigned(Packages) then'#013#010+
  '      begin',#013#010+
  '        For I:=0 to Packages.Count-1 do'#013#010+
  '          begin'#013#010+
  '            P:=Packages.PackageItems[i];'#013#010+
  '            Log(vlInfo, Format(SInfoManifestPackage,[P.Name]));'#013#010+
  '            P.GetManifest(L);'#013#010+
  '          end'#013#010+
  '      end;'#013#010+
  '    if assigned','(Package) then'#013#010+
  '      begin'#013#010+
  '        Log(vlInfo, Format(SInfoManifestPackage,[Package.Name]));'#013#010+
  '        Package.GetManifest(L);'#013#010+
  '      end;'#013#010+
  '    L.Add('#039'</packages>'#039');'#013#010+
  '    FN := ManifestFile;'#013#010+
  '    if assigned(Package) then'#013#010+
  '      FN := FixP','ath(Package.Directory, True)+FN;'#013#010+
  '    L.SaveToFile(FN);'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  NotifyEventCollection.CallEvents(neaAfterManifest, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TBuildEngine.PkgList(Packages: TPackages);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P',' : TPackage;'#013#010+
  '  L : TStrings;'#013#010+
  '  PKGL : String;'#013#010+
  'begin'#013#010+
  '  L:=TStringList.Create;'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforePkgList, Self);'#013#010+
  '  Log(vlDebug, SDbgBuildEngineGeneratePkgList);'#013#010+
  '{ Consider only the target OS, because the insta','ller would be run th'+
  'ere }'#013#010+
  '  if Defaults.OS in AllLimit83fsOSes then'#013#010+
  '    PKGL := PkgListFileBase + OSToString (Defaults.OS) + PkgListFileEx'+
  't'#013#010+
  '  else if Defaults.OS = osNone then'#013#010+
  '    PKGL := PkgListFileBase + '#039'src'#039' + PkgListFileExt'#013#010+
  '  else',#013#010+
  '    begin'#013#010+
  '    PKGL := PkgListFileBase + MakeTargetString(Defaults.CPU,Defaults.O'+
  'S,Defaults.SubTarget);'#013#010+
  '    PKGL := PKGL+ PkgListFileExt;'#013#010+
  '    end;'#013#010+
  #013#010+
  '  Try'#013#010+
  '    Log(vlDebug, Format(SDbgGenerating, [PKGL]));'#013#010+
  #013#010+
  '    For I:=0 to Packages.C','ount-1 do'#013#010+
  '      begin'#013#010+
  '        P:=Packages.PackageItems[i];'#013#010+
  '        PkgList(L, P);'#013#010+
  '      end;'#013#010+
  #013#010+
  '    L.SaveToFile(PKGL);'#013#010+
  '  Finally'#013#010+
  '    L.Free;'#013#010+
  '  end;'#013#010+
  #013#010+
  '  NotifyEventCollection.CallEvents(neaAfterPkgList, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TBu','ildEngine.Clean(Packages: TPackages; AllTargets: boolea'+
  'n);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  '  P : TPackage;'#013#010+
  'begin'#013#010+
  '  NotifyEventCollection.CallEvents(neaBeforeClean, Self);'#013#010+
  '  Log(vldebug, SDbgBuildEngineCleaning);'#013#010+
  '  For I:=0 to Packages.Count-1 do'#013,#010+
  '    begin'#013#010+
  '      P:=Packages.PackageItems[i];'#013#010+
  '      If AllTargets or PackageOK(P) then'#013#010+
  '        Clean(P, AllTargets);'#013#010+
  '    end;'#013#010+
  '  NotifyEventCollection.CallEvents(neaAfterClean, Self);'#013#010+
  'end;'#013#010+
  #013#010+
  '{******************************************','*************************'+
  '*********'#013#010+
  '                               TFPVersion'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TFPVersion.GetAsString: String;'#013#010+
  'begin'#013#010+
  '  if Empty then'#013#010+
  '    Result:='#039'<','none>'#039#013#010+
  '  else'#013#010+
  '  begin'#013#010+
  '    Result := '#039#039';'#013#010+
  '    if Major <> -1 then'#013#010+
  '      Result := Result + IntToStr(Major);'#013#010+
  '    if Minor <> -1 then'#013#010+
  '      Result := Result + '#039'.'#039' + IntToStr(Minor);'#013#010+
  '    if Micro <> -1 then'#013#010+
  '      Result := Result + '#039'.'#039' ','+ IntToStr(Micro);'#013#010+
  '    if Build <> -1 then'#013#010+
  '      Result := Result + '#039'-'#039'  + IntToStr(Build);'#013#010+
  '  end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TFPVersion.GetEmpty: Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=(Major=0) and (Minor=0) and (Micro=0) and (Build=0);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure ','TFPVersion.SetAsString(const AValue: String);'#013#010+
  #013#010+
  '  Function NextDigit(sep : AnsiChar; var V : string) : integer;'#013#010+
  '  Var'#013#010+
  '    P : Integer;'#013#010+
  '  begin'#013#010+
  '    P:=Pos(Sep,V);'#013#010+
  '    If (P=0) then'#013#010+
  '      P:=Length(V)+1;'#013#010+
  '    Result:=StrToIntDef(Copy(V',',1,P-1),-1);'#013#010+
  '    If Result<>-1 then'#013#010+
  '      Delete(V,1,P);'#013#010+
  '  end;'#013#010+
  #013#010+
  'Var'#013#010+
  '  V : String;'#013#010+
  'begin'#013#010+
  '  Clear;'#013#010+
  '  // Special support for empty version string'#013#010+
  '  if (AValue='#039#039') or (AValue='#039'<none>'#039') then'#013#010+
  '    exit;'#013#010+
  '  V:=AValue;'#013#010+
  '  Major:=NextDigi','t('#039'.'#039',V);'#013#010+
  '  Minor:=NextDigit('#039'.'#039',V);'#013#010+
  '  Micro:=NextDigit('#039'-'#039',V);'#013#010+
  '  Build:=NextDigit(#0,V);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TFPVersion.Clear;'#013#010+
  'begin'#013#010+
  '  Micro:=-1;'#013#010+
  '  Major:=-1;'#013#010+
  '  Minor:=-1;'#013#010+
  '  Build:=-1;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TFPVersion.Assign(Source: TP','ersistent);'#013#010+
  'Var'#013#010+
  '  V : TFPVersion;'#013#010+
  'begin'#013#010+
  '  if Source is TFPVersion then'#013#010+
  '    begin'#013#010+
  '    V:=Source as TFPVersion;'#013#010+
  '    Major:=V.Major;'#013#010+
  '    Minor:=V.Minor;'#013#010+
  '    Micro:=V.Micro;'#013#010+
  '    Build:=V.Build;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    inherited Assign(S','ource);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TFPVersion.CompareVersion(AVersion: TFPVersion): Integer;'#013+
  #010+
  'begin'#013#010+
  '  Result:=Major-AVersion.Major;'#013#010+
  '  If (Result=0) then'#013#010+
  '    begin'#013#010+
  '      Result:=Minor-AVersion.Minor;'#013#010+
  '      if (Result=0) then'#013#010+
  '        begin'#013#010+
  '    ','      Result:=Micro-AVersion.Micro;'#013#010+
  '          If (Result=0) then'#013#010+
  '            Result:=Build-AVersion.Build;'#013#010+
  '        end;'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TFPVersion.SameVersion(AVersion: TFPVersion): Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=CompareVersion(A','Version)=0;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                 TTarget'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'constructor TTa','rget.Create(ACollection: TCollection);'#013#010+
  'begin'#013#010+
  '  inherited Create(ACollection);'#013#010+
  '  FInstall:=True;'#013#010+
  '  FCPUs:=AllCPUs;'#013#010+
  '  FOSes:=AllOSes;'#013#010+
  '  FUnitPath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FIncludePath:=TConditionalStrings.Crea','te(TConditionalString);'#013#010+
  '  FObjectPath:=TConditionalStrings.Create(TConditionalString);'#013#010+
  '  FDependencies:=TDependencies.Create(TDependency);'#013#010+
  '  FResourceFiles:=TResourceFiles.Create(TResourceFile);'#013#010+
  '  FCommands:=TCommands.Create(TCommand);'#013,#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TTarget.Destroy;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FUnitPath);'#013#010+
  '  FreeAndNil(FObjectPath);'#013#010+
  '  FreeAndNil(FIncludePath);'#013#010+
  '  FreeAndNil(FDependencies);'#013#010+
  '  FreeAndNil(FResourceFiles);'#013#010+
  '  FreeAndNil(FCommands);'#013#010+
  '  FreeAndNil(Foptions);',#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.AssignTo(Dest: TPersistent);'#013#010+
  'var'#013#010+
  '  DestTarget: TTarget;'#013#010+
  'begin'#013#010+
  '  if Dest is TTarget then'#013#010+
  '    begin'#013#010+
  '    DestTarget := TTarget(Dest);'#013#010+
  '    DestTarget.Dependencies.Assign(Dependencies);'#013#010+
  ' ','   DestTarget.Commands.Assign(Commands);'#013#010+
  '    DestTarget.FTargetState := FTargetState;'#013#010+
  '    DestTarget.TargetType := TargetType;'#013#010+
  '    DestTarget.CPUs := CPUs;'#013#010+
  '    DestTarget.OSes := OSes;'#013#010+
  '    DestTarget.Mode := Mode;'#013#010+
  '    DestTarget.Optio','ns := Options;'#013#010+
  '    DestTarget.Name :=  Name;'#013#010+
  '    DestTarget.Extension:= Extension;'#013#010+
  '    DestTarget.FPCTarget := FPCTarget;'#013#010+
  '    DestTarget.FileType := FileType;'#013#010+
  '    DestTarget.Directory := Directory;'#013#010+
  '    DestTarget.ResourceStrings := Re','sourceStrings;'#013#010+
  '    DestTarget.ResourceFiles.Assign(ResourceFiles);'#013#010+
  '    DestTarget.Install := Install;'#013#010+
  '    DestTarget.FTargetSourceFileName := fTargetSourceFileName;'#013#010+
  '    DestTarget.ObjectPath.Assign(ObjectPath);'#013#010+
  '    DestTarget.UnitPath.','Assign(UnitPath);'#013#010+
  '    DestTarget.IncludePath.Assign(IncludePath);'#013#010+
  '    DestTarget.AfterCompile := AfterCompile;'#013#010+
  '    DestTarget.BeforeCompile := BeforeCompile;'#013#010+
  '    DestTarget.BeforeClean := BeforeCompile;'#013#010+
  '    DestTarget.AfterClean := Aft','erClean;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    inherited AssignTo(Dest);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.GetOptions: TStrings;'#013#010+
  'begin'#013#010+
  '  If Foptions=Nil then'#013#010+
  '    FOptions:=TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  Result:=FOptions;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget','.GetImportLibFileName(AOS : TOS) : String;'#013#010+
  'begin'#013#010+
  '  result := GetImportLibraryFilename(Name,AOS);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.GetUnitLibFileName(AOS : TOS): String;'#013#010+
  'begin'#013#010+
  '  if AOS in [atari,go32v2,watcom,wdosx,msdos,win16] then'#013#010+
  '    Result',' := Name+LibExt'#013#010+
  '  else if AOS in [java] then'#013#010+
  '    Result:=Name+'#039'.jar'#039#013#010+
  '  else if AOS in [macosclassic] then'#013#010+
  '    Result:=Name+'#039'Lib'#039#013#010+
  '  else'#013#010+
  '    Result:='#039'libp'#039'+Name+LibExt;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.SetOptions(const AValue: TStrings);'#013#010+
  'be','gin'#013#010+
  '  If (AValue=Nil) or (AValue.Count=0) then'#013#010+
  '    FreeAndNil(FOptions)'#013#010+
  '  else'#013#010+
  '    Options.Assign(AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.GetSourceFileName: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+FExtension;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetUnitFileNa','me: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+UnitExt;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetObjectFileName: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+ObjExt;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetLTOFileName: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+LTOExt;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget','.GetRSTFileName: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+RSText;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetRSJFileName: String;'#013#010+
  'begin'#013#010+
  '  Result:=Name+RSJext;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetBinFileBase: String;'#013#010+
  #013#010+
  'var'#013#010+
  '  S : String;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if FExeName <> ',#039#039' then'#013#010+
  '    Result := FExeName'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '    Result:=Name;'#013#010+
  '    for S in Options do'#013#010+
  '      if Copy(S,1,2)='#039'-o'#039' then'#013#010+
  '        Result:=Copy(S,3);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetProgramFileName(AOS : TOS): String;'#013#010+
  'begin'#013#010,
  '    result := AddProgramExtension(GetBinFileBase, AOS);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetProgramDebugFileName(AOS: TOS): String;'#013#010+
  'begin'#013#010+
  '  result := GetBinFileBase + DbgExt;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.GetLibraryFileName(AOS : TOS): String;'#013#010+
  'be','gin'#013#010+
  '  Result:=GetBinFileBase;'#013#010+
  '  if ExtractFileExt(Result)='#039#039' then'#013#010+
  '    result := AddLibraryExtension(Result, AOS);'#013#010+
  '  if aOS in AllUnixOSes then'#013#010+
  '    if Copy(Result,1,3)<>'#039'lib'#039' then'#013#010+
  '      Result:='#039'lib'#039'+Result;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget','.GetLibraryDebugFileName(AOS: TOS): String;'#013#010+
  'begin'#013#010+
  '  result := GetBinFileBase + DbgExt;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TTarget.GetOutputFileName(AOs: TOS): String;'#013#010+
  'begin'#013#010+
  '  if TargetType in UnitTargets then'#013#010+
  '    Result:=GetUnitFileName'#013#010+
  '  else if Ta','rgetType=ttSharedLibrary then'#013#010+
  '    Result:=GetLibraryFileName(AOs)'#013#010+
  '  else'#013#010+
  '    Result:=GetProgramFileName(AOs);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.HaveOptions: Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=(FOptions<>Nil);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.SubTargetAllowed(c','onst aSubTarget: String): Boolean'+
  ';'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=(Length(FSubTargets)=0) or (Length(aSubTarget)=0);'#013#010+
  '  if not Result then'#013#010+
  '    Result:=IndexText(aSubTarget,FSubTargets)<>-1;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TTarget.SubTargetsAsString: String;'#013#010+
  #013#010+
  'Var',#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  if Length(SubTargets)>0 then'#013#010+
  '    Result:=SubTargets[0];'#013#010+
  '  for I:=1 to Length(SubTargets) do'#013#010+
  '    Result:=Result+'#039' '#039'+SubTargets[i];'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TTarget.SetName(const AValue: String);'#013#010+
  'Va','r'#013#010+
  '  D,N,E : String;'#013#010+
  'begin'#013#010+
  '  N:=FixPath(AValue, False);'#013#010+
  '  D:=ExtractFilePath(N);'#013#010+
  '  E:=ExtractFileExt(N);'#013#010+
  '  N:=ExtractFileName(N);'#013#010+
  '  inherited SetName(Copy(N,1,Length(N)-Length(E)));'#013#010+
  '  FExtension:=E;'#013#010+
  '  FDirectory:=D;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedu','re TTarget.SetExeName(const AValue: String);'#013#010+
  'Var'#013#010+
  '  N,E : String;'#013#010+
  'begin'#013#010+
  '  N:=FixPath(AValue, False);'#013#010+
  '  E:=ExtractFileExt(N);'#013#010+
  '  N:=ExtractFileName(N);'#013#010+
  '  FExeName:=Copy(N,1,Length(N)-Length(E));'#013#010+
  '  { Use exact AValue for -o option }'#013#010+
  '  ','AddOption('#039'-o'#039'+AValue);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.GetCleanFiles(List: TStrings; const APrefixU,'#013#010+
  '  APrefixB: String; const aTarget: TcompileTarget);'#013#010+
  #013#010+
  'Var'#013#010+
  '  aOS : TOS;'#013#010+
  '  aCPU : TCPU;'#013#010+
  #013#010+
  'begin'#013#010+
  '  aCPU:=aTarget.CPU;'#013#010+
  '  aOS:=aTarget.OS;'#013#010+
  ' ',' If not(aCPU in CPUs) or not(AOS in OSes) then'#013#010+
  '    exit;'#013#010+
  '  if aPrefixU<>'#039#039' then'#013#010+
  '    begin'#013#010+
  '    List.Add(APrefixU + ObjectFileName);'#013#010+
  '    List.Add(APrefixU + LTOFileName);'#013#010+
  '    end;'#013#010+
  '  Case TargetType of'#013#010+
  '  ttUnit,ttImplicitUnit,ttExample','Unit, ttCleanOnlyUnit:'#013#010+
  '      if aPrefixU<>'#039#039' then'#013#010+
  '        begin'#013#010+
  '        List.Add(APrefixU + UnitFileName);'#013#010+
  '        if (AOS in AllSmartLinkLibraryOSes) and FileExists(APrefixU + '+
  'GetUnitLibFileName(AOS)) then'#013#010+
  '          List.Add(APrefixU ','+ GetUnitLibFileName(AOS));'#013#010+
  '        if (AOS in AllImportLibraryOSes) and FileExists(APrefixU + Get'+
  'ImportLibFilename(AOS)) then'#013#010+
  '          List.Add(APrefixU + GetImportLibFilename(AOS));'#013#010+
  '        end;'#013#010+
  '  ttProgram,ttExampleProgram:'#013#010+
  '    beg','in'#013#010+
  '    if (aPrefixB<>'#039#039') then'#013#010+
  '      begin'#013#010+
  '      List.Add(APrefixB + GetProgramFileName(AOS));'#013#010+
  '        if FileExists(APrefixB + GetProgramDebugFileName(AOS)) then'#013+
  #010+
  '          List.Add(APrefixB + GetProgramDebugFileName(AOS));'#013#010+
  '      end;'#013,#010+
  '    if (aPrefixU<>'#039#039') then'#013#010+
  '      begin'#013#010+
  '      if (AOS in AllImportLibraryOSes) and FileExists(APrefixU + GetIm'+
  'portLibFilename(AOS)) then'#013#010+
  '        List.Add(APrefixU + GetImportLibFilename(AOS));'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  ttSharedLibrary:'#013#010+
  ' ','   if (APrefixB<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '      List.Add(APrefixB + GetLibraryFileName(AOS));'#013#010+
  '      if FileExists(APrefixB + GetLibraryDebugFileName(AOS)) then'#013#010+
  '        List.Add(APrefixB + GetLibraryDebugFileName(AOS));'#013#010+
  '    end;'#013#010+
  '  end; { cas','e }'#013#010+
  '  if (APrefixU<>'#039#039') then'#013#010+
  '    begin'#013#010+
  '    If ResourceStrings  then'#013#010+
  '      begin'#013#010+
  '        // choose between 2 possible resource files'#013#010+
  '        if FileExists(APrefixU + RSJFileName) then'#013#010+
  '          List.Add(APrefixU + RSJFileName)'#013#010+
  '      ','  else'#013#010+
  '          List.Add(APrefixU + RSTFileName);'#013#010+
  '      end'#013#010+
  '    else'#013#010+
  '      begin'#013#010+
  '        if FileExists(APrefixU + RSJFileName) then'#013#010+
  '          begin'#013#010+
  '            Installer.Log(VlDebug,Format(SDbgUnregisteredResource,[APr'+
  'efixU + RSJFil','eName]));'#013#010+
  '            List.Add(APrefixU + RSJFileName);'#013#010+
  '          end'#013#010+
  '        else if FileExists(APrefixU + RSTFileName) then'#013#010+
  '          begin'#013#010+
  '            Installer.Log(VlDebug,Format(SDbgUnregisteredResource,[APr'+
  'efixU + RSTFileName]));',#013#010+
  '            List.Add(APrefixU + RSTFileName);'#013#010+
  '          end;'#013#010+
  '       end;'#013#010+
  '     end;'#013#010+
  '  // Maybe add later ?  AddConditionalStrings(List,CleanFiles);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.GetCleanFiles(List: TStrings; const APrefixU,'#013#010+
  '  APrefixB: S','tring; ACPU: TCPU; AOS: TOS; const aSubTarget: String);'+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  GetCleanFiles(List,aPrefixU,aPrefixB,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.GetInstallFil','es(List: TStrings; const APrefixU,'#013+
  #010+
  '  APrefixB: String; ACPU: TCPU; AOS: TOS; const aSubTarget: String);'#013+
  #010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:=aSubTarget;'#013#010+
  '  GetInstallFiles(List,aPrefixU,aPr','efixB,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TTarget.GetInstallFiles(List: TStrings; const APrefixU,'#013#010+
  '  APrefixB: String; const aTarget: TCompileTarget);'#013#010+
  'var'#013#010+
  '  UnitsDir : string;'#013#010+
  '  aOS : TOS;'#013#010+
  '  aCPU : TCPU;'#013#010+
  'begin'#013#010+
  '  aOS:=aTarget.OS;'#013#010+
  '  aCPU:=aTarge','t.CPU;'#013#010+
  '  UnitsDir := Installer.BuildEngine.AddPathPrefix(nil, APrefixU);'#013#010+
  '  If Not (TargetType in [ttProgram,ttSharedLibrary,ttExampleProgram]) '+
  'then'#013#010+
  '    begin'#013#010+
  '      // The compiler does not create an objectfile for all programs.'#013+
  #010+
  '      i','f FileExists(UnitsDir + ObjectFileName) then'#013#010+
  '        List.Add(APrefixU + ObjectFileName);'#013#010+
  '      if FileExists(UnitsDir + LTOFileName) then'#013#010+
  '        List.Add(APrefixU + LTOFileName);'#013#010+
  '    end;'#013#010+
  '  If (TargetType in [ttUnit,ttImplicitUnit,tt','ExampleUnit]) then'#013#010+
  '    begin'#013#010+
  '      List.Add(APrefixU + UnitFileName);'#013#010+
  '      if (AOS in AllSmartLinkLibraryOSes) and FileExists(UnitsDir + Ge'+
  'tUnitLibFileName(AOS)) then'#013#010+
  '        List.Add(APrefixU + GetUnitLibFileName(AOS));'#013#010+
  '      if (AOS',' in AllImportLibraryOSes) and FileExists(UnitsDir + Get'+
  'ImportLibFilename(AOS)) then'#013#010+
  '        List.Add(APrefixU + GetImportLibFilename(AOS));'#013#010+
  '    end'#013#010+
  '  else If (TargetType in [ttProgram,ttExampleProgram]) then'#013#010+
  '    List.Add(APrefixB + GetP','rogramFileName(AOS))'#013#010+
  '  else If (TargetType in [ttSharedLibrary]) then'#013#010+
  '    List.Add(APrefixB + GetLibraryFileName(AOS));'#013#010+
  '  If ResourceStrings then'#013#010+
  '    begin'#013#010+
  '      // choose between 2 possible resource files'#013#010+
  '      if FileExists(UnitsDir',' + RSJFileName) then'#013#010+
  '        List.Add(APrefixU + RSJFileName)'#013#010+
  '      else'#013#010+
  '        List.Add(APrefixU + RSTFileName);'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    begin'#013#010+
  '      if FileExists(UnitsDir + RSJFileName) then'#013#010+
  '        begin'#013#010+
  '          Installer.Log(VlDe','bug,Format(SDbgUNregisteredResource,[APr'+
  'efixU + RSJFileName]));'#013#010+
  '          List.Add(APrefixU + RSJFileName);'#013#010+
  '        end'#013#010+
  '      else if FileExists(UnitsDir + RSTFileName) then'#013#010+
  '        begin'#013#010+
  '          Installer.Log(VlDebug,Format(SDbgUNre','gisteredResource,[APr'+
  'efixU + RSTFileName]));'#013#010+
  '          List.Add(APrefixU + RSTFileName);'#013#010+
  '        end;'#013#010+
  '     end;'#013#010+
  '  FResourceFiles.GetInstallFiles(List, APrefixU, APrefixB, ACPU, AOS);'+
  #013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.GetArchiveFiles(List: TStr','ings; ACPU: TCPU; AOS : '+
  'TOS);'#013#010+
  #013#010+
  #013#010+
  'Var'#013#010+
  '  CT : TCompileTarget;'#013#010+
  #013#010+
  'begin'#013#010+
  '  CT.OS:=aOS;'#013#010+
  '  CT.CPU:=aCPU;'#013#010+
  '  CT.Subtarget:='#039#039';'#013#010+
  '  GetArchiveFiles(List,CT);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TTarget.GetArchiveFiles(List: TStrings; const aTarget: TComp'+
  'ileTa','rget);'#013#010+
  'var'#013#010+
  '  i : integer;'#013#010+
  '  D : TDependency;'#013#010+
  'begin'#013#010+
  '  If not(aTarget.CPU in CPUs) or not(aTarget.OS in OSes) then'#013#010+
  '    exit;'#013#010+
  '  // Main source'#013#010+
  '  if TargetSourceFileName<>'#039#039' then'#013#010+
  '    List.Add(TargetSourceFileName);'#013#010+
  '  // Includes'#013#010+
  '  fo','r i:=0 to Dependencies.Count-1 do'#013#010+
  '    begin'#013#010+
  '      D:=Dependencies[i];'#013#010+
  '      if (D.DependencyType=depInclude) and'#013#010+
  '         (D.TargetFileName<>'#039#039') then'#013#010+
  '        List.Add(D.TargetFileName);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TTarget.AddOption(co','nst aValue: String);'#013#010+
  'begin'#013#010+
  '  Options.Add(aValue);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                 TSource'#013#010+
  '********************************************************','************'+
  '********}'#013#010+
  #013#010+
  'function TSource.GetInstallSourcePath: string;'#013#010+
  'begin'#013#010+
  '  if FInstallSourcePath<>'#039#039' then'#013#010+
  '    result := FInstallSourcePath'#013#010+
  '  else if SourceType=stExample then'#013#010+
  '    result := '#039'examples'#039#013#010+
  '  else'#013#010+
  '    result := '#039#039';'#013#010+
  'en','d;'#013#010+
  #013#010+
  'constructor TSource.Create(ACollection: TCollection);'#013#010+
  'begin'#013#010+
  '  inherited Create(ACollection);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TSource.Destroy;'#013#010+
  'begin'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TSource.GetInstallFiles(List: TStrings);'#013#010+
  'begin'#013#010+
  '  i','f InstallSourcePath<>'#039#039' then'#013#010+
  '    list.Values[name] := (IncludeTrailingPathDelimiter(InstallSourcePa'+
  'th)+ExtractFileName(Name))'#013#010+
  '  else'#013#010+
  '    list.add(Name);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '***','****'#013#010+
  '                                 TCommands'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TCommands.GetCommand(const Dest : String): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=TCommand(ItemByName(Dest));'#013#010,
  'end;'#013#010+
  #013#010+
  'function TCommands.GetCommandItem(Index : Integer): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=TCommand(Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TCommands.SetCommandItem(Index : Integer; const AValue: TCom'+
  'mand);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013,#010+
  #013#010+
  'function TCommands.AddCommand(const Cmd: String): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=AddCommand(fdefaultAt,Cmd,'#039#039','#039#039','#039#039');'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCommands.AddCommand(const Cmd, Options: String): TCommand;'#013+
  #010+
  'begin'#013#010+
  '  Result:=AddCommand(fdefaultAt,Cm','d,Options,'#039#039','#039#039');'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCommands.AddCommand(const Cmd, Options, Dest, Source: String'+
  ' ): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=AddCommand(fdefaultAt,Cmd,options,Dest,Source);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCommands.AddCommand(At: TCommandAt; cons','t Cmd: String): TC'+
  'ommand;'#013#010+
  'begin'#013#010+
  '  Result:=AddCommand(At,Cmd,'#039#039','#039#039','#039#039');'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCommands.AddCommand(At: TCommandAt; const Cmd, Options: Stri'+
  'ng  ): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=AddCommand(At,Cmd,Options,'#039#039','#039#039');'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'functi','on TCommands.AddCommand(At: TCommandAt; const Cmd, Options, De'+
  'st, Source: String): TCommand;'#013#010+
  'begin'#013#010+
  '  Result:=Add as TCommand;'#013#010+
  '  Result.Command:=Cmd;'#013#010+
  '  If (Options<>'#039#039') then'#013#010+
  '    Result.ParseOptions(Options);'#013#010+
  '  Result.At:=At;'#013#010+
  '  Result.','SourceFile:=Source;'#013#010+
  '  Result.DestFile:=Dest;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TCommands.GetEnumerator: TCommandEnumerator;'#013#010+
  'begin'#013#010+
  '  Result:=TCommandEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{********************************************************************',
  '********'#013#010+
  '                           TConditionalString'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  #013#010+
  'procedure TConditionalString.Assign(aSource: TPersistent);'#013#010+
  #013#010+
  'Var'#013#010+
  '  CS : TConditionalString absolut','e aSource;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if (aSource is TConditionalString) then'#013#010+
  '    begin'#013#010+
  '    FValue:=CS.Value;'#013#010+
  '    FOSes:=CS.OSes;'#013#010+
  '    FCPUs:=CS.CPUs;'#013#010+
  '    end'#013#010+
  '  else'#013#010+
  '    inherited Assign(aSource);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TConditionalString.Match(aCPU: TCP','U; aOS: TOS): Boolean;'#013+
  #010+
  'begin'#013#010+
  '  Result:=(aCPU in CPUs) or (CPUs=[]);'#013#010+
  '  Result:=Result and ((aOS in OSes) or (OSes=[]));'#013#010+
  'end;'#013#010+
  #013#010+
  'function TConditionalString.Match(const aValue: String; aCPU: TCPU; aO'+
  'S: TOS'#013#010+
  '  ): Boolean;'#013#010+
  'begin'#013#010+
  '  Result:','=Match(aCPU,aOS) and (aValue=Value)'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TConditionalString.SetValue(const Value: String);'#013#010+
  'begin'#013#010+
  '  FValue := FixPath(Value);'#013#010+
  'end;'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '         ','                  TConditionalStrings'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  #013#010+
  'procedure TConditionalStrings.AddList(aList: TConditionalStrings);'#013+
  #010+
  #013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  For I:=0 to aLis','t.Count-1 do'#013#010+
  '    With Self.Add() do'#013#010+
  '      Assign(aList[i]);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TConditionalStrings.IndexOf(Value: String; aCPU: TCPU; aOS: T'+
  'OS'#013#010+
  '  ): Integer;'#013#010+
  'begin'#013#010+
  '  Result:=Count-1;'#013#010+
  '  While (Result>=0) and Not GetConditionalString(Resu','lt).Match(Value'+
  ',aCPU,aOS) do'#013#010+
  '    Dec(Result);'#013#010+
  'end;'#013#010+
  #013#010+
  'function TConditionalStrings.Find(Value: String; aCPU: TCPU; aOS: TOS'#013+
  #010+
  '  ): TConditionalString;'#013#010+
  #013#010+
  'var'#013#010+
  '  Idx : Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  Result:=Nil;'#013#010+
  '  Idx:=IndexOf(Value,aCPU,aOS);'#013#010+
  '  if',' Idx<>-1 then'#013#010+
  '    Result:=GetConditionalString(Idx);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TConditionalStrings.GetConditionalString(Index : Integer): TC'+
  'onditionalString;'#013#010+
  'begin'#013#010+
  '  Result:=TConditionalString(Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TConditionalSt','rings.SetConditionalString(Index : Integer; '+
  'const AValue: TConditionalString);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TConditionalStrings.Add(const Value: String): TConditionalStr'+
  'ing;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,AllCPUs,AllOSes',');'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010+
  'Function TConditionalStrings.Add(Const Value : String;const CPUs:TCPUs'+
  ') : TConditionalString;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TConditiona','lStrings.Add(const Value: String; const OSes: TO'+
  'Ses'#013#010+
  '  ): TConditionalString;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TConditionalStrings.Add(const Value: String; const CPUs: TCPU'+
  's;'#013#010+
  '  const OSes: TOSes): TConditional','String;'#013#010+
  'begin'#013#010+
  '  Result:=(Inherited Add) as TConditionalString;'#013#010+
  '  Result.Value:=Value;'#013#010+
  '  Result.OSes:=OSes;'#013#010+
  '  Result.CPUs:=CPUs;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                 ','               TDependency'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'constructor TDependency.Create(aCollection: TCollection);'#013#010+
  'begin'#013#010+
  '  inherited;'#013#010+
  '  FVersion:=TFPVersion.Create;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure T','Dependency.Assign(aSource: TPersistent);'#013#010+
  #013#010+
  'Var'#013#010+
  '  D : TDependency absolute asource;'#013#010+
  #013#010+
  'begin'#013#010+
  '  if (aSource is TDependency) then'#013#010+
  '    begin'#013#010+
  '    FDependencyType:=D.DependencyType;'#013#010+
  '    FTarget:=D.Target;'#013#010+
  '    Version:=D.Version;'#013#010+
  '    FRequ','ireChecksum:=D.RequireChecksum;'#013#010+
  '    FTargetFileName:=D.TargetFileName;'#013#010+
  '    end;'#013#010+
  '  Inherited;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TDependency.Destroy;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FVersion);'#013#010+
  '  Inherited;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependency.GetVersion: string;'#013#010+
  'be','gin'#013#010+
  '  result:=FVersion.AsString;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TDependency.SetVersion(const V: string);'#013#010+
  'begin'#013#010+
  '  FVersion.AsString:=V;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                      ','          TDependencies'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'function TDependencies.GetDependency(Index : Integer): TDependency;'#013+
  #010+
  'begin'#013#010+
  '  Result:=TDependency(Items[Index]);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure ','TDependencies.SetDependency(Index : Integer; const AValue:'+
  ' TDependency);'#013#010+
  'begin'#013#010+
  '  Items[Index]:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.Add(const Value: String): TDependency;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifd','ef cpu_only_overloads}'#013#010+
  'Function TDependencies.Add(Const Value : String;const CPUs:TCPUs) : TD'+
  'ependency;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.Add(const Value: String; cons','t OSes: TOSes): '+
  'TDependency;'#013#010+
  'begin'#013#010+
  '  result:=Add(Value,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.Add(const Value: String; const CPUs: TCPUs;'#013+
  #010+
  '  const OSes: TOSes): TDependency;'#013#010+
  'begin'#013#010+
  '  Result:=inherited Add(Value,CPUs,OSes) as TD','ependency;'#013#010+
  '  Result.Target:=nil;'#013#010+
  '  Result.FDependencyType:=depPackage;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.AddUnit(const Value: String): TDependency;'#013#010+
  'begin'#013#010+
  '  result:=AddUnit(Value,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads}'#013#010,
  'Function TDependencies.AddUnit(Const Value : String;const CPUs:TCPUs) '+
  ': TDependency;'#013#010+
  'begin'#013#010+
  '  result:=AddUnit(Value,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.AddUnit(const Value: String; const OSes: TOSe','s'+
  #013#010+
  '  ): TDependency;'#013#010+
  'begin'#013#010+
  '  result:=AddUnit(Value,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.AddUnit(const Value: String; const CPUs: TCPUs;'+
  #013#010+
  '  const OSes: TOSes): TDependency;'#013#010+
  'begin'#013#010+
  '  Result:=inherited Add(Value,CPUs,OSes) as TD','ependency;'#013#010+
  '  Result.Target:=nil;'#013#010+
  '  Result.FDependencyType:=depUnit;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDependencies.AddInclude(const Value: String): TDependency;'#013+
  #010+
  'begin'#013#010+
  '  result:=AddInclude(Value,AllCPUs,AllOSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{$ifdef cpu_only_overloads','}'#013#010+
  'Function TDependencies.AddInclude(Const Value : String;const CPUs:TCPU'+
  's) : TDependency;'#013#010+
  'begin'#013#010+
  '  result:=AddInclude(Value,CPUs,AllOSes);'#013#010+
  'end;'#013#010+
  '{$endif cpu_only_overloads}'#013#010+
  #013#010+
  #013#010+
  'Function TDependencies.AddInclude(Const Value : String;cons','t OSes:TO'+
  'Ses) : TDependency;'#013#010+
  'begin'#013#010+
  '  result:=AddInclude(Value,AllCPUs,OSes);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Function TDependencies.AddInclude(Const Value : String;const CPUs:TCPU'+
  's;const OSes:TOSes) : TDependency;'#013#010+
  'Var'#013#010+
  '  N : String;'#013#010+
  'begin'#013#010+
  '  N:=FixPath(Valu','e, False);'#013#010+
  '  if ExtractFileExt(N)='#039#039' then'#013#010+
  '    N:=ChangeFileExt(N,IncExt);'#013#010+
  '  Result:=inherited Add(N,CPUs,OSes) as TDependency;'#013#010+
  '  Result.FDependencyType:=depInclude;'#013#010+
  'end;'#013#010+
  #013#010+
  'function TDependencies.GetEnumerator: TDependencyEnumerator;'#013#010,
  'begin'#013#010+
  '  Result:=TDependencyEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                               TValueItem'#013#010+
  '******************************************************','**************'+
  '********}'#013#010+
  #013#010+
  'constructor TValueItem.Create(AValue: String);'#013#010+
  'begin'#013#010+
  '  FValue:=AValue;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                              TFunctionItem'#013#010+
  '*****','***************************************************************'+
  '********}'#013#010+
  #013#010+
  'constructor TFunctionItem.Create(AFunc: TReplaceFunction);'#013#010+
  'begin'#013#010+
  '  FFunc:=AFunc;'#013#010+
  'end;'#013#010+
  #013#010+
  '{*********************************************************************'+
  '**','*****'#013#010+
  '                           TNotifyEventItem'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'procedure TNotifyEventItem.CallEvent(Sender: TObject);'#013#010+
  'begin'#013#010+
  '  if assigned(OnEvent) then'#013#010+
  '    OnEvent(Sen','der);'#013#010+
  '  if assigned(OnProcEvent) then'#013#010+
  '    OnProcEvent(sender);'#013#010+
  'end;'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                           TNotifyEventCollection'#013#010+
  '************************************','********************************'+
  '********}'#013#010+
  #013#010+
  'constructor TNotifyEventCollection.create(ASupportedActionSet: TNotify'+
  'EventActionSet);'#013#010+
  'begin'#013#010+
  '  FSupportedActionSet:=ASupportedActionSet;'#013#010+
  '  inherited create(TNotifyEventItem);'#013#010+
  'end;'#013#010+
  #013#010+
  'function',' TNotifyEventCollection.GetEnumerator: TNotifyEventEnumerato'+
  'r;'#013#010+
  'begin'#013#010+
  '  Result:= TNotifyEventEnumerator.Create(Self);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TNotifyEventCollection.AppendEvent(AnAction: TNotifyEventAct'+
  'ion; AnEvent: TNotifyEvent);'#013#010+
  'var'#013#010+
  '  item:',' TNotifyEventItem;'#013#010+
  'begin'#013#010+
  '  if not (AnAction in FSupportedActionSet) then'#013#010+
  '    raise Exception.Create(SErrEventNotSupported);'#013#010+
  '  item := TNotifyEventItem(add);'#013#010+
  '  item.OnEvent:=AnEvent;'#013#010+
  '  item.OnAction:=AnAction;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TNotif','yEventCollection.AppendProcEvent(AnACtion: TNotifyEv'+
  'entAction;'#013#010+
  '  AnProcEvent: TNotifyProcEvent);'#013#010+
  'var'#013#010+
  '  item: TNotifyEventItem;'#013#010+
  'begin'#013#010+
  '  if not (AnAction in FSupportedActionSet) then'#013#010+
  '    raise Exception.Create(SErrEventNotSupported);'#013#010+
  ' ',' item := TNotifyEventItem(add);'#013#010+
  '  item.OnProcEvent:=AnProcEvent;'#013#010+
  '  item.OnAction:=AnAction;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TNotifyEventCollection.CallEvents(AnAction: TNotifyEventActi'+
  'on; Sender: TObject);'#013#010+
  'var'#013#010+
  '  i: integer;'#013#010+
  '  item: TNotifyEventItem',';'#013#010+
  'begin'#013#010+
  '  for i := 0 to Count-1 do'#013#010+
  '    begin'#013#010+
  '      item := TNotifyEventItem(Items[i]);'#013#010+
  '      if item.OnAction=AnAction then'#013#010+
  '        item.CallEvent(Sender);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{**********************************************************','*********'+
  '*********'#013#010+
  '                                 TDictionary'#013#010+
  '**********************************************************************'+
  '******}'#013#010+
  #013#010+
  'procedure TDictionary.ClearItem(Idx: Integer);'#013#010+
  #013#010+
  'Var'#013#010+
  '  O : TObject;'#013#010+
  #013#010+
  'begin'#013#010+
  '  O:=FList.Ob','jects[Idx];'#013#010+
  '  O.Free;'#013#010+
  '  FList.Objects[Idx]:=nil;'#013#010+
  'end;'#013#010+
  #013#010+
  'constructor TDictionary.Create(AOwner: TComponent);'#013#010+
  'begin'#013#010+
  '  inherited Create(AOwner);'#013#010+
  '  FList:=TStringList.Create;'#013#010+
  '  FList.Sorted:=True;'#013#010+
  '  FList.Duplicates:=dupError;'#013#010+
  '  FList','.OwnsObjects:=True;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'destructor TDictionary.Destroy;'#013#010+
  #013#010+
  'begin'#013#010+
  '  FreeAndNil(FList);'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TDictionary.AddVariable(const AName, Value: String);'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  I:=Flist.IndexOf(AN','ame);'#013#010+
  '  If I=-1 then'#013#010+
  '    I:=FList.Add(Aname)'#013#010+
  '  else'#013#010+
  '    ClearItem(I);'#013#010+
  '  Flist.Objects[i]:=TValueItem.Create(Value);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TDictionary.AddFunction(const AName: String; FReplacement: T'+
  'ReplaceFunction);'#013#010+
  'Var'#013#010+
  '  I : Integer;',#013#010+
  #013#010+
  'begin'#013#010+
  '  I:=Flist.IndexOf(AName);'#013#010+
  '  If I=-1 then'#013#010+
  '    I:=Flist.Add(AName)'#013#010+
  '  else'#013#010+
  '    ClearItem(I);'#013#010+
  '  Flist.Objects[i]:=TFunctionItem.Create(FReplacement);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'procedure TDictionary.RemoveItem(const AName: String);'#013#010+
  'Var'#013#010+
  '  I :',' Integer;'#013#010+
  #013#010+
  'begin'#013#010+
  '  I:=Flist.IndexOf(AName);'#013#010+
  '  If (I<>-1) then'#013#010+
  '    begin'#013#010+
  '    ClearItem(I);'#013#010+
  '    FList.Delete(I);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDictionary.GetValue(AName: String): String;'#013#010+
  'begin'#013#010+
  '  Result:=GetValue(AName,'#039#039');'#013#010+
  'end;'#013#010+
  #013#010,
  #013#010+
  'function TDictionary.GetValue(const AName,Args: String): String;'#013#010+
  'Var'#013#010+
  '  O : TObject;'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  I:=Flist.IndexOf(AName);'#013#010+
  '  If (I=-1) then'#013#010+
  '    Raise EDictionaryError.CreateFmt(SErrNoDictionaryItem,[AName]);'#013+
  #010+
  '  O:=Flist.Ob','jects[I];'#013#010+
  '  If O is TValueItem then'#013#010+
  '    Result:=TValueItem(O).FValue'#013#010+
  '  else'#013#010+
  '    Result:=TFunctionItem(O).FFunc(AName,Args);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TDictionary.ReplaceStrings(Const ASource: String; Const MaxDe'+
  'pth: Integer = 10): String;'#013#010+
  'Va','r'#013#010+
  '  S,FN,FV : String;'#013#010+
  '  P: Integer;'#013#010+
  'begin'#013#010+
  '  Result:='#039#039';'#013#010+
  '  S:=ASource;'#013#010+
  '  P:=Pos('#039'$('#039',S);'#013#010+
  '  While (P<>0) do'#013#010+
  '    begin'#013#010+
  '      Result:=Result+Copy(S,1,P-1);'#013#010+
  '      Delete(S,1,P+1);'#013#010+
  '      P:=Pos('#039')'#039',S);'#013#010+
  '      FN:=Copy(S,1,P-1);'#013#010+
  '      ','Delete(S,1,P);'#013#010+
  '      P:=Pos('#039' '#039',FN);'#013#010+
  '      If (P<>0) then // function arguments ?'#013#010+
  '        begin'#013#010+
  '        FV:=FN;'#013#010+
  '        FN:=Copy(FN,1,P);'#013#010+
  '        System.Delete(FV,1,P);'#013#010+
  '        end'#013#010+
  '      else'#013#010+
  '        FV:='#039#039';'#013#010+
  '      if MaxDepth > 0 ','then'#013#010+
  '        Result:=Result+ReplaceStrings(GetValue(FN,FV), MaxDepth-1)'#013+
  #010+
  '      else'#013#010+
  '        Result:=Result+GetValue(FN,FV);'#013#010+
  '      P:=Pos('#039'$('#039',S);'#013#010+
  '    end;'#013#010+
  '  Result:=Result+S;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Function TDictionary.Substitute(Const Source : St','ring; const Macros '+
  ': Array of string) : String;'#013#010+
  'Var'#013#010+
  '  I : Integer;'#013#010+
  'begin'#013#010+
  '  I:=0;'#013#010+
  '  While I<High(Macros) do'#013#010+
  '    begin'#013#010+
  '      AddVariable(Macros[i],Macros[I+1]);'#013#010+
  '      Inc(I,2);'#013#010+
  '    end;'#013#010+
  '  Result:=ReplaceStrings(Source);'#013#010+
  '  I:=0;'#013#010+
  '  ','While I<High(Macros) do'#013#010+
  '    begin'#013#010+
  '      RemoveItem(Macros[i]);'#013#010+
  '      Inc(I,2);'#013#010+
  '    end;'#013#010+
  'end;'#013#010+
  #013#010+
  '{*********************************************************************'+
  '*******'#013#010+
  '                                 Default Instances'#013#010+
  '********','************************************************************'+
  '********}'#013#010+
  #013#010+
  'var'#013#010+
  '  DefInstaller : TCustomInstaller;'#013#010+
  #013#010+
  'Function Installer(InstallerClass: TInstallerClass): TCustomInstaller;'+
  #013#010+
  'begin'#013#010+
  '  If Not Assigned(DefInstaller) then'#013#010+
  '    beg','in'#013#010+
  '      try'#013#010+
  '        DefInstaller:=InstallerClass.Create(Nil);'#013#010+
  '      except'#013#010+
  '        On E : Exception do'#013#010+
  '          begin'#013#010+
  '            if IsConsole then'#013#010+
  '              begin'#013#010+
  '                WriteLn(SErrInstaller);'#013#010+
  '                Write','Ln(E.Message);'#013#010+
  '                halt(1);'#013#010+
  '              end'#013#010+
  '            else'#013#010+
  '              raise;'#013#010+
  '          end;'#013#010+
  '      end;'#013#010+
  '    end;'#013#010+
  '  Result:=DefInstaller;'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'Function Installer: TCustomInstaller;'#013#010+
  'begin'#013#010+
  '  Result := Installe','r(TFPCInstaller);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  #013#010+
  '{ TCommand }'#013#010+
  #013#010+
  'function TCommand.GetOptions: TStrings;'#013#010+
  'begin'#013#010+
  '  If (FOptions=Nil) then'#013#010+
  '    FOptions:=TUnsortedCompilerOptionsStringList.Create;'#013#010+
  '  Result:=FOptions;'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCommand.SetOptions(co','nst Value: TStrings);'#013#010+
  'begin'#013#010+
  '  If (Value=Nil) or (Value.Count=0) then'#013#010+
  '    FreeAndNil(FOptions)'#013#010+
  '  else'#013#010+
  '    Options.Assign(Value);'#013#010+
  'end;'#013#010+
  #013#010+
  'destructor TCommand.Destroy;'#013#010+
  'begin'#013#010+
  '  FreeAndNil(FOptions);'#013#010+
  '  inherited Destroy;'#013#010+
  'end;'#013#010+
  #013#010+
  'functi','on TCommand.HaveOptions: Boolean;'#013#010+
  'begin'#013#010+
  '  Result:=(FOptions<>Nil);'#013#010+
  'end;'#013#010+
  #013#010+
  #013#010+
  'function TCommand.CmdLineOptions: String;'#013#010+
  'begin'#013#010+
  '  If HaveOptions then'#013#010+
  '    Result:=OptionListToString(Options);'#013#010+
  'end;'#013#010+
  #013#010+
  'procedure TCommand.ParseOptions(S: St','ring);'#013#010+
  #013#010+
  'begin'#013#010+
  '  Options:=OptionsToStringList(S);'#013#010+
  'end;'#013#010+
  #013#010+
  'Initialization'#013#010+
  '  OnGetApplicationName:=@GetFPMakeName;'#013#010+
  '  CustomFpmakeCommandlineOptions:=nil;'#013#010+
  '  CustomFpMakeCommandlineValues:=nil;'#013#010+
  #013#010+
  '  GetPluginManager.RegisterPlugin(TfpmRes','olvePackagePathsPlugin);'#013+
  #010+
  #013#010+
  'Finalization'#013#010+
  '{$ifndef LLVM_INTERFACE_PROBLEM}'#013#010+
  '  FreeAndNil(CustomFpMakeCommandlineValues);'#013#010+
  '  FreeAndNil(CustomFpmakeCommandlineOptions);'#013#010+
  '  FreeAndNil(DefInstaller);'#013#010+
  '  FreeAndNil(GlobalDictionary);'#013#010+
  '  FreeAnd','Nil(Defaults);'#013#010+
  '  FreeAndNil(GPluginManager);'#013#010+
  '{$endif ndef LLVM_INTERFACE_PROBLEM}'#013#010+
  'end.'#013#010+
  #013#010+
  #013#010
);
