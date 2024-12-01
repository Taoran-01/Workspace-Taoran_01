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

int a, b;
ll ans;

signed main() {
	// freopen("c.in", "r", stdin);
	// freopen("c.out", "w", stdout);
	a=read(), b=read();
	for (int n=a; n<=b; ++n) {
		for (int i=-n; i<=n; ++i) {
			if (i==0) continue;
			for (int j=-n; j<=n; ++j) {
				if (j==0) continue;
				if (n%abs(i*j)!=0) continue;
				int k=n/i/j;
				ans+=1LL*(abs(i)+abs(j)+abs(k))*(abs(i)+abs(j)+abs(k));
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
