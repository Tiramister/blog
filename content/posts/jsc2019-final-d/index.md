---
title: "第一回日本最強プログラマー学生選手権決勝 D - Minimize Maximum"
date: 2020-10-22
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_d"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/jsc2019-final/submissions/17572138"
---

## 問題

長さ $N$ の整数列 $(L\_i), (R\_i)$ が与えられる。各 $K = 2, \\cdots, N$ について以下の問題に答えよ。

長さ $K$ の整数列 $(X\_i)$ を考える。ただし各 $1 \\leq i \\leq K$ について $L\_i \\leq X\_i \\leq R\_i$ を満たしていなくてはならない。
そのような $(X\_i)$ のうち、 $\\max\_\{1 \\leq i \\lt K\} \\\{ X\_\{i+1\} - X\_i \\\}$ の最小値を求めよ。

### 制約

- $1 \\leq N \\leq 2 \\cdot 10\^5$
- $0 \\leq L\_i \\leq R\_i \\leq 10\^9$

## 考察

$D = \\max\_\{1 \\leq i \\lt K\} \\\{ X\_\{i+1\} - X\_i \\\}$ を二分探索することを考える。

$D$ を固定すると、 $X\_\{i+1\} \\leq X\_i + D$ が制約として加わる。
$L\_i \\leq X\_i$ に違反しないためには、 $X\_i$ は取りうる最大値を取るのが最善となる。
よって最善な $X\_i$ は以下の漸化式で表される。

- $X\_1 = R\_1$
- $X\_i = \\min(R\_i, X\_\{i-1\} + D) \\quad (i \\geq 2)$

さらにこれを整理すると、以下のように表せる。

$$
X\_i = \\min\_\{1 \\leq j \\leq i\} \\\{ R\_j + D (i - j) \\\}
$$

$i$ を $\\min$ から括りだすと以下の通り。

$$
Y\_i = X\_i - D \\cdot i = \\min\_\{1 \\leq j \\leq i\} \\\{ R\_j - D \\cdot j \\\}
$$

したがって $D$ に対する解が存在する必要十分条件は、「任意の $1 \\leq i \\leq K$ について $L\_i - D \\cdot i \\leq Y\_i$ が成り立つこと」となる。

二分探索の下界を直前の $D$ の値にすれば、解の単調性より $i \\lt K$ についての条件は必ず満たされる。
よって $L\_K - D \\cdot K \\leq Y\_K$ かどうかが高速に判定できれば良いが、 $Y\_K = \\min\_\{1 \\leq j \\leq K\} \\\{ R\_j - D \\cdot j \\\}$ は愚直に計算すると $\\Theta(K)$ かかってしまう。

ここで $R\_j - D \\cdot j$ が $D$ についての 1 次関数であることに着目すると、**Convex Hull Trick**によって $Y\_K$ は $O(\\log K)$ で求めることができる。
今回は傾き $-j$ が単調減少なので、直線の追加は均し $O(1)$ でできる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
