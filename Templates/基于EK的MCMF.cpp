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

#define N 5010
#define M 50010
#define INF 0x7f7f7f7f
#define v e[i].to
#define w e[i].val
#define c e[i].cost
int n, m, s, t;
int t1, t2, t3, t4;
ll max_flow, min_cost;
int head[N], tot;
int d[N], pre[N], flow[N], vis[N];
struct edge {int to, nxt, val, cost;} e[M<<1];

void add_edge(int x, int y, int z, int cost) {
	e[tot]={y, head[x], z, cost}, head[x]=tot++;
}

bool spfa() {
	memset(d, 0x7f, sizeof(d));
	memset(vis, 0, sizeof(vis));
	queue<int> q; q.push(s);
	d[s]=0, vis[s]=1, pre[s]=-1, flow[s]=INF;
	while (!q.empty()) {
		int u=q.front(); q.pop(); vis[u]=0;
		for (int i=head[u]; i!=-1; i=e[i].nxt) {
			if (!w||d[v]<=d[u]+c) continue;
			d[v]=d[u]+c, flow[v]=min(flow[u], w), pre[v]=i;
			if (!vis[v]) q.push(v), vis[v]=1;
		}
	}
	return d[t]!=INF;
}

void MCMF() {
	max_flow=0, min_cost=0;
	while (spfa()) {
		max_flow+=flow[t], min_cost+=flow[t]*d[t];
		for (int u=t, i; u!=s; u=e[i^1].to) {
			i=pre[u], e[i].val-=flow[t], e[i^1].val+=flow[t];
		}
	}
}

int main() {
	n=read(), m=read(), s=read(), t=read();
	memset(head, -1, sizeof(head));
	for (int i=1; i<=m; ++i) {
		t1=read(), t2=read(), t3=read(), t4=read();
		add_edge(t1, t2, t3, t4), add_edge(t2, t1, 0, -t4);
	}
	MCMF(), printf("%lld %lld\n", max_flow, min_cost);
	return 0;
}
