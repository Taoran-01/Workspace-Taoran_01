#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <ext/pb_ds/priority_queue.hpp>
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
#define INF 0x7f7f7f7f7f7f7f7fLL
// #define INF 0x7fffffffffffffffLL
typedef pair<ll,int> pli;
#define fi first
#define se second
#define mkp make_pair
typedef __gnu_pbds::priority_queue<pli, greater<pli>> heap;
int n, rt; ll s;
ll a[N], prof[N];
ll f[N];
heap h[N];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs(int u) {
	for (int i=head[u]; i; i=e[i].nxt) dfs(v);
	// if (a[u]>=0) return;
	heap &q=h[u];
	ll cur=0; // current profit	
	q.push(mkp(f[u], u));
	while (!q.empty()) {
		int t=q.top().se; q.pop();
		if (f[t]>cur) f[u]+=f[t]-cur, cur=f[t];
		if (t==u) {
			cur+=a[t];
			for (int i=head[t]; i; i=e[i].nxt) q.push(mkp(f[v], v));
		} else {
			cur+=prof[t];
			if (q.size()<h[t].size()) q.swap(h[t]);
			q.join(h[t]);
		}
		if (f[u]<cur) return prof[u]=cur-f[u], void();
	}
	f[u]=INF;
}

signed main() {
	// freopen("jobs.04-15.in", "r", stdin);
	// freopen("a.out", "w", stderr);
	n=read(), s=read(), rt=n+1;
	for (int i=1; i<=n; ++i) {
		a[i]=read();
		int x=read(); if (x==0) x=rt;
		add_edge(x, i);
	}
	dfs(rt);
	ll cur=s; // current profit
	heap q; q.push(mkp(f[rt], rt));
	while (!q.empty()) {
		int u=q.top().se; q.pop();
		if (f[u]>cur) break; cur+=a[u];
		for (int i=head[u]; i; i=e[i].nxt) {
			q.push(mkp(f[v], v));
		}
	}
	printf("%lld\n", cur-s);
	return 0;
}
