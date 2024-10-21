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

#define N 110
#define INF 0x1f1f1f1f1f1f1f1fLL
int n, m; ll len;
ll w[N][N], d[N][N];
int suf[N][N];
vector<int> ans;
vector<int>::iterator it;

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), m=read(), len=INF;
	memset(d, 0x1f, sizeof(d));
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(); ll z=read();
		d[x][y]=min(d[x][y], z), d[y][x]=min(d[y][x], z);
	}
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) suf[i][j]=j;
	memcpy(w, d, sizeof(w));
	for (int k=1; k<=n; ++k) {
		for (int i=1; i<k; ++i) for (int j=1; j<i; ++j) {
			if (len<=d[i][j]+w[i][k]+w[j][k]) continue;
			len=d[i][j]+w[i][k]+w[j][k];
			ans.clear();
			for (int x=i; x!=j; x=suf[x][j]) ans.push_back(x);
			ans.push_back(j), ans.push_back(k);
		}
		for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
			if (d[i][k]+d[k][j]>d[i][j]) continue;
			d[i][j]=d[i][k]+d[k][j], suf[i][j]=suf[i][k];
		}
	}
	if (len==INF) return puts("No solution."), 0;
	for (it=ans.begin(); it!=ans.end(); ++it) {
		printf("%d", *it); if (it!=ans.end()-1) putchar(' ');
	}
	return 0;
}
