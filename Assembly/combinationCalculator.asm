TITLE combinationCalculator	(combinationCalculator.asm)

; Name:		Jake Skinner
; Email:		skinnjac@oregonstate.edu
; Description: 	Calculates the combination of r items from a set of n numbers (user defined)

INCLUDE Irvine32.inc

hi = 12
lo = 3
max = 20
small = 48
large = 57

.data
	intro1	BYTE		"Combination Calculator by Jake Skinner (OPTION B)", 13, 10
	intro2	BYTE		"Calculates the combination of 'r' items from a set of 'n' numbers. (nCr)", 13, 10, 0
	nValue	DWORD	?
	rValue	DWORD	?
	input	BYTE		max DUP(?)
	answer	DWORD	?
	result	DWORD	?
	instruct	BYTE		"Your answer: ", 0
	badData	BYTE		"Please input only digits.", 13, 10, 0
	output1	BYTE		"There are ", 0
	output2	BYTE		" combinations of ", 0
	output3	BYTE		" items from a set of ", 0
	output4	BYTE		".", 13, 10, 0
	output5	BYTE		"Your answer of ", 0
	correct	BYTE		" was correct!", 13, 10, 0
	incorrect	BYTE		" was incorrect.", 13, 10, 0
	playAgain	BYTE		"Would you like to play again? (y/n): ", 0
	invalid	BYTE		"Input 'y' or 'n': ", 0


	miccheck	BYTE		"Mic Check", 13, 10, 0

