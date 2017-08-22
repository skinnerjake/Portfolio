#Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

def repeating(x):
	remainder = []
	i = 1%x
	while i not in remainder:
		remainder.append(i)
		i = (i*10)%x
	return remainder

def longestrepeat(a):
	longest = 0
	num = 0
	for x in range(1, a+1):
		y = repeating(x)
		if len(y) > longest:
			longest = len(y)
			num = x
	return num
	
print longestrepeat(1000)