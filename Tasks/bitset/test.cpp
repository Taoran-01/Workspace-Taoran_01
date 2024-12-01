#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

inline ull read() {
	ull x=0; char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x;
}

#define N 100010
typedef bitset<N+10> bts;

bool operator<(bts a, bts b) {
	for (signed i=N-1; i; --i) if (a.test(i)!=b.test(i)) return b.test(i);
	return 0;
} bool operator<=(bts a, bts b) {return a<b||a==b;}
bool operator>(bts a, bts b) {return !(a<=b);}
bool operator>=(bts a, bts b) {return !(a<b);}

bts operator+(bts a, bts b) {
	while (b.any()) a=a^b, b=((a^b)&b)<<1;
	return a;
} void operator+=(bts &a, bts b) {a=a+b;}
bts operator-(bts a) {return ~a+1;}
// bts operator-(bts a, bts b) {return a+(-b);} // too slow
bts operator-(bts a, bts b) {
	while (b.any()) a=a^b, b=((~(a^b))&b)<<1;
	return a;
} void operator-=(bts &a, bts b) {a=a-b;}

bts operator*(bts a, bts b) {
	bts res=0;
	while (b.any()) {if (b.test(0)) res=res+a; a=a+a, b>>=1;}
	return res;
} void operator*=(bts &a, bts b) {a=a*b;}
bts operator/(bts a, bts b) {
	bts res=0; signed hda=0, hdb=0, sft=0;
	while (a._Find_next(hda)!=a.size()) hda=a._Find_next(hda);
	while (b._Find_next(hdb)!=b.size()) hdb=b._Find_next(hdb);
	sft=max(hda-hdb, 0);
	for (; ~sft; --sft) if (a>=(b<<sft)) a-=(b<<sft), res.set(sft, 1);
	return res;
} void operator/=(bts &a, bts b) {a=a/b;}

#include <random>
#include <chrono>
using namespace chrono;
mt19937 randEngine(steady_clock::now().time_since_epoch().count());
int get(int l, int r) {return (randEngine())%(r-l+1)+l;}

ull x0, y0;
bts msk, x, y;

#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)

signed main() {
	freopen("a.in", "r", stdin);
	x0=read(), y0=read(), x=x0, y=y0;
	char ch=getchar();
	if (ch=='+') x+=y, printf("%llu\n", x.to_ullong());
	if (ch=='-') x-=y, printf("%llu\n", x.to_ullong());
	if (ch=='*') x*=y, printf("%llu\n", x.to_ullong());
	if (ch=='/') x/=y, printf("%llu\n", x.to_ullong());
	return 0;
}
