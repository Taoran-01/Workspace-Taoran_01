
<!-- 模板整理 -->

# 数据结构 | Data Structure
## 单调栈 | Monotonic Stack
### 解决问题 | Problem Solved
1. 求比当前元素大的上一个元素；
2. 求比当前元素小的上一个元素；
3. 求比当前元素大的下一个元素；
4. 求比当前元素小的下一个元素。

通过改变判断符号与改变循环顺序可解决上述问题。
### 基本思路 Basic Idea
> 维护一个从栈底到栈顶单调递增/递减的栈。

元素入栈前弹出不满足单调性的栈顶元素，访问时答案为栈顶元素。
### 模板代码 Template Code
给出项数为 $n$ 的序列 $\{a_n\}$，询问 $a_i$ 后面第一个大于 $a_i$ 的元素的下标。  
即，你需要找出一个最小的下标 $j$，满足 $j>i\land a_j>a_i$。
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

#define N 3000010
int n;
int a[N], ans[N];
int stk[N], top;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	for (int i=n; i; --i) {
		while (top&&a[stk[top]]<=a[i]) --top;
		ans[i]=stk[top];
		stk[++top]=i;
	}
	for (int i=1; i<=n; ++i) printf("%d ", ans[i]);
	return 0;
}

```
解释：构造一个存储下标的单调栈，其元素从栈底到栈顶单调递减。遍历时从后向前遍历，将“在 $a_i$ 后面且大于它的第一个数”转化为“在 $a_i$ 前面且大于它的第一个数”。
### 注意事项 | Precautions
借助单调性处理问题的思想在于及时排除不可能的选项，保持策略集合的高度有效性和秩序性。

## 单调队列 | Monotonic Queue
### 解决问题 | Problem Solved
一列数 $\{a_n\}$ 和若干区间 $[l_i,r_i]$，满足 $l_i\ge l_{i-1}$，$r_i\ge r_{i-1}$。对于每一个区间，求最小值与最大值。
### 基本思路 Basic Idea
> 如果一个选手比你小，还比你强，你就可以退役了。  
> 维护一个从队头到队尾单调递增/递减的双端队列，元素具有时效性。

新元素从前方入队，不满足单调性的元素从前方弹出。旧元素从后方出队，过期的元素从后方弹出。
### 模板代码 | Template Code
给你一个数列 $\{a_n\}$ 和一个数 $k$，询问每一个长度为 $k$ 的连续区间内最小值和最大值是多少。
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

#define N 1000010
int n, k;
int a[N];
int q[N];
int l, r; // deque in range [l,r]

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), k=read();
	for (int i=1; i<=n; ++i) a[i]=read();
	l=1, r=0; // init - query min
	for (int i=1; i<=n; ++i) {
		while (l<=r&&a[q[r]]>=a[i]) --r;
		q[++r]=i;
		while (l<=r&&q[l]<=i-k) ++l;
		if (i>=k) printf("%d ", a[q[l]]);
	}
	puts("");
	l=1, r=0; // init - query max
	for (int i=1; i<=n; ++i) {
		while (l<=r&&a[q[r]]<=a[i]) --r;
		q[++r]=i;
		while (l<=r&&q[l]<=i-k) ++l;
		if (i>=k) printf("%d ", a[q[l]]);
	}
	return 0;
}

```
解释：以最小值为例，构造一个从队头到队尾单调递增且满足时效性的双端队列，队头位置即为答案。储存元素在 $a$ 中对应的下标，而非元素本身。

插入元素分三步：
1. 小于等于新元素的弹出，因为不满足单调性；
2. 新元素加入队尾；
3. 处理队头过期元素，若下标在区间起点 $i-k+1$ 的前面则已过期，需要弹出；
4. 此时区间中的答案即为队头元素，输出。

