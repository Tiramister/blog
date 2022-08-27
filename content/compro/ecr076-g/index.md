---
title: "Educational Codeforces Round 76 G - Divisor Set"
date: 2020-02-11
tags: [codeforces]
links:
  - label: "Problem link"
    url: "https://codeforces.com/contest/1257/problem/G"
  - label: "My Submission"
    url: "https://codeforces.com/contest/1257/submission/70782672"
---

## 問題

整数 $x$ が与えられる． $x$ は素数列 $(p\_i)$ の積で表される．

$x$ の約数の集合 $S$ であって，どの相異なる 2 要素も約数の関係にないものの考える． $|S|$ の最大値を求めよ．

### 制約

- $1 \\leq n \\leq 2 \\cdot 10\^5$
- $2 \\leq p\_i \\leq 3 \\cdot 10\^6$

## 考察

まずどのような $S$ が最適かを考えるのだが，これがかなり難しい．結論を言うと， $a$ を素因数分解したときの指数部の和を $deg(a)$ としたとき， $deg(d) = \\lfloor n / 2 \\rfloor$ なる $x$ の約数 $d$ を全部持ってくるのが最善．

まず同じ $deg$ のもの同士は互いに約数の関係にないことは明らかだろう．その上で [Hasse図](https://ja.wikipedia.org/wiki/%E3%83%8F%E3%83%83%E3%82%BB%E5%9B%B3) を眺めると， $deg$ が真ん中辺りになるほど点の数が増えていくことから最適っぽいことが分かる． [ここ](https://pure.tue.nl/ws/files/4373475/597494.pdf) にちゃんとした証明があるらしいので気になる人はどうぞ．

後は $deg$ の分布が求まれば良い．これは，素因数 $p\^q$ が増えるときに $0, 1, \\cdots, q$ 全ての幅で一気に遷移するようなナップザック DP で求まるが，これは愚直にやると $O(n\^2)$ かかる．

一方これを母関数で考えると，この遷移は $1 + x + \\cdots + x\^q$ を掛けることに等しい．よってこの掛け算に NTT を適用することで計算量が落ちる．

適当な順番で掛け算を行うと計算量は悪いままだが，次数の小さい方からマージすると $O(n \\log\^2 n)$ になる．

## 実装例

{{<code file="0.cpp" language="cpp">}}
