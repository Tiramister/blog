---
title: "WUPC 2020 D - Treasure Mountains"
date: 2020-09-23
tags: [volunteer]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/WUPC/3154"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/3154/review/4865389/misteer/C++17"
---

## 問題

整数 $N$ と長さ $M$ の整数列 $(d\_i)$ が与えられる。以下の形式のクエリ $Q$ 個を処理せよ。

整数 $x, y, z$ が与えられるので、以下を満たす $N$ 以下の非負整数 $t$ を求めよ。

$$
t\^p \\equiv x \\pmod\{N+1\} \\quad \\left( p = \\prod\_\{i=y\}\^\{y+z-1\} d\_i \\right)
$$

ただし $d\_i$ の index は $\\bmod M$ で考えるとする。

なお、以下の制約下でそのような $t$ が一意に定まることが証明できる。

### 制約

- $4 \\leq N \\leq 10\^7 - 10$
- $N+1$ は素数である。
- $1 \\leq d\_i \\leq N-1$
- 各 $d\_i$ は $N$ と互いに素。
- $1 \\leq M, Q \\leq 5 \\cdot 10\^4$
- $1 \\leq x \\leq N$
- $0 \\leq y \\lt M$
- $1 \\leq z \\leq 10\^9$

## 考察

$N+1$ が素数なので、Fermat の小定理より $p$ は $\\bmod N$ で考えてよい。
よって $p$ は $(d\_i)$ の累積積を前計算することで、 $O(1)$ で求められる。

そして「 $d\_i$ が $N$ と互いに素」という制約から、 $p$ も $N$ と互いに素である。
よって $pq \\equiv 1 \\pmod\{N\}$ なる $0 \\leq q \\lt N$ が一意に定まる。
この $q$ について、 $(t\^p)\^q \\equiv t\^\{pq\} \\equiv t\^1 \\pmod\{N+1\}$ が成り立つ。
よって $t\^p \\equiv x \\pmod\{N+1\}$ の両辺を $q$ 乗することで、 $t \\equiv x\^q \\pmod\{N+1\}$ となり $t$ が求まる。

最後に $q$ の求め方だが、 $N$ が素数でないので $p\^\{N-2\}$ では求まらない。
拡張 Euclid の互除法を用いるか、トーシェント関数 $\\varphi$ を使って $p\^\{\\varphi(N)-1\}$ を求める必要がある。

## 実装例

{{<code file="0.cpp" language="cpp">}}
