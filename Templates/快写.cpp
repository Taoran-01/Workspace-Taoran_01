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

void write(const char* s) {while (*s) putchar(*s++);}
void write(const char s) {putchar(s);}
template <typename T> void write(T x) {
	if (x<0) return putchar('-'), write(-x);
	if (x==0) return putchar('0'), void();
	char d[20]={}; int idx=0;
	while (x>0) d[++idx]=x%10+48, x/=10;
	while (idx) putchar(d[idx--]);
}
template<typename T, typename... Args>
void write(const T& fst, const Args&... args) {
	write(fst); write(args...);
}

signed main() {
	freopen("a.in", "r", stdin);
	return 0;
}
