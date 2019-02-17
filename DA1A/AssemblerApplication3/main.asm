;
; Lab1A-F19.asm
;
; Created: 2/9/2019 1:33:16 PM
; Author : Mohamad Jundi
;

LDI R24, 0x04 // Loading 16 bit number to register (multiplicand)
LDI R25, 0xD2 // Loading 16 bit number to register (multiplicand)
LDI R22, 0x0A // Loading 8 bit number to register (mutiplier)
LDI R20, 0    // Reserving register for storing result of 16 bit
LDI R19, 0    // Reserving register for storing result of 16 bit
LDI R18, 0    // Reserving register for storing result of 24 bit
LDI R26, 0    // Reserving register for carry addition

CPSE R22, R26 // Compare registers to make sure it is zero
JMP add_loop  // Jump to loop if not zero
LDI R16, 0    // load zero to register as place holder
JMP stop      // jump to stop if it is zero
add_loop:     // Loop begins for repeated adding
ADD R20, R25  // Adding 16 bit multiplicand, and storing into register
ADC R19, R24  // Carry adding 16 bit multiplicand, and storing into register
ADC R18, R26  // Carry adding 16 bit multiplicand for 24 bit result, and storing into register
DEC R22       // Decrementing multiplier until 0, so loop can stop
BRNE add_loop // Branching, add_loop will repeat until multiplier is 0.


// Verifying answer using MUL
LDI R30, 0    // Reserving register for storing verified result
LDI R29, 0    // Reserving register for storing verified result
LDI R28, 0    // Reserving register for storing verified result
LDI R22, 0x0A // Loading 8 bit number to register (mutiplier)

MUL R22, R25  // Multiply values of registers together and storing high bit in R1 and low bit in R0
ADD R30, R0   // Add low bit value from R0 and store into R30
ADC R29, R1   // Add high bit value from R1 with carry and store into R30

MUL R22, R24  // Multiply values of registers together and storing high bit in R1 and low bit in R0
ADD R29, R0   // Add low bit value from R0 and store into R29
ADC R28, R1   // Add high bit value from R1 and store into R28

stop:         // Stop running program
BREAK