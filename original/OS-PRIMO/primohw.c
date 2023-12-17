/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net

 Please read the read.me for the details.
******************************************************************************/

#include <stdio.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>

#include "z80cpu.h"
#include "keytab.h"

word DescA000;		/* Descriptor for the video segment   */
int  SAddrTab[6144];	/* PRIMO/PC screen address conversion */
byte PCKBD[256];	/* PC scancode table for keyboard ISR */
byte KI1,KI2,KI3,KI4;   /* PRIMO out ports, only KI1 used now */
byte BE1,BE2,BE3,BE4;   /* PRIMO in ports, onlz BE1 used now  */

/* primo double pixels' bitmap. We use 640x200x16 graph mode,
   and doubling each pixel. This table contains the wide pixels 
   for a nybble (0x00..0x0F) */
byte gfbits[]={	0x00,0x03,0x0c,0x0f,
		0x30,0x33,0x3c,0x3f,
		0xc0,0xc3,0xcc,0xcf,
		0xf0,0xf3,0xfc,0xff};

/* here we'll store the PRIMO screen bytes. See xxxSput()s below */
int gfxb[256];


/* Calling BIOS function INT 10h to set a videomode */
void vga_mode(int mode_nr) {
 __dpmi_regs 	r;
  
 r.d.eax=mode_nr&0x7f;
 __dpmi_int(0x10,&r);
}


/* Assign a VGA palette register to a legacy EGA palette register */
void setEGApal(int reg, int data) {
 int i;

 i=inportb(0x3da);
 outportb(0x3c0,reg&0x0f);
 outportb(0x3c0,data&0xff);
 outportb(0x3c0,0x20);
}

/* Define a VGA color with R-G-B components */
void setVGApal(int reg,int R,int G,int B) {
 outportb(0x3c8,reg);
 outportb(0x3c9,R);
 outportb(0x3c9,G);
 outportb(0x3c9,B);
}

