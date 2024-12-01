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

#define N 10010
#define mod 10000LL
ll T, a, b;
ll s[N];

ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {if (b&1) res=res*a%mod; a=a*a%mod, b>>=1;}
	return res;
}

signed main() {
	// freopen("a.in", "r", stdin);
	T=read(); while (T--) {
		a=read(), b=read();
		for (int i=1; i<N; ++i) s[i]=(s[i-1]+qpow(i, b))%mod;
		printf("%lld\n", (a/mod*s[mod]+s[a%mod])%mod);
	}
	return 0;
}
