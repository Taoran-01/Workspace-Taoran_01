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

#define N 6010
#define INF 0x7f7f7f7f7f7f7f7fLL
typedef pair<ll,int> pli;
#define fi first
#define se second
#define mkp make_pair
int n, s;
ll a[N];
ll f[N];

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs(int u) {
	for (int i=head[u]; i; i=e[i].nxt) dfs(v);
	if (a[u]>=0) return;
	priority_queue<pli, vector<pli>, greater<pli>> q;
	ll cur=0; f[u]=-a[u]; // current profit	
	for (int i=head[u]; i; i=e[i].nxt) q.push(mkp(f[v], v));
	while (!q.empty()) {
		int t=q.top().se; q.pop();
		if (f[t]>cur) f[u]+=f[t]-cur, cur=f[t];
		cur+=a[t];
		if (f[u]<=cur) return;
		for (int i=head[t]; i; i=e[i].nxt) q.push(mkp(f[v], v));
	}
	f[u]=INF;
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), s=read();
	for (int i=2; i<=n; ++i) {int x=read(); add_edge(x, i);}
	for (int i=1; i<=n; ++i) a[i]=read();
	dfs(1);
	ll cur=s; // current profit
	priority_queue<pli, vector<pli>, greater<pli>> q;
	q.push(mkp(f[1], 1));
	while (!q.empty()) {
		int u=q.top().se; q.pop();
		if (f[u]>cur) break; cur+=a[u];
		for (int i=head[u]; i; i=e[i].nxt) {
			q.push(mkp(f[v], v));
		}
	}
	printf("%lld\n", cur);
	return 0;
}

/*
TIP: 子树内求 f：
1. 递归回溯过程中，子树 f 已处理完
2. 维护 cur/sum/num...(题解里各种各样的) 目的是优先取子树刚做出来的贡献。
   贪心地取新产生的贡献，先吃自己的再吃父亲的，最小化进入代价。
3. f[u] 相当于一个槛，维护子树需求的最大值。
4. 写代码时分清“代价限制”与“净代价”。
*/
