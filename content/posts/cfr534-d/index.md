---
title: "Codeforces Round 534 B - Game with modulo"
date: 2019-01-23
tags: [codeforces]
links:
  - label: "Problem"
    url: https://codeforces.com/contest/1103/problem/B
  - label: "My Submission"
    url: https://codeforces.com/contest/1104/submission/171320230
---

## 概要

以下のクエリを $60$ 回まで投げることで、整数 $a$ の値を特定せよ。

各クエリでは、 $0 \\leq x, y \\leq 2 \\times 10\^9$ を満たす好きな整数 $x, y$ を投げる。
すると $(x \\bmod a) \\lt (y \\bmod a)$ なら `y` 、そうでなければ `x` が返ってくる。

### 制約

- $1 \\leq a \\leq 10\^9$

## 考察

### 前半

$a$ が $x$ と比べて小さすぎる場合、 $x \\bmod\{a\}$ から得られる情報は少ない。
逆に、以下のようなケースは使えそうである。

- $x \\lt a$ のとき、 $x \\bmod\{a\} = x$ 。
- $a \\leq x \\lt 2a$ のとき、 $x \\bmod\{a\} = x - a$ 。

ここから、 $2\^p \\lt a \\leq 2\^{p+1}$ を満たす整数 $p$ について、以下が成り立つ。

$$
(2\^0 \\bmod\{a\}) \\lt (2\^1 \\bmod\{a\}) \\lt \\cdots \\lt (2\^p \\bmod\{a\}) \\gt (2\^\{p+1\} \\bmod\{a\})
$$

これを利用すると、 $\\log a$ 回以下のクエリで $p$ を求められる。具体的には、 $i$ 回目(0-indexed)のクエリで $(x, y) = (2\^\{i\}, 2\^\{i + 1\})$ を投げ、 `x` が帰ってきたら $p = i$ が確定する。

なお、 $a = 1$ の場合はこのような $p$ は存在しない。しかしこのケースは、最初に $(x, y) = (0, 1)$ のクエリを投げることで判定できる。

### 後半

$2\^p \\lt a \\leq 2\^{p+1}$ を満たす $p$ が見つかったので、後はこの中のどこに $a$ があるかを求めればいい。

まず、この区間内で以下が成り立つ。

$$
(2\^p \\bmod\{a\}) \\lt (2\^p + 1 \\bmod\{a\}) \\lt \\cdots \\lt (a - 1 \\bmod\{a\}) \\gt (a \\bmod\{a\}) \\lt \\cdots \\lt (2\^\{p + 1\} \\bmod\{a\})
$$

さらに $(2\^\{p + 1\} \\bmod\{a\}) = 2\^\{p + 1\} - a \\lt 2\^\{p + 1\} - 2\^p = 2\^p = (2\^p \\bmod\{a\})$ より、 $\\gt$ より後ろは全て $(2\^p \\bmod\{a\})$ より小さい。

以上より、以下が成り立つ。

- $2\^p \\lt y \\lt a$ のとき、 $(2\^p, y)$ のクエリの結果は `y` となる。
- $a \\leq y \\leq 2\^\{p + 1\}$ のとき、 $(2\^p, y)$ のクエリの結果は `x` となる。

よって $(2\^p, y)$ のクエリの結果が `x` となる最小の $y$ が $a$ となる。そのような $y$ は、二分探索によって $p$ 回で求められる。

## 実装例

一番外のループは非本質なので省いた。

{{<code file="0.cpp" language="cpp">}}
