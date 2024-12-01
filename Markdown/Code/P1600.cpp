#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 300010
#define L 30
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int n, m;
int dep[N], siz[N];
int fa[N][L];
int w[N], ans[N];
vector<pii> seq[N];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs1(int u, int f) {
	dep[u]=dep[f]+1, fa[u][0]=f;
	for (int i=1; i<L; ++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u]; i; i=e[i].nxt) if (v!=f) dfs1(v, u);
}

int LCA(int x, int y) {
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=L-1; ~i; --i) if (dep[fa[x][i]]>=dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=L-1; ~i; --i) while (fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

namespace seg {
	#define ls t[p].l
	#define rs t[p].r
	#define mid ((l+r)>>1)
	int rt[N], tot;
	struct node {int d, l, r;} t[(N<<2)*(L+2)];
	int nd(int &x) {t[x=++tot]=node(); return x;}
	void modify(int x, int l, int r, int &p, int k) {
		if (!p) nd(p);
		if (l==r) return t[p].d+=k, void();
		if (x<=mid) modify(x, l, mid, ls, k);
		if (x>mid) modify(x, mid+1, r, rs, k);
	} void modify(int p, int x, int k) {modify(x, -n, n, rt[p], k);}
	int query(int x, int l, int r, int p) {
		if (l==r) return t[p].d; int res=0;
		if (ls&&x<=mid) res+=query(x, l, mid, ls);
		if (rs&&x>mid) res+=query(x, mid+1, r, rs);
		return res;
	} int query(int p, int x) {return query(x, -n, n, rt[p]);}
	void merge(int l, int r, int &p1, int p2) {
		if (!p1||!p2) return p1=p1|p2, void();
		if (l==r) return t[p1].d+=t[p2].d, void();
		merge(l, mid, t[p1].l, t[p2].l), merge(mid+1, r, t[p1].r, t[p2].r);
	} void merge(int p1, int p2) {merge(-n, n, rt[p1], rt[p2]);}
}

void dfs2(int u) {
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa[u][0]) continue;
		dfs2(v), seg::merge(u, v);
	}
	ans[u]+=seg::query(u, dep[u]+w[u]);
	ans[u]+=seg::query(u, dep[u]-w[u]);
	if (w[u]==0) ans[u]>>=1;
}

signed main() {
	// freopen("running20.in", "r", stdin);
	// freopen("running20.out", "w", stdout);
	n=read(), m=read(), dep[0]=-1;
	for (int i=1; i<n; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	dfs1(1, 0);
	for (int i=1; i<=n; ++i) w[i]=read();
	while (m--) {
		int s=read(), t=read(), l=LCA(s,t);
		int df=dep[l]-(dep[s]-dep[l]);
		seg::modify(s, dep[s], 1), seg::modify(fa[l][0], dep[s], -1);
		seg::modify(t, df, 1), seg::modify(l, df, -1);
	}
	dfs2(1);
	for (int i=1; i<=n; ++i) printf("%d ", ans[i]); puts("");
	return 0;
}
