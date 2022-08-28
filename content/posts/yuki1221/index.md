---
title: "yukicoder No.1221 木 *= 3"
date: 2020-09-04
tags: [yukicoder]
links:
  - label: "Problem link"
    url: "https://yukicoder.me/problems/no/1221"
  - label: "My Submission"
    url: "https://yukicoder.me/submissions/547414"
---

## 問題

$n$ 頂点の木が与えられ、頂点 $i$ には整数 $a\_i, b\_i$ が割り当てられている。
これから各頂点を赤か白で塗る。1 つの塗り方に対して、スコアが以下のように計算される。

- 頂点 $i$ が白なら、スコアに $a\_i$ を加算する。
- 頂点 $i$ が赤なら、隣接する赤い頂点の個数を $d$ としたとき、スコアに $b\_i \\cdot d$ を加算する。

スコアの最大値を求めよ。

### 制約

- $1 \\leq n \\leq 10\^5$
- $-10\^9 \\leq a\_i, b\_i \\leq 10\^9$

## 考察

適当な頂点を根として木 DFS をする。より具体的には、各部分木に対して、その根を塗った色に応じて最大スコアを求める。

根 $u$ とその子 $v$ が共に赤いケースでの遷移が若干非自明だが、これは $b\_u + b\_v$ を足すことで対処できる。 $u, v$ それぞれについて、隣接する赤い頂点が 1 つずつ増えたと考えれば良い。

## 実装例

{{<code file="0.cpp" language="cpp">}}
