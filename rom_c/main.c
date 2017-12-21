#include "uart_6850.h"

extern int foo(int);
extern int bar(int);

void puts(const char *str) {
    while (*str) {
        uart_write(*str++);
    }
}

int _main() {
    puts("hello\r\n");

    for (;;);
}
