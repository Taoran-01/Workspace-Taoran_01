#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ROF(i, a, b) for (int i = a; i >= b; --i)
#define NEXT(i, r, v) for (int i = h[r], v; v = e[i].v, i; i = e[i].u)

inline int Max(const int &a, const int &b) { return a > b ? a : b; }
inline int Min(const int &a, const int &b) { return a > b ? b : a; }

inline int read() {
    int f = 1, x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

using namespace std;
const int N = 1e5 + 7;
int T, n, q, a[N];
int ch[N * 32][2], rt[N], sz[N * 32], cnt;
void insert(int p, int q, int x) {
    int f;
    ROF(i, 30, 0) {
        f = (x >> i) & 1;
        ch[q][!f] = ch[p][!f];
        ch[q][f] = ++cnt;
        sz[ch[q][f]] = sz[ch[p][f]] + 1;
        q = ch[q][f], p = ch[p][f];
    }
}
vector<pair<int, int>> p, tp;
int qry() {
    int res = 0;
    ROF(i, 30, 0) {
        tp.clear();
        int t = 0;
        for (auto &[a, b] : p) {
            t += sz[ch[a][0]] - sz[ch[b][0]];
        }
        if (t >= 2) {
            for (auto &[a, b] : p) {
                if (sz[ch[a][0]] - sz[ch[b][0]] > 0) tp.push_back({ch[a][0], ch[b][0]});
            }
        } else {
            res |= 1 << i;
            for (auto &[a, b] : p) {
                if (sz[ch[a][0]] - sz[ch[b][0]] > 0) tp.push_back({ch[a][0], ch[b][0]});
                if (sz[ch[a][1]] - sz[ch[b][1]] > 0) tp.push_back({ch[a][1], ch[b][1]});
            }
        }
        swap(p, tp);
    }
    return res;
}
void clear() {
    FOR(i, 1, cnt) ch[i][0] = ch[i][1] = sz[i] = 0;
    cnt = 0;
}
void solve() {
    n = read();
    FOR(i, 1, n) {
        a[i] = read();
        rt[i] = ++cnt;
        insert(rt[i - 1], rt[i], a[i]);
    }
    q = read();
    FOR(i, 1, q) {
        int l = read(), r = read();
        p.clear();
        p.push_back({rt[r], rt[l - 1]});
        printf("%d\n", qry());
    }
    clear();
}
int main() {
    freopen("electric.in", "r", stdin);
    freopen("electric.out", "w", stdout);
    T = 1;
    FOR(i, 1, T) { solve(); }
    return 0;
}