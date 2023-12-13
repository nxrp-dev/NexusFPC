{
    Copyright (c) 2022-2024 by Florian Klaempfl and J. Gareth "Kit" Moreton

    This unit implements the x86-specific assembly node and vectorisation
    code for x86.

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
unit nx86bas;

{$i fpcdefs.inc}

interface

  uses
    symtype,
    cgbase,
    cpubase,
    node,
    nbas,
    ncgbas,
    aasmtai;

  type
    Tx86AsmNode = class(TCGAsmNode)
{$ifdef DEBUG_NODE_XML}
      procedure XMLPrintNodeData(var T: Text); override;
    protected
      function XMLFormatOp(const Oper: POper): string; override;
      procedure XMLProcessInstruction(var T: Text; p: tai); override;
{$endif DEBUG_NODE_XML}
    end;

    tx86statementnode = class(tcgstatementnode)
    private
      function vectorize_assign: TNode;
    public
      function simplify(forinline : boolean) : tnode; override;
    end;

implementation

  uses
{$ifdef DEBUG_NODE_XML}
    cgutils,
    itcpugas,
    aasmcpu,
{$endif DEBUG_NODE_XML}
    globtype,globals,
    verbose,cutils,compinnr,
    cpuinfo,
    nld,nmem,ncnv,nadd,
    symconst,symdef,symsym,
    defutil,defcmp,constexp,
    htypechk;

{$ifdef DEBUG_NODE_XML}
  function Tx86AsmNode.XMLFormatOp(const Oper: POper): string;
    begin
      case Oper^.typ of
        top_const:
          begin
            case Oper^.val of
              -15..15:
                Result := '$' + tostr(Oper^.val);
              $10..$FF:
                Result := '$0x' + hexstr(Oper^.val, 2);
              $100..$FFFF:
                Result := '$0x' + hexstr(Oper^.val, 4);
  {$ifdef CPU64}
              $10000..$FFFFFFFF:
                Result := '$0x' + hexstr(Oper^.val, 8);
              else
                Result := '$0x' + hexstr(Oper^.val, 16);
  {$else CPU64}
              else
                Result := '$0x' + hexstr(Oper^.val, 8);
  {$endif CPU64}
            end;
          end;

        top_ref:
          with Oper^.ref^ do
            begin
              if segment <> NR_NO then
                Result := gas_regname(segment) + ':'
              else
                Result := '';

              if Assigned(symbol) then
                begin
                  Result := Result + symbol.Name;
                  if offset > 0 then
                    Result := Result + '+';
                end;

              if offset <> 0 then
                Result := Result + tostr(offset)
              else
                Result := Result;

              if (base <> NR_NO) or (index <> NR_NO) then
                begin
                  Result := Result + '(';

                  if base <> NR_NO then
                    begin
                      Result := Result + gas_regname(base);
                      if index <> NR_NO then
                        Result := Result + ',';
                    end;

                  if index <> NR_NO then
                    Result := Result + gas_regname(index);

                  if scalefactor <> 0 then
                    Result := Result + ',' + tostr(scalefactor) + ')'
                  else
                    Result := Result + ')';
                end;
            end;
        else
          Result := inherited XMLFormatOp(Oper);
      end;
    end;


  procedure Tx86AsmNode.XMLProcessInstruction(var T: Text; p: tai);
    var
      ThisOp, ThisOper: string;
      X: Integer;
    begin
      if p.typ = ait_instruction then
        begin
          ThisOp := gas_op2str[taicpu(p).opcode] + cond2str[taicpu(p).condition];
          if gas_needsuffix[taicpu(p).opcode] <> AttSufNONE then
            ThisOp := ThisOp + gas_opsize2str[taicpu(p).opsize];

          { Pad the opcode with spaces so the succeeding operands are aligned }
          XMLPadString(ThisOp, 7);

          Write(T, PrintNodeIndention, '  ', ThisOp); { Extra indentation to account for label formatting }
          for X := 0 to taicpu(p).ops - 1 do
            begin
              Write(T, ' ');

              ThisOper := XMLFormatOp(taicpu(p).oper[X]);
              if X < taicpu(p).ops - 1 then
                begin
                  ThisOper := ThisOper + ',';

                  XMLPadString(ThisOper, 7);
                end;

              Write(T, ThisOper);
            end;
          WriteLn(T);
        end
      else
        inherited XMLProcessInstruction(T, p);
    end;


  procedure Tx86AsmNode.XMLPrintNodeData(var T: Text);
    var
      hp: tai;
    begin
      if not Assigned(p_asm) then
        Exit;

      hp := tai(p_asm.First);
      while Assigned(hp) do
        begin
          XMLProcessInstruction(T, hp);
          hp := tai(hp.Next);
        end;
    end;
{$endif DEBUG_NODE_XML}


{*****************************************************************************
                              x86 vectorisation
*****************************************************************************}

  type
    TMMType = (mmtUndefined, mmtSingle, mmtDouble, mmtInteger);
    TMMOperation = (mmoUnknown, mmoAdd, mmoSub);

    TVectorStatement = record
      Statement: TStatementNode;
      Assignment: TAssignmentNode;
      Index: Integer;
    end;

  function GetSymbol(Node: TNode): TSym;
    begin
      Result := nil;
      while Node.nodetype = typeconvn do
        Node := TTypeConvNode(Node).left;

      if Node.nodetype <> loadn then
        { Direct symbol loads only }
        Exit;

      Result := TLoadNode(Node).symtableentry;
    end;


  function GetFieldDetails(StructureNode: TNode; out Def: TDef; out Sym: TSym; out FieldOffset, FieldSize: asizeint): Boolean;
    var
      RecordNode: TNode;
    begin
      Result := False;
      repeat
        case StructureNode.nodetype of
          subscriptn:
            begin
              RecordNode := TSubscriptNode(StructureNode).left;
              Def := RecordNode.resultdef;
              if Def.typ <> recorddef then
                { Records only }
                Exit;

              Sym := GetSymbol(RecordNode); { Don't worry if there's no symbol available yet }

              FieldOffset := TSubscriptNode(StructureNode).vs.fieldoffset;
              FieldSize := TSubscriptNode(StructureNode).vs.getsize;

              Result := True;
            end;
          else
            Exit;
        end;

        Break;
      until False;
    end;


  function tx86statementnode.vectorize_assign: TNode;
    var
      MMType: TMMType;
      MMOp: TMMOperation;
      NodeCount: Integer;
      CurrentStatement: TStatementNode;
      CurrentAssign,
      CurrentDestNode,
      LastNode,
      CurrentNode: TNode;

      CommonSym,
      CurrentSym: TSym;
      CommonDef,
      CurrentDef: TDef;

      CurrentOffset,
      CurrentSize: asizeint;

      CurrentBit, CurrentIndex: Integer;

      Coverage, FullCoverage: array[0..7] of Word;
      StatementNodes: array[0..15] of TVectorStatement;
      InitialAnalysis: array[0..15] of TNode;
      IndexSorted: array[0..15] of Integer;

      procedure VectorizeNodeTree(CurrentNode, ParentNode: TNode; RightNode: Boolean);
        var
          NextNode: TNode;
        begin
          if not Assigned(CurrentNode) then
            Exit;

          case CurrentNode.nodetype of
            subscriptn:
              begin
                { Just access the record as a whole }
                NextNode := TSubscriptNode(CurrentNode).PruneKeepLeft();
                if RightNode then
                  TBinaryNode(ParentNode).right := NextNode
                else
                  TUnaryNode(ParentNode).left := NextNode;

                CurrentNode.Free;
                VectorizeNodeTree(NextNode, ParentNode, RightNode);
              end;
            typeconvn,
            loadn:
              begin
                if CurrentNode.resultdef.typ <> recorddef then
                  InternalError(2023121230);
                VectorizeNodeTree(TUnaryNode(CurrentNode).left, CurrentNode, False);
              end;
            else
              begin
                if CurrentNode.resultdef <> nil then
                  CurrentNode.resultdef := CommonDef;

                if CurrentNode is TUnaryNode then
                  VectorizeNodeTree(TUnaryNode(CurrentNode).left, CurrentNode, False);

                if CurrentNode is TBinaryNode then
                  VectorizeNodeTree(TBinaryNode(CurrentNode).right, CurrentNode, True);
              end;
          end;
        end;

      function ProcessField(out Index: Integer): Boolean;
        var
          X: Integer;
          ThisDef: TDef;
          ThisSym: TSym;
          OperandOffset, OperandSize: asizeint;
        begin
          Result := False;
          Index := -1;

          case TSubscriptNode(CurrentDestNode).vs.vardef.typ of
            floatdef:
              case TFloatDef(TSubscriptNode(CurrentDestNode).vs.vardef).floattype of
                s32real:
                  begin
                    if MMType = mmtUndefined then
                      MMType := mmtSingle
                    else if MMType <> mmtSingle then
                      { Incompatible mix }
                      Exit;

                    if (CurrentSize <> 4) or ((CurrentOffset mod 4) <> 0) then
                      { Unaligned or a strange size }
                      Exit;

                    Index := CurrentOffset div 4;
                  end;
                s64real:
                  begin
                    if (CPUX86_HAS_SSE2 in cpu_capabilities[current_settings.cputype]) then
                      begin
                        if MMType = mmtUndefined then
                          MMType := mmtDouble
                        else if MMType <> mmtDouble then
                          { Incompatible mix }
                          Exit;

                        if (CurrentSize <> 8) or ((CurrentOffset mod 8) <> 0) then
                          { Unaligned or a strange size }
                          Exit;

                        Index := CurrentOffset div 8;
                      end
                    else
                      { Don't have the necessary CPU support }
                      Exit;
                  end;
                else
                  { Incompatible }
                  Exit;
              end;
            else
              { Incompatible }
              Exit;
          end;

          { Set the coverage }
          CurrentIndex := TSubscriptNode(CurrentDestNode).vs.fieldoffset div 16;
          CurrentBit := 1 shl (TSubscriptNode(CurrentDestNode).vs.fieldoffset mod 16);

          for X := 0 to CurrentSize - 1 do
            begin
              if (Coverage[CurrentIndex] and CurrentBit) <> 0 then
                { A field or overlapping union is written to more than once }
                Exit;

              Coverage[CurrentIndex] := Coverage[CurrentIndex] or CurrentBit;
              CurrentBit := CurrentBit shl 1;
              if CurrentBit >= 65536 then
                begin
                  Inc(CurrentIndex);
                  CurrentBit := 1;
                end;
            end;
          Result := True;
        end;


      procedure GetNextAssignment(RootStatement: TStatementNode; NodeType: TNodeType);
        begin
          CurrentDestNode := nil;
          CurrentStatement := TStatementNode(RootStatement.right);
          CurrentAssign := nil;
          if Assigned(CurrentStatement) then
            begin
              if CurrentStatement.nodetype <> statementn then
                InternalError(2022040401);

              CurrentAssign := TStatementNode(RootStatement.right).left;
              if not Assigned(CurrentAssign) then
                InternalError(2022040402);

              if CurrentAssign.nodetype <> assignn then
                begin
                  CurrentAssign := nil;
                  CurrentStatement := nil;
                end
              else
                begin
                  CurrentDestNode := TAssignmentNode(CurrentAssign).left;
                  if CurrentDestNode.nodetype <> NodeType then
                    begin
                      CurrentDestNode := nil;
                      CurrentStatement := nil;
                    end
                  else if (NodeType = subscriptn) then
                    if (TSubscriptNode(CurrentDestNode).left.resultdef <> CommonDef) or
                      (GetSymbol(TSubscriptNode(CurrentDestNode).left) <> CommonSym) then
                      begin
                        { Not the same record - break out }
                        CurrentDestNode := nil;
                        CurrentStatement := nil;
                      end;
                end;
            end;
        end;

      function AnalyseNodeSet(NodeSet: array of TNode): Boolean;
        var
          X: Integer;
          NextSet: array[0..15] of TNode;
          RootDef, ThisDef: TDef;
          RootSym, ThisSym: TSym;
          OperandOffset, OperandSize: asizeint;
        begin
          Result := False;

          if not Assigned(NodeSet[0]) then
            { Null node? }
            Exit;

          { Skip over type conversions }
          for X := 0 to NodeCount - 1 do
            while NodeSet[X].nodetype = typeconvn do
              begin
                if TTypeConvNode(NodeSet[X]).convtype <> tc_equal then
                  { Not possible }
                  Exit;
                NodeSet[X] := TUnaryNode(NodeSet[X]).left;
              end;

          FillChar(NextSet, SizeOf(NextSet), 0);

          for X := 1 to NodeCount - 1 do
            begin
              if not Assigned(NodeSet[X]) then
                { Null node? }
                Exit;

              if NodeSet[X].nodetype <> NodeSet[0].nodetype then
                { Different node types }
                Exit;
            end;

          case NodeSet[0].nodetype of
            subscriptn:
              begin
                { Check what is being loaded first }
                for X := 0 to NodeCount - 1 do
                  NextSet[X] := TSubscriptNode(NodeSet[X]).left;

                if not AnalyseNodeSet(NextSet) then
                  Exit;

                { Make sure the first node of the set loads from the same index
                  and is of the correct type }
                if not GetFieldDetails(NodeSet[0], RootDef, RootSym, OperandOffset, OperandSize) then
                  Exit;

                if ((TRecordDef(RootDef).size mod 16) <> 0) or
                  (TRecordDef(RootDef).size > 16) then
                  { Incompatible size }
                  Exit;

                case MMType of
                  mmtSingle:
                    begin
                      if (TSubscriptNode(NodeSet[0]).vs.vardef.typ <> floatdef) or
                        (TFloatDef(TSubscriptNode(NodeSet[0]).vs.vardef).floattype <> s32real) then
                        { Incompatible type }
                        Exit;

                      if (OperandOffset div 4) <> IndexSorted[0] then
                        { Shuffling not supported yet }
                        Exit;
                    end;

                  mmtDouble:
                    begin
                      if (TSubscriptNode(NodeSet[0]).vs.vardef.typ <> floatdef) or
                        (TFloatDef(TSubscriptNode(NodeSet[0]).vs.vardef).floattype <> s64real) then
                        { Incompatible type }
                        Exit;

                      if (OperandOffset div 8) <> IndexSorted[0] then
                        { Shuffling not supported yet }
                        Exit;
                    end;
                  else
                    InternalError(2023121220);
                end;

                for X := 1 to NodeCount - 1 do
                  begin
                    if not GetFieldDetails(NodeSet[X], ThisDef, ThisSym, OperandOffset, OperandSize) then
                      { Failed to get details for some reason }
                      Exit;

                    if (ThisDef <> RootDef) then
                      { Not the same record }
                      Exit;

                    case MMType of
                      mmtSingle:
                        begin
                          if (TSubscriptNode(NodeSet[X]).vs.vardef.typ <> floatdef) or
                            (TFloatDef(TSubscriptNode(NodeSet[X]).vs.vardef).floattype <> s32real) then
                            { Incompatible type }
                            Exit;

                          if (OperandOffset div 4) <> IndexSorted[X] then
                            { Shuffling not supported yet }
                            Exit;
                        end;

                      mmtDouble:
                        begin
                          if (TSubscriptNode(NodeSet[0]).vs.vardef.typ <> floatdef) or
                            (TFloatDef(TSubscriptNode(NodeSet[X]).vs.vardef).floattype <> s64real) then
                            { Incompatible type }
                            Exit;

                          if (OperandOffset div 8) <> IndexSorted[X] then
                            { Shuffling not supported yet }
                            Exit;
                        end;
                      else
                        InternalError(2023121221);
                    end;

                  end;

              end;
            loadn:
              begin
                if TLoadNode(NodeSet[0]).resultdef.typ <> recorddef then
                  { Records only for now }
                  Exit;

                RootSym := GetSymbol(TLoadNode(NodeSet[0]));
                if not Assigned(RootSym) then
                  { No symbol available }
                  Exit;

                for X := 1 to NodeCount - 1 do
                  if GetSymbol(TLoadNode(NodeSet[X])) <> RootSym then
                    { Different symbol }
                    Exit;

              end;
            addn, subn, muln:
              begin
                { Supported binary node }
                for X := 0 to NodeCount - 1 do
                  NextSet[X] := TBinaryNode(NodeSet[X]).left;

                if not AnalyseNodeSet(NextSet) then
                  Exit;

                for X := 0 to NodeCount - 1 do
                  NextSet[X] := TBinaryNode(NodeSet[X]).right;

                if not AnalyseNodeSet(NextSet) then
                  Exit;
              end
            else
              { Unsupported node type }
              Exit;
          end;

          Result := True;
        end;

    var
      X, Y: Integer;
    begin
      Coverage[0] := 0;
      Coverage[1] := 0;
      Coverage[2] := 0;
      Coverage[3] := 0;
      Coverage[4] := 0;
      Coverage[5] := 0;
      Coverage[6] := 0;
      Coverage[7] := 0;

      FullCoverage[0] := 0;
      FullCoverage[1] := 0;
      FullCoverage[2] := 0;
      FullCoverage[3] := 0;
      FullCoverage[4] := 0;
      FullCoverage[5] := 0;
      FullCoverage[6] := 0;
      FullCoverage[7] := 0;

      for X := Low(InitialAnalysis) to High(InitialAnalysis) do
        begin
          IndexSorted[X] := -1;
          InitialAnalysis[X] := nil;
        end;

      { Suppress compiler warning }
      StatementNodes[0].Statement := nil;
      StatementNodes[0].Assignment := nil;
      StatementNodes[0].Index := 0;

      FillChar(StatementNodes[0], SizeOf(StatementNodes), 0);

      Result := nil;
      CommonSym := nil;
      NodeCount := 1;
      MMType := mmtUndefined;
      MMOp := mmoUnknown;
      CurrentStatement := Self;
      CurrentAssign := left;
      if CurrentAssign.nodetype <> assignn then
        InternalError(2024072601);

      CurrentDestNode := TAssignmentNode(left).left;

      case CurrentDestNode.nodetype of
        subscriptn:
          begin
            if not GetFieldDetails(CurrentDestNode, CommonDef, CommonSym, CurrentOffset, CurrentSize) then
              Exit;

            if not Assigned(CommonSym) then
              { We need an available symbol }
              Exit;

            if ((TRecordDef(CommonDef).size mod 16) <> 0) or
              (TRecordDef(CommonDef).size > 16) then
              { Incompatible size }
              Exit;

            { Go through the record's fields to see which bytes are covered
              and what's just filler }
            for Y := 0 to TRecordDef(CommonDef).symtable.SymList.Count - 1 do
              if TSym(TRecordDef(CommonDef).symtable.SymList[Y]).typ = fieldvarsym then
                begin
                  CurrentIndex := TFieldVarSym(TRecordDef(CommonDef).symtable.SymList[Y]).fieldoffset div 16;
                  CurrentBit := 1 shl (TFieldVarSym(TRecordDef(CommonDef).symtable.SymList[Y]).fieldoffset mod 16);

                  for X := 0 to TFieldVarSym(TRecordDef(CommonDef).symtable.SymList[Y]).getsize - 1 do
                    begin
                      FullCoverage[CurrentIndex] := FullCoverage[CurrentIndex] or CurrentBit;
                      CurrentBit := CurrentBit shl 1;
                      if CurrentBit >= 65536 then
                        begin
                          Inc(CurrentIndex);
                          CurrentBit := 1;
                        end;
                    end;
                end;

            { Process the first field }
            if not ProcessField(StatementNodes[0].Index) then
              Exit;

            StatementNodes[0].Statement := Self;
            StatementNodes[0].Assignment := TAssignmentNode(CurrentAssign);

            { Switch to the next node }
            GetNextAssignment(Self, subscriptn);

            while Assigned(CurrentDestNode) and (NodeCount <= 15) do
              begin
                if not GetFieldDetails(CurrentDestNode, CurrentDef, CurrentSym, CurrentOffset, CurrentSize) then
                  Break;

                if (CurrentSym <> CommonSym) or
                  (CurrentDef <> CommonDef) then
                  { Different records }
                  Break;

                { Process this field }
                if not ProcessField(StatementNodes[NodeCount].Index) then
                  Break;

                StatementNodes[NodeCount].Statement := CurrentStatement;
                StatementNodes[NodeCount].Assignment := TAssignmentNode(CurrentAssign);

                { Switch to the next node }
                GetNextAssignment(CurrentStatement, subscriptn);
                Inc(NodeCount);
              end;

            for X := 0 to (TRecordDef(CommonDef).size div 16) - 1 do
              if (Coverage[X] <> FullCoverage[X]) then
                { Not completely written to }
                Exit;
          end;
        else
          Exit;
      end;

      if NodeCount <= 1 then
        { Too few to vectorise (also stops degenerate behaviour below) }
        Exit;

      { Now we can start to evaluate the assignments more closely }
      for X := 0 to NodeCount - 1 do
        begin
          Y := StatementNodes[X].Index;
          if IndexSorted[Y] <> -1 then { We have the same index twice }
            Exit;

          IndexSorted[Y] := X;
          { Initial InitialAnalysis node has already been checked }
          InitialAnalysis[Y] := StatementNodes[X].Assignment.right;
        end;

      { Check that all the indices are set }
      for X := 0 to NodeCount - 1 do
        if IndexSorted[X] = -1 then
          InternalError(2023121210);

      { Begin node analysis }
      if not AnalyseNodeSet(InitialAnalysis) then
        Exit;

      { If we get here, the nodes can be converted, so let's get to it! }
      VectorizeNodeTree(StatementNodes[0].Statement.Left, StatementNodes[0].Statement, False);

      { Delete all of the other statements }
      CurrentNode := StatementNodes[NodeCount - 1].Statement.PruneKeepRight();
      StatementNodes[1].Statement.Free; { Will delete everything up to the statement at StatementNodes[NodeCount - 1] }

      CurrentDestNode := left;
      left := nil;
      right := nil;
      Result := Self.getcopy();

      TStatementNode(Result).left := CurrentDestNode;
      TStatementNode(Result).right := CurrentNode; { This is the statement after the last one that was freed }
    end;

  function tx86statementnode.simplify(forinline : boolean) : tnode;
    begin
      Result := inherited simplify(forinline);
      if Assigned(Result) then
        Exit;

      if (cs_support_vectors in current_settings.globalswitches) and
        (CPUX86_HAS_SSEUNIT in cpu_capabilities[current_settings.cputype]) then
        begin
          case left.nodetype of
            assignn:
              Result := vectorize_assign;

            else
              ;
          end;
        end;
    end;

initialization
  cstatementnode := tx86statementnode;
  casmnode := Tx86AsmNode;

end.
