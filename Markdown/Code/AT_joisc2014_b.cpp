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

#define N 300010
int n; ll ans;
int a[N], tmp[N], lt;

template <typename T> struct BIT {
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void modify(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T query(int x) {return g(x);} T query(int l, int r) {return g(r)-g(l-1);}
}; BIT<int> t1, t2;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read(), tmp[i]=a[i];
	sort(tmp+1, tmp+n+1), lt=unique(tmp+1, tmp+n+1)-(tmp+1);
	for (int i=1; i<=n; ++i) a[i]=lower_bound(tmp+1, tmp+lt+1, a[i])-tmp;
	for (int i=1; i<=n; ++i) t1.modify(a[i], 1);
	for (int i=1; i<=n; ++i) {
		t1.modify(a[i], -1), t2.modify(a[i], 1);
		ans+=min(n-i-t1.query(a[i]), i-t2.query(a[i]));
	}
	printf("%lld\n", ans);
	return 0;
}
