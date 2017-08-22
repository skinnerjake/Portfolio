#What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20 by 20 grid?

#import string
init_str = open('Problem11.txt') 
list_int = []

#number of rows
num_lines = sum(1 for line in open('Problem11.txt')) 

#appends each row as a list within a list
while num_lines > 0:
	list_int.append( (map (int, (init_str.readline()).split() ) ) ) 
	num_lines -= 1

x = 0
num_lines = sum(1 for line in open('Problem11.txt'))

#find largest horizontally
for row in list_int:
	for item in range(0, len(row)-3):
		y = row[item] * row[item + 1] * row[item + 2] * row[item + 3]
		if y > x:
			x = y

#find largest vertically			
for row in range(0, num_lines - 3):
	for item in range(0, len(list_int[row])):
		y = list_int[row][item] * list_int[row + 1][item] * list_int[row + 2][item] * list_int[row + 3][item]
		if y > x:
			x = y

#find largest diagonally up
for row in range(3, num_lines):
	for item in range(3, len(list_int[row])):
		y = list_int[row][item - 3] * list_int[row - 1][item - 2] * list_int[row - 2][item - 1] * list_int[row - 3][item]
		if y > x:
			x = y

#find largest diagonally down
for row in range(0, num_lines - 3):
	for item in range(0, len(list_int[row]) - 3):
		y = list_int[row][item] * list_int[row + 1][item + 1] * list_int[row + 2][item + 2] * list_int[row + 3][item + 3]
		if y > x:
			x = y
			
print x
