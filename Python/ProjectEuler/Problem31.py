#1p, 2p, 5p, 10p, 20p, 50p, 1pound (100p) and 2pounds (200p).
#How many different ways can 2pounds be made using any number of coins?

cost = [1, 2, 5, 10, 20, 50, 100, 200]
goal = 200
ways = [1] + [0] * goal

marker = 0
goals = [goal] + [0] * (len(cost))

for i in range(0, goal//cost[-1] + 1):
	goals[1] = goal - (cost[-1] * i)
	for j in range(0, goals[1]//cost[-2] + 1):
		goal2 = goals[1] - (cost[-2] * j)
		for k in range(0, goal2//cost[-3] + 1):
			goal3 = goal2 - (cost[-3] * k)
			for l in range(0, goal3//cost[-4] + 1):
				goal4 = goal3 - (cost[-4] * l)
				for m in range(0, goal4//cost[-5] + 1):
					goal5 = goal4 - (cost[-5] * m)
					for n in range(0, goal5//cost[-6] + 1):
						goal6 = goal5 - (cost[-6] * n)
						for o in range(0, goal6//cost[-7] + 1):
							marker += 1

print marker

for coin in cost:
	for i in range(coin, goal + 1):
		ways[i] += ways[i - coin]
		
print ways[goal]