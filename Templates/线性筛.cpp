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

/*
求1到n的所有素数，prime[i]表示第i个素数。
*/

#define N 100000010
int n, cnt;
int prime[N], vis[N];

signed main() {
	n=read(), vis[1]=1;
	for (int i=2; i<=n; ++i) {
		if (!vis[i]) prime[++cnt]=i;
		for (int j=1; j<=cnt&&i*prime[j]<=n; ++j) {
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
	return 0;
}
