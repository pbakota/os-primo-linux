; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%macro	ADDIY   1
        and     ah,0c4h
        add     ZIY,%1
        adc     ah,0
        Fetch
%endmacro

%macro	RELADRY 0
        movsx   di,byte [esi+ebp]
        inc     si
        add     di,ZIY
%endmacro

IFD00:
IFD01:
IFD02:
IFD03:
IFD04:
IFD05:
IFD06:
IFD07:
IFD08:
	Fetch
IFD09:	; add iy,bc
	ADDIY	ZBC
IFD0A:
IFD0B:
IFD0C:
IFD0D:
IFD0E:
IFD0F:

IFD10:
IFD11:
IFD12:
IFD13:
IFD14:
IFD15:
IFD16:
IFD17:
IFD18:
	Fetch
IFD19:	; add iy,de
	ADDIY	ZDE
IFD1A:
IFD1B:
IFD1C:
IFD1D:
IFD1E:
IFD1F:

IFD20:
	Fetch
IFD21:	; ld iy,nnnn
	movzx	edi,word [esi+ebp]
	add	si,byte 2
	mov	ZIYL,edi
	Fetch
IFD22:	; ld (nnnn),iy
	push	edx
        mov     edx,ZIYL
	NextW	di
	WriteW	edi,dx
	pop	edx
	Fetch
IFD23:	; inc iy
	INC_R16	ZIY
	Fetch
IFD24:	; inc yh
	INC_R8	YH
IFD25:	; dec yh
	DEC_R8	YH
IFD26:	; ld  yh,n
	SaveAL	
	mov	al,[esi+ebp]
	inc	si
	mov	YH,al
	LoadAL
	Fetch	
IFD27:
IFD28:
	Fetch
IFD29:  ; add iy,iy
	mov	edi,ZIYL
        and     ah,0c4h
        add     ZIY,di
        adc     ah,0
	Fetch
IFD2A:	; ld iy,(nnnn)
	NextW	di
	mov	di,[edi+ebp]
	mov	ZIY,di
	Fetch
IFD2B:	; dec iy
	DEC_R16	ZIY
IFD2C:	; inc yl
	INC_R8	YL
IFD2D:	; dec yl
	DEC_R8	YL
IFD2E:	; ld  yl,n
	SaveAL	
	mov	al,[esi+ebp]
	inc	si
	mov	YL,al
	LoadAL
	Fetch	
IFD2F:

IFD30:
IFD31:
IFD32:
IFD33:
	Fetch
IFD34:	; inc (iy+??)
	RELADRY
	INC_M8	edi
IFD35:	; dec (iy+??)
	RELADRY
	DEC_M8	edi

IFD36:	; ld  (iy+??),n
	RELADRY
	SaveAL
	NextB		al
	WriteB 		edi,al
	LoadAL
	Fetch
IFD37:
IFD38:
	Fetch
IFD39:	; add iy,sp
	mov	edi,ZSPL
        and     ah,0c4h
        add     ZIY,di
        adc     ah,0
	Fetch
IFD3A:
IFD3B:
IFD3C:
IFD3D:
IFD3E:
IFD3F:
	Fetch

IFD40:
IFD41:
IFD42:
IFD43:
	Fetch
IFD44:  ; ld b,yh
	LD_R8_R8 ZB,YH
IFD45:	; ld b,yl
	LD_R8_R8 ZB,YL
IFD46:	; ld b,(iy+??)
	RELADRY
	mov	ZB,[edi+ebp]
	Fetch
IFD47:

IFD48:
IFD49:
IFD4A:
IFD4B:
	Fetch
IFD4C:  ; ld c,yh
	LD_R8_R8 ZC,YH
IFD4D:	; ld c,yl
	LD_R8_R8 ZC,YL
IFD4E:	; ld c,(iy+??)
	RELADRY
	mov	ZC,[edi+ebp]
	Fetch
IFD4F:
	Fetch

IFD50:
IFD51:
IFD52:
IFD53:
	Fetch
