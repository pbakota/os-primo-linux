; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

bits	32
cpu	486

	section	.data use32 flat class=data

	global	_Z_BC,_Z_DE,_Z_HL,_Z_AF
	global	_Z_BC2,_Z_DE2,_Z_HL2,_Z_AF2
	global	_Z_PC,_Z_SP,_Z_IX,_Z_IY,_Z_I,_Z_R
	global	_Z_IFF1,_Z_IFF2,_Z_IMOD,_HWFlag,_Z_ICtr
	global	_Z_IM2V

	align	4

_Z_BC	dd	0
_Z_DE	dd	0
_Z_HL	dd	0
_Z_AF	dd	0
_Z_BC2	dd	0
_Z_DE2	dd	0
_Z_HL2	dd	0
_Z_AF2	dd	0
_Z_PC	dd	0
_Z_SP	dd	0
_Z_IX	dd	0
_Z_IY	dd	0
_Z_I	db	0
_Z_R	db	0
_Z_IFF1	db	0
_Z_IFF2	db	0
_Z_IMOD	db	0
_Z_IM2V	db	0feh
_HWFlag	db	0

alSave	db	0
Dummy	db	0
EIctr	db	0

	align	4
_Z_ICtr	dd	0

RetPoint dd	0

%define	_ZCF	1
%define	_ZNF	2
%define	_ZPF	4
%define	_ZHF	16
%define	_ZZF	64
%define	_ZSF	128

MainJMPtab:
	%include "t_main.inc"
CBJMPtab:
	%include "t_cb.inc"
EDJMPtab:
	%include "t_ed.inc"
DDJMPtab:
	%include "t_dd.inc"
FDJMPtab:
	%include "t_fd.inc"
DDFDCBJMPtab:
	%include "t_ddfdcb.inc"

%define _fIntFlag	0x01
%define _fNmiFlag	0x02
%define _fEIFlag	0x04
%define _fHaltFlag	0x08
%define	_fExtSub	0x20
%define	_fEscFlag	0x80

%define	ZB	ch
%define	ZC	cl
%define ZD	dh
%define	ZE	dl
%define	ZH	bh
%define	ZL	bl
%define	ZF	ah
%define	ZA	al

%define	ZBC	cx
%define	ZDE     dx
%define	ZHL     bx
%define	ZAF     ax
%define	ZSP     word [_Z_SP]
%define ZPC     si
%define ZIX	word [_Z_IX]
%define ZIY	word [_Z_IY]
%define	XL	byte [_Z_IX]
%define XH	byte [_Z_IX+1]
%define YL	byte [_Z_IY]
%define YH	byte [_Z_IY+1]

%define	ZBCL	ecx
%define	ZDEL    edx
%define	ZHLL    ebx
%define	ZAFL    eax
%define	ZSPL    dword [_Z_SP]
%define ZPCL    esi
%define ZIXL	dword [_Z_IX]
%define ZIYL	dword [_Z_IY]


	section	.text use32 flat class=code

	extern	_Z80mem         ; Address of the 64K Z80 memory
	extern	_SpecWriteByte	; Function called in case special memory
				; write (byte) required
	extern	_SpecWriteWord	; Function called in case special memory
				; write (word) required
	extern	_ByteIn		; Function for 'in' instructions
	extern	_ByteOut	; Function for 'out' instructions

	extern	_ExtSub		; external subroutine 

	; procedures for communitacion with the host
	extern	_ExtProc0	; ED00
	extern	_ExtProc1	; ED01
	extern	_ExtProc2	; ED02
	extern	_ExtProc3	; ED03 

; --------------------------------------------------------------------------
; - MACRO definitions 							   -
; --------------------------------------------------------------------------

%include "main_macros.inc"

; --------------------------------------------------------------------------
; - Z80 emulation 							   -
; --------------------------------------------------------------------------
ClrRegs:
	xor	eax,eax
	xor	ebx,ebx
	xor	ecx,ecx
	xor	edx,edx
	xor	edi,edi
	xor	esi,esi
	ret
LoadRegs:
	mov	ax,[_Z_AF]
	xchg	al,ah
	mov	bx,[_Z_HL]
	mov	cx,[_Z_BC]
	mov	dx,[_Z_DE]
	mov	si,[_Z_PC]
	mov	ebp,[_Z80mem]
	ret
