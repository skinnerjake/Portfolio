x = 100
a = 1
while x > 0:
	a *= x
	x -= 1
	
b = sum(map(int, (list(str(a)))))

print b