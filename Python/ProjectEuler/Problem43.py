'''
The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d(2) be the 2nd digit, and so on. In this way, we note the following:

d(2)d(3)d(4) = 406 is divisible by 2
d(3)d(4)d(5) = 063 is divisible by 3
d(4)d(5)d(6) = 635 is divisible by 5
d(5)d(6)d(7) = 357 is divisible by 7
d(6)d(7)d(8) = 572 is divisible by 11
d(7)d(8)d(9) = 728 is divisible by 13
d(8)d(9)d(10) = 289 is divisible by 17
Find the sum of all 0 to 9 pandigital numbers with this property.
'''
#returns true if numbers can be concatenated by two digits
def appendable(p, q):
	if p[-2:] == q[:2]: return True
	else: return False

#concatenates numbers if last two and first two digits match, respectively
def link(p, q):
	if appendable(p,q) == True: return p + q[-1]

#returns only pandigital values in a list
def pandigital(alist, length):
	blist = []
	for i in alist:
		if len(set(i)) == length: blist.append(i)
	return blist

#append missing value of
def find_missing(x):
	y = list(set('1234567890') - set(x))[0]
	return y + x

primes = [2, 3, 5, 7, 11, 13, 17]
list1 = []

#create a list of lists containing 3 digit values divisible by x in primes that do not repeat digits
for num in range(len(primes)):
	shortlist = (map(str, [y for y in range(1, 1000) if y % primes[num] == 0]))
	longlist = []
	for value in shortlist: 
		longlist.append( value.zfill(3) )
	truelist = pandigital(longlist, 3)
	list1.append(truelist)

#makes a list of all values that follow the divisible rules, then rules out non-pandigital answers
candidates = list1[0]
for f in range(1, 7):
	temp = []
	for i in list1[f]:
		for j in range(len(candidates)):
			x = link(candidates[j], i)
			if x != None: temp.append(x)
	candidates = pandigital(temp, f + 3)

#appends missing integer at [0]
answer = sum(map(int, (map(find_missing, candidates))))
print answer