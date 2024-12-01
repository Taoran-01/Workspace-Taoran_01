#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
#define M 1010
#define INF 0x3f3f3f3f
int f[2][M];

int n, m, k;
int up[N], dn[N];
bool ext[N], pas[N];
int lim[N][2];
// struct node {int x, y1, y2;} p[N];

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read(), k=read(), pas[1]=1;
	for (int i=1; i<=n; ++i) up[i]=read(), dn[i]=read();
	for (int i=1; i<=n; ++i) lim[i][0]=0, lim[i][1]=m+1;
	for (int i=1; i<=k; ++i) {
		int x=read(); ext[x]=1, lim[x][0]=read(), lim[x][1]=read();
	}
	memset(f, 0x3f, sizeof(f));
	for (int i=1; i<=m; ++i) f[0][i]=0;
	// for (int j=lim[1][0]+1; j<lim[1][1]; ++j) f[1][j]=0;
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) f[i&1][j]=INF;
		for (int j=lim[i][0]+1; j<lim[i][1]; ++j) {
			assert(1<=j&&j<=m);
			if (j+dn[i]<=m) f[i&1][j]=min(f[i&1][j], f[(i&1)^1][j+dn[i]]);
			for (int c=1; ; ++c) {
				if (j-c*up[i]<1) break;
				f[i&1][j]=min(f[i&1][j], f[(i&1)^1][j-c*up[i]]+c);
			}
			if (j==m) for (int k=1; k<=m; ++k) {
				f[i&1][j]=min(f[i&1][j], f[(i&1)^1][k]+(m-k)/up[i]+1);
			}
			if (f[i&1][j]!=INF) pas[i]=1;
		}
	}
	// for (int j=m; j>=0; --j) for (int i=1; i<=n; ++i) {
	// 	if (f[i][j]==INF) fprintf(stderr, "inf%c", i==n?'\n':' ');
	// 	else fprintf(stderr, "%3d%c", f[i][j], i==n?'\n':' ');
	// }
	// for (int i=1; i<=n; ++i) fprintf(stderr, "%3d%c", ext[i], i==n?'\n':' ');
	// for (int i=1; i<=n; ++i) fprintf(stderr, "%3d%c", lim[i][0], i==n?'\n':' ');
	// for (int i=1; i<=n; ++i) fprintf(stderr, "%3d%c", lim[i][1], i==n?'\n':' ');
	// for (int i=1; i<=n; ++i) fprintf(stderr, "%3d%c", up[i], i==n?'\n':' ');
	// for (int i=1; i<=n; ++i) fprintf(stderr, "%3d%c", dn[i], i==n?'\n':' ');
	for (int i=1, cnt=0; i<=n; ++i) {
		if (!pas[i]) return printf("0\n%d\n", cnt), 0;
		cnt+=ext[i];
	}
	int ans=INF;
	for (int j=1; j<=m; ++j) ans=min(ans, f[n&1][j]);
	printf("1\n%d\n", ans);
	return 0;
}
