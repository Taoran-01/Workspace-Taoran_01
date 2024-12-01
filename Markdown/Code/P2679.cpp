#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 1010
#define M 210
#define mod 1000000007
int n, m, k;
char a[N], b[N];
int s[N][N];
int f[N][N];

signed main() {
	// freopen("b.in", "r", stdin);
	n=read(), m=read(), k=read(), f[0][0]=1;
	scanf("%s %s", a+1, b+1);
	for (int i=1; i<=n; ++i) {
		for (int j=m; j>=1; --j) {
			for (int l=min(min(i, j), k); l>=1; --l) {
				s[j][l]=(a[i]==b[j]?s[j-1][l]+f[j-1][l-1]:0)%mod;
				f[j][l]=(f[j][l]+s[j][l])%mod;
			}
		}
	}
	printf("%d\n", f[m][k]%mod);
	return 0;
}
