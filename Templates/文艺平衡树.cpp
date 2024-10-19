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

/*
给定长度为n的序列和m次操作，每次操作翻转区间[l,r]，输出操作后的序列。
*/

#define N 100010
int n, m, l, r;

namespace FHQ {
	int rt, tot;
	int ls[N], rs[N], tag[N], val[N], rnd[N], siz[N];
	void push(int p) {siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
	void down(int p) {
		if (tag[p]) tag[ls[p]]^=1, tag[rs[p]]^=1, swap(ls[p], rs[p]), tag[p]=0;
	}
	void spl(int p, int v, int &x, int &y) {
		if (!p) return x=y=0, void(); down(p);
		if (siz[ls[p]]<v) spl(rs[p], v-siz[ls[p]]-1, rs[x=p], y);
		else spl(ls[p], v, x, ls[y=p]); push(p);
	}
	int mer(int x, int y) {
		if (!x||!y) return x|y; down(x), down(y);
		if (rnd[x]<rnd[y]) return ls[y]=mer(x, ls[y]), push(y), y;
		return rs[x]=mer(rs[x], y), push(x), x;
	}
	int mer(int x, int y, int z) {return mer(x, mer(y, z));}
	int add(int v) {return val[++tot]=v, rnd[tot]=rand(), siz[tot]=1, tot;}
	void modify(int l, int r) {
		int x, y, z; spl(rt, r, x, z), spl(x, l-1, x, y), tag[y]^=1, rt=mer(x, y, z);
	}
	void prt(int p) {if(!p)return;down(p),prt(ls[p]),printf("%d ",val[p]),prt(rs[p]);}
}

signed main() {
	n=read(), m=read();
	for (int i=1; i<=n; ++i) FHQ::rt=FHQ::mer(FHQ::rt, FHQ::add(i));
	for (int i=1; i<=m; ++i) l=read(), r=read(), FHQ::modify(l, r); FHQ::prt(FHQ::rt);
	return 0;
}
