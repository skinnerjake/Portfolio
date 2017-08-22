'''
Digit cancelling fractions
Problem 33

The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
'''
from fractions import Fraction

l = []

for i in range(1, 10):
	for d in range(1, i):
		for n in range(1, d):
			x = ( float(n) / float(d) )
			n1 = float(str(n) + str(i))
			d1 = float(str(i) + str(d))
			y = n1 / d1
			if x == y: l.append([n, d])

def product(parent, location):
	sub = []
	for sublist in parent: sub.append(sublist[location])
	x = 1
	for num in sub: x *= num
	return x
	
numerator = product(l, 0)
denominator = product(l, 1)

print l
print numerator
print denominator
print Fraction(numerator, denominator)

'''
Notes about the algorithm:

1. n is the numerator in the simpified fraction
2. d is the denominator in the simplified fraction
3. i is the digit that is canceled

All two digit fractions have to be written in the form --> ('n'+'i') / ('i'+'d')
because any other order (i.e., in / id) will result in improper fractions.

1 < n < d < i < 10
'''