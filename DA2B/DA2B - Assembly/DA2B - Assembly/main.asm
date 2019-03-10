.include <m328pdef.inc>
.ORG 0                   // This is the location for the reset
JMP MAIN                 // Jump to Main loop

.ORG 0x02                // This is the location for the external interrupt 0
JMP EX0_ISR              // Jump to EX0_ISR loop

MAIN:            
LDI R16, HIGH(RAMEND)    // Load high bits from last memory location in SRAM
OUT SPH, R16             // Store high bits from R20 to Stack Pointer High
LDI R20, LOW(RAMEND)     // Load low bits from last memory location in SRAM
OUT SPL, R16             // Store high bits from R20 to Stack Pointer High

LDI R16, 0X2             // Load the value 0x2 to R20
STS EICRA, R16           // 0x2 set to the register so falling edge of INT0 
SBI DDRB, 5              // Store bit 5 to light up PB5
LDI R17, 0XFF            // Load value 0xFF to R17
OUT PORTB, R17           // Used to turn off all LEDs
SBI PORTD, 2             // Store bit 2 to use PD2 as pin
LDI R16, 1<<INT0         // Enable INT0 to R20
OUT EIMSK, R16           // Enable external interrupt zero
SEI                      // Used to enable interrupts

HERE: JMP HERE           // Jump to HERE

EX0_ISR:                 // Start of Loop EX0_ISR
IN R21, PORTB            // Input from portB
LDI R22, (1<<5)          // PB5 is the output LED loaded into R22
EOR R21, R22             // XOR both the registers
OUT PORTB, R21           // Output value from R21 to PORTB
RCALL delay_4_1_25s
RETI                    


// Begin code for all delays, used to achieve a delay of 1.25s
delay_4_1_25s:
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms
RCALL delay_4_100ms


delay_4_100ms:
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms
RCALL delay_4_10ms


delay_4_10ms:
RCALL delay_s
RCALL delay_s
RCALL delay_s
RCALL delay_s

delay_s:
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms
RCALL delay_4_2_5ms

delay_4_2_5ms:
PUSH R19              // Push R19 on stack
LDI R19, 243          // load value of 243, number of times to loop
delay_spread1:
NOP                   //
NOP                   //
NOP                   // NO OPERATION, used to waste time
NOP                   //
NOP                   //
DEC R19               // Decrement R19 value
BRNE delay_spread1    // Branch back to begining of loop
POP R19               // Pop R19 from stack
RET