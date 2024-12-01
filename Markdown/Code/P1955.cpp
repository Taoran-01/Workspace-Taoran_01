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

#define M 100010
#define N 200010
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
int T;
int m; bool flag;
pair<bool, pii> d[M];
int fa[N];
int t[N], n;

int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}

signed main() {
	// freopen("a.in", "r", stdin);
	T=read();
	while (T--) {
		n=0, m=read(), flag=1;
		for (int i=1; i<=m; ++i) {
			d[i].se.fi=read(), d[i].se.se=read(), d[i].fi=!read();
			t[++n]=d[i].se.fi, t[++n]=d[i].se.se;
		}
		sort(t+1, t+n+1), n=unique(t+1, t+n+1)-t-1;
		for (int i=1; i<=m; ++i) {
			d[i].se.fi=lower_bound(t+1, t+n+1, d[i].se.fi)-t;
			d[i].se.se=lower_bound(t+1, t+n+1, d[i].se.se)-t;
		}
		for (int i=1; i<=n; ++i) fa[i]=i;
		sort(d+1, d+m+1);
		for (int i=1; i<=m; ++i) {
			int f1=find(d[i].se.fi), f2=find(d[i].se.se);
			if (!d[i].fi) fa[f1]=f2;
			else if (f1==f2) {puts("NO"), flag=0; break;}
		}
		if (flag) puts("YES");
	}
	return 0;
}
