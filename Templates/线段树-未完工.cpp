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
ll n;
ll buildSource[N];

template <typename T> struct seg {
	#define ls (p<<1)
	#define rs (p<<1|1)
	T t[N<<2], tag[N<<2];
	void push_up(ll p) {t[p]=t[ls]+t[rs];}
	void build(ll p, ll l, ll r) { // tag[p]=INF;
		tag[p]=0; if (l==r) return t[p]=buildSource[l], void(); ll mid=l+r>>1;
		build(ls, l, mid), build(rs, mid+1, r), push_up(p); // !!!
	}
	void build() {build(1, 1, n);}
	void f(ll p, ll l, ll r, T k) {t[p]+=k*(r-l+1), tag[p]+=k;} // += -> =
	void push_down(ll p, ll l, ll r) {
		/*if (!tag[p]) return;*/ ll mid=l+r>>1; // tag[p]==INF
		f(ls, l, mid, tag[p]), f(rs, mid+1, r, tag[p]), tag[p]=0; // tag[p]=INF
	}
	void modify(ll nl, ll nr, ll l, ll r, ll p, T k) {
		if (nl<=l&&r<=nr) return t[p]+=k*(r-l+1), tag[p]+=k, void(); // += -> =
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

signed main() {
	return 0;
}