SaveRegs:
	xchg	al,ah
	mov	[_Z_AF],ax
	mov	[_Z_HL],bx
	mov	[_Z_BC],cx
	mov	[_Z_DE],dx
	mov	[_Z_PC],si
	ret

	global	_Z80Reset

_Z80Reset:
	mov	ax,0xffff
	mov	[_Z_AF],ax
	mov	[_Z_SP],ax
	xor	eax,eax
	mov	[_Z_PC],ax
	mov	[_Z_HL],ax
	mov	[_Z_BC],ax
	mov	[_Z_DE],ax
	mov	[_Z_IX],ax
	mov	[_Z_IY],ax
	mov	[_Z_I],al
	mov	[_Z_R],al
	mov	[_Z_IFF1],al
	mov	[_Z_IFF2],al
	mov	[_Z_IMOD],al
	mov	[_HWFlag],al
	ret

	global	_ExecOne,_ExecICtr

_ExecOne:
	pushad
	mov	eax,ExecOneRet
	mov	[RetPoint],eax
	call	ClrRegs
	call	LoadRegs
	jmp	short MainExecLoop
ExecOneRet:	
	call	SaveRegs
	popad
	ret

_ExecICtr:
	;pushad
	mov	eax,ExecICtrRet
	mov	[RetPoint],eax
	call	ClrRegs
	call	LoadRegs
ICtr_loop:
	jmp	short MainExecLoop
ExecICtrRet:
	dec	dword [_Z_ICtr]
	jnz	ICtr_loop
ESCfromICtr:
	call	SaveRegs
	;popad
	ret
	
MainExecLoop:
	inc	byte [_Z_R]
	test	byte [_HWFlag],0xff
	jnz	short HWHandler
MainFetch:
	movzx	edi,byte [esi+ebp]
	inc	si
	jmp	dword [MainJMPtab+4*edi]

;%define _fIntFlag	0x01	- INT request
;%define _fNmiFlag	0x02	- NMI request
;%define _fEIFlag	0x04	- EI executed previously
;%define _fHaltFlag	0x08	- processor halted
;%define _fExtSub	0x20	- external subroutine (call external func)
;%define _fEscFlag	0x80	- escape from the emulation (for ExecICtr)

HWHandler:
	test	byte [_HWFlag],_fEscFlag
	jnz	do_ESC
	test	byte [_HWFlag],_fExtSub
	jnz	do_EXTSUB
	test	byte [_HWFlag],_fNmiFlag
	jnz	do_NMI
	test	byte [_HWFlag],_fEIFlag
	jnz	do_EI
	test	byte [_HWFlag],_fIntFlag
	jnz	do_INT
	jmp	do_HALT
do_ESC:
	jmp	ESCfromICtr
do_EXTSUB:
	pushad
	call		_ExtSub		; call the external subroutine
	popad
	jmp		MainFetch	
do_EI:
	dec		byte [EIctr]
	jnz		MainFetch
	and		byte [_HWFlag],(255-_fEIFlag)
	mov		byte [_Z_IFF1],1
	mov		byte [_Z_IFF2],1
	jmp		MainFetch
do_NMI:
	jmp		end_NMI
do_INT:
	cmp		byte [_Z_IFF1],1
	jz		makeint
	jmp		MainFetch
makeint:
	cmp		byte [_Z_IMOD],2
	jz		short int_im2
int_im0:
int_im1:
        sub             ZSP,byte 2
        mov             di,ZSP
	WriteW	        edi,ZPC
	mov		ZPC,0x38
	SaveAL
	mov		al,[_Z_IFF1]		; IFF2 <= IFF1
	mov		[_Z_IFF2],al
	mov		byte [_Z_IFF1],0	; IFF1=0: disable int.
	and		byte [_HWFlag],(255-(_fHaltFlag+_fIntFlag))
	LoadAL
	jmp		MainFetch
