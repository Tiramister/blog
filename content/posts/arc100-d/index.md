---
title: "AtCoder Regular Contest 100 D - Equal Cut"
date: 2018-09-17
tags: [atcoder]
links:
  - label: "Problem"
    url: https://atcoder.jp/contests/arc100/tasks/arc100_b
  - label: "My Submission"
    url: https://atcoder.jp/contests/arc100/submissions/3213182
---

## 概要

長さ $N$ の数列 $A$ が与えられる。

今から $A$ を 3 箇所で切って、 4 つの空でない数列を作る。
各数列の総和を $P, Q, R, S$ としたとき、 $\\max\\\{P, Q, R, S\\\} - \\min\\\{P, Q, R, S\\\}$ の最小値を求めよ。

### 制約

- $4 \\leq N \\leq 2 \\times 10\^5$
- $1 \\leq A\_i \\leq 10\^9$

## 解法

メタ的だが、「なぜカット数は変数ではなく 3 で固定なのか？」に着目した結果、以下の解法に至った。

1. まず $A$ の 2 つの切り方を全探索する。
2. 各パートについて、なるべく 2 等分するような切断位置を二分探索で探す。

二分探索する上で区間和を $O(1)$ で求める必要があるが、これは累積和を作っておけば大丈夫。

## 実装例

{{<code file="0.cpp" language="cpp">}}
