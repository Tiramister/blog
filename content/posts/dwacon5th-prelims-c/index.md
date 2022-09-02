---
title: "第 5 回 ドワンゴからの挑戦状 予選 C - k-DMC"
date: 2019-10-26
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_c
  - label: My Submission
    url: https://atcoder.jp/contests/dwacon5th-prelims/submissions/8121212
---

## 問題

長さ $n$ の英大文字からなる文字列が与えられる．
これに対し，以下の形式で与えられる $q$ 個のクエリに答えよ．

各クエリでは，整数 $K$ が与えられる．
このとき，以下を全て満たす整数の組 $(a, b, c)$ の数を求めよ．

- $1 \\leq a \\lt b \\lt c \\leq n$
- $s\_a s\_b s\_c =$ `DMC`
- $c - a \\lt K$

### 制約

- $3 \\leq n \\leq 10\^6$
- $1 \\leq q \\leq 75$
- $3 \\leq K \\leq n$

## 考察

$D = \\\{ i \\mid s\_i =$ `D` $\\\}$ とする． $M, C$ も同様．

そして，以下の 3 つの累積和的な数列を考える．

- $dsum\_i = | \\\{ j \\in D \\mid 1 \\leq j \\leq i \\\} |$
- $msum\_i = | \\\{ j \\in M \\mid 1 \\leq j \\leq i \\\} |$
- $dmsum\_i = \\sum \\\{ dsum\_j \\mid 1 \\leq j \\leq i, j \\in M \\\} = | \\\{ (j, k) \\in D \\times M \\mid 1 \\leq k \\leq j \\leq i \\\}|$

これらを使うと， $s\_i =$ `C`のときにこれを末尾に持つような組の数は以下の式で求められる．

$$
(dmsum\_i - dmsum\_\{i - K\}) -
(msum\_i - msum\_\{i - K\}) \\cdot dsum\_\{i - K\}
$$

第 1 項で `M` が $(i-K, i]$ にあるような DM の個数を求めている．これでは D が $[0, i-k]$ にあるようなものも含まれるので，それを第 2 項で除いている．

後はこれを $i \\in C$ について足し上げればいい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
