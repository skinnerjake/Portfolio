'''The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not include leading zeros.)'''


list_dec = []
list_both = []

for i in range(1, 1000000):
	if str(i) == str(i)[::-1]:
		list_dec.append(i)

for i in list_dec:
	x = str(int(str(bin(i))[2:]))
	if x == x[::-1]:
		list_both.append(i)

print sum(list_both)