## 树状数组 | Binary Indexed Tree
### 解决问题 | Problem Solved
支持单点查询、区间修改的数据结构，代码量小。
### 基本思路 | Basic Idea
不会还有人不知道怎么写吧（惊讶  
很巧妙，一时半会说不明白，请自行前往[OI-Wiki](https://oi-wiki.org/ds/fenwick/)学习。
### 模板代码 | Template Code
给定 $n$ 个数 $a_1\dots a_n$ 和 $m$ 个操作，其中：
1. 操作 `1 x k` 表示将第 $x$ 个位置的数加 $k$；
2. 操作 `2 l r` 表示查询区间 $[l,r]$ 内的区间和。
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

#define N 500010
int n;

template <typename T> struct BIT {
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void modify(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T query(int x) {return g(x);} T query(int l, int r) {return g(r)-g(l-1);}
};

int m, opt, t1, t2;
BIT<int> ta;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) t1=read(), ta.modify(i, t1);
	while (m--) {
		opt=read(), t1=read(), t2=read();
		if (opt==1) ta.modify(t1, t2);
		if (opt==2) printf("%d\n", ta.query(t1, t2));
	}
	return 0;
}
```

## 区间加区间和 树状数组 | Binary Indexed Tree for Interval M&Q
### 解决问题 | Problem Solved
支持区间查询、区间修改的数据结构，代码量小。
### 基本思路 | Basic Idea
使用两个树状数组维护差分数组。一个为 $d_i=a_i-a_{i-1}$，一个为 $f_i=d_i\times i$。

对于区间加：  
$d_l\leftarrow d_l+k$，$d_{r+1}\leftarrow d_{r+1}-k$；  
$f_l\leftarrow f_l+k\times l$，$f_{r+1}\leftarrow f_{r+1}-k\times(r+1)$。

对于区间和：  
$\sum\limits_{i=1}^r=\sum\limits_{i=1}^rd_i\times(r+1)-\sum\limits_{i=1}^rf_i$
### 模板代码 Template Code
给定 $n$ 个数 $a_1\dots a_n$ 和 $m$ 个操作，其中：
1. 操作 `1 l r k` 表示将区间 $[l,r]$ 内所有数加 $k$；
2. 操作 `2 l r` 表示查询区间 $[l,r]$ 内的区间和。
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

#define N 100010
int n;

template <typename T> struct BIT {
	T c[N]; int lowbit(int x) {return x&(~x+1);}
	void modify(int x, T k) {while (x<=n) c[x]=c[x]+k, x+=lowbit(x);}
	T g(int x) {T ans=T(); while (x>0) ans=ans+c[x], x-=lowbit(x); return ans;}
	T query(int x) {return g(x);} T query(int l, int r) {return g(r)-g(l-1);}
};

template <typename T> struct BITI {
	BIT<T> t1, t2;
	void a(int x, T k) {t1.modify(x, k), t2.modify(x, x*k);}
	void modify(int l, int r, T k) {a(l, k), a(r+1, -k);}
	T query(int l, int r) {return t1.g(r)*(r+1)-t1.g(l-1)*l-t2.query(l, r);}
};

int m, opt; ll t1, t2, t3; BITI<ll> ta;

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) t1=read(), ta.modify(i, i, t1);
	while (m--) {
		opt=read(), t1=read(), t2=read();
		if (opt==1) t3=read(), ta.modify(t1, t2, t3);
		if (opt==2) printf("%lld\n", ta.query(t1, t2));
	}
	return 0;
}

```

## 数据结构名称 | Data Structure Name
### 解决问题 | Problem Solved
### 基本思路 | Basic Idea
### 模板代码 | Template Code

# 算法 | Algorithm
## ST表 | Sparse Table
### 解决问题 | Problem Solved
给定 $n$ 个数 $a_i$ 及 $m$ 个询问，每次询问给出一个区间 $[l_i,r_i]$，询问区间内的 $\operatorname{opt}$。  
其中，$\operatorname{opt}$ 满足 $\operatorname{opt}(x,y,z)=\operatorname{opt}(x,\operatorname{opt}(y,z))$，且 $\operatorname{opt}(x,x)=x$。
### 基本思路 | Basic Idea
预处理出每个子区间 $[i,i+2^j-1]$ 的结果 $f_{i,j}$，查询时答案即为 $\operatorname{opt}(f_{l,l+2^k-1},f_{r-2^k+1,r})$。
### 模板代码 | Template Code
给定 $n$ 个数 $a_i$ 及 $m$ 个询问，每次询问给出一个区间 $[l_i,r_i]$，询问区间内的最大值。
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

#define N 100010
int n, m, l, r, x;
int a[N], f[N][20]; // 17
int Log[N];

signed main() {
	// freopen("a.in", "r", stdin);
	for (int i=2; i<N; ++i) Log[i]=Log[i>>1]+1;
	n=read(), m=read();
	for (int i=1; i<=n; ++i) f[i][0]=read();
	for (int j=1; j<=Log[n]; ++j) for (int i=1; i<=n-(1<<j)+1; ++i) {
		f[i][j]=max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
	}
	while (m--) {
		l=read(), r=read(), x=Log[r-l+1];
		printf("%d\n", max(f[l][x], f[r-(1<<x)+1][x]));
	}
	return 0;
}

