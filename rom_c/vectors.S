    SECTION .vectors

_start EXTERN

_vectors:
    FDB 0 ;reserved
    FDB 0 ; swi3
    FDB 0 ; swi2
    FDB 0 ; FIRQ
    FDB 0 ; IRQ
    FDB 0 ; SWI
    FDB 0 ; NMI
    FDB _start ; reset

    ENDSECTION
