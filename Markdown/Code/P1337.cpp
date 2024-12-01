#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
typedef long long ll;
typedef long double db;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 1010
#define LX 10010.0L
int n;
int px[N], py[N], pz[N];
int stt=clock();

const db sttp=3000.0L;
const db edtp=1e-9;
const db dttp=0.995L;
db tp;
db x, y, dis;

db sqr(db x) {return x*x;}
db get() {return 1.0L*rand()/RAND_MAX;}
db calc(db x, db y) {
	db dis=0;
	for (int i=1; i<=n; ++i) dis+=sqrt(sqr(x-px[i])+sqr(y-py[i]))*pz[i];
	return dis;
}

signed main() {
// 	freopen("a.in", "r", stdin);
	srand(steady_clock::now().time_since_epoch().count());
	// srand(114514);
	n=read();
	for (int i=1; i<=n; ++i) px[i]=read(), py[i]=read(), pz[i]=read();
	for (int i=1; i<=n; ++i) x+=px[i], y+=py[i]; x/=n, y/=n, dis=calc(x, y);
	int cnt=5;
	while (cnt--) {
		for (tp=sttp; tp>edtp; tp*=dttp) {
			db dx=LX*(2.0L*get()-1.0L)*(tp/sttp), dy=LX*(2.0L*get()-1.0L)*(tp/sttp);
			db nx=x+dx, ny=y+dy, ndis=calc(nx, ny);
			if (ndis<dis||exp(-(ndis-dis)/tp)>get()*10) x=nx, y=ny, dis=ndis;
		}
// 		cout<<++cnt<<endl;
	}
	printf("%.3Lf %.3Lf\n", x, y);
	return 0;
}
