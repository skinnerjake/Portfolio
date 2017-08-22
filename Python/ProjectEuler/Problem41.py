'''
Pandigital prime:

We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?
'''

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

def pandigital(x):
	if set(x) == set(map(str, list(range(1, len(x) + 1)))):
		return True
	else:
		return False

primelist = [num for num in primes(10000000) if pandigital(num) == True]

print max(map(int, primelist))
