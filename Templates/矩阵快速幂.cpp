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

#define MN 10
#define MM 10
#define mod 1000000007LL
// #define mod 998244353LL

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

// ll smul(ll a, ll b) {
// 	ll res=0;
// 	while (b) {if (b&1) res=(res+a)%mod; a=(a+a)%mod, b>>=1;}
// 	return res;
// }

Matrix operator*(Matrix &a, Matrix &b) {
	Matrix z=Matrix(); z.n=a.n, z.m=b.m; // a.m=b.n
	for (int i=1; i<=a.n; ++i) for (int j=1; j<=a.m; ++j) {
		for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+a[i][j]*b[j][k])%mod;
		// for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+smul(a[i][j], b[j][k]))%mod;
	}
	return z;
} void operator*=(Matrix &a, Matrix b) {a=a*b;}

Matrix qpow(Matrix a, ll b) {
	assert(a.n==a.m); Matrix res=Matrix(); res.n=res.m=a.n;
	for (int i=1; i<=res.n; ++i) res[i][i]=1;
	while (b) {if (b&1) res*=a; a*=a, b>>=1;}
	return res;
}

signed main() {
	return 0;
}
