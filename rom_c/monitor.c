#include "monitor.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "io.h"

#define MAX_TOKENS 8

static uint16_t lastmem;

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

static void dump_memory(uint16_t addr) {
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

    lastmem = addr;
}

// break the line into one or more tokens, stuffing nulls
static uint8_t tokenize(char *line, char **tokens) {
    uint8_t count = 0;
    uint8_t pos = 0;

next:;
    char c = line[pos];
    if (c == 0) {
        // we're done
        goto done;
    } else if (c == ' ') {
        // eat subsequent spaces
        line[pos++] = 0; // null stuff
        goto next;
    } else { // start of a token
        if (count == MAX_TOKENS)
            goto done;

        // record this token's starting address
        tokens[count++] = &line[pos++];

        // eat printables until a space or end of string
        for (;;) {
            c = line[pos];
            if (c == ' ' || c == 0)
                goto next;
            pos++;
        }
    }

done:
    return count;
}

void monitor_do_command(void) {
    puts("\n# ");

    // read the line
    char *line = readline();

    char *token[MAX_TOKENS];
    uint8_t num_tokens = tokenize(line, token);
    if (num_tokens == 0)
        return;

    // debug dump the tokens
    if (false) {
        put_hex8(num_tokens);
        putchar('\n');
        for (uint8_t i = 0; i < num_tokens; i++) {
            put_hex16((uint16_t)token[i]);
            putchar(' ');
            puts(token[i]);
            putchar('\n');
        }
    }

    if (strcmp(token[0], "MEM") == 0) {
        uint16_t mem;
        if (num_tokens > 1) {
            char found;
            mem = parse_hex_digit(token[1], &found);
            if (found > 0) {
                lastmem = mem;
            } else {
                mem = lastmem;
            }
        } else {
            mem = lastmem;
        }

        dump_memory(mem);
    } else if (strcmp(token[0], "HELP") == 0) {
        puts("HELP:\n"
             "MEM <ADDRESS>   : dump memory at address, leave blank for last address\n"
             );
    } else {
        puts("unrecognized command\n");
    }
}


