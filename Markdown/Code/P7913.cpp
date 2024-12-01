#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
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
#define M 100010
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
int n, m1, m2, ans;
int ans1[N], ans2[N];
struct node {int l, r, idx;} d1[M], d2[M];
bool operator<(node a, node b) {return a.r==b.r?a.l<b.l:a.r>b.r;}
bool cmp(node a, node b) {return a.l<b.l;}

void calc(node d[], int m, int ans[]) {
	priority_queue<pii, vector<pii>, greater<pii>> lve;
	priority_queue<int, vector<int>, greater<int>> spr;
	for (int i=1; i<=n; ++i) spr.push(i);
	for (int i=1; i<=m; ++i) {
		while (!lve.empty()&&lve.top().fi<=d[i].l) {
			int x=lve.top().se; lve.pop(); spr.push(x);
		}
		if (spr.empty()) continue;
		int x=spr.top(); spr.pop();
		++ans[x], lve.push(mp(d[i].r, x));
	}
	for (int i=1; i<=n; ++i) ans[i]+=ans[i-1];
}

signed main() {
	// freopen("P7913_9.in", "r", stdin);
	// freopen("P7913.out", "w", stdout);
	n=read(), m1=read(), m2=read();
	for (int i=1; i<=m1; ++i) {int l=read(), r=read(); d1[i]={l,r,i};}
	for (int i=1; i<=m2; ++i) {int l=read(), r=read(); d2[i]={l,r,i};}
	sort(d1+1, d1+m1+1, cmp), sort(d2+1, d2+m2+1, cmp);
	calc(d1, m1, ans1), calc(d2, m2, ans2);
	// for (int i=1; i<=m1; ++i) printf("%d ", ans1[i]); puts("");
	// for (int i=1; i<=m2; ++i) printf("%d ", ans2[i]); puts("");
	for (int i=0; i<=n; ++i) ans=max(ans, ans1[i]+ans2[n-i]);
	printf("%d\n", ans);
	return 0;
}
