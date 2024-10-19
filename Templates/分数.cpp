#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
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

#define mod 1000000007LL

#include <algorithm>
#define gcd __gcd
template <typename T1, typename T2, typename T3> T1 qpow(T1 a, T2 b, T3 m) {
	T1 res=1; while (b) {if (b&1) res=res*a%m; a=a*a%m, b>>=1;} return res;
}
template <typename T> void prtnum(T n) { // numeric output
	if (n<0) putchar('-'), n=-n; if (n==0) return putchar('0'), void();
	string res; while (n) res+=n%10+'0', n/=10;
	reverse(res.begin(), res.end()); printf("%s", res.c_str());
}
struct frac {
	__int128_t num, den; bool sgn; frac() {num=0, den=1, sgn=0;}
	void simp() {
		if (num<0) num=-num, sgn^=1;
		__int128_t g=gcd(num, den); num/=g, den/=g;
	} __int128_t gnum() {return sgn?-num:num;}
	frac(int nume, int deno) {num=nume, den=deno, sgn=0, simp();}
	frac(int nume, int deno, bool sign) {num=nume, den=deno, sgn=sign, simp();}
	void prt() {prtnum(gnum()), putchar('/'), prtnum(den), puts("");}
};
frac operator+(frac a, frac b) {
	frac c=frac(); ll g=gcd(a.den, b.den);
	c.den=a.den/g*b.den, c.num=b.den/g*a.gnum()+a.den/g*b.gnum();
	if (c.num<0) c.sgn=1, c.num=-c.num; return c;
} void operator+=(frac &a, frac b) {a=a+b;}
frac operator*(frac a, frac b) {
	frac c; ll g1=gcd(a.num, b.den), g2=gcd(a.den, b.num);
	c.sgn=a.sgn^b.sgn, c.num=a.num/g1*b.num/g2, c.den=a.den/g2*b.den/g1;
	return c;
} void operator*=(frac &a, frac b) {a=a*b;}
frac operator-(frac a, frac b) {b.sgn=!b.sgn; return a+b;}
void operator-=(frac &a, frac b) {b.sgn=!b.sgn, a+=b;}
frac operator/(frac a, frac b) {swap(b.num, b.den); return a*b;}
void operator/=(frac &a, frac b) {swap(b.num, b.den), a*=b;}
template <typename T> __int128_t operator%(frac a, T b) {
	return (a.gnum()*qpow(a.den, b-2, b)+b)%b;
}

signed main() {
	return 0;
}
