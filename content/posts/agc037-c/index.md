---
title: "AtCoder Grand Contest 037 C - Numbers on a Circle"
date: 2020-01-17
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/agc037/tasks/agc037_c
  - label: My Submission
    url: https://atcoder.jp/contests/agc037/submissions/9548175
---

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}, \\\{ b\_i \\\}$ が与えられる．今から $\\\{ a\_i \\\}$ に以下の操作を適用することで $\\\{ b\_i \\\}$ と一致させたい．

- $1 \\leq i \\leq n$ なる $i$ を 1 つ取る．
- $a\_i$ に $a\_\{i - 1\} + a\_\{i + 1\}$ を加える．
- index は $\\bmod n$ で考える．

これが可能かどうか判定し，可能なら操作回数の最小値を出力せよ．

### 制約

- $3 \\leq n \\leq 2 \\cdot 10\^5$
- $1 \\leq a\_i, b\_i \\leq 10\^9 (= X)$

## 考察

逆から考えると，以下の問題と同値となる．

{{<framed>}}
$\\\{ b\_i \\\}$ に以下の操作を適用することで $\\\{ a\_i \\\}$ と一致させたい．

- $1 \\leq i \\leq n$ なる $i$ を 1 つ取る．
- $b\_i$ から $b\_\{i - 1\} + b\_\{i + 1\}$ を引く．

これが可能かどうか(以下略)
{{</framed>}}

こうすると，操作が可能なのは $b\_i \\geq b\_\{i - 1\} + b\_\{i + 1\}$ を満たす $i$ のみとなる．
ここから分かる重要な事実として，「両隣に自分より大きい数がいる間は操作ができない」というものがある．これにより，大きい数から順に操作していくことが最善策であることが分かる．

以上より，「 $a\_i$ と $b\_i$ が一致していない $i$ を， $b\_i$ が大きい方から揃えていく」というアルゴリズムが考えられる．これは揃っていない $i$ を $b\_i$ と一緒に priority queue に入れるなどしてシミュレートできる．ただ愚直に引き算をしていると間に合わないので，適当に除算によって高速化する必要がある．

この解法の計算量は非自明ではあるが，1 回のまとまった操作で $b\_i$ が半減することから $O(n \\log n \\log X)$ で終わる( $\\log n$ は priority queue の分)．

## 実装例

{{<code file="0.cpp" language="cpp">}}
