; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%macro	ADDIX   1
        and     ah,0c4h
        add     ZIX,%1
        adc     ah,0
        Fetch
%endmacro

%macro	RELADRX 0
        movsx   di,byte [esi+ebp]
        inc     si
        add     di,ZIX
%endmacro

IDD00:
IDD01:
IDD02:
IDD03:
IDD04:
IDD05:
IDD06:
IDD07:
IDD08:
	Fetch
IDD09:	; add ix,bc
	ADDIX	ZBC
IDD0A:
IDD0B:
IDD0C:
IDD0D:
IDD0E:
IDD0F:

IDD10:
IDD11:
IDD12:
IDD13:
IDD14:
IDD15:
IDD16:
IDD17:
IDD18:
	Fetch
IDD19:	; add ix,de
	ADDIX	ZDE
IDD1A:
IDD1B:
IDD1C:
IDD1D:
IDD1E:
IDD1F:

IDD20:
	Fetch
IDD21:	; ld ix,nnnn
	movzx	edi,word [esi+ebp]
	add	si,byte 2
	mov	ZIXL,edi
	Fetch
IDD22:	; ld (nnnn),ix
	push	edx
        mov     edx,ZIXL
	NextW	di
	WriteW	edi,dx
	pop	edx
	Fetch
IDD23:	; inc ix
	INC_R16	ZIX
	Fetch
IDD24:	; inc xh
	INC_R8	XH
IDD25:	; dec xh
	DEC_R8	XH
IDD26:	; ld  xh,n
	SaveAL	
	mov	al,[esi+ebp]
	inc	si
	mov	XH,al
	LoadAL
	Fetch	
IDD27:
IDD28:
	Fetch
IDD29:  ; add ix,ix
	mov	edi,ZIXL
        and     ah,0c4h
        add     ZIX,di
        adc     ah,0
	Fetch
IDD2A:	; ld ix,(nnnn)
	NextW	di
	mov	di,[edi+ebp]
	mov	ZIX,di
	Fetch
IDD2B:	; dec ix
	DEC_R16	ZIX
IDD2C:	; inc xl
	INC_R8	XL
IDD2D:	; dec xl
	DEC_R8	XL
IDD2E:	; ld  xl,n
	SaveAL	
	mov	al,[esi+ebp]
	inc	si
	mov	XL,al
	LoadAL
	Fetch	
IDD2F:

IDD30:
IDD31:
IDD32:
IDD33:
	Fetch
IDD34:	; inc (ix+??)
	RELADRX
	INC_M8	edi
IDD35:	; dec (ix+??)
	RELADRX
	DEC_M8	edi

IDD36:	; ld  (ix+??),n
	RELADRX
	SaveAL
	NextB		al
	WriteB 		edi,al
	LoadAL
	Fetch
IDD37:
IDD38:
	Fetch
IDD39:	; add ix,sp
	mov	edi,ZSPL
        and     ah,0c4h
        add     ZIX,di
        adc     ah,0
	Fetch
IDD3A:
IDD3B:
IDD3C:
IDD3D:
IDD3E:
IDD3F:
	Fetch

IDD40:
IDD41:
IDD42:
IDD43:
	Fetch
IDD44:  ; ld b,xh
	LD_R8_R8 ZB,XH
IDD45:	; ld b,xl
	LD_R8_R8 ZB,XL
IDD46:	; ld b,(ix+??)
	RELADRX
	mov	ZB,[edi+ebp]
	Fetch
IDD47:

IDD48:
IDD49:
IDD4A:
IDD4B:
	Fetch
IDD4C:  ; ld c,xh
	LD_R8_R8 ZC,XH
IDD4D:	; ld c,xl
	LD_R8_R8 ZC,XL
IDD4E:	; ld c,(ix+??)
	RELADRX
	mov	ZC,[edi+ebp]
	Fetch
IDD4F:
	Fetch

IDD50:
IDD51:
IDD52:
IDD53:
	Fetch
IDD54:  ; ld d,xh
	LD_R8_R8 ZD,XH
