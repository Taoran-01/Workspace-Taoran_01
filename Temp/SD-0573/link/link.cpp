#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define mod 1000000007
ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {if (b&1) res=res*a%mod; a=a*a%mod, b>>=1;}
	return res;
}

#define N 100010
int n, m;
ll ans;
bool col[N];
int siz[N], cnt[N];

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[N<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

void dfs(int u, int fa) {
	siz[u]=1, cnt[u]=col[u];
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		assert(siz[v]==0);
		dfs(v, u), siz[u]+=siz[v], cnt[u]+=cnt[v];
	}
}

void dfs1(int u, int fa, int in_w) {
	ll tmp=0;
	tmp=(tmp+1LL*cnt[u]*((siz[1]-cnt[1])-(siz[u]-cnt[u])))%mod;
	tmp=(tmp+1LL*(siz[u]-cnt[u])*(cnt[1]-cnt[u]))%mod;
//	fprintf(stderr, "%d %lld\n", in_w, tmp);
	ans=(ans+(qpow(2, in_w)*tmp%mod))%mod;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs1(v, u, w);
	}
}

signed main() {
	freopen("link.in", "r", stdin);
	freopen("link.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) col[i]=read();
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read();
		if (i<n) add_edge(x, y, i), add_edge(y, x, i);
	}
	dfs(1, 0);
//	for (int i=1; i<=n; ++i) fprintf(stderr, "%d ", siz[i]); fprintf(stderr, "\n");
//	for (int i=1; i<=n; ++i) fprintf(stderr, "%d ", cnt[i]); fprintf(stderr, "\n");
	dfs1(1, 0, 0);
	printf("%lld\n", ans);
	return 0;
}

