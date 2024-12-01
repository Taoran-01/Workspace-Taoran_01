#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

// #define DEBUG
#define TC "6.011"

#ifdef DEBUG
#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)
#endif

#define N 100010
#define L 20
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int n, q; ll maxw, lstans;
int st[N], ed[N], dfq[N], tim;
int fa[N][L], dep1[N];

#define v e[i].to
#define w e[i].val
int head[N], tot; pii d[N];
struct edge {int to, nxt; ll val;} e[N<<1];
void add_edge(int x, int y, ll z) {e[++tot]={y, head[x], z}, head[x]=tot;}

template <typename T> struct BIT { // dfq
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void m(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	void modify(int x, T k) {m(x, k), m(x+1, -k);}
	void modify(int l, int r, T k) {m(l, k), m(r+1, -k);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T operator[](int x) {return g(x);}
}; BIT<ll> dep;

void dfs(int u, int f, ll in_val) { // ori
	dfq[++tim]=u, st[u]=tim, fa[u][0]=f, dep1[u]=dep1[f]+1;
	dep.modify(st[u], dep[st[f]]+in_val);
	for (int i=1; i<L; ++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u]; i; i=e[i].nxt) if (v!=f) dfs(v, u, w);
	ed[u]=tim;
}

int LCA(int x, int y) { // ori
	if (dep1[x]<dep1[y]) swap(x, y);
	for (int i=L-1; ~i; --i) if (dep1[x]-(1<<i)>=dep1[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=L-1; ~i; --i) if (fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

// dfq
ll dis(pii p) {return dep[p.fi]+dep[p.se]-2*dep[st[LCA(dfq[p.fi],dfq[p.se])]];}

namespace seg { // ALL DFQ
	#define ls (p<<1)
	#define rs ((p<<1)|1)
	#define mid ((l+r)>>1)
	struct node {pii p; ll d;} t[N<<2];
	bool operator<(node x, node y) {return x.d<y.d;}
	node operator+(node x, node y) {
		vector<node> t(6); t[0].p=x.p, t[1].p=y.p;
		t[2].p=mkp(x.p.fi, y.p.fi), t[3].p=mkp(x.p.fi, y.p.se);
		t[4].p=mkp(x.p.se, y.p.fi), t[5].p=mkp(x.p.se, y.p.se);
		for (int i=0; i<6; ++i) t[i].d=dis(t[i].p);
		sort(t.begin(), t.end()); return t.back();
	} void operator+=(node &x, node y) {x=x+y;}
	void pushup(int p) {t[p]=t[ls]+t[rs];}
	void build(int l, int r, int p) {
		if (l==r) return t[p]={mkp(l, l), 0}, void();
		build(l, mid, ls), build(mid+1, r, rs), pushup(p);
	} void build() {build(1, n, 1);}
	void modify(int nl, int nr, int l, int r, int p) {
		if (nl<=l&&r<=nr) return;
		if (nl<=mid) modify(nl, nr, l, mid, ls);
		if (nr>mid) modify(nl, nr, mid+1, r, rs);
		pushup(p);
	} void modify(int l, int r) {modify(l, r, 1, n, 1);}
	#undef mid
}

signed main() {
	#ifdef DEBUG
	char s1_[100]=""; sprintf(s1_, "%s.in", TC);
	freopen(s1_, "r", stdin);
	freopen("a.out", "w", stdout);
	#endif
	n=read(), q=read(), maxw=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read(); ll z=read();
		add_edge(x, y, z), add_edge(y, x, z);
		d[i].fi=x, d[i].se=y;
	}
	dfs(1, 0, 0);
	for (int i=1; i<n; ++i) {
		if (dep1[d[i].fi]>dep1[d[i].se]) swap(d[i].fi, d[i].se);
	}
	seg::build();
	while (q--) {
		int i=(read()+lstans)%(n-1)+1; ll k=(read()+lstans)%maxw;
		ll val=dep[st[d[i].se]]-dep[st[d[i].fi]];
		dep.modify(st[d[i].se], ed[d[i].se], -val+k);
		seg::modify(st[d[i].se], ed[d[i].se]);
		printf("%lld\n", lstans=seg::t[1].d);
	}
	#ifdef DEBUG
	fclose(stdout);
	chktim;
	char s2_[100]=""; sprintf(s2_, "fc a.out %s.out >nul", TC);
	fprintf(stderr, "CHECK: %d\n", system(s2_));
	#endif
	return 0;
}
