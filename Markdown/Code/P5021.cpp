#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
typedef long long ll;
#define int ll

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 50010
int n, m;

#define v e[i].to
#define w e[i].val
int head[N], tot;
struct edge {int to, nxt, val;} e[N<<1];
void add_edge(int x, int y, int z) {e[++tot]={y, head[x], z}, head[x]=tot;}

int mxd, mxd_idx;
int diam;

void diam_dfs(int u, int fa, int dep) {
	if (dep>mxd) mxd=dep, mxd_idx=u; diam=max(diam, dep);
	for (int i=head[u]; i; i=e[i].nxt) if (v!=fa) diam_dfs(v, u, dep+w);
}

int mid;
int cnt;

int dfs(int u, int fa) {
	multiset<int> st;
	for (int i=head[u]; i; i=e[i].nxt) {
		if (v==fa) continue; int x=dfs(v, u)+w;
		if (x>=mid) {++cnt; continue;}
		st.insert(x);
	}
	int val=0;
	while (!st.empty()) {
		if (st.size()==1) {val=max(val, *st.begin()); break;}
		auto it=st.lower_bound(mid-*st.begin());
		if (it==st.end()) val=max(val, *st.begin()), st.erase(st.begin());
		else ++cnt, st.erase(it), st.erase(st.begin());
	}
	return val;
}

bool chk() {
	cnt=0, dfs(1, 0);
	return cnt>=m;
}

signed main() {
	// freopen("track1.in", "r", stdin);
	// freopen("track1.out", "w", stdout);
	n=read(), m=read();
	for (int i=1; i<n; ++i) {
		int x=read(), y=read(), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	diam_dfs(1, 0, 0), diam_dfs(mxd_idx, 0, 0);
	int l=0, r=diam+1, ans=0;
	while (l<r) {
		mid=(l+r)>>1;
		if (chk()) l=mid+1, ans=mid;
		else r=mid;
	}
	printf("%lld\n", ans);
	return 0;
}
