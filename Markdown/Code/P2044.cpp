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

#define MN 10
#define MM 10

ll mod;

ll smul(ll a, ll b) {
	ll res=0;
	while (b) {if (b&1) res=(res+a)%mod; a=(a+a)%mod, b>>=1;}
	return res;
}

struct Matrix {
	int n, m; ll d[MN][MM];
	ll* operator[](int x) {return d[x];}
	Matrix() {n=0, m=0, memset(d, 0, sizeof(d));}
};

Matrix operator*(Matrix &a, Matrix &b) {
	Matrix z=Matrix(); z.n=a.n, z.m=b.m; // a.m=b.n
	for (int i=1; i<=a.n; ++i) for (int j=1; j<=a.m; ++j) {
		for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+smul(a[i][j], b[j][k]))%mod;
	}
	return z;
}
void operator*=(Matrix &a, Matrix b) {a=a*b;}

template <typename T> T qpow(T a, ll b) {
	T res=a; --b;
	while (b) {if (b&1) res*=a; a*=a, b>>=1;}
	return res;
}

ll a, c, x0, n, g;
Matrix x, y, ans;

signed main() {
	// freopen("a.in", "r", stdin);
	mod=read(), a=read(), c=read(), x0=read(), n=read(), g=read();
	x=y=Matrix(), x.n=2, x.m=2, y.n=2, y.m=1;
	x[1][1]=a, x[1][2]=1, x[2][1]=0, x[2][2]=1;
	y[1][1]=x0, y[2][1]=c;
	x=qpow(x, n), ans=x*y;
	printf("%lld\n", ans[1][1]%g);
	return 0;
}
