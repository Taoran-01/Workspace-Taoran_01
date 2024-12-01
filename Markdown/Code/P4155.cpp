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

#define N 400010
#define L 20
int n, m;
int Log[N];
int nxt[N][L];
struct node {int l, r, id;} d[N];
bool operator<(node x, node y) {return x.l<y.l;}
int ans[N];

signed main() {
	// freopen("a.in", "r", stdin);
	for (int i=2; i<N; ++i) Log[i]=Log[i>>1]+1;
	n=read(), m=read();
	for (int i=1; i<=n; ++i) {
		int x=read(), y=read(); if (x>y) y+=m;
		d[i].l=x, d[i].r=y, d[i].id=i;
		d[i+n].l=x+m, d[i+n].r=y+m, d[i+n].id=i+n;
	}
	sort(d+1, d+n*2+1);
	for (int i=1, j=1; i<=n*2; ++i) { // O(n) because i,j in [1,n]
		while (j<=n*2&&d[i].r>=d[j].l) ++j; // find the most useful interval
		nxt[i][0]=j-1;
	}
	for (int j=1; j<L; ++j) for (int i=1; i<=n*2; ++i) {
		nxt[i][j]=nxt[nxt[i][j-1]][j-1];
	}
	for (int i=1; i<=n; ++i) {
		ans[d[i].id]=0; int x=i, r=d[i].l+m;
		for (int j=L-1; ~j; --j) if (nxt[x][j]&&d[nxt[x][j]].r<r) { // here
			x=nxt[x][j], ans[d[i].id]+=1<<j;
		}
		ans[d[i].id]+=2; // 1. <r + the last one | 2. itself 
	}
	for (int i=1; i<=n; ++i) printf("%d ", ans[i]);
	return 0;
}
