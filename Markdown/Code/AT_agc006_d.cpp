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

#define N 100010
int n;
int a[N<<1]; bool b[N<<1];
int tmp[N<<1], tot;
int l, r, mid, ans;

bool chk() {
	for (int i=1; i<=n*2-1; ++i) b[i]=a[i]>=mid;
	for (int i=1; i<n; ++i) {
		if (b[n-i]==b[n-i+1]) return b[n-i];
		if (b[n+i]==b[n+i-1]) return b[n+i];
	}
	return b[1];
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n*2-1; ++i) a[i]=read(), tmp[++tot]=a[i];
	sort(tmp+1, tmp+tot+1), tot=unique(tmp+1, tmp+tot+1)-(tmp+1);
	for (int i=1; i<=n; ++i) a[i]=lower_bound(tmp+1, tmp+tot+1, a[i])-tmp;
	l=1, r=tot+1;
	while (l<r) {
		mid=(l+r)>>1;
		if (chk()) l=mid+1, ans=mid;
		else r=mid;
	}
	printf("%d\n", ans);
	return 0;
}
