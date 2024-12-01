#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
typedef double db;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 20
#define eps 1e-8
#define INF 0x7f7f7f7f
// typedef pair<db, db> pdd;
// #define fi first
// #define se second
// #define mp make_pair
int T;
int n; db x[N], y[N];
int hit[N][N], lowunbit[1<<N], dp[1<<N];

// pdd equation(int i, int j) {
// 	db t=(x[i]*x[i]*y[j]-x[j]*x[j]*y[i])/(x[i]*x[i]*x[j]-x[j]*x[j]*x[i]);
// 	return mp(t, (y[i]-x[i]*t)/(x[i]*x[i]));
// }

void equation(db &x, db &y, db a1, db b1, db c1, db a2, db b2, db c2) {
	y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
	x=(c1-b1*y)/a1;
}

signed main() {
	// freopen("d1.in", "r", stdin);
	for (int i=0; i<1<<N; ++i) {
		int j=1;
		while (j<=18 && i&(1<<j-1)) ++j;
		lowunbit[i]=j;
	}
	T=read(); while (T--) {
		memset(hit, 0, sizeof(hit)), memset(dp, 0x7f, sizeof(dp));
		n=read(), read(), dp[0]=0;
		for (int i=1; i<=n; ++i) scanf("%lf%lf", &x[i], &y[i]);
		for (int i=1; i<=n; ++i) {
			for (int j=1; j<=n; ++j) {
				if (abs(x[i]-x[j])<eps) continue;
				// db a, b; equation(a, b, i, j);
				db a, b; equation(a,b,x[i]*x[i],x[i],y[i],x[j]*x[j],x[j],y[j]);
				if (a>-eps) continue;
				for (int k=1; k<=n; ++k) {
					if (abs(a*x[k]*x[k]+b*x[k]-y[k])<eps) hit[i][j]|=1<<k-1;
				}
			}
		}
		for (int i=0; i<1<<n; ++i) {
			int j=lowunbit[i];
			dp[i|(1<<j-1)]=min(dp[i|(1<<j-1)], dp[i]+1);
			for (int k=1; k<=n; ++k) dp[i|hit[j][k]]=min(dp[i|hit[j][k]], dp[i]+1);
		}
		printf("%d\n", dp[(1<<n)-1]);
	}
	return 0;
}
