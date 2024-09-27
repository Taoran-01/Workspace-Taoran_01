#include <cmath>
#include <ctime>
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

/*
输入一个匹配串s和一个模式串t，询问t出现过的次数。
*/

#define N 1000010
int n, m, fail[N], cnt;
char s[N], t[N];

void computePartialMatchTable() {
	fail[1]=0;
	for (int q=2, k=0; q<=m; ++q) {
		while (k&&t[k+1]!=t[q]) k=fail[k];
		if (t[k+1]==t[q]) ++k;
		fail[q]=k;
	}
}

void kmp() {
	cnt=0;
	computePartialMatchTable();
	for (int i=1, q=0; i<=n; ++i) {
		while (q&&t[q+1]!=s[i]) q=fail[q];
		if (t[q+1]==s[i]) ++q;
		if (q==m) ++cnt, q=fail[q];
	}
}

signed main() {
	return 0;
}
