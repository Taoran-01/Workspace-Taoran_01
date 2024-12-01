#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
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

#define N 2010
int n, m;
int t1, t2, t3;
int siz[N]; ll f[N][N];

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[N<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

void dfs(int u, int fa) {
	siz[u]=1;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs(v, u), siz[u]+=siz[v];
		for (int j=max(m, siz[u]); j>=0; --j) {
			for (int k=max(j-siz[u]+siz[v], 0); k<=min(j, siz[v]); ++k) {
				ll val=(1LL*k*(m-k)+(siz[v]-k)*(n-m-siz[v]+k))*w;
				f[u][j]=max(f[u][j], f[u][j-k]+f[v][k]+val);
			}
		}
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), m=min(m, n-m);
	for (int i=1; i<n; ++i) {
		t1=read(), t2=read(), t3=read();
		add_edge(t1, t2, t3), add_edge(t2, t1, t3);
	}
	dfs(1, 1);
	printf("%lld\n", f[1][m]);
	return 0;
}
