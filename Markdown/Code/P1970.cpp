#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
int n;
int a[N];
int ans1, ans2;
bool s1, s2;

signed main() {
	// freopen("flower8.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read(), s1=0, s2=1, ans1=ans2=1;
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=2; i<=n; ++i) {
		if (a[i]!=a[i-1]&&s1!=(a[i]>a[i-1])) s1^=1, ++ans1;
		if (a[i]!=a[i-1]&&s2!=(a[i]>a[i-1])) s2^=1, ++ans2;
	}
	printf("%d\n", max(ans1, ans2));
	return 0;
}
