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

#define N 510
#define INF 0x7f7f7f7f
int n, m, ans, lf, rt;
int h[N][N], l[N][N], r[N][N];
bool vis[N][N];
const int dir[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

void dfs(int x, int y) {
	vis[x][y]=1;
	for (int i=0; i<4; ++i) {
		int x1=x+dir[i][0], y1=y+dir[i][1];
		if (x1<1||x1>n||y1<1||y1>m||h[x1][y1]>=h[x][y]) continue;
		if (!vis[x1][y1]) dfs(x1, y1);
		l[x][y]=min(l[x][y], l[x1][y1]);
		r[x][y]=max(r[x][y], r[x1][y1]);
	}
}

signed main() {
	// freopen("c.in", "r", stdin);
	n=read(), m=read();
	memset(l, 0x7f, sizeof(l)), memset(r, 0, sizeof(r));
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) h[i][j]=read();
	for (int j=1; j<=m; ++j) l[n][j]=r[n][j]=j;
	for (int j=1; j<=m; ++j) if (!vis[1][j]) dfs(1, j);
	for (int j=1; j<=m; ++j) if (!vis[n][j]) ++ans;
	if (ans) return printf("0\n%d\n", ans), 0;
	lf=1, rt=r[1][1];
	while (lf<=m) {
		for (int j=1; j<=m; ++j) {
			if (l[1][j]<=lf) rt=max(rt, r[1][j]);
		}
		lf=rt+1, ++ans;
	}
	printf("1\n%d\n", ans);
	return 0;
}
