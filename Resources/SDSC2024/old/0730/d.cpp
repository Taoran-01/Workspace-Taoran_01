#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <bitset>
using namespace std;
typedef long long ll;

// char buf[1<<20], *p1, *p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
int n, m, q, opt, l, r;
char s[N], t[N];
bitset<N> b[64], ans;

int get(char c) {
	if (c>='A'&&c<='Z') return c-'A';
	if (c>='a'&&c<='z') return c-'a'+26;
	if (c>='0'&&c<='9') return c-'0'+52;
	if (c=='_') return 63;
	return -1;
}

signed main() {
	// freopen("d.in", "r", stdin);
	n=read(), q=read();
	scanf("%s", s+1);
	for (int i=1; i<=n; ++i) {
		b[get(s[i])][i]=1;
	}
	while (q--) {
		opt=read(), l=read(), r=read();
		if (opt==1) {
			scanf("%s", t+l), m=strlen(t+l);
			for (int i=l; i<=r; ++i) {
				b[get(s[i])][i]=0;
				s[i]=t[i];
				b[get(s[i])][i]=1;
			}
		}
		if (opt==2) {
			scanf("%s", t+1), m=strlen(t+1);
			ans=b[get(t[1])];
			for (int i=2; i<=m; ++i) {
				--r, ans&=b[get(t[i])]>>i-1;
			}
			printf("%d\n", (ans>>l<<l+N-1-r).count());
		}
	}
	return 0;
}
