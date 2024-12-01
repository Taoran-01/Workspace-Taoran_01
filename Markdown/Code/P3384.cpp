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

#define N 200010
#define M N
int n, m, rt, mod;
int a[N];
int fa[N], dep[N], siz[N], son[N];
int dfn[N], st[N], tim;
int top[N];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs1(int u, int f, int d) {
	fa[u]=f, dep[u]=d, siz[u]=1; int maxson=-1;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==f) continue;
		dfs1(v, u, d+1), siz[u]+=siz[v];
		if (siz[v]>maxson) son[u]=v, maxson=siz[v];
	}
}

void dfs2(int u, int topf) {
	dfn[u]=++tim, st[tim]=u, top[u]=topf;
	if (!son[u]) return;
	dfs2(son[u], topf);
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v, v);
	}
}

template <typename T> struct seg {
	#define ls (p<<1)
	#define rs (p<<1|1)
	T t[N<<2], tag[N<<2];
	void push_up(ll p) {t[p]=(t[ls]+t[rs])%mod;}
	void build(ll p, ll l, ll r) {
		tag[p]=0; if (l==r) return t[p]=a[st[l]]%mod, void(); ll mid=l+r>>1;
		build(ls, l, mid), build(rs, mid+1, r), push_up(p);
	}
	void build() {build(1, 1, n);}
	void f(ll p, ll l, ll r, T k) {t[p]=(t[p]+k*(r-l+1))%mod, tag[p]=(tag[p]+k)%mod;}
	void push_down(ll p, ll l, ll r) {
		ll mid=l+r>>1; f(ls, l, mid, tag[p]), f(rs, mid+1, r, tag[p]), tag[p]=0;
	}
	void modify(ll nl, ll nr, ll l, ll r, ll p, T k) {
		if (nl<=l&&r<=nr) {
			return t[p]=(t[p]+k*(r-l+1))%mod, tag[p]=(tag[p]+k)%mod, void();
		}
		push_down(p, l, r); ll mid=l+r>>1;
		if (nl<=mid) modify(nl, nr, l, mid, ls, k);
		if (nr>mid) modify(nl, nr, mid+1, r, rs, k);
		push_up(p);
	}
	void modify(ll l, ll r, T k) {modify(l, r, 1, n, 1, k);}
	T query(ll nl, ll nr, ll l, ll r, ll p) {
		if (nl<=l&&r<=nr) return t[p];
		push_down(p, l, r); T res=0; ll mid=l+r>>1;
		if (nl<=mid) res=(res+query(nl, nr, l, mid, ls))%mod;
		if (nr>mid) res=(res+query(nl, nr, mid+1, r, rs))%mod;
		return res;
	}
	T query(ll l, ll r) {return query(l, r, 1, n, 1);}
}; seg<int> t;

int query_line(int x, int y) {
	int ans=0;
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x, y);
		ans=(ans+t.query(dfn[top[x]], dfn[x]))%mod;
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x, y);
	ans=(ans+t.query(dfn[x], dfn[y]))%mod;
	return ans;
}

void modify_line(int x, int y, int k) {
	k%=mod;
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x, y);
		t.modify(dfn[top[x]], dfn[x], k);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x, y);
	t.modify(dfn[x], dfn[y], k);
}

int query_tree(int x) {return t.query(dfn[x], dfn[x]+siz[x]-1);}
void modify_tree(int x, int k) {t.modify(dfn[x], dfn[x]+siz[x]-1, k);}

signed main() {
	// freopen("c.in", "r", stdin);
	n=read(), m=read(), rt=read(), mod=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<n; ++i) {
		int t1=read(), t2=read();
		add_edge(t1, t2), add_edge(t2, t1);
	}
	dfs1(rt, 0, 1), dfs2(rt, rt), t.build();
	while (m--) {
		int k=read(), x=read(), y=0, z=0;
		if (k==1) y=read(), z=read(), modify_line(x, y, z);
		else if (k==2) y=read(), printf("%d\n", query_line(x, y));
		else if (k==3) z=read(), modify_tree(x, z);
		else if (k==4) printf("%d\n", query_tree(x));
		// for (int i=1; i<=n<<2; ++i) printf("%d ", t.t[i]); puts("");
	}
	return 0;
}
