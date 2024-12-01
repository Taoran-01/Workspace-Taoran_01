#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

/*
朴素暴力搜索：处理完子树后删去全部信息，防止影响兄弟节点。
启发式合并：先处理轻儿子信息并删除，保留重儿子信息，再合并轻儿子信息。

dfs1: 划分轻重边。
dfs2: 统计答案。
upd/rem: 更新/删除单点答案。
cal/res: 计算/重置子树答案。
*/

#define N 100010
int n;
int dep[N], siz[N], son[N];
int st[N], dfq[N], tim;

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs1(int u, int fa) {
	dep[u]=dep[fa]+1, siz[u]=1;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs1(v, u), siz[u]+=siz[v];
		if (siz[v]>=siz[son[u]]) son[u]=v;
	}
}

// update | remove
void upd(int u) {}
void rem(int u) {}

// calc | reset
void cal(int u) {for (int i=st[u]; i<st[u]+siz[u]; ++i) upd(dfq[i]);}
void rst(int u) {for (int i=st[u]; i<st[u]+siz[u]; ++i) rem(dfq[i]);}

void dfs2(int u, int fa) {
	dfq[++tim]=u, st[u]=tim;
	for (int i=head[u]; i; i=e[i].nxt) if (v!=son[u]&&v!=fa) dfs2(v, u), rst(v);
	if (son[u]) dfs2(son[u], u);
	upd(u);
	for (int i=head[u]; i; i=e[i].nxt) if (v!=son[u]&&v!=fa) cal(v);
}

signed main() {
	freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	dfs1(1, 0), dfs2(1, 0);
	return 0;
}

/*
#define N 100010
#define INF 0x7f7f7f7f
int n;
int col[N], cnt[N];
ll ans[N], mx, sum;
int dep[N], siz[N], son[N];
int st[N], dfq[N], tim;

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs1(int u, int fa) {
	dep[u]=dep[fa]+1, siz[u]=1;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs1(v, u), siz[u]+=siz[v];
		if (siz[v]>=siz[son[u]]) son[u]=v;
	}
}

// update | remove
void upd(int u) {
	++cnt[col[u]];
	if (cnt[col[u]]>mx) mx=cnt[col[u]], sum=0;
	if (cnt[col[u]]==mx) sum+=col[u];
} void rem(int u) {--cnt[col[u]];}

// calc | reset
void cal(int u) {for (int i=st[u]; i<st[u]+siz[u]; ++i) upd(dfq[i]);}
void rst(int u) {sum=mx=0; for (int i=st[u]; i<st[u]+siz[u]; ++i) rem(dfq[i]);}

void dfs2(int u, int fa) {
	dfq[++tim]=u, st[u]=tim;
	for (int i=head[u]; i; i=e[i].nxt) if (v!=son[u]&&v!=fa) dfs2(v, u), rst(v);
	if (son[u]) dfs2(son[u], u);
	upd(u);
	for (int i=head[u]; i; i=e[i].nxt) if (v!=son[u]&&v!=fa) cal(v);
	ans[u]=sum;
}

// #define DEBUG

#ifdef DEBUG
#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)
#endif

signed main() {
	#ifdef DEBUG
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	#endif
	n=read();
	for (int i=1; i<=n; ++i) col[i]=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	dfs1(1, 0), dfs2(1, 0);
	for (int i=1; i<=n; ++i) printf("%lld ", ans[i]); puts("");
	#ifdef DEBUG
	fclose(stdout); chktim;
	fprintf(stderr, "CHECK: %d\n", system("fc a.out a.ans >nul"));
	#endif
	return 0;
}
*/
