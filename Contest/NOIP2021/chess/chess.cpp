#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define pb push_back
int n, m, q;
vector<int,vector<int>> st;

namespace TC1 {
	#define N 5000
	#undef N
}

int T;

signed main() {
	freopen("chess1.in", "r", stdin);
	freopen("chess.out", "w", stdout);
	T=read(); while (T--) {
		n=read(), m=read(), q=read();
		st.clear();
		for (int i=1; i<=n; ++i) {
			for (int j=1; j<=m; ++j) {
				st.push_back(vector<int>(m));
			}
		}
	}
	return 0;
}

// g++ chess.cpp -o 