IDD55:	; ld d,xl
	LD_R8_R8 ZD,XL
IDD56:	; ld d,(ix+??)
	RELADRX
	mov	ZD,[edi+ebp]
	Fetch
IDD57:

IDD58:
IDD59:
IDD5A:
IDD5B:
	Fetch
IDD5C:  ; ld e,xh
	LD_R8_R8 ZE,XH
IDD5D:	; ld e,xl
	LD_R8_R8 ZE,XL
IDD5E:	; ld e,(ix+??)
	RELADRX
	mov	ZE,[edi+ebp]
	Fetch
IDD5F:
	Fetch

IDD60:	; ld xh,b
	LD_R8_R8 XH,ZB
IDD61:	; ld xh,c
	LD_R8_R8 XH,ZC
IDD62:	; ld xh,d
	LD_R8_R8 XH,ZD
IDD63:	; ld xh,e
	LD_R8_R8 XH,ZE
IDD64:	; ld xh,xh
	Fetch
IDD65:	; ld xh,xl
	SaveAL
	mov	al,XL
	mov	XH,al
	LoadAL
	Fetch
IDD66:	; ld h,(ix+??)
	RELADRX
	mov	ZH,[edi+ebp]
	Fetch	
IDD67:	; ld xh,a
	LD_R8_R8 XH,ZA

IDD68:	; ld xl,b
	LD_R8_R8 XL,ZB
IDD69:	; ld xl,c
	LD_R8_R8 XL,ZC
IDD6A:	; ld xl,d
	LD_R8_R8 XL,ZD
IDD6B:	; ld xl,e
	LD_R8_R8 XL,ZE
IDD6C:	; ld xl,xh
	SaveAL
	mov	al,XH
	mov	XL,al
	LoadAL
	Fetch
IDD6D:	; ld xl,xl
	Fetch
IDD6E:	; ld l,(ix+??)
	RELADRX
	mov	ZL,[edi+ebp]
	Fetch	
IDD6F:	; ld xl,a
	LD_R8_R8 XL,ZA

IDD70:	; ld (ix+??),b
	RELADRX
	WriteB	edi,ZB
	Fetch
IDD71:	; ld (ix+??),c
	RELADRX
	WriteB	edi,ZC
	Fetch
IDD72:	; ld (ix+??),d
	RELADRX
	WriteB	edi,ZD
	Fetch
IDD73:	; ld (ix+??),e
	RELADRX
	WriteB	edi,ZE
	Fetch
IDD74:	; ld (ix+??),h
	RELADRX
	WriteB	edi,ZH
	Fetch
IDD75:	; ld (ix+??),l
	RELADRX
	WriteB	edi,ZL
	Fetch
IDD76:
	Fetch
IDD77:	; ld (ix+??),a
	RELADRX
	WriteB	edi,ZA
	Fetch
IDD78:
IDD79:
IDD7A:
IDD7B:
	Fetch
IDD7C:  ; ld a,xh
	LD_R8_R8 ZA,XH
IDD7D:	; ld a,xl
	LD_R8_R8 ZA,XL
IDD7E:	; ld d,(ix+??)
	RELADRX
	mov	ZA,[edi+ebp]
	Fetch
IDD7F:
        Fetch

IDD80:
IDD81:
IDD82:
IDD83:
	Fetch
IDD84:	; add a,xh
	ADD8	XH
IDD85:	; add a,xl
	ADD8	XL
IDD86:	; add a,(ix+??)
	RELADRX
	ADD8	[edi+ebp]
IDD87:
      	Fetch
IDD88:
IDD89:
IDD8A:
IDD8B:
	Fetch
IDD8C:	; adc a,xh
	ADC8	XH
IDD8D:	; adc a,xl
	ADC8	XL
IDD8E:	; adc a,(ix+??)
	RELADRX
	ADC8	[edi+ebp]
IDD8F:
      	Fetch

IDD90:
IDD91:
IDD92:
IDD93:
	Fetch
