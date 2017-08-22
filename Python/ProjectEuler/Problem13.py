#Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.

x = open('Problem13.txt')
y = sum(map(int, (x.read()).split()))
print str(y)[0:10]