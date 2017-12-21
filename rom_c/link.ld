# linker script
define basesympat _section_start_%s
define lensympat _section_len_%s

section .start load 0xc000
section .text
section .data
section .bss high 0x8000
section .vectors load 0xfff0

