; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%macro	Fetch	0
	jmp	near [RetPoint]
	align	4
%endmacro

%macro	NextB	 1
	mov	%1,byte [esi+ebp]
	inc	si
%endmacro

%macro	NextW	 1
	mov	%1,word [esi+ebp]
	add	si,byte 2
%endmacro

%macro	WriteB	2
	test	byte [%1+ebp+65536+4],0xff
	jz	short %%normal_write
  %ifnidn %1,edi
	mov	edi,%1
  %endif
  %ifnidn %2,al
	SaveAL
	mov	al,%2
  %endif
	call	_SpecWriteByte
  %ifnidn %2,al
	LoadAL
  %endif
	jmp	short %%wrtb_end
%%normal_write:
	mov	byte [%1+ebp],%2	
%%wrtb_end:
%endmacro

%macro	WriteW	2
	test	word [%1+ebp+65536+4],0xffff
	jz	short %%normal_write
  %ifnidn	%1,edi
	mov	edi,%1
  %endif
	push	eax
  %ifnidn %2,ax
	mov	ax,%2
  %endif
	call	_SpecWriteWord
	pop	eax
	jmp	short %%wrtw_end
%%normal_write:
	mov	word [%1+ebp],%2	
%%wrtw_end:
%endmacro

%macro	LD_R16_NNNN 1
	movzx	%1,word [esi+ebp]
	add	si,byte 2
	Fetch
%endmacro

%macro	INC_R16 1
	inc	%1
	Fetch
%endmacro

%macro	DEC_R16 1
	dec	%1
	Fetch
%endmacro

%macro	INC_R8	1
	sahf
	inc 	%1
	lahf
	jo	short %%l0
	and	ah,0xf9
	Fetch
%%l0:
        and    ah,0xf9
        or     ah,4
	Fetch
%endmacro

%macro	DEC_R8	1
        sahf
        dec    %1
        lahf
        jo     short %%l0
        and    ah,0f3h
        Fetch
%%l0:
        or     ah,4
        Fetch
%endmacro

%macro 	LD_R8_N	1
	NextB	%1
	Fetch
%endmacro

%macro	ADD_HL_R16 1
        and     ah,0c4h
	add	bx,%1
        adc     ah,0
	Fetch	
%endmacro

%macro	INC_M8	1
	push	edx
	mov	dl,[ebp+%1]
	sahf
	inc 	dl
	lahf
	jo	short %%l0
	and	ah,0xf9
	WriteB  %1,dl	
	pop	edx
	Fetch
%%l0:
        and    ah,0xf9
        or     ah,4
	WriteB %1,dl
	pop	edx
	Fetch
%endmacro

%macro	DEC_M8	1
	push	edx
	mov	dl,[ebp+%1]
        sahf
        dec    	dl
        lahf
        jo     	short %%l0
        and    	ah,0f3h
	WriteB 	%1,dl
	pop	edx
        Fetch
%%l0:
        or     	ah,4
	WriteB 	%1,dl
	pop	edx
        Fetch
%endmacro

%macro	LD_R8_R8 2
	mov	%1,%2
	Fetch
%endmacro

%macro	LD_R8_HL 1
	mov	%1,byte [ebp+ebx]
	Fetch
%endmacro

%macro	LD_HL_R8 1
	WriteB	ebx,%1
	Fetch
%endmacro

%macro	ADD8   1
        add    al,%1
        lahf
        jo     short %%l_z80add
        and    ah,0f9h
        Fetch
%%l_z80add:
        and    ah,0f9h
        or     ah,4
        Fetch
%endmacro

%macro	ADC8   1
        sahf
        adc    al,%1
        lahf
        jo     short %%l_z80adc
        and    ah,0f9h
        Fetch
%%l_z80adc:
        and    ah,0f9h
        or     ah,4
        Fetch
%endmacro

%macro 	SUB8   1
        sub    al,%1
        lahf
        jo     short %%l_z80sub
        and    ah,0f3h
        Fetch
%%l_z80sub:
        or     ah,4
        Fetch
%endmacro

%macro  SBC8   1
        sahf
        sbb    al,%1
        lahf
        jo     short %%l_z80sbc
        and    ah,0f3h
        Fetch
%%l_z80sbc:
        or     ah,4
        Fetch
%endmacro

%macro  LOG8   2                      ;; AND XOR OR
        %1     al,%2
        lahf
	and	ah,0xec			;; clear H and N (xor, or)
  %ifidn	%1,and
	or	ah,0x10			;; set H for "and"
  %endif

        Fetch
%endmacro

%macro	CP8     1
        cmp    al,%1
        lahf
        jo     short %%l_z80cp
        and    ah,0f3h
        Fetch
%%l_z80cp:
        or     ah,4
        Fetch
%endmacro

%macro	RETcc	2
        test	ah,%2
%if %1==1
	jz	short %%retcc_l0
%else
	jnz	short %%retcc_l0
%endif
	mov	di,ZSP
	add	ZSP,byte 2
	mov	si,[edi+ebp]
%%retcc_l0:
	Fetch
%endmacro

%macro	JPcc	2
        test	ah,%2
%if %1==1
	jz	short %%jpcc_l0
%else
	jnz	short %%jpcc_l0
%endif
	mov	ZPC,[esi+ebp]
	Fetch
%%jpcc_l0:
	add	ZPC,byte 2
	Fetch
%endmacro

%macro	CALLcc	2
        test	ah,%2
%if %1==1
	jz	short %%callcc_l0
%else
	jnz	short %%callcc_l0
%endif
        sub     ZSP,byte 2
        mov     di,ZSP
	add	ZPC,byte 2
	WriteW	edi,ZPC
	mov	ZPC,[esi+ebp-2]
	Fetch	
%%callcc_l0:
	add	ZPC,byte 2
	Fetch
%endmacro

%macro	POP_R16	1
        mov     di,ZSP
        mov     %1,[edi+ebp]
        add     ZSP,byte 2
  %ifidn %1,ZAF
	xchg	al,ah
  %endif
        Fetch
%endmacro

%macro	PUSH_R16 1
        sub     ZSP,byte 2
        mov     di,ZSP
  %ifidn %1,ZAF
	xchg	al,ah
  %endif
	WriteW	edi,%1
  %ifidn %1,ZAF
	xchg	al,ah
  %endif
	Fetch
%endmacro

%macro	RST 1
        sub     ZSP,byte 2
        mov     di,ZSP
	WriteW	edi,ZPC
	mov	ZPC,%1
	Fetch
%endmacro

%macro	SaveAL 0
	mov	[alSave],al
%endmacro

%macro	LoadAL 0
	mov	al,[alSave]
%endmacro
