#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
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
#define M 3000010
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair

namespace ST2 {
	int n, c[N], f[N], ans;

	#define v e[i].to
	int head[N], tot;
	struct edge {int to, nxt;} e[M<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

	int dfs(int u) {
		// fprintf(stderr, "%d\n", u);
		if (f[u]) return f[u];
		for (int i=head[u]; i; i=e[i].nxt) f[u]=max(f[u], dfs(v));
		return f[u]+=c[u];
	}

	void main() {
		// fprintf(stderr, "---===---\n");
		for (int i=1; i<=n; ++i) ans=max(ans, dfs(i));
		// for (int i=1; i<=n; ++i) fprintf(stderr, "%d\n", f[i]);
		printf("%d\n", ans);
	}
}

namespace ST1 {
	#define V 1000010
	int n0, R, C, n; bool c[N];
	unordered_map<int,int> ax, ay; unordered_map<int,set<int>> dx;
	map<pii,int> d; vector<pii> seq; set<pii> ed;
	int dfn[N], low[N], tim;
	int stk[N], top; bool instk[N];
	int col[N], &cnt=ST2::n;

	#define v e[i].to
	int head[N], tot;
	struct edge {int to, nxt;} e[M<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

	void dfs(int u) {
		dfn[u]=low[u]=++tim, stk[++top]=u, instk[u]=1;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (!dfn[v]) dfs(v), low[u]=min(low[u], low[v]);
			else if (instk[v]) low[u]=min(low[u], dfn[v]);
		}
		if (dfn[u]!=low[u]) return; ++cnt;
		while (stk[top]!=u) col[stk[top]]=cnt, \
			instk[stk[top--]]=0;
		col[stk[top]]=cnt, instk[stk[top--]]=0;
	}

	void main() {
		n0=read(), R=read(), C=read();
		for (int i=1; i<=n0; ++i) {
			int x=read(), y=read(), opt=read(), p=++n; c[p]=1;
			dx[x].insert(y), d[mkp(x,y)]=p;
			if (!ax.count(x)) ax[x]=++n; add_edge(ax[x], p);
			if (!ay.count(y)) ay[y]=++n; add_edge(ay[y], p);
			if (opt==1) add_edge(p, ax[x]); if (opt==2) add_edge(p, ay[y]);
			if (opt==3) seq.push_back(mkp(x,y));
		}
		// for (auto i:d) {
		// 	fprintf(stderr, "(%d,%d)=%d\n", i.fi.fi, i.fi.se, i.se); //
		// }
		// for (auto i:ax) fprintf(stderr, "ln#%d -> %d\n", i.fi, i.se);
		// for (auto i:ay) fprintf(stderr, "co#%d -> %d\n", i.fi, i.se);
		for (pii s:seq) for (int x1=s.fi-1; x1<=s.fi+1; ++x1) {
			if (!dx.count(x1)||dx[x1].empty()) continue;
			auto y1=dx[x1].lower_bound(s.se-1);
			for (; y1!=dx[x1].end()&&*y1<=s.se+1; ++y1) add_edge(d[s], \
				d[mkp(x1,*y1)]);
		}
		for (int i=1; i<=n; ++i) if (!dfn[i]) dfs(i);
		for (int i=1; i<=n; ++i) ST2::c[col[i]]+=c[i];
		// for (int i=1; i<=n; ++i) fprintf(stderr, "%d=>%d\n", i, col[i]); //
		for (int u=1; u<=n; ++u) for (int i=head[u]; i; i=e[i].nxt) {
			// fprintf(stderr, "%d->%d %d->%d\n", u, v, col[u], col[v]);
			pii p=mkp(col[u],col[v]); if (p.fi==p.se||ed.count(p)) continue;
			ed.insert(p); ST2::add_edge(col[u], col[v]);
		}
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	ST1::main();
	ST2::main();
	return 0;
}
