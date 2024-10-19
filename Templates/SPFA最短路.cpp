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

#define N 300010
#define M 300010
#define INF 0x3f3f3f3f3f3f3f3fLL
int n, m;
int t1, t2, t3;

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt; ll val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

ll dis[N];
queue<int> q; bool inq[N];

void spfa(int s) {
	memset(dis, 0x3f, sizeof(dis));
	memset(inq, 0, sizeof(inq));
	dis[s]=0, q.push(s), inq[s]=1;
	while (!q.empty()) {
		int u=q.front(); q.pop(), inq[u]=0;
		for (int i=head[u]; i; i=e[i].nxt) {
			if (dis[u]+w>=dis[v]) continue;
			dis[v]=dis[u]+w;
			if (!inq[v]) q.push(v), inq[v]=1;
		}
	}
}

signed main() {
	// freopen("e.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=m; ++i) {
		t1=read(), t2=read(), t3=read();
		if (t1==t2) continue;
		add_edge(t1, t2, t3);
	}
	spfa(1);
	for (int i=1; i<=n; ++i) printf("%lld ", dis[i]>=INF?-1LL:dis[i]);
	return 0;
}