int_im2:
        sub             ZSP,byte 2
        mov             di,ZSP
	WriteW	        edi,ZPC
	push		eax
	xor		eax,eax
	mov		ah,[_Z_I]		; register I
	mov		al,[_Z_IM2V]		; vector for im2
	mov		ax,[ebp+eax]		; get the address
	mov		ZPC,ax
	mov		al,[_Z_IFF1]		; IFF2 <= IFF1
	mov		[_Z_IFF2],al
	mov		byte [_Z_IFF1],0	; IFF1=0: disable int.
	and		byte [_HWFlag],(255-(_fHaltFlag+_fIntFlag))
	pop		eax
	jmp		MainFetch

do_HALT:
	Fetch	

end_NMI:
        sub             ZSP,byte 2
        mov             di,ZSP
	WriteW	        edi,ZPC			; push PC 
	mov		ZPC,0x66		; new PC 0x0066
	SaveAL
	mov		al,[_Z_IFF1]		; IFF2 <= IFF1
	mov		[_Z_IFF2],al
	mov		byte [_Z_IFF1],0	; disable int.
	and		byte [_HWFlag],(255-(_fHaltFlag+_fNmiFlag))
	LoadAL
	jmp	MainFetch

	align	4
MI00:	; nop
	Fetch

MI01:	; ld bc,nnnn
	LD_R16_NNNN	ZBCL

MI02:	; ld (bc),a
	WriteB		ZBCL,ZA
	Fetch

MI03:	; inc bc
	INC_R16		ZBC

MI04:	; inc b
	INC_R8		ZB

MI05:	; dec b	
	DEC_R8		ZB

MI06:	; ld b,n
	LD_R8_N		ZB

MI07:	; rlca
        sahf
        rol     	ZA,1
        lahf
        Fetch

MI08:	; ex	af,af'
	xchg		al,ah
	xchg		ZAFL,[_Z_AF2]
	xchg		al,ah	
	Fetch

MI09:	; add	hl,bc
	ADD_HL_R16	ZBC

MI0A:	; ld a,(bc)
	mov		al,[ecx+ebp]
	Fetch

MI0B:	; dec bc
	DEC_R16		ZBC

MI0C:	; inc c
	INC_R8		ZC

MI0D:	; dec c
	DEC_R8		ZC

MI0E:	; ld c,n
	LD_R8_N		ZC

MI0F:	; rrca
        sahf
        ror     	ZA,1
        lahf
        Fetch

MI10:	; djnz d
	movsx	edi,byte [esi+ebp]
	inc	si
	dec	ZB
	jz	short mi10_l0
	add	si,di
mi10_l0:
	Fetch

MI11:	; ld de,nnnn
	LD_R16_NNNN	ZDEL

MI12:	; ld (de),a
	WriteB		ZDEL,ZA
	Fetch

MI13:	; inc de
	INC_R16		ZDE

MI14:	; inc d
	INC_R8		ZD

MI15:	; dec d	
	DEC_R8		ZD

MI16:	; ld d,n
	LD_R8_N		ZD

MI17:	; rla
        sahf
        rcl     	ZA,1
        lahf
        Fetch

MI18:	; jr d
	movsx		edi,byte [esi+ebp]
	inc		si
	add		si,di
	Fetch

MI19:	; add	hl,de
	ADD_HL_R16	ZDE

MI1A:	; ld a,(de)
	mov		al,[edx+ebp]
	Fetch

MI1B:	; dec de
	DEC_R16		ZDE

MI1C:	; inc e
	INC_R8		ZE

MI1D:	; dec e
	DEC_R8		ZE

MI1E:	; ld e,n
	LD_R8_N		ZE

MI1F:	; rra
        sahf
        rcr     	ZA,1
        lahf
        Fetch

MI20:	; jr nz,d
	movsx		edi,byte [esi+ebp]
	inc		si
	test		ah,64
	jnz		short jrnz_l0
	add		si,di
jrnz_l0:
	Fetch

MI21:	; ld hl,nnnn
	LD_R16_NNNN	ZHLL

MI22:	; ld (nnnn),hl
	NextW		di
	WriteW		edi,ZHL
	Fetch

MI23:	; inc hl
	INC_R16		ZHL

MI24:	; inc h
	INC_R8		ZH

MI25:	; dec h	
	DEC_R8		ZH

MI26:	; ld h,n
	LD_R8_N		ZH

MI27:	; daa
        test    	ah,2
        jnz     	short mi27_SUBS
