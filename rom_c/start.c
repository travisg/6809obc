#include <compiler.h>

__NAKED __SECTION(".start")
void start(void) {
    asm volatile("lds _section_start_.bss");
    asm volatile("jsr __main");
    for (;;);
}

