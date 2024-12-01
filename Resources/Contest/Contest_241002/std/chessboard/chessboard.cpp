#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int Mod = 998244353;
#define add(x, y) ((x) + (y) < Mod ? (x) + (y) : (x) + (y) - Mod)
int n, m;
int fac[N], inv[N];
int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1ll * ans * a % Mod;
		a = 1ll * a * a % Mod;
		b >>= 1;
	}
	return ans;
}
int C(int n, int m) {
	return 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod;
}
bool cover_1[N], cover_2[N];
int dp[N][N * 2], ans = 0;
int x[N], y[N];
void dfs(int step, bool flag_1, bool flag_2, int coef, int size_) {
	if (step == m + 1){
		int sum_1 = fac[size_], sum_2 = 0, sum_3 = 0, sum_4 = 0;
		if (!flag_1){
			int cnt = 0;
			int coef_ = 1;
			for (int i = 0; i < n; ++i)
				if (!cover_1[i] && !cover_2[i]) cnt++;
			for (int i = 0; i <= cnt; ++i) {
				sum_2 = (sum_2 + 1ll * coef_ * fac[size_ - i] % Mod * C(cnt, i)) % Mod;
				coef_ = Mod - coef_;
			}
		}
		if (!flag_2){
			int cnt = 0;
			int coef_ = 1;
			for (int i = 0; i < n; ++i)
				if (!cover_1[i] && !cover_2[n - i - 1]) cnt++;
			for (int i = 0; i <= cnt; ++i) {
				sum_3 = (sum_3 + 1ll * coef_ * fac[size_ - i] % Mod * C(cnt, i)) % Mod;
				coef_ = Mod - coef_;
			}
		}
		if (!flag_1 && !flag_2){
			memset (dp, 0, sizeof(dp));
			dp[0][0] = 1;
			int hoop = (n + 1) / 2;
			for (int i = 0; i < hoop; ++i) {
				for (int j = 0; j <= 2 * (i + 1); ++j) {
					dp[i + 1][j] = dp[i][j]; // case 0
					if ((n & 1) && (i == hoop - 1)) { // case 1
						if (!cover_1[i] && !cover_2[i] && j)
							dp[i + 1][j] = add(dp[i + 1][j], dp[i][j - 1]);
					}else {
						if (j) { // case 1
							int comb = 0;
							if (!cover_1[i] && !cover_2[i]) ++comb;
							if (!cover_1[i] && !cover_2[n - i - 1]) ++comb;
							if (!cover_1[n - i - 1] && !cover_2[i]) ++comb;
							if (!cover_1[n - i - 1] && !cover_2[n - i - 1]) ++comb;
							dp[i + 1][j] = (dp[i + 1][j] + 1ll * comb * dp[i][j - 1]) % Mod;
						}
						if (j > 1){ // case 2
							int comb = 0;
							if (!cover_1[i] && !cover_2[i] && !cover_1[n - i - 1] && !cover_2[n - i - 1]) comb += 2;
							dp[i + 1][j] = (dp[i + 1][j] + 1ll * comb * dp[i][j - 2]) % Mod;
						}
					}
				}
			}
			int coef_ = 1;
			for (int i = 0; i <= n; ++i){
				sum_4 = (sum_4 + 1ll * coef_ * fac[size_ - i] % Mod * dp[hoop][i]) % Mod;
				coef_ = Mod - coef_;
			}
		}
		ans = (ans + 1ll * coef * (((sum_1 - sum_2 - sum_3 + sum_4) % Mod + Mod) % Mod)) % Mod;
		return;
	}
	dfs(step + 1, flag_1, flag_2, coef, size_);
	if (!cover_1[x[step]] && !cover_2[y[step]]) {
		cover_1[x[step]] = true, cover_2[y[step]] = true;
		if (x[step] == y[step]) flag_1 = true;
		if (x[step] + y[step] == n - 1) flag_2 = true;
		dfs(step + 1, flag_1, flag_2, Mod - coef, size_ - 1);
		cover_1[x[step]] = false, cover_2[y[step]] = false;
	}
}
int main(){
	freopen ("chessboard.in", "r", stdin);
	freopen ("chessboard.out", "w", stdout);
	fac[0] = 1;
	for (int i = 1; i <= 100; ++i) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[100] = qpow(fac[100], Mod - 2);
	for (int i = 99; i >= 0; --i) inv[i] = 1ll * inv[i + 1] * (i + 1) % Mod;
	int T;scanf ("%d", &T);
	while (T--) {
		scanf ("%d%d",&n, &m);
		ans = 0;
		for (int i = 1; i <= m; ++i) {
			scanf ("%d%d", &x[i], &y[i]);
			--x[i];
			--y[i];
		}
		dfs(1, false, false, 1, n);
		printf ("%d\n",ans);
	}
	return 0;
} 
