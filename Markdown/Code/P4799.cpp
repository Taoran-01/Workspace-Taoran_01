#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define int ll

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 50
#define M 1<<21
int n, m, mid; ll ans;
int w[N];
ll a[M], b[M], la, lb;

void dfs(int l, int r, ll cur, ll a[], ll &la) {
	if (cur>m) return;
	if (l>r) return a[++la]=cur, void();
	dfs(l+1, r, cur+w[l], a, la), dfs(l+1, r, cur, a, la);
}

signed main() {
	// freopen("b.in", "r", stdin);
	n=read(), m=read(), mid=n>>1;
	for (int i=1; i<=n; ++i) w[i]=read();
	dfs(1, mid, 0, a, la), dfs(mid+1, n, 0, b, lb);
	sort(a+1, a+la+1);
	for (int i=1; i<=lb; ++i) {
		ans+=upper_bound(a+1, a+la+1, m-b[i])-a-1;
	}
	printf("%lld\n", ans);
	return 0;
}
