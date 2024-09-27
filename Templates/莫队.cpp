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
如果从[l,r]的答案能够O(1)扩展到[l-1,r],[l+1,r],[l,r+1],[l,r-1]的答案，
那么可以在O(n\sqrt n)的复杂度内求出所有询问的答案。前提：做法离线、O(1)转移。
*/

#define N 100010
int n, m, block;
int a[N], t1, t2;
int curL, curR;

struct query {int id, l, r;} q[N];
bool operator<(query x, query y) {
	if (x.l/block!=y.l/block) return x.l<y.l;
	return ((x.l/block)&1)?x.r<y.r:x.r>y.r;
}

void add(int x) {}
void del(int x) {}

signed main() {
	n=read(), m=read(), block=sqrt(n), curL=1;
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=m; ++i) t1=read(), t2=read(), q[i]={i, t1, t2};
	sort(q+1, q+m+1);
	for (int i=1; i<=m; ++i) {
		while (curL<q[i].l) del(a[curL++]);
		while (curL>q[i].l) add(a[--curL]);
		while (curR>q[i].r) del(a[curR--]);
		while (curR<q[i].r) add(a[++curR]);
		// ans ...
	}
	// output ...
	return 0;
}
