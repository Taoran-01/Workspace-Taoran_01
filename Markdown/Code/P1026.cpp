#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 210
#define M 10
#define K 50
int p, n, k, m;
char s[N];
string t[M];
int l[M];

int cst[N][N];
int f[N][K];

bool check(int l,int r){
	string x="";
	for (int i=l; i<=r; ++i) x.push_back(s[i]);
	for (int i=1; i<=m; i++) if (x.find(t[i])==0) return 1;
	return 0;
}

signed main() {
	// freopen("a.in", "r", stdin);
	p=read(), k=read();
	n=p*20;
	for (int i=0; i<p; ++i) {
		scanf("%s", s+i*20+1);
	}
	m=read();
	for (int i=1; i<=m; ++i) cin>>t[i];
	for (int i=n; i>=1; --i) {
		for (int j=i; j>=1; --j) {
			cst[j][i]=cst[j+1][i];
			if (check(j,i)) ++cst[j][i];
		}
	}
	for (int i=1; i<=k; ++i) {
		f[i][i]=f[i-1][i-1]+cst[i][i];
	}
	for (int i=1; i<=n; ++i) {
		f[i][1]=cst[1][i];
	}
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=min(k, i-1); ++j) {
			for (int x=j; x<i; ++x) {
				f[i][j]=max(f[i][j], f[x][j-1]+cst[x+1][i]);
			}
		}
	}
	printf("%d\n", f[n][k]);
	// printf("%d\n", cst[1][n]);
	return 0;
}
