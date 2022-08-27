---
title: "yukicoder No.980 Fibonacci Convolution Hard"
date: 2020-02-01
tags: [yukicoder]
links:
  - label: "Problem link"
    url: "https://yukicoder.me/problems/no/980"
  - label: "My Submission"
    url: "https://yukicoder.me/submissions/424001"
---

## 問題

数列 $(a\_i)$ を以下の漸化式で定める．

- $a\_1 = 0, a\_2 = 1$
- $a\_n = p a\_\{n - 1\} + a\_\{n - 2\} \\quad (n \\geq 3)$

$q$ 個のクエリが与えられる． $i$ 番目のクエリでは，整数 $m\_i$ に対し $\\sum\_\{s + t = m\_i\} a\_s a\_t$ を求めよ．

### 制約

- $1 \\leq p \\leq 10\^9$
- $1 \\leq q \\leq 2 \\cdot 10\^5$
- $2 \\leq m\_i \\leq 2 \\cdot 10\^6$

## 考察

$b\_i = \\sum\_\{s + t = i\} a\_s a\_t$ とすると， $(a\_i), (b\_i)$ の母関数はそれぞれ $F(x) = \\sum\_\{i = 0\}\^\{\\infty\} a\_i x\^i$ ， $G(x) = \\sum\_\{i = 0\}\^\{\\infty\} b\_i x\^i$ となる( $a\_0 = 0$ とする)．
すると $(b\_i)$ は $(a\_i)$ の和に関する畳み込みなので， $G(x) = (F(x))\^2$ が成り立つ．

さらに $a\_n - pa\_\{n - 1\} - a\_\{n - 2\} = 0$ から，項をずらして打ち消させる要領で，

$$
F(x) = \\frac\{x\^2\}\{1 - px - x\^2\}
$$

が成り立つ[^1]．ここから，

[^1]: より詳しくは [この記事](https://science-log.com/%E3%83%9B%E3%83%BC%E3%83%A0%E3%83%9A%E3%83%BC%E3%82%B8/%E6%95%B0%E5%AD%A6top%E3%83%9A%E3%83%BC%E3%82%B8/%E8%A7%A3%E6%9E%90top/%E6%AF%8D%E9%96%A2%E6%95%B0%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6/%EF%BC%93%EF%BC%8E%E6%AF%8D%E9%96%A2%E6%95%B0%E3%81%AE%E5%BF%9C%E7%94%A8%EF%BD%9E%E4%B8%80%E8%88%AC%E9%A0%85%E3%81%AE%E5%B0%8E%E5%87%BA/) を参照．

$$
G(x) = (F(x))\^2 = \\frac\{x\^4\}\{(1 - px - x\^2)\^2\} =
\\frac\{x\^4\}\{1 - 2px + (p\^2 - 2) x\^2 + 2px\^3 + x\^4\}
$$

となる．最後にさっきの $F(x)$ に施した変形の逆操作を考えると，

- $b\_1 = b\_2 = b\_3 = 0, b\_4 = 1$
- $b\_n = 2pb\_\{n - 1\} - (p\^2 - 2)b\_\{n - 2\} - 2pb\_\{n - 3\} - b\_\{n - 4\}$

という漸化式が立つ．後はこれを必要な分だけ前計算しておけばよい．

## 実装例

{{<code file="0.cpp" language="cpp">}}
