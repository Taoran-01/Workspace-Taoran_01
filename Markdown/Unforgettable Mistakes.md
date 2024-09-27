
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
