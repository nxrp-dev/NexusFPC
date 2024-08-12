program Project1;

{$mode objfpc}{$H+}
{$ModeSwitch duplicatelocals}
{$ModeSwitch advancedrecords}
 
type
  TClass1 = class(TObject)
  public
    X: Integer;
    procedure Proc1(X: Integer);
    procedure Proc2;
  end;

// Parameter has same name as member field.
// This is okay with duplicatelocals
procedure TClass1.Proc1(X: Integer);
begin
end;

// Local variable has same name as member field.
// This is okay with duplicatelocals, too.
procedure TClass1.Proc2;
var
  X: Integer;
begin
end;

// Same for objects and managed records. (Though in Delphi mode, which implicitly enables duplicatelocals, disallowed specifically for objects.)
type
  TRecord1 = record
  public
    X: Integer;
    procedure Proc1(X: Integer);
    procedure Proc2;
  end;

procedure TRecord1.Proc1(X: Integer);
begin
end;

procedure TRecord1.Proc2;
var
  X: Integer;
begin
end;

type
  TObject1 = object
  public
    X: Integer;
    procedure Proc1(X: Integer);
    procedure Proc2;
  end;

procedure TObject1.Proc1(X: Integer);
begin
end;

procedure TObject1.Proc2;
var
  X: Integer;
begin
end;

begin
end.

