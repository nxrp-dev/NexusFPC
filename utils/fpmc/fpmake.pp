{$ifndef ALLPACKAGES}
{$mode objfpc}{$H+}
program fpmake;

uses
{$ifdef unix}
  cthreads,
{$endif}
  fpmkunit, sysutils;
{$endif ALLPACKAGES}

procedure add_fpmc(const ADirectory: string);

Var
  P : TPackage;
  T : TTarget;

begin
  With Installer do
    begin
    P:=AddPackage('utils-fpmc');
    P.ShortName:='fpmc';

    P.Author := '<various>';
    P.License := 'LGPL with modification';
    P.HomepageURL := 'www.freepascal.org';
    P.Email := '';
    P.Description := 'Free Pascal Message Compiler.';
    P.NeedLibC:= false;

    P.Directory:=ADirectory;
    P.Version:='3.3.1';

    P.OSes := [win32, win64];

    P.Dependencies.Add('fcl-base');

    T:=P.Targets.AddProgram('fpmc.pp');
    T.Dependencies.AddUnit('msgcomp');

    T:=P.Targets.AddUnit('msgcomp.pp');
    T.install:=false;
    T.ResourceStrings:=true;
    end;
end;

{$ifndef ALLPACKAGES}
begin
  add_fpmc('');
  Installer.Run;
end.
{$endif ALLPACKAGES}




