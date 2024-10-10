#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, stapmx=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') stapmx=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*stapmx;
}

// stABCC
// A: a->a b->b
// B: p->positive n->negative
// C: mx->max mn->min

#define PINF 0x7f7f7f7f
#define NINF 0x80808080
#define N 100010
#define L 20
int n, m, q, l, r;
int a[N], b[N];
int stapmx[N][L], stapmn[N][L], stanmx[N][L], stanmn[N][L];
int stbpmx[N][L], stbpmn[N][L], stbnmx[N][L], stbnmn[N][L];
int LOG[N];

int qry(int st[N][L]) {int x=LOG[r-l+1]; return max(st[l][x], st[r-(1<<x)+1][x]);}

signed main() {
	freopen("P8818_1.in", "r", stdin);
	// freopen("P8818_1.out", "r", stdin);
	for (int i=2; i<N; ++i) LOG[i]=LOG[i>>1]+1;
	n=read(), m=read(), q=read();
	memset(stapmx, 0x80, sizeof(stapmx)), memset(stapmn, 0x7f, sizeof(stapmn));
	memset(stanmx, 0x80, sizeof(stanmx)), memset(stanmn, 0x7f, sizeof(stanmn));
	memset(stbpmx, 0x80, sizeof(stbpmx)), memset(stbpmn, 0x7f, sizeof(stbpmn));
	memset(stbnmx, 0x80, sizeof(stbnmx)), memset(stbnmn, 0x7f, sizeof(stbnmn));
	for (int i=1; i<=n; ++i) {
		a[i]=read();
		if (a[i]>=0) stapmx[i][i]=stapmn[i][i]=a[i];
		if (a[i]<=0) stanmx[i][i]=stanmn[i][i]=a[i];
	}
	for (int i=1; i<=m; ++i) {
		b[i]=read();
		if (b[i]>=0) stbpmx[i][i]=stbpmn[i][i]=b[i];
		if (b[i]<=0) stbnmx[i][i]=stbnmn[i][i]=b[i];
	}
	for (int j=1; j<=LOG[n]; ++j) for (int i=1; i<=n-(1<<j)+1; ++i) {
		stapmx[i][j]=max(stapmx[i][j-1], stapmx[i+(1<<(j-1))][j-1]);
		stapmn[i][j]=min(stapmn[i][j-1], stapmn[i+(1<<(j-1))][j-1]);
		stanmx[i][j]=max(stanmx[i][j-1], stanmx[i+(1<<(j-1))][j-1]);
		stanmn[i][j]=min(stanmn[i][j-1], stanmn[i+(1<<(j-1))][j-1]);
	}
	for (int j=1; j<=LOG[m]; ++j) for (int i=1; i<=m-(1<<j)+1; ++i) {
		stbpmx[i][j]=max(stbpmx[i][j-1], stbpmx[i+(1<<(j-1))][j-1]);
		stbpmn[i][j]=min(stbpmn[i][j-1], stbpmn[i+(1<<(j-1))][j-1]);
		stbnmx[i][j]=max(stbnmx[i][j-1], stbnmx[i+(1<<(j-1))][j-1]);
		stbnmn[i][j]=min(stbnmn[i][j-1], stbnmn[i+(1<<(j-1))][j-1]);
	}
	while (q--) {
		l=read(), r=read(); ll ans=(1LL*NINF<<32)+NINF;
		ll apmx=qry(stapmx), apmn=qry(stapmn), anmx=qry(stanmx), anmn=qry(stanmn);
		ll bpmx=qry(stbpmx), bpmn=qry(stbpmn), bnmx=qry(stbnmx), bnmn=qry(stbnmn);
		if (apmx!=NINF) ans=max(ans, apmx*min(bpmn, bnmn));
		if (apmn!=PINF) ans=max(ans, apmn*min(bpmn, bnmn));
		if (anmx!=NINF) ans=max(ans, anmx*max(bpmx, bnmx));
		if (anmn!=PINF) ans=max(ans, anmn*max(bpmx, bnmx));
		printf("%lld\n", ans);
	}
	return 0;
}
