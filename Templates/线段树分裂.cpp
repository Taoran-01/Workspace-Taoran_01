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
给出一个可重集 a（编号为 1），它支持以下操作：
`0 p x y`：将可重集 p 中大于等于 x 且小于等于 y 的值移动到一个新的可重集中（新可重集编号为从 2 开始的正整数，是上一次产生的新可重集的编号+1）。
`1 p t`：将可重集 t 中的数放入可重集 p，且清空可重集 t（数据保证在此后的操作中不会出现可重集 t）。
`2 p x q`：在 p 这个可重集中加入 x 个数字 q。
`3 p x y`：查询可重集 p 中大于等于 x 且小于等于 y 的值的个数。
`4 p k`：查询在 p 这个可重集中第 k 小的数，不存在时输出 `-1`。
*/

#define N 100010
int n, m, opt, t1, t2, t3, seq;
int bac[N<<4], ls[N<<4], rs[N<<4], rt[N];
ll val[N<<4];

int tot, cnt;
#define newnode() (cnt?bac[cnt--]:++tot)
#define del(p) (bac[++cnt]=p, ls[p]=rs[p]=val[p]=0)

void modify(int l, int r, int pos, int &p, int v) {
	if (!p) p=newnode(); val[p]+=v; int mid=l+r>>1; if (l==r) return;
	(pos<=mid)?modify(l, mid, pos, ls[p], v):modify(mid+1, r, pos, rs[p], v);
}

ll query(int nl, int nr, int l, int r, int p) {
	if (!p) return 0;
	if (nr<l||r<nl) return 0; if (nl<=l&&r<=nr) return val[p];
	int mid=l+r>>1; return query(nl,nr,l,mid,ls[p])+query(nl,nr,mid+1,r,rs[p]);
}

int kth(int l, int r, int p, int k) {
	if (l==r) return l; int mid=l+r>>1;
	return (val[ls[p]]>=k)?kth(l,mid,ls[p],k):kth(mid+1,r,rs[p],k-val[ls[p]]);
}

int merge(int x, int y) {
	if (!x||!y) return x|y; val[x]+=val[y];
	ls[x]=merge(ls[x], ls[y]); rs[x]=merge(rs[x], rs[y]); del(y); return x;
}

void split(int x, int &y, ll k) {
	if(!x) return;
	y=newnode(); ll v=val[ls[x]];
	(k>v)?split(rs[x], rs[y], k-v):swap(rs[x], rs[y]);
	if (k<v) split(ls[x], ls[y], k); val[y]=val[x]-k, val[x]=k;
}

signed main() {
	// freopen("temp.in", "r", stdin);
	n=read(), m=read(), seq=1;
	for (int i=1; i<=n; ++i) t1=read(), modify(1, n, i, rt[1], t1);
	while (m--) {
		opt=read(), t1=read(), t2=read(); if (opt==0||opt==2||opt==3) t3=read();
		if (opt==0) {
			ll k1=query(1, t3, 1, n, rt[t1]), k2=query(t2, t3, 1, n, rt[t1]);
			int nd=0; split(rt[t1], rt[++seq], k1-k2); split(rt[seq], nd, k2);
			rt[t1]=merge(rt[t1], nd);
		} else if (opt==1) rt[t1]=merge(rt[t1], rt[t2]);
		else if (opt==2) modify(1, n, t3, rt[t1], t2);
		else if (opt==3) printf("%lld\n", query(t2, t3, 1, n, rt[t1]));
		else if (opt==4) printf("%lld\n", val[rt[t1]]<t2?1LL*-1:kth(1,n,rt[t1],t2));
	}
	return 0;
}
