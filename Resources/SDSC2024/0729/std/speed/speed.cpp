#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define ROF(i, a, b) for (int i = a; i >= b; --i)

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

const int N = 204, mod = 998244353;

int T, n, m, k, a[N], mx;
int dp[N][N * N], sz, S;
int Mod(int x) { return x >= mod ? x - mod : x; }
void add(int v) {
    ROF(i, sz + 1, 1) {
        FOR(s, v, S + v) { dp[i][s] = Mod(dp[i][s] + dp[i - 1][s - v]); }
    }
    ++sz, S += v;
}
void del(int v) {
    FOR(i, 1, sz) {
        FOR(s, v, S) { dp[i][s] = Mod(dp[i][s] - dp[i - 1][s - v] + mod); }
    }
    --sz, S -= v;
}
void clear() {
    memset(dp, 0, sizeof(dp));
    sz = S = 0, dp[0][0] = 1;
}
int main() {
    freopen("speed.in", "r", stdin);
    freopen("speed.out", "w", stdout);
    n = read(), m = read(), k = read();
    mx = sz = S = 0;
    ll res = 0;
    FOR(i, 1, n) {
        a[i] = read();
        mx = max(mx, a[i]);
    }
    sort(a + 1, a + n + 1);
    clear();
    int now = 1, sz1 = 0, x = 0, lim = 0;
    FOR(r, 1, n) {  // |S| >= k
        x = a[r];
        while (now < r && a[now] + m < x) del(a[now]), ++now;
        if (n - now < k) break;
        FOR(i, 0, sz) {
            sz1 = (n - r) + i;
            if (sz1 < k) continue;
            FOR(j, max(0, x * i - m * k), S) { res = Mod(res + dp[i][j]); }
        }
        add(a[r]);
    }
    clear();
    now = n;
    ROF(l, n, 1) {  // |S| < k
        x = a[l] + m;
        while (now > l && a[now] > x) del(a[now]), --now;
        if (n - now + 1 >= k) break;
        FOR(i, 0, sz) {
            sz1 = (n - now) + i + 1;
            if (sz1 >= k) continue;
            lim = max(0, m * (k - sz1 - l + 1) - x * (sz - i) + S);
            FOR(j, lim, S) { res = Mod(res + dp[i][j]); }
        }
        add(a[l]);
    }
    printf("%lld\n", (res + 1) % mod);
    return 0;
}