---
title: yukicoder No.1302 Random Tree Score
date: 2020-11-28
tags: [yukicoder]
links:
  - label: Problem link
    url: https://yukicoder.me/problems/no/1302
  - label: My Submission
    url: https://yukicoder.me/submissions/586123
---

## 問題

$N$ 頂点ラベル付き木で、頂点 $v$ の次数が $d\_v$ であるような木のスコアを $\\prod\_\{v\} d\_v$ と定める。

$N$ 頂点ラベル付き木は全部で $N^\{N-2\}$ 個あるが、それらのスコアの平均値 $\\pmod\{998,244,353\}$ を求めよ

### 制約

- $2 \\leq N \\leq 10^5$

## 考察

まず頂点 $v$ の次数が $d\_v$ であるような $N$ 頂点ラベル付き木の個数は、以下で表される。

$$
(N-2)! \\prod\_v \\frac\{1\}\{(d\_v - 1)!\}
$$

これは「Prüfer コード」を使うと求められる ([参考記事](https://37zigen.com/prufer-code/))。
ということで、スコアの平均は以下の式で求まる。

$$
\\frac\{(N-2)!\}\{N^\{N-2\}\} \\sum\_\{(d\_v): \\sum\_v d\_v = 2(N-1)\} \\prod\_v \\frac\{d\_v\}\{(d\_v - 1)!\}
$$

$\\frac\{(N-2)!\}\{N^\{N-2\}\}$ は最後に掛けることにして、以降は以下の値をどう計算するか考える。

$$
\\sum\_\{(d\_v): \\sum\_v d\_v = 2(N-1)\} \\prod\_v \\frac\{d\_v\}\{(d\_v - 1)!\}
$$

まずこの値は、 $f(x) = \sum_{k=1}^{\infty} \frac{k}{(k - 1)!}x^k$ という形式的冪級数によって $[x^{2(N-1)}]f^N(x)$ と表せる。
さらにこの $f(x)$ は、 $F(x) = xe^x = \sum_{k=1}^{\infty} \frac{x^k}{(k-1)!}$ によって $f(x) = xF'(x) = x(1 + x)e^x$ と表せる。

よって $[x^{2(N-1)}]f^N(x) = [x^{2(N-1)}] x^N (1+x)^N e^{Nx} = [x^{N-2}] (1+x)^N e^{Nx}$ と変形できる。後は

$$
\\begin\{align\}
(1+x)^N &= \\sum\_\{k=0\}^\{N\} \\binom\{N\}\{k\} x^k \\\\
e^\{Nx\} &= \\sum\_\{k=0\}^\{\\infty\} \\frac\{N^k\}\{k!\} x^k
\\end\{align\}
$$

を使えば値が求まる。

## 実装例

{{<code file="main.cpp" language="cpp">}}
