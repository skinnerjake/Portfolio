'''We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 * 186 equals 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.'''

def pandigital(multiplicand, multiplier):
	check_list = map(str, list(range(1, 10)))
	product = multiplicand * multiplier
	product = str(product)
	multiplicand = str(multiplicand)
	multiplier = str(multiplier)
	numstring = multiplicand + multiplier + product
	if len(numstring) == 9:
		l = []
		for digit in numstring:
			l.append(digit)
		l.sort()
		if l == check_list:
			return int(product)
		else:
			return 0
	else:
		return 0

listsum = []
for i in range(1, 10000):
	for f in range(1, 100):
		if pandigital(i, f) != 0:
			listsum.append(pandigital(i, f))
print sum(list(set(listsum)))