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

#define N 500010
#define gcd __gcd
int n, m;
ll a[N];

#define ls (p<<1)
#define rs ((p<<1)|1)
#define mid ((l+r)>>1)
struct node {ll s, g;} t[N<<2];
node operator+(node x, node y) {
	node z={x.s+y.s, gcd(x.g, y.g)}; return z;
} void operator+=(node &x, node y) {x=x+y;}

void pushup(int p) {t[p]=t[ls]+t[rs];}

void build(int l, int r, int p) {
	if (l==r) return t[p].s=t[p].g=a[l], void();
	build(l, mid, ls), build(mid+1, r, rs), pushup(p);
} void build() {build(1, n+1, 1);}

void modify(int x, int l, int r, int p, ll k) {
	// fprintf(stderr, "MODIFY: p%d=[%d %d] x=%d\n", p, l, r, x);
	if (l==r) return t[p].s+=k, t[p].g+=k, void();
	if (x<=mid) modify(x, l, mid, ls, k);
	if (x>mid) modify(x, mid+1, r, rs, k);
	pushup(p);
} void modify(int x, ll k) {modify(x, 1, n+1, 1, k);}

node query(int nl, int nr, int l, int r, int p) {
	// fprintf(stderr, "QUERY : p(%d)=[%d %d] i=[%d %d]\n", p, l, r, nl, nr);
	if (nl<=l&&r<=nr) return t[p];
	node res={0,0};
	if (nl<=mid) res+=query(nl, nr, l, mid, ls);
	if (nr>mid) res+=query(nl, nr, mid+1, r, rs);
	return res;
} node query(int l, int r) {return query(l, r, 1, n+1, 1);}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=n; i; --i) a[i]-=a[i-1];
	build();
	while (m--) {
		char opt=getchar(); while (opt!='C'&&opt!='Q') opt=getchar();
		int l=read(), r=read(); ll k=0;
		if (opt=='C') {
			k=read(), modify(l, k), modify(r+1, -k);
		} else if (opt=='Q') {
			if (l==r) {printf("%lld\n", abs(query(1, l).s)); continue;}
			ll a=query(1, l).s, b=query(l+1, r).g;
			printf("%lld\n", abs(gcd(a,b)));
		} else fprintf(stderr, "Line #%d: %c\n", __LINE__, opt);
	}
	return 0;
}
