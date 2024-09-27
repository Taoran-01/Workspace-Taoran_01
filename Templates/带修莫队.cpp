#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
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

/*
数总数1~N，范围1~M
1. 'Q' L R 询问L到R有多少个不同的数
2. 'R' P C 将第P个数改为C
*/

#define N 150010
#define M 1000010
int n, m, block;
int a[N], t1, t2;
int curL, curR, curT;
int cnt[M], curans, ans[N];
char opt;

struct query {int id, l, r, t;} q[N]; int qcnt;
bool operator<(query x, query y) {
	if (x.l/block!=y.l/block) return x.l>y.l;
	if (x.r/block!=y.r/block) return x.r>y.r;
	return x.t>y.t;
}

struct operation {int p, x;} r[N]; int rcnt;

void add(int x) {curans+=!cnt[x]++;}
void del(int x) {curans-=!--cnt[x];}

void upd(int tim) {
	if (r[tim].p>=curL&&r[tim].p<=curR) add(r[tim].x), del(a[r[tim].p]);
	swap(a[r[tim].p], r[tim].x);
}

signed main() {
	n=read(), m=read(), block=pow(n, 2.0/3.0), curL=1;
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=m; ++i) {
		opt=getchar(); while (opt!='Q'&&opt!='R') opt=getchar();
		t1=read(), t2=read();
		if (opt=='Q') q[++qcnt]={qcnt, t1, t2, rcnt};
		else if (opt=='R') r[++rcnt]={t1, t2};
	}
	sort(q+1, q+m+1);
	for (int i=1; i<=qcnt; ++i) {
		while (curL<q[i].l) del(a[curL++]);
		while (curL>q[i].l) add(a[--curL]);
		while (curR>q[i].r) del(a[curR--]);
		while (curR<q[i].r) add(a[++curR]);
		while (curT<q[i].t) upd(++curT);
		while (curT>q[i].t) upd(curT--);
		ans[q[i].id]=curans;
	}
	for (int i=1; i<=qcnt; ++i) printf("%lld\n", ans[i]);
	return 0;
}
