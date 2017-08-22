TITLE sortRandom	(sortRandom.asm)

; Name:			Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description:	Program creates, sorts, and displays an array of random numbers using stack parameters

INCLUDE Irvine32.inc

; Global constants
	min = 10
	max = 200
	lo = 100
	hi = 999
	line = 10

.data
	request		DWORD	?
	array		DWORD	max DUP(?)
	median		DWORD	?
	intro		BYTE		"Random Number Array by Jake Skinner", 13, 10, 10, 0
	description1	BYTE		"This program generates a defined number of integers in the range 100-999. The", 13, 10
	description2	BYTE		"numbers are printed in the order they were created. The numbers are then sorted,", 13, 10
	description3	BYTE		"the median is calculated and displayed, and the sorted numbers are displayed.", 13, 10, 10, 0
	dataPrompt	BYTE		"How many random numbers should be generated? Input an integer in the range [10,200]: ",0
	badRange		BYTE		"Out of range. ", 13, 10, 0
	unsorted		BYTE		"Unsorted list: ", 13, 10, 0
	sorted		BYTE		"Sorted list: ", 13, 10, 0
	medPrompt		BYTE		"The median value is ", 0

.code
	main	PROC
		push		OFFSET intro
		push		OFFSET description1
		call		introduction

		push		OFFSET request
		call		getData
		
		push		request
		push		OFFSET array
		call		fillArray

		push		OFFSET unsorted
		call		writeArray

		call		sortArray

		push		OFFSET median
		push		OFFSET medPrompt
		call		getMedian

		push		OFFSET sorted
		call		writeArray

		exit
	main	ENDP


	; Introduce the program
	introduction	PROC
		push		ebp
		mov		ebp, esp
		mov		edx,	[ebp+12]
		call		writeString
		mov		edx,	[ebp+8]
		call		writeString
		pop		ebp
		ret		8
	introduction	ENDP


	; Get a user request in the range [min = 10... max = 200]
	getData	PROC
		
		push		ebp
		mov		ebp, esp
		mov		ebx, [ebp+8]
		
		input:
			mov		edx, OFFSET dataPrompt
			call		writeString
			call		readDec

		validate:
			cmp		eax, min
			jl		outOfRange	
			cmp		eax, max
			jg		outOfRange
			jmp		resolve
	
		outOfRange:
			mov		edx, OFFSET badRange
			call		writeString
			jmp		input

		resolve:
			mov		[ebx], eax
			pop		ebp
			ret		4
	getData	ENDP


	; Generates an integer in range then stores it in an array index from esi
	fillArray	PROC

		push		ebp
		mov		ebp, esp
		mov		ecx,	[ebp+12]
		mov		esi, [ebp+8]

		nextInt:
			mov		eax, hi
			sub		eax, lo
			inc		eax
			call		RandomRange
			add		eax, lo
			mov		[esi], eax
			add		esi, 4
			loop		nextInt
			
		pop		ebp
		ret		
	fillArray	ENDP

	; Display the array of numbers
	writeArray	PROC

		call		crlf
		push		ebp
		mov		ebp, esp
		mov		ecx, [ebp+16]
		mov		esi, [ebp+12] ; might want to use another register?
		mov		edx, [ebp+8]
		call		writeString
		mov		ebx, line

		nextInt:
			
			; Write integer in current index, move index, and tab in
			mov		eax, [esi]
			call		writeDec
			add		esi, 4
			mov		al, 9
			call		writeChar

			; Calculate element number ([ebp+16] - ecx + 1) and check for new line
			mov		eax, [ebp+16]
			sub		eax, ecx
			inc		eax
			cdq
			div		ebx		
			cmp		edx, 0
			jne		continue

			; Start new line
			call		CrLf

			continue:
				loop		nextInt

		call		crlf
		call		crlf
		pop		ebp
		ret		4
	writeArray	ENDP

	; Sorts the array in descending order 
	sortArray	PROC
		push		ebp
		mov		ebp, esp
		mov		ecx, [ebp+12]
		dec		ecx

		outerLoop:
			push		ecx
			mov		esi, [ebp+8]

			innerLoop:
				mov		eax, [esi]
				cmp		[esi+4], eax
				jl		incIndex
				xchg		eax, [esi+4]
				mov		[esi], eax

			incIndex:
				add		esi, 4
				loop		innerLoop

			pop		ecx
			loop		outerLoop
		pop		ebp
		ret
	sortArray	ENDP


	getMedian	PROC
		; Push base pointer of stack
		push		ebp
		mov		ebp, esp
		
		; Initialize registers from parameters on stack
		mov		edx, [ebp+8]
		mov		edi, [ebp+12]
		mov		esi, [ebp+16]
		mov		eax, [ebp+20]
		mov		ebx, 2

		; Write prompt
		call		writeString

		; Determine if list contains odd or even number of integers
		cdq
		div		ebx
		cmp		edx, 0
		jne		ODD

		; If even, EAX = rounded average of two middle integers
			dec		eax
			mov		ebx, 4
			mul		ebx
			add		esi, eax
			mov		eax, [esi]
			add		eax, [esi+4]
			mov		ebx, 2
			div		ebx
			cmp		edx, 0
			je		WRITE
			inc		eax
			jmp		WRITE

		ODD:
			mov		ebx, 4
			mul		ebx
			add		esi, eax
			mov		eax, [esi]

		WRITE:
			call		writeDec
			call		crlf

		pop		ebp
		ret		8
	getMedian ENDP

	END	main