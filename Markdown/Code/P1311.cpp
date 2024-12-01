#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 200010
#define K 60
int n, k, p;
int a[N], v[N], cnt[K];
ll ans;

signed main() {
	// freopen("hotel8.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), k=read(), p=read();
	for (int i=1; i<=n; ++i) a[i]=read(), v[i]=read();
	for (int i=1; i<=n; ++i) ++cnt[a[i]];
	for (int i=0; i<k; ++i) ans+=1LL*cnt[i]*(cnt[i]-1)/2;
	memset(cnt, 0, sizeof(cnt));
	for (int i=1; i<=n+1; ++i) {
		if (v[i]>p) {++cnt[a[i]]; continue;}
		for (int i=0; i<k; ++i) ans-=1LL*cnt[i]*(cnt[i]-1)/2;
		memset(cnt, 0, sizeof(int)*k);
	}
	printf("%lld\n", ans);
	return 0;
}
