    .area   vectab (ABS)
    .org    0xfff0

.globl vectab
vectab:
    .word   unhandled_vector  ; reserved
    .word   unhandled_vector  ; swi3
    .word   unhandled_vector  ; swi2
    .word   unhandled_vector  ; firq
    .word   unhandled_vector  ; irq
    .word   unhandled_vector  ; swi
    .word   unhandled_vector  ; nmi
    .word   rombase           ; reset



