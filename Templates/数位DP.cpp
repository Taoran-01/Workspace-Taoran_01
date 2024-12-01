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

#define N 15
int num[N];
ll f[N][10][N][2][2];

// k: target calculating number
// sum: contribution to answer
ll dfs(int pos, int k, int sum, bool nzr/*no zero*/, bool lim) {
	if (pos==0) return sum;
	ll &res=f[pos][k][sum][nzr][lim];
	if (~res) return res; res=0;
	int maxx=lim?num[pos]:9; // first digit
	for (int i=0; i<=maxx; ++i) {
		res+=dfs(pos-1, k, sum+(i==k&&(i!=0||!nzr)), nzr&&i==0, lim&&i==maxx);
	}
	return res;
}

ll solve(ll x, int k) {
	memset(f, 0xff, sizeof(f));
	int len=0;
	while (x) num[++len]=x%10, x/=10;
	return dfs(len, k, 0, 1, 1);
}

signed main() {
	// freopen("a.in", "r", stdin);
	ll a=read(), b=read();
	for (int k=0; k<=9; ++k) printf("%lld ", solve(b, k)-solve(a-1, k));
	return 0;
}
