#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 5010
#define INF 0x7f7f7f7f
int f[N][N], g[N][N];
int ans=INF;

int n, init;
int col[N], prf[N], cst[N], pre[N];
int pr[10], nxt[N];

// 1008709
// SD-573

signed main() {
//	freopen("survive2.in", "r", stdin);
	freopen("survive.in", "r", stdin);
	freopen("survive.out", "w", stdout);
	memset(f, 0x7f, sizeof(f));memset(g, 0x7f, sizeof(g));
	n=read();
	for (int i=1; i<=n; ++i) {
		col[i]=read();
		if (col[i]<=6) nxt[pr[col[i]]]=i, pr[col[i]]=i;
	}
	nxt[0]=INF;
//	for (int i=1; i<=n; ++i) fprintf(stderr, "%d ", nxt[i]); fprintf(stderr, "\n");
	for (int i=1; i<=n; ++i) prf[i]=read();
	for (int i=1; i<=n; ++i) cst[i]=read(), pre[i]=pre[i-1]+cst[i];
	f[0][0]=g[0][0]=read();
	int sum2=0;
	for (int x=1; x<=n; ++x) sum2+=cst[x];
	ans=min(ans, f[0][0]+sum2);
	for (int i=1; i<=n; ++i) {
//		fprintf(stderr, "%d\n", i);
		for (int j=1; j<=i; ++j) {
			for (int k=0; k<i; ++k) {
				if (i==nxt[k]) continue;
				ll sum=0;
//				for (int x=k+1; x<i; ++x) sum+=cst[x];
				sum=pre[i-1]-pre[k];
//				f[i][j]=min(1LL*f[i][j], max(1LL*f[k][j-1], sum+f[k][j-1]-prf[k]));
//				f[i][j]=min(1LL*f[i][j], (sum+f[k][j-1]-prf[k]));
				if (max(1LL*f[k][j-1], sum+g[k][j-1]-prf[k])<f[i][j]) {
					f[i][j]=max(1LL*f[k][j-1], sum+g[k][j-1]-prf[k]);
					g[i][j]=sum+g[k][j-1]-prf[k];
				}
				ll sum1=0;
//				for (int x=i+1; x<=n; ++x) sum1+=cst[x];
				sum1=pre[n]-pre[i];
				ans=min(1LL*ans, max(1LL*f[i][j], g[i][j]+sum1));
			}
		}
	}
//	for (int i=0; i<=n; ++i) {
//		for (int j=0; j<=i; ++j) {	
//			if (f[i][j]==INF) fprintf(stderr, "inf ");
//			else fprintf(stderr, "%3d ", f[i][j]);
//		}
//		puts("");
//	}
	fprintf(stderr, "%d\n", ans);
	return 0;
}

