#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

/*
n个节点，m条带权边，起点s，终点t，求s到t的最大流
*/

#define N 210
#define M 5010
#define INF 0x3f3f3f3f
#define v e[i].to
#define w e[i].val
int n, m, s, t;
int t1, t2, t3;
ll max_flow;
int head[N], cur[N], tot;
int d[N], vis[N];

struct edge {
	int to, nxt, val;
} e[M<<1];

void add_edge(int x, int y, int z) {
	e[tot]={y, head[x], z}, head[x]=tot++;
	e[tot]={x, head[y], 0}, head[y]=tot++;
}

bool bfs() {
	memset(d, -1, sizeof(d));
	queue<int> q; q.push(s), d[s]=0;
	while (!q.empty()) {
		int u=q.front(); q.pop();
		for (int i=head[u]; i!=-1; i=e[i].nxt) {
			if (w==0||d[v]!=-1) continue;
			d[v]=d[u]+1, q.push(v);
		}
	}
	return d[t]!=-1;
}

int dfs(int u, int minf) {
	if (u==t||minf==0) return minf;
	int f, flow=0;
	for (int i=cur[u]; i!=-1; i=e[i].nxt) {
		cur[u]=i;
		if (d[v]!=d[u]+1||!(f=dfs(v, min(minf, w)))) continue;
		minf-=f, flow+=f;
		e[i].val-=f, e[i^1].val+=f;
		if (minf==0) return flow;
	}
	return flow;
}

void Dinic() {
	max_flow=0;
	while (bfs()) {
		for (int i=1; i<=n; ++i) cur[i]=head[i];
		max_flow+=dfs(s, INF);
	}
}

// 1. head数组初始化为-1
// 2. 检查数据范围
// 3. 调试失败删除cur数组，改为head数组

signed main() {
	n=read(), m=read(), s=read(), t=read();
	memset(head, -1, sizeof(head));
	for (int i=1; i<=m; ++i) {
		t1=read(), t2=read(), t3=read();
		add_edge(t1, t2, t3);
	}
	Dinic(), printf("%lld\n", max_flow);
	return 0;
}
