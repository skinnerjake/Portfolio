def smallest_multiple(a, b):
	while b <= 20:
		if a % b == 0:
			(a, b) = (a, b + 1)
		else:
			(a, b) = (a + 1, 1)
	print(a)
				
smallest_multiple(1, 1)