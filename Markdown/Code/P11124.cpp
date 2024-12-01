#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <unordered_set>
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

#define N 100010
#define NP 80010
#define V 1000010
int n;
int a[N];
int cnt;
int prime[NP];

namespace EularSieve {
	bool vis[V];
	void main() {
		vis[1]=1;
		for (int i=2; i<V; ++i) {
			if (!vis[i]) prime[++cnt]=i;
			for (int j=1; j<=cnt&&i*prime[j]<V; ++j) {
				vis[i*prime[j]]=1;
				if (i%prime[j]==0) break;
			}
		}
	}
}

int fa[(V<<1)+10];
int find(int x) {return (x==fa[x]?x:fa[x]=find(fa[x]));}
void uni(int x, int y) {fa[find(x)]=find(y);}

unordered_set<int> f1, f2;
bool fd[V];

// #include <ctime>
// int stt=clock();
// #define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
// 	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)

signed main() {
	// freopen("39", "r", stdin);
	// freopen(".o", "w", stdout);
	EularSieve::main();// fprintf(stderr, "TOTAL COUNT: %d\n", cnt);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	// sort(a+1, a+n+1);
	for (int i=0; i<V<<1; ++i) fa[i]=i;
	for (int i=1; i<=n; ++i) {
		int x=a[i];
		if (fd[x]) continue; fd[x]=1;
		for (int j=1; j<=cnt&&1LL*x*prime[j]<V; ++j) {
			int y=x*prime[j];
			uni(x+V, y), uni(x, y+V);
		}
	}
	for (int i=1; i<=n; ++i) {
		int f=find(a[i]), fn=find(a[i]+V);
		if (f1.count(f)) f1.insert(f), printf("1 ");
		else if (f2.count(f)) f2.insert(f), printf("2 ");
		else if (f1.count(fn)) f2.insert(f), printf("2 ");
		else if (f2.count(fn)) f1.insert(f), printf("1 ");
		else f1.insert(f), printf("1 ");
	}
	puts("");
	// chktim;
	return 0;
}
