#What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?

def perm(x):
	a = 1
	for i in range(1, x+1):
		a *= i
	return (a)

def lexicographic(x, y):
	b = list(range(x))
	y -= 1
	c = []
	while len(b) > 0:
		x -= 1
		a = int(y/perm(x))
		c.append(b[a])
		del b[a]
		y -= (perm(x) * a)
	return (c)
	
print (lexicographic(10, 1000000))