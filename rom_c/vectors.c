#include <compiler.h>

extern void start(void);

__SECTION(".vectors")
void *vectors[] = {
    0, // reserved
    0, // swi3
    0, // swi2
    0, // FIRQ
    0, // IRQ
    0, // swi
    0, // NMI
    start // reset
};
