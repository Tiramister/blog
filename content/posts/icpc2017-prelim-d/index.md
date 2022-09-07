---
title: "ICPC 2017 国内予選 D - 弁当作り"
date: 2019-06-16
tags: [icpc]
links:
  - label: "Problem Link"
    url: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1619?year=2017
  - label: "My Submission"
    url: https://onlinejudge.u-aizu.ac.jp/solutions/problem/1619/review/3659593/misteer/C++14
---

## 問題

長さ $M$ の bit 列が $N$ 個与えられる。
全体の XOR が $0$ となるような部分集合の、要素数の最大値を求めよ。

### 制約

- $1 \\leq N, M \\leq 500$
- $1 \\leq NM \\leq 500$

## 考察

この問題の肝は「 $1 \\leq NM \\leq 500$ 」という制約で、ここから「 $N \\leq 23$ と $M \\leq 23$ のいずれかが成立する」ことが分かる。
したがって、 **常に $N$ か $M$ のいずれかで bit 全探索ができる** 。

まず $N \\leq 23$ のとき。
これは bit 列の集合を全探索して $0$ になるか判定すればいい。
ただし最大で $M = 500$ になるので、bitset で入力を持つと良いだろう。

次に $M \\leq 23$ のとき。
これは $dp\_b =$ 「全体の XOR が $b$ となるような部分集合の、要素数の最大値」という bitDP で解ける。 $N$ 個配列を取るとメモリ不足が怖いので、DP テーブルを使い回すのが良いと思われる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
