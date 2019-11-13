.global main
main:
	SUB sp, sp, #16			//Create 16 bytes storage
	LDR R0, .addr_file		//get GPIO Controller addr
	LDR R1, .flags			//set flag permissions
	BL open					//call to get file handle
	
	STR R0, [SP, #12]		//file handle number
	LDR R3, [SP, #12]		//get file handle
	STR R3, [SP, #0]		//store file handle on top of stack
	LDR R3, .gpiobase		//get GPIO_Base address
	STR R3, [SP, #4]		//store on SP+4
	MOV R0, #0				//R0=0
	MOV R1, #4096			//R1=page
	MOV R2, #3				//R2=3
	MOV R3, #1				//R3=1 (stdouts)
	BL mmap
	
	STR R0, [SP, #16]		//store virtual mem addr
	LDR R3, [SP, #16]		//get virtual mem addr
	ADD R3, R3, #8			//add 8 for block 2
	LDR R2, [SP, #16]		//get virtual mem addr
	ADD R2, R2, #8			//add 8 for block 2
	LDR R2, [R2, #0]		//load R2 with value at R2
	BIC R2, R2, #0B001<<6	//bitwise clear of three bits
	STR R2, [R3, #0]		//store result [set input]
	LDR R3, [SP, #16]		//get virtual mem addr
	ADD R3, R3, #8			//add 8 for block 2
	LDR R2, [SP, #16]		//get virtual mem addr
	ADD R2, R2, #8			//add 8 for block 2
	LDR R2, [R2, #0]		//load R2 with value at R2
	ORR R2, R2, #1<<0		//set bit...
	STR R2, [R3, #0]		//...and make output
	LDR R3, [SP, #16]		//get virtual mem addr
	ADD R3, R3, #28			//add 28 offset to GPIO_Base
	MOV R4, #1				//get 1
	MOV R2, R4, LSL#20		//Shift by pin number
	STR R2, [R3, #0]		//write to memory
	LDR R0, [SP, #12]		//get file handle
	BL close
	
	ADD SP, SP, #16			//restore SP
	MOV R7, #1
	SWI 0
	
	.addr_file: .word .file
	.flags:		.word	1576962
	.gpiobase:	.word	0x3F200000
	
	.data
	
	.file:	.ascii "/dev/mem\000"
