    SECTION .start

_start EXPORT
_start:
    lds #0x8000     ; set up the stack pointer
    jsr __main
    bra .

    ENDSECTION