IFD54:  ; ld d,yh
	LD_R8_R8 ZD,YH
IFD55:	; ld d,yl
	LD_R8_R8 ZD,YL
IFD56:	; ld d,(iy+??)
	RELADRY
	mov	ZD,[edi+ebp]
	Fetch
IFD57:

IFD58:
IFD59:
IFD5A:
IFD5B:
	Fetch
IFD5C:  ; ld e,yh
	LD_R8_R8 ZE,YH
IFD5D:	; ld e,yl
	LD_R8_R8 ZE,YL
IFD5E:	; ld e,(iy+??)
	RELADRY
	mov	ZE,[edi+ebp]
	Fetch
IFD5F:
	Fetch

IFD60:	; ld yh,b
	LD_R8_R8 YH,ZB
IFD61:	; ld yh,c
	LD_R8_R8 YH,ZC
IFD62:	; ld yh,d
	LD_R8_R8 YH,ZD
IFD63:	; ld yh,e
	LD_R8_R8 YH,ZE
IFD64:	; ld yh,yh
	Fetch
IFD65:	; ld yh,yl
	SaveAL
	mov	al,YL
	mov	YH,al
	LoadAL
	Fetch
IFD66:	; ld h,(iy+??)
	RELADRY
	mov	ZH,[edi+ebp]
	Fetch	
IFD67:	; ld yh,a
	LD_R8_R8 YH,ZA

IFD68:	; ld yl,b
	LD_R8_R8 YL,ZB
IFD69:	; ld yl,c
	LD_R8_R8 YL,ZC
IFD6A:	; ld yl,d
	LD_R8_R8 YL,ZD
IFD6B:	; ld yl,e
	LD_R8_R8 YL,ZE
IFD6C:	; ld yl,yh
	SaveAL
	mov	al,YH
	mov	YL,al
	LoadAL
	Fetch
IFD6D:	; ld yl,yl
	Fetch
IFD6E:	; ld l,(iy+??)
	RELADRY
	mov	ZL,[edi+ebp]
	Fetch	
IFD6F:	; ld yl,a
	LD_R8_R8 YL,ZA

IFD70:	; ld (iy+??),b
	RELADRY
	WriteB	edi,ZB
	Fetch
IFD71:	; ld (iy+??),c
	RELADRY
	WriteB	edi,ZC
	Fetch
IFD72:	; ld (iy+??),d
	RELADRY
	WriteB	edi,ZD
	Fetch
IFD73:	; ld (iy+??),e
	RELADRY
	WriteB	edi,ZE
	Fetch
IFD74:	; ld (iy+??),h
	RELADRY
	WriteB	edi,ZH
	Fetch
IFD75:	; ld (iy+??),l
	RELADRY
	WriteB	edi,ZL
	Fetch
IFD76:
	Fetch
IFD77:	; ld (iy+??),a
	RELADRY
	WriteB	edi,ZA
	Fetch
IFD78:
IFD79:
IFD7A:
IFD7B:
	Fetch
IFD7C:  ; ld a,yh
	LD_R8_R8 ZA,YH
IFD7D:	; ld a,yl
	LD_R8_R8 ZA,YL
IFD7E:	; ld d,(iy+??)
	RELADRY
	mov	ZA,[edi+ebp]
	Fetch
IFD7F:
        Fetch

IFD80:
IFD81:
IFD82:
IFD83:
	Fetch
IFD84:	; add a,yh
	ADD8	YH
IFD85:	; add a,yl
	ADD8	YL
IFD86:	; add a,(iy+??)
	RELADRY
	ADD8	[edi+ebp]
IFD87:
      	Fetch
IFD88:
IFD89:
IFD8A:
IFD8B:
	Fetch
IFD8C:	; adc a,yh
	ADC8	YH
IFD8D:	; adc a,yl
	ADC8	YL
IFD8E:	; adc a,(iy+??)
	RELADRY
	ADC8	[edi+ebp]
IFD8F:
      	Fetch

IFD90:
IFD91:
IFD92:
IFD93:
	Fetch
