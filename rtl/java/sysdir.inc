{
    This file is part of the Free Pascal Run time library.

    See the File COPYING.FPC, included in this distribution,
    for details about the copyright.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 **********************************************************************}

procedure do_mkdir(s: unicodestring);
const
  FileAccessDenied = 5;
begin
  DoDirSeparators(s);
  try
    if not _JIFile.Create(s).MkDir then
      InOutRes := FileAccessDenied;
  except on _JLSecurityException do
    InOutRes := FileAccessDenied;
  end;
end;

procedure do_rmdir(s: unicodestring);
const
  FileAccessDenied = 5;
  CannotRemoveCurrentDirectory = 16;
begin
  DoDirSeparators(s);
  if s = '.' then
    InOutRes := CannotRemoveCurrentDirectory
  else if s = '..' then
    InOutRes := FileAccessDenied
  else
  begin
    try
      if not _JIFile.Create(s).Delete then
        InOutRes := FileAccessDenied;
    except on _JLSecurityException do
      InOutRes := FileAccessDenied;
    end;
  end;
end;

procedure do_getdir(drivenr: byte; var dir: unicodestring);
begin
  dir := JLSystem.GetProperty('user.dir');
end;
