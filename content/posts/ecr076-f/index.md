---
title: "Educational Codeforces Round 76 F - Make Them Similar"
date: 2020-01-21
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1257/problem/F
  - label: My Submission
    url: https://codeforces.com/contest/1257/submission/69218906
---

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる．これと整数 $x$ から， $b\_i = a\_i \\oplus x$ として数列 $\\\{ b\_i \\\}$ を作る。

整数を二進数表記したときの 1 の数を popcount と呼ぶことにする．
$\\\{ b\_i \\\}$ の全要素の popcount が全て等しくなるようにできるか判定し，可能ならそのような $x$ を 1 つ求めよ。

### 制約

- $2 \\leq n \\leq 100$
- $0 \\leq a\_i, x \\lt 2\^\{30\}$

## 考察

全部の $x$ を調べるのは当然不可能だが， **半分だけなら** ，つまり 15bit だけなら調べられるというのが肝．

まず数列 $\\\{ a\_i \\\}$ を上位 15bit，下位 15bit に分割したものを $\\\{ p\_i \\\}, \\\{ q\_i \\\}$ とする．
ここで「全ての要素が同じ」は「全ての隣接箇所の差分が $0$ 」と同値なので， $0 \\leq x \\lt 2\^\{15\}$ に対して $\\\{ p\_i \\oplus x \\\}$ の popcount の差分列を求め， $x$ と共に連想配列で管理する． $\\\{ q\_i \\\}$ も同様．

$\\\{ p\_i \\oplus x \\\}$ と $\\\{ q\_i \\oplus y \\\}$ の差分列の和が全て 0 であれば，数列 $\\\{ a\_i \\oplus (x \\cdot 2\^\{15\} + y) \\\}$ が条件を満たす．よって $\\\{ p\_i \\\}$ から得られた各差分列に対し，それの符号を反転させたものが $\\\{ q\_i \\\}$ から得られたかどうかを見ればよい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
