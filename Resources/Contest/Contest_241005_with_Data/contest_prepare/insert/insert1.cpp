#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define int long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 5e6+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

int n, m, A;
int res = 0, Ans = 0, ans = 0;
int a[MAXN];
int b[MAXN], c[MAXN];
int q[MAXN], head = 1, tail = 0;

int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
    return f ? -s : s;
}

signed main()
{
	freopen("ex_insert5.in","r",stdin);
    n = read(), m = read(), A = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i < m; ++i) {
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
    }
    for(int i = m; i <= n; ++i) {
        while(head <= tail && q[head] < i - m + 1) head ++;
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
        b[i - m + 1] = a[q[head]];
    }
    head = 1, tail = 0;
    int p = m - 1;
    for(int i = 1; i < p; ++i) {
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
    }
    for(int i = p; i <= n; ++i) {
        while(head <= tail && q[head] < i - p + 1) head ++;
        while(head <= tail && a[q[tail]] < a[i]) tail --;
        q[++tail] = i;
        c[i - p + 1] = a[q[head]];
    }
    for(int i = 1; i <= n - p + 1; ++i) {
        c[i] = max(c[i], A);
    }
    for(int i = 1; i <= n - m + 1; ++i) ans += b[i];
    // 短区间长度为 m-1，个数为 m
    // 长区间长度为 m，个数为 m - 1
    // 若，插 i, i + 1 之间，所涉短区间为 [i - m + 2, i + 1]，所涉长区间为 [i - m + 2, i] 
    for(int i = 0; i <= n; ++i) {
        res -= b[i], res += c[i + 1];
        if(i - m + 1 >= 1) res += b[i - m + 1] - c[i - m + 1];
        Ans = max(Ans, ans + res);
    }
    printf("%lld\n", Ans);
    return 0;
}
