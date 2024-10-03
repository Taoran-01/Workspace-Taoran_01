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

// ll h(ll x, ll y) {
// 	if (x==0||y==0) return x+y;
// 	return h(x^y, (x&y)<<1);
// }

ll h(ll x, ll y) {
	return x+y;
}

// ll g(ll x, ll y) {
// 	if (x==0||y==0) return x+y;
// 	return g(x^y, ((~x)&y)<<1);
// }

ll g(ll x, ll y) {
	return x-y;
}

// h(x,y)*g(x,y)=x^2-y^2
// 1^2~x^2 x(x+1)(2x+1)

#define MOD 1000000007LL
ll a, b, a1, b1, a2, b2, a3, b3;

signed main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	a=a1=read(), b=b1=read();
	a2=a1+1LL, a3=(a1<<1LL)+1LL, b2=b1+1LL, b3=(b1<<1LL)+1LL;
	if (a1%2==0&&a2%3==0) a1/=2, a2/=3;
	else if (a1%3==0&&a2%2==0) a1/=3, a2/=2;
	else if (a2%2==0&&a3%3==0) a2/=2, a3/=3;
	else if (a2%3==0&&a3%2==0) a2/=3, a3/=2;
	else if (a1%2==0&&a3%3==0) a1/=2, a3/=3;
	else if (a1%3==0&&a3%2==0) a1/=3, a3/=2;
	else if (a1%6==0) a1/=6;
	else if (a2%6==0) a2/=6;
	else if (a3%6==0) a3/=6;
	// else puts("-"); //
	a1%=MOD, a2%=MOD, a3%=MOD;
	a1*=a2, a1%=MOD, a1*=a3, a1%=MOD;
	// printf("%lld\n", a1); //

	if (b1%2==0&&b2%3==0) b1/=2, b2/=3;
	else if (b1%3==0&&b2%2==0) b1/=3, b2/=2;
	else if (b2%2==0&&b3%3==0) b2/=2, b3/=3;
	else if (b2%3==0&&b3%2==0) b2/=3, b3/=2;
	else if (b1%2==0&&b3%3==0) b1/=2, b3/=3;
	else if (b1%3==0&&b3%2==0) b1/=3, b3/=2;
	else if (b1%6==0) b1/=6;
	else if (b2%6==0) b2/=6;
	else if (b3%6==0) b3/=6;
	// else puts("-"); //
	b1%=MOD, b2%=MOD, b3%=MOD;
	b1*=b2, b1%=MOD, b1*=b3, b1%=MOD;
	// printf("%lld\n", b1); //

	a1*=b, a1%=MOD, b1*=a, b1%=MOD;
	printf("%lld\n", (a1+MOD-b1)%MOD);
	return 0;
}
