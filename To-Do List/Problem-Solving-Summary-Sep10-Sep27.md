<!-- 做题总结 24-09-10 至 24-09-XX -->

---
### 并不简单的简单题
#### T1
[洛谷P1630](https://www.luogu.com.cn/problem/P1630) 求和

给定两个整数 $a$ 和 $b$。要求计算从 $1^b$ 到 $a^b$ 的和，然后取模 $10^4$，输出余数。

模数只有 $10^4$，考虑针对模数下手。  
根据 $a^b\equiv(a\operatorname{mod}10^4)^b\ (\operatorname{mod}\ 10^4)$，只需要求出 $(x\operatorname{mod}10^4)^b\operatorname{mod}10^4$ 的所有值即可，其中 $x\in[0,10^4)$。

记上面的值为 $d_x$，则解为 $(\sum\limits_{i=0}^ad_{i\operatorname{mod}10^4})\operatorname{mod}10^4$。  
当 $a<10^4$ 时，正常求解。  
当 $a>10^4$ 时，必定重复求解 $\sum\limits_{i=0}^{10^4-1}d_i$，并且求解次数是 $\lfloor\frac a{10^4}\rfloor$。

记 $s_x=\sum\limits_{i=0}^xd_i$，则答案为 $(\lfloor\frac a{10^4}\rfloor s_n+s_{a\operatorname{mod}10^4})\operatorname{mod}10^4$。  
时间复杂度 $O(m\log b)$，其中 $m=10^4$。

[AC](https://www.luogu.com.cn/record/176728849) 644.00KB 697ms
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 10010
#define mod 10000LL
ll T, a, b;
ll s[N];

ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {if (b&1) res=res*a%mod; a=a*a%mod, b>>=1;}
	return res;
}

signed main() {
	// freopen("a.in", "r", stdin);
	T=read(); while (T--) {
		a=read(), b=read();
		for (int i=1; i<N; ++i) s[i]=(s[i-1]+qpow(i, b))%mod;
		printf("%lld\n", (a/mod*s[mod]+s[a%mod])%mod);
	}
	return 0;
}

```

#### T2
[洛谷P3740](https://www.luogu.com.cn/problem/P3740) [HAOI2014] 贴海报

给定一个长度为 $N$ 的墙和 $M$ 张海报，每张海报覆盖墙上从第 $A_i$ 到第 $B_i$ 个位置。后贴的海报可以覆盖前面的海报。你需要计算在所有海报张贴完成后，墙上仍可见的海报数量。

一个十分简单的做法：从上向下覆盖。即，将修改倒序处理。  
维护一个 $O(V)$ 的 0-1 序列，被覆盖设为 $1$。由于覆盖操作倒序处理，新的在旧的前面处理；如果旧的还可以覆盖额外的 $0$，说明从外面它看可以被看到，答案累加 $1$。

[AC](https://www.luogu.com.cn/record/176742963) 2.85MB 48ms  
我不知道为什么我的离散化假了。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N0 10000010
#define M0 1010
// #define N (M0<<2)
#define N N0
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
ll m, n, ans;
pii d[N];
// ll t[N], nt;

struct seg {
	#define ls (p<<1)
	#define rs (p<<1|1)
	bool tag[N<<2];
	void push_up(ll p) {tag[p]=tag[ls]&&tag[rs];}
	bool modify(ll nl, ll nr, ll l, ll r, ll p) {
		if (tag[p]) return 0;
		if (nl<=l&&r<=nr) return tag[p]=1, 1;
		ll mid=l+r>>1; bool res=0;
		if (nl<=mid) res|=modify(nl, nr, l, mid, ls);
		if (nr>mid) res|=modify(nl, nr, mid+1, r, rs);
		push_up(p); return res;
	}
	// bool modify(ll l, ll r) {return modify(l, r, 1, n<<1, 1);}
	bool modify(ll l, ll r) {return modify(l, r, 1, m, 1);}
} tr;

signed main() {
	// freopen("a.in", "r", stdin);
	m=read(), n=read();
	for (int i=1; i<=n; ++i) {
		d[i].fi=read(), d[i].se=read();
		// t[++nt]=d[i].fi, t[++nt]=d[i].se;
	}
	// sort(t+1, t+nt+1), nt=unique(t+1, t+nt+1)-t-1;
	// for (int i=1; i<=n; ++i) {
	// 	d[i].fi=lower_bound(t+1, t+nt+1, d[i].fi)-t;
	// 	d[i].se=lower_bound(t+1, t+nt+1, d[i].se)-t;
	// }
	for (int i=n; i>=1; --i) {
		ans+=tr.modify(d[i].fi, d[i].se);
	}
	printf("%lld\n", ans);
	return 0;
}

```

#### T3
[洛谷P5682](https://www.luogu.com.cn/problem/P5682) [CSP-J2019 江西] 次大值

给定 $n$ 个正整数 $a_1,a_2,\dots,a_n$。计算所有 $a_i\operatorname{mod} a_j$ 的值并去重，其中 $1\le i,j\le n\land i\neq j$。找到去重后结果中的严格次大值。如果去重后的结果不足两个唯一值，输出 $-1$。

关注性质 $a\operatorname{mod}b<b$。  
将 $a$ 数组去重后从小到大排序，则 $a_n$、$a_{n-1}$、$a_{n-2}$ 分别为第一、二、三大的值。

考虑最大值：$a_{n-1}$。简证：  
$\forall i,j\in[1,n]$，$a_i\operatorname{mod}a_j<n$，所以 $a_i\operatorname{mod}a_j<a_i\operatorname{mod}a_n$，故最大值的模数为 $a_n$。  
$\forall i\in[1,n)$，$a_i<a_n$，$a_i\operatorname{mod}a_n=a_i$。  
$\therefore\forall i,j\in[1,n)$，$a_i<a_j\Leftrightarrow a_i\operatorname{mod}a_n<a_j\operatorname{mod}a_n$。  
又因为答案中 $i\neq j$，根据上面的性质，最大值为 $a_{n-1}\operatorname{mod}a_n=a_{n-1}$。

次大值一定严格小于最大值 $a_{n-1}$，所以最大值可能为以下两种情况：
1. 一个比 $a_{n-1}$ 大的数对 $a_{n-1}$ 取模；
2. 一个比 $a_{n-1}$ 小的数对 $a_{n-1}$ 取模，是它本身。

对于情况一，只有 $a_n>a_{n-1}$，该情况下的答案为 $a_n\operatorname{mod}a_{n-1}$。  
对于情况二，变成 $i,j\in[1,n-1]\land i\neq j$ 的子问题，该情况下的答案为 $a_{n-2}$。

故答案为 $\max\{a_n\operatorname{mod}a_{n-1},\ a_{n-2}\}$。

[AC](https://www.luogu.com.cn/record/177524755) 2.20MB 81ms
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 300010
int n;
int a[N];

signed main() {
	// freopen("a1.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	sort(a+1, a+n+1), n=unique(a+1, a+n+1)-(a+1);
	if (n<=1) return puts("-1"), 0;
	printf("%d\n", max(a[n-2], a[n]%a[n-1]));
	return 0;
}

```

#### T4
[AT_kupc2021_c](https://atcoder.jp/contests/kupc2021/tasks/kupc2021_c?lang=en) Gacha | [vjudge](https://vjudge.net/problem/AtCoder-kupc2021_c)

给定两个长度为 $N$ 的严格递增整数序列 $A_1, A_2, \dots, A_N$ 和 $B_1, B_2, \dots, B_N$，表示 $N$ 个位置上分别有 $N$ 台扭蛋机和 $N$ 枚硬币。你起始在位置 $0$，可以自由移动并需要在每个扭蛋机位置消耗一枚硬币来启动扭蛋机。计算移动距离的最小值。

贪心。将游戏机和硬币同一处理。  
考虑将位置分为两份：第一份从 $a_1$ 到 $a_x$，全部一次性走完，不留空缺；第二份从 $a_{x+1}$ 到 $a_n$，先走到终点 $a_n$，再返回到 $a_{x+1}$。

可以证明这样是最优的。

[AC](https://atcoder.jp/contests/kupc2021/submissions/57878714) 7.78MB 22ms  
场上死因：没开 `long long`。挂了 $50\text{pts}$，$\text{rk}51\rightarrow\text{rk}70$。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

#define int ll

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 100010
#define INF 0x7f7f7f7f
int n, ans;
struct node {int dis, val;} a[N<<1];
bool operator<(node a, node b) {return a.dis==b.dis?a.val<b.val:a.dis<b.dis;}

int cur, cnt; // cur ans | coin cnt

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), ans=INF;
	for (int i=1; i<=n; ++i) a[i].dis=read(), a[i].val=-1;
	for (int i=n+1; i<=n+n; ++i) a[i].dis=read(), a[i].val=1;
	n<<=1, sort(a+1, a+n+1);
	for (int i=1; i<=n; ++i) { // 枚举转折点
		cur+=a[i].dis-a[i-1].dis;
		if (cnt<0) cur+=(a[i].dis-a[i-1].dis)*2;
		cnt+=a[i].val;
		ans=min(ans, cur+(a[n].dis-a[i].dis)*2);
	}
	printf("%lld\n", ans);
	return 0;
}

```

---
### 数据结构
#### T1
[AT_joisc2014_b](https://atcoder.jp/contests/joisc2014/tasks/joisc2014_b) たのしい家庭菜園 | [洛谷](https://www.luogu.com.cn/problem/AT_joisc2014_b)

给定 $n$ 株草，种在编号为 $1$ 到 $n$ 的 $n$ 段草地上，每段草的高度为 $h_i$。若某株草两侧的草都比它高，则该株草会枯萎。为了避免草枯萎，需满足以下两个条件至少一个：

1. 对于任意 $1\le j\le i-1$，有 $h_j\le h_i$。
2. 对于任意 $i+1\le k\le n$，有 $h_k\le h_i$。

考虑最小的值。若要维护草地非严格单峰，每次需要选出最小的值移到两侧。  
显然，将最小值移动到最近的那一侧会是最优解。正确性容易证明。  
把最小值移到两侧之后，新的序列再次构成子问题。

模拟的时间复杂度不足以支持解决这道题。我们令距离 $x$ 更近的边界为“目标边界”。  
注意到每个元素在跳之前，它到目标边界的这段范围中，比它小的都已经“跳”走了。所以这个元素的交换次数 (即对答案的贡献) 为这段范围内比它大的数的个数。  
这个个数可以使用树状数组维护。

再考虑相同元素的情况。优先处理更靠外的元素，在代码中不需要额外考虑。具体证明方式可以看[这篇题解](https://www.luogu.com.cn/article/citgpgh9)。

枚举中间分界点是错误的，考虑以下样例：
```
3 4 5 6 7 1 8 9
```
枚举中间点时，最优解是 $9$ 位于最右侧，此时会将 $1$ 移到最左侧。  
正确答案是将 $1$ 移到右侧，这样交换次数最小。

暴力枚举中间点骗分 [WA](https://loj.ac/s/2160391) 30pts 688KB 38ms  
正解 [AC](https://atcoder.jp/contests/joisc2014/submissions/57908704) 9.13MB 59ms
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define N 300010
int n; ll ans;
int a[N], tmp[N], lt;

template <typename T> struct BIT {
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void modify(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T query(int x) {return g(x);} T query(int l, int r) {return g(r)-g(l-1);}
}; BIT<int> t1, t2;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read(), tmp[i]=a[i];
	sort(tmp+1, tmp+n+1), lt=unique(tmp+1, tmp+n+1)-(tmp+1);
	for (int i=1; i<=n; ++i) a[i]=lower_bound(tmp+1, tmp+lt+1, a[i])-tmp;
	for (int i=1; i<=n; ++i) t1.modify(a[i], 1);
	for (int i=1; i<=n; ++i) {
		t1.modify(a[i], -1), t2.modify(a[i], 1);
		ans+=min(n-i-t1.query(a[i]), i-t2.query(a[i]));
	}
	printf("%lld\n", ans);
	return 0;
}

```

---
### 动态规划
#### T1
[洛谷P1026](https://www.luogu.com.cn/problem/P1026) [NOIP2001 提高组] 统计单词个数

给定一个字母串，要求将其分为 $k$ 份，并统计每份中包含的单词总数最大。单词来自一个不超过 $6$ 个单词的字典，且单词可以重叠使用，但首字母不能重复使用。

#### T2
[洛谷P2679](https://www.luogu.com.cn/problem/P2679) [NOIP2015 提高组] 子串

有两个仅包含小写英文字母的字符串 A 和 B。需要从字符串 A 中取出 $k$ 个互不重叠的非空子串，将这些子串按在 A 中出现的顺序连接，形成一个新字符串。问有多少种方法可以使新串等于字符串 B。子串取出的位置不同视为不同方案。

#### T3
[洛谷P4362](https://www.luogu.com.cn/problem/P4362) [NOI2002] 贪吃的九头龙

给定一棵拥有 $n$ 个节点的树，每个节点上有一个果子。九头龙有 $m$ 个头，每个头必须吃至少一个果子。你需要将这些果子划分给九头龙，划分的难度由每个头吃到的果子中最大和最小编号的差值决定，目标是使最大的难度值最小化。

#### T4
[洛谷P3177](https://www.luogu.com.cn/problem/P3177) [HAOI2015] 树上染色

给定一棵有 $n$ 个点的树，每条边有权重。要求在树中选择 $k$ 个点染成黑色，其余 $n-k$ 个点染成白色。目标是最大化染色后的收益，该收益等于所有黑色点之间的两两距离之和加上所有白色点之间的两两距离之和。求最大收益值。

---
### 搜索
#### T1
[洛谷P4799](https://www.luogu.com.cn/problem/P4799) [CEOI2015 Day2] 世界冰球锦标赛

给定 $N$ 场冰球比赛和一个预算 $M$，每场比赛的门票价格不同。你需要计算所有不超过预算的观赛方案数。每场比赛要么选择观看，要么不观看，不同的选择组合视为不同方案。

#### T2
[洛谷P1514](https://www.luogu.com.cn/problem/P1514) [NOIP2010 提高组] 引水入城

在一个 $N \times M$ 的矩形区域中，每个城市有一个海拔高度。只允许在第 $1$ 行与湖泊接壤的城市建造蓄水厂，其它城市只能建造输水站。输水站能将水从高海拔城市输送到低海拔城市。目标是确保第 $N$ 行的所有城市都有水利设施。如果可能，输出最少需要的蓄水厂数量；如果不可能，输出无法建有水利设施的干旱区城市数量。

#### T3
[洛谷P2831](https://www.luogu.com.cn/problem/P2831) [NOIP2016 提高组] 愤怒的小鸟

在平面上有 $n$ 只小猪，位置为 $(x_i, y_i)$。每只小鸟的飞行轨迹为 $y=ax^2+bx$，其中 $a<0$。要求确定最少需要多少只小鸟才能消灭所有小猪。

---
### 简单题
#### T1
[洛谷P1955](https://www.luogu.com.cn/problem/P1955) [NOI2015] 程序自动分析

给定多个独立的约束满足问题，每个问题包含 $n$ 个形如 $x_i=x_j$ 或 $x_i\neq x_j$ 的约束条件。需要判断能否为每个变量赋值，使得所有约束条件同时成立。如果可以，则输出 `YES`，否则输出 `NO`。

#### T2
[洛谷P1439](https://www.luogu.com.cn/problem/P1439) 最长公共子序列

给定两个 $1$ 到 $n$ 的排列 $P_1$ 和 $P_2$，要求计算它们的最长公共子序列的长度。