/* Clear the video memory 0xA0000(64K) */
void ClearVideoArea() {
 __asm __volatile__("
	push	%ES
	pushal
	movw	_DescA000,%ES
	cld
	xorl	%edi,%edi
	xorl	%eax,%eax
	movl	$16384,%ecx	/* 4*16K = 64K ! */
	rep	
	stosl
	popal
	pop	%ES
 ");	
}

/* A high-speed routine to show one PRIMO screen byte on the 
   PC screen. Called by the CPU emulator (SpecWriteByte). */
void PriSput(int Addr, int Data) {
 __asm __volatile__("
	push	%%ES
	movw	_DescA000,%%ES
	movl	%0,%%ebx

	subl	$0xe800,%%ebx			/* %%ebx: absoulte address */
	movl	_SAddrTab(,%%ebx,4),%%ebx	/* real PC screen position */

	movl	%1,%%eax
	movl	_gfxb(,%%eax,4),%%eax		/* get the wide pixels     */

	movw	%%ax,%%ES:(%%ebx)

	pop	%%ES
 "
 :
 : "g" (Addr), "g" (Data)
 : "%eax","%ebx");
}

/* A high-speed routine to show one PRIMO screen byte on the 
   PC screen. Called by the CPU emulator (SpecWriteByte). */
void SecSput(int Addr, int Data) {
 __asm __volatile__("
	push	%%ES
	movw	_DescA000,%%ES
	movl	%0,%%ebx

	subl	$0xc800,%%ebx			/* %%ebx: absoulte address */
	movl	_SAddrTab(,%%ebx,4),%%ebx	/* real PC screen position */
	addl	$16000,%%ebx			/* second screen */

	movl	%1,%%eax
	movl	_gfxb(,%%eax,4),%%eax		/* get the wide pixels     */

	movw	%%ax,%%ES:(%%ebx)

	pop	%%ES
 "
 :
 : "g" (Addr), "g" (Data)
 : "%eax","%ebx");
}

/* Calculate the screen positions for the primo screenbytes */
void CalcScrnAddr() {
int i,j,k,l,m,w;

 m=0;
 for(i=0;i<192;i++) 
  for(j=0;j<32;j++) {
   SAddrTab[m]=4*80+8+j*2+i*80; m++;
  }
    
}

void PrimoScreen() {
 int i;

 vga_mode(0x0e);  /* 640x200/16c graph screen */
 CalcScrnAddr();
 ClearVideoArea();
 /* make the 256 possible screenbyte combinations */
 for(i=0;i<256;i++) gfxb[i]=(gfbits[i&15]<<8)|gfbits[i>>4];

 for(i=0;i<16;i++) setEGApal(i,i);
 setVGApal(15,30,35,63);	/* a nice blue color :-) */
}

void PcScreen() {
 vga_mode(0x03);   /* 80x25/16c text screen */
}


/* Timer ISR function. Sets the NMI bit in the CPU emulator's sysflag. 
  It's a 50IRQs/sec period here! */
void my_timer_isr(void) {
 if (KI1&0x80) HWFlag|=_fNmiFlag;
}

/* Timer ISR installer/deinstaller: see DJGPP docs for more info.
   Protected mode sucks. */

 _go32_dpmi_seginfo OldINT_1C,NewINT_1C;

void InstallTimerISR() {
  outportb(0x43,0xb6);		/* timer reset */
  outportb(0x43,0);
  outportb(0x43,0);

  outportb(0x43,0x36);		/* timer set to 50irqs/sec */
  outportb(0x40,23684&255);
  outportb(0x40,23684>>8);
  /* protected mode stuff comes */
  NewINT_1C.pm_offset =(int)my_timer_isr;
  NewINT_1C.pm_selector=_go32_my_cs();
  _go32_dpmi_get_protected_mode_interrupt_vector(0x1c,&OldINT_1C);
  _go32_dpmi_allocate_iret_wrapper(&NewINT_1C);
  _go32_dpmi_set_protected_mode_interrupt_vector(0x1c,&NewINT_1C);
}

void UninstallTimerISR() {
  outportb(0x43,0x36);		/* timer reset */
  outportb(0x40,0x00);
  outportb(0x40,0x00);
  /* protected mode stuff comes */
  _go32_dpmi_set_protected_mode_interrupt_vector(0x1c,&OldINT_1C);
  _go32_dpmi_free_iret_wrapper(&NewINT_1C);
}


int xkey = 0 ;

/* Keyboard ISR. We got the keyboard state from the hardware, and here
   we update the primokey[] table */
void my_keyboard_isr() {

 unsigned char b,d,t;
 word c;

 b=inportb(0x60);		/* scan-code */
 if (b==0xe0) {
  xkey=128;             	/* extended scan code */
 } else {
  d = xkey+(b&0x7f);
  t = (b>>7)^1;
  PCKBD[d]=t;			/* press/release state */
  xkey=0;
  c=keyconvtable[d];		/* primo keydata */
  primokey[c&255]=t;
  if (!(c&0x8000)) primokey[0x03]=t;  /* primo shift   */
  if (!(c&0x4000)) primokey[0x07]=t;  /* primo control */
 }

 /* end of IRQ, hardware stuff */
 b=inportb(0x61);
 outportb(0x61,b|0x80);
 outportb(0x61,b);
 outportb(0x20,0x20);
}


/* Keyboard ISR installer/deinstaller: see DJGPP docs for more info.
   Protected mode sucks. */

_go32_dpmi_seginfo OldINT_09,NewINT_09;

void InstallKeyboardISR() {

  memset(primokey,0x00,256);
  memset(PCKBD,0x00,256);

  NewINT_09.pm_offset =(int)my_keyboard_isr;
  NewINT_09.pm_selector=_go32_my_cs();
  _go32_dpmi_get_protected_mode_interrupt_vector(0x09,&OldINT_09);
  _go32_dpmi_allocate_iret_wrapper(&NewINT_09);
  _go32_dpmi_set_protected_mode_interrupt_vector(0x09,&NewINT_09);
}

void UninstallKeyboardISR() {
  _go32_dpmi_set_protected_mode_interrupt_vector(0x09,&OldINT_09);
  _go32_dpmi_free_iret_wrapper(&NewINT_09);
}

/* PRIMO IN #1 port

BE-1
====

+-7---+-6---+-5---+-4---+-3---+-2---+-1---+-0---+
|     |     |     |     |     |     |     |     |
|  -  |  -  | BLK | IN1 | IN0 | TIN | RES | KBD |
|     |     |     |     |     |     |     |     |
+-----+-----+-----+-----+-----+-----+-----+-----+

only KBD,RES and BLK are implemented at the moment

*/

// ecx: port address, al: data return
void BE1in() {
 __asm __volatile__("
	pushl	%edx
	pushl	%ecx

	/* get the KBD bit */
	andl	$63,%ecx
	movb	_primokey(%ecx),%cl
	andb	$1,%cl

	/* check the reset button bit 	*/
	movb	(_PCKBD+0x46),%al
	shlb	$1,%al
	orb     %al,%cl

	/* get vertical blank bit 	*/
	movw   	$0x03da,%dx
	inb     %dx,%al
	andb    $8,%al
	shlb    $2,%al
	orb     %al,%cl

	orb     $0xdc,%cl
	mov     %cl,_BE1
	mov	%cl,%al

	popl	%ecx
	popl	%edx
 ");
}

/* PRIMO OUT port

KI-1
====

+-7---+-6---+-5---+-4---+-3---+-2---+-1---+-0---+
|     |     |     |     |     |     |     |     |
| NMI | JOY | V-2 | SPK | PAG | V-1 | TP1 | TP0 |
|     |     |     |     |     |     |     |     |
+-----+-----+-----+-----+-----+-----+-----+-----+

TP0,TP1 : tape output (SAVE), not implemented
V-2,V-1 : general output lines, not implemented
JOY     : serial joy, not implemented

PAG     : display pagingh low/high 8K (0xE800 or 0xC800)
SPK     : speaker bit 
NMI     : NMI enable/disable

*/

// ecx: port address, al: data to write to 
void KI1out() {
 __asm __volatile__("
	pushal
	cmpb	_KI1,%al
	jz	ki1_quit
	movb	%al,_KI1

	/* speaker */
	testb	$0x10,%al
	jz	spk_off
spk_on:
	inb	$0x61,%al
	orb	$0x03,%al
	outb	%al,$0x61
	jmp	setPage
spk_off:
	inb	$0x61,%al
	andb	$0xfc,%al
	outb	%al,$0x61
	
	/* display page */
setPage:	
	xorl	%ebx,%ebx
	testb	$0x08,_KI1
	jnz	sp1
	movl	$16000,%ebx
sp1:
	movw	$0x3d4,%dx
	movb	$0x0c,%al
	movb	%bh,%ah
	outw	%ax,%dx
	movb	%bl,%ah
	incb	%al
	outw	%ax,%dx

ki1_quit:
 	popal
 ");
}
