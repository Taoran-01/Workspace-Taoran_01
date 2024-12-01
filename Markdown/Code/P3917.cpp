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

#define N 100010
#define L 32
int n;
int a[N], f[N][L];
ll ans;

signed main() {
	// freopen("b2.in", "r", stdin);
	// freopen("b2.out", "w", stdout);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=n; ++i) {
		for (int j=0; j<L; ++j) {
			if (a[i]&(1<<j)) f[i][j]=i-f[i-1][j];
			else f[i][j]=f[i-1][j];
			ans+=f[i][j]*(1LL<<j);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
