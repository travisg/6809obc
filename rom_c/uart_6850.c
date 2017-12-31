#include "uart_6850.h"

#include <stdint.h>
#include <stddef.h>

#define UART_ADDR 0xa000

#define STAT_RDRF (1<<0)
#define STAT_TDRE (1<<1)
#define STAT_DCD  (1<<2)
#define STAT_CTS  (1<<3)
#define STAT_FE   (1<<4)
#define STAT_OVRN (1<<5)
#define STAT_PE   (1<<6)
#define STAT_IRQ  (1<<7)

static inline void uart_reg_write(size_t offset, char c) {
    *(volatile char *)(UART_ADDR + offset) = c;
}

static inline char uart_reg_read(size_t offset) {
    return *(volatile char *)(UART_ADDR + offset);
}

void uart_write(char c) {
    uart_reg_write(1, c);
}

int uart_read(void) {
    char stat = uart_reg_read(0);
    if ((stat & STAT_RDRF) == 0)
        return -1;

    return uart_reg_read(1);
}
