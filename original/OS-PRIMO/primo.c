/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net

 Please read the read.me for the details.
******************************************************************************/

#include <stdio.h>
#include <dpmi.h>
#include <time.h>

#include "z80cpu.h"
#include "primohw.h"

/* globals */
static dword addr;
static byte  data;

/* implemented in priread.c */
int ReadPRI(const char *filename);

/* called when the CPU wants to write the following areas:
   0x0000...0x3fff: ROM, prohibited (nothing happens)
   0xc800...0xdfff: second screen page 
   0xe800...0xffff: primary screen page */
void SpecWriteByte() {
 __asm("
	pushal
	movl	%edi,_addr	/* we use nasty globals for this */
	movb	%al,_data
 ");
  /* if it's the screenram */
 if (addr>=0xc800) {
   Z80mem[addr]=data; /* update the real primo memory, too */
   (addr<0xe800)?(SecSput(addr,data)):(PriSput(addr,data));
 }
  /* There is no code here for handling the writes into the ROM,
     but the SpecWriteByte is called, when the CPU wants to write the
     ROM. In this case, nothing happes, so the ROM remains the same. */
 __asm("popal");
}

/* For now there is no special word writing. It's calling the 
   SpecWriteByte function to write out the lo/hi bytes. */
void SpecWriteWord() {
 __asm("
	pushl	%eax
	call	_SpecWriteByte
	movb	%ah,%al
	inc	%edi
	call	_SpecWriteByte
	dec	%edi
	popl	%eax	
");
}

/* PRIMO IN ports realization ("BE1": 0x00..0x3f) */
/* %ecx: port address, %al: must contain the return value */
void ByteIn() {
 __asm("
	mov	$00,%al
	cmpb	$64,%cl
	jnc	in_quit
	call	_BE1in
in_quit:
 ");
}

/* PRIMO OUT ports realization ("KI1": 0x00..0x3f) */
/* %ecx: port address, %al: byte to out */
void ByteOut() {
 __asm("
	cmpb	$64,%cl
	jnc	out_quit
	call	_KI1out
out_quit:
 ");
}

void ExtSub() {
}

/* PRIMO ROM patch codes: PTP tape handling could be here */

void ExtProc0() {
}

void ExtProc1() {
}

void ExtProc2() {
}

void ExtProc3() {
}


int main(int argc, char *argv[]) {
 FILE *f;
 int i,j;

 /* Create a descriptor for the PC video segment */
 DescA000=__dpmi_segment_to_descriptor(0xa000);
 /* Init PRIMO screen */
 PrimoScreen();

 /* memory allocation:
    64K for the normal spectrum RAM
    64K for the memory specification (RAM/ROM/Spec RAM)
    4 bytes for "padding" ( just in case Z80 PC=0xffff )
 */
 Z80mem=(byte *)malloc(2*(65536+4));
 /* memory specifier */
 Z80memSpec=Z80mem+65536+4;
 /* clear both */
 memset(Z80mem,0x00,65536+4);
 memset(Z80memSpec,0x00,65536+4);

 memset(Z80memSpec,0x01,16384);		/* PRIMO ROM area 	 */
 memset(Z80memSpec+0xC800,0x01,6144);	/* Secondary screen area */
 memset(Z80memSpec+0xE800,0x01,6144);	/* Primary screen area   */

 /* read the ROM image */
 if (f=fopen("a64rom.bin","rb")) {
   fread(Z80mem,1,16384,f);
   fclose(f);
 } else {
   free(Z80mem);
   PcScreen();
   printf("The default ROM image 'a64rom.bin' not found. Abort.\n");
   return 1;
 }

 /* install ISRs */
 InstallTimerISR();
 InstallKeyboardISR();

 /* Reset the CPU */
 Z80Reset();

 /* OK, here comes the RAM init part. The address 0x3994 below is the
    entry point of the basic command line input. This step is required
    for loading the PRI files. */
 while (Z_PC!=0x3994) ExecOne();

 /* load the pri file if it was specified in the command line */
 if (argc==2) {
   i=ReadPRI(argv[1]);
   /* if i>0, it's a valid address for start the loaded program. */
   if (i>0) Z_PC=i;
 }

 /* Main execution cycle */
 do {
  /* Execute one Z80 instruction */
  ExecOne();

  /* some delay: calibrated to a 2.4GHz intel proc (more or less) */
  __asm("
	pushl	%ecx
	movl	$3000,%ecx
ml0:
	nop
	nop
	loop	ml0
	
	popl	%ecx
  ");
  /* F11: HARD reset the PRIMO */
  if (PCKBD[0x57]) Z80Reset();

 } while (!PCKBD[1]); /* ESC:  quit */

 /* deinstall the ISR routines */
 UninstallKeyboardISR();
 UninstallTimerISR();

 /* restore the PC screenmode (80x25/c16 text) */
 PcScreen();
 /* freeing the allocated memory */
 free(Z80mem);
 return 0;
}
