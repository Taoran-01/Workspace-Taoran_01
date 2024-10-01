#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
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

#define N 500010
int n; ll ans;
int a[N];
int tmp[N], nt;

template <typename T> struct BIT {
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void modify(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T query(int x) {return g(x);} T query(int l, int r) {return g(r)-g(l-1);}
}; BIT<ll> t;

signed main() {
	freopen("P1774_1.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read(), tmp[++nt]=a[i];
	reverse(a+1, a+n+1), sort(tmp+1, tmp+nt+1), nt=unique(tmp+1, tmp+nt+1)-(tmp+1);
	for (int i=1; i<=n; ++i) a[i]=lower_bound(tmp+1, tmp+nt+1, a[i])-tmp;
	for (int i=n; i; --i) ans+=t.query(a[i]-1), t.modify(a[i], 1);
	printf("%d\n", ans);
	return 0;
}
