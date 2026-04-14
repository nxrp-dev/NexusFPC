program tw41712;
{$mode delphi}
type
  TTestObject = class
    procedure Foo<T: class>;
  end;

procedure TTestObject.Foo<T>;
begin
end;

begin
  with TTestObject.Create do
    Foo<TTestObject>;
end.