mi27_ADDS:
        sahf
        daa
        lahf
        Fetch
mi27_SUBS:
        sahf
        das
        lahf
        Fetch

MI28:	; jr z,d
	movsx		edi,byte [esi+ebp]
	inc		si
	test		ah,64
	jz		short jrz_l0
	add		si,di
jrz_l0:
	Fetch

MI29:	; add	hl,hl
	ADD_HL_R16	ZHL

MI2A:	; ld	hl,(nnnn)
	NextW		di
	mov		ZHL,[edi+ebp]
	Fetch

MI2B:	; dec hl
	DEC_R16		ZHL

MI2C:	; inc l
	INC_R8		ZL

MI2D:	; dec l
	DEC_R8		ZL

MI2E:	; ld l,n
	LD_R8_N		ZL

MI2F:	; cpl
        not     	al
        or      	ah,12h
	Fetch

MI30:	; jr nc,d
	movsx		edi,byte [esi+ebp]
	inc		si
	test		ah,1
	jnz		short jrnc_l0
	add		si,di
jrnc_l0:
	Fetch

MI31:	; ld sp,nnnn
	movzx		edi,word [esi+ebp]
	add		ZPC,2
	mov		ZSPL,edi
	Fetch

MI32:	; ld (nnnn),a
	NextW		di
	WriteB		edi,al
	Fetch

MI33:	; inc sp
	INC_R16		ZSP

MI34:	; inc (hl)
	INC_M8		ZHLL
MI35:	; dec (hl)
	DEC_M8		ZHLL
MI36:	; ld (hl),n
	push		eax
	NextB		al
	WriteB 		ZHLL,al
	pop		eax
	Fetch

MI37:	; scf
	or	ah,1
	Fetch

MI38:	; jr c,d
	movsx		edi,byte [esi+ebp]
	inc		si
	test		ah,1
	jz		short jrc_l0
	add		si,di
jrc_l0:
	Fetch

MI39:	; add	hl,sp
	ADD_HL_R16	ZSP

MI3A:	; ld a,(nnnn)
	NextW		di
	mov		al,[edi+ebp]
	Fetch

MI3B:	; dec sp
	DEC_R16		ZSP

MI3C:	; inc a
	INC_R8		ZA

MI3D:	; dec a
	DEC_R8		ZA

MI3E:	; ld a,n
	LD_R8_N		ZA

MI3F:	; ccf
	xor	ah,1
	Fetch

MI40:	; ld b,b
	LD_R8_R8	ZB,ZB
MI41:	; ld b,c
	LD_R8_R8	ZB,ZC
MI42:	; ld b,d
	LD_R8_R8	ZB,ZD
MI43:	; ld b,e
	LD_R8_R8	ZB,ZE
MI44:	; ld b,h
	LD_R8_R8	ZB,ZH
MI45:	; ld b,l
	LD_R8_R8	ZB,ZL
MI46:	; ld b,(hl)
	LD_R8_HL	ZB
MI47:	; ld b,a
	LD_R8_R8	ZB,ZA
MI48:	; ld c,b
	LD_R8_R8	ZC,ZB
MI49:	; ld c,c
	LD_R8_R8	ZC,ZC
MI4A:	; ld c,d
	LD_R8_R8	ZC,ZD
MI4B:	; ld c,e
	LD_R8_R8	ZC,ZE
MI4C:	; ld c,h
	LD_R8_R8	ZC,ZH
MI4D:	; ld c,l
	LD_R8_R8	ZC,ZL
MI4E:	; ld c,(hl)
	LD_R8_HL	ZC
MI4F:	; ld c,a
	LD_R8_R8	ZC,ZA

MI50:	; ld d,b
	LD_R8_R8	ZD,ZB
MI51:	; ld d,c
	LD_R8_R8	ZD,ZC
MI52:	; ld d,d
	LD_R8_R8	ZD,ZD
MI53:	; ld d,e
	LD_R8_R8	ZD,ZE
MI54:	; ld d,h
	LD_R8_R8	ZD,ZH
MI55:	; ld d,l
	LD_R8_R8	ZD,ZL
MI56:	; ld d,(hl)
	LD_R8_HL	ZD
