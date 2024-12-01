#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 15;
int a[maxn][maxn];
long long smaskSum[1 << maxn];
pair<long long, int> dp[1 << maxn][1 << (maxn / 2)];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    long long s;
    cin >> s;
    int half = m / 2;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < (1 << half); ++j) {
            dp[i][j] = { 0, 0 };
        }
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        fill(smaskSum, smaskSum + (1 << half), 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < half; ++j) {
                if ((1 << i) & mask) {
                    smaskSum[1 << j] += a[i][j];
                }
            }
        }
        for (int bit = 0; bit < half; ++bit) {
            for (int mask = 0; mask < (1 << half); ++mask) {
                if ((1 << bit) & mask) {
                    smaskSum[mask] += smaskSum[mask ^ (1 << bit)];
                }
            }
        }
        for (int smask = 0; smask < (1 << half); ++smask) {
            dp[mask][smask] = make_pair(smaskSum[smask], smask);
        }
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        sort(dp[mask], dp[mask] + (1 << half));
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
        fill(smaskSum, smaskSum + (1 << (m - half)), 0);
        for (int i = 0; i < n; ++i) {
            for (int j = half; j < m; ++j) {
                if ((1 << i) & mask) {
                    smaskSum[1 << (j - half)] += a[i][j];
                }
            }
        }
        for (int bit = 0; bit < m - half; ++bit) {
            for (int mask = 0; mask < (1 << (m - half)); ++mask) {
                if ((1 << bit) & mask) {
                    smaskSum[mask] += smaskSum[mask ^ (1 << bit)];
                }
            }
        }
        for (int smask = 0; smask < (1 << (m - half)); ++smask) {
            long long need = s - smaskSum[smask];
            auto pt = lower_bound(dp[mask], dp[mask] + (1 << half), make_pair(need, -1));
            if (pt != dp[mask] + (1 << half) && pt->first == need) {
                cout << "YES\n";
                int msk = (1 << half) * smask + pt->second;
                vector<pair<int, int>> res;
                for (int i = 0; i < n; ++i) {
                    if (!((1 << i) & mask)) {
                        res.push_back({ 1, i + 1 });
                    }
                }
                for (int i = 0; i < m; ++i) {
                    if (!((1 << i) & msk)) {
                        res.push_back({ 2, i + 1 });
                    }
                }
                cout << res.size() << '\n';
                // for (auto [i, j] : res) {
                for (auto x : res) {
                    int i=x.first, j=x.second;
                    cout << i << ' ' << j << '\n';
                }
                return;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    while (t--) {
        solve();
    }
}
