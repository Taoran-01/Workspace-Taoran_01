
---
### 图论
#### Dijkstra
```cpp
memset(dis, 0x3f, sizeof(dis));
memset(vis, 0, sizeof(vis));
```

```cpp
if (vis[u]) continue; vis[u]=1;
```

`vis[u]` 出队列检查。
#### 欧拉路
欧拉路径的 Hierholzer 算法只能在回溯时取答案。  
因为只有回溯过程保证走的欧拉路径。

Hack:
```
1 3
3 3
3 2
```
答案：`1 3 3 2`。  
如果直接在遍历过程输出，不存栈，答案可能是 `1 3 2 3`，这是错的。

欧拉回路由于终点任意，可以直接输出。

---
### DP
#### 分组背包
```cpp
vector<vector<pii>> d; // fi 代价 | se 收益
int f[W]; // 开容量大小的数组即可

signed main() {
	for (int i=1; i<=n; ++i) { // 循环每一组
		for (int k=w; ~k; --k) { // 循环容量 倒序
			for (pii j:d[i]) if (j.fi<=k) { // 循环组内元素
				f[k]=max(f[k], f[k-j.fi]+j.se); // 更新答案
			}
		}
	}
}

```

相比 0/1 背包，唯一的区别在于组内元素均可转移。  
容量循环需要倒序，组内元素循环在容量循环内，方可保证答案正确。
#### 多重背包计数
先遍历枚举容量，再枚举物品个数。
```cpp
f[0][0]=1;
for (int i=1; i<=n; ++i) {
	for (int j=0; j<=w; ++j) {
		for (int l=0; l<=k; ++l) {
			f[i][j]=(f[i][j]+f[i-1][j-l*i])%mod;
		}
	}
}
```
#### 排列组合
看组合数的 `fac[]` 和 `inv[]` 的空间是否开够。  
例如，如果过程中有计算 $\begin{pmatrix}2i\\j\end{pmatrix}$，则必须开二倍的 $N$。

**每乘两次就需要取一次模**，不然会爆 `long long`！



