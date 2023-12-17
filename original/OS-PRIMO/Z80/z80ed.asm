; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%include "ed_macros.inc"

IED00:	call	_ExtProc0
	Fetch
IED01:	call	_ExtProc1
	Fetch
IED02:	call	_ExtProc2
	Fetch
IED03:	call	_ExtProc3
	Fetch
IED04:
IED05:
IED06:
IED07:
IED08:
IED09:
IED0A:
IED0B:
IED0C:
IED0D:
IED0E:
IED0F:
IED10:
IED11:
IED12:
IED13:
IED14:
IED15:
IED16:
IED17:
IED18:
IED19:
IED1A:
IED1B:
IED1C:
IED1D:
IED1E:
IED1F:
IED20:
IED21:
IED22:
IED23:
IED24:
IED25:
IED26:
IED27:
IED28:
IED29:
IED2A:
IED2B:
IED2C:
IED2D:
IED2E:
IED2F:
IED30:
IED31:
IED32:
IED33:
IED34:
IED35:
IED36:
IED37:
IED38:
IED39:
IED3A:
IED3B:
IED3C:
IED3D:
IED3E:
IED3F:
	Fetch


IED40:	; in b,(c)
	IN_C	ZB
IED41:	; out (c),b
	OUT_C	ZB
IED42:	; sbc hl,bc
	SBCHL	ZBC
IED43:	; ld (nnnn),bc
	LDMEMR16 ZBC
IED44:	; neg
	sahf
        neg     al
        lahf
        jo      short l_neg
        and     ah,0f3h
        Fetch
l_neg:
        or      ah,4
        Fetch
IED45:	; retn
	SaveAL
	mov	al,[_Z_IFF2]		; IFF2 => IFF1
	mov	[_Z_IFF1],al
	LoadAL
	POP_R16	ZPC			; pop PC
IED46:	; im 0
	mov	byte [_Z_IMOD],0x00
	Fetch
IED47:	; ld i,a
	mov	[_Z_I],al	
	Fetch
IED48:	; in c,(c)
	IN_C	ZC
IED49:	; out (c),c
	OUT_C	ZC
IED4A:	; adc hl,bc
	ADCHL	ZBC
IED4B:	; ld bc,(nnnn)
	LDR16MEM ZBC
IED4C:	; neg*
	jmp	IED44
IED4D:	; reti
	SaveAL
	mov	al,[_Z_IFF2]
	mov	[_Z_IFF1],al
	LoadAL
	POP_R16	ZPC
IED4E:	; im 0*
	jmp	IED46
IED4F:	; ld r,a
	mov	[_Z_R],al
	Fetch
	

IED50:	; in d,(c)
	IN_C	ZD
IED51:	; out (c),d
	OUT_C	ZD
IED52:	; sbc hl,de
	SBCHL	ZDE
IED53:	; ld (nnnn),de
	LDMEMR16 ZDE
IED54:	; neg*
        jmp     IED44
IED55:	; retn*
        jmp     IED45
IED56:	; im 1
	mov	byte [_Z_IMOD],0x01
	Fetch
IED57:	; ld a,i
        mov     al,[_Z_I]
        test    al,0FFh
        ror     ah,1
        lahf
        and     ah,11111011b
 	SaveAL
	mov	al,[_Z_IFF2]
	and	al,1
	shl	al,1
        or      ah,al
	LoadAL
        Fetch
IED58:	; in e,(c)
	IN_C	ZE
IED59:	; out (c),e
	OUT_C	ZE
IED5A:	; adc hl,de
	ADCHL	ZDE
IED5B:	; ld de,(nnnn)
	LDR16MEM ZDE
IED5C:	; neg*
	jmp	IED44
IED5D:	; retn*
	jmp	IED45
IED5E:	; im 2
	mov     byte [_Z_IMOD],0x02
	Fetch
IED5F:	; ld a,r
        mov     al,[_Z_R]
        test    al,0FFh
        ror     ah,1
        lahf
        and     ah,11111011b
 	SaveAL
	mov	al,[_Z_IFF2]		; IFF2 => P/V
	and	al,1
	shl	al,1
        or      ah,al
	LoadAL
        Fetch

IED60:	; in h,(c)
	IN_C	ZH
IED61:	; out (c),h
	OUT_C	ZH
IED62:	; sbc hl,hl
	SBCHL	ZHL
