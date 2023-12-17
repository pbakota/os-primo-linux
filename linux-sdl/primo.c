/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net
 (C) Peter Bakota, 2023. bakota@gmail.com Linux (SDL2 port)

 Please read the read.me for the details.
******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include "Z80/Z80.h"
#include "Z80/Z80.c"

#include "io.c"
#include "keyboard.c"

byte PCKBD[256]; /* press/release state */

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture *texture;
SDL_TimerID timer_id = 0;
SDL_DisplayMode dm;

/* ARGB format */
Uint32 back_color = 0x00050505;
Uint32 pixel_color = 0x00ffffff;
#define RED(x) ((x & 0x00ff0000) >> 16)
#define GREEN(x) ((x & 0x0000ff00) >> 8)
#define BLUE(x) ((x & 0x000000ff))

#define WINDOW_W 640
#define WINDOW_H 480

#define SCREEN_W 256
#define SCREEN_H 192

// clang-format off
const SDL_Rect windowed_view_port =
{
    (WINDOW_W - SCREEN_W*2) / 2,
    (WINDOW_H - SCREEN_H*2) / 2,
    SCREEN_W*2,
    SCREEN_H*2
};
// clang-format on
SDL_Rect wp = windowed_view_port;

/* Primo memory */
word display_page = 0xe800;
byte Z80mem[65536];

char *pri_to_load = NULL;

Z80 R;
byte KI1, KI2, KI3, KI4; /* PRIMO out ports, only KI1 used now */
byte BE1, BE2, BE3, BE4; /* PRIMO in ports, only BE1 used now  */

#define Q1 15000000
#define CPU_CLOCK_NORMAL (Q1 / 6) /* ~2.5 MHz */
#define CPU_CLOCK_TURBO (Q1 / 4)  /* ~3.75 MHz */
#define CPU_CLOCK CPU_CLOCK_NORMAL

#define VSCANLINES 312
#define HSCANLINES 240 /* ??? not sure about this number, do not get it granted I am totally noob in emulation */
#define FRAME_PER_SECOND 50

#define FRAME_RATE (1000 / FRAME_PER_SECOND)
#define CYCLES_PER_SCANLINE ((CPU_CLOCK / FRAME_PER_SECOND) / VSCANLINES)

word scanline = 0;
byte vblank = 0;
byte frame_count = 0;
Uint32 prev_ticks;
bool fullscreen = false;

void cleanup()
{
  if (timer_id)
    SDL_RemoveTimer(timer_id);
  if (texture)
    SDL_DestroyTexture(texture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);

  SDL_Quit();
}

bool die(const char *message)
{
  fprintf(stderr, "%s : %s\n", message, SDL_GetError());
  exit(1);
}

void read_keyboard(void)
{
  int d;
  const byte *key = SDL_GetKeyboardState(NULL);
  byte t, c;

  memset(primokey, 0, 256);
  for (d = 0; d < 256; ++d)
  {
    if (keyconvtable[d].scancode == SDL_SCANCODE_UNKNOWN)
    {
      continue;
    }

    t = key[keyconvtable[d].scancode];
    c = keyconvtable[d].primo;
    PCKBD[d] = t;
    primokey[c & 255] |= t;

    // if (!(c & 0x8000))
    // {
    //   primokey[0x03] |= t; /* primo shift   */
    // }
    // if (!(c & 0x4000))
    // {
    //   primokey[0x07] |= t; /* primo control */
    // }
  }
}

void update_screen()
{
  int i, j, k;
  byte *src = Z80mem + display_page, m;
  Uint32 *pixels;
  int pitch;

  ((SDL_LockTexture(texture, NULL, (void **)&pixels, &pitch))) && die("Lock texture");

  for (j = 0; j < 192; ++j)
  {
    for (i = 0; i < 32; ++i, src++)
    {
      m = 128;
      for (k = 0; k < 8; ++k, m >>= 1)
      {
        pixels[i * 8 + k] = (*src & m) ? pixel_color : back_color;
      }
    }
    pixels += pitch / sizeof(Uint32);
  }

  SDL_UnlockTexture(texture);
}

// Z80 stuffs
inline byte RdZ80(word addr)
{
  return Z80mem[addr];
}

/* called when the CPU wants to write the following areas:
   0x0000...0x3fff: ROM, prohibited (nothing happens)
   0xc800...0xdfff: second screen page
   0xe800...0xffff: primary screen page */
inline void WrZ80(word addr, byte val)
{
  if (addr < 0X4000)
  {
    /* There is no code here for handling to write into the ROM,
       but it is called, when the CPU wants to write the
       ROM. In this case, nothing happen, so the ROM remains the same. */
    return;
  }
  Z80mem[addr] = val;
}

/* PRIMO IN ports realization ("BE1": 0x00..0x3f) */
inline byte InZ80(word port)
{
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

  /* get the KBD bit */
  byte val = primokey[port & 0x3f];

  /* check the reset button bit 	*/
  val |= PCKBD[0x46] << 1;

  /* get vertical blank bit 	*/
  val |= vblank << 5;

  /* set unused bits */
  val |= 0xdc; /* 0b11011100 */
  BE1 = val;

  return val;
}

