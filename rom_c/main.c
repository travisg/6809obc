#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "uart_6850.h"

static const char *hexval = "0123456789abcdef";

static void put_hex_prefix() {
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

uint8_t read_num_8() {


}

char *readline() {
    static char linebuf[256];
    uint8_t pos = 0;

    // read a line of characters
    while (pos < 255) {
        int c = getchar();
        switch (c) {
            case '\r':
            case '\n':
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


static void do_command() {
    puts("\n# ");

    // read the command char
    char *line = readline();
    puts(line);
#if 0
    char cmd;
    bool readmem;
    for (;;) {
        int c = getchar();
        putchar(c);

        switch (c) {
            case 'M': // inspect memory
                cmd = c;
                readmem = true;
                break;
            case '\r':
            case '\n':
                return;
            case ' ':
                continue;
            default:
                puts("\nunrecognized command");
                return;
        }
    }

    if (readmem) {
        uintptr_t mem = 0;

        int c = getchar();
        putchar(c);
    }
#endif


}

int _main() {
    puts("welcome\n\n");

#if 0
    put_hex8(sizeof(char));
    put_hex8(sizeof(short));
    put_hex8(sizeof(int));
    put_hex8(sizeof(long));
    put_hex8(sizeof(long long));
    put_hex8(sizeof(size_t));
    put_hex16(0x1234);
    putchar('\n');
#endif

    for (;;) {
        do_command();
    }
}
