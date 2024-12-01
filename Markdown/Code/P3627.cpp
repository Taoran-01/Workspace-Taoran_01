#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 500010
#define M 500010
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair

namespace ST2 {
	int n, s, nt;
	vector<int> t;
	int a[N];
	int f[N], ans;

	#define v e[i].to
	int head[N], tot;
	struct edge {int to, nxt;} e[M<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

	int dfs(int u) {
		if (f[u]) return f[u];
		for (int i=head[u]; i; i=e[i].nxt) f[u]=max(f[u], dfs(v));
		f[u]+=a[u];
		return f[u];
	}

	void main() {
		for (int x:t) ans=max(ans, dfs(x));
		printf("%d\n", ans);
	}
}

namespace ST1 {
	int n, m, s, nt;
	vector<int> t;
	int a[N];

	int dfn[N], low[N], tim;
	vector<int> scc[N]; int col[N], cnt;
	bool instk[N];
	int stk[N], top;

	#define v e[i].to
	int head[N], tot;
	struct edge {int to, nxt;} e[M<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

	set<pii> d;

	void dfs(int u) {
		dfn[u]=low[u]=++tim, stk[++top]=u, instk[u]=1;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (!dfn[v]) dfs(v), low[u]=min(low[u], low[v]);
			else if (instk[v]) low[u]=min(low[u], dfn[v]);
		}
		if (low[u]!=dfn[u]) return; ++cnt;
		while (stk[top]!=u) scc[cnt].push_back(stk[top]), col[stk[top]]=cnt, \
			instk[stk[top--]]=0;
		scc[cnt].push_back(stk[top]), col[stk[top]]=cnt, instk[stk[top--]]=0;
	}

	void main() {
		n=read(), m=read();
		for (int i=1; i<=m; ++i) {int x=read(), y=read(); add_edge(x, y);}
		for (int i=1; i<=n; ++i) a[i]=read();
		s=read(), nt=read(), t.resize(nt);
		for (int i=0; i<nt; ++i) t[i]=read();
		dfs(s);
		ST2::n=cnt, ST2::s=col[s], ST2::nt=nt, ST2::t.swap(t);
		for (int &x:ST2::t) x=col[x];
		for (int i=1; i<=cnt; ++i) for (auto x:scc[i]) ST2::a[i]+=a[x];
		for (int u=1; u<=n; ++u) for (int i=head[u]; i; i=e[i].nxt) {
			if (col[u]==col[v]) continue;
			if (d.count(mkp(v,u))) continue; d.insert(mkp(v,u));
			ST2::add_edge(col[v], col[u]); // opposite
		}
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	ST1::main();
	ST2::main();
	return 0;
}
