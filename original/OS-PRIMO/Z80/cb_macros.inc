; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

;    7   6   5   4   3   2   1   0
; +---+---+---+---+---+---+---+---+
; | S | Z | - | H | - |P/V| N | C |
; +---+---+---+---+---+---+---+---+

b0 equ 1
b1 equ 2
b2 equ 4
b3 equ 8
b4 equ 16
b5 equ 32
b6 equ 64
b7 equ 128

%macro	RLC 1
     rol    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	RRC 1
     ror    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro 	RL 1
     sahf
     rcl    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	RR 1
     sahf
     rcr    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	SLA 1
     sal    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	SRA 1
     sar    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	SLL 1
     stc
     rcl    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	SRL 1
     shr    %1,1
     inc    %1
     dec    %1
     lahf
     Fetch
%endmacro

%macro	BIT 2
     test   %2,%1
     ror    ah,1
     lahf
     Fetch
%endmacro

%macro	RES 2
     and    %2,(0ffh-%1)
     Fetch
%endmacro

%macro	SET 2
     or     %2,%1
     Fetch
%endmacro

%macro	RESMEM 2
	test	byte [%2+ebp+65536+4],0xff
	jnz	short %%resmem_l0
	and	byte [%2+ebp],(0ffh-%1)
	Fetch
%%resmem_l0:
	SaveAL
	mov	al,byte [%2+ebp]
	and	al,(0ffh-%1)
  %ifnidn %2,edi
	mov	edi,%2
  %endif
	call	_SpecWriteByte
	LoadAL
	Fetch
%endmacro

%macro	SETMEM 2
	test	byte [%2+ebp+65536+4],0xff
	jnz	short %%setmem_l0
	or	byte [%2+ebp],%1
	Fetch
%%setmem_l0:
	SaveAL
	mov	al,byte [%2+ebp]
	or	al,%1
  %ifnidn %2,edi
	mov	edi,%2
  %endif
	call	_SpecWriteByte
	LoadAL
	Fetch
%endmacro

%macro  STORE_AL 1
	test	byte [%1+ebp+65536+4],0xff
	jnz	short %%store_l0
	mov	byte [%1+ebp],al
	LoadAL
	Fetch
%%store_l0:
  %ifnidn %1,edi
	mov	edi,%1
  %endif
	call	_SpecWriteByte
	LoadAL
	Fetch
%endmacro

%macro	RLCMEM 1
	SaveAL
	mov	al,[%1+ebp]
	rol	al,1
	inc	al
	dec	al
	lahf
	STORE_AL %1
%endmacro

%macro	RRCMEM 1
	SaveAL
	mov	al,[%1+ebp]
	ror	al,1
	inc	al
	dec	al
	lahf
	STORE_AL %1
%endmacro

%macro 	RLMEM 1
    	SaveAL
	mov	al,[%1+ebp]
     	sahf
     	rcl    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_AL %1
%endmacro

%macro	RRMEM 1
	SaveAL
	mov	al,[%1+ebp]
     	sahf
     	rcr    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_AL %1
%endmacro

%macro	SLAMEM 1
	SaveAL
	mov	al,[%1+ebp]
     	sal    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_AL %1
%endmacro

%macro	SRAMEM 1
	SaveAL
	mov	al,[%1+ebp]
     	sar    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_AL %1
%endmacro

%macro	SLLMEM 1
	SaveAL
	mov	al,[%1+ebp]
     	stc
     	rcl    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_AL %1
%endmacro

%macro	SRLMEM 1
	SaveAL
	mov	al,[%1+ebp]
     	shr    al,1
     	inc    al
    	dec    al
     	lahf
     	STORE_AL %1
%endmacro
