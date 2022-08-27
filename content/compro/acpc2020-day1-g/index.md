---
title: "ACPC 2020 day1 G - 移動の最小化"
date: 2020-09-20
tags: [voluntary]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/servhttps://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/TUATPC/3199"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/3199/review/4856261/misteer/C++17"
---

## 問題

数直線上に $N$ 個の点があり、 $i$ 番目の座標は $x\_i$ である。

いくつかの点を移動させて、点が $M$ 個ある長さ $K$ の区間が存在するようにする。
移動距離の総和の最小値を求めよ。

### 制約

- $2 \\leq M \\leq N \\leq 10\^5$
- $1 \\leq K \\leq 10\^9$
- $0 \\leq x\_1 \\lt \\cdots \\lt x\_N \\leq 10\^9$

## 考察

点 $x\_i, \\cdots, x\_\{i+M-1\}$ を長さ $K$ の区間に収めることを考える。
これを各 $i$ について高速に処理できればよい。

ここで極端な例として、 $K=0$ 、つまり全ての点を 1 点に集める場合を考える[^zero]。
これは [この問題](https://atcoder.jp/contests/arc100/tasks/arc100_a) にもあるように、集める地点を $x\_i, \\cdots, x\_\{i+M-1\}$ の中央値にするのが最善となる。

[^zero]: このケースは制約には存在しない。

これを一般の $K$ にも適用すると、区間から左・右にはみ出した点の個数が釣り合うところが最善となる。
この区間の位置は、二分探索により求めることができる。
そして区間を固定した後の移動距離も、 $(x\_i)$ の累積和を使うことで求められる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