IDD94:	; sub xh
	SUB8	XH
IDD95:	; sub xl
	SUB8	XL
IDD96:	; sub (ix+??)
	RELADRX
	SUB8	[edi+ebp]
IDD97:
      	Fetch
IDD98:
IDD99:
IDD9A:
IDD9B:
	Fetch
IDD9C:	; sbc a,xh
	SBC8	XH
IDD9D:	; sbc a,xl
	SBC8	XL
IDD9E:	; sbc a,(ix+??)
	RELADRX
	SBC8	[edi+ebp]
IDD9F:
      	Fetch

IDDA0:
IDDA1:
IDDA2:
IDDA3:
	Fetch
IDDA4:	; and xh
	LOG8	and,XH
IDDA5:	; and xl
	LOG8	and,XL
IDDA6:	; and (ix+??)
	RELADRX
	LOG8	and,[edi+ebp]
IDDA7:
	Fetch
IDDA8:
IDDA9:
IDDAA:
IDDAB:
	Fetch
IDDAC:	; xor xh
	LOG8	xor,XH
IDDAD:	; xor xl
	LOG8	xor,XL
IDDAE:	; xor (ix+??)
	RELADRX
	LOG8	xor,[edi+ebp]
IDDAF:
	Fetch

IDDB0:
IDDB1:
IDDB2:
IDDB3:
	Fetch
IDDB4:	; or  xh
	LOG8	or,XH
IDDB5:	; or  xl
	LOG8	or,XL
IDDB6:	; or  (ix+??)
	RELADRX
	LOG8	or,[edi+ebp]
IDDB7:
	Fetch
IDDB8:
IDDB9:
IDDBA:
IDDBB:
	Fetch
IDDBC:	; cp xh
	CP8	XH
IDDBD:	; cp xl
	CP8	XL
IDDBE:	; cp (ix+??)
	RELADRX
	CP8	[edi+ebp]
IDDBF:
	Fetch

IDDC0:
IDDC1:
IDDC2:
IDDC3:
IDDC4:
IDDC5:
IDDC6:
IDDC7:
IDDC8:
IDDC9:
IDDCA:
IDDCB:
	RELADRX
	push		edi
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [DDFDCBJMPtab+4*edi]

IDDCC:
IDDCD:
IDDCE:
IDDCF:
IDDD0:
IDDD1:
IDDD2:
IDDD3:
IDDD4:
IDDD5:
IDDD6:
IDDD7:
IDDD8:
IDDD9:
IDDDA:
IDDDB:
IDDDC:
IDDDD:
IDDDE:
IDDDF:
        Fetch

IDDE0:
	Fetch
IDDE1:	; pop ix
        mov     di,ZSP
        mov     di,[edi+ebp]
	mov	ZIX,di
        add     ZSP,byte 2
	Fetch	
IDDE2:
	Fetch

IDDE3:	; ex (sp),ix
	push		eax
	mov		di,ZSP
	mov		ax,[edi+ebp]
	xchg		ax,ZIX
	WriteW		edi,ax
	pop		eax
	Fetch

IDDE4:
	Fetch

IDDE5:	; push ix
	push	eax
        sub     ZSP,byte 2
        mov     di,ZSP
	mov	ax,ZIX
	WriteW	edi,ax
	pop	eax
	Fetch

IDDE6:
IDDE7:
IDDE8:
	Fetch

IDDE9:	; jp ix
	mov	edi,ZIXL
	mov	ZPC,di
	Fetch
IDDEA:
IDDEB:
IDDEC:
IDDED:
IDDEE:
IDDEF:
IDDF0:
IDDF1:
IDDF2:
IDDF3:
IDDF4:
IDDF5:
IDDF6:
IDDF7:
IDDF8:
	Fetch

IDDF9:	; ld sp,ix
	mov	edi,ZIXL
	mov	ZSP,di
	Fetch

IDDFA:
IDDFB:
IDDFC:
IDDFD:
IDDFE:
IDDFF:
        Fetch

