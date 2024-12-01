#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
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

#define eps 1e-10L
#define mod 998244353LL
int T, n;
ll ans;

signed main() {
	// freopen("a.in", "r", stdin);
	T=read(); while (T--) {
		n=read(), ans=0;
		int m=sqrt(1.0L*n)+eps;
		ans=1LL*m*m%mod*m%mod;
		for (int l=m+1, r=0; l<=n; l=r+1) {
			r=n/(n/l);
			ans=(ans+1LL*(n/l)*(n/l)%mod*3%mod*(r-l+1)%mod)%mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
