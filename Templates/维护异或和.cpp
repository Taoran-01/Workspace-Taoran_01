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
维护一些数的异或和，支持插入、删除、合并、全局加一等操作。
rt[u]=trie::merge(rt[u], rt[v]);
trie::insert(rt[u], x, 0);
*/

#define N 500010
#define M 12500010 // M = N * 25

namespace trie {
	int rt[N], ch[M][2], w[M], xorv[M], tot=0;
	void maintain(int x) {
		w[x]=xorv[x]=0;
		if (ch[x][0]) w[x]+=w[ch[x][0]], xorv[x]^=xorv[ch[x][0]]<<1;
		if (ch[x][1]) w[x]+=w[ch[x][1]], xorv[x]^=(xorv[ch[x][1]]<<1)|(w[ch[x][1]]&1);
	}
	int mknode() {ch[++tot][0]=ch[tot][1]=0, w[tot]=0; return tot;}
	void insert(int &x, int num, int dep) {
		if (!x) x=mknode();
		if (dep>20) {++w[x]; return;}
		insert(ch[x][num&1], num>>1, dep+1);
		maintain(x);
	}
	void erase(int x, int num, int dep) {
		if (dep>20) {--w[x]; return;}
		erase(ch[x][num&1], num>>1, dep+1);
		maintain(x);
	}
	int merge(int a, int b) {
		if (!a) return b;
		if (!b) return a;
		w[a]+=w[b], xorv[a]^=xorv[b];
		ch[a][0]=merge(ch[a][0], ch[b][0]);
		ch[a][1]=merge(ch[a][1], ch[b][1]);
		return a;
	}
	void addall(int x) {
		swap(ch[x][1], ch[x][0]);
		if (ch[x][0]) addall(ch[x][0]);
		maintain(x);
	}
}

signed main() {
	return 0;
}
