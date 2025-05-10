  
type
  //Obsolete types, kept for backwards compatibility
  TResourceHandle = PtrUint;
{$ifndef CPUJVM}
  TResourceId = PAnsiChar;
{$else CPUJVM}
  { JVM Notes: using a PAnsiChar crashes the compiler (Internal error 2011072410) }
  TResourceId = ansistring;
{$endif CPUJVM}
{$ifdef Win16}
  HMODULE = THandle; {HINST}
  HGLOBAL = THandle;
{$else Win16}
  HMODULE = PtrUint;
  HGLOBAL = PtrUint;
{$endif Win16}
  //New types
  TFPResourceHandle = PtrUInt;
  TFPResourceHMODULE = PtrUInt;
  TFPResourceHGLOBAL = PtrUInt;
{$ifndef Win16}
{$ifdef FPC_OS_UNICODE}
  {roozbeh : maybe it shoud be moved after ifndef mswindows,as there is one declared in wince,base.inc}
  MAKEINTRESOURCE = pwidechar;
{$else}
  MAKEINTRESOURCE = PAnsiChar;
{$endif}  
{$endif not Win16}
  
{$ifndef MSWINDOWS }
{ windows has this in the windows unit. It probably would better
  fit into the classes/sysutils unit but because it is resource
  related, I put it here (FK)
}
{$ifndef CPUJVM}
const
  RT_CURSOR = MAKEINTRESOURCE(1);
  RT_BITMAP = MAKEINTRESOURCE(2);
  RT_ICON = MAKEINTRESOURCE(3);
  RT_MENU = MAKEINTRESOURCE(4);
  RT_DIALOG = MAKEINTRESOURCE(5);
  RT_STRING = MAKEINTRESOURCE(6);
  RT_FONTDIR = MAKEINTRESOURCE(7);
  RT_FONT = MAKEINTRESOURCE(8);
  RT_ACCELERATOR = MAKEINTRESOURCE(9);
  RT_RCDATA = MAKEINTRESOURCE(10);
  RT_MESSAGETABLE = MAKEINTRESOURCE(11);
  RT_GROUP_CURSOR = MAKEINTRESOURCE(12);
  RT_GROUP_ICON = MAKEINTRESOURCE(14);
  RT_VERSION = MAKEINTRESOURCE(16);
  RT_ANICURSOR = MAKEINTRESOURCE(21);
  RT_ANIICON = MAKEINTRESOURCE(22);
  RT_HTML = MAKEINTRESOURCE(23);
  RT_MANIFEST = MAKEINTRESOURCE(24);
{$else CPUJVM}
const
  RT_CURSOR = '#1';
  RT_BITMAP = '#2';
  RT_ICON = '#3';
  RT_MENU = '#4';
  RT_DIALOG = '#5';
  RT_STRING = '#6';
  RT_FONTDIR = '#7';
  RT_FONT = '#8';
  RT_ACCELERATOR = '#9';
  RT_RCDATA = '#10';
  RT_MESSAGETABLE = '#11';
  RT_GROUP_CURSOR = '#12';
  RT_GROUP_ICON = '#14';
  RT_VERSION = '#16';
  RT_ANICURSOR = '#21';
  RT_ANIICON = '#22';
  RT_HTML = '#23';
  RT_MANIFEST = '#24';
{$endif CPUJVM}

{$endif MSWINDOWS }

// Win32 API compatible Resource callbacks
type
  EnumResTypeProc = function(ModuleHandle : TFPResourceHMODULE; ResourceType : TResourceId; lParam : PtrInt) : LongBool; stdcall;
  EnumResNameProc = function(ModuleHandle : TFPResourceHMODULE; ResourceType, ResourceName : TResourceId; lParam : PtrInt) : LongBool; stdcall;
  EnumResLangProc = function(ModuleHandle : TFPResourceHMODULE; ResourceType, ResourceName : TResourceId; IDLanguage : word; lParam : PtrInt) : LongBool; stdcall;

// Useful functions (macros in win32 headers)
function Is_IntResource(aStr : PAnsiChar) : boolean; {$ifdef SYSTEMINLINE}inline;{$endif}
function MakeLangID(primary,sub : word) : word; {$ifdef SYSTEMINLINE}inline;{$endif}

