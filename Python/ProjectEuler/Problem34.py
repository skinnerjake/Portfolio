#Find the sum of all numbers which are equal to the sum of the factorial of their digits.

def factorial(x):
	n = 1
	while x > 0:
		n *= x
		x -= 1
	return n

def listdigits(x):
	return map(int, [i for i in str(x)])

f = 0

for i in range(3, 1000000):
	k = sum(map(factorial, listdigits(i)))
	if k == i: 
		f += k

print f