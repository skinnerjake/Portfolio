x = 1

def sumevenfib(a):
	x = 0 #Fibonacci2
	y = 1 #Fibonacci2
	z = 0 #sum
	while y < a:
		x, y = y, x + y
		if y % 2 == 0: #check for even
			z += y
	print(z)
	
sumevenfib(4000000)
	
	
