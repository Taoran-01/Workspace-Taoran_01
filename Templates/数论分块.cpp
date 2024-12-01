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
计算 i∈[1,n] Σf(i)⌊n/i⌋
s(i)=j∈[1,i] Σf(j)
*/

#define N 1000010
int n;
ll s[N], ans;

signed main() {
	freopen("a.in", "r", stdin);
	for (int i=1; i<=n; ++i) s[i]=read()+s[i-1];
	for (int l=1, r=0; l<=n; l=r+1) {
		r=n/(n/l);
		ans+=(s[r]-s[l-1])*(n/l);
	}
	return 0;
}
