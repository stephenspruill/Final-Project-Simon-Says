@Author: Liam Tang
@date: 05/12/18
@wait function waits in number of micro seconds
.globl Wait
Wait:
@=================================================
@Setup stack frame
@=================================================
	push {r7,lr}		
	mov r7,sp
	push {r1-r5}

@=================================================
@Function logic
@=================================================
@initialize for readablility
	arg .req r0
	base .req r1
	stamp1 .req r2
	elapsed .req r3
	delay .req r4
	start .req r5
@=================================================
@arg is number of micro seconds to wait passed in 
@with r0(arg)
@=================================================
	mov delay,arg
	.unreq arg	
@=================================================
@load base(r1) with base address of system timer
@=================================================
	ldr base,=0x3f003000

	mov start,#0			@start at 0
	mov elapsed,#0			@set to 0 for later

	ldrd stamp1,elapsed,[base,#4]	@get lo word of system timer and put in stamp1 and get hi word of system timer and put in elapsed
	@get time stamp

	mov start,stamp1		@place initial time stamp in start
@=================================================
@Wait loop
@=================================================
	w_loop:
		ldrd stamp1,elapsed,[base,#4]	@get time stamp again
		sub elapsed,stamp1,start	@subtract current time(stamp1) from start time and put in elapsed
		cmp elapsed,delay		@compare elapsed with delay
		bls w_loop
	
	@=========================================
	@function cleanup
	@=========================================
	.unreq elapsed
	.unreq base
	.unreq stamp1	
	.unreq delay
	.unreq start
	pop {r1-r5}
	pop {r7,pc}

