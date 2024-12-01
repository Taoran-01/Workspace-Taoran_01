#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#include <random>
#include <chrono>
using namespace chrono;
mt19937 randEngine(steady_clock::now().time_since_epoch().count());
int get(int l, int r) {return (randEngine())%(r-l+1)+l;}

#define INF 0x7f7f7f7f
int x, y; char opt;
char s[4]={'+', '-', '*', '/'};

signed main() {
	freopen("a.in", "w", stdout);
	x=get(0, INF), y=get(0, INF);
	opt=s[get(0,3)];
	if (opt=='-') while (x<y) x=get(0, INF), y=get(0, INF);
	printf("%d %d %c\n", x, y, opt);
	return 0;
}
