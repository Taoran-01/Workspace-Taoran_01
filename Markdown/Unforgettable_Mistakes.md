
<!-- 永生难忘的低级错误 -->

---
### 综述
书写者：[Taoran_01](https://www.luogu.com/user/593907)(我)  
整理者：[Taoran_01](https://www.luogu.com/user/593907)  
受难者：[Taoran_01](https://www.luogu.com/user/593907)、[Wxq820](https://www.luogu.com/user/468920)、[lhc0707](https://www.luogu.com/user/759145)

---
### 0x00 二重循环
共有$m$次询问。
```cpp
for (int i=1; i<=m; ++i) {
	while (m--) {
		// ...
	}
}
```
然而它循环了$m^2$次。

---
### 0x01 投机取巧
$x$需要加$y$后对$300$取模。
```cpp
x+=y%=300;
```
然而它是先对$y$取模后在加到$x$上。

---
### 0x02 铤而走险
对于所有数据，$1\le n\le10000$，$1\le m\le100000$。
```cpp
#define N 10000
```
[Wa了三发](https://www.luogu.com.cn/record/163828656)

---
### 0x04 不明所以
`int`函数无返回值，喜提$TLE$。

---
### 0x05 迷途知返
把输出数据粘到输入数据里。

---
### 0x06 弹道左偏
压行压得太厉害了，结果出现了下面这段代码：
```cpp
while (l<=r) {
	mid=(l+r)>>1, x=mid;
	if (chk()) ans=mid, l=mid+1;
	r=mid-1;
}
```

---
### 0x07 马失前蹄
SPFA最短路，调了 $7$ 遍没调过去。
```cpp
int u=q.front(); q.pop(); // 原来的代码
int u=q.front(); q.pop(), inq[u]=0; // 正确代码
```

---
### 0x08 徒劳无功
线段树，写了 `build()`，但最后忘记调用。
```cpp
signed main() {
	// freopen("P4513.in", "r", stdin);
	n=read(), m=read();
	for (int i=1; i<=n; ++i) bs[i]=read();
	// 这里
	while (m--) {
		int opt=read(), x=read(), y=read(), k=0;
		if (opt==1) {if (x>y) swap(x, y); printf("%d\n", query(x, y));}
		if (opt==2) modify(x, y);
	}
	return 0;
}

```

没有 `return c;`。
```cpp
node operator+(node a, node b) {
	node c=node();
	c.lmax=max(a.lmax, a.sum+b.lmax);
	c.rmax=max(b.rmax, b.sum+a.rmax);
	if (a.rmax<0&&b.lmax<0) c.pmax=max(a.rmax, b.lmax);
	else c.pmax=max(a.rmax, 0LL)+max(b.lmax, 0LL);
	c.pmax=max(c.pmax, max(a.pmax, b.pmax));
	c.sum=a.sum+b.sum;
	// 这里
}

```

---
### 0x09 百密一疏
离散化忘记排序。根本原因：压行过度。
```cpp
sort(a+1, a+n+1), nt=unique(tmp+1, tmp+nt+1)-(tmp+1);
```

---
### 0x0A 醉眼朦胧
多测，无答案输出 `-1`。
```cpp
if (abs(cnt-(n-cnt))>1) return -1; // 原来的代码
if (abs(cnt-(n-cnt))>1) {puts("-1"); continue;} // 正确代码
```
RE 0pts  
$\texttt{tmc}$：这是被几餐了吧才能写出来。

---
### 0x0B 昏聩无能
以第二元素为第一关键字升序排序 `pair` 数组。
```cpp
pii a[N]; int d[N]; // 2nd key compare (below)
bool cmp(pii a, pii b) {return a.se<b.se?a.se<b.se:a.fi<b.fi;} // 原代码
bool cmp(pii a, pii b) {return a.se==b.se?a.fi<b.fi:a.se<b.se;} // 正确代码
```

---
### 0x0C 迟眉钝眼
RE，调了半个月，在同学的建议下开 `-Wall -Wextra` 后问题显现。
```cpp
int query(int l, int r, int p, int k) {
	if (k>t[p].d) return -1; if (l==r) return idx[l];
	if (t[p].ls&&t[t[p].ls].d>=k) return query(l, mid, t[p].ls, k);
	else return query(mid+1, r, t[p].rs, k-t[t[p].ls].d);
} int query(int p, int k) {query(1, n, p, k);} // 原代码
int query(int p, int k) {return query(1, n, p, k);} // 正确代码
```

---
### 0x0D 气急败坏
尝试删除文件夹，但因文件占用删除失败。上网搜寻解决方法，多次尝试无效。最后发现是 VSCode 中的 Terminal 没有关掉。

---
### 0x0E 顺序错误
Floyd 最短路需要先枚举中间转折节点。

---
### 0x0F 粗枝大叶
DAG上DFS，自认为没有环就可以不记录 `vis` 数组。
```cpp
void dfs(int u) {
	for (int i=head[u]; i; i=e[i].nxt) dfs(v);
}
```
不记录 `vis` 的后果是一个点会被多次递归访问，最后 [TLE](https://www.luogu.com.cn/record/184248030)。

---
### 峰回路转
`main()` 函数中的内容：
```cpp
if (l==r) return query(l, l).g;
```
报错 `exit with return value -1`，始终没调出错。
