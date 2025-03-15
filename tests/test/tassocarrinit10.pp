{$Mode ObjFpc}

type
  TCharType = (ctWhitespace, ctSpecial, ctNumber, ctChar);
var
  MyArray: array[Char] of TCharType = [
    #00..#32: ctWhitespace;
    #33..#47: ctSpecial;
    #48..#57: ctNumber;
    #58..#64: ctSpecial;
    #65..#90: ctChar;
    #91..#96: ctSpecial;
    #97..#122: ctChar;
    #123..#255: ctSpecial
  ];
  c: char;
begin
  for c:=#00 to #255 do
    case c of
      #00..#32: if MyArray[c] <> ctWhitespace then halt(1);
      '0'..'9': if MyArray[c] <> ctNumber then halt(2);
      'A'..'Z', 'a'..'z': if MyArray[c] <> ctChar  then halt(3);
      otherwise if MyArray[c] <> ctSpecial then halt(4);
    end;
  WriteLn('Ok');
end.
