n=int(input())
a=[]
s=input()
s=s.split(' ')
x1=int(s[0])
x2=int(s[1])

for i in range(0,n,1):
	s=input()
	s=s.split(' ')
	t1=int(s[0])
	t2=int(s[1])
	a.append((t1*t2,t1,t2))

a.sort(key=lambda pair:pair[0])

prod=x1
ans=0

for i in range(0,n,1):
	ans=max(ans, prod//a[i][2])
	prod*=a[i][1]

print(ans)
