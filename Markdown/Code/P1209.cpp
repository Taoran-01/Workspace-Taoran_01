#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 210
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int K, m, n;
int b[N], tot;
int cnt, len;
pair<int, pii> a[N];

signed main() {
	// freopen("a.in", "r", stdin);
	K=read(), m=read(), n=read();
	for (int i=1; i<=n; ++i) {int x=read(); b[x]=1, ++len;}
	for (int i=1; i<=m+1; ++i) if (b[i-1]&&!b[i]) ++cnt;
	while (cnt>K) {
		// fprintf(stderr, "cnt=%d len=%d\n", cnt, len);
		// for (int i=1; i<=m; ++i) fprintf(stderr, "%d", b[i]); puts("");
		tot=0;
		for (int i=1; i<=m; ++i) {
			if (b[i-1]&&!b[i]) ++tot, a[tot]=mkp(0, mkp(i,i-1));
			if (!b[i]) ++a[tot].fi, ++a[tot].se.se;
		}
		sort(a+1, a+tot+1);
		for (int i=a[1].se.fi; i<=a[1].se.se; ++i) b[i]=1;
		--cnt, len+=a[1].fi;
	}
	printf("%d\n", len);
	return 0;
}
