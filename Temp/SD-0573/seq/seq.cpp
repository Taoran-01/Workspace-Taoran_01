#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
int n, tot, x, y;
vector<int> tmp;
int a[N];

// 67731

signed main() {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	n=read(), x=read(), y=read();
	tmp.reserve(n);
	for (int i=1; i<=y; ++i) {
		a[n-i+1]=n-(y-i+1)+1;
	}
	tot=n-y;
	for (int i=0; i<x-1; ++i) {
		tmp.push_back(1), --tot;
	}
	if (tot<0) return puts("NO"), 0;
	for (auto it=tmp.rbegin(); it!=tmp.rend()&&tot; ++it) {
		int rem=y-*it;
		if (rem<=0) break;
		if (rem>=tot) (*it)+=tot, tot=0;
		else (*it)+=rem, tot-=rem;
	}
//	for (auto x:tmp) fprintf(stderr, "%d ", x); fprintf(stderr, "\n");
	if (tot) return puts("NO"), 0;
	
	for (auto x:tmp) {
		tot+=x;
		for (int i=1; i<=x; ++i) a[tot-i+1]=tot-(x-i+1)+1;
	}
	
	puts("YES");
	for (int i=1; i<=n; ++i) printf("%d ", a[i]);
	puts("");
	return 0;
}

