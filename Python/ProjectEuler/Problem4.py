list1 = list2 = list(range(100, 999))
list3 = [0]

for a in list1:
	for b in list2:
		x = a * b
		if str(x) == str(x)[::-1]: #check for palindrome
			list3.append(x)
		
print(max(list3))
