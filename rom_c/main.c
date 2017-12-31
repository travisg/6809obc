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
    return 0;
}

char *readline() {
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

uint16_t parse_hex_digit(const char *str, char *len_found) {
    uint16_t val = 0;
    *len_found = 0;

    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            (*len_found)++;
            val <<= 4;
            val += *str - '0';
        } else if (*str >= 'A' && *str <= 'F') {
            (*len_found)++;
            val <<= 4;
            val += *str - 'A' + 0xa;
        } else {
            break;
        }
        str++;
    }

    return val;
}

static uint16_t dump_memory(uint16_t addr) {
    uint8_t *ptr = (uint8_t*)addr;

    char i;
    for (i = 0; i < 16; i++) {
        put_hex16(addr); puts(": ");
        char j;
        for (j = 0; j < 16; j++) {
            put_hex8(*ptr++);
            putchar(' ');
        }
        addr += j;
        putchar('\n');
    }

    return 0x100;
}

static void do_command() {
    puts("\n# ");

    // read the line
    char *line = readline();

    // trim on the left
    while (*line == ' ')
        line++;

    // look for a command character next
    char cmd;
    bool readmem;
    switch (line[0]) {
        case 'M': // inspect memory
            cmd = line[0];
            line++;
            readmem = true;
            break;
        default:
            puts("\nunrecognized command");
            return;
    }

    // parse a memory address
    static uint16_t lastmem;
    uint16_t mem = 0;
    if (readmem) {
        char found;
        mem = parse_hex_digit(line, &found);
        line += found;
        if (found > 0) {
            lastmem = mem;
        } else {
            mem = lastmem;
        }
    }

    switch (cmd) {
        case 'M': // inspect memory
            lastmem += dump_memory(mem);
            break;
    }
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
