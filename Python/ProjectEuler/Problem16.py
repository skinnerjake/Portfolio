#2 to the 15th power = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

#What is the sum of the digits of the number 2 to the 1000th power?

x = str(2 ** 1000)
y = []
for i in x:
	y.append(i)
z = sum(map(int, y))
print z