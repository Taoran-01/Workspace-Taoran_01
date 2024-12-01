
#### T
<!-- Trick -->
[洛谷P11244](https://www.luogu.com.cn/problem/P11244) 吻秋

问题描述：有多个长度为n的整数序列，进行q次操作。操作包括两种类型：  
1. 合并两个序列，排序后更新原序列。  
2. 查询某个序列的第j个元素。

性质：两个序列经过一次合并后值域上至多只有一个值的交。  
这是值域优化的暴力复杂度正确的前提。

合并时暴力合并即可。若序列未排序则将其排序，若值域非包含关系则仅处理交集。

[AC](https://www.luogu.com.cn/record/186701105) 15.71MB 603ms

#### T
<!-- 反悔贪心 -->
[洛谷P2949](https://www.luogu.com.cn/problem/P2949) [USACO09OPEN] Work Scheduling G

给定多个工作，每个工作有一个截止时间和利润。每个工作需要1个单位时间，目标是选择最多的工作，使得在不超过其截止时间的前提下，获得最大利润。

反悔贪心。先贪心地将能选择的所有工作选择上，并加入堆中。遇到不能选择的，判断是否优于对顶。  
若优，则撤下对顶，换上当前工作。这样对总体的答案来说是不劣的。

[AC](https://www.luogu.com.cn/record/186721720) 3.31MB 92ms

#### T
<!-- 暴力枚举模拟 -->
[洛谷P1315](https://www.luogu.com.cn/problem/P1315) [NOIP2011 提高组] 观光公交

在一座城市中有多个景点和一个观光公交车。每个游客从一个景点到另一个景点需要乘车。公交车可以通过加速器减少行驶时间，目标是最小化所有游客的总旅行时间。

暴力。预处理每一个站点的到达时间，每次枚举加速区间，计算能够减少的最多旅行时间。

[AC](https://www.luogu.com.cn/record/186763470) 688.00KB 334ms

#### T
<!-- 根号分治 -->
[AT_arc160_b](https://atcoder.jp/contests/arc160/tasks/arc160_b) Triple Pair | [洛谷](https://www.luogu.com.cn/problem/AT_arc160_b)

给定一个正整数 $n$，求满足特定条件的有序三元组 $(x,y,z)$ 的个数。条件是每对乘积 $xy$、$xz$、$yz$ 都不超过 $n$。

首先计算 $x,y,z\le\lfloor\sqrt n\rfloor$ 的情况，共有 $\lfloor\sqrt n\rfloor^2$ 种。

接下来，不妨设 $x>\sqrt n>y,z$，此时一定有 $yz\le n$。为保证 $xy\le n\land xz\le n$，有 $y,z\in[1,\frac nx]$。所以方案数为 $\lfloor\frac nx\rfloor^2$。  
考虑 $x$ 的位置有三个，故这一种答案 $\times3$。

最终答案为：
$$
\lfloor\sqrt n\rfloor+\sum_{x=\lceil\sqrt n\rceil}^n\lfloor\frac nx\rfloor^2
$$

整除分块求解即可，时间复杂度 $O(T\sqrt n)$。

[AC](https://atcoder.jp/contests/arc160/submissions/59441969) 3.68MB 25ms

> 机房里的其它做法：
> 1. 二分，$O(T\log n)$。
> 2. 枚举中间的数，只需要保证中间的数 $\le\sqrt n$ 就有解。

#### T
<!-- 二分+最短路 -->
[洛谷P1462](https://www.luogu.com.cn/problem/P1462) 通往奥格瑞玛的道路

有多个城市和双向公路，城市间的通行有血量消耗 $c_i$，且每个城市需要支付过路费 $f_i$。目标是找出最小的最大过路费，保证从起点城市到终点城市的血量消耗不超过给定值。如果无法到达终点，则输出"AFK"。

二分代价的最大值，每次都跑一遍 Dijkstra。仅 $f_i\le\text{mid}$ 的点参与最短路，判断血量消耗即可。

时间复杂度 $O(m\log V\log n)$

[AC](https://www.luogu.com.cn/record/186905204) 2.82MB 390ms

#### T
<!-- 分层图+最短路 -->
[洛谷P4568](https://www.luogu.com.cn/problem/P4568) [JLOI2011] 飞行路线

城市之间有航线，某些航线免费。给定起点和终点，求最少的旅行费用。最多可以免费乘坐 $k$ 条航线。其中，$0\le k\le10$。

注意到 $k$ 非常小，考虑建分层图。层间与层内连原图的边，层间的边代价为 $0$，$k$ 是多少就建多少层。从第一层的起点跑单源最短路，每一层终点距离的最小值即为答案。

[AC](https://www.luogu.com.cn/record/186952074) 27.48MB 199ms

#### T
<!-- 对偶图+最短路 -->
[洛谷P4001](https://www.luogu.com.cn/problem/P4001) [ICPC-Beijing 2006] 狼抓兔子

在一个网格上，有三种方向的道路连接不同点。每条道路上有一个权值表示最大通行能力。求从起点到终点经过的道路中，参与最小狼数的方案。

平面图最小割问题。

平面图判定：不存在 $K_5$ 或 $G_{3,3}$，即 $5$ 个点的完全图和 $3-3$ 的完全二分图。  
网格图是一种平面图。

对偶图：平面图上的“面”视作“点”，分割“面”的“边”作为连接“点”的“边”，边权不变。

法一：最大流=最小割。建图后跑 Dinic 即可。  
法二：平面图上，对偶图最短路=原图最小割。建原图的对偶图，在对偶图上跑最短路。

[AC](https://www.luogu.com.cn/record/186960593) 92.48MB 475ms

#### T
<!-- 并查集/二分图染色 -->
[洛谷P11124](https://www.luogu.com.cn/problem/P11124) [ROIR 2024 Day 2] 数组划分

给定一个正整数数组，要求把数组元素涂成两种颜色，满足同色的元素不能互为一个素数的倍数。输出一个合法的涂色方案。

先筛出所有质数，再使用带权或扩展域并查集扫一遍数组，维护出相同/对立关系。

还可以建二分图，再遍历染色。

[AC](https://www.luogu.com.cn/record/187081080) 13.45MB 170ms

#### T
<!-- 根号分治 -->
[洛谷P10761](https://www.luogu.com.cn/problem/P10761) [BalticOI 2024] Trains

有 $N$ 个城市，部分城市有单轨列车可用。每个列车每次能停几个站。计算从第一个城市出发，能到达的不同城市序列的数量。  
列车每隔 $d_i$ 个站停靠一次，共停靠 $x_i+1$ 站。仅第 $1$ 站可以上车，第 $2$ 站至第 $x_i+1$ 站可以下车。

先列出朴素 DP 转移方式：$f_j=\sum f_i$，满足从 $i$ 到 $j$ 有至少一趟列车。

对于这道题而言，走几站下一站，就相当于向模 $d_i$ 同余 $i$ 的地方转移。细化方程：

$$
f_j=\begin{cases}
1&j=1\\
\sum\limits_{i=1}^{j-1} f_i[j\equiv i\pmod{d_i}\land \frac{j-i}{d_i}\le x_i]&j\neq 1
\end{cases}
$$

对于这种模数类的题目，对 $d_i$ 分治，分界点为 $B$。后面会证明 $B=\sqrt{n}$。

开一个数组 $\text{tag}_{q,r}$，表示对于所有的 $j$，满足 $j\operatorname{mod}q=r$，$f_j$ 都需要加上 $\text{tag}_{q,r}$。  
$q,r\in[1,B)$

首先考虑 $\forall i\in[1,n],\ x_i=+\infty$ 的情况。
1. 先处理当前答案 $f_i\leftarrow f_i+\sum\limits_{q=1}^{B-1}\text{tag}_{q,i\operatorname{mod}q}$，表示当前车站的答案等于暴力转移的答案 $f_i$ 加上从同余点转移的答案 $\text{tag}_{q,r}$。
2. 如果 $d_i\ge B$，则列车 $i$ 在所有的 $1\sim n$ 中至多停靠 $O(\frac nB)$ 量级的车站，暴力处理 $f_j\leftarrow f_j+f_i$。
3. 如果 $d_i<B$，$\text{tag}_{d_i,i}\leftarrow\text{tag}_{d_i,d_i\operatorname{mod}i}+f_i$，表示之后所有模 $d_i$ 同余 $i$ 的车站都可以从 $i$ 转移，需要加上答案 $f_i$。

暴力转移时间复杂度 $O(n\times\frac nB)$，空间复杂度 $O(1)$；同余转移时间复杂度 $O(1)$，空间复杂度 $O(B^2)$。  
故 $B=\sqrt n$ 时时间复杂度有最优的 $O(n\sqrt n)$。

对于 $x_i\neq+\infty$ 的情况，只需要在 $x_i$ 之后将 $\text{tag}_{p,q}$ 复原即可。  
维护差分数组 $\text{seq}_n$，每次先执行 $\text{seq}_i$ 的操作，同余转移后在 $i+d_i\times x_{i}+1$ 位置打上标记，表示在那个位置将 $\text{tag}_{d_i,d_i\operatorname{mod}i}$ 位置减去 $f_i$，移除过期标记。

最终的答案即为 $\sum\limits_{i=1}^nf_i$。

[AC](https://www.luogu.com.cn/record/187080860) 5.25MB 280ms

SDSC原题弱化版，机房里的都会做，没有补题吃亏了 QWQ

#### T
<!-- 可并堆维护树上贪心 -->
[洛谷P7925](https://www.luogu.com.cn/problem/P7925) [EVOI-RD2] 童年 | [洛谷P10759](https://www.luogu.com.cn/problem/P10759) [BalticOI 2024] Jobs

给定一棵树，树上的每个节点 $u$ 都有整数权值 $a_u$，有正有负。你需要从 $n$ 个节点中选择任意多个，最大化总权值。  
节点的选择有条件，选择节点 $u$ 的前提时选择父节点 $\text{fa}_u$。  
有初始价值，节点操作后价值根据节点权值更新。任何时刻的价值都必须是非负的。

进入一棵子树，当且仅当该子树最终能够“挣回来”代价。即，进入子树获益 $>$ 进入子树代价。  
除此之外，由于“本金”的限制，进入子树**获益**有“最低门槛”。  
将获益的最低门槛加入小根堆中，每次贪心地取出堆顶进到子树获益。这样，持续收益而本金变高，行动能力增强，对于总问题是更优的。

剩下的看题解，讲得较详细。两道题的数篇题解都有通病。看题解前后，读一遍下面的：
1. 递归回溯过程中，子树的 $f$ 已处理完
2. 维护 $\text{cur}$/$\text{sum}$/$\text{num}$/$\dots$(题解里各种各样的) 目的是优先取子树刚做出来的贡献。
   贪心地取新产生的贡献，先吃自己的再吃父亲的，最小化进入代价。
3. $f[u]$ 相当于一个槛，维护子树需求的最大值。
4. 写代码时分清“代价限制”与“净代价”。

P7925 [AC](https://www.luogu.com.cn/record/187124320) 1.48MB 20ms

考虑如何优化。每一次到子树都更新 $f_v$，浪费了大量信息。收益后、离开前，考虑将子树中的剩余节点保存，下次前来时利用其中的信息。使用可并堆维护即可。

P10759 [AC](https://www.luogu.com.cn/record/187148836) 34.66MB 483ms

如果你过不去 Subtask 1：
1. 检查是否开了 `long long`。
2. 检查最大值是否开够，需要 $8$ 个 $\texttt{3f}/\texttt{7f}$。
3. 在弱化版中，`dfs` 前可以判断 `if (a[u]>=0) return;`，表示取完父节点就走。  
   而在加强版中，由于 `prof[]` 的记录，每个点都需要走完。

#### T
<!-- 图论+状压DP -->
[洛谷P3959](https://www.luogu.com.cn/problem/P3959) [NOIP2017 提高组] 宝藏

有 $n$ 个宝藏点，$m$ 条宝藏点之间的路段，每条路段有一个开凿费用。选择一个宝藏点作为起点，并决定修建哪些路段以访问所有宝藏，使得总费用最小。  
数据范围：$1\le n\le12$，$0\le m\le10^3$。

设 $f_{S,i}$ 表示当前最小生成树中有点集 $S$，树高为 $i$，即可唯一确定“最优子结构”。

剩下的看扶苏的[题解](https://www.luogu.com.cn/article/lifylaaf)。

简单说一下拓展边集 $G_S$ 的求法。$G_S$ 应为从 $S$ 出发、到达 $C_US$ 的边集，$S$ 之内的边可以不计算。  
另外，我们其实只需要关注连到 $C_US$ 的终点，所以拓展边集可以进一步缩减至 $O(N)$ 量级。

[AC](https://www.luogu.com.cn/record/187219941) 972.00KB 1.25s

#### T
<!-- 图论+数据结构 -->
[洛谷P6845](https://www.luogu.com.cn/record/187460353) [CEOI2019] Dynamic Diameter | [CF1192B](http://codeforces.com/problemset/problem/1192/B) Dynamic Diameter [洛谷](https://www.luogu.com.cn/problem/CF1192B)

给定一棵带权树，进行 $q$ 次操作，每次修改一条边的权值，并求修改后树的直径上的边权和。所有操作必须在线完成。

非常好的 DS + 图论 题！

注意：DFS 序上连续的一段区间不一定在树上联通，因为可能没有父节点。

首先考虑不带修改操作：

经典 Trick：两棵树(虚实均可，点无需联通)合并后的直径的两端点一定在原树各直径的四个端点中。  
考虑树上任意一个点的最大距离点是直径的两个端点之一，不难证明结论成立。

对整棵树的 DFS 序列建线段树，维护一个信息：该(虚)树直径的两个端点。  
这样，区间的信息就可以合并了。一共有 $\begin{pmatrix}4\\2\end{pmatrix}=6$ 种可能，一次 `pushup` 需要对这六种可能的直径取最大的。

接下来考虑边的修改：

对于 $u=\text{fa}_v$，考虑边 $(u,v)$ 的权值修改后，各(虚)树是否可能受到影响：
1. $\text{Subtree}_v$ 不受影响；
2. $T-\text{Subtree}_v$ （即除了 $v$ 子树以外的部分）不受影响；
3. 剩下的全部可能受影响，即点既有在 $\text{Subtree}_v$ 内的，也有不在的。

转换到 DFS 序上，$\text{Subtree}_v$ 在 $[\text{st}_v,\text{ed}_v]$ 上，受影响的子树区间是跨过 $\text{st}_v$ 或 $\text{ed}_v$。这些区间内的点被区间修改时 `modify` 函数的遍历区间恰好包含。所以直接对这些区间重新 `pushup` 即可。

[AC](https://www.luogu.com.cn/record/187460353) 26.79MB 3.34s

#### T
<!-- 暴力DP -->
[洛谷P1941](https://www.luogu.com.cn/problem/P1941) [NOIP2014 提高组] 飞扬的小鸟

在一个二维平面内，有小鸟从左侧开始飞行并要穿过一些障碍物。小鸟可以点击屏幕上升或不点击下降，不同位置的上升和下降高度不同。求最少的点击次数使小鸟成功通过所有障碍；若无法通过，输出最多能通过的障碍数量。

暴力 DP。记 $f_{i,j}$ 表示从 $(i,j)$ 这个点飞过来所需要的最小点击数，可以从整数点击和不点击自由下落转移。特别判断是否到达顶端 $m$，在 $m$ 跳多少次都会锁在 $m$。

[AC](https://www.luogu.com.cn/record/187479630) 940.00KB 1.77s

#### T
<!-- 简单题 -->
[洛谷P2312](https://www.luogu.com.cn/problem/P2312) [NOIP2014 提高组] 解方程

给定一个多项式方程，找出它在区间 $[1,m]$ 内的整数解。

构建数值哈希函数，判断对于每个 $x\in[1,m]$ 是否成立。  
利用秦九韶公式可以简化代码。具体地，次数从高到低处理，每多处理一个数就乘上 $x$。

不可以用快速幂或双模数哈希，会被卡时间。

[AC](https://www.luogu.com.cn/record/187487535) 940.00KB 1.77s

#### T
<!-- 性质题 -->
[洛谷P2827](https://www.luogu.com.cn/problem/P2827) [NOIP2016 提高组] 蚯蚓

给定 $n$ 只蚯蚓，每秒将最长的蚯蚓按比例切分成两只，并使剩下的蚯蚓每只长度增加 $q$。持续 $m$ 秒。

首先考虑暴力，使用大根堆维护。每次从堆顶取出长度最大的蚯蚓，将其切成两半后放回堆中。堆内其它元素长度累加。时间复杂度 $O(nm\log n)$，不现实。  
考虑“时间静止”：堆内元素累加，相当于被切的蚯蚓长度减小。保持所有长度不变，仅在操作蚯蚓 / 统计答案时还原长度。时间复杂度 $O(m\log n)$。

接下来，优先队列成为复杂度的瓶颈，冲不过 $7\times10^6$。  
注意到蚯蚓是按比例切开的。也就是说，感性理解，两段**长度递增**的蚯蚓，在**相同比例位置**切开后**长度依旧递增**。加上题目背景，先切开的先“倍速增长”，后切开的自然追不上。严格证明见 dbxxx 的[题解](https://www.luogu.com.cn/article/hgnmtohe)。  
于是我们可以先将蚯蚓降序排序，放到队列 $\text{q1}$，切开后两段分别放到 $\text{q2}$ 和 $\text{q3}$。这样，队列始终是从队头到队尾单调递减的。取蚯蚓从三个队头中选最大的，按类型插入三个队中。

[AC](https://www.luogu.com.cn/record/187771287) 29.29MB 1.42s

#### T
<!-- 简单题 -->
[洛谷P2822](https://www.luogu.com.cn/problem/P2822) [NOIP2016 提高组] 组合数问题

给定整数 $t$、$k$ 和若干组 $(n, m)$，对于每组 $(n, m)$，求 $0 \leq i \leq n, 0 \leq j \leq \min(i, m)$ 中有多少对 $(i, j)$ 满足 $k \mid \binom{i}{j}$。

递推预处理组合数及答案前缀和，直接计算即可。  
特别注意 `sum[i][i+1]=sum[i][i];`。

[AC](https://www.luogu.com.cn/record/188088779) 54.95MB 818ms

#### T
<!-- 贪心 交换法 -->
[洛谷P1080](https://www.luogu.com.cn/problem/P1080) [NOIP2012 提高组] 国王游戏

有 $n$ 位大臣排队，国王在前面。每位大臣拥有左右手数值。每位大臣的奖赏为排在他前面所有人左手数的乘积除以其右手数。重新排列队伍，使得奖赏最多的大臣的奖赏尽量少。输出最小可能的最大奖赏。

临项交换法求解。

设排序后第 $i$ 个人左右手上的数分别为 $a_i$、$b_i$，则第 $i$ 个人获益 $\lfloor\frac{\prod_{j=1}^{i-1}a_j}{b_i}\rfloor$，第 $i+1$ 个人获益 $\lfloor\frac{\prod_{j=1}^ia_j}{b_{i+1}}\rfloor$。交换后，第 $i$ 个人获益 $\lfloor\frac{\prod_{j=1}^ia_j}{b_{i+1}}\rfloor$，第 $i+1$ 个人获益 $\lfloor\frac{\prod_{j=1}^{i+1}a_j}{b_i}\rfloor$。

交换前比交换后更优，当且仅当：
$$
\begin{aligned}
\max(\lfloor\frac{\prod_{j=1}^{i-1}a_j}{b_i}\rfloor,\lfloor\frac{\prod_{j=1}^ia_j}{b_{i+1}}\rfloor)&<\max(\lfloor\frac{\prod_{j=1}^ia_j}{b_{i+1}}\rfloor,\lfloor\frac{\prod_{j=1}^{i+1}a_j}{b_i}\rfloor)\\
\max(\lfloor\frac1{b_i}\rfloor,\lfloor\frac{a_i}{b_{i+1}}\rfloor)&<\max(\lfloor\frac1{b_{i+1}}\rfloor,\lfloor\frac{a_{i+1}}{b_i}\rfloor)\\
\max(b_{i+1},a_ib_i)&<\max(b_i,a_{i+1}b_{i+1})
\end{aligned}
$$

[AC](https://www.luogu.com.cn/record/188099991) Python3 3.95MB 191ms

#### T
<!-- 简单题 -->
[洛谷P1209](https://www.luogu.com.cn/problem/P1209) [USACO1.3] 修理牛棚 Barn Repair

给定牛棚数 $s$ 和牛的分布， Farmer John 可用至多 $m$ 块木板覆盖有牛的牛棚，要求覆盖的最小总长度。

先不计数量以最小长度补上缺口，再将小块连成大块满足数量要求。  
每次贪心地取最小的空隙填补。

[AC](https://www.luogu.com.cn/record/188102870) 664.00KB 30ms

#### T
<!-- 简单题 -->
[洛谷P1970](https://www.luogu.com.cn/problem/P1970) [NOIP2013 提高组] 花匠

给定一排花的高度序列，移除部分花，使得剩下的花高度形成特定的高低交替模式，最多能保留多少株花。

不难证明，波峰/波谷计数可直接作为答案，且不劣于选择中间点。

[AC](https://www.luogu.com.cn/record/188121055) 740.00KB 93ms

#### T
<!-- 简单题 -->
[洛谷P1311](https://www.luogu.com.cn/problem/P1311) [NOIP2011 提高组] 选择客栈

有 $n$ 家客栈，按色调编号并各自有最低消费。两人想住在色调相同但不同的客栈，且希望两家之间有一家咖啡店的最低消费不高于 $p$。问共有多少种住宿方案满足此条件。

比较简单的做法是，处理出所有可能情况计数，再减去不跨过廉价咖啡店的计数。每次到达廉价咖啡店就统计并清空数据。  
题解里有直接做的，题太简单没细看。

时空限度极宽，无需担心常数。

[AC](https://www.luogu.com.cn/record/188123896) 1.95MB 61ms

#### T
<!-- 二分答案 -->
[洛谷P2678](https://www.luogu.com.cn/problem/P2678) [NOIP2015 提高组] 跳石头

给定一条起点和终点之间有若干岩石的河道，最多可移除 $M$ 块岩石，使跳跃距离尽可能长。计算最短跳跃距离的最大值。

二分答案模板题。二分最小距离，判断移除的石头块数能否满足要求。

贪心地删去石头。当前石头需要被删去，**当且仅当上一块石头到这一块的距离 $<\text{mid}$**。  
代码中维护坐标 $\text{lst}$ 即可。

感性理解，相当于上一块空隙“向后合并”。由于贪心是从前向后的，故答案不劣。

[AC](https://www.luogu.com.cn/record/188134483) 676.00KB 46ms

使用优先队列维护贪心是错误的，因为不知道当前空段要向哪边合并。

```
26 3 2
10
13
17

答案 13
间隔 10 3 4 9
向大的合并√ 10 3 4 9 -> 13 4 9 -> 13 13 (ans=13)
向小的合并× 10 3 4 9 -> 10 7 9 -> 10 16 (ans=10)
```

```
9 2 1
2
5

答案 4
间隔 2 3 4
向小的合并√ 2 3 4 -> 5 4 (ans=4)
向大的合并× 2 3 4 -> 2 7 (ans=2)
```

#### T
<!-- 简单二维DP -->
[洛谷P3126](https://www.luogu.com.cn/problem/P3126) [USACO15OPEN] Palindromic Paths G | [CF570E](https://codeforces.com/problemset/problem/570/E) Pig and Palindromes [洛谷](https://www.luogu.com.cn/problem/CF570E)

设 $f_{i,j,k,l}$ 表示从 $(1,1)$ 到 $(i,j)$、从 $(n,m)$ 到 $(k,l)$ 字母相同的路径个数。  
初始状态：$f_{1,1,n,m}=1$  
转移方式：

$$
f_{i,j,k,l}=\begin{cases}
0&a_{i,j}\neq a_{k,l}\\
\begin{aligned}
&f_{i-1,j,k+1,l}\ [i\neq1\land k\neq n]\\
+&f_{i-1,j,k,l+1}\ [i\neq1\land l\neq m]\\
+&f_{i,j-1,k+1,l}\ [j\neq1\land k\neq n]\\
+&f_{i,j-1,k,l+1}\ [j\neq1\land l\neq m]
\end{aligned}&a_{i,j}=a_{k,l}
\end{cases}
$$

时间复杂度：$O(n^4)$。  
空间复杂度：$O(n^4)$。

初学二维 DP 时遇见的 Trick：  
路径长度相等，则有 $i+j+k+l=(n+1)+(m+1)$，所以 $l$ 可由 $i,j,k$ 推得。  
优化时空复杂度到 $O(n^3)$。注意到 $i$ 一维度仅与上一行有关，滚动数组优化空间至 $O(n^2)$。

[AC](https://codeforces.com/problemset/submission/570/291145545) 3.04MB 1.93s

#### T
<!-- 简单背包 -->
[洛谷P1833](https://www.luogu.com.cn/problem/P1833) 樱花

混合背包模板。

多重背包二进制拆分成 0/1 背包，转移时 0/1 背包和完全背包分类处理。

[AC](https://www.luogu.com.cn/record/188312720) 680.00KB 46ms

#### T
<!-- 分组背包 -->
[洛谷P1064](https://www.luogu.com.cn/problem/P1064) [NOIP2006 提高组] 金明的预算方案

带限制背包。

每一个“$1$ 主件+$k$ 配件组合”二进制枚举拆成 $2^k$ 组。  
总共可选任意多组，但一组只能选择一种。分组背包解决。

[AC](https://www.luogu.com.cn/record/188312720) 680.00KB 46ms

#### T
<!-- SCC缩点 -->
[洛谷P3627](https://www.luogu.com.cn/problem/P3627) [APIO2009] 抢掠计划

SCC 缩点，转化为 DAG 上的问题。建反图，跑 DP (记忆化搜索)即可。

[AC](https://www.luogu.com.cn/record/188342118) 67.79MB 593ms

### T
[洛谷P2515](https://www.luogu.com.cn/problem/P2515) [HAOI2010] 软件安装

SCC 缩点。由于每个点只有一个前驱，**缩点后是森林**。建立超级源点后转化为树上背包，和 [选课](https://www.luogu.com.cn/problem/P2014) 一样。

设 $f_{u,j}$ 表示 $u$ 子树花 $j$ 容量所能获得的最大收益，每个子节点遍历容量看能否优化当前容量的答案。

注意：选择子节点的前提是选择父节点，所以转移时注意循环范围。  
枚举父节点剩余容量时，从“选择当前节点”开始。子节点容量必须在“剩余容量”以下。

[AC](https://www.luogu.com.cn/record/188551554) 680.00KB 70ms

### T
[洛谷P2403](https://www.luogu.com.cn/problem/P2403) [SDOI2010] 所驼门王的宝藏

建图，转化为 [抢掠计划](https://www.luogu.com.cn/problem/P3627)。

相邻 $8$ 个点暴力建边。对于通向整行/整列的，考虑用一个虚点指向该行/列上所有的点，边数即可从 $O(n^2)$ 量级降至 $O(n)$。方法同 [车站分级](https://www.luogu.com.cn/problem/P1983)。

点量级 $O(c_1n)$，有向边量级 $O(c_1c_2n)$，其中 $c_1=3$，$c_2=8$。

[AC](https://www.luogu.com.cn/record/188737021) 33.77MB 1.16s

#### T
[洛谷P1600](https://www.luogu.com.cn/problem/P1600) [NOIP2016 提高组] 天天爱跑步

树上差分+线段树合并。

考虑一个路线什么时候对一个观察点做贡献。
1. 路线 $[s,t]$ 在下降过程中（即，$s\rightsquigarrow\text{lca}$），对 $u$ 做贡献，当且仅当路径经过 $u$，且 $\text{dep}_s-w_u=\text{dep}_u$，移项得 $\text{dep}_s=\text{dep}_u-w_u$。
2. 路线 $[s,t]$ 在下降过程中（即，$\text{lca}\rightsquigarrow t$），并不方便统计。因为对于第一种，从 $s$ 出发的时间是确定的 $0$，而第二种从 $\text{lca}$ 出发的时间并不确定。  
   考虑将路径“翻上去”：将 $s$ 翻到 $\text{lca}$ 的上方。令 $\text{nt}=\text{dep}_\text{lca}-(\text{dep}_x-\text{dep}_\text{lca})$，即翻上去之后点 $s_1$ 的深度。  
   路径对 $u$ 做贡献，当且仅当路径经过 $u$，且 $nt+w_u=\text{dep}_u$，移项得 $nt=\text{dep}_u+w_u$。

对于 $\text{lca}$ 对 $u$ 的贡献，钦定 $\text{lca}$ 位于上升段上，对差分过程微调即可完成去重。

首先建值域 $[-n,n]$ 的动态开点权值线段树，第 $u$ 棵的第 $i$ 个位置记录经过 $u$ 的路径上、对应深度为 $i$ 的起点/终点个数。
1. 递归 $u$ 回溯过程中将所有 $\text{son}_u$ 的线段树并到 $u$ 的线段树上。
2. 差分：$s$ 处 $\text{dep}_s$ 累加 $1$，$\text{fa}_\text{lca}$ 处 $\text{dep}_s$ 减去 $1$，就可以完成 $\text{dep}_s$ 在 $[s,\text{lca}]$ 上的累加。  
   $nt$ 在 $(\text{lca},t]$ 上的累加也可以类似方法完成。

对于 $\text{w}_u=0$ 的情况，由于 $\text{dep}_u+w_u=\text{dep}_u-w_u$，统计时执行了两次相同的线段树查询操作，故答案 $\text{ans}_u\leftarrow\text{ans}_u\div2$。  
剩下的情况，由于 $\text{dep}_u-w_u<\text{dep}_u+w_u$，贡献统计区间是分离的，也就不会出现不合法的第一种贡献到了第二种等类似情况。

[AC](https://www.luogu.com.cn/record/188854935) 134.72MB 2.54s
