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

#define N 500010
// #define INF 0x7f7f7f7f7f7f7f7fLL
int n, m;
ll bs[N];
#define ls (p<<1)
#define rs ((p<<1)|1)
#define mid (l+r>>1)
struct node {
	ll lmax, rmax, pmax, sum;
	node() {lmax=rmax=pmax=sum=0;}
	node(ll x) {lmax=rmax=pmax=sum=x;}
} t[N<<2];
node operator+(node a, node b) {
	node c=node();
	c.lmax=max(a.lmax, a.sum+b.lmax);
	c.rmax=max(b.rmax, b.sum+a.rmax);
	if (a.rmax<0&&b.lmax<0) c.pmax=max(a.rmax, b.lmax);
	else c.pmax=max(a.rmax, 0LL)+max(b.lmax, 0LL);
	c.pmax=max(c.pmax, max(a.pmax, b.pmax));
	c.sum=a.sum+b.sum; return c;
}
void push_up(int p) {t[p]=t[ls]+t[rs];}
void build(int l, int r, int p) {
	if (l==r) return t[p]=node(bs[l]), void();
	build(l, mid, ls), build(mid+1, r, rs), push_up(p);
} void build() {build(1, n, 1);}
void modify(int x, int l, int r, int p, ll k) {
	if (l==r) return t[p]=node(k), void();
	if (x<=mid) modify(x, l, mid, ls, k);
	if (x>mid) modify(x, mid+1, r, rs, k);
	push_up(p);
} void modify(int x, ll k) {modify(x, 1, n, 1, k);}
node query(int nl, int nr, int l, int r, int p) {
	if (nl<=l&&r<=nr) return t[p];
	if (nl<=mid&&nr>mid) return query(nl, nr, l, mid, ls)+query(nl, nr, mid+1, r, rs);
	if (nl<=mid) return query(nl, nr, l, mid, ls);
	if (nr>mid) return query(nl, nr, mid+1, r, rs);
} ll query(int l, int r) {return query(l, r, 1, n, 1).pmax;}
#undef ls
#undef rs
#undef mid

signed main() {
	// freopen("P4513.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) bs[i]=read(); build();
	while (m--) {
		int opt=read(), x=read(), y=read(), k=0;
		if (opt==1) {if (x>y) swap(x, y); printf("%d\n", query(x, y));}
		if (opt==2) modify(x, y);
	}
	return 0;
}
