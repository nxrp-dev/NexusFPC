{ %OPT=-O- -Ooregvar -CR }
program tw41558;
{$mode objfpc}
{$modeswitch advancedrecords}

type
  TLazEditDisplayTokenBound = record
    Physical,
    Logical,
    Offset: Integer;

    procedure Init; inline;
  end;

  TLazCustomEditTextAttribute = class
    FStartX: TLazEditDisplayTokenBound;
    procedure SetStartX(AValue: TLazEditDisplayTokenBound); virtual;
    procedure SetFrameBoundsLog; inline;
  end;

  TSynEditMarkupHighlightMatches = class
    function  HasDisplayAbleMatches: Boolean; virtual;
    function  GetMarkupAttributeAtRowCol2: TLazCustomEditTextAttribute;
  end;

procedure TLazEditDisplayTokenBound.Init;
begin
end;

procedure TLazCustomEditTextAttribute.SetStartX(AValue: TLazEditDisplayTokenBound);
begin
end;

procedure TLazCustomEditTextAttribute.SetFrameBoundsLog;
var
  b: TLazEditDisplayTokenBound;
begin
  b.Init;
  SetStartX(b);
end;

function TSynEditMarkupHighlightMatches.HasDisplayAbleMatches: Boolean;
begin
  Result := False;
end;

function TSynEditMarkupHighlightMatches.GetMarkupAttributeAtRowCol2: TLazCustomEditTextAttribute;
begin
  Result := nil;
  if not HasDisplayAbleMatches then
    exit;
  Result.SetFrameBoundsLog;
end;

var
  O: TSynEditMarkupHighlightMatches;
  R: TObject;
begin
  O := TSynEditMarkupHighlightMatches.Create;
  R := O.GetMarkupAttributeAtRowCol2;
  if PtrUInt(R) <> 0 then
    halt(1);
  O.Free;
end.