.code

	main PROC
		
		; Call introduction procedure
		call		introduction

		again:

		; Push parameters for and call showProblem
		call		crlf
		push		OFFSET nValue
		push		OFFSET rValue
		call		showProblem

		; Push parameters for and call getData
		push		OFFSET answer
		push		OFFSET input
		call		getData

		; Push parameters for and call combinations
		push		OFFSET result
		push		rValue
		push		nValue
		call		combinations

		; Push parameters for and call showResults
		push		nValue
		push		rValue
		push		answer
		push		result
		call		showResults

		; Play again?
		mov		edx, OFFSET playAgain
		call		WriteString
		getinput:
		call		ReadChar
		call		crlf
		cmp		al, 'y'
		je		again
		cmp		al, 'n'
		je		endprog
		mov		edx, OFFSET invalid
		call		writestring
		jmp		getinput
	
		endProg:

		exit
	main ENDP

	; Outputs title and intro 
	introduction PROC
		mov		edx, OFFSET intro1
		call		writeString
		ret	
	introduction ENDP


	; Calculates random N and R values and outputs the problem.
	; Param: OFFSET nValue, OFFSET rValue
	showProblem PROC
		push		ebp
		mov		ebp, esp

		; Find N
		mov		edi, [ebp + 12]
		mov		eax, hi
		sub		eax, lo
		inc		eax
		call		RandomRange
		add		eax, lo
		mov		[edi], eax
		
		; Find R
		mov		esi, edi
		mov		edi, [ebp + 8]
		call		RandomRange
		inc		eax
		mov		[edi], eax

		; Write the combination
		mov		edx, [ebp + 12]
		mov		eax, [edx]
		call		WriteDec
		
		mov		al, 'C'
		call		WriteChar

		mov		edx, [ebp + 8]
		mov		eax, [edx]
		call		WriteDec
		call		CRLF

		pop		ebp
		ret		8
	showProblem ENDP


	; Get user data as a string
	; Validate input is a number
	; Convert string data to integer and stores value in 'answer'
	; Param: OFFSET answer, OFFSET input
	getData PROC
		push		ebp
		mov		ebp, esp

		; Prompt user for input:
		mov		edx, OFFSET instruct
		call		WriteString

		getInput:
			; Get user input
			mov		eax, 0
			mov		edi, [ebp + 8]
			mov		edx,	edi
			mov		ecx, max
			call		ReadString

			; If first value is NULL, get new input
			mov		esi, [ebp + 8]
			cld
			lodsb
			cmp		al, 0
			je		redo

		; Validate each number in string is an integer until a null character is reached
		; Increment esi
		readForward:
			cmp		al, small
			jl		nullChar
			cmp		al, large
			jg		redo
			lodsb
			jmp		readForward
		nullChar:
			dec		esi
			cmp		eax, 0
			jne		redo
			jmp		proceed
		redo:
			mov		edx, OFFSET badData
			call		WriteString
			jmp		getInput


		proceed:
			; Calculate length of user input (@null - @first), move to counter (ecx)
			mov		eax, esi
			sub		eax, [ebp + 8]
			mov		ecx, eax

			; ebx = place value
			mov		ebx, 1

			; answer = [edi] = 0
			mov		edi, [ebp + 12]
			mov		eax, [edi]
			sub		[edi], eax

		readBackwards:

			; Decrement the source index
			dec		esi

			; convert ascii to integer value * place value
			mov		eax, 0
			mov		al, [esi]
			sub		eax, small
			mul		ebx

			; increment place value in ebx
			imul		ebx, 10

			; add value to [edi],
			add		[edi], eax
			loop		readBackwards

		pop		ebp
		ret		8
	getData ENDP


	; Calculate combination, given values for n and r
	; Store result in 'result'
	; Param: OFFSET result, nValue, rValue
	combinations PROC
		push		ebp
		mov		ebp, esp

		; calculate n!
		mov		eax, [ebp + 8]
		push		eax
		call		factorial
		push		eax

		; calculate r!
		mov		eax, [ebp + 12]
		push		eax
		call		factorial
		push		eax

		; calculate (n-r)!
		mov		eax, [ebp + 8]
		mov		ebx, [ebp + 12]
		sub		eax, ebx
		push		eax
		call		factorial
		push		eax

		; calculate combination
		mov		edi, [ebp + 16]
		pop		ecx
		pop		ebx
		pop		eax
		div		ebx
		div		ecx
		mov		[edi], eax

		pop		ebp
		ret 12
	combinations ENDP


	; Calculates factorial (n!)
	; Param: n (number by value)
	; Value returned in eax, then pushed
	factorial PROC
		push		ebp
		mov		ebp, esp

		; Initialize accumulator (eax) and loop counter (ecx)
		mov		eax, 1
		mov		ecx, [ebp + 8]

		; 0! = 1 -> skip loop
		cmp		ecx, 0
		je		noLoops

		; Calculate factorial by multiplying accumulator (eax) by remaining value in loop counter (ecx)
		loop1:
			mul		ecx
			loop		loop1

		noLoops:
		pop		ebp
		ret		4
	factorial ENDP


	; Shows all results to user, then indicates if they were correct or not
	; Param: nValue, rValue, answer, result
	showResults PROC
		push		ebp
		mov		ebp, esp

		; Prints 'There are [result] combinations of [r] items from a set of [n]. '
		mov		edx, OFFSET output1
		call		writestring
		mov		eax, [ebp + 8]
		call		writeDec
		mov		edx, OFFSET output2
		call		writeString
		mov		eax, [ebp + 16]
		call		writeDec
		mov		edx, OFFSET output3
		call		writeString
		mov		eax, [ebp + 20]
		call		writeDec
		mov		edx, OFFSET output4
		call		writeString

		; Prints 'Your answer of [answer] was (correct/incorrect).'
		mov		edx, OFFSET output5
		call		writeString
		mov		eax, [ebp + 12]
		call		writeDec
		cmp		eax, [ebp + 8]
		je		rightAnswer
		mov		edx, OFFSET incorrect
		call		writeString
		jmp		TheEnd
		rightAnswer:
		mov		edx, OFFSET correct
		call		writeString
		TheEnd:

		pop		ebp
		ret		16
	showResults ENDP


	END main