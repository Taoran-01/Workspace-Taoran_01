#include "wheel.h"

#include<iostream>
#include<cstdio>
#define F(i,l,r) for(int i=(l);i<=(r);i++)

const int MaximumN=1e6+5;

int perm[MaximumN], rotate_count, ptr=0, Real_n, Real_m;

int rotate(bool way,int k)
{
	++rotate_count;
	if(way)
	{
		ptr=(ptr+k)%Real_n;
	}else
	{
		ptr=((ptr-k)%Real_n+Real_n)%Real_n;
	}
	return perm[ptr];
}
int guess(int,int);

int main()
{
	std::scanf("%d %d", &Real_n, &Real_m);
	F(i,0,Real_n-1)
	{
		std::scanf("%d", &perm[i]);
	}
	std::printf("Your answer: %d\n", guess(perm[0], Real_m));
	std::printf("Real Answer: %d\n", Real_n);
	std::printf("Operation Used: %d\n", rotate_count);
	return 0;
}
#undef F
