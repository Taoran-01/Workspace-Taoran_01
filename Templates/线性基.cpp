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
对于线性基所表示的所有数的集合S，S中任意多个数异或所得的结果均能表示为线性基中的元素互相异或的结果。线性基能使用异或运算来表示原数集使用异或运算能表示的所有数。
1. ins(x) 插入x
2. chk(x) 查询x能否被S中的数异或得到
3. qmax() 查询S中若干数异或起来的最大值
4. qmin() 查询S中若干数异或起来的最小值
5. query(k) 查询S中若干数异或起来第k小的值

前缀线性基：使用pos[i]表示线性基的第i个数受影响的数的最小编号，即pos[i]之后线性基a[i]才有效。
PrefixLinerBasis a[N]; 初始a[i]=a[i-1]，类似前缀和。
1. ins(x) 插入x
2. chk(x, l) 查询l之后x是否能被S中的数异或得到
3. qmax(l) 查询l之后S中若干数异或起来的最大值
查询区间[l,r]异或最大值，可以使用a[r].qmax(l)得到。
*/

#define V 63 // log(range)
typedef unsigned long long ull;
struct LinerBasis {
	ull a[V+1], tmp[V+1]; bool zf; // Zero Flag
	void ins(ull x) { // Insert
		for (int i=V; ~i; --i) if (x&1ULL<<i) {
			if (!a[i]) return a[i]=x, void();
			x^=a[i];
		}
		zf=true;
	}
	bool chk(ull x) { // Check Exist
		for (int i=V; ~i; --i) if (x&1ULL<<i) {
			if (!a[i]) return false;
			x^=a[i];
		}
		return true;
	}
	ull qmax() { // Query Max
		ull res=0;
		for (int i=V; ~i; --i) res=max(res, res^a[i]);
		return res;
	}
	ull qmin() { // Query Min
		if (zf) return 0;
		for (int i=0; i<=V; ++i) if (a[i]) return a[i];
	}
	ull query(int k) { // Query the kth Smaller
		ull res=0; int cnt=0;
		k-=zf; if (!k) return 0;
		for (int i=0; i<=V; ++i) {
			for (int j=i-1; ~j; --j) if (a[i]&(1ULL<<j)) a[i]^=a[j];
			if (a[i]) tmp[cnt++]=a[i];
		}
		if (k>=(1ULL<<cnt)) return -1;
		for (int i=0; i<cnt; ++i) if (k&1ULL<<i) res^=tmp[i];
		return res;
	}
};

#define V 63
typedef unsigned long long ull;
struct PrefixLinerBasis {
	ull a[V+1]; int pos[V+1]; // Zero Flag
	void ins(ull x, int p) { // Insert(val, pos)
		for (int i=V; ~i; --i) if (x&1ULL<<i) {
			if (!a[i]) return a[i]=x, pos[i]=p, void();
			if (pos[i]<p) swap(pos[i], p), swap(a[i], x);
			x^=a[i];
		}
	}
	bool chk(ull x, int l) { // Check Exist ( "pos" in Range [l, +INF) )
		for (int i=V; ~i; --i) if (x&1ULL<<i) {
			if (!a[i]||pos[i]<l) return false;
			x^=a[i];
		}
		return true;
	}
	ull qmax(int l) { // Query Max ( "pos" in Range [l, +INF) )
		ull res=0;
		for (int i=V; ~i; --i) {
			if (pos[i]<l) continue;
			res=max(res, res^a[i]);
		}
		return res;
	}
};

signed main() {
	return 0;
}
