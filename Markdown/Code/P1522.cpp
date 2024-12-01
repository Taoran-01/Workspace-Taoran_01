#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
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

#define N 160
#define INF 1e18
#define eps 1e-8
int n, fa[N];
double x[N], y[N], d[N][N], far[N]; // Furthest‌ Dist in DSU
double ans, diam[N];
vector<int> v[N];

template <typename T> T sqr(T x) {return x*x;}
int find(int x) {return (x==fa[x]?x:fa[x]=find(fa[x]));}
void uni(int x, int y) {fa[find(x)]=find(y);}

signed main() {
	// freopen("a3.in", "r", stdin);
	// freopen("a3.out", "w", stdout);
	n=read(), ans=INF;
	for (int i=1; i<=n; ++i) fa[i]=i;
	for (int i=1; i<=n; ++i) x[i]=read(), y[i]=read();
	for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		char ch=getchar(); while (ch!='0'&&ch!='1') ch=getchar();
		if (ch=='0'&&i!=j) d[i][j]=INF; // d[i][i]←0
		else d[i][j]=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])), uni(i, j);
	}
	for (int k=1; k<=n; ++k) for (int i=1; i<=n; ++i) for (int j=1; j<=n; ++j) {
		if (d[i][k]+d[k][j]-d[i][j]<-eps) d[i][j]=d[i][k]+d[k][j];
		// d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
	} 
	for (int i=1; i<=n; ++i) v[find(i)].push_back(i);
	for (auto v1:v) for (int i:v1) for (int j:v1) far[i]=max(far[i], d[i][j]);
	for (int x=1; x<=n; ++x) for (int i:v[x]) diam[x]=max(diam[x], far[i]);
	for (auto v1:v) for (auto v2:v) if (v1!=v2) for (int i:v1) for (int j:v2) {
		double dist=sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
		ans=min(ans, max(max(diam[find(i)], diam[find(j)]), far[i]+dist+far[j]));
	}
	printf("%.6lf", ans);
	return 0;
}
