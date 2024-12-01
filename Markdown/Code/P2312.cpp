#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
#define mod 1000000097

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=((x<<1)+(x<<3)+(ch^48))%mod, ch=getchar();
	return (x*f+mod)%mod;
}

#define N 110
int n, m; ll x;
ll a[N];
ll ans[N], tot;

ll calc() {
	ll ans=0;
	for (int i=n; ~i; --i) {
		ans=(ans+a[i])%mod; if (i) ans=ans*x%mod;
	}
	return ans;
}

#define DEBUG

#ifdef DEBUG
#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)
#endif

signed main() {
	#ifdef DEBUG
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	#endif
	n=read(), m=read();
	for (int i=0; i<=n; ++i) a[i]=read();
	for (x=1; x<=m; ++x) if (calc()==0LL) ans[++tot]=x;
	printf("%lld\n", tot);
	for (int i=1; i<=tot; ++i) printf("%lld\n", ans[i]);
	#ifdef DEBUG
	fclose(stdout);
	chktim;
	fprintf(stderr, "CHECK: %d\n", system("fc a.out a.ans >nul"));
	#endif
	return 0;
}