IED63:	; ld (nnnn),hl
	LDMEMR16 ZHL
IED64:	; neg*
        jmp     IED44
IED65:	; retn*
        jmp     IED45
IED66:	; im 0
	jmp     IED46
IED67:	; rrd
	push	ecx
        mov     cl,[ZHLL+ebp]
        mov     ch,al
        xor     al,cl
        and     al,0f0h
        xor     al,cl
        shr     cx,4
        test    al,al
        ror     ah,1
        lahf
        WriteB	ZHLL,cl
	pop	ecx
	Fetch
IED68:	; in l,(c)
	IN_C	ZL
IED69:	; out (c),l
	OUT_C	ZL
IED6A:	; adc hl,hl
	ADCHL	ZHL
IED6B:	; ld hl,(nnnn)
	LDR16MEM ZHL
IED6C:	; neg*
	jmp	IED44
IED6D:	; retn*
	jmp	IED45
IED6E:	; im 0*
	jmp	IED46
IED6F:  ; rld
	push	ecx
        mov     cl,[ZHLL+ebp]
        xor     ch,ch
        shl     cx,4
        xor     cl,al
        and     cl,0f0h
        xor     cl,al
        and     al,0f0h
        or      al,ch
        ror     ah,1
        lahf
	WriteB	ZHLL,cl
	pop	ecx
	Fetch

IED70:	; in f,(c)
	IN_C	[Dummy]
IED71:	; out (c),0
	OUT_C	0
IED72:	; sbc hl,sp
	SBCHL	ZSP
IED73:	; ld (nnnn),sp
	push	edx
        mov     edx,[_Z_SP]
	NextW	di
	WriteW	edi,dx
	pop	edx
	Fetch
IED74:	; neg*
        jmp     IED44
IED75:	; retn*
        jmp     IED45
IED76:	; im 1*
	jmp     IED56
IED77:	; nop*
        Fetch
IED78:	; in a,(c)
	IN_C	ZA
IED79:	; out (c),a
	OUT_C	ZA
IED7A:	; adc hl,sp
	ADCHL	ZSP
IED7B:	; ld sp,(nnnn)
	NextW	di
	mov	di,[edi+ebp]
	mov	ZSP,di
	Fetch
IED7C:	; neg*
	jmp	IED44
IED7D:	; retn*
	jmp	IED45
IED7E:	; im 2*
	jmp	IED5E
IED7F:  ; nop*
	Fetch

IED80:
IED81:
IED82:
IED83:
IED84:
IED85:
IED86:
IED87:
IED88:
IED89:
IED8A:
IED8B:
IED8C:
IED8D:
IED8E:
IED8F:
IED90:
IED91:
IED92:
IED93:
IED94:
IED95:
IED96:
IED97:
IED98:
IED99:
IED9A:
IED9B:
IED9C:
IED9D:
IED9E:
IED9F:
	Fetch

IEDA0: 	; ldi
	SaveAL
	mov	al,[ZHLL+ebp]
	WriteB	ZDEL,al
	inc	ZDE
	inc	ZHL
	ENDBLK
	LoadAL
	Fetch

IEDA1:	; cpi
        cmp     al,[ZHLL+ebp]
	ror	ah,1
	lahf
	and	ah,11111011b
	inc	ZHL
        dec    	ZBC
        jz    	short cpi_end
        or    	ah,4
cpi_end:
        Fetch

IEDA2:	; ini
	SaveAL
	call	_ByteIn
	WriteB	ZHLL,al
	inc	ZHL
	dec	ZB
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDA3:	; outi
	SaveAL
	mov	al,[ZHLL+ebp]
	call	_ByteOut
	inc	ZHL
	dec	ZB
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDA4:
IEDA5:
IEDA6:
IEDA7:
	Fetch

IEDA8: 	; ldd
	SaveAL
	mov	al,[ZHLL+ebp]
	WriteB	ZDEL,al
	dec	ZDE
	dec	ZHL
	ENDBLK
	LoadAL
	Fetch

IEDA9:	; cpd
        cmp     al,[ZHLL+ebp]
	ror	ah,1
	lahf
	and	ah,11111011b
	dec	ZHL
        dec    	ZBC
        jz    	short cpd_end
        or    	ah,4
cpd_end:
        Fetch

