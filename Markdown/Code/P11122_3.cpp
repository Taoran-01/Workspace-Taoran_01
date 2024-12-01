#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
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

#define N 16
#define S ((1<<15)+5)
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
#define popcount __builtin_popcount
#define lowbit(x) (x&-x)
int n, m; ll k; bool flag;
int d[N][N];
unordered_map<ll, int> mp;

int q[S];

void output(int x, int y) {
	printf("YES\n%d\n", n+m-popcount(x)-popcount(y));
	for (int i=1; i<=n; ++i) if (!(x&(1<<(i-1)))) printf("1 %d\n", i);
	for (int j=1; j<=m; ++j) if (!(y&(1<<(j-1)))) printf("2 %d\n", j);
}

// #define DEBUG // 
#define TC 88

#ifdef DEBUG
#include <ctime>
int stt=clock();
#endif

signed main() {
	#ifdef DEBUG
	char s[100]=""; sprintf(s, "%02d", TC);
	freopen(s, "r", stdin), freopen(strcat(s, ".o"), "w", stdout);
	#endif

	n=read(), m=read();
	for (int i=0; i<=15; ++i) q[1<<i]=i;
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) d[i][j]=read();
	k=read();
	for (int x=0; x<1<<n; ++x) {
		mp.clear();
		int sl=m>>1, sr=m-sl;
		for (int y=0; y<1<<sl; ++y) {
			ll c=0;
			// for (int i=1; i<=n; ++i) for (int j=1; j<=sl; ++j) {
			// 	if ((x&(1<<(i-1))&&y&(1<<(j-1)))) c+=d[i][j];
			// }
			for (int tx=x; tx; tx-=lowbit(tx)) {
				for (int ty=y; ty; ty-=lowbit(ty)) {
					c+=d[q[lowbit(tx)]+1][q[lowbit(ty)]+1];
				}
			}
			if (!mp.count(c)) mp.insert(mkp(c, y));
		}
		for (int y=0; y<1<<sr; ++y) {
			ll c=0;
			// for (int i=1; i<=n; ++i) for (int j=sl+1; j<=m; ++j) {
			// 	if ((x&(1<<(i-1))&&y&(1<<(j-sl-1)))) c+=d[i][j];
			// }
			for (int tx=x; tx; tx-=lowbit(tx)) {
				for (int ty=y; ty; ty-=lowbit(ty)) {
					c+=d[q[lowbit(tx)]+1][q[lowbit(ty)]+sl+1];
				}
			}
			if (mp.count(k-c)) {output(x, (y<<sl)+mp[k-c]), flag=1; break;}
		}
		if (flag) break;
	}
	if (!flag) puts("NO");

	#ifdef DEBUG
	cerr<<1.0*(clock()-stt)/CLOCKS_PER_SEC<<'\n'; //
	sprintf(s, "check %02d %02d.o %02d.a", TC, TC, TC);
	fclose(stdout), system(s);
	#endif

	return 0;
}
