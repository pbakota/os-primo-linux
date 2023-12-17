; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%macro	RESXY 2
	pop	edi
	test	byte [edi+ebp+65536+4],0xff
	jnz	short %%resmem_l0
	and	byte [edi+ebp],(0ffh-%1)
  %ifnidn %2,_
	mov	%2,byte [edi+ebp]
  %endif
	Fetch
%%resmem_l0:
	SaveAL
	mov	al,byte [edi+ebp]
	and	al,(0ffh-%1)
	call	_SpecWriteByte
	LoadAL
  %ifnidn %2,_
	mov	%2,byte [edi+ebp]
  %endif
	Fetch
%endmacro

%macro	SETXY 2
	pop	edi
	test	byte [edi+ebp+65536+4],0xff
	jnz	short %%setmem_l0
	or	byte [edi+ebp],%1
  %ifnidn %2,_
	mov	%2,byte [edi+ebp]
  %endif
	Fetch
%%setmem_l0:
	SaveAL
	mov	al,byte [edi+ebp]
	or	al,%1
	call	_SpecWriteByte
	LoadAL
  %ifnidn %2,_
	mov	%2,byte [edi+ebp]
  %endif
	Fetch
%endmacro

%macro  STORE_XY 1
	test	byte [edi+ebp+65536+4],0xff
	jnz	short %%store_l0
	mov	byte [edi+ebp],al
%%ends:
	LoadAL
  %ifnidn %1,_
	mov	%1,byte [edi+ebp]
  %endif
	Fetch
%%store_l0:
	call	_SpecWriteByte
	jmp	short %%ends
%endmacro

%macro	RLCXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
	rol	al,1
	inc	al
	dec	al
	lahf
	STORE_XY %1
%endmacro

%macro	RRCXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
	ror	al,1
	inc	al
	dec	al
	lahf
	STORE_XY %1
%endmacro

%macro 	RLXY 1
	pop	edi
    	SaveAL
	mov	al,[edi+ebp]
     	sahf
     	rcl    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_XY %1
%endmacro

%macro	RRXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
     	sahf
     	rcr    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_XY %1
%endmacro

%macro	SLAXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
     	sal    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_XY %1
%endmacro

%macro	SRAXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
     	sar    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_XY %1
%endmacro

%macro	SLLXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
     	stc
     	rcl    al,1
     	inc    al
     	dec    al
     	lahf
     	STORE_XY %1
%endmacro

%macro	SRLXY 1
	pop	edi
	SaveAL
	mov	al,[edi+ebp]
     	shr    al,1
     	inc    al
    	dec    al
     	lahf
     	STORE_XY %1
%endmacro

IXY00:	RLCXY	ZB
IXY01:	RLCXY	ZC
IXY02:	RLCXY	ZD
IXY03:	RLCXY	ZE
IXY04:	RLCXY	ZH
IXY05:	RLCXY	ZL
IXY06:	RLCXY	_
IXY07:	RLCXY	ZA

IXY08:	RRCXY	ZB
IXY09:	RRCXY	ZC
IXY0A:	RRCXY	ZD
IXY0B:	RRCXY	ZE
IXY0C:	RRCXY	ZH
IXY0D:	RRCXY	ZL
IXY0E:	RRCXY	_
IXY0F:	RRCXY	ZA

IXY10:	RLXY	ZB
IXY11:	RLXY	ZC
IXY12:	RLXY	ZD
IXY13:	RLXY	ZE
IXY14:	RLXY	ZH
IXY15:	RLXY	ZL
IXY16:	RLXY	_
IXY17:	RLXY	ZA

IXY18:	RRXY	ZB
IXY19:	RRXY	ZC
IXY1A:	RRXY	ZD
IXY1B:	RRXY	ZE
IXY1C:	RRXY	ZH
IXY1D:	RRXY	ZL
IXY1E:	RRXY	_
IXY1F:	RRXY	ZA

IXY20:	SLAXY	ZB
IXY21:	SLAXY	ZC
IXY22:	SLAXY	ZD
IXY23:	SLAXY	ZE
IXY24:	SLAXY	ZH
IXY25:	SLAXY	ZL
IXY26:	SLAXY	_
IXY27:	SLAXY	ZA