MI57:	; ld d,a
	LD_R8_R8	ZD,ZA
MI58:	; ld e,b
	LD_R8_R8	ZE,ZB
MI59:	; ld e,c
	LD_R8_R8	ZE,ZC
MI5A:	; ld e,d
	LD_R8_R8	ZE,ZD
MI5B:	; ld e,e
	LD_R8_R8	ZE,ZE
MI5C:	; ld e,h
	LD_R8_R8	ZE,ZH
MI5D:	; ld e,l
	LD_R8_R8	ZE,ZL
MI5E:	; ld e,(hl)
	LD_R8_HL	ZE
MI5F:	; ld e,a
	LD_R8_R8	ZE,ZA

MI60:	; ld h,b
	LD_R8_R8	ZH,ZB
MI61:	; ld h,c
	LD_R8_R8	ZH,ZC
MI62:	; ld h,d
	LD_R8_R8	ZH,ZD
MI63:	; ld h,e
	LD_R8_R8	ZH,ZE
MI64:	; ld h,h
	LD_R8_R8	ZH,ZH
MI65:	; ld h,l
	LD_R8_R8	ZH,ZL
MI66:	; ld h,(hl)
	LD_R8_HL	ZH
MI67:	; ld h,a
	LD_R8_R8	ZH,ZA
MI68:	; ld l,b
	LD_R8_R8	ZL,ZB
MI69:	; ld l,c
	LD_R8_R8	ZL,ZC
MI6A:	; ld l,d
	LD_R8_R8	ZL,ZD
MI6B:	; ld l,e
	LD_R8_R8	ZL,ZE
MI6C:	; ld l,h
	LD_R8_R8	ZL,ZH
MI6D:	; ld l,l
	LD_R8_R8	ZL,ZL
MI6E:	; ld l,(hl)
	LD_R8_HL	ZL
MI6F:	; ld l,a
	LD_R8_R8	ZL,ZA

MI70:   ; ld (hl),b
        LD_HL_R8        ZB
MI71:   ; ld (hl),c
        LD_HL_R8        ZC
MI72:   ; ld (hl),d
        LD_HL_R8        ZD
MI73:   ; ld (hl),e
        LD_HL_R8        ZE
MI74:   ; ld (hl),h
        LD_HL_R8        ZH
MI75:   ; ld (hl),l
        LD_HL_R8        ZL
MI76:   ; halt
        or              byte [_HWFlag],_fHaltFlag
        Fetch
MI77:   ; ld (hl),a
        LD_HL_R8        ZA

MI78:	; ld a,b
	LD_R8_R8	ZA,ZB
MI79:	; ld a,c
	LD_R8_R8	ZA,ZC
MI7A:	; ld a,d
	LD_R8_R8	ZA,ZD
MI7B:	; ld a,e
	LD_R8_R8	ZA,ZE
MI7C:	; ld a,h
	LD_R8_R8	ZA,ZH
MI7D:	; ld a,l
	LD_R8_R8	ZA,ZL
MI7E:	; ld a,(hl)
	LD_R8_HL	ZA
MI7F:	; ld a,a
	LD_R8_R8	ZA,ZA


MI80:	; add a,b
	ADD8		ZB
MI81:	; add a,c
	ADD8		ZC
MI82:	; add a,d
	ADD8		ZD
MI83:	; add a,e
	ADD8		ZE
MI84:	; add a,h
	ADD8		ZH
MI85:	; add a,l
	ADD8		ZL
MI86:	; add a,(hl)
	ADD8		[ebx+ebp]
MI87:	; add a,a
	ADD8		ZA
MI88:	; adc a,b
	ADC8		ZB
MI89:	; adc a,c
	ADC8		ZC
MI8A:	; adc a,d
	ADC8		ZD
MI8B:	; adc a,e
	ADC8		ZE
MI8C:	; adc a,h
	ADC8		ZH
MI8D:	; adc a,l
	ADC8		ZL
MI8E:	; adc a,(hl)
	ADC8		[ebx+ebp]
MI8F:	; adc a,a
	ADC8		ZA

MI90:	; sub b
	SUB8		ZB
MI91:	; sub c
	SUB8		ZC
MI92:	; sub d
	SUB8		ZD
