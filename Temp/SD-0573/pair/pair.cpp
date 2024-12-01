#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 500010
#define INF 0x7f7f7f7f
#define gcd __gcd
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
int Log[N];
int n;
int a[N];
int st[N][20];
int mx;
vector<int> ans;

int query(int l, int r) {
	int x=Log[r-l+1];
	return gcd(st[l][x], st[r-(1<<x)+1][x]);
}

bool chk(int l, int r, int x) {
//	fprintf(stderr, "query: x=%d [%d %d] ans=%d\n", l, r, x, query(l,r)%a[x]==0);
	return query(l,r)%a[x]==0;
}

void solve(int x) {
	int L=0, R=0, mid=0, lf=x, rt=x;
	L=1, R=x+1; while (L<R) {
		mid=(L+R)>>1;
		if (chk(mid, x, x)) R=mid, lf=mid;
		else L=mid+1;
	}
	L=x, R=n+1; while (L<R) {
		mid=(L+R)>>1;
		if (chk(x, mid, x)) L=mid+1, rt=mid;
		else R=mid;
	}
//	fprintf(stderr, "x=%d [%d %d]\n", x, lf, rt);
	int val=rt-lf;
	if (val<mx) return;
	if (val==mx) return ans.pb(lf), void();
	mx=val, ans.clear(), ans.pb(lf);
}

signed main() {
	freopen("pair.in", "r", stdin);
	freopen("pair.out", "w", stdout);
	for (int i=2; i<N; ++i) Log[i]=Log[i>>1]+1;
	n=read();
	for (int i=1; i<=n; ++i) a[i]=st[i][0]=read();
	for (int j=1; j<=Log[n]; ++j) for (int i=1; i<=n-(1<<j)+1; ++i) {
		st[i][j]=gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	}
//	fprintf(stderr, "%d\n", chk(2, 5, 4));
	for (int i=1; i<=n; ++i) solve(i);
	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end())-ans.begin());
	printf("%d %d\n", (int)ans.size(), mx);
	for (auto x:ans) printf("%d ", x);
	puts("");
	return 0;
}

