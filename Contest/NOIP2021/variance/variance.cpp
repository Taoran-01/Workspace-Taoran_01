#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace chrono;
typedef long long ll;
typedef long double db;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 10010
#define INF 0x7f7f7f7f7f7f7f7fLL
#define sqr(x) ((x)*(x))
int n; ll ans;
int a[N], a1[N];

int get(int l, int r) {return rand()%(r-l+1)+l;}
db get() {return 1.0L*rand()/RAND_MAX;}

ll calc(int a[]) {
	ll ave=0, res=0;
	for (int i=1; i<=n; ++i) ave+=a[i];
	for (int i=1; i<=n; ++i) res+=sqr(n*a[i]-ave);
	return res/n;
}

#define STT 10000000.0
#define EDT 0.00000001
#define DTT 0.9998
void SA() {
	// fprintf(stderr, "SA\n");
	memcpy(a1, a, sizeof(a));
	ll cans=calc(a1);
	for (db t=STT; t>EDT; t*=DTT) {
		int x=get(2, n-1), tmp=a1[x];
		a1[x]=a1[x-1]+a1[x+1]-a1[x];
		// if (a1[x]==tmp) continue;
		ll cur=calc(a1);
		// fprintf(stderr, "t=%.4Lf x=%d cans=%lld cur=%lld\n", t,x,cans,cur);
		if (cur<cans) cans=cur; // ACC
		else if (get()>exp(-1.0L*(cur-cans)/t)) {} // ACC
		else a1[x]=tmp; // REJ
	}
	ans=min(cans, ans);
}

#define TIM 0.97
int st=clock();
signed main() {
	freopen("variance.in", "r", stdin);
	freopen("variance.out", "w", stdout);
	n=read(), ans=INF;
	srand(30822);
	// srand(steady_clock::now().time_since_epoch().count());
	for (int i=1; i<=n; ++i) a[i]=read();
	if (n==2) return printf("%d\n", (sqr(2*a[1]-2*(a[1]+a[2])/2)
		+sqr(2*a[2]-2*(a[1]+a[2])/2))/2), 0;
	while (1.0*(clock()-st)/CLOCKS_PER_SEC<TIM) SA();
	// SA();
	printf("%lld\n", ans);
	fprintf(stderr, "%.2f\n", 1.0*(clock()-st)/CLOCKS_PER_SEC);
	return 0;
}
