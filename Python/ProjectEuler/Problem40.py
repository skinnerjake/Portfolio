'''
Champernowne's constant:

An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...
             ^
It can be seen that the 12th digit of the fractional part is 1.

If d(n) represents the nth digit of the fractional part, find the value of the following expression.

d(1) * d(10) * d(100) * d(1000) * d(10000) * d(100000) * d(1000000)
'''

champernowne = '0.'
list1 = map(str, list(range(1, 200000)))
digit = []

for i in list1:
	champernowne += i

looking = 1
while len(digit) < 7:
	looking_dig = looking + 1
	digit.append(champernowne[looking_dig])
	looking *= 10

def product(x):
	f = 1
	for i in x: f *= i
	return f

print product(map(int, digit))