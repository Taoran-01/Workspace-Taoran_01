#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
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
和：区间加，区间查询和。将数组分成sqrt(n)块，整块和散块分别操作。
排名：区间加，查询单点在区间内的排名。对每一个块维护未排序数组a和已排序数组b，reset重新排序。
哈希：区间修改，区间查询单个数的出现次数。对每一个块维护一个map。
	由于map的存在，块的大小应为sqrt(n log n)，但是这里写的sqrt(n)。
*/

#define N 100010
ll n;
ll buildSource[N];

template <typename T> struct chunking_summation {
	ll block, t;
	ll st[N], ed[N], pos[N];
	T a[N], sum[N], add[N];
	void build() {
		block=sqrt(n), t=n/block; if (n%block) ++t;
		for (ll i=1; i<=t; ++i) st[i]=(i-1)*block+1, ed[i]=i*block; ed[t]=n;
		for (ll i=1; i<=n; ++i) pos[i]=(i-1)/block+1, a[i]=buildSource[i];
		for (ll i=1; i<=t; ++i) for (ll j=st[i]; j<=ed[i]; ++j) sum[i]+=a[j];
	}
	void modify(ll l, ll r, T k) {
		ll pl=pos[l], pr=pos[r];
		if (pl==pr) {
			for (ll i=l; i<=r; ++i) a[i]+=k;
			sum[pl]+=k*(r-l+1); return;
		}
		for (ll i=pl+1; i<=pr-1; ++i) add[i]+=k;
		for (ll i=l; i<=ed[pl]; ++i) a[i]+=k; sum[pl]+=k*(ed[pl]-l+1);
		for (ll i=st[pr]; i<=r; ++i) a[i]+=k; sum[pr]+=k*(r-st[pr]+1);
	}
	T query(ll l, ll r) {
		ll pl=pos[l], pr=pos[r]; T ans=0;
		if (pl==pr) {
			for (ll i=l; i<=r; ++i) ans+=a[i];
			ans+=add[pl]*(r-l+1); return ans;
		}
		for (ll i=pl+1; i<=pr-1; ++i) ans+=sum[i]+add[i]*(ed[i]-st[i]+1);
		for (ll i=l; i<=ed[pl]; ++i) ans+=a[i]; ans+=add[pl]*(ed[pl]-l+1);
		for (ll i=st[pr]; i<=r; ++i) ans+=a[i]; ans+=add[pr]*(r-st[pr]+1);
		return ans;
	}
};

template <typename T> struct chunking_ranking {
	ll block, t;
	ll st[N], ed[N], pos[N];
	T a[N], b[N], add[N];
	void build() {
		block=sqrt(n), t=n/block; if (n%block) ++t;
		for (ll i=1; i<=t; ++i) st[i]=(i-1)*block+1, ed[i]=i*block; ed[t]=n;
		for (ll i=1; i<=n; ++i) pos[i]=(i-1)/block+1, a[i]=b[i]=buildSource[i];
		for (ll i=1; i<=t; ++i) sort(b+st[i], b+ed[i]+1);
	}
	void reset(ll p) {
		for (ll i=st[p]; i<=ed[p]; ++i) b[i]=a[i]; sort(b+st[p], b+ed[p]+1);
	}
	ll find(ll p, T k) {
		ll l=st[p], r=ed[p], mid=0;
		while (l<=r) mid=l+r>>1, (b[mid]>=k)?r=mid-1:l=mid+1; return ed[p]-l+1;
	}
	void modify(ll l, ll r, T k) {
		ll pl=pos[l], pr=pos[r];
		if (pl==pr) {for (ll i=l; i<=r; ++i) a[i]+=k; reset(pl); return;}
		for (ll i=pl+1; i<=pr-1; ++i) add[i]+=k;
		for (ll i=l; i<=ed[pl]; ++i) a[i]+=k; reset(pl);
		for (ll i=st[pr]; i<=r; ++i) a[i]+=k; reset(pr);
	}
	ll query(ll l, ll r, T k) {
		ll pl=pos[l], pr=pos[r], ans=0;
		if (pl==pr) {
			for (ll i=l; i<=r; ++i) if (a[i]+add[pl]>=k) ++ans;
			return ans;
		}
		for (ll i=pl+1; i<=pr-1; ++i) ans+=find(i, k-add[i]);
		for (ll i=l; i<=ed[pl]; ++i) if (a[i]+add[pl]>=k) ++ans;
		for (ll i=st[pr]; i<=r; ++i) if (a[i]+add[pr]>=k) ++ans;
		return ans;
	}
};

template <typename T> struct chunking_hashing {
	ll block, t, st[N], ed[N], pos[N];
	T a[N], tag[N]; map<T, ll> mp[N];
	void build() {
		block=sqrt(n), t=n/block; if (n%block) ++t;
		for (ll i=1; i<=t; ++i) st[i]=(i-1)*block+1, ed[i]=min(n,i*block);
		for (ll i=1; i<=n; ++i) pos[i]=(i-1)/block+1, a[i]=buildSource[i];
		for (ll i=1; i<=t; ++i) mp[i].clear(), tag[i]=-1;
		for (ll i=1; i<=n; ++i) mp[pos[i]][a[i]]++;
	}
	void push_down(ll p) {
		if (!~tag[p]) return; for (ll i=st[p]; i<=ed[p]; ++i) a[i]=tag[p];
		mp[p].clear(), mp[p][tag[p]]=ed[p]-st[p]+1, tag[p]=-1; return;
	}
	void modify(ll l, ll r, T k) {
		ll pl=pos[l], pr=pos[r]; push_down(pl), push_down(pr);
		if (pl==pr) {
			for (ll i=l; i<=r; ++i) --mp[pl][a[i]], a[i]=k, ++mp[pl][a[i]];
			return;
		}
		for (ll i=pl+1; i<=pr-1; ++i) tag[i]=k;
		for (ll i=l; i<=ed[pl]; ++i) --mp[pl][a[i]], a[i]=k, ++mp[pl][a[i]];
		for (ll i=st[pr]; i<=r; ++i) --mp[pr][a[i]], a[i]=k, ++mp[pr][a[i]];
	}
	ll query(ll l, ll r, T k) {
		ll pl=pos[l], pr=pos[r], ans=0; push_down(pl), push_down(pr);
		if (pl==pr) {for (ll i=l; i<=r; ++i) ans+=a[i]==k; return ans;}
		for (ll i=pl+1; i<=pr-1; ++i) {
			if (~tag[i]) {if (tag[i]==k) ans+=ed[i]-st[i]+1;}
			else {if (mp[i].count(k)) ans+=mp[i][k];}
		}
		for (ll i=l; i<=ed[pl]; ++i) ans+=a[i]==k;
		for (ll i=st[pr]; i<=r; ++i) ans+=a[i]==k;
		return ans;
	}
};

signed main() {
	return 0;
}
