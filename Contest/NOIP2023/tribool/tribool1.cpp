#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
#define INF 0x7f7f7f7f
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int T, tc;
int n, m;
vector<pair<char, pii>> seq;
int d[N<<1];

int fa[N<<1];
int find(int x) {return (x==fa[x]?x:fa[x]=find(fa[x]));}
void uni(int x, int y) {fa[find(x)]=find(y);}

signed main() {
	freopen("tribool2.in", "r", stdin);
	tc=read(), T=read();
	while (T--) {
		n=read(), m=read();
		for (int i=1; i<=n; ++i) d[i]=INF;
		for (int i=1; i<=n+n; ++i) fa[i]=i;
		seq.clear(), seq.reserve(m);
		for (int i=1; i<=m; ++i) {
			char opt=getchar(); int x=read(), y=INF;
			while ((opt<'A'||opt>'Z')&&opt!='-'&&opt!='+') opt=getchar();
			if (opt=='-'||opt=='+') y=read();
			seq.push_back(mkp(opt, mkp(x, y)));
		}
		int len1=0;
		for (auto p:seq) {
			char &opt=p.fi; int &x=p.se.fi, &y=p.se.se;
			if (opt>='A'&&opt<='Z') d[x]=opt=='U'?1:0;
			else if (d[y]!=INF) d[x]=d[y];
			else seq[len1++]=p;
		}
		seq.resize(len1);
		for (auto it=seq.rbegin(); it!=seq.rend(); ++it) {
			char &opt=it->fi; int &x=it->se.fi, &y=it->se.se;
			assert(opt<'A'||opt>'Z');
			assert(y!=INF);
			// fprintf(stderr, "%d %d %d %d\n", x, d[x], y, d[y]);
			// assert(d[x]==INF&&d[y]==INF);
			if (opt=='+') uni(x, y), uni(x+n, y+n);
			if (opt=='-') uni(x, y+n), uni(x+n, y);
		}
		for (int i=1; i<=n; ++i) if (d[i]==INF) {
			d[i]=(find(i)==find(i+n));
			// fprintf(stderr, "%d %d\n", find(i), find(i+n));
		}
		int ans=0;
		for (int i=1; i<=n; ++i) ans+=d[i];
		// for (int i=1; i<=n; ++i) fprintf(stderr, "%d ", d[i]);
		printf("%d\n", ans);
	}
	return 0;
}
