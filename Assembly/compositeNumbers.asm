TITLE compositeNumbers	(compositeNumbers.asm)

; Name:			Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description:	The program outputs a user-defined number of composite numbers

INCLUDE Irvine32.inc

.data
upperLimit = 400;
intro		BYTE		"Composite Numbers by Jake Skinner ", 13, 10, 0
extra		BYTE		"XC1: Align the output columns", 13, 10, 0
prompt1		BYTE		"Enter your name.", 13, 10, 0
greet		BYTE		"Hello, ", 0
prompt2		BYTE		"Input a number between 1-400:", 13, 10, 0
useName		BYTE	20	DUP(?)
count		DWORD	?
prompt3		BYTE		"You entered: ", 0
redo			BYTE		"Invalid input.", 13, 10, 0
tabin		BYTE		9,0
spacer		DWORD	0
linemax		DWORD	10
dividend		DWORD	3
divisor		DWORD	0
goodbye		BYTE		"Thanks for playing, ",0



.code

main PROC

	call		introduction
	call		getUserData
	call		showComposites
	call		farewell
	exit
main	ENDP


; function introduces the program and gets the user name
introduction PROC
	mov		edx, OFFSET intro
	call		WriteString
	mov		edx, OFFSET extra
	call		WriteString
	mov		edx, OFFSET prompt1
	call		WriteString
	mov		edx, OFFSET useName
	mov		ecx, SIZEOF useName
	call		ReadString
	mov		edx, OFFSET greet
	call		WriteString
	mov		edx, OFFSET useName
	call		WriteString
	call		CrLf

	ret
introduction ENDP


; function recieves user input and calls function to validate
getUserData PROC
	mov		edx, OFFSET prompt2
	call		WriteString

	call		ReadInt

	call		validate
	ret
getUserData ENDP


; function makes sure that input is within the correct range
; else, calls getUserData again
validate PROC
	cmp		eax, 0
	jle		NOTVALID

	cmp		eax, upperLimit
	jg		NOTVALID

	jmp		VALID

NOTVALID:
	mov		edx, OFFSET redo
	call		WriteString
	call		getUserData
	jmp		RETURN
	
VALID:
	mov		count, eax

RETURN:
	ret

validate ENDP


; Function prints out composite numbers
showComposites PROC
	mov		ecx, count

COMPOSITE:
	call		isComposite
	inc		dividend

	; jump to end of function if counter is zero
	jecxz	STOP

	; else loop through composite numbers
	jmp		COMPOSITE

STOP:
	ret
showComposites ENDP


; function determines if an integer is a composit number, then prints it
isComposite PROC
	push		ecx
	mov		divisor, 2
	mov		ecx, dividend
	sub		ecx, 2

; loop to see if number is divisible by any integers
NEXT:
	mov		eax, dividend
	cdq
	div		divisor
	inc		divisor

	cmp		edx, 0
	je		PASS
	loop		NEXT

	pop		ecx
	ret

; prints out number, spaces and creates a new line if necessary
PASS:
	mov		eax, dividend
	call		WriteDec
	pop		ecx
	
	dec		ecx
	inc		spacer
	call		checkNewLine

	ret
isComposite ENDP


; Helper function for spacing 
checkNewLine PROC
	mov		eax,spacer
	cdq
	div		linemax
	cmp		edx,0
	je		NEWLINE
	
	mov		edx, OFFSET tabin
	call		WriteString
	ret

NEWLINE:
	call		Crlf

	ret
checkNewLine ENDP


; Function bids user farewell
farewell PROC
	call		Crlf
	mov		edx, OFFSET goodbye
	call		WriteString
	mov		edx, OFFSET useName
	call		WriteString
	call		Crlf

	ret
farewell ENDP


END main