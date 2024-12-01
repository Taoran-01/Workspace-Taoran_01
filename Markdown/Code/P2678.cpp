#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <bitset>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 50010
#define INF 0x7f7f7f7f
int l, n, m;
int d[N];

bool chk(int x) {
	int lst=0, cst=0;
	for (int i=1; i<=n; ++i) {
		if (d[i]-lst<x) ++cst; // remove current stone
		else lst=d[i];
	}
	return cst<=m;
}

signed main() {
	// freopen("stone10.in", "r", stdin);
	l=read(), n=read(), m=read();
	for (int i=1; i<=n; ++i) d[i]=read(); d[++n]=l;
	int L=1, R=l+1, mid=0, ans=INF; while (L<R) {
		mid=(L+R)>>1;
		if (chk(mid)) L=mid+1, ans=mid;
		else R=mid;
	} assert(ans!=INF);
	printf("%d\n", ans);
	return 0;
}
