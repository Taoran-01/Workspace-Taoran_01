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

#define N 3010
int n, m, cnt, ans;
bool d[N][N]; // hor+vec
int a[N][N], b[N][N]; // vec

signed main() {
	// freopen("a3.in", "r", stdin);
	n=read(), m=read(), cnt=read();
	for (int i=1; i<=cnt; ++i) {
		int x=read(), y=read();
		d[x][y]=1;
	}
	for (int i=1; i<=n; ++i)  for (int j=1; j<=m; ++j) {
		if (d[i][j]) continue;
		a[i][j]=a[i-1][j]+1, b[i][j]=b[i-1][j-1]+1;
	}
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
		if (d[i][j]) continue;
		for (int k=ans+1; k<=min(i,j); ++k) {
			if (a[i][j]<k) continue;
			if (b[i][j]<k) continue;
			if (a[i][j-k+1]<k) continue;
			ans=k;
		}
	}
	// for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
	// 	printf("%d%c", a[i][j], j==m?'\n':' ');
	// }
	printf("%d\n", ans);
	return 0;
}
