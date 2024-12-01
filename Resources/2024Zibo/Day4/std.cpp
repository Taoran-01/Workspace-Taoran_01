#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

void D(int n, int k, int *p1, int *p2)
{
    if (!n) return p1[0] = p2[0] = 0, void();
    if (n == 1) return p1[0] = p2[1] = 0, p1[1] = p2[0] = 1, void();

    int mid = 1 << (n - 1);
    if (k < mid) D(n - 1, k, p1, p1 + mid);
    else D(n - 1, k - mid, p1 + mid, p1);
    for (int i = 0; i < (1 << n); i++) p2[i] = p1[(1 << n) - 1 - i];
    for (int i = mid; i < (1 << n); i++) p1[i] += mid;
    for (int i = 0; i < mid; i++) p2[i] += mid;
}

void C(int x, int *p1, int *p2)
{
    if (!x) return;
    if (x == 1) return p1[0] = p2[0] = 0, void();
    if (x == 2) return p1[0] = p2[1] = 0, p1[1] = p2[0] = 1, void();

    int l = 1, n = 0, k;
    while ((l << 1) <= x) l <<= 1, n++; k = x - l;
    C(k, p1, p1 + l);
    for (int i = 0; i < k; i++) p1[i] += l;

    D(n, k, p2 + l, p2);
    for (int i = l; i < x; i++) p2[i] += l;
    for (int i = x; i < (l << 1); i++) p1[i - l] = p2[i];
}

int p1[maxn], p2[maxn], p[maxn];
bool vis[maxn];

void work()
{
    int n; cin >> n;
    for (int i = 0; i < n; i++) vis[i] = 0;
    if (n == 1) return cout << "Yes\n0\n0\n", void();
    if (n & 3) return cout << "No\n", void();
    C(n / 4, p1, p2);
    for (int i = 0; i < n / 4; i++)
    {
        int a = (i << 2), b = a | 1, c = a | 2, d = b | 2;
        p[a] = p1[i] << 2, p[b] = (p1[i] << 2) | 2;
        if (vis[p[a] ^ a] || vis[p[b] ^ b]) p[a] ^= 2, p[b] ^= 2;
        vis[p[a] ^ a] = vis[p[b] ^ b] = 1;

        p[c] = (p2[i] << 2) | 3, p[d] = (p2[i] << 2) | 1;
        if (vis[p[c] ^ c] || vis[p[d] ^ d]) p[c] ^= 2, p[d] ^= 2;
        vis[p[c] ^ c] = vis[p[d] ^ d] = 1;
    }

    cout << "Yes\n";
    for (int i = 0; i < n; i++) cout << i << " "; cout << "\n";
    for (int i = 0; i < n; i++) cout << p[i] << " "; cout << "\n";
	for (int i = 0; i < n; i++) cout << (i ^ p[i]) << " "; cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    work();
    return 0;
}