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

// #define N 1010
#define N 100010
#define EPS 1e-8
#define INF 0x7f7f7f7f
#define L 10
char s[N];
ll a[N], n;
ll k[N];
ll f[N][L+2], ans;

int T;

signed main() {
	freopen("bargain2.in", "r", stdin);
	freopen("bargain2.out", "w", stdout);
	read(), T=read(); while (T--) {
		scanf("%s\a", s+1), n=strlen(s+1), ans=INF;
		for (int i=1; i<=n; ++i) a[i]=s[i]-'0';
		for (int i=1; i<=9; ++i) k[i]=read();
		for (int i=n; i; --i) {
			for (int j=0; j<=L; ++j) {
				f[i][j]=f[i+1][j]+k[a[i]];
				if (j) f[i][j]=min(f[i][j], f[i+1][j-1]+ll(a[i]*pow(10, j-1)+EPS));
			}
		}
		for (int j=0; j<=L; ++j) ans=min(ans, f[1][j]);
		printf("%lld\n", ans);
	}
	// read();
	return 0;
}
