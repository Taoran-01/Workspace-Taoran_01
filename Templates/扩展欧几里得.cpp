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

/*
求线性同余方程 ax≡1(mod b) 的最小正整数解
*/

/*
int exgcd(int a, int b, int &x, int &y) {
	if (b==0) return x=1, y=0, a;
	int d=exgcd(b, a%b, x, y);
	int tmp=x; x=y, y=tmp-a/b*y;
	return d;
}

int a, b, x, y;

signed main() {
	// freopen("c.in", "r", stdin);
	a=read(), b=read(), x=1, y=1;
	exgcd(a, b, x, y), printf("%d\n", (x+b)%b);
	return 0;
}
*/

/*
求不定方程 ax+by=c 的最小正整数解。
无整数解输出-1，有整数解但无正整数解输出x的最小正整数值和y的最小正整数值。
有正整数解输出数量、x最小值、y最小值、x最大值、y最大值。
*/

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b==0) return x=1, y=0, a;
	ll d=exgcd(b, a%b, x, y);
	ll tmp=x; x=y, y=tmp-a/b*y;
	return d;
}

bool solve(ll a, ll b, ll c, ll &x, ll &y) {
	ll d=exgcd(a, b, x, y);
	if (c%d!=0) return 0; // 无解
	return x*=c/d, y*=c/d, 1;
}

int T;
ll a, b, c, x, y;

signed main() {
	// freopen("c.in", "r", stdin);
	T=read(); while (T--) {
		a=read(), b=read(), c=read();
		ll d=exgcd(a, b, x, y);
		if (!solve(a, b, c, x, y)) {puts("-1"); continue;}
		ll tx=b/d, ty=a/d;
		ll k=ceil((1.0-x)/tx);
		x+=tx*k, y-=ty*k;
		if (y<=0) {
			ll ymin=y+ty*1ll*ceil((1.0-y)/ty);
			printf("%lld %lld\n", x, ymin);
		} else printf("%lld %lld %lld %lld %lld\n", (y-1)/ty+1, x, \
			(y-1)%ty+1, x+(y-1)/ty*tx, y);
	}
	return 0;
}
