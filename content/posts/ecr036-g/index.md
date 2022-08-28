---
title: "Educational Codeforces Round 36 G - Coprime Arrays"
date: 2020-09-09
tags: [codeforces]
links:
  - label: "Problem link"
    url: "https://codeforces.com/contest/915/problem/G"
  - label: "My Submission"
    url: "https://codeforces.com/contest/915/submission/92357245"
---

## 問題

$\\gcd(a\_1, \\cdots, a\_n) = 1$ であるとき、数列 $(a\_i)$ は互いに素であるという。

各整数 $1 \\leq x \\leq k$ について、 $1 \\leq a\_i \\leq x$ を満たす互いに素な長さ $n$ の整数列 $(a\_i)$ の個数を求めよ。

### 制約

- $1 \\leq n, k \\leq 2 \\cdot 10\^6$

## 考察

$x$ を固定して考える。ここで $f(g)=$ 「 $\\gcd(a\_1, \\cdots, a\_n)$ が $g$ の倍数となる $(a\_i)$ の個数」と定める。これは「各 $a\_i$ が $g$ の倍数である」と同値なので、 $f(g)=\\left\\lfloor \\frac\{x\}\{g\} \\right\\rfloor\^n$ となる。

そして約数に関する包除原理を用いると、答えは以下の式で求まる。 $\\mu(g)$ は [メビウス関数](https://ja.wikipedia.org/wiki/%E3%83%A1%E3%83%93%E3%82%A6%E3%82%B9%E9%96%A2%E6%95%B0)。

$$
\\sum\_\{g=1\}\^\{x\} f(g) \\mu(g)
$$

これを毎回愚直に計算していると間に合わないので、 $f$ が変化する箇所だけ再計算することを考える。 $\\left\\lfloor \\frac\{x\}\{g\} \\right\\rfloor$ は $x$ が $g$ の倍数のときだけ 1 増えるので、 $x$ の約数についてだけ再計算すればよい。よって再計算の回数は全体で $\\Theta(k \\log k)$ となり、間に合う。

## 実装例

TL が厳しい。毎回 $n$ べきを計算していると log が 2 つ付くので、前計算しておくと良い。
他にも「メビウス関数が 0 のものは約数に加えない」などの地味な高速化もしている。

{{<code file="0.cpp" language="cpp">}}
