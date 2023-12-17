; *****************************************************************************
; **
; ** Z80 CPU emulator by Jozsef Laszlo. See the read.me file 
; **
; *****************************************************************************

%include "cb_macros.inc"

; ---     rlc  b
ICB00:
        RLC     ZB

; ---     rlc  c
ICB01:
        RLC     ZC

; ---     rlc  d
ICB02:
        RLC     ZD

; ---     rlc  e
ICB03:
        RLC     ZE

; ---     rlc  h
ICB04:
        RLC     bh

; --- 	      rlc  l
ICB05:
        RLC     bl

; ---     rlc  (hl)
ICB06:
	RLCMEM	ZHLL

; ---     rlc  a
ICB07:
       	RLC     al


; ---     rrc  b
ICB08:
        RRC     ZB

; ---     rrc  c
ICB09:
        RRC     ZC

; ---     rrc  d
ICB0A:
        RRC     ZD

; ---     rrc  e
ICB0B:
        RRC     ZE

; ---     rrc  h
ICB0C:
        RRC     bh

; ---     rrc  l
ICB0D:
        RRC     bl

; ---     rrc  (hl)
ICB0E:
	RRCMEM	ZHLL

; ---     rrc  a
ICB0F:
        RRC     al


; ---     rl  b
ICB10:
        RL      ZB

; ---     rl  c
ICB11:
        RL      ZC

; ---     rl  d
ICB12:
        RL      ZD

; ---     rl  e
ICB13:
        RL      ZE

; ---     rl  h
ICB14:
        RL      bh

; ---     rl  l
ICB15:
        RL      bl

; ---     rl  (hl)
ICB16:          
	RLMEM	ZHLL

; ---     rl  a
ICB17:
        RL      al


; ---     rr  b
ICB18:
        RR      ZB

; ---     rr  c
ICB19:
        RR      ZC

; ---     rr  d
ICB1A:
        RR      ZD

; ---     rr  e
ICB1B:
        RR      ZE

; ---     rr  h
ICB1C:
        RR      bh

; ---     rr  l
ICB1D:
        RR      bl

; ---     rr  (hl)
ICB1E:
	RRMEM	ZHLL

; ---     rr  a
ICB1F:
        RR      al

; ---     sla  b
ICB20:
        SLA      ZB

; ---     sla  c
ICB21:
        SLA      ZC

; ---     sla  d
ICB22:
        SLA      ZD

; ---     sla  e
ICB23:
        SLA      ZE

; ---     sla  h
ICB24:
        SLA      bh

; ---     sla  l
ICB25:
        SLA      bl

; ---     sla  (hl)
ICB26:
	SLAMEM	ZHLL

; ---     sla  a
ICB27:
        SLA      al


; ---     sra  b
ICB28:
        SRA      ZB

; ---     sra  c
ICB29:
        SRA      ZC

; ---     sra  d
ICB2A:
        SRA      ZD

; ---     sra  e
ICB2B:
        SRA      ZE

; ---     sra  h
ICB2C:
        SRA      bh

; ---     sra  l
ICB2D:
        SRA      bl

; ---     sra  (hl)
ICB2E:
	SRAMEM	ZHLL

; ---     sra  a
ICB2F:
        SRA      al


; ---     sll  b
ICB30:
        SLL      ZB

; ---     sll  c
ICB31:
        SLL      ZC

; ---     sll  d
ICB32:
        SLL      ZD

; ---     sll  e
ICB33:
        SLL      ZE

; ---     sll  h
ICB34:
        SLL      bh

; ---     sll  l
ICB35:
        SLL      bl

; ---     sll  (hl)
ICB36:
	SLLMEM	ZHLL

; ---     sll  a
ICB37:
        SLL      al


; ---     srl  b
ICB38:
        SRL      ZB

; ---     srl  c
ICB39:
        SRL      ZC

; ---     srl  d
ICB3A:
        SRL      ZD

; ---     srl  e
ICB3B:
        SRL      ZE

; ---     srl  h
ICB3C:
        SRL      bh

; ---     srl  l
ICB3D:
        SRL      bl

; ---     srl  (hl)
ICB3E:
	SRLMEM	ZHLL

; ---     srl  a
ICB3F:
        SRL      al


ICB40:	; bit 0,b
	BIT	b0,ZB
