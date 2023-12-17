/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net

 Please read the read.me for the details.
******************************************************************************/

/* PRI file reader */

#include <stdio.h>
#include "z80cpu.h"

// #define DEBUG

/* a simple filesize function  */
long filesize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}


int ReadPRI(const char *filename) {
 FILE *f;
 word w,q;
 word a,s;
 byte t;
 int  l;
 byte *bf;

#ifdef DEBUG
 FILE *dbg;

 dbg=fopen("debug.txt","w");
 fprintf(dbg,"ReadPRI called, filename is [%s]\n",filename); 
#endif

 if (f=fopen(filename,"rb")) {
  l=filesize(f);

#ifdef DEBUG
	fprintf(dbg,"Filesize is %d\n",l);
#endif

  if ((l>65536)||(!l)) {
   fclose(f);
   return -1;
  }

  bf=(byte *)malloc(l);	/* something "buffered" read */
  fread(bf,1,l,f);
  fclose(f);
  
  w=0;  
  do {
    t=*(bf+w); 				/* type of the block 	*/


    if (t==0xc9) {

#ifdef DEBUG
	fprintf(dbg," got 0xC9 return 0\n");
#endif

	free(bf);
	return 0;
    }

    a=((*(bf+w+2))<<8) + (*(bf+w+1));	/* address of the block */

#ifdef DEBUG
	fprintf(dbg,"t=%x a=%x; ",t,a);
#endif


    if (t==0xc3) {

#ifdef DEBUG
	fprintf(dbg," got 0xC3 a=%x\n",a);
#endif

	free(bf);
	return (int)a;
    }

    s=((*(bf+w+4))<<8) + (*(bf+w+3));	/* size of the block    */	

#ifdef DEBUG
	fprintf(dbg,"s=%x; ",s);
#endif

    if (t==0xd1) {
	a+= ( (*(Z80mem+0x40a5)) <<8)+ (*(Z80mem+0x40a4))  ;
	*(Z80mem+0x40f9)=(a+s+1)&255;
	*(Z80mem+0x40fa)=((a+s+1)>>8)&255;
    }

    w+=5;
    memcpy(Z80mem+a,bf+w,s);

#ifdef DEBUG
	fprintf(dbg,"memcpy(%x,%x,%x); ",a,w,s);
#endif

    w+=s;

#ifdef DEBUG
	fprintf(dbg,"w=%d\n",w);
#endif

  } while (w<l);

  free(bf); 
 
 }
 return -1;

}