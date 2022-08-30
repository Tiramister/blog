---
title: "AtCoder Beginner Contest 152 E - Flatten"
date: 2020-01-19
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/abc152/tasks/abc152_e
  - label: My Submission
    url: https://atcoder.jp/contests/abc152/submissions/9622077
---

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる．
これに対して，以下を満たす長さ $n$ の正整数列 $\\\{ b\_i \\\}$ を考える．

- 任意の $1 \\leq i \\lt j \\leq n$ なる $i, j$ について， $a\_i b\_i = a\_j b\_j$

$\\sum b\_i$ の最小値を求めよ．

### 制約

- $1 \\leq n \\leq 10\^4$
- $1 \\leq a\_i \\leq 10\^6 (= X)$

## 考察

制約は「ある正整数 $L$ が存在して任意の $i$ について $a\_i b\_i = L$ 」と同値で，このような $L$ で最小のものが明らかに最適．その $L$ は何かと考えると，これは $a\_1, \\cdots, a\_n$ の **最小公倍数** である．

しかし MOD を取った状態では最小公倍数を求めるのは不可能．そこで， **素因数分解した状態で** 求めることにする．このとき「各素因数について指数の大きい方で更新する」とすることで最小公倍数が求まる．

後は素因数分解したものを MOD 上の整数に復元して，実際に $\\sum b\_i = \\sum \\frac\{L\}\{a\_i\}$ を計算すればいい．

計算量は、

- $X$ 以下の全整数の素因数分解に $O(X \\log X)$
- 各整数の素因数の個数は $O(\\log X)$

となるので、全体で $O(n \\log\{X\})$ 。

## 実装例

{{<code file="0.cpp" language="cpp">}}
