#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "uart_6850.h"
#include "monitor.h"

void _main(void) {
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
        monitor_do_command();
    }
}