IXY28:	SRAXY	ZB
IXY29:	SRAXY	ZC
IXY2A:	SRAXY	ZD
IXY2B:	SRAXY	ZE
IXY2C:	SRAXY	ZH
IXY2D:	SRAXY	ZL
IXY2E:	SRAXY	_
IXY2F:	SRAXY	ZA

IXY30:	SLLXY	ZB
IXY31:	SLLXY	ZC
IXY32:	SLLXY	ZD
IXY33:	SLLXY	ZE
IXY34:	SLLXY	ZH
IXY35:	SLLXY	ZL
IXY36:	SLLXY	_
IXY37:	SLLXY	ZA

IXY38:	SRLXY	ZB
IXY39:	SRLXY	ZC
IXY3A:	SRLXY	ZD
IXY3B:	SRLXY	ZE
IXY3C:	SRLXY	ZH
IXY3D:	SRLXY	ZL
IXY3E:	SRLXY	_
IXY3F:	SRLXY	ZA

IXY40:
IXY41:
IXY42:
IXY43:
IXY44:
IXY45:
IXY46:
IXY47:	pop	edi
	BIT	b0,byte [edi+ebp]

IXY48:
IXY49:
IXY4A:
IXY4B:
IXY4C:
IXY4D:
IXY4E:
IXY4F:	pop	edi
	BIT	b1,byte [edi+ebp]

IXY50:
IXY51:
IXY52:
IXY53:
IXY54:
IXY55:
IXY56:
IXY57:	pop	edi
	BIT	b2,byte [edi+ebp]

IXY58:
IXY59:
IXY5A:
IXY5B:
IXY5C:
IXY5D:
IXY5E:
IXY5F:	pop	edi
	BIT	b3,byte [edi+ebp]

IXY60:
IXY61:
IXY62:
IXY63:
IXY64:
IXY65:
IXY66:
IXY67:	pop	edi
	BIT	b4,byte [edi+ebp]

IXY68:
IXY69:
IXY6A:
IXY6B:
IXY6C:
IXY6D:
IXY6E:
IXY6F:	pop	edi
	BIT	b5,byte [edi+ebp]

IXY70:
IXY71:
IXY72:
IXY73:
IXY74:
IXY75:
IXY76:
IXY77:	pop	edi
	BIT	b6,byte [edi+ebp]

IXY78:
IXY79:
IXY7A:
IXY7B:
IXY7C:
IXY7D:
IXY7E:
IXY7F:	pop	edi
	BIT	b7,byte [edi+ebp]

IXY80:	RESXY	b0,ZB
IXY81:	RESXY	b0,ZC
IXY82:	RESXY	b0,ZD
IXY83:	RESXY	b0,ZE
IXY84:	RESXY	b0,ZH
IXY85:	RESXY	b0,ZL
IXY86:	RESXY	b0,_
IXY87:	RESXY	b0,ZA
IXY88:	RESXY	b1,ZB
IXY89:	RESXY	b1,ZC
IXY8A:	RESXY	b1,ZD
IXY8B:	RESXY	b1,ZE
IXY8C:	RESXY	b1,ZH
IXY8D:	RESXY	b1,ZL
IXY8E:	RESXY	b1,_
IXY8F:	RESXY	b1,ZA

IXY90:	RESXY	b2,ZB
IXY91:	RESXY	b2,ZC
IXY92:	RESXY	b2,ZD
IXY93:	RESXY	b2,ZE
IXY94:	RESXY	b2,ZH
IXY95:	RESXY	b2,ZL
IXY96:	RESXY	b2,_
IXY97:	RESXY	b2,ZA
IXY98:	RESXY	b3,ZB
IXY99:	RESXY	b3,ZC
IXY9A:	RESXY	b3,ZD
IXY9B:	RESXY	b3,ZE
IXY9C:	RESXY	b3,ZH
IXY9D:	RESXY	b3,ZL
IXY9E:	RESXY	b3,_
IXY9F:	RESXY	b3,ZA

