#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

/*
数据结构，支持大规模类字符串数据插入与查找。
1. 给定范围 [0,K) 的串 s，插入串 s；
2. 给定范围 [0,K) 的串 t，查询当前有多少串 s 以串 t 作为前缀。
*/

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

int gen(char ch) {
	if (ch>='A'&&ch<='Z') return ch-'A';
	if (ch>='a'&&ch<='z') return ch-'a'+26;
	if (ch>='0'&&ch<='9') return ch-'0'+52;
	return -1; //
}

struct trie {
	#define N 3000010
	#define K 62
	int t[N][K], cnt[N], tot;
	void clr() {
		for (int i=0; i<tot; ++i) for (int j=0; j<K; ++j) t[i][j]=0;
		for (int i=0; i<=tot; ++i) cnt[i]=0; tot=0;
	}
	void ins(int a[], int len) { // [1,len]
		int p=0; ++cnt[0];
		for (int i=1; i<=len; ++i) {
			if (!t[p][a[i]]) t[p][a[i]]=++tot;
			p=t[p][a[i]], ++cnt[p];
		}
	}
	int qry(int a[], int len) { // [1,len]
		int p=0;
		for (int i=1; i<=len; ++i) {
			if (!t[p][a[i]]) return 0;
			p=t[p][a[i]];
		}
		return cnt[p];
	}
	#undef N
	#undef K
} t;

#define N 3000010
int T, n, q;
char s[N]; int a[N], len;

signed main() {
	// freopen("a.in", "r", stdin);
	// freopen("a.out", "w", stdout);
	T=read();
	while (T--) {
		t.clr();
		n=read(), q=read();
		while (n--) {
			scanf("%s", s+1), len=strlen(s+1);
			for (int i=1; i<=len; ++i) a[i]=gen(s[i]);
			t.ins(a, len);
		}
		while (q--) {
			scanf("%s", s+1), len=strlen(s+1);
			for (int i=1; i<=len; ++i) a[i]=gen(s[i]);
			printf("%d\n", t.qry(a, len));
		}
	}
	return 0;
}
