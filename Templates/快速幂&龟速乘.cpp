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

ll smul(ll a, ll b) {
	ll res=0;
	while (b) {if (b&1) res=(res+a)%mod; a=(a+a)%mod, b>>=1;}
	return res;
}

ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {if (b&1) res=res*a%mod; a=a*a%mod, b>>=1;}
	return res;
}

signed main() {
	freopen("a.in", "r", stdin);
	return 0;
}
