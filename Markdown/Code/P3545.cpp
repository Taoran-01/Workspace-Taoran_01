#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
#define int ll

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 250010
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int n, ans;
int a[N];
priority_queue<pii> q;
vector<int> tmp;

signed main() {
	// freopen("hur10a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=1; i<=n; ++i) {
		int b=read(); a[i]+=a[i-1];
		if (a[i]>=b) a[i]-=b, q.push(mkp(b,i)), ++ans;
		else if (!q.empty()&&b<q.top().fi) {
			a[i]+=q.top().fi, q.pop(), --ans;
			a[i]-=b, q.push(mkp(b,i)), ++ans;
		}
	}
	printf("%lld\n", ans);
	while (!q.empty()) tmp.push_back(q.top().se), q.pop();
	sort(tmp.begin(), tmp.end());
	for (auto x:tmp) printf("%lld ", x); puts("");
	return 0;
}

// chk hur10a.in a.out hur10a.out
