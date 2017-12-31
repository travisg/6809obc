#include "io.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

static const char *hexval = "0123456789abcdef";

static void put_hex_prefix(void) {
    putchar('0');
    putchar('x');
}

void put_hex8(uint8_t v) {
    put_hex_prefix();
    putchar(hexval[v >> 4]);
    putchar(hexval[v & 0xf]);
}

void put_hex16(uint16_t v) {
    put_hex_prefix();
    putchar(hexval[(v >> 12) & 0xf]);
    putchar(hexval[(v >> 8) & 0xf]);
    putchar(hexval[(v >> 4) & 0xf]);
    putchar(hexval[v & 0xf]);
}

char *readline(void) {
    static char linebuf[256];
    uint8_t pos = 0;

    // read a line of characters, skipping unprintable
    while (pos < 255) {
        int c = getchar();
        switch (c) {
            case '\r':
            case '\n':
                putchar('\n');
                goto done;
            case 0x20 ... 0x7f:
                linebuf[pos++] = c;
                putchar(c);
                break;
            default:
                break;
        }
    }
done:
    linebuf[pos] = '\0';
    return linebuf;
}


