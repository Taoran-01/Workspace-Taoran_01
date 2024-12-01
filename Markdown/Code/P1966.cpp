#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
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
#define mod 99999997
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
int n; ll ans;
pii a[N]; int d[N]; // 2nd key compare (below)
bool cmp(pii a, pii b) {return a.se==b.se?a.fi<b.fi:a.se<b.se;}
unordered_map<int, int> pos1, pos2, rnk1, rnk2;
// pos: 原来的位置 | rnk: 大小排号

ll msort(int a[], int l, int r) { // Merge sort in [l,r].
	if (l==r) return 0; int mid=l+r>>1;
	ll res=msort(a, l, mid)+msort(a, mid+1, r);
	int tmp[r-l+1]; memcpy(tmp, a+l, sizeof(int)*(r-l+1));
	int i=l, j=mid+1, k=0;
	while (i<=mid&&j<=r) {
		if (a[i]<=a[j]) tmp[k++]=a[i++];
		else tmp[k++]=a[j++], res+=mid-i+1;
	}
	while (i<=mid) tmp[k++]=a[i++];
	while (j<=r) tmp[k++]=a[j++];
	memcpy(a+l, tmp, sizeof(int)*(r-l+1));
	return res;
}

signed main() {
	// freopen("P1966.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i].fi=read(), pos1[a[i].fi]=i;
	for (int i=1; i<=n; ++i) a[i].se=read(), pos2[a[i].se]=i;
	sort(a+1, a+n+1, cmp); for (int i=1; i<=n; ++i) rnk2[a[i].se]=i;
	sort(a+1, a+n+1); for (int i=1; i<=n; ++i) rnk1[a[i].fi]=i;
	for (int i=1; i<=n; ++i) d[pos2[a[i].se]]=pos1[a[rnk2[a[i].se]].fi];
	ans=msort(d, 1, n);
	printf("%lld\n", ans%mod);
	return 0;
}
