---
title: "CODE FESTIVAL 2016 qual B E - Lexicographical disorder"
date: 2020-09-26
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/code-festival-2016-qualb/tasks/codefestival_2016_qualB_e"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/code-festival-2016-qualb/submissions/16537362"
---

## 問題

英小文字からなる $n$ 個の文字列 $(s\_i)$ が与えられる。以下の形式で与えられる $q$ 個のクエリに答えよ。

- a から z からなる、文字の比較順序を表す順列 $(p\_i)$ が与えられる。つまり $i \\lt j$ ならば、 $p\_i$ は $p\_j$ より小さい扱いとなる。
- この順序において、 $s\_k$ が $(s\_i)$ 中で辞書順で何番目かを求めよ。

### 制約

- $1 \\leq n, q \\leq 10\^5$
- $\\sum |s\_i| \\leq 4 \\cdot 10\^5 (= m)$
- $i \\neq j \\implies s\_i \\neq s\_j$

## 考察

以降、文字種数を $\\sigma(=26)$ とおく。

Trie のノードに「部分木中の $(s\_i)$ の個数」を持たせれば、根から Trie を辿ることで $O(\\sigma |s\_k|)$ でクエリを処理できる。しかしこれでは最悪 $\\Theta(\\sigma nq)$ 掛かってしまうので間に合わない。

そこで、Trie を辿るときの無駄を省くことにする。具体的には、

- 根でない
- 子を 1 つしか持たない
- どの $(s\_i)$ にも対応しない

ようなノードは、解に影響を及ぼすことはない。よってスキップすることができる。

このようなノードを省くと、Trie の深さの最大値は $\\Theta(\\sqrt\{m\})$ となる。これは $s$ に対応するパスが圧縮されないためには、 $s$ の接頭辞全てが Trie に追加されなくてはならないことによる。

よって圧縮後の Trie を使うことで、全体の計算量は $O(\\sigma \\sqrt\{m\} q)$ に落ちて間に合う。

## 実装例

{{<code file="0.cpp" language="cpp">}}
