---
title: AtCoder Grand Contest 047 A - Integer Product
date: 2020-08-10
tags: [atcoder, agc]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/agc047/tasks/agc047_a
  - label: My Submission
    url: https://atcoder.jp/contests/agc047/submissions/15793193
---

## 問題

$n$ 個の _実数_ $\\\{ a\_i \\\}$ が与えられる。
$a\_i a\_j$ が整数となる $i, j \\; (i \\lt j)$ の個数を求めよ。

### 制約

- $2 \\leq n \\leq 2 \\times 10^5$
- $0 \\lt a\_i \\lt 10^4$
- $a\_i$ は最大で小数点以下 9 桁まで与えられる

## 考察

制約から $a\_i$ を $10^9$ 倍すれば整数になる。これを $b\_i$ とおくと、
「 $a\_i a\_j$ が整数になる」ことと「 $b\_i b\_j$ が $10^\{18\}$ の倍数である」ことが同値となる。

ここである整数 $x$ が $10^\{18\}$ の倍数であることは、 $x$ が $2^\{18\}$ と $5^\{18\}$ 両方の倍数であることと同値。
よって $b\_i$ を素因数分解したときの $2, 5$ の指数をそれぞれ $t\_i, f\_i$ とすると、
「 $b\_i b\_j$ が $10^\{18\}$ の倍数である」ことと「 $t\_i + t\_j \\geq 18$ かつ $f\_i + f\_j \\geq 18$ である」ことが同値となる。

$(t\_i, f\_i)$ 毎に個数をまとめてやれば、 $(t\_i, f\_i)$ と $(t\_j, f\_j)$ を全通り ($19^4$ 通り) 試すことで条件を満たすペアの個数が計算できる。

## 実装例

{{<code file="main.cpp" language="cpp">}}
