def sum35(x):
	for i in range(1000):
		if (i % 3 == 0) or (i % 5 == 0):
			x = x + i
	print(x)
	
sum35(0)
