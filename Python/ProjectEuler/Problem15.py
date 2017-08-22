#Starting in the top left corner of a 2 by 2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
#How many such routes are there through a 20 by 20 grid?

def lattice_paths(d, r):
	comb_dr = 1
	comb_d = 1
	comb_r = 1
	for num in range(1, d + r + 1):
		comb_dr *= num
	for num in range(1, d + 1):
		comb_d *= num
	for num in range(1, r + 1):
		comb_r *= num
	print (comb_dr / (comb_d * comb_r))
	
lattice_paths(20,20)