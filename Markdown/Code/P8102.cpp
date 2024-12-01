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

#define N 5000010
#define INF 0x7f7f7f7f
int n, k, v; ll sum, ans;
int a[N];
int d1[N], d2[N];
ll s1[N], s2[N];
int q[N], l, r;

void pcs(int m, int d[]) {
	l=1, r=0;
	for (int i=1; i<=n; ++i) {
		while (l<=r&&a[q[r]]<=a[i]) --r;
		q[++r]=i;
		while (l<=r&&q[l]<=i-m) ++l;
		if (i>=m) d[i]=a[q[l]];
	}
}

signed main() {
	// freopen("insert.in", "r", stdin);
	// freopen("insert.out", "w", stdout);
	n=read(), k=read(), v=read(), ans=-INF;
	for (int i=1; i<=n; ++i) a[i]=read(), sum+=a[i];
	if (k==1) return printf("%lld\n", sum+v), 0;
	pcs(k, d1), pcs(k-1, d2);
	for (int i=k; i<=n; ++i) s1[i]=s1[i-1]+d1[i];
	for (int i=k-1; i<=n; ++i) d2[i]=max(d2[i], v);
	for (int i=k-1; i<=n; ++i) s2[i]=s2[i-1]+d2[i];
	for (int pos=0; pos<=n; ++pos) {
		ll cur=0; int l=max(pos, 1), r=min(pos+k-1, n);
		cur+=s1[l];
		cur+=s1[n]-s1[r];
		cur+=s2[r]-s2[l-1];
		ans=max(ans, cur);
	}
	printf("%lld\n", ans);
	return 0;
}
