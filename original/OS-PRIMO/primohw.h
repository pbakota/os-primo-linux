/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net

 Please read the read.me for the details.
******************************************************************************/


#ifndef _PRIMOHW_HEADER
#define _PRIMOHW_HEADER

#ifndef _JOCOTYPES
#define _JOCOTYPES     
typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int  dword;
#endif

extern word DescA000;
extern int  SAddrTab[6144];

extern byte gfbits[];
extern int  gfxb[];
extern byte PCKBD[256];

void PrimoScreen();
void PcScreen();

void PriSput(int Addr, int Data);
void SecSput(int Addr, int Data);
void InstallTimerISR();
void UninstallTimerISR();
void InstallKeyboardISR();
void UninstallKeyboardISR();
void CalcScrnAddr();

void BE1in();
void KI1out();


#endif
