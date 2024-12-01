#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ROF(i, a, b) for (int i = a; i >= b; --i)

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

const int N = 5e5 + 7;
const int mod = 998244353;
int T;
int n, a[N], b[N];
int c[N], d[N], p[N];
ll res, s;
int main() {
    freopen("shark.in", "r", stdin);
    freopen("shark.out", "w", stdout);
    n = read(), T = read();
    FOR(i, 1, n) a[i] = c[i] = read();
    FOR(i, 1, n) b[i] = d[i] = read();
    sort(c + 1, c + n + 1), sort(d + 1, d + n + 1);
    FOR(i, 1, n) res = (res + 1ll * (c[i] - d[i]) * (c[i] - d[i])) % mod;
    if (T == 0) {
        printf("%lld\n", res);
        return 0;
    }
    FOR(i, 1, n) {
        a[i] = lower_bound(c + 1, c + n + 1, a[i]) - c;
        b[i] = lower_bound(d + 1, d + n + 1, b[i]) - d;
        p[a[i]] = i;
    }
    FOR(i, 1, n) {
        if (a[i] != b[i]) {
            ++s;
            p[a[i]] = p[b[i]];
            swap(a[i], a[p[b[i]]]);
        }
    }
    printf("%lld %lld\n", res, s);
    return 0;
}