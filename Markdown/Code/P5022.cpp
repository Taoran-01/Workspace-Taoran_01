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

#define N 5010
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
#define inv(i) (((i-1)^1)+1)
int n, m;
bool vis[N];
vector<int> ans, ans1;

#define v e[i].to
int head[N], tot;
struct edge {int to, nxt; bool ext;} e[N<<1];
void add_edge(int x, int y) {e[++tot]={y, head[x], 1}, head[x]=tot;}

void srt_edge() {
	for (int u=1; u<=n; ++u) {
		vector<pii> tmp;
		for (int i=head[u]; i; i=e[i].nxt) tmp.push_back(mkp(v, i));
		sort(tmp.begin(), tmp.end()), tmp.push_back(mkp(0, 0));
		auto it=tmp.begin(); head[u]=(*it).se;
		for (int i=head[u]; i; i=e[i].nxt) e[i].nxt=(*it++).se;
	}
}

void dfs(int u) {
	ans1.push_back(u), vis[u]=1;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (!e[i].ext) continue;
		if (!vis[v]) dfs(v);
	}
}

signed main() {
	// freopen("travel.in", "r", stdin);
	// freopen("travel.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read();
		add_edge(x, y), add_edge(y, x);
	}
	srt_edge();
	if (m==n-1) {
		dfs(1);
		for (int x:ans1) printf("%d ", x); puts("");
	} else if (m==n) {
		ans.resize(n), ans[0]=N;
		for (int i=1; i<=tot; i+=2) {
			ans1.clear(), memset(vis, 0, sizeof(vis));
			e[i].ext=0, e[inv(i)].ext=0;
			dfs(1);
			e[i].ext=1, e[inv(i)].ext=1;
			if ((int)ans1.size()!=n) continue;
			ans=min(ans, ans1);
		}
		for (auto x:ans) printf("%d ", x); puts("");
	}
	return 0;
}
