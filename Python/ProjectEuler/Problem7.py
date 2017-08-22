""" By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

What is the 10 001st prime number?"""

def nthprime(n):
	x = 1
	y = 0
	while y < n:
		x += 1
		for i in range(2, x):
			if x % i == 0:
				break
		else:
			y += 1
	return x
	
print(nthprime(10001))