#include <iostream>
#include <string>
#include <vector>

using namespace std;

int d[300][300], t[300][300];

int main() {
	freopen("CF538D_2.in", "r", stdin);
	int N;
	cin >> N;
	char a[N+1][N+1];
	for (int i = 1; i <= N; ++i) cin >> a[i]+1;

	for (int i = 1; i <= 2 * N - 1; ++i)
		for (int j = 1; j <= 2 * N - 1; ++j)
			d[i][j] = 1;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (a[i][j] != 'o') continue; // 2
			for (int x = 1; x <= N; ++x) {
				for (int y = 1; y <= N; ++y) {
					if (a[x][y] == '.') { // 0
						d[x - i + N][y - j + N] = 0;
					}
				}
			}
		}
	}

	// 构建模拟攻击范围
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (a[i][j] != 'o') continue; // 2
			for (int x = 1; x <= 2 * N - 1; ++x) {
				for (int y = 1; y <= 2 * N - 1; ++y) {
					int xx = i + x - N, yy = j + y - N;
					if (xx < 1 || yy < 1 || xx > N || yy > N || !d[x][y]) continue;
					t[xx][yy] = 1;
				}
			}
		}
	}

	// 验证模拟结果
	bool ok = true;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (a[i][j] == 'o') continue; // 2
			ok &= (a[i][j] == 'x') == (t[i][j] == 1); // 1
		}
	}

	// 输出结果
	d[N][N] = 2; // 中心位置棋子标记为2
	if (ok) {
		cout << "YES\n";
		for (int i = 1; i <= 2 * N - 1; ++i) {
			for (int j = 1; j <= 2 * N - 1; ++j)
				cout << ".xo"[d[i][j]];
			cout << '\n';
		}
	} else {
		cout << "NO\n";
	}
	return 0;
}
