#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

inline ull read() {
	ull x=0; char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x;
}

ull x, y;

signed main() {
	freopen("a.in", "r", stdin);
	x=read(), y=read();
	char ch=getchar();
	if (ch=='+') x+=y, printf("%llu\n", x);
	if (ch=='-') x-=y, printf("%llu\n", x);
	if (ch=='*') x*=y, printf("%llu\n", x);
	if (ch=='/') x/=y, printf("%llu\n", x);
	return 0;
}
