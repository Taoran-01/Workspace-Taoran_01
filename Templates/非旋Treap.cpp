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
维护一个序列：
1. 插入x
2. 删除x
3. 查询x的排名
4. 查询排名为x的数
5. 求小于等于x的最大值
6. 求大于等于x的最小值
*/

#define N 100010
int n, opt, x;

namespace FHQ {
	int rt, tot;
	int ls[N], rs[N], val[N], rnd[N], siz[N];
	void push(int p) {siz[p]=siz[ls[p]]+siz[rs[p]]+1;}
	void spl(int p, int v, int &x, int &y) {
		if (!p) return x=y=0, void();
		if (val[p]<=v) spl(rs[p], v, rs[x=p], y);
		else spl(ls[p], v, x, ls[y=p]); push(p);
	}
	int mer(int x, int y) {
		if (!x||!y) return x|y;
		if (rnd[x]<rnd[y]) return ls[y]=mer(x, ls[y]), push(y), y;
		return rs[x]=mer(rs[x], y), push(x), x;
	}
	int mer(int x, int y, int z) {return mer(x, mer(y, z));}
	int add(int v) {return val[++tot]=v, rnd[tot]=rand(), siz[tot]=1, tot;}
	void ins(int v) {int x=0, y=0; spl(rt, v-1, x, y), rt=mer(x, add(v), y);}
	void del(int v) {
		int x=0, y=0, z=0; spl(rt, v-1, x, y), spl(y, v, y, z);
		y=mer(ls[y], rs[y]), rt=mer(x, y, z);
	}
	int kth(int k) {
		for (int p=rt; ; ) {
			if (k<siz[ls[p]]+1) p=ls[p];
			else if (k>siz[ls[p]]+1) k-=siz[ls[p]]+1, p=rs[p];
			else return val[p];
		}
	}
	int pre(int v) {
		for (int p=rt, ans=0; ; ) {
			if (!p) return ans;
			else if (v<=val[p]) p=ls[p];
			else ans=val[p], p=rs[p];
		}
	}
	int suc(int v) {
		for (int p=rt, ans=0; ; ) {
			if (!p) return ans;
			else if (v>=val[p]) p=rs[p];
			else ans=val[p], p=ls[p];
		}
	}
	int rnk(int v) {
		int x=0, y=0, ans=0;
		spl(rt, v-1, x, y), ans=siz[x]+1, rt=mer(x, y);
		return ans;
	}
}

signed main() {
	n=read();
	for (int i=1; i<=n; ++i) {
		opt=read(), x=read();
		if (opt==1) FHQ::ins(x);
		if (opt==2) FHQ::del(x);
		if (opt==3) printf("%d\n", FHQ::rnk(x));
		if (opt==4) printf("%d\n", FHQ::kth(x));
		if (opt==5) printf("%d\n", FHQ::pre(x));
		if (opt==6) printf("%d\n", FHQ::suc(x));
	}
	return 0;
}
