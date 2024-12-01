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

#define N 110
#define M 40010
int n, w;
ll f[2][M];
int q[M];

signed main() {
	// freopen("a.in", "r", stdin);
	int n=read(), w=read();
	for (int ii=1; ii<=n; ++ii) {
		int i=ii&1;
		int v=read(), c=read(), cnt=read();
		for (int x=0; x<c; ++x) {
			int head=1, tail=0; // [head,tail] decrease
			for (int j=x; j<=w; j+=c) {
				while (head<=tail&&f[i^1][q[tail]]+(j-q[tail])/c*v<=f[i^1][j])
					--tail;
				q[++tail]=j;
				while (head<=tail&&(j-q[head])/c>cnt) ++head;
				f[i][j]=f[i^1][q[head]]+(j-q[head])/c*v;
			}
		}
	}
	ll ans=0;
	for (int j=0; j<=w; ++j) ans=max(ans, f[n&1][j]);
	printf("%lld\n", ans);
	return 0;
}