```

## 有理数取余 | Taking the Remainder of Rational Numbers
### 解决问题 | Problem Solved
对一个分数 $\frac ab$ 进行取余。
### 基本思路 | Basic Idea
前提：$p\nmid b$
1. 扩展欧几里得算法求解线性同余方程：$x=\frac ab\operatorname{mod}p\Leftrightarrow bx\equiv a\ (\operatorname{mod}\ p)$。
2. 快速幂求逆元：$b^{-1}=b^{p-2}$，前提：$p\in\text{Prime}$。
### 模板代码 | Template Code
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)
#define MOD 19260817

inline ll read() {
	ll x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=((x<<1)+(x<<3)+(ch^48))%MOD, ch=getchar();
	return x*f%MOD;
}

ll qpow(ll a, ll b) {
	ll res=1;
	while (b) {
		if (b&1) res=res*a%MOD;
		a=a*a%MOD, b>>=1;
	}
	return res;
}

ll a, b;

signed main() {
	// freopen("a.in", "r", stdin);
	a=read(), b=read();
	if (b==0) return puts("Angry!"), 0;
	printf("%lld\n", (a*qpow(b, MOD-2)%MOD+MOD)%MOD);
	return 0;
}

```

## 矩阵快速幂 | Matrix Fast Power
### 解决问题 | Problem Solved
给定一个 DP 的递推式，并且转移可以使用矩阵乘法，则可以使用矩阵加速递推。
### 基本思路 | Basic Idea
矩阵乘法：左行右列。
$$
C_{i,j}=\sum_{k=1}^mA_{i,k}B_{k,j}
$$

以斐波那契数列为例。
$$
\begin{aligned}
&f_i=f_{i-1}+f_{i-2}\\
\Rightarrow&
\begin{bmatrix}f_i&f_{i-1}\end{bmatrix}=
\begin{bmatrix}f_{i-1}&f_{i-2}\end{bmatrix}
\begin{bmatrix}1&1\\1&0\end{bmatrix}\\
\Rightarrow&
\begin{bmatrix}f_n&f_{n-1}\end{bmatrix}=
\begin{bmatrix}1&1\end{bmatrix}
\begin{bmatrix}1&1\\1&0\end{bmatrix}^{n-2}
\end{aligned}
$$

我们可以使用快速幂的方式计算出右侧矩阵，从而 $O(\log n)$ 地求出递推结果。

以行向量为例，

- 求解问题特点：
  1. 可以抽象出长度为 $n$ 的一维向量，该向量在每个单位时间发生一次变化；
  2. 变化的形式是一个线性递推，仅包含加法和乘系数运算；
  3. 该递推式在每个时间可能作用于不同的数据上，但本身保持不变；
  4. 向量变化时间很长，但向量长度 $n$ 不大。
- 构造矩阵：
  1. 状态矩阵：长度为 $n$ 的一维向量；
  2. 转移矩阵：参加快速幂运算的不变的矩阵；
  3. 若状态矩阵第 $x$ 个数对下一时间状态矩阵第 $y$ 个数产生影响，则应修改转移矩阵第 $x$ 行第 $y$ 列的数。
### 模板代码 | Template Code
定义空矩阵：`Matrix a=Matrix(), a.n=xxx, a.m=xxx;`  
其中，$n$ 表示行，$m$ 表示列。

修改元素：`a[i][j]=xxx;`

注意：这段代码不能处理零次幂及负数次幂的情况，需要特判。矩阵大小和模数按题目要求更改。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

char buf[1<<20], *p1, *p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?0:*p1++)

inline ull read() {
	ull x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	return x*f;
}

#define MN 110
#define MM 110
#define MOD 1000000007ULL

struct Matrix {
	int n, m; ull d[MN][MM];
	ull* operator[](int x) {return d[x];}
	Matrix() {n=0, m=0, memset(d, 0, sizeof(d));}
};

Matrix operator*(Matrix &a, Matrix &b) {
	Matrix z=Matrix(); z.n=a.n, z.m=b.m;
	for (int i=1; i<=a.n; ++i) for (int j=1; j<=a.m; ++j) {
		for (int k=1; k<=b.m; ++k) z[i][k]=(z[i][k]+a[i][j]*b[j][k])%MOD;
	}
	return z;
}
void operator*=(Matrix &a, Matrix b) {a=a*b;}

template <typename T> T qpow(T a, ull b) {
	T res=a; --b;
	while (b) {if (b&1) res*=a; a*=a, b>>=1;}
	return res;
}

signed main() {
	return 0;
}

// ull n;
// Matrix a, b, ans;

