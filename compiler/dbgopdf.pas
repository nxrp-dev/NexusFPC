{
    Copyright (c) 2025 by Graeme Geldenhuys

    This unit contains OPDF debug format support for the FPC compiler.
    OPDF (Object Pascal Debug Format) is an alternative to DWARF and STABS.

    Debug data is emitted into an asm list (al_opdf) which produces an
    .opdf ELF section in the final binary. This follows the same pattern
    used by DWARF (dbgdwarf.pas) for label-based address resolution.

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
unit dbgopdf;

{$i fpcdefs.inc}

interface

    uses
      cclasses,
      aasmbase,aasmtai,aasmdata,
      systems,
      symbase,symconst,symtype,symdef,symsym,symtable,
      finput,
      fmodule,
      globtype,
      cgbase,
      defutil,
      DbgBase,
      widestr,
      dbgopdf_typemap;

    type
      { OPDF debug format writer - emits debug data into asm list }
      TOPDFDebugWriter=class(TDebugInfo)
      private
        { accumulated line info records from insertlineinfo calls.
          these are collected per-procedure and merged into al_opdf
          during inserttypeinfo, after the section header is emitted. }
        FLineInfoList    : TAsmList;
        { FByteCounter at start of current unit }
        FUnitStartBytes  : QWord;

        { emit helpers - write raw bytes into asm list }
        procedure EmitByte(list:TAsmList;value:Byte);
        procedure EmitWord(list:TAsmList;value:Word);
        procedure EmitDWord(list:TAsmList;value:Cardinal);
        procedure EmitQWord(list:TAsmList;value:QWord);
        procedure EmitString(list:TAsmList;const s:AnsiString);
        procedure EmitRecordHeader(list:TAsmList;rectype:Byte;recsize:Cardinal);
        procedure EmitSymRef(list:TAsmList;symref:tai);
        procedure EmitOPDFHeader(list:TAsmList);
        { type dedup: returns true if this def's type was already emitted }
        function TypeAlreadyEmitted(def:tdef):Boolean;
      protected
        { override TDebugInfo virtual methods for type definitions }
        procedure appenddef_ord(list:TAsmList;def:torddef);override;
        procedure appenddef_float(list:TAsmList;def:tfloatdef);override;
        procedure appenddef_enum(list:TAsmList;def:tenumdef);override;
        procedure appenddef_array(list:TAsmList;def:tarraydef);override;
        procedure appenddef_record(list:TAsmList;def:trecorddef);override;
        procedure appenddef_object(list:TAsmList;def:tobjectdef);override;
        procedure appenddef_pointer(list:TAsmList;def:tpointerdef);override;
        procedure appenddef_string(list:TAsmList;def:tstringdef);override;
        procedure appenddef_procvar(list:TAsmList;def:tprocvardef);override;
        procedure appenddef_variant(list:TAsmList;def:tvariantdef);override;
        procedure appenddef_set(list:TAsmList;def:tsetdef);override;
        procedure appenddef_file(list:TAsmList;def:tfiledef);override;
        procedure appenddef_formal(list:TAsmList;def:tformaldef);override;
        procedure appenddef_undefined(list:TAsmList;def:tundefineddef);override;

        { override TDebugInfo virtual methods for symbols }
        procedure appendsym_staticvar(list:TAsmList;sym:tstaticvarsym);override;
        procedure appendsym_paravar(list:TAsmList;sym:tparavarsym);override;
        procedure appendsym_localvar(list:TAsmList;sym:tlocalvarsym);override;
        procedure appendsym_fieldvar(list:TAsmList;sym:tfieldvarsym);override;
        procedure appendsym_const(list:TAsmList;sym:tconstsym);override;
        procedure appendsym_type(list:TAsmList;sym:ttypesym);override;
        procedure appendsym_label(list:TAsmList;sym:tlabelsym);override;
        procedure appendsym_absolute(list:TAsmList;sym:tabsolutevarsym);override;
        procedure appendsym_property(list:TAsmList;sym:tpropertysym);override;

        { override proc definition handler for function scope records }
        procedure appendprocdef(list:TAsmList;def:tprocdef);override;
      public
        constructor Create;override;
        destructor Destroy;override;

        { main OPDF entry points }
        procedure inserttypeinfo;override;
        procedure insertmoduleinfo;override;
        procedure insertlineinfo(list:TAsmList);override;
      end;

    { OPDF debug format info record }
    const
      dbg_opdf_info : tdbginfo =
        (
          id     : dbg_opdf;
          idtxt  : 'OPDF'
        );

implementation

var
  G_TypeMapper     : TTypeMapper;
  G_EmittedTypeIDs : TFPHashList;
  G_ByteCounter    : QWord;
  G_UnitSizes      : TFPList;
  G_UnitNames      : TFPList;
  i                : longint;

    { OPDF format constants - must match opdf_types.pas (opdf-lib) definitions }
    const
      OPDF_MAGIC_0 = Ord('O');
      OPDF_MAGIC_1 = Ord('P');
      OPDF_MAGIC_2 = Ord('D');
      OPDF_MAGIC_3 = Ord('F');
      OPDF_VERSION = 1;

      { header flags }
      OPDF_FLAG_HAS_DIRECTORY = 1;

      { record types - must match TOPDFRecordType in opdf_types.pas (opdf-lib) }
      REC_PRIMITIVE  = 1;
      REC_GLOBALVAR  = 2;
      REC_SHORTSTR   = 3;
      REC_ANSISTR    = 4;
      REC_UNICODESTR = 5;
      REC_POINTER    = 6;
      REC_ARRAY      = 7;
      REC_RECORD     = 8;
      REC_CLASS      = 9;
      REC_PROPERTY   = 10;
      REC_LOCALVAR   = 12;
      REC_PARAMETER  = 13;
      REC_LINEINFO   = 14;
      REC_FUNCSCOPE  = 15;
      REC_INTERFACE  = 16;
      REC_ENUM       = 17;
      REC_SET        = 18;
      REC_UNITDIR    = 19;
      REC_CONSTANT   = 20;  { must match recConstant in opdf_types.pas }

      { constant kind — must match TConstantKind in opdf_types.pas }
      CKIND_ORD      = 0;
      CKIND_STRING   = 1;
      CKIND_REAL     = 2;
      CKIND_NIL      = 3;
      CKIND_WIDESTR  = 4;


{*****************************************************************************
                               Emit helpers
*****************************************************************************}

    procedure TOPDFDebugWriter.EmitByte(list:TAsmList;value:Byte);
      begin
        list.concat(tai_const.Create_8bit(value));
        inc(G_ByteCounter,1);
      end;


    procedure TOPDFDebugWriter.EmitWord(list:TAsmList;value:Word);
      begin
        list.concat(tai_const.Create_16bit_unaligned(value));
        inc(G_ByteCounter,2);
      end;


    procedure TOPDFDebugWriter.EmitDWord(list:TAsmList;value:Cardinal);
      begin
        list.concat(tai_const.Create_32bit_unaligned(longint(value)));
        inc(G_ByteCounter,4);
      end;


    procedure TOPDFDebugWriter.EmitQWord(list:TAsmList;value:QWord);
      begin
        { emit as two 32-bit values in little-endian order }
        list.concat(tai_const.Create_32bit_unaligned(longint(value and $FFFFFFFF)));
        list.concat(tai_const.Create_32bit_unaligned(longint(value shr 32)));
        inc(G_ByteCounter,8);
      end;


    procedure TOPDFDebugWriter.EmitString(list:TAsmList;const s:AnsiString);
      var
        i : longint;
      begin
        for i:=1 to Length(s) do
          list.concat(tai_const.Create_8bit(Ord(s[i])));
        inc(G_ByteCounter,QWord(Length(s)));
      end;


    procedure TOPDFDebugWriter.EmitRecordHeader(list:TAsmList;rectype:Byte;recsize:Cardinal);
      begin
        EmitByte(list,rectype);
        EmitDWord(list,recsize);
      end;


    procedure TOPDFDebugWriter.EmitSymRef(list:TAsmList;symref:tai);
      begin
        list.concat(symref);
        { symbol references are pointer-sized on this target }
        if tai_const(symref).consttype=aitconst_32bit_unaligned then
          inc(G_ByteCounter,4)
        else
          inc(G_ByteCounter,sizeof(pint));
      end;


    function TOPDFDebugWriter.TypeAlreadyEmitted(def:tdef):Boolean;
      var
        typeid : Cardinal;
        key    : shortstring;
      begin
        typeid:=G_TypeMapper.GetTypeID(def);
        Str(typeid,key);
        if G_EmittedTypeIDs.Find(key)<>nil then
          result:=true
        else
          begin
            G_EmittedTypeIDs.Add(key,Pointer(PtrInt(typeid)));
            result:=false;
          end;
      end;


    procedure TOPDFDebugWriter.EmitOPDFHeader(list:TAsmList);
      var
        archbyte : Byte;
        ptrsize  : Byte;
        i        : longint;
      begin
        { magic: 'OPDF' (4 bytes) }
        EmitByte(list,OPDF_MAGIC_0);
        EmitByte(list,OPDF_MAGIC_1);
        EmitByte(list,OPDF_MAGIC_2);
        EmitByte(list,OPDF_MAGIC_3);

        { version (2 bytes) }
        EmitWord(list,OPDF_VERSION);

        { BuildID: 16 zero bytes (not needed for embedded sections) }
        for i:=1 to 16 do
          EmitByte(list,0);

        { target architecture (1 byte) }
{$if defined(cpu64bitaddr)}
        archbyte:=2; { archX86_64 }
        ptrsize:=8;
{$elseif defined(cpu32bitaddr)}
        archbyte:=1; { archI386 }
        ptrsize:=4;
{$else}
        archbyte:=0; { archUnknown }
        ptrsize:=4;
{$endif}
        EmitByte(list,archbyte);

        { pointer size (1 byte) }
        EmitByte(list,ptrsize);

        { TotalRecords: 0 = stream-terminated mode (4 bytes) }
        EmitDWord(list,0);

        { Flags: has directory (4 bytes) }
        EmitDWord(list,OPDF_FLAG_HAS_DIRECTORY);
      end;


{*****************************************************************************
                            Constructor / Destructor
*****************************************************************************}

    constructor TOPDFDebugWriter.Create;
      begin
        inherited Create;
        FLineInfoList:=TAsmList.Create;
        FUnitStartBytes:=0;
      end;


    destructor TOPDFDebugWriter.Destroy;
      begin
        FLineInfoList.Free;
        inherited Destroy;
      end;


{*****************************************************************************
                           Type definition handlers
*****************************************************************************}

    procedure TOPDFDebugWriter.appenddef_ord(list:TAsmList;def:torddef);
      var
        opdflist : TAsmList;
        typeid   : Cardinal;
        typename : AnsiString;
        issigned : Byte;
        namelen  : Word;
        recsize  : Cardinal;
        sz       : Integer;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        { get or allocate TypeID }
        typeid:=G_TypeMapper.GetTypeID(def);

        { determine type name }
        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        { get size in bytes }
        sz:=def.size;
        if sz<1 then
          sz:=1;

        { determine signedness }
        issigned:=0;
        case def.ordtype of
          s8bit,s16bit,s32bit,s64bit,s128bit:
            issigned:=1;
          else
            issigned:=0;
        end;

        { record payload: TypeID(4) + SizeInBytes(1) + IsSigned(1) + NameLen(2) + Name }
        recsize:=4+1+1+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_PRIMITIVE,recsize);
        EmitDWord(opdflist,typeid);
        EmitByte(opdflist,Byte(sz));
        EmitByte(opdflist,issigned);
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);
      end;


    procedure TOPDFDebugWriter.appenddef_float(list:TAsmList;def:tfloatdef);
      var
        opdflist : TAsmList;
        typeid   : Cardinal;
        typename : AnsiString;
        namelen  : Word;
        recsize  : Cardinal;
        sz       : Integer;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        sz:=def.size;
        if sz<1 then
          sz:=1;

        { all float types are signed }
        recsize:=4+1+1+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_PRIMITIVE,recsize);
        EmitDWord(opdflist,typeid);
        EmitByte(opdflist,Byte(sz));
        EmitByte(opdflist,1); { IsSigned = 1 for all floats }
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);
      end;


    procedure TOPDFDebugWriter.appenddef_enum(list:TAsmList;def:tenumdef);
      var
        opdflist      : TAsmList;
        typeid        : Cardinal;
        typename      : AnsiString;
        namelen       : Word;
        recsize       : Cardinal;
        membercount   : Cardinal;
        hp            : tenumsym;
        membername    : AnsiString;
        membernamelen : Word;
        i             : Longint;
      begin
        if not assigned(def) then
          exit;
        if not assigned(def.symtable) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        { count members in range }
        membercount:=0;
        for i:=0 to def.symtable.SymList.Count-1 do
          begin
            hp:=tenumsym(def.symtable.SymList[i]);
            if (hp.value>=def.minval) and (hp.value<=def.maxval) then
              inc(membercount);
          end;

        { calculate record size: TypeID(4) + SizeInBytes(1) + MemberCount(4) + NameLen(2) + Name }
        recsize:=4+1+4+2+Cardinal(namelen);
        { add member sizes: Value(8) + MemberNameLen(2) + MemberName per member }
        for i:=0 to def.symtable.SymList.Count-1 do
          begin
            hp:=tenumsym(def.symtable.SymList[i]);
            if (hp.value>=def.minval) and (hp.value<=def.maxval) then
              recsize:=recsize+8+2+Cardinal(Length(hp.RealName));
          end;

        EmitRecordHeader(opdflist,REC_ENUM,recsize);
        EmitDWord(opdflist,typeid);
        EmitByte(opdflist,Byte(def.size));
        EmitDWord(opdflist,membercount);
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);

        { emit enum members }
        for i:=0 to def.symtable.SymList.Count-1 do
          begin
            hp:=tenumsym(def.symtable.SymList[i]);
            if (hp.value>=def.minval) and (hp.value<=def.maxval) then
              begin
                EmitQWord(opdflist,QWord(hp.value));
                membername:=hp.RealName;
                membernamelen:=Word(Length(membername));
                EmitWord(opdflist,membernamelen);
                EmitString(opdflist,membername);
              end;
          end;
      end;


    procedure TOPDFDebugWriter.appenddef_array(list:TAsmList;def:tarraydef);
      var
        opdflist   : TAsmList;
        typeid     : Cardinal;
        elemtypeid : Cardinal;
        typename   : AnsiString;
        namelen    : Word;
        recsize    : Cardinal;
        isdyn      : Boolean;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        { get element type ID }
        if assigned(def.elementdef) then
          elemtypeid:=G_TypeMapper.GetTypeID(def.elementdef)
        else
          elemtypeid:=0;

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        isdyn:=is_dynamic_array(def);

        { REC_ARRAY: TypeID(4) + ElementTypeID(4) + Dimensions(1) + IsDynamic(1) + NameLen(2) + Name }
        { for static arrays, add bounds: LowerBound(8) + UpperBound(8) per dimension }
        recsize:=4+4+1+1+2+Cardinal(namelen);
        if not isdyn then
          recsize:=recsize+16; { one dimension: LowerBound(8) + UpperBound(8) }

        EmitRecordHeader(opdflist,REC_ARRAY,recsize);
        EmitDWord(opdflist,typeid);
        EmitDWord(opdflist,elemtypeid);
        EmitByte(opdflist,1); { Dimensions: always 1 for Pascal arrays }
        if isdyn then
          EmitByte(opdflist,1)
        else
          EmitByte(opdflist,0);
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);

        { write bounds for static arrays }
        if not isdyn then
          begin
            EmitQWord(opdflist,QWord(def.lowrange));
            EmitQWord(opdflist,QWord(def.highrange));
          end;
      end;


    procedure TOPDFDebugWriter.appenddef_record(list:TAsmList;def:trecorddef);
      var
        opdflist     : TAsmList;
        typeid       : Cardinal;
        typename     : AnsiString;
        namelen      : Word;
        recsize      : Cardinal;
        fieldcount   : Cardinal;
        fieldtypeid  : Cardinal;
        fieldname    : AnsiString;
        fieldnamelen : Word;
        i            : Longint;
        sym          : tsym;
        fvsym        : tfieldvarsym;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        { get record name }
        if assigned(def.objrealname) then
          typename:=def.objrealname^
        else
          typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        { count non-static fields }
        fieldcount:=0;
        if assigned(def.symtable) then
          for i:=0 to def.symtable.SymList.Count-1 do
            begin
              sym:=tsym(def.symtable.SymList[i]);
              if (sym.typ=fieldvarsym) and
                 not (sp_static in sym.symoptions) then
                inc(fieldcount);
            end;

        { calculate record size }
        { header: TypeID(4) + FieldCount(4) + TotalSize(4) + NameLen(2) + Name }
        recsize:=4+4+4+2+Cardinal(namelen);
        { fields: FieldTypeID(4) + Offset(4) + FieldNameLen(2) + FieldName per field }
        if assigned(def.symtable) then
          for i:=0 to def.symtable.SymList.Count-1 do
            begin
              sym:=tsym(def.symtable.SymList[i]);
              if (sym.typ=fieldvarsym) and
                 not (sp_static in sym.symoptions) then
                recsize:=recsize+4+4+2+Cardinal(Length(sym.RealName));
            end;

        EmitRecordHeader(opdflist,REC_RECORD,recsize);
        EmitDWord(opdflist,typeid);
        EmitDWord(opdflist,fieldcount);
        EmitDWord(opdflist,Cardinal(def.size));
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);

        { emit field descriptors }
        if assigned(def.symtable) then
          for i:=0 to def.symtable.SymList.Count-1 do
            begin
              sym:=tsym(def.symtable.SymList[i]);
              if (sym.typ=fieldvarsym) and
                 not (sp_static in sym.symoptions) then
                begin
                  fvsym:=tfieldvarsym(sym);

                  if assigned(fvsym.vardef) then
                    fieldtypeid:=G_TypeMapper.GetTypeID(fvsym.vardef)
                  else
                    fieldtypeid:=0;

                  fieldname:=fvsym.RealName;
                  fieldnamelen:=Word(Length(fieldname));

                  EmitDWord(opdflist,fieldtypeid);
                  EmitDWord(opdflist,Cardinal(fvsym.fieldoffset));
                  EmitWord(opdflist,fieldnamelen);
                  EmitString(opdflist,fieldname);
                end;
            end;
      end;


    procedure TOPDFDebugWriter.appenddef_object(list:TAsmList;def:tobjectdef);
      var
        opdflist     : TAsmList;
        typeid       : Cardinal;
        parenttypeid : Cardinal;
        typename     : AnsiString;
        namelen      : Word;
        recsize      : Cardinal;
        fieldcount   : Cardinal;
        fieldtypeid  : Cardinal;
        fieldname    : AnsiString;
        fieldnamelen : Word;
        i            : Longint;
        sym          : tsym;
        fvsym        : tfieldvarsym;
        intftypebyte : Byte;
        methodcount  : Cardinal;
        psym         : tprocsym;
        pdef         : tprocdef;
        mtdname      : AnsiString;
        mtdnamelen   : Word;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        { get parent type ID }
        if assigned(def.childof) then
          parenttypeid:=G_TypeMapper.GetTypeID(def.childof)
        else
          parenttypeid:=0;

        { get type name }
        if assigned(def.objrealname) then
          typename:=def.objrealname^
        else
          typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        case def.objecttype of
          odt_interfacecom,odt_interfacecorba,odt_dispinterface:
            begin
              { emit REC_INTERFACE }

              { determine interface type }
              case def.objecttype of
                odt_interfacecom:   intftypebyte:=0; { COM }
                odt_interfacecorba: intftypebyte:=1; { CORBA }
                odt_dispinterface:  intftypebyte:=2; { Dispatch }
                else                intftypebyte:=0;
              end;

              { count methods (procsym entries) }
              methodcount:=0;
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if sym.typ=procsym then
                      inc(methodcount);
                  end;

              { calculate record size }
              { TypeID(4) + ParentTypeID(4) + IntfType(1) + GUID(16) + MethodCount(4) + NameLen(2) + Name }
              recsize:=4+4+1+16+4+2+Cardinal(namelen);
              { methods: ReturnTypeID(4) + ParamCount(1) + MtdNameLen(2) + MtdName per method }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if sym.typ=procsym then
                      recsize:=recsize+4+1+2+Cardinal(Length(sym.RealName));
                  end;

              EmitRecordHeader(opdflist,REC_INTERFACE,recsize);
              EmitDWord(opdflist,typeid);
              EmitDWord(opdflist,parenttypeid);
              EmitByte(opdflist,intftypebyte);

              { emit GUID - 16 bytes }
              if assigned(def.iidguid) then
                begin
                  EmitDWord(opdflist,def.iidguid^.D1);
                  EmitWord(opdflist,def.iidguid^.D2);
                  EmitWord(opdflist,def.iidguid^.D3);
                  for i:=0 to 7 do
                    EmitByte(opdflist,def.iidguid^.D4[i]);
                end
              else
                begin
                  { null GUID: 16 zero bytes }
                  for i:=0 to 15 do
                    EmitByte(opdflist,0);
                end;

              EmitDWord(opdflist,methodcount);
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);

              { emit method descriptors }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if sym.typ=procsym then
                      begin
                        psym:=tprocsym(sym);
                        { use the first procdef for return type and param count }
                        if psym.ProcdefList.Count>0 then
                          begin
                            pdef:=tprocdef(psym.ProcdefList[0]);
                            if assigned(pdef.returndef) and not is_void(pdef.returndef) then
                              EmitDWord(opdflist,G_TypeMapper.GetTypeID(pdef.returndef))
                            else
                              EmitDWord(opdflist,0);
                            EmitByte(opdflist,Byte(pdef.paras.Count));
                          end
                        else
                          begin
                            EmitDWord(opdflist,0);
                            EmitByte(opdflist,0);
                          end;

                        mtdname:=sym.RealName;
                        mtdnamelen:=Word(Length(mtdname));
                        EmitWord(opdflist,mtdnamelen);
                        EmitString(opdflist,mtdname);
                      end;
                  end;
            end;

          odt_object:
            begin
              { emit REC_RECORD for old-style 'object' types — value types
                stored inline on the stack, like records with methods }

              { count non-static fields }
              fieldcount:=0;
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      inc(fieldcount);
                  end;

              { calculate record size }
              { TypeID(4) + FieldCount(4) + TotalSize(4) + NameLen(2) + Name }
              recsize:=4+4+4+2+Cardinal(namelen);
              { fields: FieldTypeID(4) + Offset(4) + FieldNameLen(2) + FieldName per field }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      recsize:=recsize+4+4+2+Cardinal(Length(sym.RealName));
                  end;

              EmitRecordHeader(opdflist,REC_RECORD,recsize);
              EmitDWord(opdflist,typeid);
              EmitDWord(opdflist,fieldcount);
              EmitDWord(opdflist,Cardinal(tobjectsymtable(def.symtable).datasize));
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);

              { emit field descriptors }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      begin
                        fvsym:=tfieldvarsym(sym);

                        if assigned(fvsym.vardef) then
                          fieldtypeid:=G_TypeMapper.GetTypeID(fvsym.vardef)
                        else
                          fieldtypeid:=0;

                        fieldname:=fvsym.RealName;
                        fieldnamelen:=Word(Length(fieldname));

                        EmitDWord(opdflist,fieldtypeid);
                        EmitDWord(opdflist,Cardinal(fvsym.fieldoffset));
                        EmitWord(opdflist,fieldnamelen);
                        EmitString(opdflist,fieldname);
                      end;
                  end;

              { emit property records for object types }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if sym.typ=propertysym then
                      appendsym_property(list,tpropertysym(sym));
                  end;
            end;

          odt_class:
            begin
              { emit REC_CLASS }

              { count non-static fields }
              fieldcount:=0;
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      inc(fieldcount);
                  end;

              { calculate record size }
              { TypeID(4) + ParentTypeID(4) + VMTAddress(8) + InstanceSize(4) + FieldCount(4) + NameLen(2) + Name }
              recsize:=4+4+8+4+4+2+Cardinal(namelen);
              { fields: FieldTypeID(4) + Offset(4) + FieldNameLen(2) + FieldName per field }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      recsize:=recsize+4+4+2+Cardinal(Length(sym.RealName));
                  end;

              EmitRecordHeader(opdflist,REC_CLASS,recsize);
              EmitDWord(opdflist,typeid);
              EmitDWord(opdflist,parenttypeid);
              EmitQWord(opdflist,0); { VMTAddress: 0 placeholder }
              EmitDWord(opdflist,Cardinal(def.size));
              EmitDWord(opdflist,fieldcount);
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);

              { emit field descriptors }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if (sym.typ=fieldvarsym) and
                       not (sp_static in sym.symoptions) then
                      begin
                        fvsym:=tfieldvarsym(sym);

                        if assigned(fvsym.vardef) then
                          fieldtypeid:=G_TypeMapper.GetTypeID(fvsym.vardef)
                        else
                          fieldtypeid:=0;

                        fieldname:=fvsym.RealName;
                        fieldnamelen:=Word(Length(fieldname));

                        EmitDWord(opdflist,fieldtypeid);
                        EmitDWord(opdflist,Cardinal(fvsym.fieldoffset));
                        EmitWord(opdflist,fieldnamelen);
                        EmitString(opdflist,fieldname);
                      end;
                  end;

              { emit property records for each property in this class.
                properties are class members and not visited by write_symtable_syms,
                so we must emit them here directly after the class record. }
              if assigned(def.symtable) then
                for i:=0 to def.symtable.SymList.Count-1 do
                  begin
                    sym:=tsym(def.symtable.SymList[i]);
                    if sym.typ=propertysym then
                      appendsym_property(list,tpropertysym(sym));
                  end;
            end;

          else
            { other object types (ObjC, Java, etc.) - just register type ID }
            ;
        end;
      end;


    procedure TOPDFDebugWriter.appenddef_pointer(list:TAsmList;def:tpointerdef);
      var
        opdflist     : TAsmList;
        typeid       : Cardinal;
        targettypeid : Cardinal;
        typename     : AnsiString;
        namelen      : Word;
        recsize      : Cardinal;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        { resolve target type - 0 for void pointers }
        if is_voidpointer(def) then
          targettypeid:=0
        else if assigned(def.pointeddef) then
          targettypeid:=G_TypeMapper.GetTypeID(def.pointeddef)
        else
          targettypeid:=0;

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        { REC_POINTER: TypeID(4) + TargetTypeID(4) + NameLen(2) + Name }
        recsize:=4+4+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_POINTER,recsize);
        EmitDWord(opdflist,typeid);
        EmitDWord(opdflist,targettypeid);
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);
      end;


    procedure TOPDFDebugWriter.appenddef_string(list:TAsmList;def:tstringdef);
      var
        opdflist : TAsmList;
        typeid   : Cardinal;
        typename : AnsiString;
        namelen  : Word;
        recsize  : Cardinal;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        case def.stringtype of
          st_shortstring:
            begin
              { REC_SHORTSTR: TypeID(4) + MaxLength(1) + NameLen(2) + Name }
              recsize:=4+1+2+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_SHORTSTR,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,Byte(def.len and $FF));
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);
            end;
          st_ansistring:
            begin
              { REC_ANSISTR: TypeID(4) + NameLen(2) + Name }
              recsize:=4+2+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_ANSISTR,recsize);
              EmitDWord(opdflist,typeid);
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);
            end;
          st_unicodestring,st_widestring:
            begin
              { REC_UNICODESTR: TypeID(4) + NameLen(2) + Name }
              recsize:=4+2+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_UNICODESTR,recsize);
              EmitDWord(opdflist,typeid);
              EmitWord(opdflist,namelen);
              EmitString(opdflist,typename);
            end;
          else
            { st_longstring or other: just register type ID }
            ;
        end;
      end;


    procedure TOPDFDebugWriter.appenddef_procvar(list:TAsmList;def:tprocvardef);
      begin
        if assigned(def) and not TypeAlreadyEmitted(def) then
          ;
      end;


    procedure TOPDFDebugWriter.appenddef_variant(list:TAsmList;def:tvariantdef);
      begin
        if assigned(def) and not TypeAlreadyEmitted(def) then
          ;
      end;


    procedure TOPDFDebugWriter.appenddef_set(list:TAsmList;def:tsetdef);
      var
        opdflist   : TAsmList;
        typeid     : Cardinal;
        basetypeid : Cardinal;
        typename   : AnsiString;
        namelen    : Word;
        recsize    : Cardinal;
        lowerbound : LongInt;
      begin
        if not assigned(def) then
          exit;
        if TypeAlreadyEmitted(def) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(def);

        { base type ID (the enum/ordinal this is a set of) }
        if assigned(def.elementdef) then
          basetypeid:=G_TypeMapper.GetTypeID(def.elementdef)
        else
          basetypeid:=0;

        { lowest valid ordinal in the set declaration }
        lowerbound:=LongInt(def.setlow);

        typename:=def.GetTypeName;
        namelen:=Word(Length(typename));

        { REC_SET: TypeID(4) + BaseTypeID(4) + SizeInBytes(1) + LowerBound(4) + NameLen(2) + Name }
        recsize:=4+4+1+4+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_SET,recsize);
        EmitDWord(opdflist,typeid);
        EmitDWord(opdflist,basetypeid);
        EmitByte(opdflist,Byte(def.size));
        EmitDWord(opdflist,Cardinal(lowerbound));
        EmitWord(opdflist,namelen);
        EmitString(opdflist,typename);
      end;


    procedure TOPDFDebugWriter.appenddef_file(list:TAsmList;def:tfiledef);
      begin
        if assigned(def) and not TypeAlreadyEmitted(def) then
          ;
      end;


    procedure TOPDFDebugWriter.appenddef_formal(list:TAsmList;def:tformaldef);
      begin
        if assigned(def) and not TypeAlreadyEmitted(def) then
          ;
      end;


    procedure TOPDFDebugWriter.appenddef_undefined(list:TAsmList;def:tundefineddef);
      begin
        if assigned(def) and not TypeAlreadyEmitted(def) then
          ;
      end;


