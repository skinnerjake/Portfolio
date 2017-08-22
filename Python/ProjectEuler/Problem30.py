#Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
total = 0

for i in range (2, 1000000):
	j = str(i)
	list1 = map(int, [digit for digit in j])
	for k in range(len(list1)):
		list1[k] **= 5
	if sum(list1) == i:
		total += i
		
print total