n=int(input())
h=1
for i in range(1, n+1, 1):
	h=h*(i*4-2)//(i+1)
print(h)