{*****************************************************************************
                               Symbol handlers
*****************************************************************************}

    procedure TOPDFDebugWriter.appendsym_staticvar(list:TAsmList;sym:tstaticvarsym);
      var
        opdflist : TAsmList;
        typeid   : Cardinal;
        varname  : AnsiString;
        namelen  : Word;
        recsize  : Cardinal;
      begin
        if not assigned(sym) or not assigned(sym.vardef) then
          exit;

        { skip external variables }
        if vo_is_external in sym.varoptions then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        { get the variable's type ID }
        typeid:=G_TypeMapper.GetTypeID(sym.vardef);

        { use mangled name for the variable }
        varname:=sym.mangledname;
        namelen:=Word(Length(varname));

        { record payload: TypeID(4) + Address(8) + NameLen(2) + Name }
        recsize:=4+8+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_GLOBALVAR,recsize);
        EmitDWord(opdflist,typeid);

        { emit address as a symbol reference - linker resolves the actual address }
        EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_ptr_unaligned,
          current_asmdata.RefAsmSymbol(sym.mangledname,AT_DATA)));

        EmitWord(opdflist,namelen);
        EmitString(opdflist,varname);
      end;


    procedure TOPDFDebugWriter.appendsym_paravar(list:TAsmList;sym:tparavarsym);
      var
        opdflist    : TAsmList;
        typeid      : Cardinal;
        paramname   : AnsiString;
        namelen     : Word;
        recsize     : Cardinal;
        isvar       : Byte;
        isconst     : Byte;
        isout       : Byte;
        stackoffset : Longint;
        funcname    : AnsiString;
        declindex   : Word;
        j           : Longint;
      begin
        if not assigned(sym) or not assigned(sym.vardef) then
          exit;

        { skip the hidden self/vmt/result parameters }
        if vo_is_hidden_para in sym.varoptions then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(sym.vardef);

        paramname:=sym.RealName;
        namelen:=Word(Length(paramname));

        { determine var/const/out flags }
        isvar:=0;
        isconst:=0;
        isout:=0;
        case sym.varspez of
          vs_var:
            isvar:=1;
          vs_out:
            isout:=1;
          vs_const,vs_constref:
            isconst:=1;
          else
            ; { vs_value, vs_final }
        end;

        { REC_PARAMETER: TypeID(4) + IsVar(1) + IsConst(1) + IsOut(1) + NameLen(2) + Name }
        recsize:=4+1+1+1+2+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_PARAMETER,recsize);
        EmitDWord(opdflist,typeid);
        EmitByte(opdflist,isvar);
        EmitByte(opdflist,isconst);
        EmitByte(opdflist,isout);
        EmitWord(opdflist,namelen);
        EmitString(opdflist,paramname);

        { also emit a REC_LOCALVAR so that 'locals' command can find parameters }
        if sym.localloc.loc in [LOC_REFERENCE,LOC_CREFERENCE] then
          begin
            stackoffset:=sym.localloc.reference.offset;

            { clamp offset to ShortInt range }
            if stackoffset>127 then
              stackoffset:=127
            else if stackoffset<-128 then
              stackoffset:=-128;

            { find declaration index: position in parent procedure's SymList }
            declindex:=0;
            if assigned(sym.owner) then
              for j:=0 to sym.owner.SymList.Count-1 do
                if sym.owner.SymList[j]=sym then
                  begin
                    declindex:=Word(j);
                    break;
                  end;

            { REC_LOCALVAR: TypeID(4) + ScopeID(4) + LocationExpr(1) + DeclIndex(2) + NameLen(2) + LocationData(1) + Name }
            recsize:=4+4+1+2+2+1+Cardinal(namelen);

            EmitRecordHeader(opdflist,REC_LOCALVAR,recsize);
            EmitDWord(opdflist,typeid);

            { ScopeID: use the owning function's address as scope ID }
            if assigned(sym.owner) and assigned(sym.owner.defowner) and
               (sym.owner.defowner.typ=procdef) then
              begin
                funcname:=tprocdef(sym.owner.defowner).mangledname;
                EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_32bit_unaligned,
                  current_asmdata.RefAsmSymbol(funcname,AT_FUNCTION)));
              end
            else
              EmitDWord(opdflist,0);

            EmitByte(opdflist,1); { LocationExpr: 1 = RBP-relative }
            EmitWord(opdflist,declindex);
            EmitWord(opdflist,namelen);
            EmitByte(opdflist,Byte(ShortInt(stackoffset))); { LocationData }
            EmitString(opdflist,paramname);
          end;
      end;


    procedure TOPDFDebugWriter.appendsym_localvar(list:TAsmList;sym:tlocalvarsym);
      var
        opdflist    : TAsmList;
        typeid      : Cardinal;
        varname     : AnsiString;
        namelen     : Word;
        recsize     : Cardinal;
        stackoffset : Longint;
        funcname    : AnsiString;
        declindex   : Word;
        j           : Longint;
      begin
        if not assigned(sym) or not assigned(sym.vardef) then
          exit;

        { only handle reference-based locations (stack variables) }
        if not (sym.localloc.loc in [LOC_REFERENCE,LOC_CREFERENCE]) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        typeid:=G_TypeMapper.GetTypeID(sym.vardef);

        varname:=sym.RealName;
        namelen:=Word(Length(varname));

        stackoffset:=sym.localloc.reference.offset;

        { clamp offset to ShortInt range }
        if stackoffset>127 then
          stackoffset:=127
        else if stackoffset<-128 then
          stackoffset:=-128;

        { find declaration index: position in parent procedure's SymList }
        declindex:=0;
        if assigned(sym.owner) then
          for j:=0 to sym.owner.SymList.Count-1 do
            if sym.owner.SymList[j]=sym then
              begin
                declindex:=Word(j);
                break;
              end;

        { REC_LOCALVAR: TypeID(4) + ScopeID(4) + LocationExpr(1) + DeclIndex(2) + NameLen(2) + LocationData(1) + Name }
        recsize:=4+4+1+2+2+1+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_LOCALVAR,recsize);
        EmitDWord(opdflist,typeid);

        { ScopeID: use the owning function's address as scope ID }
        if assigned(sym.owner) and assigned(sym.owner.defowner) and
           (sym.owner.defowner.typ=procdef) then
          begin
            funcname:=tprocdef(sym.owner.defowner).mangledname;
            EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_32bit_unaligned,
              current_asmdata.RefAsmSymbol(funcname,AT_FUNCTION)));
          end
        else
          EmitDWord(opdflist,0);

        EmitByte(opdflist,1); { LocationExpr: 1 = RBP-relative }
        EmitWord(opdflist,declindex);
        EmitWord(opdflist,namelen);
        EmitByte(opdflist,Byte(ShortInt(stackoffset))); { LocationData }
        EmitString(opdflist,varname);
      end;


    procedure TOPDFDebugWriter.appendsym_fieldvar(list:TAsmList;sym:tfieldvarsym);
      begin
        { fields are emitted inline within record/class records.
          no separate field record is needed. }
      end;


    procedure TOPDFDebugWriter.appendsym_const(list:TAsmList;sym:tconstsym);
      var
        opdflist  : TAsmList;
        typeid    : Cardinal;
        constname : AnsiString;
        namelen   : Word;
        recsize   : Cardinal;
        valuelen  : Word;
        orddata   : array[0..7] of Byte;
        dbldata   : array[0..7] of Byte;
        i         : Longint;
        dval      : Double;
        wlen      : Longint;
        wch       : Word;
      begin
        if not assigned(sym) then
          exit;

        { skip unsupported constant kinds }
        if sym.consttyp in [constnone,constresourcestring,constwresourcestring,
                            constset,constguid,constpointer] then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];
        constname:=sym.RealName;
        namelen:=Word(Length(constname));

        { get the constant's type ID }
        if assigned(sym.constdef) then
          typeid:=G_TypeMapper.GetTypeID(sym.constdef)
        else
          typeid:=0;

        { payload fixed part: TypeID(4) + ConstKind(1) + ValueLen(2) + NameLen(2) = 9 }
        case sym.consttyp of
          constord:
            begin
              valuelen:=8;
              PInt64(@orddata)^:=sym.value.valueord.svalue;
              recsize:=9+valuelen+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_CONSTANT,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,CKIND_ORD);
              EmitWord(opdflist,valuelen);
              EmitWord(opdflist,namelen);
              for i:=0 to 7 do
                EmitByte(opdflist,orddata[i]);
              EmitString(opdflist,constname);
            end;

          conststring:
            begin
              valuelen:=Word(sym.value.len);
              recsize:=9+valuelen+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_CONSTANT,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,CKIND_STRING);
              EmitWord(opdflist,valuelen);
              EmitWord(opdflist,namelen);
              for i:=0 to sym.value.len-1 do
                EmitByte(opdflist,pbyte(sym.value.valueptr+i)^);
              EmitString(opdflist,constname);
            end;

          constreal:
            begin
              valuelen:=8;
              dval:=Double(PExtended(sym.value.valueptr)^);
              PDouble(@dbldata)^:=dval;
              recsize:=9+valuelen+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_CONSTANT,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,CKIND_REAL);
              EmitWord(opdflist,valuelen);
              EmitWord(opdflist,namelen);
              for i:=0 to 7 do
                EmitByte(opdflist,dbldata[i]);
              EmitString(opdflist,constname);
            end;

          constnil:
            begin
              valuelen:=0;
              recsize:=9+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_CONSTANT,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,CKIND_NIL);
              EmitWord(opdflist,0);
              EmitWord(opdflist,namelen);
              EmitString(opdflist,constname);
            end;

          constwstring:
            begin
              wlen:=getlengthwidestring(sym.value.valuews);
              valuelen:=Word(wlen*2);
              recsize:=9+valuelen+Cardinal(namelen);
              EmitRecordHeader(opdflist,REC_CONSTANT,recsize);
              EmitDWord(opdflist,typeid);
              EmitByte(opdflist,CKIND_WIDESTR);
              EmitWord(opdflist,valuelen);
              EmitWord(opdflist,namelen);
              for i:=0 to wlen-1 do
                begin
                  wch:=getcharwidestring(sym.value.valuews,i);
                  EmitByte(opdflist,wch and $FF);
                  EmitByte(opdflist,(wch shr 8) and $FF);
                end;
              EmitString(opdflist,constname);
            end;
          else
            ; { remaining kinds (constset, constguid, etc.) not yet supported }
        end;
      end;


    procedure TOPDFDebugWriter.appendsym_type(list:TAsmList;sym:ttypesym);
      begin
        { TODO: implement type symbol mapping }
      end;


    procedure TOPDFDebugWriter.appendsym_label(list:TAsmList;sym:tlabelsym);
      begin
        { TODO: implement label symbol mapping }
      end;


    procedure TOPDFDebugWriter.appendsym_absolute(list:TAsmList;sym:tabsolutevarsym);
      begin
        { TODO: implement absolute variable mapping }
      end;


    procedure TOPDFDebugWriter.appendsym_property(list:TAsmList;sym:tpropertysym);
      var
        opdflist        : TAsmList;
        classtypeid     : Cardinal;
        proptypeid      : Cardinal;
        propname        : AnsiString;
        readmethodname  : AnsiString;
        writemethodname : AnsiString;
        namelen         : Word;
        readmnamelen    : Word;
        writemnamelen   : Word;
        recsize         : Cardinal;
        readtype        : Byte;
        writetype       : Byte;
        readaddr        : QWord;
        writeaddr       : QWord;
        plist           : tpropaccesslist;
        pitem           : ppropaccesslistitem;
        fvsym           : tfieldvarsym;
      begin
        if not assigned(sym) then
          exit;
        if not assigned(sym.owner) or not assigned(sym.owner.defowner) then
          exit;
        { only emit for class/object symtables }
        if not (sym.owner.symtabletype in [objectsymtable,recordsymtable]) then
          exit;

        opdflist:=current_asmdata.asmlists[al_opdf];

        { get owning class TypeID }
        classtypeid:=G_TypeMapper.GetTypeID(tdef(sym.owner.defowner));

        { get property return type ID }
        if assigned(sym.propdef) then
          proptypeid:=G_TypeMapper.GetTypeID(sym.propdef)
        else
          proptypeid:=0;

        { determine read accessor kind }
        readtype:=2; { patNone }
        readaddr:=0;
        readmethodname:='';
        if sym.getpropaccesslist(palt_read,plist) and assigned(plist) then
          begin
            if not assigned(plist.procdef) then
              begin
                { field-backed read: firstsym is sl_load on a fieldvarsym }
                pitem:=plist.firstsym;
                if assigned(pitem) and (pitem^.sltype=sl_load) and
                   (pitem^.sym.typ=fieldvarsym) then
                  begin
                    fvsym:=tfieldvarsym(pitem^.sym);
                    readtype:=0; { patField }
                    readaddr:=QWord(fvsym.fieldoffset);
                  end;
              end
            else
              begin
                readtype:=1; { patMethod }
                readmethodname:=tprocdef(plist.procdef).procsym.RealName;
              end;
          end;

        { determine write accessor kind }
        writetype:=2; { patNone }
        writeaddr:=0;
        writemethodname:='';
        if sym.getpropaccesslist(palt_write,plist) and assigned(plist) then
          begin
            if not assigned(plist.procdef) then
              begin
                pitem:=plist.firstsym;
                if assigned(pitem) and (pitem^.sltype=sl_load) and
                   (pitem^.sym.typ=fieldvarsym) then
                  begin
                    fvsym:=tfieldvarsym(pitem^.sym);
                    writetype:=0; { patField }
                    writeaddr:=QWord(fvsym.fieldoffset);
                  end;
              end
            else
              begin
                writetype:=1; { patMethod }
                writemethodname:=tprocdef(plist.procdef).procsym.RealName;
              end;
          end;

        propname:=sym.RealName;
        namelen:=Word(Length(propname));
        readmnamelen:=Word(Length(readmethodname));
        writemnamelen:=Word(Length(writemethodname));
        { ClassTypeID(4) + PropTypeID(4) + ReadType(1) + WriteType(1) +
          ReadAddr(8) + WriteAddr(8) + ReadMethodNameLen(2) +
          WriteMethodNameLen(2) + NameLen(2) +
          ReadMethodName + WriteMethodName + Name }
        recsize:=4+4+1+1+8+8+2+2+2+Cardinal(readmnamelen)+Cardinal(writemnamelen)+Cardinal(namelen);

        EmitRecordHeader(opdflist,REC_PROPERTY,recsize);
        EmitDWord(opdflist,classtypeid);
        EmitDWord(opdflist,proptypeid);
        EmitByte(opdflist,readtype);
        EmitByte(opdflist,writetype);
        EmitQWord(opdflist,readaddr);
        EmitQWord(opdflist,writeaddr);
        EmitWord(opdflist,readmnamelen);
        EmitWord(opdflist,writemnamelen);
        EmitWord(opdflist,namelen);
        if readmnamelen>0 then
          EmitString(opdflist,readmethodname);
        if writemnamelen>0 then
          EmitString(opdflist,writemethodname);
        EmitString(opdflist,propname);
      end;


    procedure TOPDFDebugWriter.appendprocdef(list:TAsmList;def:tprocdef);
      var
        opdflist        : TAsmList;
        procendlabel    : TAsmLabel;
        funcname        : AnsiString; { mangled name - used for linker symbol references }
        funcdisplayname : AnsiString; { Pascal name - stored in OPDF record for display }
        namelen         : Word;
        recsize         : Cardinal;
        in_currentunit  : Boolean;
        declindex       : Word;
        j               : Longint;
      begin
        if not assigned(def) then
          exit;

        in_currentunit:=def.in_currentunit;

        { only write debug info for procedures defined in the current module,
          except for methods }
        if not in_currentunit and
           not (def.owner.symtabletype in [objectsymtable,recordsymtable]) then
          exit;

        { skip units without init section }
        if in_currentunit and not assigned(def.procstarttai) then
          exit;

        { skip generics }
        if df_generic in def.defoptions then
          exit;

        { check if already written }
        if (def.dbg_state in [dbg_state_writing,dbg_state_written]) then
          exit;
        defnumberlist.Add(def);

        { note: DWARF gates method emission on the parent objectdef being in
          dbg_state_writing, because DWARF nests methods inside class DIEs.
          OPDF uses flat records, so we emit function scopes and locals for
          all procedures regardless of parent class dedup state. }

        def.dbg_state:=dbg_state_writing;

        opdflist:=current_asmdata.asmlists[al_opdf];

        funcname:=def.mangledname;

        { use the original Pascal name for display; fall back to mangled name }
        if assigned(def.procsym) then
          funcdisplayname:=def.procsym.RealName
        else
          funcdisplayname:=funcname;

        namelen:=Word(Length(funcdisplayname));

        { find declaration index: procsym's position in parent scope's SymList.
          for nested procedures, the procsym is in the enclosing procedure's
          localsymtable. for top-level procedures, declindex=0 (not meaningful). }
        declindex:=0;
        if assigned(def.procsym) and assigned(def.procsym.owner) then
          for j:=0 to def.procsym.owner.SymList.Count-1 do
            if def.procsym.owner.SymList[j]=def.procsym then
              begin
                declindex:=Word(j);
                break;
              end;

        if in_currentunit then
          begin
            { create a label for the end of the procedure }
            current_asmdata.getlabel(procendlabel,alt_dbgtype);
            current_asmdata.asmlists[al_procedures].insertbefore(
              tai_label.create(procendlabel),def.procendtai);

            { REC_FUNCSCOPE: ScopeID(4) + LowPC(8) + HighPC(8) + DeclIndex(2) + NameLen(2) + Name }
            recsize:=4+8+8+2+2+Cardinal(namelen);

            EmitRecordHeader(opdflist,REC_FUNCSCOPE,recsize);

            { ScopeID: linker symbol reference to function start (uses mangled name) }
            EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_32bit_unaligned,
              current_asmdata.RefAsmSymbol(funcname,AT_FUNCTION)));

            { LowPC - function start address (uses mangled name for linker) }
            EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_ptr_unaligned,
              current_asmdata.RefAsmSymbol(funcname,AT_FUNCTION)));

            { HighPC - function end address }
            EmitSymRef(opdflist,tai_const.Create_type_sym(aitconst_ptr_unaligned,
              procendlabel));

            { DeclIndex: declaration order in parent scope }
            EmitWord(opdflist,declindex);

            { Name: emit the Pascal (display) name, not the mangled linker name }
            EmitWord(opdflist,namelen);
            EmitString(opdflist,funcdisplayname);
          end;

        { write parameter symbols }
        if assigned(def.paras) then
          write_symtable_parasyms(opdflist,def.paras);

        { write local variable symbols }
        if in_currentunit and
           assigned(def.localst) and
           (def.localst.symtabletype=localsymtable) then
          write_symtable_syms(opdflist,def.localst);

        { write local type definitions }
        if assigned(def.parast) then
          write_symtable_defs(opdflist,def.parast);
        if in_currentunit and
           assigned(def.localst) and
           (def.localst.symtabletype=localsymtable) then
          write_symtable_defs(opdflist,def.localst);

        def.dbg_state:=dbg_state_written;
      end;


