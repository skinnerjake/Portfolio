TITLE basicArithmetic	(basicArithmetic.asm)

; Name:		Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description:	Program demonstrates basic integer arithmetic using assembly language

INCLUDE Irvine32.inc

.data
intro	BYTE		"Simple Operations by Jake Skinner",13,10,0
xtracr1	BYTE		"**EC1: Repeat until user chooses to quit",13,10
xtracr2	BYTE		"**EC2: Validate the second number to be less than the first",13,10,0
prompt1	BYTE		"Enter two numbers and get their sum, difference, product, quotient, and remainder:",13,10,0
getNum1	BYTE		"Number 1: ",0
getNum2	BYTE		"Number 2: ",0
warning	BYTE		"0 < Num2 <= Num1; try again:",13,10,0
output1	BYTE		"Sum: ",0
output2	BYTE		"Difference: ",0
output3	BYTE		"Product: ",0
output4	BYTE		"Quotient: ",0
output5	BYTE		"Remainder: ",0
goodbye	BYTE		"Goodbye!",13,10,0
doAgain	BYTE		"Would you like to repeat? 1 for yes, or 0 for no: ",0
num1		DWORD	?
num2		DWORD	?
result	DWORD	?
choice	DWORD	?

.code
main PROC

	; Write introduction and extracredit
	mov		edx, OFFSET intro
	CALL		WriteString
	mov		edx, OFFSET xtracr1
	CALL		WriteString

	; Repeat until user is finished
l1:
	CALL		RunNumbers
	mov		edx, OFFSET doAgain
	CALL		WriteString
	CALL		ReadDec
	mov		ecx, eax
	cmp		ecx,0
	jne		l1

	; Farewell and close process
	mov		edx, OFFSET goodbye
	CALL		WriteString

	exit
main ENDP

; Procedure takes 2 integers and writes sum, difference, etc.
RunNumbers PROC
	; Write the first prompt
	mov		edx, OFFSET prompt1
	CALL		WriteString

	; Get first number
	mov		edx, OFFSET getNum1
	CALL		WriteString
	CALL		ReadDec
	mov		num1,eax

tryAgain:
	; Get second number
	mov		edx,OFFSET getNum2
	CALL		WriteString
	CALL		ReadDec
	cmp		eax,num1
	jg		NotValid
	cmp		eax,0
	jne		Valid

NotValid:
	mov		edx,OFFSET warning
	CALL		WriteString
	jmp		tryAgain

Valid:
	;continue
	mov		num2,eax

	; Calculate sum
	mov		eax,num1
	add		eax,num2
	mov		result,eax

	; Write the sum
	mov		edx, OFFSET output1
	CALL		WriteResult

	; Calculate difference
	mov		eax,num1
	sub		eax,num2
	mov		result,eax

	; Write difference
	mov		edx, OFFSET output2
	CALL		WriteResult

	; Calculate product
	mov		eax, num1
	mul		num2
	mov		result, eax

	; Write product
	mov		edx, OFFSET output3
	CALL		WriteResult

	; Calculate quotient and remainder
	sub		edx,edx
	mov		eax,num1
	mov		ebx,num2
	div		ebx
	mov		result,eax
	mov		ebx,edx

	; Write quotient
	mov		edx, OFFSET output4
	CALL		WriteResult

	; Calculate remainder
	mov		result,ebx

	; Write remainder
	mov		edx, OFFSET output5
	CALL		WriteResult

	ret
RunNumbers ENDP

; Procedure to write sum, difference, etc.
WriteResult PROC
	mov		eax, result
	CALL		WriteString
	CALL		WriteDec
	CALL		CrLf
	ret
WriteResult ENDP

END main