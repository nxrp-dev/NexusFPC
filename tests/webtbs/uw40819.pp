unit uw40819;

{$mode delphi}

interface

function inArray(needle: Integer; const a: array of Integer; out idx: Integer): Boolean;

implementation

function inArray(needle: Integer; const a: array of Integer; out idx: Integer): Boolean;
begin
  idx := 0;
  result := false;
end;

function inArray<T>(needle: T; const a: array of T; out idx: Integer): Boolean;
begin
  idx := 0;
  result := false;
end;

end.
