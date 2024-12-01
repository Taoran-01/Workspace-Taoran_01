
<!-- 做题总结 24-09-10 至 24-10-20 -->

#### T
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

#### T
[洛谷P3740](https://www.luogu.com.cn/problem/P3740) [HAOI2014] 贴海报

给定一个长度为 $N$ 的墙和 $M$ 张海报，每张海报覆盖墙上从第 $A_i$ 到第 $B_i$ 个位置。后贴的海报可以覆盖前面的海报。你需要计算在所有海报张贴完成后，墙上仍可见的海报数量。

一个十分简单的做法：从上向下覆盖。即，将修改倒序处理。  
维护一个 $O(V)$ 的 0-1 序列，被覆盖设为 $1$。由于覆盖操作倒序处理，新的在旧的前面处理；如果旧的还可以覆盖额外的 $0$，说明从外面它看可以被看到，答案累加 $1$。

[AC](https://www.luogu.com.cn/record/176742963) 2.85MB 48ms  
我不知道为什么我的离散化假了。

#### T
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

#### T
[AT_kupc2021_c](https://atcoder.jp/contests/kupc2021/tasks/kupc2021_c?lang=en) Gacha | [洛谷](https://www.luogu.com.cn/problem/AT_kupc2021_c)

给定两个长度为 $N$ 的严格递增整数序列 $A_1, A_2, \dots, A_N$ 和 $B_1, B_2, \dots, B_N$，表示 $N$ 个位置上分别有 $N$ 台扭蛋机和 $N$ 枚硬币。你起始在位置 $0$，可以自由移动并需要在每个扭蛋机位置消耗一枚硬币来启动扭蛋机。计算移动距离的最小值。

贪心。将游戏机和硬币同一处理。  
考虑将位置分为两份：第一份从 $a_1$ 到 $a_x$，全部一次性走完，不留空缺；第二份从 $a_{x+1}$ 到 $a_n$，先走到终点 $a_n$，再返回到 $a_{x+1}$。

可以证明这样是最优的。

[AC](https://atcoder.jp/contests/kupc2021/submissions/57878714) 7.78MB 22ms  
场上死因：没开 `long long`。挂了 $50\text{pts}$，$\text{rk}51\rightarrow\text{rk}70$。

#### T
[洛谷P1966](https://www.luogu.com.cn/problem/P1966) [NOIP2013 提高组] 火柴排队

有两列高度互不相同的火柴，每列有 $n$ 根火柴。定义两列火柴之间的距离为每根火柴高度差的平方和。通过交换相邻火柴的方式，求最小的距离和最少的交换次数。如果交换次数过大，输出该次数对 $10^8-3$ 取模的结果。

根据排序不等式，火柴两两配对应该是第 $k$ 小的匹配第 $k$ 小的。

先找到每支火柴的目标位置，再对当前和目标的位置坐标做逆序对。绕来绕去相当复杂，思路需要理清。

[AC](https://www.luogu.com.cn/record/179789949) 180ms 20.54MB

#### T6
[洛谷P8446](https://www.luogu.com.cn/problem/P8446) 虹色的北斗七星

你有一个长度为 $n$ 的序列 $a$，它的一个区间 $[l,r]$ 的价值是 $\max\{a_l,a_{l+1},\dots,a_r\}-\min\{a_l,a_{l+1},\dots,a_r\}-r+l-1$。求这个价值序列价值最大的子区间并输出这个价值。

关键点在于区间 $[l,r]$ 中 $\max$ 和 $\min$ 的位置一定分别对应 $l$ 和 $r$ 两个端点。

开始分类讨论：

1. 如果 $a_l=\min\land a_r=\max$，则有
   $$
   \begin{aligned}
   &\max\{a_l,a_{l+1},\dots,a_r\}-\min\{a_l,a_{l+1},\dots,a_r\}-r+l-1\\
   =&a_r-a_l-r+l-1\\
   =&-(a_l-l)+(a_r-r)-1
   \end{aligned}
   $$
   不妨令 $d_i=a_i-i$，则原式变为 $-d_l+d_r-1$。求最大值即可。
2. 如果 $a_l=\max\land a_r=\min$，则有
   $$
   \begin{aligned}
   &\max\{a_l,a_{l+1},\dots,a_r\}-\min\{a_l,a_{l+1},\dots,a_r\}-r+l-1\\
   =&a_l-a_r-r+l-1\\
   =&(a_l+l)-(a_r+r)-1
   \end{aligned}
   $$
   不妨令 $d_i=a_i+i$，则原式变为 $d_l-d_r-1$。求最大值即可。

关于答案的正确性：即使一种情况 $d_l$ 不是 $\min/\max$，则另一种情况一定正确，取了最大值之后是对的。

[AC](https://www.luogu.com.cn/record/179967910) 47.28MB 437ms

场上做法：考虑答案区间不会跨过 $\min$ 和 $\max$，将序列按 $\min$ 和 $\max$ 为界分治成三个子问题求解。最多拆分 $n$ 次，复杂度 $O(n)$。汪老师说做法正确，但是我写挂了。

#### T7
[洛谷P8102](https://www.luogu.com.cn/problem/P8102) [LCOI2022] Cow Insertion

给出一个长度为 $n$ 的序列 $a$，一个长度 $k$ 和一个值 $v$。你可以将 $v$ 插入 $a$ 的任意 $n+1$ 个位置得到序列 $b$。最大化 $\max\limits_{l=1}^{n-k+1}\max\limits_{i=l}^{l+k-1}b_i$，即长度为 $k$ 的子区间内最大值的最大值。

单调队列预处理当前位置向前 $k$ 长度的最大值序列 $\text{d1}_i=\max\limits_{j=i-k+1}^ia_j$ 和向前 $k-1$ 长度的最大值序列 $\text{d2}_i=\max\limits_{j=i-k}^ia_j$。

考虑插入后影响到的长度为 $k$ 的区间，恰恰是以当前位置为终点的长度为 $k-1$ 的区间和向后 $k-1$ 个位置为终点的长度为 $k-1$ 的区间。（及这段范围内，因被包含其中故只需考虑这两个。）

将 $\text{d2}_i$ 对 $v$ 取 $\max$ 后更新，考虑 $v$ 插入的每一个位置，遍历求解即可。注意边界。

[AC](https://www.luogu.com.cn/record/180244474) 46.09MB 72ms

场上挂分原因：考虑到求长度为 $k-1$ 的区间最值，但首尾不会处理，没考虑到对边界取 $\min/\max$。索性假定区间较整体非常短，最大值大概率在中间普通位置取得，得到了 $90pts$。

#### T8
[洛谷P2882](https://www.luogu.com.cn/problem/P2882) [USACO07MAR] Face The Right Way G

有 $N$ 头牛排成一列，每头牛朝向前方或后方。农夫需要将所有牛调整为朝前。可以使用一个机器，每次可以翻转 $K$ 头连续牛的朝向。请确定最小的 $K$ 值，使得翻转操作次数最少，并输出 $K$ 和最小操作次数 $M$。

考虑取反操作：取反两次与未取反是等价的。因此机器在相邻位置做两次操作，即可将单独的一头牛翻过来。故只需要判断最前端的牛是否需要调正，就可以确定当前机器的运行状态。

让机器从左向右遍历，只考虑最左边的牛。如果它反了就调正。此时判断后面的牛是否全部为正，若有则记录一次答案。

[AC](https://www.luogu.com.cn/record/180867586) 612.00KB 223ms

#### T9
[洛谷P3917](https://www.luogu.com.cn/problem/P3917) 异或序列

给出序列 $A_1,A_2,\cdots,A_N$，求 $\sum\limits_{1\le l\le r\le N}\bigoplus\limits_{i=l}^rA_i$。

令 $f_{i,j}$ 表示**前** $i$ 个数的**第** $j$ 个二进制位做的贡献**和**，不移位。

1. 若 $a_i$ 的第 $j$ 个二进制数为 $1$，相比前 $i-1$ 个数多异或了一个 $1$。它前面的数 $a_1\sim a_{i-1}$ 之前做的贡献都取消，没做贡献的都可以做。
2. 若 $a_i$ 的第 $j$ 个二进制数为 $0$，则它前面的数做的贡献都不发生变化。

$$
f_{i,j}=\begin{cases}
i-f_{i-1,j}&a_i\&2^j=0\\
f_{i-1,j}&a_i\&2^j=1
\end{cases}
$$

答案即为 $\sum\limits_{j=0}^{32}f_{n,j}\times2^j$。

[AC](https://www.luogu.com.cn/record/180868931) 13.49MB 58ms

另一种巧妙的解法：

> 按二进制每一位分开算。
> 
> 记前缀异或值 X[0...N]，一段区间 [L, R] 的异或值就是 X[L-1] xor X[R]。
> 
> 那么就是统计有多少个区间的异或值是 1，那只需要统计 X[0...N] 中是 0 和 1 的分别有多少个，两个个数相乘就是区间个数。

#### T10
[洛谷P7913](https://www.luogu.com.cn/problem/P7913) [CSP-S 2021] 廊桥分配

在一个机场，有若干个廊桥供飞机停靠。飞机有国内航班和国际航班，分别只能使用各自区域的廊桥。机场决定遵循“先到先得”原则分配廊桥，要求最大化停靠在廊桥上的飞机数量。给定廊桥数量、国内航班和国际航班的信息，包括每架飞机的抵达和离开时刻，最大化能够停靠廊桥的飞机总数。

考虑“先到先得”的性质，先忽略廊桥限制安排航班，看各区内的各航班能安排到的最小编号是多少。  
容易发现，在这种情况下安排的航班，如果容量小于客机停机位编号，则它一定在远机位。

接着预处理前缀和，枚举各区的机位数求解即可。

[AC](https://www.luogu.com.cn/record/181059360) 4.55MB 355ms

---
### 数据结构
#### T1
[洛谷P3224](https://www.luogu.com.cn/problem/P3224) [HNOI2012] 永无乡

有 $n$ 个岛，每个岛有一个独特的重要度排名。某些岛之间有桥相连，可以通过桥到达其他岛。两种操作： 
1. `B x y`：在岛 $x$ 和岛 $y$ 之间修建一座新桥。
2. `Q x k`：查询与岛 $x$ 连通的岛中，重要度排名第 $k$ 小的岛的编号。

动态开点线段树+并查集 模板。

1. 初始化：建立 $1\sim n$ 的动态开点线段树，第 $i$ 个岛的根节点为 $\text{rt}_i$，范围为 $[\text{rk}_i,\text{rk}_i]$。  
   每个节点 $p$ 记录该节点下挂的 $\text{rk}$ 的个数，记作 $d_p$。
   每个排名 $\text{rk}_i$ 反向记录编号 $\text{idx}_{\text{rk}_i}=i$。
2. 合并：查询 $x,y$ 的父亲 $\text{fa}_x,\text{fa}_y$，将 $\text{rt}_{\text{fa}_x}$ 为根的线段树和 $\text{rt}_{\text{fa}_y}$ 为根的线段树 merge 起来。
3. 查询：查询 $x$ 的父亲 $\text{fa}_x$ 对应的线段树 $\text{rt}_{\text{fa}_x}$ 中排名为 $k$ 的节点。  
   如果小了就向左子树查 $k$，若大了就向右子树查 $k-d_\text{ls}$。  
   叶子节点对应区间即为 $[\text{rk}_i,\text{rk}_i]$，借助 $\text{idx}$ 反向可获得 $i$。

[WA](https://www.luogu.com.cn/record/180903242) 10pts
```cpp
struct node {
	int ls, rs, d;
	node() {ls=rs=0, d=1;}
} t[N<<6];
```
`t[p].d` 不可直接初始化为 $1$，应在 `nd()` 构造函数中将 $d$ 初始化。  
因为在访问到空的线段树节点时，不应有任何 $\text{rk}$ 挂在此节点。

[AC](https://www.luogu.com.cn/record/180914498) 75.96MB 881ms

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

#### T3
[洛谷P4513](https://www.luogu.com.cn/problem/P4513) 小白逛公园

单点修改区间查询最大子段和。

开线段树。对于节点 $p\rightarrow[l,r]$ 维护以下信息：
1. 以 $a_l$ 为左端点且被 $[l,r]$ 包含的最大字段和 $\text{lmax}$；
2. 以 $a_r$ 为右端点且被 $[l,r]$ 包含的最大字段和 $\text{rmax}$；
3. 被 $[l,r]$ 包含的最大子段和 $\text{pmax}$；
4. $[l,r]$ 内所有数的和 $\text{sum}$。

形式化地：
$$
\begin{aligned}
\text{lmax}&=\max_{i=l}^r\sum_{j=l}^ia_j\\
\text{rmax}&=\max_{i=l}^r\sum_{j=i}^ra_j\\
\text{pmax}&=\max_{i=l}^r\max_{j=i}^r\sum_{k=i}^ja_k\\
\text{sum}&=\sum_{i=l}^ra_i
\end{aligned}
$$

考虑合并相邻的两个区间 $[l_\text{ls},r_\text{ls}],\ [l_\text{rs},r_\text{rs}]\Rightarrow[l,r]$，其 $l_2=r_1+1$。

- 对于 $\text{lmax}$：
  - 若右端点在左区间内取得，区间答案和左区间答案相同，所以 $\text{lmax}=\text{lmax}_\text{ls}$；
  - 若右端点在右区间内取得，必须要把左区间全部取走再取右区间，所以 $\text{lmax}=\text{sum}_\text{ls}+\text{rmax}_\text{rs}$。
- 对于 $\text{rmax}$：  
  - 若左端点在右区间内取得，区间答案和右区间答案相同，所以 $\text{rmax}=\text{rmax}_\text{rs}$；
  - 若左端点在左区间内取得，必须要把右区间全部取走再取左区间，所以 $\text{rmax}=\text{rmax}_\text{ls}+\text{sum}_\text{rs}$。
- 对于 $\text{pmax}$：  
  - 最大子段和有三个来源：单独左间、单独右区间和跨左右区间。  
  所以 $\text{pmax}=\max\{\text{pmax}_\text{ls},\ \text{pmax}_\text{rs},\ \text{rmax}_{ls}+\text{lmax}_{rs}\}$。
- 对于 $\text{sum}$：  
  - 朴素的，左右直接相加即可。 $\text{sum}=\text{sum}_\text{ls}+\text{sum}_\text{rs}$。

按上面的方式处理区间合并，完成线段树。

[AC](https://www.luogu.com.cn/record/185431114) 66.38MB 606ms

> 问题形式：序列，单点修改，区间查询；  
> 信息合并条件：最优端点决策有限。  
> 考虑维护靠左、靠右和子区间答案三个信息，可以满足信息封闭。

---
### 动态规划
状态设计根据题目条件定。

#### T1
[洛谷P1026](https://www.luogu.com.cn/problem/P1026) [NOIP2001 提高组] 统计单词个数

给定一个字母串，要求将其分为 $k$ 份，并统计每份中包含的单词总数最大。单词来自一个不超过 $6$ 个单词的字典，且单词可以重叠使用，但首字母不能重复使用。

注意到数据范围相当小，匹配时 $O(n)$ 暴力匹配即可。

令 $\text{cst}_{i,j}$ 表示第 $i$ 个位置到第 $j$ 个位置出现的不重叠首字母的单词总量，$f_{i,j}$ 表示前 $i$ 个单词分了 $j$ 块所得到的最大单词总数。

初始化：整个一块 $f_{i,1}=\text{cst}_{1,i}$，一字一块 $f_{i,i}=f_{i-1,i-1}+\text{cst}_{i,i}$。  
转移：枚举断点 $f_{i,j}=\max\limits_{x=j}^{i-1}f_{x,j-1}+\text{cst}_{x+1,i}$。

初始化一字一块的原因：后续过程不能处理 $f_{i,i}$，因为枚举断点需要长度 $>1$。

[AC](https://www.luogu.com.cn/record/176525193) 684.00KB 79ms

状态设计：记录当前位置和分的份数，即可唯一确定状态。  
状态转移：前若干位置到当前位置作为块，预处理单词数。

#### T2
[洛谷P2679](https://www.luogu.com.cn/problem/P2679) [NOIP2015 提高组] 子串

有两个仅包含小写英文字母的字符串 A 和 B。需要从字符串 A 中取出 $k$ 个互不重叠的非空子串，将这些子串按在 A 中出现的顺序连接，形成一个新字符串。问有多少种方法可以使新串等于字符串 B。子串取出的位置不同视为不同方案。

令 $f_{i,j,k}$ 表示 $A$ 的前 $i$ 个位置与 $B$ 的前 $j$ 个位置匹配，共 $k$ 个子串的方案数。则有：

$$
f_{i,j,k}=\begin{cases}
f_{i-1,j,k}&A_i\neq B_j\\
f_{i-1,j,k}+f_{i-1,j-1,k-1}&A_i=B_j\land A_{i-1}\neq B_{j-1}
f_{i-1,j,k}+f_{i-1,j-1,k-1}+f_{i-2,j-2,k-2}&A_i=B_j\land A_{i-1}=B_{j-1}\land A_{i-2}\neq B_{j-2}
\end{cases}
$$

解释：
1. 当前两字母不同，由于 $A$ 部分匹配到 $B$，故 $A$ 不选，总子串数量不变。
2. 两字母相同，除了可以执行上面的操作之外，还可以多匹配一个。总子串数量 $+1$。
3. 两字母相同且前一个字母相同，除了可以执行上面的操作之外，还可以多匹配一个。总子串数量 $+1$。

优化：  
设 $p$ 为满足 $\forall x\in[0,p],A_{i-x}=B_{j-x}$ 的最大值，则有：
$$
f_{i,j,k}=\begin{cases}
f_{i-1,j,k}&p=0\\
f_{i-1,j,k}+\sum_{x=1}^{p+1}f_{i-x,j-x,k-1}&p\neq0
\end{cases}
$$
前缀和优化即可。

还有滚动数组优化，第一维 $i$ 可以滚掉。

[AC](https://www.luogu.com.cn/record/176516555) 5.12MB 93ms

状态设计：记录 $A$ 与 $B$ 的当前位置，及匹配子串数，即可唯一确定状态。  
状态转移：逐个字母比较，是否选择当前字符。对先前状态进行加和。

#### T3
[洛谷P4362](https://www.luogu.com.cn/problem/P4362) [NOI2002] 贪吃的九头龙

给定一棵拥有 $n$ 个节点的树，每个节点上有一个果子。九头龙有 $m$ 个头，每个头必须吃至少一个果子。另外，$1$ 号头必须吃掉包括 $1$ 号节点在内的 $k$ 个节点。你需要将这些果子划分给九头龙，划分的难度由每个头吃到的果子中最大和最小编号的差值决定，目标是使最大的难度值最小化。

首先**考虑特殊条件**。  
注意到大头必须同时满足**吃掉一号节点**和**吃掉 $k$ 个节点**，考虑设 $f_{i,j,0/1}$ 表示 $i$ 子树内被**大头**吃掉了 $j$ 个果子，且 $i$ 自身(是/否)被**大头**吃掉。

答案：$f_{1,k,1}$。  
无解情况：头的数量太多，大头吃不到 $k$ 个。

> 如果有 $3$ 个或以上的头，虽然可能有的边连的两个点都没有被**大头**吃掉，但是一定可以通过剩下的头让这条边不被吃掉。

$$
\begin{aligned}
&f_{u,j,0}=\min_{v\in\text{son}_u}
\min_{t=0}^jf_{u,j-t,0}+\begin{cases}\min(f_{v,t,0}+w(u,v),f_{v,t,1})&m=2\\\min(f_{v,t,0},f_{v,t,1})&m\neq2\end{cases}\\
&f_{u,j,1}=\min_{v\in\text{son}_u}
\min_{t=0}^jf_{u,j-t,1}+\min(f_{v,t,0},f_{v,t,1}+w(u,v))
\end{aligned}
$$

注意到 $t=0$ 时自己更新了自己，代码实现方面先计算再赋值。

[AC](https://www.luogu.com.cn/record/176671835) 1.22MB 69ms

状态设计：抓住题目中的特殊要求，对大头设计状态。  
状态转移：从子节点向父节点转移。特别注意自身能否被自身计算，需要提前备份。

#### T4
[洛谷P3177](https://www.luogu.com.cn/problem/P3177) [HAOI2015] 树上染色

给定一棵有 $n$ 个点的树，每条边有权重。要求在树中选择 $k$ 个点染成黑色，其余 $n-k$ 个点染成白色。目标是最大化染色后的收益，该收益等于所有黑色点之间的两两距离之和加上所有白色点之间的两两距离之和。求最大收益值。

> 你统计一个答案 $f$ 和一个深度和 $d$ 是错的，具体原因我还不知道。

考虑将距离转化为路径。路径由边组成，考虑每一条边什么时候做贡献。

一条边做贡献，当且仅当边的两侧有同色点。另外，对于每一个同色点对，边都会做一次贡献。该边做的总贡献次数为两侧同各色点的乘积相加。

设 $v$ 子树中有 $k$ 个黑点，则边 $(u,v)$ 的贡献 $\text{cst}=w(u,v)\times(k\times(n-k)+(\text{siz}_v-k)\times(n-\text{siz}_u+k))$。

设 $f_{u,j}$ 表示 $u$ 子树中选 $j$ 个黑点的最大收益。则：
$$
f_{u,j}=\max_{v\in\text{son}_u}\max_{k=0}^jf_{v,k}+f_{u,j-k}+\text{cst}
$$

注意：优先处理 $k=0$ 的情况，因为如果 $k=0$ 不是最先处理的，$f_{u,j}$ 就会被后面的答案更新为 $\max$，再计算 $f_{v,0}+f_{u,j}+\text{cst}$ 时答案就错了。

[AC](https://www.luogu.com.cn/record/176726938) 22.86MB 173ms

突破口：边的统计次数取决于两侧同色点的数目。  
状态设计：记录当前子树内黑色节点，即可唯一确定边的贡献。  
状态转移：从子节点向父节点转移。

机房里的同学都在 6月17日、18日过了这道题。而我不知道为啥，9月12日才做的 QWQ

#### T5
[洛谷P3146](https://www.luogu.com.cn/problem/P3146) [USACO16OPEN] 248 G | [洛谷P3147](https://www.luogu.com.cn/problem/P3147) [USACO16OPEN] 262144 P

给定一个包含 $N$ 个正整数的序列，范围在 $1$ 到 $40$。每次可以选择两个相邻且相同的数，将它们合并为一个比原来的数大 $1$ 的数。目标是使得合并后序列中的最大值尽可能大。请输出能生成的最大整数。

弱化版：区间 DP  
令 $f_{l,r}=\text{val}$ 表示区间 $[l,r]$ 合并后的值是 $\text{val}$，则有 $f_{l,r}=\max\limits_{k=l}^{r-1}(f_{l,k}+f_{k+1,r})[f_{l,k}=f_{k+1,r}\neq0]$。  
初始值：$f_{i,i}=a_i$。  
注意：非零区间才可以合并，值为零的区间由于不合法无法合并。  
注意：答案不是 $f_{1,n}$，因为这段区间可能无法合并。

强化版：倍增优化 DP  
令 $f_{l,\text{val}}=r$ 表示区间 $[l,r)$ 合并后的值是 $\text{val}$，则有 $f_{l,\text{val}}=f_{f_{l,\text{val}-1},\text{val}-1}$，表示合并区间 $[l,r_1)$ 与 $[r_1,r)$。保证了两段区间的值相同，均为 $\text{val}-1$。  
初始值：$f_{i,a_i=i}$。  
注意：不存在 $\f_{l,\text{val}-1}$ 或不存在 $f_{r_1,\text{val}-1}$，就不可以转移。

[AC](https://www.luogu.com.cn/record/180873182) 62.10MB 161ms

突破口：合并 $2$ 个元素后值 $+1$，值每 $+1$ 就有 $2$ 个元素合并。  
状态设计：将值作为状态，即可出现倍增结构。  
状态转移：上一个值到下一个值，小区间合并为大区间。

---
### 矩阵快速幂
#### T1
[洛谷P2044](https://www.luogu.com.cn/problem/P2044) [NOI2012] 随机数生成器

$X_{n+1}=(aX_n+c)\bmod m$，要求计算并输出 $X_n\bmod g$ 的值。

快速幂+龟速乘

$$
\begin{bmatrix}
a&1\\
0&1
\end{bmatrix}\times\begin{bmatrix}
X_n\\c
\end{bmatrix}=\begin{bmatrix}
X_{n+1}\\c
\end{bmatrix}
$$

[AC](https://www.luogu.com.cn/record/178608595) 668.00KB 36ms

#### T2
[洛谷P2579](https://www.luogu.com.cn/problem/P2579) [ZJOI2005] 沼泽鳄鱼

有一个石墩和石桥的图，石墩之间用石桥相连。给定一个起始石墩和一个目标石墩，以及需要经过的时间单位，计算从起始石墩出发，在规定时间内到达目标石墩的路径数量。

食人鱼在石墩上有周期性的运动，运动周期为 $2$、$3$ 或 $4$ 个单位时间。食人鱼到达石墩时会攻击在上面的人，要求计算的路径中不能与食人鱼在同一时刻到达同一石墩。求从起点到终点恰好经过 $K$ 条石桥的方案数。

邻接矩阵快速幂：恰好 $k$ 道路的方案数。

```cpp
for (int i=1; i<=a.n; ++i) for (int j=1; j<=a.m; ++j) {
	for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+a[i][j]*b[j][k])%mod;
}
```

类似 Floyd。枚举中间节点 $j$，$i\rightsquigarrow k$ 的方案数叠加 $\text{cnt}_{i\rightsquigarrow j}\times\text{cnt}_{j\rightsquigarrow k}$。

对于周期运动，设某只鱼运动到了 $x$，只需 $\forall x\in[1,n],\ cnt_{x\rightsquigarrow i}\leftarrow0$ 即可。

优化：周期为 $12$，考虑每 $12$ 个时间一遍，记作 $A_0\sim A_{11}$。令 $A_{12}\leftarrow\prod\limits_{i=0}^{11}A_i$，则答案为 ${A_{12}}^{\lfloor\frac k{12}\rfloor}\times\prod\limits_{i=0}^{k\bmod12}A_i$。

[AC](https://www.luogu.com.cn/record/179328104) 1.25MB 80ms

---
### 树链剖分
#### T1
[洛谷P3384](https://www.luogu.com.cn/problem/P3384) 重链剖分/树链剖分

如题，已知一棵包含 $N$ 个结点的树（连通且无环），每个节点上包含一个数值，需要支持以下操作：
- `1 x y z`，表示将树从 $x$ 到 $y$ 结点最短路径上所有节点的值都加上 $z$。
- `2 x y`，表示求树从 $x$ 到 $y$ 结点最短路径上所有节点的值之和。
- `3 x z`，表示将以 $x$ 为根节点的子树内所有节点值都加上 $z$。
- `4 x` 表示求以 $x$ 为根节点的子树内所有节点值之和。

太板子了。

记录每个点的重儿子(子树节点数目最大的)，父节点 $\rightarrow$ 重儿子为重边，其它为轻边。则树会被剖成 $O(\log n)$ 条重链和若干轻边。

每个点到根节点只会跳 $O(\log n)$ 条链。对 dfs 序做数据结构，复杂度多带一个 $\log$。

[AC](https://www.luogu.com.cn/record/178414236) 16.39MB 578ms

---
### 卡特兰数
#### T1
[洛谷P2532](https://www.luogu.com.cn/problem/P2532) [AHOI2012] 树屋阶梯

给定一些空心钢材，它们的高度为正整数倍且数量充足。要求从这些钢材中选择 $N$ 个，搭建一个总高度为 $N$ 尺的阶梯，每一步台阶的高度和宽度均为 $1$ 尺。请计算有多少种不同的搭建方法。注意，钢材的空心面不可向上。

答案是卡特兰数的第 $N$ 项。

由于总共用了 $N$ 个方块，找规律发现总有**一个**方块左下角在**第一列的最下方**(即台阶最深处)，右上角在**某一列的最上方**(即台阶面上)。

借助这个方块，我们可以将原台阶分成该方块和两个新台阶。  
根据加乘原理：$\text{ans}_n=\sum\limits_{i=1}^n\text{ans}_{i-1}\times\text{ans}_{n-i}=\sum\limits_{i=0}^{n-1}\text{ans}_i\times\text{ans}_{n-i-1}$。

这个是卡特兰数的公式。

[AC](https://www.luogu.com.cn/record/178335704) Python3 3.72MB 156ms

#### T2
[洛谷P7118](https://www.luogu.com.cn/problem/P7118) Galgame

给定一棵以 $1$ 为根的二叉树，每个节点代表一个场景。每个场景有两个子场景，分别对应选择 $A$ 和选择 $B$。定义两个场景的趣味度比较如下：

1. 如果两个场景能到达的不同场景总数不同，趣味度高的场景更有趣。
2. 如果两个场景的 $A$ 子场景不同，趣味度高的 $A$ 子场景更有趣。
3. 否则比较 $B$ 子场景的趣味度。

两个场景被认为本质相同，当且仅当它们的 $A$ 子场景和 $B$ 子场景均相同。趣味度是所有本质不同且不比当前场景有趣的场景数量。要求输出趣味度对 $998244353$ 取模的结果。

> 本题有思路更为直接的生成函数做法，但是我不会。

卡特兰数 $C_n$ 有一个意义：$n$ 个节点组成的不同的二叉树数目为 $C_n$。

考虑 Galgame $X$ 比给定的 Galgame $Y$ **更无趣**，有以下几种可能：
1. 总大小更小：$\text{siz}_X<\text{siz}_Y$。对答案的贡献 $\sum\limits_{i=0}^{n-1}C_i$，其中 $i$ 表示总节点数大小。
2. 总大小相同：$\text{siz}_X=\text{siz}_Y$。
   1. 左子树大小更小：$\text{siz}_{ls_X}<\text{siz}_{ls_Y}$。对答案的贡献 $\sum\limits_{i=0}^{\text{siz}_{ls}-1}C_i\times C_{n-i-1}$，其中 $i$ 表示左子树大小。
   2. 左子树大小相同：$\text{siz}_{ls_X}=\text{siz}_{ls_Y}$。
      1. 左子树更无趣：递归处理左子树，乘上权值(倍率) $C_{n-\text{siz}_{ls}}$，因为右子树可以随便选。
      2. 右子树更无趣：递归处理右子树，乘上权值(倍率) $1$，因为左子树必然同构，每个右子树对于一种答案。

[AC](https://www.luogu.com.cn/record/178345415) 8.73MB 24ms

---
### 搜索
#### T1
[洛谷P4799](https://www.luogu.com.cn/problem/P4799) [CEOI2015 Day2] 世界冰球锦标赛

给定 $n$ 场冰球比赛和一个预算 $m$，每场比赛的门票价格不同。你需要计算所有不超过预算的观赛方案数。每场比赛要么选择观看，要么不观看，不同的选择组合视为不同方案。  
数据范围：$1\le n\le40$。

$2^{40}$ 暴力显然不可取，考虑优化。

先 $2\times2^{20}$ 暴力处理出前 $20$ 场和后 $20$ 场各自的**观看情况**和**价格**，存到 `map` 中。  
接下来，对于每个前 $20$ 场情况，设其价格为 $m_1$，那么后 $20$ 场的预算就是 $m-m_1$。  
价格升序排序，二分查找 $m-m_1$ 对应价格的位置，那么它前面的、花费比它小的答案都可取。  
时间复杂度 $O(2^n\log n)$。

[AC](https://www.luogu.com.cn/record/177418904) 2.94MB 53ms

这种 Trick 叫 Meet in the Middle，通常适用于“答案计数、有界、可合并”的情况。

#### T2
[洛谷P1514](https://www.luogu.com.cn/problem/P1514) [NOIP2010 提高组] 引水入城

在一个 $N \times M$ 的矩形区域中，每个城市有一个海拔高度。只允许在第 $1$ 行与湖泊接壤的城市建造蓄水厂，其它城市只能建造输水站。输水站能将水从高海拔城市输送到低海拔城市。目标是确保第 $N$ 行的所有城市都有水利设施。如果可能，输出最少需要的蓄水厂数量；如果不可能，输出无法建有水利设施的干旱区城市数量。

一个十分重要的性质：在**有解**的情况下，蓄水厂可灌溉区间总是连续的。即，蓄水厂不存在“交叉灌溉”的情况。  
DP (记忆化搜索)维护每个点向下能到达最左/最右的点，$O(n\times n^2)$ 的 BFS 可优化至 $O(n^2)$。

[AC](https://www.luogu.com.cn/record/177432579) 8.49MB 63ms

#### T3
[洛谷P2831](https://www.luogu.com.cn/problem/P2831) [NOIP2016 提高组] 愤怒的小鸟

在平面上有 $n$ 只小猪，位置为 $(x_i, y_i)$。每只小鸟的飞行轨迹为 $y=ax^2+bx$，其中 $a<0$。要求确定最少需要多少只小鸟才能消灭所有小猪。

状态压缩 DP。记 $\text{hit}_{i,j}$ 表示经过 $i$、$j$ 两点所能经过的点的集合(待定系数法预处理)，$f_S$ 表示解决掉集合 $S$ 的猪花费的最小代价，则有：
1. $f_\emptyset=0$，表示解决掉空集不需要鸟。
2. $f_{S|\text{hit}_{i,j}}=\min(f_{S|hit_{i,j}},\ f_S+1)$，表示一只鸟可以打一条抛物线，“原集”并上“抛物线”可以多发一次解决掉。
3. $f_{S|x}=\min(f_{S|x},\ f_{S}+1)$，表示任意一点都有一条抛物线经过，一只鸟可以打掉一只猪。

第三种转移方式：如果猪活着的数量只有一个，第二种转移不能得到答案。

[AC](https://www.luogu.com.cn/record/177439929) 8.45MB 353ms

#### T4
[洛谷P1849](https://www.luogu.com.cn/problem/P1849) [USACO12MAR] Tractor S

在二维平面上，给定一个拖拉机的起始坐标和若干干草堆的坐标。拖拉机只能沿坐标轴移动，且不能停留在干草堆的坐标上。请计算将拖拉机移动回原点所需最少移走的干草堆数量。  
注意：二维平面无限，即，第 $0$ 行、第 $0$ 列、第 $1001$ 行、第 $1001$ 列均可通行。

SPFA 能过，但是这题可以 01-BFS。

建网格图，进入“干草堆方块”的边权设为 $1$，进入“空方块”的边权为 $0$。从起始点到 $(0,0)$ 的最短路即为代价。  
注意到此时边权只有 $0$ 或 $1$ 两种情况，使用 01-BFS 即可。具体地，在朴素 BFS 基础上，通过 $1$ 边权扩展的插到队尾，通过 $0$ 边权扩展的插到队头，即可维持 `deque` 的单调性。

[AC](https://www.luogu.com.cn/record/180869369) 56.37MB 861ms

---
### 简单题
#### T1
[洛谷P1955](https://www.luogu.com.cn/problem/P1955) [NOI2015] 程序自动分析

给定多个独立的约束满足问题，每个问题包含 $n$ 个形如 $x_i=x_j$ 或 $x_i\neq x_j$ 的约束条件。需要判断能否为每个变量赋值，使得所有约束条件同时成立。如果可以，则输出 `YES`，否则输出 `NO`。

扩展域并查集/01异或加权并查集/二分图01染色……

[AC](https://www.luogu.com.cn/record/176746925) 3.98MB 681ms

---
### 未分类
#### T
[洛谷P1439](https://www.luogu.com.cn/problem/P1439) 最长公共子序列

给定两个 $1$ 到 $n$ 的排列 $P_1$ 和 $P_2$，要求计算它们的最长公共子序列的长度。

$O(n^2)$ 的 DP 十分朴素，考虑 $O(n\log n)$ 做法。

> 将序列 $A$ 中所有元素在序列 $B$ 中的位置按照降序排列，形成一个新的序列。这个新序列的最长严格递增子序列即为 $A$ 和 $B$ 的最长公共子序列。

接下来套用最长上升子序列二分/树状数组的 $O(n\log n)$ 做法即可。

[AC](https://www.luogu.com.cn/record/176768397) 3.32MB 54ms

#### T
[洛谷P4395](https://www.luogu.com.cn/problem/P4395) [BOI2003] Gem 气垫车 | [洛谷P5765](https://www.luogu.com.cn/problem/P5765) [CQOI2005] 珠宝

给定一棵树，要求为树的每个结点分配一个正整数权值，且相邻结点的权值不能相同，目标是使整棵树的总权值最小。输入包括结点数量和结点间的连接关系，输出为最小的总权值。

先考虑 DP。  
注意到一个点的答案只取决于相邻的点，而点只有颜色这一种信息，所以设 $f_{u,j}$ 表示节点 $u$ 填 $j$，子树的最小答案。  
**子树之间互不影响**，所以可以贪心地取每个子树的最小答案。

设树上最大点权为 $L$，则有：  
$$
\begin{aligned}
f_{u,j}&=j+\min\sum_{v\in\text{son}_u\land k\neq j}f_{v,k}\\
&=j+\sum_{v\in\text{son}_u}\min_{k\neq j}f_{v,k}
\end{aligned}\hspace{0.2cm}
$$

其中，$i,j\in[1,L]$。

注意到最大点的最大颜色是有限的，且与点的规模呈正相关。具体地，这个上限是 $\log_2n+1$。证明可以看 [这篇题解](https://www.luogu.com.cn/article/s19nq02q)。

[AC](https://www.luogu.com.cn/record/181242380) 6.60MB 89ms

#### T
[洛谷P5658](https://www.luogu.com.cn/problem/P5658) [CSP-S2019] 括号树

给定一棵树，要求统计从根结点到每个结点的路径上，有多少个不同的合法括号串子串。输入包括结点数量、每个结点的括号和父结点信息，输出为每个结点的路径上合法括号串子串数量的加权异或和。

先考虑当树是一条链时，

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
