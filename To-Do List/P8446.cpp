#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
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

#define N 4000010
#define INF 0x7f7f7f7f
int n, mn, mx, ans;
int a[N], b[N], c[N];

signed main() {
	// freopen("P8446.in", "r", stdin);
	n=read(), mn=INF, mx=-INF, ans=-INF;
	for (int i=1; i<=n; ++i) a[i]=read(), b[i]=a[i]-i, c[i]=a[i]+i;
	for (int i=1; i<=n; ++i) {
		mn=min(mn, b[i]);
		ans=max(ans, b[i]-mn-1);
	}
	for (int i=1; i<=n; ++i) {
		mx=max(mx, c[i]);
		ans=max(ans, mx-c[i]-1);
	}
	printf("%d\n", ans);
	return 0;
}
