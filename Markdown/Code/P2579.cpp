#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
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

#define MN 60
#define MM 60
#define mod 10000LL

struct Matrix {
	int n, m; ll d[MN][MM];
	ll* operator[](int x) {return d[x];}
	Matrix() {n=0, m=0, memset(d, 0, sizeof(d));}
	void output() {
		for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
			printf("%d%c", d[i][j], (j==m)?'\n':' ');
		} puts("");
	}
};

Matrix operator*(Matrix &a, Matrix &b) {
	Matrix z=Matrix(); z.n=a.n, z.m=b.m; // a.m=b.n
	for (int i=1; i<=a.n; ++i) for (int j=1; j<=a.m; ++j) {
		for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+a[i][j]*b[j][k])%mod;
	}
	return z;
} void operator*=(Matrix &a, Matrix b) {a=a*b;}

Matrix qpow(Matrix a, ll b) {
	assert(a.n==a.m); Matrix res=Matrix(); res.n=res.m=a.n;
	for (int i=1; i<=res.n; ++i) res[i][i]=1;
	while (b) {if (b&1) res*=a; a*=a, b>>=1;}
	return res;
}

#define N 60
int n, m, q, s, t, k;

Matrix a, ans;
Matrix d[20]; // d[12]=\prod_{i=0}^11 d[i]
bool ban[20][N];

signed main() {
	// freopen("P2579.in", "r", stdin);
	n=read(), m=read(), s=read()+1, t=read()+1, k=read();
	a.n=a.m=d[12].n=d[12].m=n;
	while (m--) {int x=read()+1, y=read()+1; a[x][y]=a[y][x]=1;}
	q=read(); while (q--) {
		int rnd=read(); for (int i=0; i<rnd; ++i) {
			int u=read()+1;
			for (int j=i; j<12; j+=rnd) ban[j][u]=1;
		}
	}
	for (int i=0; i<12; ++i) {
		d[i]=a;
		for (int j=1; j<=n; ++j) for (int k=1; k<=n; ++k) {
			d[i][j][k]&=!ban[i][k];
		}
	}
	d[12]=qpow(d[12], 0);
	for (int i=1; i<=12; ++i) d[12]*=d[i%12];
	
	ans=qpow(d[12], k/12);
	for (int i=1; i<=k%12; ++i) ans*=d[i];
	printf("%lld\n", ans[s][t]);
	return 0;
}
