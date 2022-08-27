---
title: "HUPC 2020 day2 J - Partition"
date: 2020-09-23
tags: [voluntary]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/UOA/UAPC/3086"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/3086/review/4865756/misteer/C++17"
---

## 問題

長さ $N$ の整数列 $(a\_i)$ が与えられる。これを長さ $L$ 以上の連続部分列に分割する。

各部分列の最大値の総和を最大化せよ。

### 制約

- $1 \\leq L \\leq N \\leq 2 \\cdot 10\^5$
- $-10\^9 \\leq a\_i \\leq 10\^9$

## 考察

「 $dp\_i = (a\_0, \\cdots, a\_\{i-1\})$ に対する答え」という DP を考える。
単純に考えると、以下のような遷移が考えられる。

$$
dp\_i = \\max\_\{0 \\leq j \\leq i-L\}
\\\{ dp\_j + \\max\_\{j \\leq k \\lt i\} \\\{ a\_k \\\} \\\}
$$

このままでは計算量が $\\Theta(N\^2)$ なので間に合わないが、少し場合分けをすると高速化できる。

まず $i-j=L$ 、つまり直前の区間の長さがちょうど $L$ である場合。
更新する値は $dp\_\{i-L\} + \\max\_\{i-L \\leq k \\lt i\} \\\{ a\_k \\\}$ となる。
これはスライド最小値なりセグメント木を用いれば高速に求まる。

$i-j \\gt L$ の場合、最大値が直前の区間のどこにあるかで場合分けをする。

最大値が末尾にある場合。
$a\_\{i-1\}$ が最大なので、更新する値は $\\max\_\{0 \\leq j \\lt i-L\} \\\{ dp\_j \\\} + a\_\{i-1\}$ となる。
これは $dp$ に対して累積 $\\max$ を持てば高速に求まる。

最大値が末尾にない場合。
このとき直前の区間から $a\_\{i-1\}$ を取り除いても、 $\\max$ は変わらないし長さは $L$ 以上のままとなる。
したがって、更新する値は $dp\_\{i-1\}$ となる。

以上の 3 パターンをまとめると、各遷移を $\\Theta(1)$ で行える。

## 実装例

index で頭壊れる

{{<code file="0.cpp" language="cpp">}}