IFD94:	; sub yh
	SUB8	YH
IFD95:	; sub yl
	SUB8	YL
IFD96:	; sub (iy+??)
	RELADRY
	SUB8	[edi+ebp]
IFD97:
      	Fetch
IFD98:
IFD99:
IFD9A:
IFD9B:
	Fetch
IFD9C:	; sbc a,yh
	SBC8	YH
IFD9D:	; sbc a,yl
	SBC8	YL
IFD9E:	; sbc a,(iy+??)
	RELADRY
	SBC8	[edi+ebp]
IFD9F:
      	Fetch

IFDA0:
IFDA1:
IFDA2:
IFDA3:
	Fetch
IFDA4:	; and yh
	LOG8	and,YH
IFDA5:	; and yl
	LOG8	and,YL
IFDA6:	; and (iy+??)
	RELADRY
	LOG8	and,[edi+ebp]
IFDA7:
	Fetch
IFDA8:
IFDA9:
IFDAA:
IFDAB:
	Fetch
IFDAC:	; xor yh
	LOG8	xor,YH
IFDAD:	; xor yl
	LOG8	xor,YL
IFDAE:	; xor (iy+??)
	RELADRY
	LOG8	xor,[edi+ebp]
IFDAF:
	Fetch

IFDB0:
IFDB1:
IFDB2:
IFDB3:
	Fetch
IFDB4:	; or  yh
	LOG8	or,YH
IFDB5:	; or  yl
	LOG8	or,YL
IFDB6:	; or  (iy+??)
	RELADRY
	LOG8	or,[edi+ebp]
IFDB7:
	Fetch
IFDB8:
IFDB9:
IFDBA:
IFDBB:
	Fetch
IFDBC:	; cp yh
	CP8	YH
IFDBD:	; cp yl
	CP8	YL
IFDBE:	; cp (iy+??)
	RELADRY
	CP8	[edi+ebp]
IFDBF:
	Fetch

IFDC0:
IFDC1:
IFDC2:
IFDC3:
IFDC4:
IFDC5:
IFDC6:
IFDC7:
IFDC8:
IFDC9:
IFDCA:
IFDCB:
	RELADRY
	push		edi
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [DDFDCBJMPtab+4*edi]

IFDCC:
IFDCD:
IFDCE:
IFDCF:
IFDD0:
IFDD1:
IFDD2:
IFDD3:
IFDD4:
IFDD5:
IFDD6:
IFDD7:
IFDD8:
IFDD9:
IFDDA:
IFDDB:
IFDDC:
IFDDD:
IFDDE:
IFDDF:
        Fetch

IFDE0:
	Fetch
IFDE1:	; pop iy
        mov     di,ZSP
        mov     di,[edi+ebp]
	mov	ZIY,di
        add     ZSP,byte 2
	Fetch	
IFDE2:
	Fetch

IFDE3:	; ex (sp),iy
	push		eax
	mov		di,ZSP
	mov		ax,[edi+ebp]
	xchg		ax,ZIY
	WriteW		edi,ax
	pop		eax
	Fetch

IFDE4:
	Fetch

IFDE5:	; push iy
	push	eax
        sub     ZSP,byte 2
        mov     di,ZSP
	mov	ax,ZIY
	WriteW	edi,ax
	pop	eax
	Fetch

IFDE6:
IFDE7:
IFDE8:
	Fetch

IFDE9:	; jp iy
	mov	edi,ZIYL
	mov	ZPC,di
	Fetch
IFDEA:
IFDEB:
IFDEC:
IFDED:
IFDEE:
IFDEF:
IFDF0:
IFDF1:
IFDF2:
IFDF3:
IFDF4:
IFDF5:
IFDF6:
IFDF7:
IFDF8:
	Fetch

IFDF9:	; ld sp,iy
	mov	edi,ZIYL
	mov	ZSP,di
	Fetch

IFDFA:
IFDFB:
IFDFC:
IFDFD:
IFDFE:
IFDFF:
        Fetch

