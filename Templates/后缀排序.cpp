#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

/*
字符串的所有非空后缀按字典序从小到大排序，按顺序输出后缀的第一个字符在原串中的位置（1到n）。
*/

#define N 1000010
int n, m;
int rk[N], y[N], c[N], sa[N];
char s[N];

signed main() {
	scanf("%s", s+1), n=strlen(s+1), m=127;
	for (int i=1; i<=n; ++i) rk[i]=s[i], ++c[rk[i]];
	for (int i=2; i<=m; ++i) c[i]+=c[i-1];
	for (int i=n; i>=1; i--) sa[c[rk[i]]--]=i;
	for (int k=1, d=0; k<=n&&d!=n; k<<=1, m=d, d=0) {
		memset(c, 0, sizeof(c));
		for (int i=n-k+1; i<=n; ++i) y[++d]=i;
		for (int i=1; i<=n; ++i) if (sa[i]>k) y[++d]=sa[i]-k;
		for (int i=1; i<=n; ++i) ++c[rk[i]];
		for (int i=2; i<=m; ++i) c[i]+=c[i-1];
		for (int i=n; i>=1; --i) sa[c[rk[y[i]]]--]=y[i], y[i]=0;
		swap(rk, y), d=1, rk[sa[1]]=1;
		for (int i=2; i<=n; ++i) {
			if (y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k]) ++d;
			rk[sa[i]]=d;
		}
	}
	for (int i=1; i<=n; ++i) printf("%d ", sa[i]);
	return 0;
}
