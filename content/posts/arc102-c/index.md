---
title: "AtCoder Regular Contest 102 C - Triangular Relationship"
date: 2018-09-20
tags: [atcoder]
links:
  - label: "Problem"
    url: https://atcoder.jp/contests/arc102/tasks/arc102_a
  - label: "My Submission"
    url: https://atcoder.jp/contests/arc102/submissions/3229596
---

## 概要

$N$ 以下の整数の組 $(a, b, c)$ で、 $a + b, b + c, c + a$ が全て $K$ の倍数であるものの個数を求めよ。

### 制約

- $1 \\leq N, K \\leq 2 \\times 10\^5$

## 解説

$a\' = a \\bmod K$ とおく。 $b\', c\'$ も同様。
このとき $(a + b) \\bmod K = 0 \\Leftrightarrow (a\' + b\') \\bmod K = 0$ となる。

ここで $a\'$ の値について場合分けをする。

### $a\' = 0$ の場合

$(a\' + b\') \\bmod K = 0$ より、 $b\' = 0$。
同様にして $(b\' + c\') \\bmod K = 0$ より $c\' = 0$。
これは $(c\' + a\') \\bmod K = 0$ に矛盾しない。

まとめると、 $a\' = b\' = c\' = 0$ は条件を満たす。

### $a\' \\gt 0$ の場合

$(a\' + b\') \\bmod K = 0$ より $b\' = K - a\'$。
同様にして、 $(b\' + c\') \\bmod K = 0$ より $c\' = K - b\' = a\'$。

ここで $(c\' + a\') \\bmod K = 2a\' \\bmod K = 0$ が成立する条件を考える。

- $K$ が奇数の場合。 $2a\' \\bmod K \\neq 0$ なので不成立。
- $K$ が偶数の場合。 $a\' = K / 2$ のみにて $2a\' \\bmod K = 0$ が成立。

まとめると、 $K$ が偶数の場合のみ、 $a\' = b\' = c\' = K / 2$ が条件を満たす。

### 合算

以上で全パターンが網羅できた。ではパターン数を数えてみよう。

まず $a\' = b\' = c\' = 0$ のパターン。
$1 \\sim N$ には $K$ の倍数が $\\lceil N / K \\rceil$ 個含まれている。
$a, b, c$ はそこから自由に選べるため、パターン数は $\{\\lceil N / K \\rceil\}\^3$ 通り。

次に $K$ が偶数かつ $a\' = b\' = c\' = K / 2$ のパターン。
$1 \\sim N$ には $K$ で割って $K/2$ 余る値が $\\lceil (N + K/2) / K \\rceil$ 個含まれている。
よってパターン数は $\{\\lceil (N + K/2) / K \\rceil\}\^3$ 通り。

## 実装例

{{<code file="0.cpp" language="cpp">}}
