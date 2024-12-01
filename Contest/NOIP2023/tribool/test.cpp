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

struct node {
	int x;
	// node() {x=0;}
	// node() {}
};

#define N 1000
node d1[N];

signed main() {
	freopen("a.in", "r", stdin);
	node d2[N];
	printf("%d %d\n", d1[2].x, d2[105].x);
	for (auto x:d1) {
		printf("%d ", x.x);
	}
	return 0;
}
