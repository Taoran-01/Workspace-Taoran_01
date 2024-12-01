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

#define N 2010
int T, k;
int n, m, cnt;
ll C[N][N];
ll sum[N][N];

signed main() {
	// freopen("problem20.in", "r", stdin);
	// freopen("problem20.out", "w", stdout);
	T=read(), k=read();
	C[0][0]=C[1][0]=C[1][1]=1; // !!!
	for (int i=2; i<N; ++i) for (int j=1; j<=i; ++j) {
		C[i][0]=1; // !!!
		C[i][j]=(C[i-1][j-1]+C[i-1][j])%k;
	}
	for (int i=1; i<=N-1; ++i) {
		for (int j=1; j<=min(i,N-1); ++j) {
			sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
			if (C[i][j]==0) ++sum[i][j];
		}
		sum[i][i+1]=sum[i][i];
	}
	while (T--) {
		n=read(), m=read(), cnt=0;
		// cnt=sum[n][m];
		if (n<m) printf("%lld\n", sum[n][n]);
		else printf("%lld\n", sum[n][m]);
	}
	return 0;
}