// Win32 API compatible Resource functions
{$ifndef Win16}
Function HINSTANCE : TFPResourceHMODULE;
{$endif Win16}
Function EnumResourceTypes(ModuleHandle : TFPResourceHMODULE; EnumFunc : EnumResTypeProc; lParam : PtrInt) : LongBool;
Function EnumResourceNames(ModuleHandle : TFPResourceHMODULE; ResourceType : PAnsiChar; EnumFunc : EnumResNameProc; lParam : PtrInt) : LongBool;
Function EnumResourceLanguages(ModuleHandle : TFPResourceHMODULE; ResourceType, ResourceName : PAnsiChar; EnumFunc : EnumResLangProc; lParam : PtrInt) : LongBool;
{$ifndef Win16}
Function FindResource(ModuleHandle: TFPResourceHMODULE; ResourceName, ResourceType: PAnsiChar): TFPResourceHandle;
Function FindResourceEx(ModuleHandle: TFPResourceHMODULE; ResourceType, ResourceName: PAnsiChar; Language : word): TFPResourceHandle;
Function LoadResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): TFPResourceHGLOBAL;
Function SizeofResource(ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): LongWord;
Function LockResource(ResData: TFPResourceHGLOBAL): Pointer;
Function UnlockResource(ResData: TFPResourceHGLOBAL): LongBool;
Function FreeResource(ResData: TFPResourceHGLOBAL): LongBool;
{$endif Win16}
{$ifdef FPC_HAS_FEATURE_ANSISTRINGS}
Function FindResource(ModuleHandle: TFPResourceHMODULE; const ResourceName, ResourceType: AnsiString): TFPResourceHandle;
Function FindResourceEx(ModuleHandle: TFPResourceHMODULE; const ResourceType, ResourceName: AnsiString; Language : word): TFPResourceHandle;
{$ifndef Win16}
Function FindResource(ModuleHandle: TFPResourceHMODULE; const ResourceName: AnsiString; ResourceType: PAnsiChar): TFPResourceHandle;
Function FindResourceEx(ModuleHandle: TFPResourceHMODULE; ResourceType: PAnsiChar; const ResourceName: AnsiString; Language : word): TFPResourceHandle;
Function FindResource(ModuleHandle: TFPResourceHMODULE; ResourceName: PAnsiChar; const ResourceType: AnsiString): TFPResourceHandle;
Function FindResourceEx(ModuleHandle: TFPResourceHMODULE; const ResourceType: AnsiString; ResourceName: PAnsiChar; Language : word): TFPResourceHandle;
{$endif Win16}
{$endif}

{ JVM Notes: predeclare the callback types to prevent a runtime crash (classformaterror: duplicate entry in innerclasses attribute) }
type
  THINSTANCEFunc = function : TFPResourceHMODULE;
  TEnumResourceTypesFunc = function (ModuleHandle : TFPResourceHMODULE; EnumFunc : EnumResTypeProc; lParam : PtrInt) : LongBool;
  TEnumResourceNamesFunc = function (ModuleHandle : TFPResourceHMODULE; ResourceType : TResourceId; EnumFunc : EnumResNameProc; lParam : PtrInt) : LongBool;
  TEnumResourceLanguagesFunc = function (ModuleHandle : TFPResourceHMODULE; ResourceType,ResourceName : TResourceId; EnumFunc : EnumResLangProc; lParam : PtrInt) : LongBool;
  TFindResourceFunc = function (ModuleHandle: TFPResourceHMODULE; ResourceName, ResourceType: TResourceId): TFPResourceHandle;
  TFindResourceExFunc = function (ModuleHandle: TFPResourceHMODULE; ResourceType, ResourceName: TResourceId; Language : word): TFPResourceHandle;
  TLoadResourceFunc = function (ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): TFPResourceHGLOBAL;
  TSizeofResourceFunc = function (ModuleHandle: TFPResourceHMODULE; ResHandle: TFPResourceHandle): LongWord;
{$if not declared(TLockResourceFunc)}
  TLockResourceFunc = function (ResData: TFPResourceHGLOBAL): Pointer;
{$endif not declared}
  TUnlockResourceFunc = function (ResData: TFPResourceHGLOBAL): LongBool;
  TFreeResourceFunc = function (ResData: TFPResourceHGLOBAL): LongBool;

type
  TResourceManager = record
    HINSTANCEFunc : THINSTANCEFunc;
    EnumResourceTypesFunc : TEnumResourceTypesFunc;
    EnumResourceNamesFunc : TEnumResourceNamesFunc;
    EnumResourceLanguagesFunc : TEnumResourceLanguagesFunc;
    FindResourceFunc : TFindResourceFunc;
    FindResourceExFunc : TFindResourceExFunc;
    LoadResourceFunc : TLoadResourceFunc;
    SizeofResourceFunc : TSizeofResourceFunc;
    LockResourceFunc : TLockResourceFunc;
    UnlockResourceFunc : TUnlockResourceFunc;
    FreeResourceFunc : TFreeResourceFunc;
  end;

procedure GetResourceManager (var Manager : TResourceManager);
procedure SetResourceManager (const New : TResourceManager);

