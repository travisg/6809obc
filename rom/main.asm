; vim: ts=4 sw=4 expandtab:
    .title  6809 rom

stacktop = 0x8000

; start of rom
    .area rom (ABS)
    .org 0xc000

rombase:
    lds     #stacktop

; configure the uart
    bsr     uart_config

romloop:
    lda     #'a
    bsr     uart_write
    lda     #'b
    bsr     uart_write
    lda     #'c
    bsr     uart_write
    lda     #0xd
    bsr     uart_write
    lda     #0xa
    bsr     uart_write


;    ldx     #0x0
;    bsr     memtest_bank
;    ldx     #0x4000
;    bsr     memtest_bank
;    ldx     #0x8000
;    bsr     memtest_bank
;    ldx     #0x8800
;    bsr     memtest_bank
;    ldx     #0x9000
;    bsr     memtest_bank
;    ldx     #0x9800
;    bsr     memtest_bank
;    ldx     #0xa000
;    bsr     memtest_bank
;    ldx     #0xa800
;    bsr     memtest_bank
;    ldx     #0xb000
;    bsr     memtest_bank
;    ldx     #0xb800
;    bsr     memtest_bank

;    ldx     #0xc000
;    bsr     memtest_bank
;    ldx     #0xd000
;    bsr     memtest_bank
;    ldx     #0xe000
;    bsr     memtest_bank
;    ldx     #0xf000
;    bsr     memtest_bank

    bra     romloop

    ; test a bank of memory, address passed in X
memtest_bank:
    ; write value out and read it back
    lda     #0x1

.memtest_bank_loop:
    sta     ,x
    ldb     ,x
    lsla
    bne     .memtest_bank_loop

    rts

unhandled_vector:
    bra     .

