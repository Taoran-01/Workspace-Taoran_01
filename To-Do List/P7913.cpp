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

#define N 100010
#define M 5010
int n, m1, m2;
struct node {int l, r;} d1[M], d2[M];
bool operator<(node a, node b) {return a.r==b.r?a.r<b.r:a.l<b.l;}
bool cmp(node a, node b) {return a.l<b.l;}

signed main() {
	freopen("P7913_1.in", "r", stdin);
	freopen("P7913.out", "w", stdout);
	n=read(), m1=read(), m2=read();
	for (int i=1; i<=m1; ++i) {int l=read(), r=read(); d1[i]={l,r};}
	for (int i=1; i<=m2; ++i) {int l=read(), r=read(); d2[i]={l,r};}
	return 0;
}
