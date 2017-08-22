TITLE fibonacci	(fibonacci.asm)

; Name:		Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description:	Program calculates a fibonacci number 1-46 

INCLUDE Irvine32.inc

.data
intro	BYTE		"Fibonacci Numbers by Jake Skinner",13,10,0
extra1	BYTE		"EC1: Display the numbers in aligned columns",13,10,0
prompt1	BYTE		"What is your name? ",0
usename	BYTE	20	DUP(?)
greet	BYTE		"Hello, ",0
prompt2	BYTE		"Ender the number of Fibonacci terms to be displayed.", 13, 10
prompt3	BYTE		"Please choose a number between 1 & 46: ", 0
limit	=		46
count	DWORD	?
small	BYTE		"Number is too small. Try again: ", 0
large	BYTE		"Number is too large. Try again: ", 0
num1		DWORD	1
num2		DWORD	0
countup	DWORD	0
spacer	BYTE		09, 0
goodbye	BYTE		"Goodbye!", 13, 10, 0

.code
main PROC
	
	; Write introduction
	mov		edx, OFFSET intro
	CALL		WriteString

	; Write extra1
	mov		edx, OFFSET extra1
	call		WriteString

	; Prompt user for usename
	mov		edx, OFFSET prompt1
	CALL		WriteString

	; Read user input for usename
	mov		edx, OFFSET usename
	mov		ecx, SIZEOF usename
	CALL		ReadString

	; Write greet + usename
	mov		edx, OFFSET greet
	CALL		WriteString
	mov		edx, OFFSET usename
	CALL		WriteString
	CALL		CrLf
	
	; Prompt user for count
	mov		edx, OFFSET prompt2
	CALL		WriteString
	
TryAgain:
	; Read user input for count
	CALL		ReadDec

	; POST TEST LOOP
	CMP		eax, 0
	JLE		TooSmall
	CMP		eax, limit
	JG		TooLarge
	JMP		InRange

TooSmall:
	; Input is too small, try again
	mov		edx, OFFSET small
	CALL		WriteString
	JMP		TryAgain

TooLarge:
	; input is too large, try again
	mov		edx, OFFSET large
	CALL		WriteString
	JMP		TryAgain

InRange:
	; move input to count register (ecx)
	mov		ecx, eax

displayFibs:
	; Calculate the next Fibonnaci number
	mov		eax, num1
	call		WriteDec

	; Space numbers in columns
	mov		edx, OFFSET spacer
	call		WriteString
	cmp		countup, 35
	jl		dbltab
	jmp		onetab

dbltab:
	call		WriteString

onetab:
	mov		ebx, num2
	mov		num2, eax
	add		eax, ebx
	mov		num1, eax

	; Increment to determine if new line
	mov		eax, countup
	inc		eax
	mov		countup, eax
	mov		ebx, 5
	sub		edx, edx
	div		ebx
	cmp		edx, 0
	jne		LpFib
	
	call		CrLf

LpFib:
	; Loop until ecx counter reaches 0
	loop		displayFibs

	; Farewell
	call		CrLf
	mov		edx, OFFSET goodbye
	call		WriteString

	exit
main ENDP

END main