TITLE average	(average.asm)

; Name:		Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description:	Take negative integer input and return the average

INCLUDE Irvine32.inc

.data
intro	BYTE		"Average Negative Integers by Jake Skinner",13,10,0
extra1	BYTE		"EC1: Number the lines during user input",13,10,0
prompt1	BYTE		"What is your name? ",0
usename	BYTE	20	DUP(?)
greet	BYTE		"Hello, ",0
prompt2	BYTE		"Input a number from -100 to -1. Input a non-negative integer to stop.",13,10,0
tooLow	BYTE		"Input was less than -100. Try again.",13,10,0
number	BYTE		"Number ",0
colon	BYTE		": ",0
sum		SDWORD	0
count	SDWORD	1
average	SDWORD	?
noinput	BYTE		"You input no numbers. Cannot divide by zero.",13,10,0
output1	BYTE		"You entered ",0
output2	BYTE		" numbers.",13,10,0
output3	BYTE		"The rounded average is ",0
goodbye1	BYTE		"Thank you, ",0
goodbye2	BYTE		"! Have a nice day.",13,10,0

; Constant for lower limit
LOWER = -100


.code
main PROC

	; Write introduction
	mov		edx, OFFSET intro
	call		WriteString

	; Write extracredit
	mov		edx, OFFSET extra1
	call		WriteString

	; Prompt user for usename
	mov		edx, OFFSET prompt1
	call		WriteString

	; Read user input for usename
	mov		edx, OFFSET usename
	mov		ecx, SIZEOF usename
	call		ReadString

	; Write greet + usename + instructions
	mov		edx, OFFSET greet
	call		WriteString
	mov		edx, OFFSET usename
	call		WriteString
	call		CrLf
	mov		edx, OFFSET prompt2
	call		WriteString

INPUT:		; loop for input

	; Get input
	call		LineNumber
	call		ReadInt

	; Validate input is greater than or equal to lower limit
	cmp		eax, LOWER
	jge		VALID

	; Prompt user and get new input if current input is too low
	mov		edx, OFFSET tooLow
	call		WriteString
	jmp		INPUT

VALID:
	cmp		eax, 0
	jge		CALCULATE

	add		sum,eax
	inc		count
	jmp		INPUT

CALCULATE:	; Finish taking input and calculate
	dec		count
	cmp		count,0
	je		DIVZERO
	jmp		DIVIDE

DIVZERO:		; no inputs, cannot divide by zero
	call		ValidNums
	mov		edx, OFFSET noinput
	call		WriteString
	call		Farewell
	exit

DIVIDE:
	; Extend doubleword (EAX) to quadword (EDX:EAX) and divide
	call		CrLf
	mov		eax, sum
	cdq
	idiv		count
	mov		average, eax

	; Calculate round using count and remainder
	mov		eax, count
	add		eax, edx
	cmp		eax, edx
	jg		PRINT

	; Round average up if remainder is over half
	dec		average

PRINT:		; jump if not incrementing

	; Print number of valid inputs
	call		ValidNums

	; Print message with rounded average of inputs
	mov		eax, average
	mov		edx, OFFSET output3
	call		WriteString
	call		WriteInt
	call		CrLf
	
	; Write farewell message
	call		Farewell

	exit
main ENDP

Farewell PROC
	; Farewell
	mov		edx, OFFSET goodbye1
	call		WriteString
	mov		edx, OFFSET usename
	call		WriteString
	mov		edx, OFFSET goodbye2
	call		WriteString
	ret
Farewell ENDP

LineNumber PROC

	; Function outputs 'Number #: '
	mov		eax,count
	mov		edx, OFFSET number
	call		WriteString
	call		WriteDec
	mov		edx, OFFSET colon
	call		WriteString
	
	ret
LineNumber ENDP

ValidNums PROC
	; Print message with number of inputs
	mov		eax, count
	mov		edx, OFFSET output1
	call		WriteString
	call		WriteDec
	mov		edx, OFFSET output2
	call		WriteString
	ret
ValidNums ENDP

END main