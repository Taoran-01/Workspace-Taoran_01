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

#define N 10010
#define M 50010
#define INF 0x7f7f7f7f
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int n, m, b;
int f[N];
ll mid;

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

bool vis[N]; int dis[N];
priority_queue<pii, vector<pii>, greater<pii>> q;
void dijkstra(int s) {
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	if (f[s]>mid) return;
	dis[s]=0, q.push(mkp(0, s));
	while (!q.empty()) {
		int u=q.top().se; q.pop();
		if (vis[u]) continue; vis[u]=1;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (f[v]>mid) continue;
			if (dis[u]+w>=dis[v]) continue;
			dis[v]=dis[u]+w, q.push(mkp(dis[v], v));
		}
	}
}

bool chk() {
	dijkstra(1);
	return dis[n]<=b;
}

signed main() {
	// freopen("P1462_1.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), m=read(), b=read();
	for (int i=1; i<=n; ++i) f[i]=read();
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	ll l=1, r=INF, ans=0;
	while (l<r) {
		mid=(l+r)>>1;
		if (chk()) r=mid, ans=mid;
		else l=mid+1;
	}
	if (!ans) puts("AFK");
	else printf("%lld\n", ans);
	return 0;
}
