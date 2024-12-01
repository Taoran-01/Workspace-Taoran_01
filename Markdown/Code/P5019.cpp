#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
int n; ll ans;
int a[N], d[N];

signed main() {
	// freopen("road5.in", "r", stdin);
	// freopen("road5.out", "w", stdout);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=n; ++i) d[i]=a[i]-a[i-1];
	for (int i=1; i<=n; ++i) ans+=max(d[i], 0);
	printf("%lld\n", ans);
	return 0;
}