MI93:	; sub e
	SUB8		ZE
MI94:	; sub h
	SUB8		ZH
MI95:	; sub l
	SUB8		ZL
MI96:	; sub (hl)
	SUB8		[ebx+ebp]
MI97:	; sub a
	SUB8		ZA
MI98:	; sbc a,b
	SBC8		ZB
MI99:	; sbc a,c
	SBC8		ZC
MI9A:	; sbc a,d
	SBC8		ZD
MI9B:	; sbc a,e
	SBC8		ZE
MI9C:	; sbc a,h
	SBC8		ZH
MI9D:	; sbc a,l
	SBC8		ZL
MI9E:	; sbc a,(hl)
	SBC8		[ebx+ebp]
MI9F:	; sbc a,a
	SBC8		ZA

MIA0:   ; and b
        LOG8            and,ZB
MIA1:   ; and c
        LOG8            and,ZC
MIA2:   ; and d
        LOG8            and,ZD
MIA3:   ; and e
        LOG8            and,ZE
MIA4:   ; and h
        LOG8            and,ZH
MIA5:   ; and l
        LOG8            and,ZL
MIA6:   ; and (hl)
        LOG8            and,[ebx+ebp]
MIA7:   ; and a
        LOG8            and,ZA
MIA8:   ; xor b
        LOG8            xor,ZB
MIA9:   ; xor c
        LOG8            xor,ZC
MIAA:   ; xor d
        LOG8            xor,ZD
MIAB:   ; xor e
        LOG8            xor,ZE
MIAC:   ; xor h
        LOG8            xor,ZH
MIAD:   ; xor l
        LOG8            xor,ZL
MIAE:   ; xor (hl)
        LOG8            xor,[ebx+ebp]
MIAF:   ; xor a
        LOG8            xor,ZA

MIB0:   ; or b
        LOG8            or,ZB
MIB1:   ; or c
        LOG8            or,ZC
MIB2:   ; or d
        LOG8            or,ZD
MIB3:   ; or e
        LOG8            or,ZE
MIB4:   ; or h
        LOG8            or,ZH
MIB5:   ; or l
        LOG8            or,ZL
MIB6:   ; or (hl)
        LOG8            or,[ebx+ebp]
MIB7:   ; or a
        LOG8            or,ZA
MIB8:	; cp b
	CP8		ZB
MIB9:	; cp c
	CP8		ZC
MIBA:	; cp d
	CP8		ZD
MIBB:	; cp e
	CP8		ZE
MIBC:	; cp h
	CP8		ZH
MIBD:	; cp l
	CP8		ZL
MIBE:	; cp (hl)
	CP8		[ebx+ebp]
MIBF:	; cp a
	CP8		ZA

MIC0:	; ret nz
	RETcc		0,_ZZF

MIC1:	; pop	bc
	POP_R16		ZBC

MIC2:	; jp nz,nnnn
	JPcc		0,_ZZF

MIC3:	; jp nnnn
	mov		ZPC,[esi+ebp]
	Fetch

MIC4:	; call nz,nnnn
	CALLcc		0,_ZZF

MIC5:	; push bc
	PUSH_R16	ZBC

MIC6:	; add a,n
	inc		ZPC
	ADD8		[esi+ebp-1]

MIC7:	; rst 00
	RST		0x00

MIC8:	; ret z
	RETcc		1,_ZZF

MIC9:	; ret
	POP_R16		ZPC

MICA:	; jp z,nnnn
	JPcc		1,_ZZF

MICB:	; CB prefix
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [CBJMPtab+4*edi]

MICC:	; call z,nnnn
	CALLcc		1,_ZZF

MICD:	; call nnnn
        sub             ZSP,byte 2
        mov             di,ZSP
	add	        ZPC,byte 2
	WriteW	        edi,ZPC
	mov	        ZPC,[esi+ebp-2]
	Fetch

MICE:	; adc a,n
	inc	        ZPC
	ADC8	        [esi+ebp-1]

MICF:	; rst 08
	RST	        0x08

MID0:	; ret nc
	RETcc		0,_ZCF

MID1:	; pop	de
	POP_R16		ZDE

MID2:	; jp nc,nnnn
	JPcc		0,_ZCF

