#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
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
#define M 200010
int n, m;
int ind[N], otd[N], rt;

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt;} e[M<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x]}, head[x]=tot;}

bool vis[N];
vector<int> route;
vector<int>::reverse_iterator it;

void dfs(int u) {
	for (int i=head[u]; i; i=head[u]) {
		head[u]=e[i].nxt;
		dfs(v);
	}
	route.push_back(u);
}

void sort_edge() {
	for (int u=1; u<=n; ++u) {
		vector<int> tmp;
		for (int i=head[u]; i; i=e[i].nxt) tmp.push_back(v);
		sort(tmp.begin(), tmp.end());
		for (int i=head[u], x=0; i; i=e[i].nxt, ++x) v=tmp[x];
	}
}

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(); add_edge(x, y), ++ind[y], ++otd[x];
	}
	for (int i=1; i<=n; ++i) {
		if (otd[i]-ind[i]==1) {if (rt) return puts("No"), 0; rt=i;}
		if (abs(otd[i]-ind[i])>1) return puts("No"), 0;
	}
	sort_edge(), dfs(rt?rt:1);
	if (route.size()!=unsigned(m+1)) return puts("No"), 0;
	for (it=route.rbegin(); it!=route.rend(); ++it) printf("%d ", *it); puts("");
	return 0;
}
