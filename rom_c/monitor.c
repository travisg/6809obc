#include "monitor.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "io.h"

static uint16_t parse_hex_digit(const char *str, char *len_found) {
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

    return addr;
}

void monitor_do_command(void) {
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
            lastmem = dump_memory(mem);
            break;
    }
}


