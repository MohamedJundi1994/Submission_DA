
.org 0

LDI R16, 4        // Used to light up LED(PB2)
OUT DDRB, R16     // PB2 LED is output
LDI R17, 0        // For set or reset of LED (PB2)
LDI R18, 5        // Clock prescaler is set to 1024
STS TCCR1B, R18   // Store prescaler to data space

Loop1:
LDI R18, 0x00     // Reset the counter to 0
STS TCNT1H, R18   // Store high bits from R18
STS TCNT1L, R18   // Store low bits from R18

RCALL DelayON
EOR R17, R16      // XOR to toggle LED
OUT PORTB, R17    // Output value of R17 on PORTB

LDI R18, 0x00     // Reset the counter to 0
STS TCNT1H, R18   // Store high bits from R18
STS TCNT1L, R18   // Store low bits from R18

RCALL DelayOFF
EOR R17, R16      // XOR to toggle LED
OUT PORTB, R17    // Output value of R17 on PORTB

RJMP Loop1        // Repeat Loop1

DelayOFF:
LDS R19, TCNT1H   // Load upper bits of counter to R19
LDS R20, TCNT1L   // Load lower bits of counter to R20
CPI R20, 0xB2     // Compare lower 8 bits of counter to R20
BRSH LoopOFF      // If the lower bits are equal to inputted amount, go to DelayOFF
RJMP DelayOFF   

LoopOFF:
CPI R19, 0x11     // Check upper bits to inputted amount
BRLT DelayOFF     // Branch if less than the inputted amount
RET               // Return from Subroutine

DelayON:
LDS R19, TCNT1H   // Load upper bits of counter to R19
LDS R20, TCNT1L   // Load lower bits of counter to R20
CPI R20, 0x8C     // Compare lower 8 bits of counter to R20
BRSH LoopON       // If the lower bits are equal to inputted amount, go to upper bits
RJMP DelayON

LoopON:
CPI R19, 0x1A     // Check upper bits to inputted amount
BRLT DelayON      // Branch if less than the inputted amount
RET               // Return from Subroutine
