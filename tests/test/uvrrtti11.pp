{ %NORUN  }
unit uvrrtti11;

{$Mode ObjFPC}{$H+}
{$VariantRTTI On}

interface

type
  TVarRec = record
  case Boolean of
  True: (case Boolean of
    True:(AA: Integer);
    False:(AB: Double);
  );
  False: (C, D: Word);
  end;

implementation

end.
