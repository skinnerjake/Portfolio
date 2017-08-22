'''
Integer right triangles:
If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of (p equal or less than 1000), is the number of solutions maximised?
'''

#create a list to capture lists of solutions for each integer in range; 0 included
solutions = [[]]

for perimeter in range(1, 1000): 				
	solutions.append([])								#create an index to append solutions for value (perimeter)
	minhyp = int(perimeter/(1 + (2 ** 0.5)))			#min hypotenuse = perimeter/(1 + sqrt(2))
	maxhyp = int(perimeter/2)							#max hypotenuse = half perimeter
	for c in range(minhyp, maxhyp):
		for a in range(1, int((perimeter - c) / 2)):	#a and b are inversely related; 
			b = perimeter - a - c						#after (perimeter - c)/2, no new values return
			if (a ** 2 + b ** 2) == c ** 2: 			#check for pythagorean theorem
				solutions[perimeter].append([a, b, c])	
				
solution_numbers = []									#new list containing number of solutions for value (perimeter)
for i in range(len(solutions)): 
	solution_numbers.append(len(solutions[i]))	
answer = solution_numbers.index(max(solution_numbers))
print answer
print solutions[answer]