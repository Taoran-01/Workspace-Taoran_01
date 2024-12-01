#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
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

#define N 100010
#define S 320
#define mod 1000000007
typedef pair<pair<int,int>,int> ppi;
#define fi first
#define se second
#define mkp make_pair
int n, sn;
ll f[N];
ll ans;

ll tag[S][S];
vector<ppi> seq[N];

// #define DEBUG
// #define TC "a"
#define TC "trains.57-5"

#ifdef DEBUG
#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)
#endif

signed main() {
	#ifdef DEBUG
	char s1_[100]=""; sprintf(s1_, "%s.in", TC);
	freopen(s1_, "r", stdin);
	freopen("a.out", "w", stdout);
	#endif

	n=read(), sn=sqrt(n);
	f[1]=1;
	for (int i=1; i<=n; ++i) {
		for (ppi op:seq[i]) tag[op.fi.fi][op.fi.se]=\
			(tag[op.fi.fi][op.fi.se]+op.se+mod)%mod;
		int d=read(), x=read();
		for (int j=1; j<=sn; ++j) f[i]=(f[i]+tag[j][i%j])%mod;
		if (!d) continue; // !
		if (d>sn) {
			for (int j=1; j<=x; ++j) {
				int p=i+1LL*j*d; if (p>n) break;
				f[p]=(f[p]+f[i])%mod;
			}
			continue;
		}
		tag[d][i%d]=(tag[d][i%d]+f[i])%mod;
		if (i+1LL*d*x+1>n) continue;
		seq[i+d*x+1].push_back(mkp(mkp(d,i%d),-f[i]));
	}
	for (int i=1; i<=n; ++i) ans=(ans+f[i])%mod;
	printf("%lld\n", ans);

	#ifdef DEBUG
	fprintf(stderr, "%lld\n", ans);
	fclose(stdout);
	chktim;
	char s2_[100]=""; sprintf(s2_, "fc a.out %s.sol >nul", TC);
	fprintf(stderr, "CHECK: %d\n", system(s2_));
	#endif
	return 0;
}