// signed main() {
// 	// freopen("a.in", "r", stdin);
// 	n=read();
// 	if (n<=2) return puts("1"), 0;
// 	a.n=1, a.m=2, b.n=2, b.m=2;
// 	a[1][1]=1, a[1][2]=1;
// 	b[1][1]=0, b[1][2]=1, b[2][1]=1, b[2][2]=1;
// 	ans=a, ans*=qpow(b, n-2), printf("%llu\n", ans[1][2]);
// 	return 0;
// }

```
解释：矩阵乘法阶段改变枚举顺序，使内存连续访问，减小常数。

## 三维偏序 - CDQ | 3D Partial Order Problems - CDQ
### 解决问题 | Problem Solved
$n$ 个元素，有 $a_i$、$b_i$ 和 $c_i$ 三个属性值，求满足 $a_i\le a_j\land b_i\le b_j\land c_i\le c_j\land i\neq j$ 的点对 $(i,j)$。
### 基本思路 | Basic Idea
第一维 $a_i$ 通过排序解决。  
对所有点按 $a_i$ 从小到大排序，这样左边取 $i$ 右边取 $j$，总能满足第一个维度的限制。

后两维考虑分治，类似归并排序。  
假设当前已经处理好了区间 $[l,mid]$ 和 $[mid+1,r]$ 的答案，现在要处理的就是跨区间的答案。

第二维 $b_i$ 通过排序解决。
对区间 $[l,mid]$ 和区间 $[mid+1,r]$ 分别按 $b_i$ 从小到大排序，这样左边取 $i$ 右边取 $j$，总能满足第二个维度的限制。  
接下来枚举每一个 $j$，将所有 $b_i\le b_j$ 的值 $c_i$ 插入到树状数组中。

第三位 $c_i$ 通过树状数组解决。  
在插入一个 $c_i$ 时，令 $arr_{c_i}\leftarrow arr_{c_i}+1$，然后查询有多少个 $x$ 满足 $arr_x<arr_{c+i}$。

难点在于 $a_i$、$b_i$、$c_i$ 都相同的点。这些会被计为一个点，存储在 `p.cnt` 中，统计答案的时候考虑上即可。

### 模板代码 | Template Code
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

#define N 100010
#define M 200010

int n, k, m; // k: value max | m: total p
int res[N];

struct node {int a, b, c, cnt, res;} p[N], e[N]; // e: multi | p: unique
bool operator!=(node a, node b) {return a.a!=b.a||a.b!=b.b||a.c!=b.c;}

struct BIT {
	int t[M];
	#define lowbit(x) (x&(~x+1))
	void modify(int pos, int val) {
		for (int i=pos; i<=k; i+=lowbit(i)) t[i]+=val;
	}
	int query(int pos) {
		int res=0;
		for (int i=pos; i; i-=lowbit(i)) res+=t[i];
		return res;
	}
} t;

bool cmpa(node a, node b) { // p.a first sort
	if (a.a!=b.a) return a.a<b.a;
	if (a.b!=b.b) return a.b<b.b;
	return a.c<b.c;
}

bool cmpb(node a, node b) { // p.b first sort
	if (a.b!=b.b) return a.b<b.b;
	return a.c<b.c;
}

void cdq(int l, int r) {
	if (l==r) return; int mid=l+r>>1;
	cdq(l, mid), cdq(mid+1, r);
	sort(p+l, p+mid+1, cmpb), sort(p+mid+1, p+r+1, cmpb);
	int i=l, j=mid+1;
	while (j<=r) {
		while (i<=mid&&p[i].b<=p[j].b) {
			t.modify(p[i].c, p[i].cnt), ++i;
		}
		p[j].res+=t.query(p[j].c), ++j;
	}
	for (int x=l; x<i; ++x) t.modify(p[x].c, -p[x].cnt); // clear
}

signed main() {
	// freopen("a.in", "r", stdin);
	n=read(), k=read();
	for (int i=1; i<=n; ++i) e[i].a=read(), e[i].b=read(), e[i].c=read();
	sort(e+1, e+n+1, cmpa);
	for (int i=1, x=1; i<=n; ++i, ++x) {
		if (e[i]!=e[i+1]) swap(p[++m], e[i]), p[m].cnt=x, x=0;
	}
	cdq(1, m);
	for (int i=1; i<=m; ++i) res[p[i].res+p[i].cnt]+=p[i].cnt;
	for (int i=1; i<=n; ++i) printf("%d\n", res[i]);
	return 0;
}

```

## 算法名称 | Algorithm Name
### 解决问题 | Problem Solved
### 基本思路 | Basic Idea
### 模板代码 | Template Code
