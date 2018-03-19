; TODO INSERT CONFIG CODE HERE USING CONFIG BITS GENERATOR

RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program

; TODO ADD INTERRUPTS HERE IF USED

MAIN_PROG CODE                      ; let linker place main program

START
    PORTB equ 06h
    PORTC equ 07h
    TRISB equ 86h
    TRISC equ 87h
    STATUS equ 03h
    BSF STATUS,5
    MOVLW FFh
    MOVWF TRISB
    MOVLW 00h
    MOVWF TRISC
    MOVWF PORTC
    BCF STATUS,5

MAIN_LOOP
    
    MOVELW F0h
    ANDWF PORTB,1
    BTFSS PORTB,4
    GOTO AND_LOOP
    
XOR_LOOP
    MOVLW 00h
    MOVWF PORTC
    MOVLW FFh
    BTFSC PORTB,7
    MOVLW 80h
    RRF W,0
    XORWF PORTB,0
    RRF W,0
    XORWF PORTB,0
    BTFSC W,5
    GOTO LED_GLOW
    GOTO LED_OFF

AND_LOOP
    MOVLW 00h
    MOVWF PORTC
    BTFSC PORTB,7
    GOTO MAIN_LOOP
    BTFSC PORTB,6
    GOTO MAIN_LOOP
    BTFSC PORTB,5
    GOTO MAIN_LOOP
    GOTO LED_GLOW
    GOTO LED_OFF
    
LED_GLOW
    MOVLW FFh
    MOVWF PORTC
    GOTO MAIN_LOOP
    
LED_OFF
    MOVLW 00h
    MOVWF PORTC
    GOTO MAIN_LOOP
    
    GOTO $                 ; loop forever

    END