/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net
 (C) Peter Bakota, 2023. bakota@gmail.com Linux (SDL2 port)

 Please read the read.me for the details.

 Code page: CP 852
******************************************************************************/

/* keyboard converter table */

#include <SDL2/SDL_scancode.h>

// clang-format off
struct
{
    int scancode;
    unsigned short primo;
} keyconvtable[256] = {
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x00, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_0             , .primo = /* 0x01, 0         */ 0xff25},
    {.scancode = SDL_SCANCODE_1             , .primo = /* 0x02, 1         */ 0xff0d},
    {.scancode = SDL_SCANCODE_2             , .primo = /* 0x03, 2         */ 0xff0b},
    {.scancode = SDL_SCANCODE_3             , .primo = /* 0x04, 3         */ 0xff09},
    {.scancode = SDL_SCANCODE_4             , .primo = /* 0x05, 4         */ 0xff1f},
    {.scancode = SDL_SCANCODE_5             , .primo = /* 0x06, 5         */ 0xff1d},
    {.scancode = SDL_SCANCODE_6             , .primo = /* 0x07, 6         */ 0xff1b},
    {.scancode = SDL_SCANCODE_7             , .primo = /* 0x08, 7         */ 0xff17},
    {.scancode = SDL_SCANCODE_8             , .primo = /* 0x09, 8         */ 0xff21},
    {.scancode = SDL_SCANCODE_9             , .primo = /* 0x0a, 9         */ 0xff2d},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x0b, ö         */ 0xff3e},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x0c, ü         */ 0xff30},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x0d, ó         */ 0xff3b},
    {.scancode = SDL_SCANCODE_BACKSPACE     , .primo = /* 0x0e, BACKSP    */ 0xff39},
    {.scancode = SDL_SCANCODE_TAB           , .primo = /* 0x0f, TAB       */ 0x7f29},

    {.scancode = SDL_SCANCODE_Q             , .primo = /* 0x10, Q         */ 0xff0c},
    {.scancode = SDL_SCANCODE_W             , .primo = /* 0x11, W         */ 0xff06},
    {.scancode = SDL_SCANCODE_E             , .primo = /* 0x12, E         */ 0xff04},
    {.scancode = SDL_SCANCODE_R             , .primo = /* 0x13, R         */ 0xff14},
    {.scancode = SDL_SCANCODE_T             , .primo = /* 0x14, T         */ 0xff16},
    {.scancode = SDL_SCANCODE_Z             , .primo = /* 0x15, Z         */ 0xff22},
    {.scancode = SDL_SCANCODE_U             , .primo = /* 0x16, U         */ 0xff24},
    {.scancode = SDL_SCANCODE_I             , .primo = /* 0x17, I         */ 0xff2e},
    {.scancode = SDL_SCANCODE_O             , .primo = /* 0x18, O         */ 0xff34},
    {.scancode = SDL_SCANCODE_P             , .primo = /* 0x19, P         */ 0xff32},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x1a, Ő         */ 0x7f3b},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x1b, Ú         */ 0xff33},
    {.scancode = SDL_SCANCODE_RETURN        , .primo = /* 0x1c, ENTER     */ 0xff37},
    {.scancode = SDL_SCANCODE_LCTRL         , .primo = /* 0x1d, Lf-CTRL   */ 0xff07},
    {.scancode = SDL_SCANCODE_A             , .primo = /* 0x1e, A         */ 0xff0e},
    {.scancode = SDL_SCANCODE_S             , .primo = /* 0x1f, S         */ 0xff02},

    {.scancode = SDL_SCANCODE_D             , .primo = /* 0x20, D         */ 0xff08},
    {.scancode = SDL_SCANCODE_F             , .primo = /* 0x21, F         */ 0xff12},
    {.scancode = SDL_SCANCODE_G             , .primo = /* 0x22, G         */ 0xff1c},
    {.scancode = SDL_SCANCODE_H             , .primo = /* 0x23, H         */ 0xff18},
    {.scancode = SDL_SCANCODE_J             , .primo = /* 0x24, J         */ 0xff26},
    {.scancode = SDL_SCANCODE_K             , .primo = /* 0x25, K         */ 0xff2a},
    {.scancode = SDL_SCANCODE_L             , .primo = /* 0x26, L         */ 0xff28},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x27, É         */ 0xff3a},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x28, Á         */ 0xff3c},
    {.scancode = SDL_SCANCODE_0             , .primo = /* 0x29, í         */ 0xff25},
    {.scancode = SDL_SCANCODE_LSHIFT        , .primo = /* 0x2a, Lf-SHIFT  */ 0xff03},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x2b, Ű         */ 0x7f33},
    {.scancode = SDL_SCANCODE_Y             , .primo = /* 0x2c, Y         */ 0xff00},
    {.scancode = SDL_SCANCODE_X             , .primo = /* 0x2d, X         */ 0xff0a},
    {.scancode = SDL_SCANCODE_C             , .primo = /* 0x2e, C         */ 0xff10},
    {.scancode = SDL_SCANCODE_V             , .primo = /* 0x2f, V         */ 0xff1e},

    {.scancode = SDL_SCANCODE_B             , .primo = /* 0x30, B         */ 0xff1a},
    {.scancode = SDL_SCANCODE_N             , .primo = /* 0x31, N         */ 0xff20},
    {.scancode = SDL_SCANCODE_M             , .primo = /* 0x32, M         */ 0xff2c},
    {.scancode = SDL_SCANCODE_COMMA         , .primo = /* 0x33, ,?        */ 0xff2f},
    {.scancode = SDL_SCANCODE_PERIOD        , .primo = /* 0x34, .:        */ 0xff2b},
    {.scancode = SDL_SCANCODE_MINUS         , .primo = /* 0x35, -_        */ 0xff29},
    {.scancode = SDL_SCANCODE_RSHIFT        , .primo = /* 0x36, Rg-SHIFT  */ 0xff03},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x37, NUM-star **/ 0xff31},
    {.scancode = SDL_SCANCODE_LALT          , .primo = /* 0x38, Lf-ALT    */ 0x7f27},
    {.scancode = SDL_SCANCODE_SPACE         , .primo = /* 0x39, SPACE     */ 0xff19},
    {.scancode = SDL_SCANCODE_CAPSLOCK      , .primo = /* 0x3a, CAPSLOCK  */ 0xff05},
    {.scancode = SDL_SCANCODE_F1            , .primo = /* 0x3b, F1        */ 0xbf08}, /* primo ctrl-d */
    {.scancode = SDL_SCANCODE_F2            , .primo = /* 0x3c, F2        */ 0xbf16}, /* primo ctrl-t */
    {.scancode = SDL_SCANCODE_F3            , .primo = /* 0x3d, F3        */ 0xbf04}, /* primo ctrl-e */
    {.scancode = SDL_SCANCODE_F4            , .primo = /* 0x3e, F4        */ 0xbf24}, /* primo ctrl-u */
    {.scancode = SDL_SCANCODE_F5            , .primo = /* 0x3f, F5        */ 0xbf10}, /* primo ctrl-c */

    {.scancode = SDL_SCANCODE_F6            , .primo = /* 0x40, F6        */ 0xbf02},  /* primo ctrl-s */
    {.scancode = SDL_SCANCODE_F7            , .primo = /* 0x41, F7        */ 0xbf1a},  /* primo ctrl-b */
    {.scancode = SDL_SCANCODE_F8            , .primo = /* 0x42, F8        */ 0xbf14},  /* primo ctrl-r */
    {.scancode = SDL_SCANCODE_F9            , .primo = /* 0x43, F9        */ 0xbf34},  /* primo ctrl-o */
    {.scancode = SDL_SCANCODE_F10           , .primo = /* 0x44, F10       */ 0xbf06},  /* primo ctrl-w */
    {.scancode = SDL_SCANCODE_NUMLOCKCLEAR  , .primo = /* 0x45, NUMLOCK   */ 0x7f2f},
    {.scancode = SDL_SCANCODE_SCROLLLOCK    , .primo = /* 0x46, SCROLLLOCK*/ 0xff40},  /* primo reset button */
    {.scancode = SDL_SCANCODE_KP_7          , .primo = /* 0x47, NUM-7     */ 0xff17},
    {.scancode = SDL_SCANCODE_KP_8          , .primo = /* 0x48, NUM-8     */ 0xff21},
    {.scancode = SDL_SCANCODE_KP_9          , .primo = /* 0x49, NUM-9     */ 0xff2d},
    {.scancode = SDL_SCANCODE_KP_MINUS      , .primo = /* 0x4a, NUM-minus-*/ 0xff29},
    {.scancode = SDL_SCANCODE_KP_4          , .primo = /* 0x4b, NUM-4     */ 0xff1f},
    {.scancode = SDL_SCANCODE_KP_5          , .primo = /* 0x4c, NUM-5     */ 0xff1d},
    {.scancode = SDL_SCANCODE_KP_6          , .primo = /* 0x4d, NUM-6     */ 0xff1b},
    {.scancode = SDL_SCANCODE_KP_PLUS       , .primo = /* 0x4e, NUM-plus +*/ 0xff23},
    {.scancode = SDL_SCANCODE_KP_1          , .primo = /* 0x4f, NUM-1     */ 0xff0d},

    {.scancode = SDL_SCANCODE_KP_2          , .primo = /* 0x50, NUM-2     */ 0xff0b},
    {.scancode = SDL_SCANCODE_KP_3          , .primo = /* 0x51, NUM-3     */ 0xff09},
    {.scancode = SDL_SCANCODE_KP_0          , .primo = /* 0x52, NUM-0     */ 0xff25},
    {.scancode = SDL_SCANCODE_KP_PERIOD     , .primo = /* 0x53, NUM-dot  .*/ 0xff2b},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x54, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x55, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x56, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_F11           , .primo = /* 0x57, F11       */ 0xffff},
    {.scancode = SDL_SCANCODE_F12           , .primo = /* 0x58, F12       */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x59, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5a, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5b, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5c, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5d, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5e, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x5f, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x60, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x61, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x62, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x63, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x64, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x65, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x66, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x67, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x68, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x69, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6a, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6b, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6c, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6d, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6e, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x6f, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x70, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x71, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x72, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x73, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x74, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x75, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x76, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x77, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x78, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x79, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7a, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7b, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7c, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7d, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7e, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x7f, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x80, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x81, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x82, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x83, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x84, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x85, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x86, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x87, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x88, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x89, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8a, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8b, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8c, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8d, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8e, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x8f, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x90, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x91, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x92, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x93, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x94, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x95, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x96, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x97, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x98, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x99, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x9a, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x9b, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_KP_ENTER      , .primo = /* 0x9c, NUM-ENTER */ 0xff37},
    {.scancode = SDL_SCANCODE_RCTRL         , .primo = /* 0x9d, Rg-CTRL   */ 0xff07},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x9e, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0x9f, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa0, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa1, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa2, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa3, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa5, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa7, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa8, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xa9, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xaa, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xab, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xac, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xad, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xae, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xaf, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb0, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb1, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb2, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb3, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_KP_DIVIDE     , .primo = /* 0xb5, NUM-per  /*/ 0x7f17},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb7, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_RALT          , .primo = /* 0xb8, Rg-ALT    */ 0xff27},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xb9, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xba, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xbb, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xbc, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xbd, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xbe, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xbf, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc0, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc1, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc2, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc3, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc5, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xc6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_HOME          , .primo = /* 0xc7, HOME      */ 0xff35},
    {.scancode = SDL_SCANCODE_UP            , .primo = /* 0xc8, CR-UP     */ 0xff01},
    {.scancode = SDL_SCANCODE_PAGEUP        , .primo = /* 0xc9, PGUP      */ 0xbf0c},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xca, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_LEFT          , .primo = /* 0xcb, CR-LEFT   */ 0xff39},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xcc, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_RIGHT         , .primo = /* 0xcd, CR-RIGHT  */ 0xff3d},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xce, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_END           , .primo = /* 0xcf, END       */ 0xff3f},

    {.scancode = SDL_SCANCODE_DOWN          , .primo = /* 0xd0, CR-DOWN   */ 0xff0f},
    {.scancode = SDL_SCANCODE_PAGEDOWN      , .primo = /* 0xd1, PGDN      */ 0xbf32},
    {.scancode = SDL_SCANCODE_INSERT        , .primo = /* 0xd2, INS       */ 0x7f23},
    {.scancode = SDL_SCANCODE_DELETE        , .primo = /* 0xd3, DEL       */ 0x7f2b},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd5, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd7, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd8, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xd9, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xda, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xdb, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xdc, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xdd, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xde, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xdf, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe0, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe1, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe2, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe3, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe5, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe7, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe8, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xe9, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xea, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xeb, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xec, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xed, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xee, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xef, no-key    */ 0xffff},

    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf0, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf1, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf2, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf3, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf4, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf5, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf6, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf7, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf8, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xf9, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xfa, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xfb, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xfc, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xfd, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xfe, no-key    */ 0xffff},
    {.scancode = SDL_SCANCODE_UNKNOWN       , .primo = /* 0xff, no-key    */ 0xffff}
};
// clang-format on

unsigned char primokey[256];

/*
  PC - PRIMO special keyboard assignments

  "SYS" keys:
  F11                 - Toggle fullscreen
  Ctrl + F12          - Primo reset
  SCROLL LOCK         - Primo "reset" button
  ESC                 - Quit from the emulator

  Aux. keys:
  F1/F2               - Inverse chars on/off
  F3/F4               - Underline on/of
  F5/F6               - Inverse screen on/off
  F7/F8               - Double width chars on/off
  F9/F10              - Horizontal/vertical writing

  Insert              - :
  Home                - CLS
  Page Up             - upper index
  Delete              - Delete
  End                 - BRK
  Page Down           - lower index

*/
