---
title: "Educational Codeforces Round 78 F - Cards"
date: 2020-01-13
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1278/problem/F
  - label: My Submission
    url: https://codeforces.com/contest/1278/submission/68670202
---

## 問題

1 枚だけジョーカーの入った $m$ 枚のデッキがある．
今から，このデッキに対して以下の操作を $n$ 回行う．

- デッキをランダムにシャッフルする．
- 一番上のカードを見て，デッキに戻す．

ジョーカーが出た回数を $x$ としたとき， $x\^k$ の期待値を求めよ．

### 制約

- $1 \\leq n, m \\lt 998,244,353$
- $1 \\leq k \\leq 5 \\cdot 10\^3$

## 考察

ジョーカーが出る確率は常に $\\frac\{1\}\{m\}$ なので，以降 $p = \\frac\{1\}\{m\}$ とおく．

ちょうど $x$ 回出る確率から直接出そうとすると，

$$
\\sum\_\{0 \\leq x \\leq n\} x\^k \\binom\{n\}\{x\} p\^x (1 - p)\^\{n - x\}
$$

という式が立つ．が，残念ながら $n$ が非常に大きいのでこれを高速に計算するのは困難．よって視点を大きく変える必要がある．

カードの引き方を 1 つ固定し， $i$ 番目に出たカードがジョーカーなら $a\_i = 1$ ，そうでなければ $a\_i = 0$ として数列 $\\\{ a\_i \\\}$ を作る．このとき求めるべきは $\\left( \\sum a\_i \\right)\^k$ の期待値となる．

これは展開によって

$$
\\left( \\sum a\_i \\right)\^k
= \\sum\_\{1 \\leq d\_1 \\leq n\} \\cdots \\sum\_\{1 \\leq d\_k \\leq n\} \\prod\_j a\_\{d\_j\}
$$

となる．これを意味的に解釈すると，「 $k$ 要素のタプル $(d\_1, \\cdots, d\_k)$ で，全ての $1 \\leq j \\leq k$ で $a\_\{d\_j\} = 1$ なるものの個数」となる．この変形が重要．

タプル $(d\_1, \\cdots, d\_k)$ を 1 つ固定し，全ての $1 \\leq j \\leq k$ で $a\_\{d\_j\} = 1$ が成り立つ確率を考える．これはタプルの重複を除いた要素数を $s$ として $p\^s$ と表せる。
後は要素数が $s$ となるタプルの個数を求めればよく，これは $dp\_\{i, j\} =$ 「サイズ $i$ のタプルで要素数が $j$ のものの個数」を更新していけば $O(k\^2)$ で求まる．

## 実装例

{{<code file="0.cpp" language="cpp">}}
