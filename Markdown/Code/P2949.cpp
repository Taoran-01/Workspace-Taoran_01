#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
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

#define N 100010
int n, tim;
ll ans;
struct node {int d, p;} d[N];
bool operator<(node a, node b) {return a.p>b.p;}
bool cmp(node a, node b) {return a.d<b.d;}
priority_queue<node> q;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), tim=1;
	for (int i=1; i<=n; ++i) {d[i].d=read(), d[i].p=read();}
	sort(d+1, d+n+1, cmp);
	for (int i=1; i<=n; ++i) {
		if (tim<=d[i].d) ans+=d[i].p, q.push(d[i]), ++tim;
		else {
			node u=q.top();
			if (u.p<d[i].p) q.pop(), q.push(d[i]), ans+=d[i].p-u.p;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
