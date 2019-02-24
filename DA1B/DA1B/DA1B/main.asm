;
; LAB1B-S19.asm
;
; Created: 2/22/2019 5:04:23 PM
; Author : moham
;

.ORG 0							
	LDI XL, low(0x0200)  // Load low bits of memory location 0x200 into XL
	LDI XH, high(0x200)  // Load high bits of memory location 0x200 into XH
	LDI YL, low(0x400)   // Load low bits of memory location 0x400 into YL
	LDI YH, high(0x400)  // Load high bits of memory location 0x400 into YH
	LDI ZL, low(0x600)   // Load low bits of memory location 0x600 into ZL
	LDI ZH, high(0x600)  // Load high bits of memory location 0x600 into ZH

	// Start

	LDI R20, 34                 // Load value 34 into R20, used as start number > 10
	LDI R22, 0                  // Load 0 into R22, used for carry addition
	loopx:                      // Loop to store values into X and begin check
		ST X+, R20              // Store values of R20 into X register, and then increment
		MOV R21, R20            // Move value of R20 into R21, used for division
			
			div3:               // Loop to check if divisible by 3
				CPI R21, 3      // Compare if value R21 with 3
				BRLT less       // Branch to less if R21 is less than 3
				SUBI R21, 3		// Subtract 3 from value of R21	
				CPI R21, 3      // Compare if value R21 with 3
				BREQ equal      // Branch to equal if equal to 3
				BRNE div3       // Branch to div3 for repetition otherwise

			less:               // less is used to store values into Z register, used for not divisible numbers
				ST Z+, R20      // Store value of R20 into Z register
				ADD R19, R20    // Add value of R20 to R19 and store.
				ADC R18, R22    // Add in the carry as well
				rjmp skip       // Jump to skip when complete to avoid next loop
			
			equal:              // equal is to store values into Y register, used for divisible numbers
				ST Y+, R20      // Store value of R20 into Y register
				ADD R17, R20    // Add value of R20 to R17 and store.
				ADC R16, R22    // Add in the carry as well

		skip:                   // skip is used at end of program for incrementation branching
		INC R20                 // Used to increment R20 value
		CPI R20, 133            // Compare R20 value to 133 
		BRNE loopx              // branch to loopx if R20 value is not 133

BREAK                           // Stop program when value of R20 is 133

	