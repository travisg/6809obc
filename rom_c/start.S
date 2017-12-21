    SECTION .start

_start EXPORT
_start:
    lds _section_start_.bss ; set up the stack pointer just below bss
    jsr __main
    bra .

    ENDSECTION