inline void OutZ80(word port, byte val)
{
  if (port >= 0x40 || KI1 == val)
  {
    return;
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

  KI1 = val;

  /* speaker */
  if (val & 0x10)
  {
    /* spk_on */
  }
  else
  {
    /* spk_off */
  }

  /* display page */
  if (val & 0x08)
  {
    display_page = 0xe800;
  }
  else
  {
    display_page = 0xc800;
  }
}

inline void PatchZ80(Z80 *R) {}

#ifdef DEBUG_Z80
byte DebugZ80(Z80 *R)
{
  fprintf(stderr, "PC=%04x\n", R->PC.W);
}
#endif

void set_title(float fps)
{
  unsigned char b[256];
  snprintf(b, sizeof(b), "OS-PRIMO SDL (Esc-EXIT) FPS:%d", (int)fps);
  SDL_SetWindowTitle(window, b);
}

void set_window_size()
{
  if (fullscreen)
  {
    SDL_SetWindowSize(window, dm.w, dm.h);
  }
  else
  {
    SDL_SetWindowSize(window, WINDOW_W, WINDOW_H);
  }

  SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  if (fullscreen)
  {
    // "fake" fullscreen
    float yz = (float)dm.h / (float)WINDOW_H;

    wp.h = (float)(SCREEN_H * 2) * yz;
    wp.w = (float)wp.h * ((float)(SCREEN_W * 2) / (float)(SCREEN_H * 2));
    wp.x = (dm.w - wp.w) / 2;
    wp.y = (dm.h - wp.h) / 2;
  }
  else
  {
    wp = windowed_view_port;
  }
}

/** LoopZ80() ************************************************/
/** Refresh screen, check keyboard.                         **/
/*************************************************************/
word LoopZ80(Z80 *R)
{
  /* New scanline */
  scanline = scanline < VSCANLINES ? scanline + 1 : 0;

  /* If first scanline of the screen... */
  if (scanline == 0)
  {
    vblank = 0;
    R->IPeriod = CYCLES_PER_SCANLINE;
  }

  /* When reaching end of screen */
  if (scanline == 192)
  {

    bool exit_loop = false;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        exit_loop = true;
        break;
      case SDL_KEYDOWN:
      {
        Uint32 ctrl = event.key.keysym.mod & KMOD_CTRL;
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          exit_loop = true;
          break;
        case SDLK_F11:
          fullscreen = !fullscreen;
          set_window_size();
          break;
        case SDLK_F12:
          if (ctrl)
          {
            ResetZ80(R);
          }
          break;
        }
        break;
      }
      break;
      case SDL_KEYUP:
        break;
      }
    }

    if (exit_loop)
    {
      return INT_QUIT;
    }

    read_keyboard();
    update_screen();

    SDL_SetRenderDrawColor(renderer, RED(back_color), GREEN(back_color), BLUE(back_color), 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, &wp);
    SDL_RenderPresent(renderer);

    /* limit to frame rate */
    int remains = FRAME_RATE - (SDL_GetTicks() - prev_ticks);
    if (remains > 0)
    {
      SDL_Delay(remains);
    }

    prev_ticks = SDL_GetTicks();

    ++frame_count;

    if(pri_to_load) {
      if(R->PC.W >= 0x3935 && R->PC.W <= 0x3994) {
        int addr = load_pri(pri_to_load);
        if(addr>0){
          R->PC.W = addr;
        }
        pri_to_load = NULL;
      }
    }

    vblank = 1;

    /* During the vblank phase, more CPU cycles can be executed */
    R->IPeriod = CYCLES_PER_SCANLINE*2; /* 2x faster. This multiplier is totally made up, I am not sure how accurate is this (probalby not)*/
    return INT_NMI;
  }

  return INT_NONE;
}

unsigned int timer(unsigned int, void *)
{
  set_title(frame_count);
  frame_count = 0;
  return 1000;
}

int main(int argc, char *argv[])
{
  FILE *f;
  int i, j;

  /* clear memory */
  memset(Z80mem, 0x00, 65536);
  memset(PCKBD, 0x00, 256);
  memset(primokey, 0x00, 256);

  /* 0x0000 0x3fff    16384 bytes   ROM */
  /* 0x4000 0xc7ff    34816 bytes   RAM */
  /* 0xc800 0xe7ff     6144 bytes   SECONDARY SCREEN */
  /* 0xe800 0xffff     6144 bytes   PRIMARY SCREEN */

  /* read the ROM image */
  if (f = fopen("a64rom.bin", "rb"))
  {
    fread(Z80mem, 1, 16384, f);
    fclose(f);
  }
  else
  {
    printf("The default ROM image 'a64rom.bin' not found. Abort.\n");
    return 1;
  }

  (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) == -1) && die("Failed to initialize SDL");

  atexit(cleanup);

  ((window = SDL_CreateWindow("OS-PRIMO SDL (Esc-EXIT)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN)) == NULL) && die("Failed to create window");

  ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) && die("Failed to create renderer");

  ((texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H)) == NULL) && die("Failed to create texture");

  ((timer_id = SDL_AddTimer(1000, &timer, NULL)) == 0) && die("Failed to create timer");

  (SDL_GetDesktopDisplayMode(0, &dm)) && die("Display mode failed");

  (dm.w < WINDOW_W || dm.h < WINDOW_H) && die("Not supported desktop resolution");

#ifdef DEBUG_Z80
  R.Trap = 0x0000;
  R.Trace = 0;
#endif

  prev_ticks = SDL_GetTicks();

  R.IPeriod = CYCLES_PER_SCANLINE;
  ResetZ80(&R);

  if (argc > 1)
  {
    pri_to_load = argv[1];
  }

  word pc = RunZ80(&R);
  fprintf(stderr, "Leaving emulator at PC=$%04x\n", pc);

  cleanup();

  return 0;
}
