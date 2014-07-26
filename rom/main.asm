; vim: ts=4 sw=4 expandtab:
    .title  6809 rom

stacktop = 0x8000

    .area rom (ABS)

; zero page vars
    .org    0x0
ATESTVAR:   .rmb    2
ATESTVAR2:  .rmb    2

; start of rom
     .org   0xc000
rombase:
    lds     #stacktop

    ; configure the uart
    bsr     uart_config

    ; display a nice welcome screen
    ldx     #welcome_str
    bsr     uart_write_string

romloop:
    ldx     #prompt_str
    bsr     uart_write_string

.readloop:
    bsr     uart_read

    cmpa    #'\r
    beq     .endofline

.echo:
    bsr     uart_write
    bra     .readloop

.endofline:
    bsr     uart_write
    lda     #'\n
    bsr     uart_write

    bra     romloop

unhandled_vector:
    bra     .

welcome_str:
    .asciz "welcome to the computer\r\n"
prompt_str:
    .asciz "> "

; vim: syntax=as6809:
