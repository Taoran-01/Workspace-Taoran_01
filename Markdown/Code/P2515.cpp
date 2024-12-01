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

#define N 110
#define M 510
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int m;

namespace ST2 {
	int n, rt;
	int c[N], val[N];
	bool vis[N];
	int f[N][M], ans;

	#define v e[i].to
	int head[N], tot, ind[N];
	struct edge {int to, nxt;} e[M<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot, ++ind[y];}

	void dfs(int u) {
		vis[u]=1;
		for (int i=m; i>=c[u]; --i) f[u][i]=val[u];
		for (int i=head[u]; i; i=e[i].nxt) {
			if (!vis[v]) dfs(v);
			// ITEM U MUST BE CHOSEN !!!
			for (int j=m; j>=c[u]; --j) for (int w=0; w<=j-c[u]; ++w) {
				f[u][j]=max(f[u][j], f[u][j-w]+f[v][w]);
			}
		}
	}

	void main() {
		for (int i=1; i<=n; ++i) if (!ind[i]) add_edge(rt, i);
		dfs(rt);
		printf("%d\n", f[rt][m]);
	}
}

namespace ST1 {
	int n, rt;
	int c[N], val[N];
	int dfn[N], low[N], tim;
	int stk[N], top; bool instk[N];
	vector<int> scc[N]; int col[N], &cnt=ST2::n;
	set<pii> d;

	#define v e[i].to
	int head[N], tot;
	struct edge {int to, nxt;} e[N<<1];
	void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

	void dfs(int u) {
		dfn[u]=low[u]=++tim, stk[++top]=u, instk[u]=1;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (!dfn[v]) dfs(v), low[u]=min(low[u], low[v]);
			else if (instk[v]) low[u]=min(low[u], dfn[v]);
		}
		if (dfn[u]!=low[u]) return; ++cnt;
		while (stk[top]!=u) scc[cnt].push_back(stk[top]), col[stk[top]]=cnt, \
			instk[stk[top--]]=0;
		scc[cnt].push_back(stk[top]), col[stk[top]]=cnt, instk[stk[top--]]=0;
	}

	void main() {
		n=read(), m=read(), rt=n+1;
		for (int i=1; i<=n; ++i) c[i]=read();
		for (int i=1; i<=n; ++i) val[i]=read();
		for (int i=1; i<=n; ++i) {int x=read(); add_edge(x==0?rt:x, i);}
		for (int i=1; i<=n+1; ++i) if (!dfn[i]) dfs(i); ST2::rt=col[rt];
		for (int i=1; i<=n; ++i) ST2::c[col[i]]+=c[i], ST2::val[col[i]]+=val[i];
		for (int u=1; u<=n+1; ++u) for (int i=head[u]; i; i=e[i].nxt) {
			if (col[u]==col[v]) continue; pii p=mkp(col[u],col[v]);
			if (d.count(p)) continue; d.insert(p);
			ST2::add_edge(col[u], col[v]);
		}
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	ST1::main();
	ST2::main();
	return 0;
}
