#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 500010
#define INF 0x7f7f7f7f
int n, m;

#define DEBUG

#define ls (p<<1)
#define rs ((p<<1)|1)
#define mid ((l+r)>>1)
struct node {
	int cntl, cntr, cnt; bool clr;
	int tag;
	node() {cntl=cntr=cnt=clr=0, tag=-1;}
	node(int l, int r) {cntl=cntr=cnt=r-l+1, clr=1, tag=-1;}
} t[N<<2];
node operator+(node a, node b) {
	#ifdef DEBUG
	#endif
	node c=node();
	if (a.clr) c.cntl=a.cntl+b.cntl;
	else c.cntl=a.cntl;
	if (b.clr) c.cntr=a.cntr+b.cntr;
	else c.cntr=b.cntr;
	c.cnt=max(max(a.cnt, b.cnt), a.cntr+b.cntl);
	if (a.clr&&b.clr) c.clr=1;
	#ifdef DEBUG
	fprintf(stderr, "merge: %d[l:%d r:%d t:%d] %d[l:%d r:%d t:%d] -> %d[l:%d r:%d t:%d]\n",
	a.clr, a.cntl, a.cntr, a.cnt, b.clr, b.cntl, b.cntr, b.cnt, c.clr, c.cntl, c.cntr, c.cnt);
	#endif
	return c;
}
void pushup(int p) {t[p]=t[ls]+t[rs];}
void pushdn(int l, int r, int p) {
	if (t[p].tag==-1) return;
	t[p].clr=!t[p].tag;
	t[p].cntl=t[p].cntr=t[p].cnt=t[p].tag*(r-l+1);
	t[ls].tag=t[rs].tag=t[p].tag, t[p].tag=-1;
}
void build(int l, int r, int p) {
	if (l==r) return t[p]=node(l, r), void();
	build(l, mid, ls), build(mid+1, r, rs), pushup(p);
} void build() {build(1, n, 1);}
void modify(int nl, int nr, int l, int r, int p, bool k) {
	#ifdef DEBUG
	fprintf(stderr, "modify: [%d %d] (%d)[%d %d] %d\n", nl, nr, p, l, r, k);
	#endif
	if (nl<=l&&r<=nr) {
		t[p].tag=k, t[p].clr=!k;
		t[p].cntl=t[p].cntr=t[p].cnt=r-l+1;
		return;
	}
	pushdn(l, r, p);
	if (nl<=mid) modify(nl, nr, l, mid, ls, k);
	if (nr>mid) modify(nl, nr, mid+1, r, rs, k);
	pushup(p);
} void modify(int l, int r, bool k) {modify(l, r, 1, n, 1, k);}
int query(int l, int r, int p, int x) {
	#ifdef DEBUG
	fprintf(stderr, "query: (%d)[%d %d] %d\n", p, l, r, x);
	#endif
	pushdn(l, r, p);
	if (x==0) return r;
	if (t[p].cnt<x) return 0;
	if (l==r) return l;
	if (t[ls].cnt>=x) return query(l, mid, ls, x);
	if (t[ls].cntr+t[rs].cntl>=x) return query(l, mid, ls, t[ls].cntr);
	return query(mid+1, r, rs, x);
} int query(int x) {return query(1, n, 1, x);}

#ifdef DEBUG
bool chkclr(int nl, int nr, int l, int r, int p) {
	if (nl<=l&&r<=nr) return t[p].clr;
	bool res=1;
	if (nl<=mid) res&=chkclr(nl, nr, l, mid, ls);
	if (nr>mid) res&=chkclr(nl, nr, mid+1, r, rs);
	return res;
} bool chkclr(int l, int r) {return chkclr(l, r, 1, n, 1);}
void prt(int l, int r, int p) {
	printf("(%d)[%d %d] %d [l:%d r:%d t:%d]\n", p, l, r, 
	t[p].clr, t[p].cntl, t[p].cntr, t[p].cnt);
	if (l==r) return;
	prt(l, mid, ls), prt(mid+1, r, rs);
} void prt() {prt(1, n, 1);}
#endif

signed main() {
	freopen("a.in", "r", stdin);
	n=read(), m=read(), build();
	#ifdef DEBUG
	prt();
	#endif
	while (m--) {
		int opt=read();
		if (opt==1) {
			int x=read(), res=query(x);
			printf("%d\n", res);
			if (res) {
				#ifdef DEBUG
				assert(chkclr(res, res+x-1)==1);
				#endif
				modify(res, res+x-1, 1);
			}
		} else if (opt==2) {
			int l=read(), r=l+read()-1;
			modify(l, r, 0);
		} else fprintf(stderr, "%d: %d\n", __LINE__, opt);
		#ifdef DEBUG
		prt();
		#endif
	}
	return 0;
}
