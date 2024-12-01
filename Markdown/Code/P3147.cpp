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

#define N 262160
#define L 60
int n, ans;
int a[N];
int f[N][L]; // lf, val => rt ( interval [lf,rt) )

signed main() {
	// freopen("d1.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read(), f[i][a[i]]=i+1;
	for (int i=1; i<=n; ++i) ans=max(ans, a[i]); // Important
	for (int x=1; x<L; ++x) for (int i=1; i<=n; ++i) {
		if (!f[i][x]) f[i][x]=f[f[i][x-1]][x-1];
		if (f[i][x]) ans=max(ans, x);
	}
	printf("%d\n", ans);
	return 0;
}
