def sum_squares(x):
	y = 0
	for i in range(x+1):
		y += (i ** 2)
	return y

def square_sums(x): 
	y = 0
	for i in range(x+1):
		y += i
	return (y ** 2)

print(square_sums(100) - sum_squares(100))