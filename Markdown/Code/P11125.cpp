#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
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

#define N 200010
typedef pair<ll,pair<int,bool>> plib;
#define fi first
#define se second
#define mkp make_pair
ll n, m, c1, c2;
ll tim;
ll a[N], t[N];
priority_queue<plib, vector<plib>, greater<plib>> q;

void pcs() {
	auto f=q.top(); q.pop(), tim=f.fi;
	if (f.se.se) --c1, c2+=2;
	else q.push(mkp(t[f.se.fi], mkp(f.se.fi, 1))), ++c1;
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) a[i]=read(), q.push(mkp(a[i], mkp(i, 0)));
	for (int i=1; i<=n; ++i) t[i]=a[i]+read();
	while (!c2) {
		do pcs(); while (!q.empty()&&q.top().fi==tim);
		if (c1+c2==m) return printf("%lld\n", tim), 0;
	}
	while (c1+c2<m) {
		++tim, c2*=2LL;
		while (!q.empty()&&q.top().fi==tim) pcs();
	}
	printf("%lld\n", c1+c2==m?tim:-1);
	return 0;
}
