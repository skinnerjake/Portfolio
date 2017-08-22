"""Considering quadratics of the form:

	n**2 + a*n + b, where |a| < 1000 and |b| < 1000

where |n| is the modulus/absolute value of n
	
	ex. 11 is 11 and -4 is 4

Find the product of the coefficients, a and b, for the quadratic expression that 
produces the maximum number of primes for consecutive values of n, starting with n = 0.
"""

def isprime(x):
	if x < 2:
		return False
	if x == 2:
		return True
	if (x + 1) & 1:
		return False
	for i in range(2, int(x**0.5)+1):
		if (x % i) == 0:
			return False
			break
	return True

def quadratic(a, b, x):
	return (x**2 + a * x + b)
	
maxlen = 0	
f = []
n = 0
for i in range(-1000, 1001):
	for j in range(-1000, 1001):
		y = []
		x = 0
		while isprime(quadratic(i, j, x)) == True:
			y.append(x)
			x += 1
		if len(y) > maxlen:
			maxlen = len(y)
			print str(i) + ' * ' + str(j) + ' = ' + str(i*j)