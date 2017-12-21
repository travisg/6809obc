#include <stdint.h>
#include <stddef.h>

#include "uart_6850.h"

void putchar(char c) {
    if (c == '\n')
        uart_write('\r');
    uart_write(c);
}

void puts(const char *str) {
    while (*str) {
        putchar(*str++);
    }
}

int getchar() {
    int c;
    while ((c = uart_read()) < 0)
        ;

    return c;
}

void *memcpy(void *dest, const void *src, size_t count) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    if (count == 0 || dest == src)
        return dest;

    for (; count > 0; count--)
        *d++ = *s++;

    return dest;
}

void *memset(void *dest, int c, size_t count) {
    char *d = (char *)dest;

    for (; count > 0; count--)
        *d++ = c;

    return dest;
}

#if 0
__attribute__((noreturn))
void abort() {
    puts("abort\n");
    for (;;);
}

void *malloc(size_t len) {
    // satisfy libgcc
    abort();
}
#endif


