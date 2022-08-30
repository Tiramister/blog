---
title: "Educational Codeforces Round 76 E. The Contest"
date: 2020-01-21
tags: [codeforces]
links:
  - label: Problem link
    url: https://codeforces.com/contest/1257/problem/E
  - label: My Submission
    url: https://codeforces.com/contest/1257/submission/69218307
---

## 問題

$n$ 枚のカードがある． $i$ 枚目には $i$ が書かれている．

最初，これを A, B, C にそれぞれ $k\_A, k\_B, k\_C$ 枚ずつ分けた．これから以下の操作を繰り返す．

- 1 人が，手持ちの好きなカードを好きな誰かに渡す．

これを繰り返すことで，ある $l, r$ について A が $[1, l]$ ，B が $(l, r]$ ，C が $(r, n]$ の区間のカードを持っているようにしたい．最小の操作回数を求めよ．

### 制約

- $1 \\leq n \\leq 2 \\cdot 10\^5$

## 考察

まず $l, r$ を固定したときの操作回数を考える．これは区間 $I$ の中で X が持っているカードの枚数を $s\_\{X, I\}$ とすると，以下で表される．

$$
f(l, r) = s\_\{B, [1, l]\} + s\_\{C, [1, l]\} + s\_\{A, (l, r]\} + s\_\{C, (l, r]\} + s\_\{A, (r, n]\} + s\_\{B, (r, n]\}
$$

要は銘々が要らないカードを必要な人に渡すわけである．

これを累積和で表す，つまり $s\_\{X, i\} = s\_\{X, [1, i]\}$ とすれば，

$$
\\begin\{align*\}
f(l, r)
&= s\_\{B, l\} + s\_\{C, l\} + (s\_\{A, r\} - s\_\{A, l\}) + (s\_\{C, r\} - s\_\{C, l\}) + (s\_\{A, n\} - s\_\{A, r\}) + (s\_\{B, n\} - s\_\{B, r\}) \\\\
&= (k\_A + k\_B) + (s\_\{B, l\} - s\_\{A, l\}) + (s\_\{C, r\} - s\_\{B, r\})
\\end\{align*\}
$$

となり

- 定数
- $l$ に依存する部分
- $r$ に依存する部分

の 3 つに分けられた．後は $s\_\{B, l\} - s\_\{A, l\}$ の最小値を保持しながら $r$ を全探索すればいい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
