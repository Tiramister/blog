---
title: "Educational Codeforces Round 94 G - Mercenaries"
date: 2020-08-27
tags: [codeforces, div2]
links:
  - label: "Problem link"
    url: "https://codeforces.com/contest/1400/problem/G"
  - label: "My Submission"
    url: "https://codeforces.com/contest/1400/submission/91094127"
---

## 問題

$n$ 頂点 $m$ 辺の無向グラフ $(V, E)$ が与えられる。以下を全て満たす $S \\subseteq V$ の個数を求めよ。

- $S \\neq \\emptyset$
- $v \\in S \\implies l\_v \\leq |S| \\leq r\_v$
- $uv \\in E \\implies u \\not \\in S \\lor v \\not \\in S$

### 制約

- $1 \\leq n \\leq 3 \\cdot 10\^5$
- $0 \\leq m \\leq 20$
- $1 \\leq l\_v \\leq r\_v \\leq n$

## 考察

まず $|S| = x$ を先に固定してしまうことにする。こうすることで選べる頂点の集合 $T$ が定まり、「辺に関する制約を満たすサイズ $x$ の集合 $S \\subseteq T$ はいくつか？」を求めればよいことになる。

$x$ を変える度に $T$ を計算していると $\\Theta(n\^2)$ かかるが、これは $x$ を昇順に見て、差分だけ計算することで $\\Theta(n)$ で処理できる。というのも、各頂点が $T$ に出入りするのは 2 回だからである。

次に辺に関する制約だが、これは「 $S$ が独立集合である」ことと同値である。

ここで $m$ が非常に小さいことに着目する。条件を満た**さない**辺集合 $E\' \\subseteq E$ について包除原理を適用すると、独立集合のサイズ毎の個数は $\\Theta(n 2\^m)$ で求められる。 [この問題](https://atcoder.jp/contests/abc152/tasks/abc152_f) と要領は全く同じ。

さらに孤立点は選ぶ・選ばないを自由に選べるので、本質的な計算は必要ない。そこで非孤立点のみを考慮することで、計算量は $O(m 2\^m)$ に落ちる。

後は非孤立点からいくつ選ぶかを全探索することで、サイズ $x$ の独立集合の個数が $\\Theta(m)$ で求まる。
最大独立集合の再計算を非孤立点の集合が変わったときだけにすれば、全体の計算量は $O(nm + m\^2 2\^m)$ となり、辛うじて TL に間に合う。

## 実装例

{{<code file="0.cpp" language="cpp">}}
