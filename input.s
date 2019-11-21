b main

.section .text

main:

mov sp,#0x8000 		@this initializes the stack pointer to start after the 
			@.text section this allows us to use sp without any problems

@Author: Liam Tang
@date: 05/12/18
@desc: lights up leds direction depends on input
@=================================================
@Declare symbols
@=================================================
.equ BASE_ADDR,0x3f200000 	@Base address
.equ GPFSEL0,  0x0
.equ GPFSEL1,  0x04		@FSEL1 register offset | use to select GPIO 10-19 and set input/output/alt func
.equ GPFSEL2,  0x08		@FSEL2 register offset | use to select GPIO 20-29 and set input/output/alt func
.equ GPSET0,   0x1c		@GPSET0 register offset| use to set GPIO's logic level high(3.3v)
.equ GPCLR0,   0x28		@GPCLR0 register offset| use to set GPIO's logic level low(0v)
.equ GPLEV0,   0x34		@GPIO level offset     | use to read current level of pin(on/off)[high/low]{3.3v/0v}

.equ CLEAR_BITS21_23,0xFF1FFFFF @mask to clear bits 21 through 23 | use to set GPIO 17 to input
.equ SET_20_27,0x249249		@mask to set bits 20 through 27   | use to set GPIO 20-27 to output
.equ SET_BIT27,0x8000000	@mask to set bits 27   | use to set GPIO 27 to high(3.3v) or low(0v) GPIO 27 is indicator light
.equ half_second, 0x7a120	@hex value for half a second in milliseconds
.equ quarter_second, 0x3d090	@hex value for quarter of a second in milliseconds
.equ eighth_second,0x1e848	@hex value for eigth of a second in milliseconds

base .req r1			@Sets symbol base to refer to r1: can use base and r1 interchangeably base<=>r1
ldr base,=BASE_ADDR		@base = 0x3f20000, load base with the base address of peripherals

offset .req r2			@Sets symbol offset to refer to r2: can use offset and r2 interchangeably offset<=>r2
mask .req r3			@Sets symbol mask to refer to r3 mask<=>r3
i .req r4			@Sets symbol i to refer to r4 i<=>r4
j .req r5			@Sets symbol j to refer to r5 j<=>r5
return .req r0			@return <=> r0



@=================================================
@Set gpio 17 to input
@=================================================
ldr offset,=GPFSEL1
ldr mask,=CLEAR_BITS21_23
str mask,[base,offset]


@=================================================
@Set gpio 20 through 27 to output
@=================================================
ldr mask,=SET_20_27
ldr offset,=GPFSEL2
str mask,[base,offset]

@=================================================
@Input Loop Repeats forever:
@1. waits a little
@2. checks input state(GPIO 17)
@3. turns off/on indicator depending on input state
@	1. loop up through row of leds 
@	2. or loops down through leds depending on input state
@4. returns to input loop
@=================================================
input_loop:
	mov r0,#30000		
	bl Wait			@wait 30,000 microseconds

	mov mask,#17		@load args for proc
	push {mask}		@ push onto stack	
	bl getInput		@get input for pin 
					@result in r0

	cmp r0,#1		@compare r0 to #1
	bne turn_off_indicator @if pin is off turn on indicator
	beq turn_on_indicator@if pin is on turn on indicator
b input_loop

@=================================================
@Returns State of Input Pin(GPIO 17)
@ARGUMENTS:1
@number of pin
@Reads state of pin from GPLEV0
@and returns it in r0
@=================================================
 getInput:
	push {r7,lr}
	mov r7,sp
	push {r1-r5}
@--------Set up stack frame
	ldr r4,[r7,#8]
@--------For readability
	argument .req r4
	result .req r5
@--------get first arg
	mov mask,#1
	lsl mask,argument		@create mask based on argument
		
	ldr base,=BASE_ADDR	@addr of base peripherals
	ldr offset,=GPLEV0		@GPLEV holds pin states
	ldr result,[base,offset]		@access GPLEV0
	tst result,mask
	moveq r0,#0		@tst performs and. If result is 1 zero flag is not set(ne) 
	movne r0,#1		@if the result is zero, zero flag is set (eq)
@--------
	.unreq argument
	.unreq result
@------Destroy stack frame
	pop {r1-r5}				
	pop {r7,lr}
	add sp,sp,#4		@clean up argument on stack
	mov pc,lr		@return

@=================================================
@turns on indicator light
@=================================================
turn_on_indicator:
	ldr offset,=GPSET0
	ldr mask,=SET_BIT27
	str mask,[base,offset]
	b loop_up_set		@if indicator light is on branch to loop_up
@=================================================
@turns off indicator light
@=================================================
turn_off_indicator:
	ldr offset,=GPCLR0
	ldr mask,=SET_BIT27
	str mask,[base,offset]
	b loop_down_set		@if indicator light is off branch to loop_down

@=================================================
@Turns on GPIO Pin
@Accepts one argument:
@	arg1=>r0: pin number to turn on
@=================================================
turn_on:
	@turns on led
	@accepts pin number to turn on from pin 0-31	
	ldr offset,=GPSET0
	mov mask,#1
	lsl mask,r0
	str mask,[base,offset]
	mov pc,lr
@=================================================
@Turns off GPIO Pin
@Accepts one argument:
@	arg1=>r0: pin number to turn off
@=================================================
turn_off:
	@turns off led
	@accepts  pin numnber to turn off from pin 0-31
	ldr offset,=GPCLR0
	mov mask,#1
	lsl mask,r0
	str mask,[base,offset]
	mov pc,lr
@=================================================
@Setup looping variable i and j
@if going down sets j to 26 and loops to 20
@if going up set i to 20 and loops up to 26
@=================================================
loop_down_set:			@set up parameters for looping down
	mov j,#26	
	b loop_down
loop_up_set:			@ set up parameters for looping up
	mov i,#20
	b loop_up	
@=================================================
@Loops through Gpio pins and turns them on and off
@Loops from GPIO 20 to 26
@=================================================
loop_up:
	mov r0,i		@args to turn on pin
	bl turn_on		@turn on  pin
	@---------
	ldr r0,=eighth_second	@wait for an eigth of a second
	bl Wait			
	@---------
	mov r0,i		@args to turn offf pin
	bl turn_off		@turn off pin
	@---------
	cmp i,#25		@check for end of loop
	beq input_loop		@go back to input loop if at end
	add i,i,#1		@increment counter
	b loop_up		@loop back if not at end
@=================================================
@Loops through Gpio pins and turns them on and off
@Loops from GPIO 26 to 20
@=================================================
loop_down:			@same as loop_up but decrements
	mov r0,j
	bl turn_on
	@---------
	ldr r0,=eighth_second
	bl Wait
	@---------
	mov r0,j
	bl turn_off
	@--------
	cmp j,#19
	beq input_loop
	sub j,j,#1
	b loop_down





