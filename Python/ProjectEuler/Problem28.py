'''
Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

It can be verified that the sum of the numbers on the diagonals is 101.

What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
'''

def NumSpiralDiags (x):
	sum = 1
	length = 1
	value = 1
	while length < (x):
		side = 0
		length += 2
		while side < 4:
			value += length - 1
			sum += value
			side += 1
	return (sum)
	
print (NumSpiralDiags (1001))