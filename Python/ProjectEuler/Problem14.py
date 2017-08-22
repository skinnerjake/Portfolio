x = 0
y = []
z = 0
for i in range(2, 1000000):
	del y[:]
	y.append(i)
	while i != 1:
		if i % 2 == 0:
			i = i / 2
			y.append(i)
		else:
			i = i * 3 + 1
			y.append(i)
	if len(y) > z:
		z = len(y)
		x = y[0]
		
print x