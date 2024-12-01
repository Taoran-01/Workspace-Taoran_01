#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
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

#define N 2010
#define M 10010
int n, m;
int k[N], ind[N];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[M<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

queue<int> q;
vector<int> d[N];
bool vis[N];

void dfs(int u) {
	vis[u]=1;
	for (int i=head[u]; i; i=e[i].nxt) if (!vis[v]) dfs(v);
}

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) k[i]=read();
	while (m--) {int x=read(), y=read(); add_edge(y, x), ++ind[x];}
	for (int i=1; i<=n; ++i) if (ind[i]==0) q.push(i);
	while (!q.empty()) {
		int u=q.front(); q.pop();
		d[u[k]].push_back(u);
		for (int i=head[u]; i; i=e[i].nxt) {
			k[v]=min(k[v], k[u]-1);
			--ind[v]; if (ind[v]==0) q.push(v);
		}
	}
	for (int i=1; i<=n; ++i) for (int x:d[i]) printf("%d ", x); puts("");
	for (int x=1; x<=n; ++x) {
		memset(vis, 0, sizeof(vis)); int rem=n;
		dfs(x);
		for (int i=n; i; --i) {
			for (int x:d[i]) if (!vis[x]) --rem;
			if (rem>=i) break;
		}
		printf("%d ", rem);
	}
	return 0;
}