MID3:	; out (n),a
        push            ecx
        mov             cl,[esi+ebp]
        inc             ZPC
        mov             ch,ZA
        call            _ByteOut
        pop             ecx
	Fetch

MID4:	; call nc,nnnn
	CALLcc		0,_ZCF

MID5:	; push de
	PUSH_R16	ZDE

MID6:	; sub n
	inc		ZPC
	SUB8		[esi+ebp-1]

MID7:	; rst 10
	RST		0x10

MID8:	; ret c
	RETcc		1,_ZCF

MID9:	; exx
        xchg            ZBC,word [_Z_BC2]
        xchg            ZDE,word [_Z_DE2]
        xchg            ZHL,word [_Z_HL2]
        Fetch

MIDA:	; jp c,nnnn
	JPcc		1,_ZCF

MIDB:	; in a,(n)
        push            ecx
        mov             cl,[esi+ebp]
        inc             ZPC
        mov             ch,ZA
        call            _ByteIn
        pop             ecx
        Fetch

MIDC:	; call c,nnnn
	CALLcc		1,_ZCF

MIDD:	; DD prefix (IX)
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [DDJMPtab+4*edi]

MIDE:	; sbc a,n
	inc   	        ZPC
	SBC8	        [esi+ebp-1]

MIDF:	; rst 18
	RST	        0x18

MIE0:	; ret po
	RETcc		0,_ZPF

MIE1:	; pop hl
	POP_R16		ZHL

MIE2:	; jp po,nnnn
	JPcc		0,_ZPF

MIE3:	; ex (sp),hl
	push		eax
	mov		di,ZSP
	mov		ax,[edi+ebp]
	xchg		ax,ZHL
	WriteW		edi,ax
	pop		eax
	Fetch

MIE4:	; call po,nnnn
	CALLcc		0,_ZPF

MIE5:	; push hl
	PUSH_R16	ZHL

MIE6:	; and n
	inc   	        ZPC
	LOG8	        and,[esi+ebp-1]

MIE7:	; rst 20
	RST		0x20

MIE8:	; ret pe
	RETcc		1,_ZPF

MIE9:	; jp hl
	mov		ZPC,ZHL
	Fetch

MIEA:	; jp pe,nnnn
	JPcc		1,_ZPF

MIEB:	; ex		de,hl
	xchg		ZDE,ZHL
	Fetch

MIEC:	; call pe,nnnn
	CALLcc		1,_ZPF

MIED:	; ED prefix
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [EDJMPtab+4*edi]

MIEE:	; xor n
	inc   	        ZPC
	LOG8	        xor,[esi+ebp-1]

MIEF:	; rst 28
	RST		0x28

MIF0:	; ret p
	RETcc		0,_ZSF

MIF1:	; pop af
	POP_R16		ZAF	

MIF2:	; jp p,nnnn
	JPcc		0,_ZSF

MIF3:	; di
	mov		byte [_Z_IFF1],0
	mov		byte [_Z_IFF2],0
	Fetch

MIF4:	; call p,nnnn
	CALLcc		0,_ZSF

MIF5:	; push af
	PUSH_R16	ZAF

MIF6:	; or n
	inc   	        ZPC
	LOG8	        or,[esi+ebp-1]

MIF7:	; rst 30
	RST		0x30

MIF8:	; ret m
	RETcc		1,_ZSF

MIF9:	; ld sp,hl
	mov		ZSP,ZHL
	Fetch

MIFA:	; jp m,nnnn
	JPcc		1,_ZSF

MIFB:	; ei
	or		byte [_HWFlag],_fEIFlag
	mov		byte [EIctr],2
	Fetch

MIFC:	; call m,nnnn
	CALLcc		1,_ZSF

MIFD:	; FD prefix (IY)
	movzx	        edi,byte [esi+ebp]
	inc	        ZPC
	jmp	        dword [FDJMPtab+4*edi]

MIFE:	; cp n
	inc   	        ZPC
	CP8	        [esi+ebp-1]

MIFF:	; rst 38
	RST		0x38

%include "z80cb.asm"

%include "z80ed.asm"

%include "z80dd.asm"

%include "z80fd.asm"

%include "z80ddfdcb.asm"

