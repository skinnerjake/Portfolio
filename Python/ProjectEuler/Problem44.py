'''
Pentagon numbers
Problem 44

Pentagonal numbers are generated by the formula, P(n) equals n times (3 times n minus 1) over 2. The first ten pentagonal numbers are:

1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

It can be seen that the sum of P(4) and P(7) equals 22 + 70 equals 92 equals P(8). However, their difference, 70 minus 22 equals 48, is not pentagonal.

Find the pair of pentagonal numbers, P(j) and P(k), for which their sum and difference are pentagonal and D equals |P(k) minus P(j)| is minimised; what is the value of D?
'''

l1 = []

for n in range(1, 1000):
	x = (3 * n ** 2 - n) / 2
	l1.append(x)
	
print l1

l2 = []

for i in range(1, len(l1)):
	l1[i] - l1[i-1]
	
	