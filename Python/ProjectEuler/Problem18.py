#Find the maximum sum path from top to bottom of the triangle in pyramid.txt:

nums = []

for i in (open('pyramid.txt').read()).splitlines():
	nums += [[int(x) for x in (i.split())]]

while len(nums) > 1:
	z = len(nums) - 1
	for i in range(0, z):
		if nums[z][i] > nums[z][i+1]:
			nums[z-1][i] += nums[z][i]
		elif nums[z][i+1] > nums[z][i]:
			nums[z-1][i] += nums[z][i+1]
	del (nums[z])
	
print (nums[0])