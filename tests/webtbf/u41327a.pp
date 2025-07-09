unit u41327a;

{$mode objfpc}
{$modeswitch advancedrecords}

interface
type
  generic TTypeWrapper<T> = record
    data: T;
  
    class operator =(const lhs, rhs: specialize TTypeWrapper<T>): Boolean;inline;
    class operator <>(const lhs, rhs: specialize TTypeWrapper<T>): Boolean;inline;
    class operator Explicit(const rec: specialize TTypeWrapper<T>): T;inline;
    class operator Explicit(const value: T): specialize TTypeWrapper<T>;inline;
  end;
  
  
implementation

class operator TTypeWrapper.=(const lhs, rhs: specialize TTypeWrapper<T>): Boolean;
begin
  result:=lhs.data=rhs.data;
end;
  
class operator TTypeWrapper.<>(const lhs, rhs: specialize TTypeWrapper<T>): Boolean;
begin
  result:=lhs.data<>rhs.data;
end;
  
class operator TTypeWrapper.Explicit(const rec: specialize TTypeWrapper<T>): T;
begin
  result:=rec.data;
end;
  
class operator TTypeWrapper.Explicit(const value: T): specialize TTypeWrapper<T
  >;
begin
  result.data:=value;
end;

type
  TIntegerWrapper = specialize TTypeWrapper<Integer>;
  THWND = type TIntegerWrapper;
  THandle = type TIntegerWrapper;
  
end.
