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

#define N 100010
#define INF 0x7f7f7f7f
int n, ans;
struct node {int dis, val;} a[N<<1];
bool operator<(node a, node b) {return a.dis==b.dis?a.val<b.val:a.dis<b.dis;}

int cur, cnt; // cur ans | coin cnt

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), ans=INF;
	for (int i=1; i<=n; ++i) a[i].dis=read(), a[i].val=-1;
	for (int i=n+1; i<=n+n; ++i) a[i].dis=read(), a[i].val=1;
	n<<=1, sort(a+1, a+n+1);
	for (int i=1; i<=n; ++i) { // 枚举转折点
		cur+=a[i].dis-a[i-1].dis;
		if (cnt<0) cur+=(a[i].dis-a[i-1].dis)*2;
		cnt+=a[i].val;
		ans=min(ans, cur+(a[n].dis-a[i].dis)*2);
	}
	printf("%lld\n", ans);
	return 0;
}
