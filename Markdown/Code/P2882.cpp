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

#define N 15010
#define INF 0x7f7f7f7f
typedef pair<int, int> pii;
#define fi first
#define se second
int n;
bool a[N], cur;
bool cf[N];
pii ans[N];

signed main() {
	// freopen("c1.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) {
		char ch=getchar();
		while (ch!='F'&&ch!='B') ch=getchar();
		a[i]=ch=='F';
		ans[i].se=i;
	}
	for (int k=1; k<=n; ++k) {
		cur=0;
		memset(cf, 0, sizeof(cf));
		for (int i=1; i<=n-k+1; ++i) {
			cur^=cf[i];
			// printf("%d ", (!(a[i]^cur)));
			if (!(a[i]^cur)) ++ans[k].fi, cf[i+1]^=1, cf[i+k]^=1;
		}
		// puts("");
		for (int i=n-k+2; i<=n; ++i) {
			cur^=cf[i];
			if (!(a[i]^cur)) ans[k].fi=INF;
		}
	}
	sort(ans+1, ans+1+n);
	// for (int i=1; i<=n; ++i) printf("%d %d\n", ans[i].se, ans[i].fi);
	printf("%d %d\n", ans[1].se, ans[1].fi);
	return 0;
}
