#include <iostream>
#include <string>
#include <vector>

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

int d[300][300], t[300][300];

int main() {
	freopen("CF538D_3.in", "r", stdin);
	freopen("CF538D_3.ans", "w", stdout);
	int N;
	cin >> N;
	vector<string> f(N);
	forn(i, N) cin >> f[i];
	forn(i, 2 * N - 1) forn(j, 2 * N - 1) d[i][j] = 1;
	forn(i, N) forn(j, N) {
		if (f[i][j] != 'o') continue;
		forn(x, N) forn(y, N) if (f[x][y] == '.') d[x - i + N - 1][y - j + N - 1] = 0;
	}
	forn(i, N) forn(j, N) {
		if (f[i][j] != 'o') continue;
		forn(x, 2 * N - 1) forn(y, 2 * N - 1) {
			int xx = i + x - (N - 1), yy = j + y - (N - 1);
			if (min(xx, yy) < 0 || max(xx, yy) >= N || !d[x][y]) continue;
			t[xx][yy] = 1;
		}
	}

	bool ok = true;
	forn(i, N) forn(j, N) {
		if (f[i][j] == 'o') continue;
		ok &= (f[i][j] == 'x') == (t[i][j] == 1);
	}

	d[N - 1][N - 1] = 2;
	if (ok) {
		cout << "YES\n";
		forn(i, 2 * N - 1) {
			forn(j, 2 * N - 1) cout << ".xo"[d[i][j]];
			cout << '\n';
		}
	} else cout << "NO\n";
	return 0;
}
