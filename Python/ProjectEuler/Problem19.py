#How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

month = [[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31], [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]]

year = 1901
day = 2 # Jan 1 1901 was a Tuesday
sunday = 0

while year < 2001:
	if year % 4 == 0:
		for i in month[1]:
			day += i
			day %= 7
			if day == 0:
				sunday += 1
	elif year % 4 != 0:
		for i in month[0]:
			day += i
			day %= 7
			if day == 0: 
				sunday += 1
	year += 1
	
print(sunday)