IEDAA:	; ind
	SaveAL
	call	_ByteIn
	WriteB	ZHLL,al
	dec	ZHL
	dec	ZB
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDAB:	; outd
	SaveAL
	mov	al,[ZHLL+ebp]
	call	_ByteOut
	dec	ZHL
	dec	ZB
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDAC:
IEDAD:
IEDAE:
IEDAF:
	Fetch

IEDB0: 	; ldir
	SaveAL
	mov	al,[ZHLL+ebp]
	WriteB	ZDEL,al
	inc	ZDE
	inc	ZHL
	and    	ah,0C1h
        dec    	ZBC
        jz    	short ldir_end
	or	ah,4
	sub	ZPC,byte 2
ldir_end:
	LoadAL
	Fetch

IEDB1:	; cpir
	cmp	al,[ZHLL+ebp]
	jz	short cpir_q
	ror	ah,1
	lahf
	and	ah,11111011b
	inc	ZHL
        dec    	ZBC
        jz    	short cpir_end
        sub	ZPC,byte 2
cpir_end:
        Fetch
cpir_q:
        ror     ah,1
        lahf
        inc     ZHL
        or      ah,4
        dec     ZBC
        jnz     short l_cpir2
        and     ah,0fbh
l_cpir2:
	Fetch

IEDB2:	; inir
	SaveAL
	call	_ByteIn
	WriteB	ZHLL,al
	inc	ZHL
	dec	ZB
	jz	short inir_q
        sub	ZPC,byte 2
inir_q:
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDB3:	; otir
	SaveAL
	mov	al,[ZHLL+ebp]
	call	_ByteOut
	inc	ZHL
	dec	ZB
	jz	otir_q
        sub	ZPC,byte 2
otir_q:
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDB4:
IEDB5:
IEDB6:
IEDB7:
	Fetch

IEDB8: 	; lddr
	SaveAL
	mov	al,[ZHLL+ebp]
	WriteB	ZDEL,al
	dec	ZDE
	dec	ZHL
	and    	ah,0C1h
        dec    	ZBC
        jz    	short lddr_end
	sub	ZPC,byte 2
	or	ah,4
lddr_end:
	LoadAL
	Fetch

IEDB9:	; cpdr
	cmp	al,[ZHLL+ebp]
	jz	short cpdr_q
	ror	ah,1
	lahf
	and	ah,11111011b
	dec	ZHL
        dec    	ZBC
        jz    	short cpdr_end
        sub	ZPC,byte 2
cpdr_end:
        Fetch
cpdr_q:
        ror     ah,1
        lahf
        dec     ZHL
        or      ah,4
        dec     ZBC
        jnz     short l_cpdr2
        and     ah,0fbh
l_cpdr2:
	Fetch

IEDBA:	; indr
	SaveAL
	call	_ByteIn
	WriteB	ZHLL,al
	dec	ZHL
	dec	ZB
	jz	short indr_q
        sub	ZPC,byte 2
indr_q:
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDBB:	; otdr
	SaveAL
	mov	al,[ZHLL+ebp]
	call	_ByteOut
	dec	ZHL
	dec	ZB
	jz	otdr_q
        sub	ZPC,byte 2
otdr_q:
	ror	ah,1
	lahf
	LoadAL
	Fetch

IEDBC:
IEDBD:
IEDBE:
IEDBF:
	Fetch


IEDC0:
IEDC1:
IEDC2:
IEDC3:
IEDC4:
IEDC5:
IEDC6:
IEDC7:
IEDC8:
IEDC9:
IEDCA:
IEDCB:
IEDCC:
IEDCD:
IEDCE:
IEDCF:
IEDD0:
IEDD1:
IEDD2:
IEDD3:
IEDD4:
IEDD5:
IEDD6:
IEDD7:
IEDD8:
IEDD9:
IEDDA:
IEDDB:
IEDDC:
IEDDD:
IEDDE:
IEDDF:
IEDE0:
IEDE1:
IEDE2:
IEDE3:
IEDE4:
IEDE5:
IEDE6:
IEDE7:
IEDE8:
IEDE9:
IEDEA:
IEDEB:
IEDEC:
IEDED:
IEDEE:
IEDEF:
IEDF0:
IEDF1:
IEDF2:
IEDF3:
IEDF4:
IEDF5:
IEDF6:
IEDF7:
IEDF8:
IEDF9:
IEDFA:
IEDFB:
IEDFC:
IEDFD:
IEDFE:
IEDFF:
	Fetch
	