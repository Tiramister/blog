---
title: ICPC 地区予選 2010 F - Test Case Tweaking
date: 2020-11-14
tags: [ipcp]
links:
  - label: Problem link
    url: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Regional/1311?year=2010
  - label: My Submission
    url: https://onlinejudge.u-aizu.ac.jp/solutions/problem/1311/review/4990761/misteer/C++17
---

## 問題

$N$ 頂点 $M$ 辺の重み付き有向グラフが与えられる。
あなたはこのグラフに対して、以下の操作を行うことができる。

- 辺を 1 つ選び、その辺の重みを好きな **非負整数** に変更する。

頂点 $1$ から $N$ までの最短距離を $C$ にするのに、必要な操作回数の最小値を求めよ。

### 制約

- $2 \\leq N \\leq 100$
- $1 \\leq M \\leq 1000$
- $0 \\leq C \\leq 10\^5$
- 辺の重みは $10\^4$ 以下の非負整数
- 与えられるグラフにおいて、頂点 $1$ から $N$ までの最短距離は $C$ より大きい

## 考察

まず、問題は以下のように言い換えられる。

> いくつかの辺を選んでその重みを $0$ にできるとき、頂点 $1$ から $N$ までの最短距離を $C$ 以下にするには最低何本の辺を選べばよいか。

$C$ を下回った分だけ、選んだ辺の重みを適当に増やしてやればいい。

後は(今いる頂点, 選んだ辺の本数)を頂点とした(つまり頂点倍加した)グラフの最短距離を求めればよい。

## 実装例

{{<code file="main.cpp" language="cpp">}}
