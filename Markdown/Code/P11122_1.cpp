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

#define N 16
#define S ((1<<15)+5)
int n, m; ll k; bool flag;
int d[N][N];
int sl[S][N][N], sr[S][N][N]; // line | row

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) d[i][j]=read();
	k=read();
	for (int x=0; x<1<<n; ++x) for (int i=1; i<=n; ++i) {
		if (x&(1<<(i-1))) for (int j=1; j<=m; ++j) sl[x][i][j]=d[i][j];
	}
	for (int y=0; y<1<<m; ++y) for (int j=1; j<=m; ++j) {
		if (y&(1<<(j-1))) for (int i=1; i<=n; ++i) sr[y][i][j]=d[i][j];
	}
	for (int x=0; x<1<<n; ++x) if (!flag) for (int y=0; y<1<<m; ++y) {
		ll c=0;
		for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) c+=sl[x][i][j]&sr[y][i][j];
		if (c!=k) continue; puts("YES"), flag=1; ll cnt=0;
		for (int i=1; i<=n; ++i) if (!(x&(1<<(i-1)))) ++cnt;
		for (int j=1; j<=m; ++j) if (!(y&(1<<(j-1)))) ++cnt;
		printf("%lld\n", cnt);
		for (int i=1; i<=n; ++i) if (!(x&(1<<(i-1)))) printf("1 %d\n", i);
		for (int j=1; j<=m; ++j) if (!(y&(1<<(j-1)))) printf("2 %d\n", j);
		break;
	}
	if (!flag) puts("NO");
	return 0;
}
