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

#define N0 10000010
#define M0 1010
// #define N (M0<<2)
#define N N0
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
ll m, n, ans;
pii d[N];
// ll t[N], nt;

struct seg {
	#define ls (p<<1)
	#define rs (p<<1|1)
	bool tag[N<<2];
	void push_up(ll p) {tag[p]=tag[ls]&&tag[rs];}
	bool modify(ll nl, ll nr, ll l, ll r, ll p) {
		if (tag[p]) return 0;
		if (nl<=l&&r<=nr) return tag[p]=1, 1;
		ll mid=l+r>>1; bool res=0;
		if (nl<=mid) res|=modify(nl, nr, l, mid, ls);
		if (nr>mid) res|=modify(nl, nr, mid+1, r, rs);
		push_up(p); return res;
	}
	// bool modify(ll l, ll r) {return modify(l, r, 1, n<<1, 1);}
	bool modify(ll l, ll r) {return modify(l, r, 1, m, 1);}
} tr;

signed main() {
	// freopen("a.in", "r", stdin);
	m=read(), n=read();
	for (int i=1; i<=n; ++i) {
		d[i].fi=read(), d[i].se=read();
		// t[++nt]=d[i].fi, t[++nt]=d[i].se;
	}
	// sort(t+1, t+nt+1), nt=unique(t+1, t+nt+1)-t-1;
	// for (int i=1; i<=n; ++i) {
	// 	d[i].fi=lower_bound(t+1, t+nt+1, d[i].fi)-t;
	// 	d[i].se=lower_bound(t+1, t+nt+1, d[i].se)-t;
	// }
	for (int i=n; i>=1; --i) {
		ans+=tr.modify(d[i].fi, d[i].se);
	}
	printf("%lld\n", ans);
	return 0;
}
