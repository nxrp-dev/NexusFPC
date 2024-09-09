{
    This file is part of the Free Pascal run time library.
    Copyright (c) 1999-2000 by the Free Pascal development team

    Textrec record definition

    See the file COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

{
  This file contains the definition of the textrec record.
  It is put separately, so it is available outside the system
  unit without sacrificing TP compatibility.
}

const
{$ifdef CPUAVR}
  TextRecNameLength = 16;
  TextRecBufSize    = 16;
{$else CPUAVR}
  TextRecNameLength = 256;
  TextRecBufSize    = 256;
{$endif CPUAVR}
type
  TLineEndStr = string [3];
  TextBuf = array[0..TextRecBufSize-1] of ansichar;
  TTextBuf = TextBuf;

  { using packed makes the compiler to generate ugly code on some CPUs, further
    using packed causes the compiler to handle arrays of text wrongly, see  see tw0754 e.g. on arm  }
  TextRec = Record
{$ifdef CPUJVM}
  type
    FileFunc = procedure(var T: TextRec);
  public
{$endif}
    Handle    : THandle;
{$if defined(CPU8) or defined(CPU16)}
    Mode      : Word;
{$else}
    Mode      : longint;
{$endif}
    bufsize   : SizeInt;
    _private  : SizeInt;
    bufpos,
    bufend    : SizeInt;
    bufptr    : ^textbuf;
    openfunc,
    inoutfunc,
    flushfunc,
{$ifndef CPUJVM}
    closefunc : codepointer;
    UserData  : array[1..32] of byte;
{$else CPUJVM}
    closefunc : FileFunc;
    UserData  : array[1..32] of pointer;
{$endif CPUJVM}
    name      : array[0..textrecnamelength-1] of TFileTextRecChar;
    LineEnd   : TLineEndStr;
    buffer    : textbuf;
    CodePage  : TSystemCodePage;
{$ifdef FPC_HAS_FEATURE_UNICODESTRINGS}
{$ifndef CPUJVM}
    FullName  : Pointer;
{$else CPUJVM}
    FullName  : unicodestring;
{$endif CPUJVM}
{$endif FPC_HAS_FEATURE_UNICODESTRINGS}
  End;

