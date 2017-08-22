#return product of pythagorean triangle whose sum is 1000
def pythagtriangle (x):
	for i in range(2, x//3):
		for j in range(2, x//2):
			for k in range(2, x//2):
				if i ** 2 + j ** 2 == k ** 2:
					if i + j + k == x:
						return(i * j * k)

print(pythagtriangle(1000))