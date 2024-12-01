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

#define N 110
#define INF 0x3f3f3f3f3f3f3f3fLL
int n, m;
double ans[N];
ll d[N][N], cnt[N][N];

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	memset(d, 0x3f, sizeof(d));
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(); ll z=read();
		d[x][y]=d[y][x]=z, cnt[x][y]=cnt[y][x]=1;
	} // ↓↓ K FOR THE FIRST ↓↓
	for (int k=1; k<=n; ++k) for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		if (d[i][k]+d[k][j]<d[i][j]) {
			d[i][j]=d[i][k]+d[k][j], cnt[i][j]=cnt[i][k]*cnt[k][j];
		} else if (d[i][k]+d[k][j]==d[i][j]) cnt[i][j]+=cnt[i][k]*cnt[k][j];
	}
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		for (int k=1; k<=n; ++k) if (i!=k&&k!=j&&i!=j&&d[i][k]+d[k][j]==d[i][j]) {
			ll Cst=cnt[i][j], CstV=cnt[i][k]*cnt[k][j];
			ans[k]+=1.0*CstV/Cst;
		}
	}
	for (int i=1; i<=n; ++i) printf("%.3lf\n", ans[i]);
	return 0;
}
