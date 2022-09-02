---
title: "AtCoder Beginner Contest 129 F - Takahashi's Basics in Education and Learning"
date: 2019-10-31
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/abc129/tasks/abc129_f
  - label: My Submission
    url: https://atcoder.jp/contests/abc129/submissions/8223429
---

## 問題

初項 $a$ ，公比 $b$ で長さ $l$ の等差数列を，第 1 項から連結してできる整数を $m$ で割った余りを求めよ．

### 制約

- $1 \\leq l, a, b \\lt 10\^\{18\}$
- $2 \\leq m \\leq 10\^9$
- 等差数列の項は全て $10\^\{18\}$ 未満

## 考察

まず，桁数によって数列を分割する．
$k$ 桁の要素は $[10\^\{k-1\}, 10\^k)$ に属するので， $p(x) =$ 「 $x$ 以上で最小の項」とすれば，第 $\\left[ p(10\^\{k - 1\}), p(10\^k) \\right)$ 項が $k$ 桁の区間となる．
そして $p(x) = \\lceil \\frac\{x - a\}\{b\} \\rceil$ で計算できるので，これで桁毎に分割できた．

第 $[l, r)$ 項が $k$ 桁の区間とする．ここで

$$
\\begin\{aligned\}
s\_0 &= a \\\\
c\_0 &= 0 \\\\
s\_\{n + 1\} &= s\_n + b \\\\
c\_\{n + 1\} &= 10\^k c\_n + s\_n
\\end\{aligned\}
$$

とすれば， $c\_\{r-l\}$ が $k$ 桁の項を全て連結した値となる．そしてこの数列は，

$$
\\begin\{pmatrix\}
   c\_\{m + 1\} \\\\
   s\_\{m + 1\} \\\\
   1
\\end\{pmatrix\} =
\\begin\{pmatrix\}
   10\^k & 1 & 0 \\\\
   0    & 1 & b \\\\
   0    & 0 & 1 \\\\
\\end\{pmatrix\}
\\begin\{pmatrix\}
   c\_m \\\\
   s\_m \\\\
   1
\\end\{pmatrix\}
$$

と表現できるので，行列累乗によって $\\Theta(\\log(r - l))$ で $c\_\{r - l\}$ が求められる．

## 実装例

{{<code file="0.cpp" language="cpp">}}
