#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
using namespace std;
typedef long long ll;
typedef long double db;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 13
#define LX 2010.0L
int n;
int stt=clock();

const db sttp=2010;
const db edtp=0.0001;
const db dttp=0.99998;
db tp;

db d[N][N], dt[N], chg[N];
db pos[N], ave;

db sqr(db x) {return x*x;}
db get() {return 1.0L*rand()/RAND_MAX;}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n+1; ++i) for (int j=1; j<=n; ++j) scanf("%Lf", &d[i][j]);
	for (int i=1; i<=n+1; ++i) for (int j=1; j<=n; ++j) pos[j]+=d[i][j];
	for (int i=1; i<=n; ++i) pos[i]/=n+1;
	for (tp=sttp; tp>=edtp&&1.0*(clock()-stt)/CLOCKS_PER_SEC<=0.995; tp*=dttp) {
		ave=0;
		for (int i=1; i<=n+1; ++i) {
			dt[i]=chg[i]=0;
			for (int j=1; j<=n; ++j) dt[i]+=sqr(d[i][j]-pos[j]);
			dt[i]=sqrt(dt[i]), ave+=dt[i];
		}
		ave/=n+1;
		for (int i=1; i<=n+1; ++i) for (int j=1; j<=n; ++j) chg[j]+=(dt[i]-ave)*(d[i][j]-pos[j])/ave;
		for (int i=1; i<=n; ++i) pos[i]+=chg[i]*tp;
	}
	for (int i=1; i<=n; ++i) printf("%.3Lf ", pos[i]);
	return 0;
}
