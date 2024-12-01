#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 3010
#define M 3010
int n, m;

struct node {int idx; string d;} a[N], b[N];
bool operator<(node a, node b) {return a.d<b.d;}

signed main() {
	// freopen("dict4.in", "r", stdin);
	// freopen("dict.out", "w", stdout);
	n=read(), m=read();
	// memset(mx, 0x80, sizeof(mx));
	// memset(mn, 0x7f, sizeof(mn));
	if (n==1) return puts("1"), 0;
	for (int i=1; i<=n; ++i) cin>>a[i].d;
	for (int i=1; i<=n; ++i) sort(a[i].d.begin(), a[i].d.end());
	for (int i=1; i<=n; ++i) b[i].d=a[i].d, b[i].idx=i;
	for (int i=1; i<=n; ++i) reverse(b[i].d.begin(), b[i].d.end());
	sort(b+1, b+n+1);
	for (int i=1; i<=m; ++i) b[0].d.push_back('a'-1);

	// for (int i=1; i<=n; ++i) cerr<<a[i].d<<endl;
	// cerr<<"---===---\n";
	// for (int i=1; i<=n; ++i) cerr<<b[i].d<<endl;
	// cerr<<"---===---\n";
	for (int i=1; i<=n; ++i) {
		int idx=upper_bound(b+1, b+n+1, a[i])-b;
		// fprintf(stderr, "%s: %d\n", a[i].d.c_str(), idx);
		if (idx==1||(idx==2&&b[1].idx==i)) putchar('1');
		else putchar('0');
	}
	return 0;
}
