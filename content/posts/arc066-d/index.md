---
title: "AtCoder Regular Contest 066 D - Xor Sum"
date: 2019-02-26
tags: [atcoder]
links:
  - label: "Problem Link"
    url: https://atcoder.jp/contests/arc066/tasks/arc066_b
---

## 概要

正の整数 $N$ が与えられる。このとき、

- $a + b = u$
- $a \\oplus b = v$

なる非負整数の組 $(a, b)$ が存在し、かつ $0 \\leq u, v \\leq N$ を満たすような $(u, v)$ の組の個数を求めよ。

ここで $\\oplus$ は bitwise xor を表す。

### 制約

- $1 \\leq N \\leq 10\^\{18\}$

## 考察

### 観察

まず、 $+$ と $\\oplus$ の間には以下のような性質がある。

- $a \\oplus b \\geq 0$
- $(a + b) - (a \\oplus b) = (a \\land b) \\times 2 \\geq 0$

ここから $0 \\leq u \\leq v$ という関係がわかる。よって $v$ を $0$ から $N$ の間で固定して、それぞれ $u$ が何通りの値を取りうるかを考えることにする。

ここで、 $a \\oplus b$ を最下位 bit から順に決めていくことを考える。 $v = a + b$ の最下位 bit について場合分けすると以下の通り。

- $v$ の最下位 bit が 1(つまり奇数)の場合

  最下位 bit にだけ注目すると、 $(a, b) = (0, 1), (1, 0)$ となる。 $a \\oplus b$ の最下位 bit はどちらも 1 で、繰り上がりは常になし。

- $v$ の最下位 bit が 0(つまり偶数)の場合

  最下位 bit にだけ注目すると、 $(a, b) = (0, 0), (1, 1)$ となる。 $a \\oplus b$ の最下位 bit はどちらも 0 だが、繰り上がりの有無によりそこから先が異なる。

以上を踏まえると、 $v$ を固定したときに $a \\oplus b$ の取りうる値の数は以下のような再帰関数によって求まる。

{{<code file="0.cpp" language="cpp" title="遅い解法">}}

## 高速化

このままではメモ化しても $O(N \\log N)で$ TLE なので、 $v \\in \\\{0, 1, \\cdots, M\\\}$ を一気に処理することで高速化する。

上の遷移が奇数と偶数で分かれているので、こちらも $v$ を奇数と偶数のグループに分ける。

- 奇数グループ

  奇数グループは $\\\{1, 3, \\cdots, 2 \\lfloor (M - 1) / 2 \\rfloor + 1\\\}$ となる。これらは $\\\{0, 1, \\cdots, \\lfloor (M - 1) / 2 \\rfloor\\\}$ へと遷移する。

- 偶数グループ

  偶数グループは $\\\{0, 2, \\cdots, 2 \\lfloor M / 2 \\rfloor\\\}$ となる。

  繰り上がり無しの場合、これらは $\\\{0, 1, \\cdots, \\lfloor M / 2 \\rfloor\\\}$ へと遷移する。

  繰り上がり有りの場合は注意が必要で、 $0$ からは遷移ができない。よって $M \\lt 2$ のケースを弾く必要がある。
  そうでない場合、 $\\\{2, 4, \\cdots, 2\\lfloor M / 2 \\rfloor\\\}$ は $\\\{0, 1, \\cdots, \\lfloor M / 2 \\rfloor - 1\\\}$ へと遷移する。

以上をメモ化再帰で実装すれば、計算量 $O(\\log N)$ で解が求まる。

## 実装例

{{<code file="1.cpp" language="cpp">}}
