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
查询树上两点的最近公共祖先。
倍增法：O(log n)
fa[u][i] 表示点 u 的 2^i 级祖先。
*/

#define N 500010
#define L 20
int n, m, rt;
int dep[N], fa[N][L];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs(int u, int f) {
	fa[u][0]=f, dep[u]=dep[f]+1;
	for (int i=1; i<L; ++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u]; i; i=e[i].nxt) if (v!=f) dfs(v, u);
}

int lca(int x, int y) {
	if (dep[x]<dep[y]) swap(x, y);
	for (int i=L-1; ~i; --i) if (dep[x]-(1<<i)>=dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=L-1; ~i; --i) if (fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
	return fa[x][0];
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), rt=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	dfs(rt, 0);
	while (m--) {
		int x=read(), y=read(), l=lca(x,y);
		printf("%d\n", l);
	}
	return 0;
}
