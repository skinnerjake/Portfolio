'''The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?'''

def rotate(n):
    return n[1:]+n[:1]
	
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

def circular_primes(x):
	prime_list = primes(10) + [item for item in primes(x)[4:] if set(item).issubset(set('1379'))]
	circularprimes = []
	allprime = True
	for i in prime_list:
		circular = []
		while i not in circular:
			circular.append(i)
			i = rotate(i)
		if set(circular).issubset(set(prime_list)): circularprimes.append(i)
	return circularprimes

print len(circular_primes(1000000))