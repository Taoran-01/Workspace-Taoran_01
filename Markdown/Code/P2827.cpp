#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
#define M 7000010
#define INF 0x7f7f7f7f7f7f7f7fLL
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
// typedef __gnu_pbds::priority_queue<int> heap;
int n, m, q, u, v, t;
int d[N];
// heap a;
queue<int> a, b, c;

// #define DEBUG
#define TC "earthworm17"

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

	n=read(), m=read(), q=read(), u=read(), v=read(), t=read();
	// for (int i=1; i<=n; ++i) a.push((int)read());
	for (int i=1; i<=n; ++i) d[i]=read();
	sort(d+1, d+n+1);
	for (int i=n; i; --i) a.push(d[i]); 

	for (int tim=1; tim<=m; ++tim) {
		ll p=-INF;
		if (!a.empty()) p=max(p, 1LL*a.front());
		if (!b.empty()) p=max(p, 1LL*b.front());
		if (!c.empty()) p=max(p, 1LL*c.front());
		if (!a.empty()&&p==a.front()) a.pop();
		else if (!b.empty()&&p==b.front()) b.pop();
		else if (!c.empty()&&p==c.front()) c.pop();
		ll dt=(tim-1)*q; p+=dt;
		b.push(int(p*u/v)-dt-q);
		c.push(int(p-p*u/v)-dt-q);
		if (tim%t==0) printf("%lld ", p);
	} puts("");

	for (int idx=1; (!a.empty()||!b.empty()||!c.empty()); ++idx) {
		// fprintf(stderr, "%d %d %d\n", !a.empty(), !b.empty(), !c.empty());
		ll p=-INF;
		if (!a.empty()) p=max(p, 1LL*a.front());
		if (!b.empty()) p=max(p, 1LL*b.front());
		if (!c.empty()) p=max(p, 1LL*c.front());
		if (!a.empty()&&p==a.front()) a.pop();
		else if (!b.empty()&&p==b.front()) b.pop();
		else if (!c.empty()&&p==c.front()) c.pop();
		p+=m*q;
		if (idx%t==0) printf("%lld ", p);
	} puts("");

	#ifdef DEBUG
	fclose(stdout);
	chktim;
	char s2_[100]=""; sprintf(s2_, "fc a.out %s.ans /w >nul", TC);
	fprintf(stderr, "CHECK: %d\n", system(s2_));
	#endif
	return 0;
}
