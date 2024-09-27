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

#define mod 998244353
#define N 1000010
int fac[N], inv[N]; // fact invfact

ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {if (b&1) res=res*a%mod; a=a*a%mod, b>>=1;}
	return res;
}

int A(int n, int m) {return 1LL*fac[n]*inv[n-m]%mod;}
int C(int n, int m) {return 1LL*fac[n]*inv[n-m]%mod*inv[m]%mod;}

signed main() {
	// freopen("a.in", "r", stdin);
	fac[0]=inv[0]=1;
	for (int i=1; i<N; ++i) fac[i]=1LL*fac[i-1]*i%mod;
	for (int i=1; i<N; ++i) inv[i]=inv[i-1]*qpow(i, mod-2)%mod;
	return 0;
}
