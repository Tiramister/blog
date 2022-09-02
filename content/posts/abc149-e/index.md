---
title: "AtCoder Beginner Contest 149 E - Handshake"
date: 2019-12-29
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/abc149/tasks/abc149_e
  - label: My Submission
    url: https://atcoder.jp/contests/abc149/submissions/9224815
---

## 問題

長さ $n$ の数列 $\\\{a\_i\\\}$ に対し，以下の操作を $m$ 回行う．最初スコアは $0$ である．

- $1 \\leq x, y \\leq n$ なる $x, y$ を任意に選ぶ．
- ただし，既に選んだ $(x, y)$ の組を選ぶことはできない．
- $a\_x + a\_y$ をスコアに加算する．

最終的なスコアの最大値を求めよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $1 \\leq m \\leq n\^2$
- $1 \\leq a\_i \\leq 10\^5$

## 考察

以降 $\\\{a\_i\\\}$ は昇順とする．

愚直な解法として，「PriorityQueue に全ペアを突っ込んで大きい方から $m$ 個取る」というのが考えられる．しかしこのアルゴリズムの計算量は $O(n\^2 \\log n)$ なので，今回の制約では許されない．

そこで，この上から $m$ 番目の値( $S$ とおく)を二分探索することにする． $x$ を固定したときの $S$ 以下のペアの個数は， $\\\{a\_i\\\}$ 中で $S - a\_x$ 以下の要素の個数となる．これは二分探索により十分高速に求まる．したがって $S$ 以下のペアの個数は $O(n \\log n)$ で求まる．

この $S$ が求まれば，後は $\\\{a\_i\\\}$ の累積和を使うことで十分高速に $S$ 以下のペアの和が求まる．ただし $S$ 以下の要素が $m$ 個より多い場合もあるので，その場合は余剰分を引く必要がある．

## 実装例

{{<code file="0.cpp" language="cpp">}}
