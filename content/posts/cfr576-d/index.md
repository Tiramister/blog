---
title: "Codeforces Round 576 D. Rectangle Painting 1"
date: 2020-01-21
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1198/problem/D
  - label: My Submission
    url: https://codeforces.com/contest/1198/submission/69230699
---

## 問題

$n \\times n$ の白黒で塗られたグリッドがある．これに以下の操作を繰り返す．

- $h \\times w$ の長方形領域を白く塗る．
- このとき $\\max(h, w)$ のコストが掛かる．

グリッドを全て白くするのに必要な最小コストを求めよ．

### 制約

- $1 \\leq n \\leq 50$

## 考察

まず操作は「 $m \\times m$ の正方形領域を白く塗るのにコスト $m$ 掛かる」と言い換えられる．

元のグリッドがコスト $n$ 以下で塗れるとき，辺長の合計が $n - 1$ 以下の正方形いくつかで黒い頂点を覆える．したがってこのとき， **全て白の行か列が存在する** ことになる．

そこで $dp\_\{lx, ly, rx, ry\} =$ 「長方形領域 $[lx, rx] \\times [ly, ry]$ を白く塗る最小値」とすれば，これは初期値を $\\max(rx - lx + 1, ry - ly + 1)$ として，白行・白列で分割して再帰的に計算し，和で緩和すれば $O(h + w)$ で求まる．

よって全体の計算量は $O(n\^5)$ となる．TL が厳しく，事前にどこが白行・白列かを列挙しないと全然間に合わない．

## 実装例

`std::function`では間に合わなかった．

{{<code file="0.cpp" language="cpp">}}
