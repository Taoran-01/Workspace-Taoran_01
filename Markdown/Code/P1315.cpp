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

#define N 1010
#define M 10010
int n, m, k;
ll ans;
int d[N];
int arvC[N], arvP[N];
int lve[N];
struct node {int tim, fr, to;} f[M];
bool operator<(node x, node y) {return x.fr<y.fr;}

signed main() {
	// freopen("P1315_3.in", "r", stdin);
	// freopen("P1315_3.out", "w", stdout);
	n=read(), m=read(), k=read();
	for (int i=1; i<n; ++i) d[i]=read();
	for (int i=1; i<=m; ++i) f[i].tim=read(), f[i].fr=read(), f[i].to=read();
	for (int i=1; i<=m; ++i) {
		arvP[f[i].fr]=max(arvP[f[i].fr], f[i].tim), ++lve[f[i].to];
	} for (int i=1; i<n; ++i) arvC[i+1]=max(arvC[i], arvP[i])+d[i];
	while (k--) {
		int pos=0, maxx=0;
		for (int i=2; i<=n; ++i) {
			if (!d[i-1]) continue;
			int cur=0;
			for (int j=i; j<=n; ++j) {cur+=lve[j]; if (arvC[j]<=arvP[j]) break;}
			if (cur>maxx) maxx=cur, pos=i;
		}
		if (!pos) break;
		--d[pos-1];
		for (int j=pos; j<=n; ++j) {--arvC[j]; if (arvC[j]<arvP[j]) break;}
	}
	for (int i=1; i<=m; ++i) ans+=arvC[f[i].to]-f[i].tim;
	printf("%lld\n", ans);
	// fclose(stdout);
	// fprintf(stderr, "CHECK: %d\n", system("fc P1315_3.out P1315_3.ans >nul"));
	return 0;
}
