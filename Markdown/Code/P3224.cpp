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
int n, m, q;
int idx[N], fa[N];
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}

#define mid (l+r>>1)
int rt[N], tot;
struct node {
	int ls, rs, d;
	node() {ls=rs=d=0;} // !!! d != 1 !!!
} t[N<<6];
int nd() {return t[++tot]=node(), t[tot].d=1, tot;}
int insert(int l, int r, int x) {
	int p=nd(); if (l==r) return p;
	if (x<=mid) t[p].ls=insert(l, mid, x);
	if (x>mid) t[p].rs=insert(mid+1, r, x);
	return p;
} int insert(int x) {return insert(1, n, x);}
int query(int l, int r, int p, int k) {
	if (k>t[p].d) return -1; if (l==r) return idx[l];
	if (t[p].ls&&t[t[p].ls].d>=k) return query(l, mid, t[p].ls, k);
	else return query(mid+1, r, t[p].rs, k-t[t[p].ls].d);
} int query(int p, int k) {return query(1, n, p, k);}
int merge(int l, int r, int px, int py) {
	if (!px||!py) return px|py;
	int res=nd(); t[res].d=t[px].d+t[py].d;
	t[res].ls=merge(l, mid, t[px].ls, t[py].ls);
	t[res].rs=merge(mid+1, r, t[px].rs, t[py].rs);
	return res;
} int merge(int px, int py) {return merge(1, n, px, py);}
#undef mid

void mer(int x, int y) {
	int fx=find(x), fy=find(y);
	if (fx==fy) return;
	fa[fx]=fy, rt[fy]=merge(rt[fx], rt[fy]);
}

signed main() {
	// freopen("P3224.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) fa[i]=i;
	for (int i=1; i<=n; ++i) {int x=read(); rt[i]=insert(x), idx[x]=i;}
	while (m--) {int t1=read(), t2=read(); mer(t1, t2);}
	q=read(); while (q--) {
		char ch=getchar(); while (ch!='B'&&ch!='Q') ch=getchar();
		int x=read(), y=read();
		if (ch=='Q') x=find(x), printf("%d\n", query(rt[x], y));
		else mer(x, y);
	}
	return 0;
}
