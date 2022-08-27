---
title: "ICPC 2019 国内予選 E - 立方体表面パズル"
date: 2020-09-03
tags: [icpc]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1636"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/1636/review/4814241/misteer/C++14"
---

## 問題

立方体が $n \\times n$ の正方形状に並んだ板が $6$ つ与えられる。
これらは外周が一部欠けているもある。

これら $6$ つの板を組み合わせて、 $n \\times n \\times n$ の立方体の表面を作れるか判定せよ。なお各板はどちらの面を表面にしてもよい(つまり反転できる)ものとする。

### 制約

- $3 \\leq n \\leq 9$
- $n$ は奇数

## 考察

枝刈り DFS でシミュレーションするだけ(ちなみに DFS ではなく各板の配置・向きを全探索すると TLE する)。

ただ実装がかなり面倒くさい。以下では実際に $n \\times n \\times n$ の配列を塗っていくのだが、どの面に置くかによって 3 つの場合分け(といってもほとんどコピペだが)が生じている。

## 実装例

{{<code file="0.cpp" language="cpp">}}
