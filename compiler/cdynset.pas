{
    Dynamic set

    Copyright (c) 2007-2026 by Florian Klaempfl

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 ****************************************************************************
}
unit cdynset;

{$i fpcdefs.inc}
{$modeswitch advancedrecords}

  interface


    type
      PDynSet = ^TDynSet;
      TDynSet = record
        procedure SetEmpty; inline;
        function IsEmpty: boolean; inline;
        class function Empty: TDynSet; static; inline; { .SetEmpty is preferred, but := Empty avoids warnings when initializing local variables. }

        procedure Include(e: integer);
        procedure IncludeSet(const s: TDynSet);
        procedure Exclude(e: integer);
        procedure ExcludeSet(const s: TDynSet);
        class operator in(e: integer; const s: TDynSet): boolean;
        procedure Union(const s2: TDynSet; out r: TDynSet);
        procedure Intersect(const s2: TDynSet; out r: TDynSet);
        procedure Diff(const s2: TDynSet; out r: TDynSet);
        class operator =(const a, b: TDynSet): boolean;
        function GetCount: SizeInt; { Get the last index set + 1, or 0 for empty set. }
        procedure Print(var f: text);

        class operator Initialize(var self: TDynSet);
        class operator Finalize(var self: TDynSet);
        class operator Copy(constref b: TDynSet; var self: TDynSet);
        class operator AddRef(var self: TDynSet);

      private type
        PDynamic = ^TDynamic;
        TDynamic = record
          n: SizeUint; { In bits; divisible by BaseBits. }
          data: array[0 .. 0] of PtrUint;
          function ZeroedStartingFromCell(c: SizeUint): boolean;
        end;

      const
        BaseBits = bitsizeof(PtrUint);
        StaticTag = 1 shl 0;
        StaticShift = 1;

        procedure Resize(n: SizeUint); { Careful: occasionally assumed to work like “ResizeAndForceToBeDynamic”, so it can’t leave the set static. }
        procedure SetCopyFromDyn(d: PDynamic);

      var
        { If tagged and StaticTag <> 0, tagged shr StaticShift is the static set with bitsizeof(PtrUint) - 1 bits.
          If tagged and StaticTag = 0, set data is dyn. }
      case uint32 of
        0: (tagged: PtrUint);
        1: (dyn: PDynamic);
      end;

  implementation

    uses
      cutils;

    procedure TDynSet.SetEmpty;
      begin
        if tagged and StaticTag=0 then
          FreeMem(dyn);
        tagged:=StaticTag;
      end;


    function TDynSet.IsEmpty: boolean;
      begin
        result:=(tagged=StaticTag) or (tagged and StaticTag=0) and dyn^.ZeroedStartingFromCell(0);
      end;


    class function TDynSet.Empty: TDynSet;
      begin
        PDynSet(@result)^.SetEmpty;
      end;


    procedure TDynSet.Include(e: integer);
      begin
        if (tagged and StaticTag<>0) and (e<BaseBits-StaticShift) then
          begin
            { self is static and e fits. }
            tagged:=tagged or PtrUint(1 shl StaticShift) shl e;
            exit;
          end;
        { self is static and the previous check was not met, which means e does not fit and self must be made dynamic; or self is dynamic and e does not fit. }
        if (tagged and StaticTag<>0) or (e>=SizeInt(dyn^.n)) then
          Resize(1+e);
        PPtrUint(dyn^.data)[cardinal(e) div BaseBits]:=
          PPtrUint(dyn^.data)[cardinal(e) div BaseBits] or PtrUint(1) shl (cardinal(e) mod BaseBits);
      end;


    procedure TDynSet.IncludeSet(const s: TDynSet);
      var
        i : SizeInt;
      begin
        if tagged and StaticTag<>0 then
          begin
            if s.tagged and StaticTag<>0 then
              begin
                { Both are static. }
                tagged:=tagged or s.tagged;
                exit;
              end;
            { self is static, s is dynamic: resize to s. }
            Resize(s.dyn^.n);
          end;
        { self is dynamic. }
        if s.tagged and StaticTag<>0 then
          begin
            { s is static: combine with the first cell. }
            dyn^.data[0]:=dyn^.data[0] or s.tagged shr StaticShift;
            exit;
          end;
        if dyn^.n<s.dyn^.n then
          Resize(s.dyn^.n);
        for i:=0 to SizeInt(s.dyn^.n div BaseBits)-1 do
          PPtrUint(dyn^.data)[i]:=PPtrUint(dyn^.data)[i] or PPtrUint(s.dyn^.data)[i];
      end;


    procedure TDynSet.Exclude(e: integer);
      begin
        if (tagged and StaticTag<>0) then
          begin
            if e<BaseBits-StaticShift then
              { self is static and e fits. }
              tagged:=tagged and PtrUint(not (PtrUint(1 shl StaticShift) shl e));
            exit; { if self is static and e doesn’t fit, simply nothing to do. }
          end;
        if cardinal(e)<dyn^.n then
          PPtrUint(dyn^.data)[cardinal(e) div BaseBits]:=
            PPtrUint(dyn^.data)[cardinal(e) div BaseBits] and PtrUint(not (PtrUint(1) shl (cardinal(e) mod BaseBits)));
      end;


    procedure TDynSet.ExcludeSet(const s: TDynSet);
      var
        i : SizeInt;
      begin
        if tagged and StaticTag<>0 then
          begin
            if s.tagged and StaticTag<>0 then
              { Both are static. }
              tagged:=tagged and not s.tagged+StaticTag { Careful with StaticTag :D }
            else
              { self is static, s is dynamic: exclude the first cell. }
              tagged:=tagged and not (s.dyn^.data[0] shl StaticShift);
            exit;
          end;
        { self is dynamic. }
        if s.tagged and StaticTag<>0 then
          begin
            { s is static: combine with the first cell. }
            dyn^.data[0]:=dyn^.data[0] and not (s.tagged shr StaticShift);
            exit;
          end;
        { s is dynamic. }
        for i:=0 to SizeInt(SizeUint(min(SizeInt(dyn^.n),SizeInt(s.dyn^.n))) div BaseBits)-1 do
          PPtrUint(dyn^.data)[i]:=PPtrUint(dyn^.data)[i] and not PPtrUint(s.dyn^.data)[i];
      end;


    class operator TDynSet.in(e: integer; const s: TDynSet): boolean;
      begin
        if s.tagged and StaticTag<>0 then
          result:=(cardinal(e)<BaseBits-StaticShift) and boolean(s.tagged shr (e+StaticShift) and 1)
        else
          result:=(cardinal(e)<s.dyn^.n) and boolean(PPtrUint(s.dyn^.data)[cardinal(e) div BaseBits] shr (cardinal(e) mod BaseBits) and 1);
      end;


    procedure TDynSet.Union(const s2: TDynSet; out r: TDynSet);
      begin
        r:=self;
        r.IncludeSet(s2);
      end;


    procedure TDynSet.Intersect(const s2: TDynSet; out r: TDynSet);
      var
        selfminuss2, s2minusself: TDynSet;
      begin
        { Function is not used anyway so don’t bother with optimality for now... }
        self.Diff(s2,selfminuss2);
        s2.Diff(self,s2minusself);
        self.Diff(selfminuss2,r);
        r.ExcludeSet(s2minusself);
      end;


    procedure TDynSet.Diff(const s2: TDynSet; out r: TDynSet);
      begin
        { Fast path for all static, can be removed completely. Note in case of “var r” r must be tested for StaticFlag too, or cleared (“out r” automatically clears r). }
        if tagged and s2.tagged and StaticTag<>0 then
          begin
            r.tagged:=tagged and not s2.tagged+StaticTag; { Careful with StaticTag :D }
            exit;
          end;
        r:=self;
        r.ExcludeSet(s2);
      end;


    class operator TDynSet.=(const a, b: TDynSet): boolean;
      begin
        if a.tagged and StaticTag<>0 then
          if b.tagged and StaticTag<>0 then
            result:=a.tagged=b.tagged
          else
            result:=(a.tagged shr StaticShift=b.dyn^.data[0]) and b.dyn^.ZeroedStartingFromCell(1)
        else
          if b.tagged and StaticTag<>0 then
            result:=(a.dyn^.data[0]=b.tagged shr StaticShift) and a.dyn^.ZeroedStartingFromCell(1)
          else
            if a.dyn^.n<=b.dyn^.n then
              result:=(CompareByte(a.dyn^.data[0],b.dyn^.data[0],a.dyn^.n div bitsizeof(byte))=0) and b.dyn^.ZeroedStartingFromCell(a.dyn^.n div BaseBits)
            else
              result:=(CompareByte(a.dyn^.data[0],b.dyn^.data[0],b.dyn^.n div bitsizeof(byte))=0) and a.dyn^.ZeroedStartingFromCell(b.dyn^.n div BaseBits);
      end;


    function TDynSet.GetCount : SizeInt;
      begin
        if tagged and StaticTag<>0 then
          result:={$if sizeof(PtrUint)>4}BsrQWord{$else}BsrDWord{$endif}(tagged) { Assuming StaticTag = 1 and no other tags, automatically gives the correct count. }
        else
          begin
            result:=dyn^.n;
            repeat
              dec(result,BaseBits);
            until (result=0) or (PPtrUint(dyn^.data)[SizeUint(result) div BaseBits]<>0);
            if PPtrUint(dyn^.data)[SizeUint(result) div BaseBits]<>0 then
              inc(result,1+{$if sizeof(PtrUint)>4}BsrQWord{$else}BsrDWord{$endif}(PPtrUint(dyn^.data)[SizeUint(result) div BaseBits]));
          end;
      end;


    procedure TDynSet.Print(var f: text);
      var
        i : integer;
        first : boolean;
      begin
        first:=true;
        for i:=0 to GetCount-1 do
          if i in self then
            begin
              if not(first) then
                write(f,',');
              write(f,i);
              first:=false;
            end;
      end;


    class operator TDynSet.Initialize(var self: TDynSet);
      begin
        self.tagged:=StaticTag;
      end;


    class operator TDynSet.Finalize(var self: TDynSet);
      begin
        self.SetEmpty;
      end;


    class operator TDynSet.Copy(constref b: TDynSet; var self: TDynSet);
      begin
        if @self=@b then
          exit;
        self.SetEmpty;
        if b.tagged and StaticTag<>0 then
          self.tagged:=b.tagged
        else
          self.SetCopyFromDyn(b.dyn);
      end;


    class operator TDynSet.AddRef(var self: TDynSet);
      begin
        if self.tagged and StaticTag=0 then
          self.SetCopyFromDyn(self.dyn);
      end;


    function TDynSet.TDynamic.ZeroedStartingFromCell(c: SizeUint): boolean;
      var
        e : SizeUint;
      begin
        e:=n div BaseBits;
        while (c<e) and (PPtrUint(data)[c]=0) do
          inc(c);
        result:=c>=e;
      end;


    procedure TDynSet.Resize(n: SizeUint);
      var
        oldn,sz,tmp : PtrUint;
      begin
        n:=(n+(BaseBits-1)) and PtrUint(-BaseBits);
        sz:=PtrUint(@TDynamic(nil^).data)+n div bitsizeof(byte);
        if tagged and StaticTag<>0 then
          begin
            tmp:=tagged;
            dyn:=AllocMem(sz);
            dyn^.data[0]:=tmp shr StaticShift;
          end
        else
          begin
            oldn:=dyn^.n;
            ReallocMem(dyn,sz);
            if n>oldn then
              FillChar(PPtrUint(dyn^.data)[oldn div BaseBits],SizeUint(n-oldn) div bitsizeof(byte),0);
          end;
        dyn^.n:=n;
      end;


    procedure TDynSet.SetCopyFromDyn(d: PDynamic);
      var
        sz : SizeUint;
      begin
        sz:=PtrUint(@TDynamic(nil^).data)+d^.n div bitsizeof(byte);
        dyn:=GetMem(sz);
        Move(d^,dyn^,sz);
      end;


end.

