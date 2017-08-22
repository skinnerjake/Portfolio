#Using names.txt, a 46K text file containing over five-thousand first names, 
#begin by sorting it into alphabetical order. Then, working out the alphabetical value for each name, 
#multiply this value by its alphabetical position in the list to obtain a name score.

#What is the sum of all the name scores in the file?

import re

x = list(enumerate(sorted(re.findall(r'"(.*?)"', open('names.txt').read())), start = 1))

def namevalue(name):
	sumchr = 0
	for i in name: 
		sumchr += (ord(i)-64)
	return (sumchr)

def bignamevalue(names):
	sumproducts = 0
	for i in names:
		product = namevalue(i[1]) * i[0]
		sumproducts += product
	return (sumproducts)

print (bignamevalue(x))
