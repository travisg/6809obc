# linker script
section .vectors load 0xfff0
section .start load 0xc000
section .text
section .data
section .bss high 0xc000

