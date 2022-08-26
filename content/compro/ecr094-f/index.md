---
title: "Educational Codeforces Round 94 F. x-prime Substrings"
date: 2020-09-11
tags: [codeforces, div2]
links:
  - label: "Problem link"
    url: "https://codeforces.com/contest/1400/problem/F"
  - label: "My Submission"
    url: "https://codeforces.com/contest/1400/submission/91178679"
---

## 問題

数字からなる文字列 $s$ に対して、 $f(s)$ をその総和とする。

文字列 $s$ が $f(s) = x$ かつ以下を満たす連続部分文字列 $t$ を持た**ない**とき、 $s$ は $x$ -prime という。

- $f(t) \\neq x$
- $x$ は $f(t)$ で割り切れる。

1 から 9 からなる文字列 $s$ が与えられる。 $s$ から最小何文字消せば、 $s$ が $x$ -prime な連続部分文字列を持たなくなるか求めよ。

### 制約

- $1 \\leq |s| \\leq 10\^3$
- $1 \\leq x \\leq 20$

## 考察

まず桁和が $x$ である文字列は全部で $2\^\{x-1\}$ 通りなので、 $x$ -prime な文字列を列挙することができる。
実験してみると分かるが、制約下における $x$ -prime な文字列の最大数は、 $x=19$ での $2399$ 個でかなり少ない。

$x$ -prime な文字列を列挙したら、後は禁止文字列 DP をすればよい。
禁止文字列 DP は蟻本の P.331 に載っていて、要は Trie のノードを状態とする DP。
先に述べたように $x$ -prime な文字列は少ないので、Trie のノード数も十分少ない。

この DP では「今いるノードから遷移できない文字が来たとき、どのノードへ飛ぶべきか？」というのを前計算する必要がある。今いるノードの最長の接尾辞に当たるノードに飛ぶべきなのだが、これは文字列を愚直に前から削っていくと求められる。

ちなみにこれをノード数について線形時間で求めるのが Aho-Corasick 法。 [このブログ](https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick) の解説が分かりやすい。

## 実装例

以下の実装では Aho-Corasick 法を使っている。

{{<code file="0.cpp" language="cpp">}}
