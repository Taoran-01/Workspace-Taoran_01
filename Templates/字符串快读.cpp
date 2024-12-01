#include <cmath>
#include <ctime>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void getstr(char* s, int &len) {
	for (int pt=1; s[pt]; ++pt) s[pt]=0;
	char ch=getchar(); len=0;
	while (ch<'a'||ch>'z') ch=getchar();
	while (ch>='a'&&ch<='z') s[++len]=ch, ch=getchar();
}

signed main() {
	return 0;
}
