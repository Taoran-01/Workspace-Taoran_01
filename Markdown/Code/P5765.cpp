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

#define N 50010
#define L 20
#define INF 0x7f7f7f7f
int n;
int f[N][L]; // Point u fill with number k.

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

void dfs(int u, int fa) {
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs(v, u);
		for (int j=1; j<L; ++j) {
			int minn=INF;
			for (int k=1; k<L; ++k) {
				if (k==j) continue;
				minn=min(minn, f[v][k]);
			}
			f[u][j]+=minn;
		}
	}
	for (int j=1; j<L; ++j) f[u][j]+=j;
}

signed main() {
	// freopen("P5765_2.in", "r", stdin);
	n=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	dfs(1, 1);
	int ans=INF;
	for (int j=1; j<L; ++j) ans=min(ans, f[1][j]);
	printf("%d\n", ans);
	return 0;
}
