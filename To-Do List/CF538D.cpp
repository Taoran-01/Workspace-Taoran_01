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

#define N 60
int n;
int a[N][N], d[N][N], t[N][N];

signed main() {
	// freopen("CF538D_1.in", "r", stdin);
	// freopen("CF538D_1.out", "w", stdout);
	n=read();
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		char ch=getchar(); while (ch!='x'&&ch!='o'&&ch!='.') ch=getchar();
		if (ch=='.') a[i][j]=0; if (ch=='x') a[i][j]=1; if (ch=='o') a[i][j]=2;
	}
	for (int i=1; i<=n*2-1; ++i) for (int j=1; j<=n*2-1; ++j) d[i][j]=1;
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) if (a[i][j]==2) {
		for (int x=1; x<=n; ++x) for (int y=1; y<=n; ++y) {
			if (a[x][y]==0) d[x-i+n][y-j+n]=0;
		}
	}
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) if (a[i][j]==2) {
		for (int x=1; x<=n*2-1; ++x) for (int y=1; y<=n*2-1; ++y) if (d[x][y]) {
			int x1=i+x-n, y1=j+y-n;
			if (x1>=1&&x1<=n&&y1>=1&&y1<=n) t[x1][y1]=1;
		}
	}
	bool flag=1;
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) if (a[i][j]!=2) {
		flag&=(a[i][j]==1)==(t[i][j]==1);
	}
	d[n][n]=2;
	if (!flag) return puts("NO"), 0;
	puts("YES");
	for (int i=1; i<=2*n-1; ++i) {
		for (int j=1; j<=2*n-1; ++j) {
			putchar(".xo"[d[i][j]]);
		} puts("");
	}
	return 0;
}