ICB41:	; bit 0,c
	BIT	b0,ZC
ICB42:	; bit 0,d
	BIT	b0,ZD
ICB43:	; bit 0,e
	BIT	b0,ZE
ICB44:	; bit 0,h
	BIT	b0,ZH
ICB45:	; bit 0,l
	BIT	b0,ZL
ICB46:	; bit 0,(hl)
	BIT	b0,byte [ZHLL+ebp]
ICB47:	; bit 0,a
	BIT	b0,ZA
ICB48:	; bit 1,b
	BIT	b1,ZB
ICB49:	; bit 1,c
	BIT	b1,ZC
ICB4A:	; bit 1,d
	BIT	b1,ZD
ICB4B:	; bit 1,e
	BIT	b1,ZE
ICB4C:	; bit 1,h
	BIT	b1,ZH
ICB4D:	; bit 1,l
	BIT	b1,ZL
ICB4E:	; bit 1,(hl)
	BIT	b1,byte [ZHLL+ebp]
ICB4F:	; bit 1,a
	BIT	b1,ZA

ICB50:	; bit 2,b
	BIT	b2,ZB
ICB51:	; bit 2,c
	BIT	b2,ZC
ICB52:	; bit 2,d
	BIT	b2,ZD
ICB53:	; bit 2,e
	BIT	b2,ZE
ICB54:	; bit 2,h
	BIT	b2,ZH
ICB55:	; bit 2,l
	BIT	b2,ZL
ICB56:	; bit 2,(hl)
	BIT	b2,byte [ZHLL+ebp]
ICB57:	; bit 2,a
	BIT	b2,ZA
ICB58:	; bit 3,b
	BIT	b3,ZB
ICB59:	; bit 3,c
	BIT	b3,ZC
ICB5A:	; bit 3,d
	BIT	b3,ZD
ICB5B:	; bit 3,e
	BIT	b3,ZE
ICB5C:	; bit 3,h
	BIT	b3,ZH
ICB5D:	; bit 3,l
	BIT	b3,ZL
ICB5E:	; bit 3,(hl)
	BIT	b3,byte [ZHLL+ebp]
ICB5F:	; bit 3,a
	BIT	b3,ZA

ICB60:	; bit 4,b
	BIT	b4,ZB
ICB61:	; bit 4,c
	BIT	b4,ZC
ICB62:	; bit 4,d
	BIT	b4,ZD
ICB63:	; bit 4,e
	BIT	b4,ZE
ICB64:	; bit 4,h
	BIT	b4,ZH
ICB65:	; bit 4,l
	BIT	b4,ZL
ICB66:	; bit 4,(hl)
	BIT	b4,byte [ZHLL+ebp]
ICB67:	; bit 4,a
	BIT	b4,ZA
ICB68:	; bit 5,b
	BIT	b5,ZB
ICB69:	; bit 5,c
	BIT	b5,ZC
ICB6A:	; bit 5,d
	BIT	b5,ZD
ICB6B:	; bit 5,e
	BIT	b5,ZE
ICB6C:	; bit 5,h
	BIT	b5,ZH
ICB6D:	; bit 5,l
	BIT	b5,ZL
ICB6E:	; bit 5,(hl)
	BIT	b5,byte [ZHLL+ebp]
ICB6F:	; bit 5,a
	BIT	b5,ZA

ICB70:	; bit 6,b
	BIT	b6,ZB
ICB71:	; bit 6,c
	BIT	b6,ZC
ICB72:	; bit 6,d
	BIT	b6,ZD
ICB73:	; bit 6,e
	BIT	b6,ZE
ICB74:	; bit 6,h
	BIT	b6,ZH
ICB75:	; bit 6,l
	BIT	b6,ZL
ICB76:	; bit 6,(hl)
	BIT	b6,byte [ZHLL+ebp]
ICB77:	; bit 6,a
	BIT	b6,ZA
ICB78:	; bit 7,b
	BIT	b7,ZB
ICB79:	; bit 7,c
	BIT	b7,ZC
ICB7A:	; bit 7,d
	BIT	b7,ZD
ICB7B:	; bit 7,e
	BIT	b7,ZE
ICB7C:	; bit 7,h
	BIT	b7,ZH
