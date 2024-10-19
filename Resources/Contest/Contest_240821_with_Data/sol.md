# a

注意到 $3$ 位数两次迭代后变成 $ 213$，容易归纳得到所有数都会很快收敛

特判 $n=0,k=1$

# b

想到矩阵乘加速，而无法处理 $a_i^2$ 于是在矩阵内加入 $a_i^2$

推出

$\begin{bmatrix} 1&1&1&0\\0&x^2&y^2&2xy\\0&1&0&0\\0&x&0&y \end{bmatrix} 
*\begin{bmatrix} S_{i-1}\\a_i^2\\a_{i-1}^2\\a_ia_{i-1} \end{bmatrix}=
\begin{bmatrix} S_{i}\\a_{i+1}^2\\a_{i}^2\\a_{i+1}a_{i} \end{bmatrix}
$

# c
线段树即可

# d
1.主席树
2.树状数组/桶
