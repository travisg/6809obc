#include <compiler.h>

extern void _main(void);

__NAKED __SECTION(".start")
void start(void) {
    asm volatile("lds _section_start_.bss");
    _main();
    for (;;);
}