IXYA0:	RESXY	b4,ZB
IXYA1:	RESXY	b4,ZC
IXYA2:	RESXY	b4,ZD
IXYA3:	RESXY	b4,ZE
IXYA4:	RESXY	b4,ZH
IXYA5:	RESXY	b4,ZL
IXYA6:	RESXY	b4,_
IXYA7:	RESXY	b4,ZA
IXYA8:	RESXY	b5,ZB
IXYA9:	RESXY	b5,ZC
IXYAA:	RESXY	b5,ZD
IXYAB:	RESXY	b5,ZE
IXYAC:	RESXY	b5,ZH
IXYAD:	RESXY	b5,ZL
IXYAE:	RESXY	b5,_
IXYAF:	RESXY	b5,ZA

IXYB0:	RESXY	b6,ZB
IXYB1:	RESXY	b6,ZC
IXYB2:	RESXY	b6,ZD
IXYB3:	RESXY	b6,ZE
IXYB4:	RESXY	b6,ZH
IXYB5:	RESXY	b6,ZL
IXYB6:	RESXY	b6,_
IXYB7:	RESXY	b6,ZA
IXYB8:	RESXY	b7,ZB
IXYB9:	RESXY	b7,ZC
IXYBA:	RESXY	b7,ZD
IXYBB:	RESXY	b7,ZE
IXYBC:	RESXY	b7,ZH
IXYBD:	RESXY	b7,ZL
IXYBE:	RESXY	b7,_
IXYBF:	RESXY	b7,ZA

IXYC0:  SETXY   b0,ZB
IXYC1:  SETXY   b0,ZC
IXYC2:  SETXY   b0,ZD
IXYC3:  SETXY   b0,ZE
IXYC4:  SETXY   b0,ZH
IXYC5:  SETXY   b0,ZL
IXYC6:  SETXY   b0,_
IXYC7:  SETXY   b0,ZA
IXYC8:  SETXY   b1,ZB
IXYC9:  SETXY   b1,ZC
IXYCA:  SETXY   b1,ZD
IXYCB:  SETXY   b1,ZE
IXYCC:  SETXY   b1,ZH
IXYCD:  SETXY   b1,ZL
IXYCE:  SETXY   b1,_
IXYCF:  SETXY   b1,ZA

IXYD0:  SETXY   b2,ZB
IXYD1:  SETXY   b2,ZC
IXYD2:  SETXY   b2,ZD
IXYD3:  SETXY   b2,ZE
IXYD4:  SETXY   b2,ZH
IXYD5:  SETXY   b2,ZL
IXYD6:  SETXY   b2,_
IXYD7:  SETXY   b2,ZA
IXYD8:  SETXY   b3,ZB
IXYD9:  SETXY   b3,ZC
IXYDA:  SETXY   b3,ZD
IXYDB:  SETXY   b3,ZE
IXYDC:  SETXY   b3,ZH
IXYDD:  SETXY   b3,ZL
IXYDE:  SETXY   b3,_
IXYDF:  SETXY   b3,ZA

IXYE0:  SETXY   b4,ZB
IXYE1:  SETXY   b4,ZC
IXYE2:  SETXY   b4,ZD
IXYE3:  SETXY   b4,ZE
IXYE4:  SETXY   b4,ZH
IXYE5:  SETXY   b4,ZL
IXYE6:  SETXY   b4,_
IXYE7:  SETXY   b4,ZA
IXYE8:  SETXY   b5,ZB
IXYE9:  SETXY   b5,ZC
IXYEA:  SETXY   b5,ZD
IXYEB:  SETXY   b5,ZE
IXYEC:  SETXY   b5,ZH
IXYED:  SETXY   b5,ZL
IXYEE:  SETXY   b5,_
IXYEF:  SETXY   b5,ZA

IXYF0:  SETXY   b6,ZB
IXYF1:  SETXY   b6,ZC
IXYF2:  SETXY   b6,ZD
IXYF3:  SETXY   b6,ZE
IXYF4:  SETXY   b6,ZH
IXYF5:  SETXY   b6,ZL
IXYF6:  SETXY   b6,_
IXYF7:  SETXY   b6,ZA
IXYF8:  SETXY   b7,ZB
IXYF9:  SETXY   b7,ZC
IXYFA:  SETXY   b7,ZD
IXYFB:  SETXY   b7,ZE
IXYFC:  SETXY   b7,ZH
IXYFD:  SETXY   b7,ZL
IXYFE:  SETXY   b7,_
IXYFF:  SETXY   b7,ZA
