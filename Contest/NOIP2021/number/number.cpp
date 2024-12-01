#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 10000010
bool vis[N];
int nxt[N], p;
int T;

signed main() {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	for (int i=1; i<N; ++i) {
		for (int x=i; x; x/=10) if (x%10==7) vis[i]=1;
		if (!vis[i]) {nxt[p]=i, p=i; continue;}
		for (int j=2; i*j<N; ++j) vis[i*j]=1;
	}
	T=read();
	while (T--) {
		int x=read();
		if (vis[x]) puts("-1");
		else printf("%d\n", nxt[x]);
	}
	return 0;
}
