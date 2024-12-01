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

#define N0 50010
#define M0 1010
#define g(x,y) (x+y*1000)
int n;
int sx, sy;
bool d[M0][M0];
const int dirx[4]={-1,0,1,0};
const int diry[4]={0,-1,0,1};

#define N 1010000
#define M 4010000
#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[M];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

int dis[N];
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
	// freopen("P1849_11.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), sx=read(), sy=read();
	for (int i=1; i<=n; ++i) {
		int x=read(), y=read();
		d[x][y]=1;
	}
	for (int x=0; x<=1001; ++x) for (int y=0; y<1001; ++y) {
		for (int dir=0; dir<4; ++dir) {
			int x1=x+dirx[dir], y1=y+diry[dir];
			if (x1<0||x1>1001||y1<0||y1>1001) continue;
			add_edge(g(x,y), g(x1, y1), d[x1][y1]);
		}
	}
	// printf("PTS: %d | EDG: %d\n", g(1001,1001), tot);
	spfa(g(sx, sy));
	printf("%d\n", dis[g(1,1)]);
	return 0;
}
