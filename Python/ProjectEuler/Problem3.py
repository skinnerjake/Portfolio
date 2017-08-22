'''The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143 ?'''

x = 600851475143
n = 1
list1 = [1]

def checkfactor(a, b):
	if a % b == 0:
		list1.append(b)
		return a / b
	else:
		return a

while x > (n - 1):
	x = checkfactor(x, n)
	n += 1

for i in list1:
	for f in range(1, i):
		if i % f == 0:
			list1.remove(i)

print(list1)