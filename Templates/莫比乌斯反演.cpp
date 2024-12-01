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
给定n、m和k，求满足条件1<=i<=n，1<=j<=m，gcd(i,j)=k的个数，整除分块优化。
*/

#define N 10000010
int n, m, k, cnt; ll ans;
int prime[N], vis[N], mu[N], sum[N];

signed main() {
	vis[1]=1, mu[1]=1;
	for (int i=2; i<N; ++i) {
		if (!vis[i]) prime[++cnt]=i, mu[i]=-1;
		for (int j=1; j<=cnt&&i*prime[j]<N; ++j) {
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) {mu[i*prime[j]]=0; break;}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for (int i=1; i<N; ++i) sum[i]=sum[i-1]+mu[i]; // otherwise ...
	n=read(), m=read(), k=read(), n/=k, m/=k, ans=0; if (n>m) swap(n, m);
	for (int l=1, r; l<=n; l=r+1) {
		r=min(n/(n/l), m/(m/l));
		ans+=1LL*(sum[r]-sum[l-1])*(n/l)*(m/l);
	}
	printf("%lld\n", ans);
	return 0;
}
