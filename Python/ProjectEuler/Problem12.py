x = 0
y = []
z = 0

while len(y) < 500:
	z += 1
	x += z	
	del y[:]
	a = x**0.5
	for i in range(1, int(a)):
		if x % i == 0:
			y.append(i)
			y.append(x/i)
	if x % a == 0:
		y.append(a)
	y.append(x)

print x