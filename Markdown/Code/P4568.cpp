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

#define N0 10010
#define M0 50010
#define N 110010
#define M 1100010
#define INF 0x7f7f7f7f
typedef pair<ll,int> pli;
#define fi first
#define se second
#define mkp make_pair
int n, m, k, s, t;
ll ans;

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

ll dis[N]; bool vis[N];
priority_queue<pli, vector<pli>, greater<pli> > q;

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
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), k=read(), s=read(), t=read(), ans=INF;
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(), z=read();
		for (int i=0; i<=n*k; i+=n) {
			add_edge(x+i, y+i, z), add_edge(y+i, x+i, z);
			if (i==n*k) continue;
			add_edge(x+i, y+i+n, 0), add_edge(y+i, x+i+n, 0);
		}
	}
	dijkstra(s);
	for (int i=0; i<=n*k; i+=n) ans=min(ans, dis[i+t]);
	printf("%lld\n", ans);
	return 0;
}
