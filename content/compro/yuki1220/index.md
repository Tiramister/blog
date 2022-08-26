---
title: "yukicoder No.1220 yukipoker"
date: 2020-09-04
tags: [yukicoder]
links:
  - label: "Problem link"
    url: "https://yukicoder.me/problems/no/1220"
  - label: "My Submission"
    url: "https://yukicoder.me/submissions/548073"
---

## 問題

$m$ 種類のスートからなり、スート毎に $1, \\cdots, n$ のカードが 1 枚ずつ含まれる、計 $nm$ 枚のカードからなるトランプがある。

このトランプ 1 セットから $k$ 枚のカードを無作為に選ぶ。このとき、以下の 2 つの役のうち、どちらの役の方が成立する確率が高いか求めよ。

- フラッシュ: $k$ 枚全てのスートが同じ。
- ストレート: $k$ 枚に書かれた数字が連続している。

### 制約

- クエリ数 $\\leq 10\^5$
- $1 \\leq n, m \\leq 10\^5$
- $1 \\leq k \\leq n$

## 考察

実際にフラッシュ、ストレートとなる引き方の通り数 $F, S$ を考えると、以下のようになる。

$$
\\begin\{aligned\}
   F &= m \\binom\{n\}\{k\} = \\frac\{m \\cdot n!\}\{k! (n-k)!\} \\\\
   S &= (n - k + 1) \\cdot m\^k
\\end\{aligned\}
$$

しかしこのままでは大きすぎて比べられない。そこで**対数**を取ることにする。

$$
\\begin\{aligned\}
   \\log F &=
       \\log m + s\_n - s\_k - s\_\{n - k\} \\\\
   \\log S &= \\log(n - k + 1) + k \\log m
\\end\{aligned\}
$$

ここで $s\_p = \\log p! = \\sum\_\{i=1\}\^\{p\} \\log i$ で、これは前計算しておけば $\\Theta(1)$ で求まる。

## 実装例

$\\log(1 + x)$ を求める関数`std::log1p`というのが存在する。精度が高くなるらしい。

{{<code file="0.cpp" language="cpp">}}
