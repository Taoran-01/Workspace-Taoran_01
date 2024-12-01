#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 300010
int n;
int a[N];

signed main() {
	// freopen("a1.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	sort(a+1, a+n+1), n=unique(a+1, a+n+1)-(a+1);
	if (n<=1) return puts("-1"), 0;
	printf("%d\n", max(a[n-2], a[n]%a[n-1]));
	return 0;
}
