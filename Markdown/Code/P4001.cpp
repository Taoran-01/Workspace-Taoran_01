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

#define N0 1020
#define N 2500002
#define M 6500006
typedef pair<ll,int> pli;
#define fi first
#define se second
#define mkp make_pair
int n, m, s, t;

int get(int i, int j, bool c) {return i*(m+2)*2+j*2+c;}

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

ll dis[N]; bool vis[N];
priority_queue<pli, vector<pli>, greater<pli>> q;
void dijkstra(int s) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[s]=0, q.push(mkp(0, s));
	while (!q.empty()) {
		int u=q.top().se; q.pop();
		if (vis[u]) continue; vis[u]=1;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (dis[u]+w>=dis[v]) continue;
			dis[v]=dis[u]+w, q.push(mkp(dis[v], v));
		}
	}
}

signed main() {
	// freopen("P4001_2.in", "r", stdin);
	n=read(), m=read(), s=N-2, t=N-1;
	for (int i=1; i<=n; ++i) for (int j=1; j<m; ++j) {
		int x=get(i-1, j, 0), y=get(i, j, 1), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	for (int i=1; i<n; ++i) for (int j=1; j<=m; ++j) {
		int x=get(i, j-1, 1), y=get(i, j, 0), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	for (int i=1; i<n; ++i) for (int j=1; j<m; ++j) {
		int x=get(i, j, 0), y=get(i, j, 1), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	for (int i=1; i<n; ++i) add_edge(s, get(i, 0, 1), 0);
	for (int i=1; i<n; ++i) add_edge(get(i, m, 0), t, 0);
	for (int j=1; j<m; ++j) add_edge(s, get(n, j, 1), 0);
	for (int j=1; j<m; ++j) add_edge(get(0, j, 0), t, 0);
	dijkstra(s);
	printf("%lld\n", dis[t]);
	return 0;
}
