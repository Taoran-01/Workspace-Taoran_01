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


#define N 1000010
ll n, d[N], st;
ll buildSource[N];

template <typename T> struct seg {
	#define ls (p<<1)
	#define rs (p<<1|1)
	T t[N<<2], tag[N<<2];
	void push_up(ll p) {t[p]=t[ls]+t[rs];}
	void build(ll p, ll l, ll r) {
		tag[p]=0; if (l==r) return t[p]=buildSource[l], void(); ll mid=l+r>>1;
		build(ls, l, mid), build(rs, mid+1, r), push_up(p);
	}
	void build() {build(1, 1, n);}
	void f(ll p, ll l, ll r, T k) {t[p]+=k*(r-l+1), tag[p]+=k;}
	void push_down(ll p, ll l, ll r) {
		ll mid=l+r>>1; f(ls, l, mid, tag[p]), f(rs, mid+1, r, tag[p]), tag[p]=0;
	}
	void modify(ll nl, ll nr, ll l, ll r, ll p, T k) {
		if (nl<=l&&r<=nr) return t[p]+=k*(r-l+1), tag[p]+=k, void();
		push_down(p, l, r); ll mid=l+r>>1;
		if (nl<=mid) modify(nl, nr, l, mid, ls, k);
		if (nr>mid) modify(nl, nr, mid+1, r, rs, k);
		push_up(p);
	}
	void modify(ll l, ll r, T k) {modify(l, r, 1, n, 1, k);}
	T query(ll nl, ll nr, ll l, ll r, ll p) {
		if (nl<=l&&r<=nr) return t[p];
		push_down(p, l, r); T res=0; ll mid=l+r>>1;
		if (nl<=mid) res+=query(nl, nr, l, mid, ls);
		if (nr>mid) res+=query(nl, nr, mid+1, r, rs);
		return res;
	}
	T query(ll l, ll r) {return query(l, r, 1, n, 1);}
};

seg<ll> tr;

signed main() {
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n=read(), d[1]=read();
	for (ll i=1; i<=n; ++i) buildSource[i]=1;
	tr.build();
	for (ll i=2; i<=n; ++i) {
		d[i]=read();
		if (d[i]>d[i-1]) tr.modify(i, i, tr.query(i-1, i-1)), st=0;
		if (d[i]==d[i-1]) continue;
		if (d[i]<d[i-1]) {
			if (!st) st=i-1;
			tr.modify(st, i-1, 1);
		}
	}
	printf("%lld\n", tr.query(1, n));
	return 0;
}
