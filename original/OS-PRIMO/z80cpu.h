/*****************************************************************************

 JOCO's Z80 CPU emulator.
 z80cpu.h: header file for the variables/functions implemented in the
           z80main.o file (which is written in assembly language)

 Please contact joco@szabolcs.net in case you're not sure about the legal.

******************************************************************************/

#ifndef _Z80CPU_HEADER
#define _Z80CPU_HEADER

#ifndef _JOCOTYPES
#define _JOCOTYPES
/* my basic types... why C does not know them by default??? */
typedef unsigned char 		byte;
typedef unsigned short		word;
typedef unsigned int		dword;
#endif


#define _fIntFlag	0x01
#define _fNmiFlag	0x02
#define _fEIFlag	0x04
#define _fHaltFlag	0x08
#define	_fExtSub	0x20
#define	_fEscFlag	0x80

byte *Z80mem;		/* pointer for Z80 main mem 		*/
byte *Z80memSpec;	/* pointer for Z80 mem spec. array 	*/

/* %edi: address, %al: data. You must save/restore all registers! */
void SpecWriteByte();	/* write a special byte			*/
/* %edi: address, %ax: data. You must save/restore all registers! */
void SpecWriteWord();	/* write a special word 		*/
/* %ecx: port address. Put the return value into %al.
   You must save/restore all other registers. */
void ByteIn();		/* I/O in 				*/
/* %ecx: port address, %al: data to write to. 
   You must save/restore other registers. */
void ByteOut();		/* I/O out 				*/

/* You must save/restore all registers! */
void ExtSub();		/* external function 			*/

extern void Z80Reset();	/* CPU reset 				*/
extern void ExecOne();	/* Execute one Z80 instruction   	*/
extern void ExecICtr(); /* Execute Z_ICtr # instructions   	*/

/* Z80 Registers and hardware flags */			
extern dword Z_BC,Z_DE,Z_HL,Z_AF,Z_BC2,Z_DE2,Z_HL2,Z_AF2,Z_IX,Z_IY;
extern dword Z_SP,Z_PC,Z_ICtr;
extern byte  Z_IFF1,Z_IFF2,Z_IMOD,HWFlag,Z_I,Z_R,Z_IM2V;

#endif