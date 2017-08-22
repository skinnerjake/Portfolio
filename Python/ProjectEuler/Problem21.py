"""
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
"""

def sum_divisors(x):
	y = [1]
	a = (x**0.5)
	for i in range(2, int(round(a)) + 1):
		if x % i == 0:
			y.append(i)
			if i != a:
				y.append(x/i)
	return sum(y)

def sum_amicable(x):
	a = []
	for num in range(1, x + 1):
		y = sum_divisors(num)
		z = sum_divisors(y)
		if (z == num) and (y != num) and (z not in a):
			a.append(z)
			a.append(y)
	return sum(a)
	
print sum_amicable(10000)