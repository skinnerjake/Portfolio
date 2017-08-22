#Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

#parameters:  it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers.

def sum_divisors(x):
	y = [1]
	a = (x**0.5)
	for i in range(2, int(round(a)) + 1):
		if x % i == 0:
			y.append(i)
			if i != a:
				y.append(x/i)
	return sum(y)

r = 28123

a = [i for i in range(1, r + 1) if sum_divisors(i) > i]
l = []

for i in range(len(a)):
	for b in range(i + 1):
		l.append(a[b] + a[i])

f = list(range(1, r + 1))

print sum(list(set(f) - set(l)))