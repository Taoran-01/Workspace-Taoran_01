#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for(register int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for(register int i = (a); i >= (b); --i)
#define For_Edge(i, x) for(auto i : edge[x])
#define For_Mul(i, a, b) for(register int i = (a); i <= (b); i += (a))
#define pii pair <int, int>
#define fi first
#define se second
#define eb push_back
#define mp make_pair
#define Size(a) ((int)a.size())
#define All_Vec(a) a.begin(), a.end()
#define nop (op ^ 1)
using namespace std;
inline int read() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	while(!isdigit(c)) f |= (c == '-'), c = getchar();
	while(isdigit(c)) x = (x * 10) + (c ^ 48), c = getchar();
	return f ? -x : x;
}
inline void Checkmin(int &x, int y) { x = x < y ? x : y; }
inline void Checkmax(int &x, int y) { x = x > y ? x : y; }
const int maxn = 1005, maxS = (1 << 12);
int n, m, Answer; int Fa[maxn], Id[maxn];
vector < int > edge[maxn];
vector < pair < pii, int > > Line, Vec[maxn];
namespace LCA {
    int f[maxn][22], Dep[maxn];
    inline void Deal_First(int x, int fa) {
        Dep[x] = Dep[fa] + 1, f[x][0] = Fa[x] = fa;
        For(i, 1, 20) f[x][i] = f[f[x][i - 1]][i - 1];
        For_Edge(y, x) {
            if(y == fa) continue;
            Deal_First(y, x);
        }
    }
    inline int Get_Lca(int x, int y) {
        if(Dep[x] < Dep[y]) swap(x, y);
        Rof(i, 20, 0)
            if(Dep[f[x][i]] >= Dep[y]) x = f[x][i];
        if(x == y) return x;
        Rof(i, 20, 0)
            if(f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
        return f[x][0];
    }
}
int f[maxn][maxS], Son[maxn][15];
inline void Search(int x, int fa) {
    int tot = 0;
    For_Edge(y, x) {
        if(y == Fa[x]) continue;
        Search(y, x);
    }
    For_Edge(y, x) {
        if(y == Fa[x]) continue;
        Id[y] = (1 << tot), Son[x][tot] = y, tot++;
    }
    For(S, 0, (1 << tot) - 1)
        For(i, 0, tot - 1) if(!((S >> i) & 1)) f[x][S] += f[Son[x][i]][0];
    for(auto [i, w] : Vec[x]) {
        auto [u, v] = i; int Cnt = w;
        if(u != x) { Cnt += f[u][0]; while(Fa[u] != x) Cnt += f[Fa[u]][Id[u]], u = Fa[u]; }
        if(v != x) { Cnt += f[v][0]; while(Fa[v] != x) Cnt += f[Fa[v]][Id[v]], v = Fa[v]; }
        int T = Id[u] | Id[v];
        For(S, 0, (1 << tot) - 1)
            if(!(S & T)) f[x][S] = max(f[x][S], f[x][S | T] + Cnt);
    }   
}
signed main() {
    freopen("aurora.in", "r", stdin);
    freopen("aurora.out", "w", stdout);
    n = read(), m = read();
    For(i, 1, n - 1) {
        int u = read(), v = read();
        edge[u].eb(v), edge[v].eb(u);
    }
    For(i, 1, m) {
        int u = read(), v = read(), w = read();
        Line.eb(mp(mp(u, v), w));
    }
    LCA::Deal_First(1, 0);
    for(auto [i, w] : Line) Vec[LCA::Get_Lca(i.fi, i.se)].eb(mp(i, w));
    Search(1, 0);
    printf("%lld\n", f[1][0]);
    return 0;
}
