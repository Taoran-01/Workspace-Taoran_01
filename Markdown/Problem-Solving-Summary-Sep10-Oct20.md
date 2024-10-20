<!-- 做题总结 24-09-10 至 24-10-20 -->

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
[AT_kupc2021_c](https://atcoder.jp/contests/kupc2021/tasks/kupc2021_c?lang=en) Gacha | [洛谷](https://www.luogu.com.cn/problem/AT_kupc2021_c)

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

#### T5
[洛谷P1966](https://www.luogu.com.cn/problem/P1966) [NOIP2013 提高组] 火柴排队

有两列高度互不相同的火柴，每列有 $n$ 根火柴。定义两列火柴之间的距离为每根火柴高度差的平方和。通过交换相邻火柴的方式，求最小的距离和最少的交换次数。如果交换次数过大，输出该次数对 $10^8-3$ 取模的结果。

#### T6
[洛谷P8446](https://www.luogu.com.cn/problem/P8446) 虹色的北斗七星

你有一个长度为 $n$ 的序列 $a$，它的一个区间 $[l,r]$ 的价值是 $\max{a_l,a_{l+1},\dots,a_r}-\min{a_l,a_{l+1},\dots,a_r}-r+l-1$。求这个价值序列价值最大的子区间并输出这个价值。

#### T7
[洛谷P8102](https://www.luogu.com.cn/problem/P8102) [LCOI2022] Cow Insertion

给出一个长度为 $n$ 的序列 $a$，一个长度 $k$ 和一个值 $v$。你可以将 $v$ 插入 $a$ 的任意 $n+1$ 个位置得到序列 $b$。最大化 $\max\limits_{l=1}^{n-k+1}\max\limits_{i=l}^{l+k-1}b_i$，即长度为 $k$ 的子区间内最大值的最大值。

#### T8
[洛谷P2882](https://www.luogu.com.cn/problem/P2882) [USACO07MAR] Face The Right Way G

有 $N$ 头牛排成一列，每头牛朝向前方或后方。农夫需要将所有牛调整为朝前。可以使用一个机器，每次可以翻转 $K$ 头连续牛的朝向。请确定最小的 $K$ 值，使得翻转操作次数最少，并输出 $K$ 和最小操作次数 $M$。

#### T9
[洛谷P3917](https://www.luogu.com.cn/problem/P3917) 异或序列

给出序列 $A_1,A_2,\cdots,A_N$，求 $\sum\limits_{1\le l\le r\le N}\bigoplus\limits_{i=l}^rA_i$。

#### T10
[洛谷P7913](https://www.luogu.com.cn/problem/P7913) [CSP-S 2021] 廊桥分配

在一个机场，有若干个廊桥供飞机停靠。飞机有国内航班和国际航班，分别只能使用各自区域的廊桥。机场决定遵循“先到先得”原则分配廊桥，要求最大化停靠在廊桥上的飞机数量。

给定廊桥数量、国内航班和国际航班的信息，包括每架飞机的抵达和离开时刻，最大化能够停靠廊桥的飞机总数。

---
### 数据结构
#### T1
[洛谷P3224](https://www.luogu.com.cn/problem/P3224) [HNOI2012] 永无乡

有 $n$ 个岛，每个岛有一个独特的重要度排名。某些岛之间有桥相连，可以通过桥到达其他岛。两种操作： 
1. `B x y`：在岛 $x$ 和岛 $y$ 之间修建一座新桥。
2. `Q x k`：查询与岛 $x$ 连通的岛中，重要度排名第 $k$ 小的岛的编号。

#### T2
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

#### T3
[洛谷P4513](https://www.luogu.com.cn/problem/P4513) 小白逛公园

单点修改区间查询最大子段和。

问题形式：序列，单点修改，区间查询；
信息合并条件：最优端点决策有限。
考虑维护靠左、靠右和子区间答案三个信息，可以满足信息封闭。

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

#### T5
[洛谷P3146](https://www.luogu.com.cn/problem/P3146) [USACO16OPEN] 248 G | [洛谷P3147](https://www.luogu.com.cn/problem/P3147) [USACO16OPEN] 262144 P

给定一个包含 $N$ 个正整数的序列，范围在 $1$ 到 $40$。每次可以选择两个相邻且相同的数，将它们合并为一个比原来的数大 $1$ 的数。目标是使得合并后序列中的最大值尽可能大。请输出能生成的最大整数。

---
### 矩阵快速幂
#### T1
[洛谷P2044](https://www.luogu.com.cn/problem/P2044) [NOI2012] 随机数生成器 
$X_{n+1} = (aX_n + c) \bmod m$，要求计算并输出 $X_n \bmod g$ 的值。

#### T2
[洛谷P2579](https://www.luogu.com.cn/problem/P2579) [ZJOI2005] 沼泽鳄鱼

有一个石墩和石桥的图，石墩之间用石桥相连。给定一个起始石墩和一个目标石墩，以及需要经过的时间单位，计算从起始石墩出发，在规定时间内到达目标石墩的路径数量。

食人鱼在石墩上有周期性的运动，运动周期为 $2$、$3$ 或 $4$ 个单位时间。食人鱼到达石墩时会攻击在上面的人，要求计算的路径中不能与食人鱼在同一时刻到达同一石墩。

1. 第一行：石墩数目、石桥数目、起始石墩编号、目标石墩编号和时间单位。
2. 接下来 $M$ 行：每行两个整数，表示一座石桥连接的两座石墩。
3. 第 $M+2$ 行：食人鱼的数量。
4. 接下来每条食人鱼的信息，包含运动周期及其路径。

---
### 树链剖分
#### T1
[洛谷P3384](https://www.luogu.com.cn/problem/P3384) 重链剖分/树链剖分

如题，已知一棵包含 $N$ 个结点的树（连通且无环），每个节点上包含一个数值，需要支持以下操作：
- `1 x y z`，表示将树从 $x$ 到 $y$ 结点最短路径上所有节点的值都加上 $z$。
- `2 x y`，表示求树从 $x$ 到 $y$ 结点最短路径上所有节点的值之和。
- `3 x z`，表示将以 $x$ 为根节点的子树内所有节点值都加上 $z$。
- `4 x` 表示求以 $x$ 为根节点的子树内所有节点值之和。

---
### 卡特兰数
#### T1
[洛谷P2532](https://www.luogu.com.cn/problem/P2532) [AHOI2012] 树屋阶梯

给定一些空心钢材，它们的高度为正整数倍且数量充足。要求从这些钢材中选择 $N$ 个，搭建一个总高度为 $N$ 尺的阶梯，每一步台阶的高度和宽度均为 $1$ 尺。请计算有多少种不同的搭建方法。注意，钢材的空心面不可向上。

#### T2
[洛谷P7118](https://www.luogu.com.cn/problem/P7118) Galgame

给定一棵以 $1$ 为根的二叉树，每个节点代表一个场景。每个场景有两个子场景，分别对应选择 $A$ 和选择 $B$。定义两个场景的趣味度比较如下：

1. 如果两个场景能到达的不同场景总数不同，趣味度高的场景更有趣。
2. 如果两个场景的 $A$ 子场景不同，趣味度高的A子场景更有趣。
3. 否则比较 $B$ 子场景的趣味度。

两个场景被认为本质相同，当且仅当它们的 $A$ 子场景和 $B$ 子场景均相同。趣味度是所有本质不同且不比当前场景有趣的场景数量。要求输出趣味度对 $998244353$ 取模的结果。

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

#### T4
[洛谷P1849](https://www.luogu.com.cn/problem/P1849) [USACO12MAR] Tractor S

在二维平面上，给定一个拖拉机的起始坐标和若干干草堆的坐标。拖拉机只能沿坐标轴移动，且不能停留在干草堆的坐标上。请计算将拖拉机移动回原点所需最少移走的干草堆数量。

---
### 简单题
#### T1
[洛谷P1955](https://www.luogu.com.cn/problem/P1955) [NOI2015] 程序自动分析

给定多个独立的约束满足问题，每个问题包含 $n$ 个形如 $x_i=x_j$ 或 $x_i\neq x_j$ 的约束条件。需要判断能否为每个变量赋值，使得所有约束条件同时成立。如果可以，则输出 `YES`，否则输出 `NO`。

#### T2
[洛谷P1439](https://www.luogu.com.cn/problem/P1439) 最长公共子序列

给定两个 $1$ 到 $n$ 的排列 $P_1$ 和 $P_2$，要求计算它们的最长公共子序列的长度。

---
### 未分类
#### T
[洛谷P4395](https://www.luogu.com.cn/problem/P4395) [BOI2003] Gem 气垫车 | [洛谷P5765](https://www.luogu.com.cn/problem/P5765) [CQOI2005] 珠宝

给定一棵树，要求为树的每个结点分配一个正整数权值，且相邻结点的权值不能相同，目标是使整棵树的总权值最小。输入包括结点数量和结点间的连接关系，输出为最小的总权值。

#### T
[洛谷P5658](https://www.luogu.com.cn/problem/P5658) [CSP-S2019] 括号树

给定一棵树，要求统计从根结点到每个结点的路径上，有多少个不同的合法括号串子串。输入包括结点数量、每个结点的括号和父结点信息，输出为每个结点的路径上合法括号串子串数量的加权异或和。

#### T
[洛谷P1880](https://www.luogu.com.cn/problem/P1880) [NOI1995] 石子合并

在一个圆形操场上，有 $N$ 堆石子，要求将这些石子合并成一堆，每次只能合并相邻的两堆，且合并的得分为两堆石子的总数。设计一个算法计算将 $N$ 堆石子合并成 $1$ 堆的最小得分和最大得分。输入包括堆数和每堆石子的数量，输出为最小得分和最大得分。

#### T
[洛谷P1063](https://www.luogu.com.cn/problem/P1063) [NOIP2006 提高组] 能量项链

给定一个能量项链，上面有 $N$ 颗能量珠。每颗珠子有一个头标记和尾标记，可以通过相邻的两颗珠子聚合成新珠子，释放的能量为头标记、尾标记和下一颗珠子的头标记的乘积。要求设计聚合顺序，使得释放的总能量最大。输入包括珠子的数量和各珠子的头标记，输出为最大释放能量。

#### T
[洛谷P1541](https://www.luogu.com.cn/problem/P1541) [NOIP2010 提高组] 乌龟棋

给定一个包含 $N$ 个格子的棋盘，每个格子上有非负整数分数，起点为第 $1$ 格，终点为第 $N$ 格。玩家有 $M$ 张爬行卡片，分为 $4$ 种类型，每种类型标记为 $1$ 到 $4$，表示向前移动的格数。每张卡片只能使用一次，玩家的目标是选择一种卡片使用顺序，使得从起点到终点的总分数最大化。输入包括棋盘格子数、分数和爬行卡片的数量与类型，输出为最多能获得的分数。

#### T
[洛谷P4310](https://www.luogu.com.cn/problem/P4310) 绝世好题

给定一个长度为 $n$ 的数列 $a_i$，求 $a_i$ 的子序列 $b_i$ 的最长长度 $k$，满足 $b_i\&b_{i-1}\neq0$，其中 $2\le i\le k$，$\&$ 表示位运算取与。


#### T
[洛谷P2704](https://www.luogu.com.cn/problem/P2704) [NOI2001] 炮兵阵地

在一个 $N\times M$ 的网格中，标记某些格子为可布置炮兵的平原，其余为山地。目标是在不互相攻击的情况下，尽可能多地布置炮兵。

#### T
[洛谷P1879](https://www.luogu.com.cn/problem/P1879) [USACO06NOV] Corn Fields G

给定一个 $M\times N$ 的矩形牧场，某些格子可种植，某些格子不能。要求计算不相邻的可种植格子的选择方案总数，包括不种植的情况。

#### T
[洛谷P1896](https://www.luogu.com.cn/problem/P1896) [SCOI2005] 互不侵犯

在一个 $N\times N$ 的棋盘上，放置 $K$ 个国王，使其不互相攻击。求所有可能的放置方案数。

#### T
[AT_nikkei2019_2_final_c](https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_c) Largest N | [洛谷](https://www.luogu.com.cn/problem/AT_nikkei2019_2_final_c)

给定一个 $H$ 行 $W$ 列的矩阵，其中有 $K$ 个白点，其余为黑点。求一个 $k\times k$ 的子矩阵，使其左边、右边及主对角线上的所有点均为黑点，返回 $k$ 的最大值。

#### T
[洛谷P11188](https://www.luogu.com.cn/problem/P11188) [KDOI-10] 商店砍价

给定一个正整数 $n$（由 $1\sim9$ 的数字组成），可以选择删除某一位，代价为对应位的值，或删除所有数位，代价为 $n$。求删除整个数的最小代价。

#### T
[AT_arc121_d](https://atcoder.jp/contests/arc121/tasks/arc121_d) 1 or 2 | [洛谷](https://www.luogu.com.cn/problem/AT_arc121_d)

有 $n$ 个糖果，每个糖果的美味值为 $a_i$。每次可以选择吃 $1$ 个或 $2$ 个糖，记录总和。求所有吃糖方式中，记录的最大值和最小值之差的最小值。

#### T
[洛谷P9753](https://www.luogu.com.cn/problem/P9753) [CSP-S 2023] 消消乐

给定一个由小写字母组成的字符串，可以通过删除相邻相同字符变为空字符串。判断其所有非空连续子串中，有多少个是可消除的。输出可消除子串的数量。

#### T
[洛谷P5390](https://www.luogu.com.cn/problem/P5390) [Cnoi2019] 数学作业

给定 $T$ 天的作业，每天有一个集合 $V$，要求计算所有子集的异或和的和，结果对 $998244353$ 取模。输入包含 $T$ 和每个集合的大小及元素，输出每个集合的结果。

#### T
[洛谷P8819](https://www.luogu.com.cn/problem/P8819) [CSP-S 2022] 星战

有 $n$ 个据点和 $m$ 条单向虫洞。敌人可以摧毁虫洞或据点，摧毁后连接的虫洞变为不可用。修复虫洞或据点的特种部队可以恢复连接。若从任一据点出发可以无限次通过虫洞，且只有一条虫洞可用，则可反击。要求根据每次指令判断当前是否可以反击。

#### T
[洛谷P4427](https://www.luogu.com.cn/problem/P4427) [BJOI2018] 求和

给定一棵根树，求路径上所有节点深度的 $k$ 次方和，节点深度定义为到根的边数。输入包含树的节点数和边，询问包含节点对及幂次，输出每次询问结果对 $998244353$ 取模。

#### T
[洛谷P2680](https://www.luogu.com.cn/problem/P2680) [NOIP2015 提高组] 运输计划

在一个星球系统中，有多个星球和航道连接，航道之间的旅行时间不同。一个物流公司有多个运输计划，需要在最短时间内完成这些计划。公司可以选择将一条航道改造成虫洞，使用虫洞旅行将不消耗时间。任务是找出在选择一条航道作为虫洞后，完成所有运输计划所需的最短时间。输入包括星球数量、航道信息及运输计划，输出为最短完成时间的整数值。

#### T
[CF173B](https://codeforces.com/contest/173/problem/B) Chamber of Secrets | [洛谷](https://www.luogu.com.cn/problem/CF173B)

给定一个 $n\times m$ 的矩形网格，部分单元格有柱子。光线可以穿过柱子，但施法后柱子能将光线反射向四个方向。蛇怪位于右下角，向左凝视，进入密室的人需朝其移动方向看。求施法的最小柱子数量，确保无法进入密室；若不可能，则输出 $-1$。

#### T
[CF325B](https://codeforces.com/contest/325/problem/B) Stadium and Games | [洛谷](https://www.luogu.com.cn/problem/CF325B)

有若干队伍参加足球赛。队伍数量为偶数时，两两配对进行淘汰赛；为奇数时，若剩一队，则比赛结束；若剩多队，则进行单循环赛。给定比赛场数 $n$，求可能的队伍数并升序输出，若无解，则输出 $-1$。

#### T
[CF358D](https://codeforces.com/contest/538/problem/D) Weird Chess | [洛谷](https://www.luogu.com.cn/problem/CF538D)

在一个 $n\times n$ 的棋盘上，棋子只能按照给定的移动向量移动。已知棋盘上棋子的分布，求能否恢复可能的移动向量，并输出该向量的描述；若不可能，则输出 `NO`。

#### T
[CF1637D](https://codeforces.com/contest/1637/problem/D) Yet Another Minimization Problem | [洛谷](https://www.luogu.com.cn/problem/CF1637D)

给定两个长度为 $n$ 的数组 $a$ 和 $b$，可交换其中任意元素。定义数组的权值为所有元素对和的平方和，目标是最小化两个数组的总权值。输出最小可能的总权值。

#### T
[CF1479B1](https://codeforces.com/contest/1479/problem/B1) Painting the Array I | [洛谷](https://www.luogu.com.cn/problem/CF1479B1)

给定一个数组 $a$ 和一个二进制数组 $b$，将 $a_i$ 染为 $b_i$ 色，求最大化被染成 $0$ 和 $1$ 的数组的分段数之和。输出最大分段数。

#### T
[CF1891F](https://codeforces.com/contest/1891/problem/F) A Growing Tree | [洛谷](https://www.luogu.com.cn/problem/CF1891F)

给定一棵树，初始只含一个节点，编号为 $1$，初始权值为 $0$，设树的大小为 $\text{sz}$。$q$ 次操作，每次：
- `1 x`：在 $x$ 下挂一个节点，编号为 $\text{sz}+1$，初始权值为 $0$。
- `2 x v`：将当前 $x$ 子树中节点的权值加上 $v$。
    
求所有操作完成后每个节点的点权。

#### T
[CF1473E](https://codeforces.com/contest/1473/problem/E) Minimum Path | [洛谷](https://www.luogu.com.cn/problem/CF1473E)

给定一个含有 $n$ 个顶点和 $m$ 条边的带权无向图，要求计算从顶点 $1$ 到每个顶点 $i$ 的最小路径权值。路径权值定义为边权和减去最大边权再加上最小边权。

#### T
[CF1383A](https://codeforces.com/contest/1383/problem/A) String Transformation 1 | [洛谷](https://www.luogu.com.cn/problem/CF1383A)

给定两个相同长度的字符串 $A$ 和 $B$，每次可以选择相同字母 $x$ 变为严格大于 $x$ 的字母 $y$。求将 $A$ 变为 $B$ 的最少操作次数或判断是否无法完成。

#### T
[CF471D](https://codeforces.com/contest/471/problem/D) MUH and Cube Walls | [洛谷](https://www.luogu.com.cn/problem/CF471D)

给定两堵墙，分别由 $n$ 和 $w$ 个塔构成，求出墙中与 $b$ 墙顶部形状相同的连续区间的数量。

#### T
[CF1506G](https://codeforces.com/contest/1506/problem/G) Maximize the Remaining String | [洛谷](https://www.luogu.com.cn/problem/CF1506G)

给定一个字符串 $s$，通过删除字符和复制字符串的方式，使得最终字符串 $t$ 中每种字符只保留一个，并且最大化其字典序。输出可以得到的字典序最大字符串。

#### T
[CF1537E2](https://codeforces.com/contest/1537/problem/E2) Erase and Extend (Hard Version) | [洛谷](https://www.luogu.com.cn/problem/CF1537E2)

给定字符串 $s$，可以删除最后一个字符或将字符串复制，求字典序最小的长度为 $k$ 的字符串。

#### T
[CF1800E2](https://codeforces.com/contest/1800/problem/E2) Unforgivable Curse (hard version) | [洛谷](https://www.luogu.com.cn/problem/CF1800E2)

给定两个字符串 $s_1$ 和 $s_2$ 以及一个整数 $k$，可以在距离为 $k$ 或 $k+1$ 的位置交换字符。判断最终能否将 $s_1$ 和 $s_2$ 变为相同的字符串。