ICB7D:	; bit 7,l
	BIT	b7,ZL
ICB7E:	; bit 7,(hl)
	BIT	b7,byte [ZHLL+ebp]
ICB7F:	; bit 7,a
	BIT	b7,ZA

ICB80:	; res 0,b
	RES	b0,ZB
ICB81:	; res 0,c
	RES	b0,ZC
ICB82:	; res 0,d
	RES	b0,ZD
ICB83:	; res 0,e
	RES	b0,ZE
ICB84:	; res 0,h
	RES	b0,ZH
ICB85:	; res 0,l
	RES	b0,ZL
ICB86:	; res 0,(hl)
	RESMEM	b0,ZHLL
ICB87:	; res 0,a
	RES	b0,ZA
ICB88:	; res 1,b
	RES	b1,ZB
ICB89:	; res 1,c
	RES	b1,ZC
ICB8A:	; res 1,d
	RES	b1,ZD
ICB8B:	; res 1,e
	RES	b1,ZE
ICB8C:	; res 1,h
	RES	b1,ZH
ICB8D:	; res 1,l
	RES	b1,ZL
ICB8E:	; res 1,(hl)
	RESMEM	b1,ZHLL
ICB8F:	; res 1,a
	RES	b1,ZA

ICB90:	; res 2,b
	RES	b2,ZB
ICB91:	; res 2,c
	RES	b2,ZC
ICB92:	; res 2,d
	RES	b2,ZD
ICB93:	; res 2,e
	RES	b2,ZE
ICB94:	; res 2,h
	RES	b2,ZH
ICB95:	; res 2,l
	RES	b2,ZL
ICB96:	; res 2,(hl)
	RESMEM	b2,ZHLL
ICB97:	; res 2,a
	RES	b2,ZA
ICB98:	; res 3,b
	RES	b3,ZB
ICB99:	; res 3,c
	RES	b3,ZC
ICB9A:	; res 3,d
	RES	b3,ZD
ICB9B:	; res 3,e
	RES	b3,ZE
ICB9C:	; res 3,h
	RES	b3,ZH
ICB9D:	; res 3,l
	RES	b3,ZL
ICB9E:	; res 3,(hl)
	RESMEM	b3,ZHLL
ICB9F:	; res 3,a
	RES	b3,ZA

ICBA0:	; res 4,b
	RES	b4,ZB
ICBA1:	; res 4,c
	RES	b4,ZC
ICBA2:	; res 4,d
	RES	b4,ZD
ICBA3:	; res 4,e
	RES	b4,ZE
ICBA4:	; res 4,h
	RES	b4,ZH
ICBA5:	; res 4,l
	RES	b4,ZL
ICBA6:	; res 4,(hl)
	RESMEM	b4,ZHLL
ICBA7:	; res 4,a
	RES	b4,ZA
ICBA8:	; res 5,b
	RES	b5,ZB
ICBA9:	; res 5,c
	RES	b5,ZC
ICBAA:	; res 5,d
	RES	b5,ZD
ICBAB:	; res 5,e
	RES	b5,ZE
ICBAC:	; res 5,h
	RES	b5,ZH
ICBAD:	; res 5,l
	RES	b5,ZL
ICBAE:	; res 5,(hl)
	RESMEM	b5,ZHLL
ICBAF:	; res 5,a
	RES	b5,ZA

ICBB0:	; res 6,b
	RES	b6,ZB
ICBB1:	; res 6,c
	RES	b6,ZC
ICBB2:	; res 6,d
	RES	b6,ZD
ICBB3:	; res 6,e
	RES	b6,ZE
ICBB4:	; res 6,h
	RES	b6,ZH
ICBB5:	; res 6,l
	RES	b6,ZL
ICBB6:	; res 6,(hl)
	RESMEM	b6,ZHLL
ICBB7:	; res 6,a
	RES	b6,ZA
ICBB8:	; res 7,b
	RES	b7,ZB
ICBB9:	; res 7,c
	RES	b7,ZC
ICBBA:	; res 7,d
	RES	b7,ZD
ICBBB:	; res 7,e
	RES	b7,ZE
ICBBC:	; res 7,h
	RES	b7,ZH
ICBBD:	; res 7,l
	RES	b7,ZL
ICBBE:	; res 7,(hl)
	RESMEM	b7,ZHLL
