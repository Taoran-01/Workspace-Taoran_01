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

#define N 310
#define INF 0x3f3f3f3f
int n, m, k;
int t1, t2, t3;
int f[N][N][2];
int tmp[N][2];

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[N<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

void dfs(int u, int fa) {
	f[u][0][0]=f[u][1][1]=0; // Contributes on its self
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue;
		dfs(v, u);
		memcpy(tmp, f[u], sizeof(tmp));
		memset(f[u], 0x3f, sizeof(f[u]));
		for (int j=1; j<=k; ++j) for (int t=0; t<=j; ++t) {
			f[u][j][0]=min(f[u][j][0], 
				min(f[v][t][0]+tmp[j-t][0]+(m==2)*w, f[v][t][1]+tmp[j-t][0]));
			f[u][j][1]=min(f[u][j][1], 
				min(f[v][t][1]+tmp[j-t][1]+w, f[v][t][0]+tmp[j-t][1]));
		}
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), k=read();
	for (int i=1; i<n; ++i) {
		t1=read(), t2=read(), t3=read();
		add_edge(t1, t2, t3), add_edge(t2, t1, t3);
	}
	if (n<=k) return puts("-1"), 0;
	memset(f, 0x3f, sizeof(f));
	dfs(1, 1);
	printf("%d\n", f[1][k][1]);
	return 0;
}
