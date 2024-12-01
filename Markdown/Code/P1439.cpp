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

#define N 100010
int n;
int a[N], b[N];
int mp[N], d[N];
int f[N], m;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=n; ++i) b[i]=read(), mp[b[i]]=i;
	for (int i=1; i<=n; ++i) d[i]=mp[a[i]];
	// for (int i=1; i<=n; ++i) printf("%d ", d[i]); puts(""); //
	f[1]=d[1], m=1;
	for (int i=1; i<=n; ++i) {
		if (d[i]>f[m]) {f[++m]=d[i]; continue;}
		*lower_bound(f+1, f+m+1, d[i])=d[i];
	}
	printf("%d\n", m);
	return 0;
}
