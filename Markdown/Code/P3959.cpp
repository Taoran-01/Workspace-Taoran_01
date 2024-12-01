#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

// #define DEBUG
// #define DEBUG_OUTPUT
#define TC "treasure20"

#ifdef DEBUG
#include <ctime>
int stt=clock();
#define chktim fprintf(stderr, "Line #%d: %.2fs\n", \
	__LINE__, 1.0*(clock()-stt)/CLOCKS_PER_SEC)
#endif

#define N 15
#define M 1010
#define S 4100
#define INF 0x3f3f3f3f
#define popcount __builtin_popcount
#define ctz __builtin_ctz
#define lowbit(x) (x&-x)
typedef pair<int,int> pii;
#define fi first
#define se second
#define mkp make_pair
int n, m;

#define v e[i].to
#define w e[i].val
int head[N], tte;
struct edge {int to, nxt, val;} e[M<<1];
void add_edge(int x, int y, int z) {e[++tte]={y, head[x], z}, head[x]=tte;}

int s[S], tot, U;
vector<int> g[S];
int f[S][N];
int fd[S], tmp[N];
int ans;

bool chk(int x, vector<int> &g) {
	assert(x!=0);
	int rem=x; queue<int> q;
	q.push(ctz(rem)+1); rem^=1<<ctz(rem);
	while (!q.empty()) {
		int u=q.front(); q.pop();
		for (int i=head[u]; i; i=e[i].nxt) {
			if (rem&(1<<(v-1))) q.push(v), rem^=1<<(v-1);
			if (!(x&(1<<(v-1)))) g.push_back(i);
		}
	}
	return !rem;
}

void minimizeG(vector<int> &g) {
	memset(tmp, 0x3f, sizeof(tmp));
	for (int i:g) if (tmp[v]==INF||e[tmp[v]].val>w) tmp[v]=i;
	g.clear(); for (int i=1; i<=n; ++i) if (tmp[i]!=INF) g.push_back(tmp[i]);
}

void init() {
	memset(f, 0x3f, sizeof(f));
	for (int i=1; i<(1<<n); ++i) {
		vector<int> gt; if (!chk(i, gt)) continue;
		minimizeG(gt), s[++tot]=i, g[tot]=gt, fd[s[tot]]=tot;
		// s[++tot]=i, g[tot]=gt, fd[s[tot]]=tot;
		if (popcount(s[tot])==1) f[tot][0]=0;
		if (popcount(s[tot])==n) U=tot;
	}
	#ifdef DEBUG_OUTPUT
	fprintf(stderr, "Total Count: %d\n", tot);
	for (int idx=1; idx<=tot; ++idx) {
		for (int u=n; u; --u) fprintf(stderr, "%d", bool(s[idx]&(1<<(u-1))));
		fprintf(stderr, ", |");
		for (int i:g[idx]) fprintf(stderr, "%d %d|", v, w);
		fprintf(stderr, "\n");
	}
	#endif
}

bool ext(int idx, int cur) {
	int &as=s[idx], res=s[cur]; memset(tmp, 0x3f, sizeof(tmp));
	for (int i:g[cur]) {res|=1<<(v-1);if (as&(1<<(v-1))) tmp[v]=min(tmp[v], w);}
	return (as&res)==as;
}

signed main() {
	#ifdef DEBUG
	char s1_[100]=""; sprintf(s1_, "%s.in", TC);
	freopen(s1_, "r", stdin);
	freopen("a.out", "w", stdout);
	#endif
	n=read(), m=read(), ans=INF;
	if (n==1) return puts("0"), 0; // IMPORTANT
	for (int i=1; i<=m; ++i) {
		int x=read(), y=read(), z=read();
		add_edge(x, y, z), add_edge(y, x, z);
	}
	init();
	for (int i=1; i<=n; ++i) {
		for (int idx=1; idx<=tot; ++idx) {
			int &as=s[idx];
			for (int cs=(as-1)&as; cs; cs=(cs-1)&as) {
				if (!fd[cs]) continue; int cur=fd[cs];
				if (!ext(idx, cur)) continue;
				int sum=0;
				for (int cls=as^cs; cls; cls-=lowbit(cls)) {
					int u=ctz(cls)+1; sum+=tmp[u];
					if (1LL*sum*i+f[cur][i-1]>=f[idx][i]) break;
				}
				f[idx][i]=min(1LL*f[idx][i], 1LL*sum*i+f[cur][i-1]);
			}
		}
		ans=min(ans, f[U][i]);
	}
	printf("%d\n", ans);
	#ifdef DEBUG
	fclose(stdout);
	fprintf(stderr, "%d\n", ans);
	chktim;
	char s2_[100]=""; sprintf(s2_, "fc a.out %s.ans >nul", TC);
	fprintf(stderr, "CHECK: %d\n\n", system(s2_));
	#endif
	#ifdef DEBUG_OUTPUT
	for (int idx=1; idx<=tot; ++idx) {
		for (int u=n; u; --u) fprintf(stderr, "%d", bool(s[idx]&(1<<(u-1))));
		fprintf(stderr, "%c", idx==tot?'\n':' ');
	}
	char cs1_[100]=""; sprintf(cs1_, "%%%ds ", n);
	char cs2_[100]=""; sprintf(cs2_, "%%%dd ", n);
	for (int i=0; i<=n; ++i) {
		for (int idx=1; idx<=tot; ++idx) {
			if (f[idx][i]==INF) fprintf(stderr, cs1_, "inf");
			else fprintf(stderr, cs2_, f[idx][i]);
		}
		fprintf(stderr, "\n");
	}
	#endif
	return 0;
}
