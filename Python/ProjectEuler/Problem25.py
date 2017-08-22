#What is the index of the first term in the Fibonacci sequence to contain 1000 digits?

x = 0 #Fibonacci (n-1)
y = 1 #Fibonacci (n)
n = 1
while len(str(y)) < 1000:
	x, y = y, x + y
	n += 1
print n