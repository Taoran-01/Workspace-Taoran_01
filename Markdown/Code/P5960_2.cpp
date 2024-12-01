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

#define N 5010
#define M 5010
int n, m;

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt; ll val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

ll dis[N]; int cnt[N];
queue<int> q; bool inq[N];

bool spfa(int s) {
	memset(dis, 0xC0, sizeof(dis));
	memset(inq, 0, sizeof(inq));
	dis[s]=0, q.push(s), inq[s]=1, ++cnt[s];
	while (!q.empty()) {
		int u=q.front(); q.pop(), inq[u]=0;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (dis[u]+w<=dis[v]) continue;
			dis[v]=dis[u]+w;
			if (inq[v]) continue;
			q.push(v), inq[v]=1, ++cnt[v];
			if (cnt[v]>n+1) return 1;
		}
	}
	return 0;
}

// Longest Distance

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=m; ++i) {
		int x1=read(), x2=read(), c=read();
		add_edge(x1, x2, -c);
	}
	for (int i=1; i<=n; ++i) add_edge(n+1, i, 0);
	if (spfa(n+1)) return puts("NO"), 0;
	for (int i=1; i<=n; ++i) printf("%lld ", dis[i]);
	return 0;
}
