'''
The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
'''

#creates list of primes as strings
def primes(n):
    size = n//2
    sieve = [1]*size
    limit = int(n**0.5)
    for i in range(1,limit):
        if sieve[i]:
            val = 2*i+1
            tmp = ((size-1) - i)//val 
            sieve[i+val::val] = [0]*tmp
    return map(str, [2] + [i*2+1 for i, v in enumerate(sieve) if v and i>0])

#deletes right digit
def truncate_right(x):
	x = x[:-1]
	return x
	
#deletes left digit
def truncate_left(x):
	x = x[1:]
	return x

#given a string, returns a list of truncated strings, from left and right
def truncate(x):
	num_r = x
	num_l = x
	truncated = []
	while len(num_r) > 0:
		truncated.append(num_r)
		num_r = truncate_right(num_r)
	while len(num_l) > 0:
		truncated.append(num_l)
		num_l = truncate_left(num_l)
	return truncated

#returns all truncatable primes in list of primes
def truncatable_primes(list1):
	truncatable = []
	while len(truncatable) < 11:
		for i in list1[4:]:
			trunc = truncate(i)
			if (set(trunc).issubset(set(list1))) == True: truncatable.append(i)
	return truncatable

print sum(map(int, truncatable_primes([item for item in primes(1000000) if (set(item).issubset(set('123579')))])))