/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net

 Please read the read.me for the details.
******************************************************************************/


/* keyboard converter table */

unsigned short keyconvtable[256]={

 /* 0x00, no-key    */         0xffff,
 /* 0x01, ESC       */         0xffff,
 /* 0x02, 1         */         0xff0d,
 /* 0x03, 2         */         0xff0b,
 /* 0x04, 3         */         0xff09,
 /* 0x05, 4         */         0xff1f,
 /* 0x06, 5         */         0xff1d,
 /* 0x07, 6         */         0xff1b,
 /* 0x08, 7         */         0xff17,
 /* 0x09, 8         */         0xff21,
 /* 0x0a, 9         */         0xff2d,
 /* 0x0b, î         */         0xff3e,
 /* 0x0c, Å         */         0xff30,
 /* 0x0d, ¢         */         0xff3b,
 /* 0x0e, BACKSP    */         0xff39,
 /* 0x0f, TAB       */         0x7f29,

 /* 0x10, Q         */         0xff0c,
 /* 0x11, W         */         0xff06,
 /* 0x12, E         */         0xff04,
 /* 0x13, R         */         0xff14,
 /* 0x14, T         */         0xff16,
 /* 0x15, Z         */         0xff22,
 /* 0x16, U         */         0xff24,
 /* 0x17, I         */         0xff2e,
 /* 0x18, O         */         0xff34,
 /* 0x19, P         */         0xff32,
 /* 0x1a, ä         */         0x7f3b,
 /* 0x1b, È         */         0xff33,
 /* 0x1c, ENTER     */         0xff37,
 /* 0x1d, Lf-CTRL   */         0xff07,
 /* 0x1e, A         */         0xff0e,
 /* 0x1f, S         */         0xff02,

 /* 0x20, D         */         0xff08,
 /* 0x21, F         */         0xff12,
 /* 0x22, G         */         0xff1c,
 /* 0x23, H         */         0xff18,
 /* 0x24, J         */         0xff26,
 /* 0x25, K         */         0xff2a,
 /* 0x26, L         */         0xff28,
 /* 0x27, ê         */         0xff3a,
 /* 0x28, µ         */         0xff3c,
 /* 0x29, °        */         0xff25,
 /* 0x2a, Lf-SHIFT  */         0xff03,
 /* 0x2b, Î         */         0x7f33,
 /* 0x2c, Y         */         0xff00,
 /* 0x2d, X         */         0xff0a,
 /* 0x2e, C         */         0xff10,
 /* 0x2f, V         */         0xff1e,

 /* 0x30, B         */         0xff1a,
 /* 0x31, N         */         0xff20,
 /* 0x32, M         */         0xff2c,
 /* 0x33, ,?        */         0xff2f,
 /* 0x34, .:        */         0xff2b,
 /* 0x35, -_        */         0xff29,
 /* 0x36, Rg-SHIFT  */         0xff03,
 /* 0x37, NUM-star **/         0xff31,
 /* 0x38, Lf-ALT    */         0x7f27,
 /* 0x39, SPACE     */         0xff19,
 /* 0x3a, CAPSLOCK  */         0xff05,
 /* 0x3b, F1        */         0xbf08, /* primo ctrl-d */
 /* 0x3c, F2        */         0xbf16, /* primo ctrl-t */
 /* 0x3d, F3        */         0xbf04, /* primo ctrl-e */
 /* 0x3e, F4        */         0xbf24, /* primo ctrl-u */
 /* 0x3f, F5        */         0xbf10, /* primo ctrl-c */

 /* 0x40, F6        */         0xbf02, /* primo ctrl-s */
 /* 0x41, F7        */         0xbf1a, /* primo ctrl-b */
 /* 0x42, F8        */         0xbf14, /* primo ctrl-r */
 /* 0x43, F9        */         0xbf34, /* primo ctrl-o */
 /* 0x44, F10       */         0xbf06, /* primo ctrl-w */
 /* 0x45, NUMLOCK   */         0x7f2f,
 /* 0x46, SCROLLLOCK*/         0xff40, /* primo reset button */
 /* 0x47, NUM-7     */         0xff17,
 /* 0x48, NUM-8     */         0xff21,
 /* 0x49, NUM-9     */         0xff2d,
 /* 0x4a, NUM-minus-*/         0xff29,
 /* 0x4b, NUM-4     */         0xff1f,
 /* 0x4c, NUM-5     */         0xff1d,
 /* 0x4d, NUM-6     */         0xff1b,
 /* 0x4e, NUM-plus +*/         0xff23,
 /* 0x4f, NUM-1     */         0xff0d,

 /* 0x50, NUM-2     */         0xff0b,
 /* 0x51, NUM-3     */         0xff09,
 /* 0x52, NUM-0     */         0xff25,
 /* 0x53, NUM-dot  .*/         0xff2b,
 /* 0x54, no-key    */         0xffff,
 /* 0x55, no-key    */         0xffff,
 /* 0x56, no-key    */         0xffff,
 /* 0x57, F11       */         0xffff,
 /* 0x58, F12       */         0xffff,
 /* 0x59, no-key    */         0xffff,
 /* 0x5a, no-key    */         0xffff,
 /* 0x5b, no-key    */         0xffff,
 /* 0x5c, no-key    */         0xffff,
 /* 0x5d, no-key    */         0xffff,
 /* 0x5e, no-key    */         0xffff,
 /* 0x5f, no-key    */         0xffff,

 /* 0x60, no-key    */         0xffff,
 /* 0x61, no-key    */         0xffff,
 /* 0x62, no-key    */         0xffff,
 /* 0x63, no-key    */         0xffff,
 /* 0x64, no-key    */         0xffff,
 /* 0x65, no-key    */         0xffff,
 /* 0x66, no-key    */         0xffff,
 /* 0x67, no-key    */         0xffff,
 /* 0x68, no-key    */         0xffff,
 /* 0x69, no-key    */         0xffff,
 /* 0x6a, no-key    */         0xffff,
 /* 0x6b, no-key    */         0xffff,
 /* 0x6c, no-key    */         0xffff,
 /* 0x6d, no-key    */         0xffff,
 /* 0x6e, no-key    */         0xffff,
 /* 0x6f, no-key    */         0xffff,

 /* 0x70, no-key    */         0xffff,
 /* 0x71, no-key    */         0xffff,
 /* 0x72, no-key    */         0xffff,
 /* 0x73, no-key    */         0xffff,
 /* 0x74, no-key    */         0xffff,
 /* 0x75, no-key    */         0xffff,
 /* 0x76, no-key    */         0xffff,
 /* 0x77, no-key    */         0xffff,
 /* 0x78, no-key    */         0xffff,
 /* 0x79, no-key    */         0xffff,
 /* 0x7a, no-key    */         0xffff,
 /* 0x7b, no-key    */         0xffff,
 /* 0x7c, no-key    */         0xffff,
 /* 0x7d, no-key    */         0xffff,
 /* 0x7e, no-key    */         0xffff,
 /* 0x7f, no-key    */         0xffff,

 /* 0x80, no-key    */         0xffff,
 /* 0x81, no-key    */         0xffff,
 /* 0x82, no-key    */         0xffff,
 /* 0x83, no-key    */         0xffff,
 /* 0x84, no-key    */         0xffff,
 /* 0x85, no-key    */         0xffff,
 /* 0x86, no-key    */         0xffff,
 /* 0x87, no-key    */         0xffff,
 /* 0x88, no-key    */         0xffff,
 /* 0x89, no-key    */         0xffff,
 /* 0x8a, no-key    */         0xffff,
 /* 0x8b, no-key    */         0xffff,
 /* 0x8c, no-key    */         0xffff,
 /* 0x8d, no-key    */         0xffff,
 /* 0x8e, no-key    */         0xffff,
 /* 0x8f, no-key    */         0xffff,

 /* 0x90, no-key    */         0xffff,
 /* 0x91, no-key    */         0xffff,
 /* 0x92, no-key    */         0xffff,
 /* 0x93, no-key    */         0xffff,
 /* 0x94, no-key    */         0xffff,
 /* 0x95, no-key    */         0xffff,
 /* 0x96, no-key    */         0xffff,
 /* 0x97, no-key    */         0xffff,
 /* 0x98, no-key    */         0xffff,
 /* 0x99, no-key    */         0xffff,
 /* 0x9a, no-key    */         0xffff,
 /* 0x9b, no-key    */         0xffff,
 /* 0x9c, NUM-ENTER */         0xff37,
 /* 0x9d, Rg-CTRL   */         0xff07,
 /* 0x9e, no-key    */         0xffff,
 /* 0x9f, no-key    */         0xffff,

 /* 0xa0, no-key    */         0xffff,
 /* 0xa1, no-key    */         0xffff,
 /* 0xa2, no-key    */         0xffff,
 /* 0xa3, no-key    */         0xffff,
 /* 0xa4, no-key    */         0xffff,
 /* 0xa5, no-key    */         0xffff,
 /* 0xa6, no-key    */         0xffff,
 /* 0xa7, no-key    */         0xffff,
 /* 0xa8, no-key    */         0xffff,
 /* 0xa9, no-key    */         0xffff,
 /* 0xaa, no-key    */         0xffff,
 /* 0xab, no-key    */         0xffff,
 /* 0xac, no-key    */         0xffff,
 /* 0xad, no-key    */         0xffff,
 /* 0xae, no-key    */         0xffff,
 /* 0xaf, no-key    */         0xffff,

 /* 0xb0, no-key    */         0xffff,
 /* 0xb1, no-key    */         0xffff,
 /* 0xb2, no-key    */         0xffff,
 /* 0xb3, no-key    */         0xffff,
 /* 0xb4, no-key    */         0xffff,
 /* 0xb5, NUM-per  /*/         0x7f17,
 /* 0xb6, no-key    */         0xffff,
 /* 0xb7, no-key    */         0xffff,
 /* 0xb8, Rg-ALT    */         0xff27,
 /* 0xb9, no-key    */         0xffff,
 /* 0xba, no-key    */         0xffff,
 /* 0xbb, no-key    */         0xffff,
 /* 0xbc, no-key    */         0xffff,
 /* 0xbd, no-key    */         0xffff,
 /* 0xbe, no-key    */         0xffff,
 /* 0xbf, no-key    */         0xffff,

 /* 0xc0, no-key    */         0xffff,
 /* 0xc1, no-key    */         0xffff,
 /* 0xc2, no-key    */         0xffff,
 /* 0xc3, no-key    */         0xffff,
 /* 0xc4, no-key    */         0xffff,
 /* 0xc5, no-key    */         0xffff,
 /* 0xc6, no-key    */         0xffff,
 /* 0xc7, HOME      */         0xff35,
 /* 0xc8, CR-UP     */         0xff01,
 /* 0xc9, PGUP      */         0xbf0c,
 /* 0xca, no-key    */         0xffff,
 /* 0xcb, CR-LEFT   */         0xff39,
 /* 0xcc, no-key    */         0xffff,
 /* 0xcd, CR-RIGHT  */         0xff3d,
 /* 0xce, no-key    */         0xffff,
 /* 0xcf, END       */         0xff3f,

 /* 0xd0, CR-DOWN   */         0xff0f,
 /* 0xd1, PGDN      */         0xbf32,
 /* 0xd2, INS       */         0x7f23,
 /* 0xd3, DEL       */         0x7f2b,
 /* 0xd4, no-key    */         0xffff,
 /* 0xd5, no-key    */         0xffff,
 /* 0xd6, no-key    */         0xffff,
 /* 0xd7, no-key    */         0xffff,
 /* 0xd8, no-key    */         0xffff,
 /* 0xd9, no-key    */         0xffff,
 /* 0xda, no-key    */         0xffff,
 /* 0xdb, no-key    */         0xffff,
 /* 0xdc, no-key    */         0xffff,
 /* 0xdd, no-key    */         0xffff,
 /* 0xde, no-key    */         0xffff,
 /* 0xdf, no-key    */         0xffff,

 /* 0xe0, no-key    */         0xffff,
 /* 0xe1, no-key    */         0xffff,
 /* 0xe2, no-key    */         0xffff,
 /* 0xe3, no-key    */         0xffff,
 /* 0xe4, no-key    */         0xffff,
 /* 0xe5, no-key    */         0xffff,
 /* 0xe6, no-key    */         0xffff,
 /* 0xe7, no-key    */         0xffff,
 /* 0xe8, no-key    */         0xffff,
 /* 0xe9, no-key    */         0xffff,
 /* 0xea, no-key    */         0xffff,
 /* 0xeb, no-key    */         0xffff,
 /* 0xec, no-key    */         0xffff,
 /* 0xed, no-key    */         0xffff,
 /* 0xee, no-key    */         0xffff,
 /* 0xef, no-key    */         0xffff,

 /* 0xf0, no-key    */         0xffff,
 /* 0xf1, no-key    */         0xffff,
 /* 0xf2, no-key    */         0xffff,
 /* 0xf3, no-key    */         0xffff,
 /* 0xf4, no-key    */         0xffff,
 /* 0xf5, no-key    */         0xffff,
 /* 0xf6, no-key    */         0xffff,
 /* 0xf7, no-key    */         0xffff,
 /* 0xf8, no-key    */         0xffff,
 /* 0xf9, no-key    */         0xffff,
 /* 0xfa, no-key    */         0xffff,
 /* 0xfb, no-key    */         0xffff,
 /* 0xfc, no-key    */         0xffff,
 /* 0xfd, no-key    */         0xffff,
 /* 0xfe, no-key    */         0xffff,
 /* 0xff, no-key    */         0xffff
 };

unsigned char primokey[256];

/*
  PC - PRIMO special keyboard assignments

  "SYS" keys:
  F11                 - Primo reset
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
