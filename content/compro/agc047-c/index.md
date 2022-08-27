---
title: AtCoder Grand Contest 047 C - Product Modulo
date: 2020-08-10
tags: [atcoder]
links:
  - label: 問題
    url: https://atcoder.jp/contests/agc047/tasks/agc047_c
  - label: 提出
    url: https://atcoder.jp/contests/agc047/submissions/15794827
---

## 問題

$P = 2 \cdot 10^5 + 3$ (素数)とする。

$n$ 個の整数 $\\\{ a_i \\\}$ が与えられる。 $\sum_{i \lt j} (a_i a_j \bmod P)$ を求めよ。

### 制約

- $2 \leq n \leq 2 \cdot 10^5$
- $0 \leq a_i \lt P$

## 考察

コンテスト中は $x \bmod P = x - \lfloor x / P \rfloor \cdot P$ を使うとずっと思っていたが違った。

以降 $a_i = 0$ なる $i$ は無視して考える。

$g = 2$ は $P$ の原始根なので、任意の $1 \leq x \lt P$ に対して $g^k \equiv x$ なる $0 \leq k \leq P - 2$ が存在する。
そこで、 $g^{b_i} = a_i$ を満たす数列 $\\\{ b_i \\\}$ を考える。すると、 $a_i a_j \equiv g^{b_i + b_j}$ となり、「 $\\\{a_i\\\}$ 同士の掛け算」が「 $\\\{b_i\\\}$ 同士の足し算」に変わる。よって各 $0 \leq k \leq 2(P - 2)$ について $b_i + b_j = k$ なる $i \lt j$ を数え上げればよく、これは FFT によって $\Theta(P \log P)$ でできる。

## 実装例

{{< code file="main.cpp" language="cpp" >}}
