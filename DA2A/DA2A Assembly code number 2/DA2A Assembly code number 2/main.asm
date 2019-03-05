.ORG 0

LDI R17, 5           // For prescaler to be 1024
LDI R18, 4           // For PC2 be input
LDI R24, 0           // For turning LED off

STS TCCR1B, R17      // Set clock prescaler 
SBI DDRB, 2          // P02 is set to output

INPUT:               // Input loop
IN R20, PINC         // PINC is set to input
AND R20, R18          // OR value of R20 and R18
CP R20, R18          // Compare values or R20 and R18
BREQ START           // Branch if equal to START LOOP
RJMP INPUT           // Jump back to INPUT if values don't match

START:               // Start loop to load high and low values
LDI R21, 0           // Used to set R21 back to 0
STS TCNT1H, R21      // Load high bits from R21
STS TCNT1L, R21      // Load low bits from R21
SBI PORTB, 2         // PB2 is output

LED_ON1:
LDS R22, TCNT1H      // Load upper bits to R22
LDS R23, TCNT1L      // Load lower bits to R21
CPI R23, 0x25        // Compare lower bits
BRSH LED_ON2         // Branch to LED_ON2 if lower bits exceed value 

LED_ON2:
CPI R22, 0x26        // Compare high bits
BRLT LED_ON1         // Branch back to LED_ON1 if less than given value

RESTART:
OUT PORTB, R24       // PORTB is OFF
RJMP INPUT           // Jump back to INPUT loop, ready for button to be pressed
