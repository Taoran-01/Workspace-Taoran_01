#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define W 32010
#define N0 70
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int w, n0, n, rt;
int c0[N0], v0[N0], f0[N0];
vector<int> son[N0];

vector<vector<pii>> d;
// .fi cst | .se val

int f[W];

signed main() {
	// freopen("P1064_2.in", "r", stdin);
	w=read(), n0=read(), rt=n0+1;
	for (int i=1; i<=n0; ++i) {
		c0[i]=read(), v0[i]=c0[i]*read(), f0[i]=read();
		son[f0[i]].push_back(i);
	}
	d.push_back(vector<pii>());
	for (int i=1; i<=n0; ++i) {
		if (f0[i]) continue;
		d.push_back(vector<pii>()), d[++n].reserve(son[i].size());
		for (int x=0; x<1<<son[i].size(); ++x) {
			d[n].push_back(mkp(c0[i],v0[i])); pii &y=d[n].back();
			for (int j=0; j<(int)son[i].size(); ++j) {
				if (x&(1<<j)) y.fi+=c0[son[i][j]], y.se+=v0[son[i][j]];
			}
		}
	}
	fprintf(stderr, "%d\n", n);
	for (int i=1; i<=n; ++i) {
		for (pii x:d[i]) fprintf(stderr, "(%d %d) ", x.fi, x.se);
		fprintf(stderr, "\n");
	}
	for (int i=1; i<=n; ++i) {
		for (int k=w; ~k; --k) {
			for (pii j:d[i]) if (j.fi<=k) {
				f[k]=max(f[k], f[k-j.fi]+j.se);
			}
		}
	}
	for (int k=0; k<=w; ++k) f[w]=max(f[w], f[k]);
	printf("%d\n", f[w]);
	return 0;
}
