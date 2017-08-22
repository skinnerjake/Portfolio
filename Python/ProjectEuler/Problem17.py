On = [0,3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8]
Te = [0,3,6,6,5,5,5,7,6,6]
Hu = 7
Th = 8
 
total = 0
for i in range(1,1000):
    c = i % 10 # singles digit
    b = ((i % 100) - c) / 10 # tens digit
    a = ((i % 1000) - (b * 10) - c) / 100 # hundreds digit
 
    if a != 0:
        total += On[a] + Hu # '___ hundred'
        if b != 0 or c != 0: 
        	total += 3 # 'and'
    if b == 0 or b == 1: 
    	total += On[b * 10 + c] # 
    else: total += Te[b] + On[c]
 
total += On[1] + Th
print total

# I did not write this. The list parsing was not my idea.