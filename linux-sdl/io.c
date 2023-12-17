/*****************************************************************************

 JOCO's OpenSource Primo emulator.

 (C) Jozsef Laszlo, 2004. joco@szabolcs.net
 (C) Peter Bakota, 2023. bakota@gmail.com Linux (SDL2 port)

 Please read the read.me for the details.
******************************************************************************/

#include <stdio.h>
#include "Z80/Z80.h"

#define DEBUG_IO

extern byte Z80mem[];

// clang-format off
#define DIE(...) do { fprintf(stderr, __VA_ARGS__); fclose(fp); } while(0);
// clang-format on

typedef struct _pri_header
{
    byte type;
    pair addr;
} __attribute__((packed)) pri_header;

typedef struct _pri_data
{
    pair size;
    byte bytes[0];
} __attribute__((packed)) pri_data;

int load_pri(const char *filename)
{
    FILE *fp;
    pri_header header;
    pri_data data;
    int eof = 0;
    int start_addr = -1;

    if (!(fp = fopen(filename, "rb")))
    {
        return -1;
    }

    while (!feof(fp) && !eof)
    {
        fread(&header, sizeof(header), 1, fp);

#if 1
        fprintf(stderr, "TYPE: 0x%02x\n", header.type);
        fprintf(stderr, " ADDR: 0x%04x\n", header.addr.W);
#endif

        switch (header.type)
        {
        default:
            DIE("Error: Unknown block type: 0x%02x\n", header.type);
            return -1;
        case 0xd1:
        case 0xd5:
        case 0xd9:
        {
            fread(&data, sizeof(data), 1, fp);
#if 1
            fprintf(stderr, " SIZE: 0x%04x (%d bytes)\n", data.size.W, data.size.W);
#endif
            if (header.addr.W + data.size.W > 65535)
            {
                DIE("Error: Invalid block: addr=0x%02x, size=%d\n", header.addr.W, data.size.W);
                return -1;
            }

            word addr;
            switch (header.type)
            {
            case 0xd1:
                /* basic */
                addr = header.addr.W + (Z80mem[0x40a5] << 8 | Z80mem[0x40a4]);
                Z80mem[0x40f9] = (addr + data.size.W + 1) & 255;
                Z80mem[0x40fa] = ((addr + data.size.W + 1) >> 8) & 255;
                fread(&Z80mem[addr], data.size.W, 1, fp);
                break;
            case 0xd5:
                /* screen */
                fseek(fp, data.size.W, SEEK_CUR);
                break;
            case 0xd9:
                /* machine code */
                addr = header.addr.W;
                fread(&Z80mem[addr], data.size.W, 1, fp);
                break;
            }
        }
        break;
        case 0xc3:
            start_addr = header.addr.W;
        case 0xc9:
            eof = 1;
            break;
        }
    }

    fclose(fp);
    return start_addr;
}

#undef DIE
