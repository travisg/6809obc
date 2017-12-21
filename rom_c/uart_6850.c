
#define UART_ADDR 0xa000

static inline void uart_reg_write(unsigned int offset, char c) {
    *(volatile char *)(UART_ADDR + offset) = c;
}

void uart_write(char c) {
    uart_reg_write(1, c);
}