ICBBF:	; res 7,a
	RES	b7,ZA


ICBC0:	; set 0,b
	SET	b0,ZB
ICBC1:	; set 0,c
	SET	b0,ZC
ICBC2:	; set 0,d
	SET	b0,ZD
ICBC3:	; set 0,e
	SET	b0,ZE
ICBC4:	; set 0,h
	SET	b0,ZH
ICBC5:	; set 0,l
	SET	b0,ZL
ICBC6:	; set 0,(hl)
	SETMEM	b0,ZHLL
ICBC7:	; set 0,a
	SET	b0,ZA
ICBC8:	; set 1,b
	SET	b1,ZB
ICBC9:	; set 1,c
	SET	b1,ZC
ICBCA:	; set 1,d
	SET	b1,ZD
ICBCB:	; set 1,e
	SET	b1,ZE
ICBCC:	; set 1,h
	SET	b1,ZH
ICBCD:	; set 1,l
	SET	b1,ZL
ICBCE:	; set 1,(hl)
	SETMEM	b1,ZHLL
ICBCF:	; set 1,a
	SET	b1,ZA

ICBD0:	; set 2,b
	SET	b2,ZB
ICBD1:	; set 2,c
	SET	b2,ZC
ICBD2:	; set 2,d
	SET	b2,ZD
ICBD3:	; set 2,e
	SET	b2,ZE
ICBD4:	; set 2,h
	SET	b2,ZH
ICBD5:	; set 2,l
	SET	b2,ZL
ICBD6:	; set 2,(hl)
	SETMEM	b2,ZHLL
ICBD7:	; set 2,a
	SET	b2,ZA
ICBD8:	; set 3,b
	SET	b3,ZB
ICBD9:	; set 3,c
	SET	b3,ZC
ICBDA:	; set 3,d
	SET	b3,ZD
ICBDB:	; set 3,e
	SET	b3,ZE
ICBDC:	; set 3,h
	SET	b3,ZH
ICBDD:	; set 3,l
	SET	b3,ZL
ICBDE:	; set 3,(hl)
	SETMEM	b3,ZHLL
ICBDF:	; set 3,a
	SET	b3,ZA

ICBE0:	; set 4,b
	SET	b4,ZB
ICBE1:	; set 4,c
	SET	b4,ZC
ICBE2:	; set 4,d
	SET	b4,ZD
ICBE3:	; set 4,e
	SET	b4,ZE
ICBE4:	; set 4,h
	SET	b4,ZH
ICBE5:	; set 4,l
	SET	b4,ZL
ICBE6:	; set 4,(hl)
	SETMEM	b4,ZHLL
ICBE7:	; set 4,a
	SET	b4,ZA
ICBE8:	; set 5,b
	SET	b5,ZB
ICBE9:	; set 5,c
	SET	b5,ZC
ICBEA:	; set 5,d
	SET	b5,ZD
ICBEB:	; set 5,e
	SET	b5,ZE
ICBEC:	; set 5,h
	SET	b5,ZH
ICBED:	; set 5,l
	SET	b5,ZL
ICBEE:	; set 5,(hl)
	SETMEM	b5,ZHLL
ICBEF:	; set 5,a
	SET	b5,ZA

ICBF0:	; set 6,b
	SET	b6,ZB
ICBF1:	; set 6,c
	SET	b6,ZC
ICBF2:	; set 6,d
	SET	b6,ZD
ICBF3:	; set 6,e
	SET	b6,ZE
ICBF4:	; set 6,h
	SET	b6,ZH
ICBF5:	; set 6,l
	SET	b6,ZL
ICBF6:	; set 6,(hl)
	SETMEM	b6,ZHLL
ICBF7:	; set 6,a
	SET	b6,ZA
ICBF8:	; set 7,b
	SET	b7,ZB
ICBF9:	; set 7,c
	SET	b7,ZC
ICBFA:	; set 7,d
	SET	b7,ZD
ICBFB:	; set 7,e
	SET	b7,ZE
ICBFC:	; set 7,h
	SET	b7,ZH
ICBFD:	; set 7,l
	SET	b7,ZL
ICBFE:	; set 7,(hl)
	SETMEM	b7,ZHLL
ICBFF:	; set 7,a
	SET	b7,ZA