{*****************************************************************************
                               Main entry points
*****************************************************************************}

    procedure TOPDFDebugWriter.inserttypeinfo;

      { mark all non-procdef definitions in a symbol table as used so
        write_symtable_defs will process them. the base class only processes
        defs in dbg_state_used state; DWARF does this in get_def_dwarf_labs.
        for OPDF we simply mark all defs upfront. procdefs are excluded
        because they are handled separately by write_symtable_procdefs. }
      procedure mark_defs_used(st:TSymtable);
        var
          j : longint;
          d : tdef;
        begin
          if not assigned(st) then
            exit;
          for j:=0 to st.DefList.Count-1 do
            begin
              d:=tdef(st.DefList[j]);
              if (d.dbg_state=dbg_state_unused) and (d.typ<>procdef) then
                begin
                  d.dbg_state:=dbg_state_used;
                  deftowritelist.Add(d);
                  defnumberlist.Add(d);
                end;
            end;
        end;

      { recursively mark defs in used units as used }
      procedure mark_used_unit_defs(hp:tmodule);
        var
          pu : tused_unit;
        begin
          pu:=tused_unit(hp.used_units.first);
          while assigned(pu) do
            begin
              if assigned(pu.u.globalsymtable) then
                mark_defs_used(pu.u.globalsymtable);
              pu:=tused_unit(pu.next);
            end;
        end;

      procedure emit_unit_directory(opdflist:TAsmList);
        var
          dirsize : Cardinal;
          i       : longint;
          uname   : AnsiString;
        begin
          { calculate directory record payload size:
            UnitCount(2) + per-unit: DataSize(4) + NameLen(2) + Name }
          dirsize:=2;
          for i:=0 to G_UnitSizes.Count-1 do
            begin
              uname:=PShortString(G_UnitNames[i])^;
              dirsize:=dirsize+4+2+Cardinal(Length(uname));
            end;
          EmitRecordHeader(opdflist,REC_UNITDIR,dirsize);
          EmitWord(opdflist,Word(G_UnitSizes.Count));
          for i:=0 to G_UnitSizes.Count-1 do
            begin
              EmitDWord(opdflist,Cardinal(PtrUInt(G_UnitSizes[i])));
              uname:=PShortString(G_UnitNames[i])^;
              EmitWord(opdflist,Word(Length(uname)));
              EmitString(opdflist,uname);
            end;
        end;

      var
        opdflist : TAsmList;
        i        : longint;
        def      : tdef;
        modname  : AnsiString;
        ps       : PShortString;
      begin
        { get the OPDF asm list }
        opdflist:=current_asmdata.asmlists[al_opdf];

        { create the .opdf section and emit header for this module }
        new_section(opdflist,sec_user,'.opdf',0);
        EmitOPDFHeader(opdflist);

        { record start of this unit's data }
        FUnitStartBytes:=G_ByteCounter;

        { initialize base class lists required by inherited write_symtable_* methods }
        defnumberlist:=TFPObjectList.Create(false);
        deftowritelist:=TFPObjectList.Create(false);

        { mark all definitions as used so write_symtable_defs will process them.
          this must include used unit defs, because system types like LongInt
          are referenced by fields in user records/classes. }
        mark_used_unit_defs(current_module);
        if assigned(current_module.globalsymtable) then
          mark_defs_used(current_module.globalsymtable);
        if assigned(current_module.localsymtable) then
          mark_defs_used(current_module.localsymtable);

        { write types from used units }
        write_used_unit_type_info(opdflist,current_module);

        { write types from global symbol table }
        if assigned(current_module.globalsymtable) then
          write_symtable_defs(opdflist,current_module.globalsymtable);

        { write types from local symbol table }
        if assigned(current_module.localsymtable) then
          write_symtable_defs(opdflist,current_module.localsymtable);

        { write symbols (variables) from global symbol table }
        if assigned(current_module.globalsymtable) then
          write_symtable_syms(opdflist,current_module.globalsymtable);

        { write symbols (variables) from local symbol table }
        if assigned(current_module.localsymtable) then
          write_symtable_syms(opdflist,current_module.localsymtable);

        { write procedure definitions (function scopes, locals, params) }
        if assigned(current_module.globalsymtable) then
          write_symtable_procdefs(opdflist,current_module.globalsymtable);
        if assigned(current_module.localsymtable) then
          write_symtable_procdefs(opdflist,current_module.localsymtable);

        { reset dbg_state on all tracked defs so they can be reused }
        for i:=0 to defnumberlist.count-1 do
          begin
            def:=tdef(defnumberlist[i]);
            if assigned(def) then
              def.dbg_state:=dbg_state_unused;
          end;

        { append accumulated line info records (collected during insertlineinfo calls) }
        opdflist.concatList(FLineInfoList);

        { record this unit's name and data size for directory }
        if assigned(current_module.realmodulename) then
          modname:=current_module.realmodulename^
        else
          modname:='?';
        G_UnitSizes.Add(Pointer(PtrUInt(G_ByteCounter-FUnitStartBytes)));
        New(ps);
        ps^:=modname;
        G_UnitNames.Add(ps);

        { if this is the main program (not a unit), emit the directory }
        if not current_module.is_unit then
          emit_unit_directory(opdflist);

        defnumberlist.free;
        defnumberlist:=nil;
        deftowritelist.free;
        deftowritelist:=nil;
      end;


    procedure TOPDFDebugWriter.insertlineinfo(list:TAsmList);
      var
        currfileinfo,
        lastfileinfo    : tfileposinfo;
        currsectype     : TAsmSectiontype;
        hp              : tai;
        infile          : tinputfile;
        currlabel       : tasmlabel;
        nolineinfolevel : Integer;
        filename        : AnsiString;
        filenamelen     : Word;
        recsize         : Cardinal;
      begin
        FillChar(lastfileinfo,sizeof(lastfileinfo),0);
        currsectype:=sec_code;
        nolineinfolevel:=0;

        hp:=Tai(list.first);
        while assigned(hp) do
          begin
            case hp.typ of
              ait_section:
                currsectype:=tai_section(hp).sectype;
              ait_force_line:
                lastfileinfo.line:=-1;
              ait_marker:
                begin
                  case tai_marker(hp).kind of
                    mark_NoLineInfoStart:
                      inc(nolineinfolevel);
                    mark_NoLineInfoEnd:
                      dec(nolineinfolevel);
                    else
                      ;
                  end;
                end;
              else
                ;
            end;

            if (currsectype=sec_code) and
               (hp.typ=ait_instruction) then
              begin
                currfileinfo:=tailineinfo(hp).fileinfo;

                { set line to 0 for code without line info }
                if nolineinfolevel>0 then
                  currfileinfo.line:=0;

                { emit a record when file or line changes }
                if (currfileinfo.fileindex<>0) and
                   (currfileinfo.line<>0) and
                   ((lastfileinfo.line<>currfileinfo.line) or
                    (lastfileinfo.fileindex<>currfileinfo.fileindex) or
                    (lastfileinfo.moduleindex<>currfileinfo.moduleindex)) then
                  begin
                    { create a label at this instruction for address resolution }
                    current_asmdata.getlabel(currlabel,alt_dbgline);
                    list.insertbefore(tai_label.create(currlabel),hp);

                    { resolve source file name }
                    infile:=get_module(currfileinfo.moduleindex).sourcefiles.get_file(currfileinfo.fileindex);
                    if assigned(infile) then
                      begin
                        filename:=infile.path+infile.name;
                        filenamelen:=Word(Length(filename));

                        { record payload: Address(8) + LineNumber(4) + ColumnNumber(2) + FileNameLen(2) + FileName }
                        recsize:=8+4+2+2+Cardinal(filenamelen);

                        { write to FLineInfoList - merged into al_opdf during inserttypeinfo }
                        EmitRecordHeader(FLineInfoList,REC_LINEINFO,recsize);

                        { address - linker resolves the label to final address }
                        EmitSymRef(FLineInfoList,tai_const.Create_type_sym(aitconst_ptr_unaligned,currlabel));

                        { LineNumber (4 bytes) }
                        EmitDWord(FLineInfoList,Cardinal(currfileinfo.line));

                        { ColumnNumber (2 bytes) }
                        EmitWord(FLineInfoList,currfileinfo.column);

                        { FileNameLen + FileName }
                        EmitWord(FLineInfoList,filenamelen);
                        EmitString(FLineInfoList,filename);
                      end;

                    lastfileinfo:=currfileinfo;
                  end;
              end;

            hp:=tai(hp.next);
          end;
      end;


    procedure TOPDFDebugWriter.insertmoduleinfo;
      begin
        { nothing to do - data is in asm list, handled by assembler }
      end;


initialization
  RegisterDebugInfo(dbg_opdf_info,TOPDFDebugWriter);
  G_TypeMapper := TTypeMapper.Create;
  G_EmittedTypeIDs := TFPHashList.Create;
  G_ByteCounter := 0;
  G_UnitSizes := TFPList.Create;
  G_UnitNames := TFPList.Create;

finalization
  G_TypeMapper.Free;
  G_EmittedTypeIDs.Free;
  if assigned(G_UnitNames) then
    begin
      for i:=0 to G_UnitNames.Count-1 do
        Dispose(PShortString(G_UnitNames[i]));
      G_UnitNames.Free;
    end;
  if assigned(G_UnitSizes) then
    G_UnitSizes.Free;
end.
