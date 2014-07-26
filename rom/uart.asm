    .area rom (ABS)

; uart registers
uart_base   = 0x8000
uart_rbr    = uart_base + 0 ; receiver buffer
uart_thr    = uart_base + 0 ; transmitter hold
uart_ier    = uart_base + 1 ; interrupt enable
uart_iir    = uart_base + 2 ; interrupt ident
uart_fcr    = uart_base + 2 ; fifo control
uart_lcr    = uart_base + 3 ; line control
uart_mcr    = uart_base + 4 ; modem control
uart_lsr    = uart_base + 5 ; line status
uart_msr    = uart_base + 6 ; modem status
uart_scr    = uart_base + 7 ; scratch
uart_dll    = uart_base + 0 ; divisor latch low
uart_dlm    = uart_base + 1 ; divisor latch high

uart_config:
    ; config for n81
    lda     #0x80 ; DLAB
    sta     uart_lcr

    ; divisor bits active, div 2 (115200 at 1.8432Mhz)
    lda     #0x1
    sta     uart_dll
    lda     #0
    sta     uart_dlm

    ; set n81, clear divisor bits
    lda     #0x03; n81
    sta     uart_lcr

    ; disable fifo
    lda     #0x0
    sta     uart_fcr

    ; disable interrupts
    sta     uart_ier

    rts

uart_write:
    ldb     uart_lsr
    andb    #0x20       ; test if transmitter hold is empty
    beq     uart_write  ; if bit is clear, loop
    sta     uart_thr
    rts

uart_read:
    ldb     uart_lsr
    andb    #0x01       ; data ready?
    beq     uart_read   ; if bit is clear, loop
    lda     uart_rbr
    rts

uart_write_string:
    lda     ,x+
    cmpa    #0
    beq     .uart_write_string_done
    bsr     uart_write
    bra     uart_write_string

.uart_write_string_done:
    rts

; vim: syntax=as6809:
