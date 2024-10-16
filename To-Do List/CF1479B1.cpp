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

#define N 100010
#define INF 0x7f7f7f7f
int n, ans;
int d[N], pos[N], nxt[N];
int a[N], la;
int b[N], lb;

// WA on test 8

signed main() {
	// freopen("a1.in", "r", stdin);
	n=read();
	memset(nxt, 0x7f, sizeof(nxt));
	for (int i=1; i<=n; ++i) d[i]=read(), nxt[pos[d[i]]]=i, pos[d[i]]=i;
	for (int i=1; i<=n; ++i) {
		int t=0;
		if (d[a[la]]==d[i]) t=b[lb], b[++lb]=i;
		else if (d[b[lb]]==d[i]) t=a[la], a[++la]=i;
		else if (nxt[a[la]]<nxt[b[lb]]) t=a[la], a[++la]=i;
		else t=b[lb], b[++lb]=i;
		ans+=d[t]!=d[i];
	}
	printf("%d\n", ans);
	return 0;
}
