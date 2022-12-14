---
title: "JAG 夏合宿 2014 day2C - Clique Coloring"
date: 2020-09-04
tags: [icpc, voluntary]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Summer/2631?year=2014"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/2631/review/4816018/misteer/C++14"
---

## 問題

長さ $n$ の整数列 $(a\_i)$ が与えられる。以下を満たすような頂点の選び方が存在する、最小の $m$ を求めよ。

- $m$ 頂点完全グラフがある。最初全ての辺に色はついていない。
- 各 $i$ に対して $a\_i$ 個の頂点を選び、それらの間に張られている辺を全て色 $i$ で塗る。
- 最終的に 2 色以上で塗られた辺は存在しなかった。

### 制約

- $1 \\leq n \\leq 5$
- $2 \\leq a\_i \\leq 10\^9$

## 考察

各 $i$ について、選ばれた頂点集合を $U\_i$ とする ($|U\_i| = a\_i$)。
すると「最終的に 2 色以上で塗られた辺は存在しなかった」という条件は、「任意の $i \\neq j$ について、 $|U\_i \\cap U\_j| \\lt 2$ 」と同値となる。
一方で $m$ を最小化するためには、 $(U\_i)$ はできるだけ互いに多くの共通部分を持っている方がよい。

以降 $(a\_i)$ は降順に並んでいるものとする。ここで $a\_1 \\geq n - 1$ の場合、以下のように $U\_1$ と他の集合がそれぞれ相異なる 1 点で交わるようにするのが最善となる。

{{<image src="0.png">}}

このように配置した場合、残りは各 $a\_i$ が 1 ずつ減ったケースに帰着される( $a\_i = 0$ なら消す)ので、帰納的に解くことができる。

そうでない場合、 $m$ の小さい方から $U\_i$ の選び方を全探索する。最大ケースは $(3, 3, 3, 3, 3)$ だが、これは以下のように $m = 7$ で達成できる。

{{<image src="1.png">}}

つまり全探索は $m \\leq 7$ で止まる。そして以下の式から分かるように、計算量もそこまで大きくならない。

$$
\\prod\_\{i=1\}\^\{n\} \\binom\{m\}\{a\_i\} \\leq \\binom\{7\}\{3\}\^5 \\leq 5.3 \\cdot 10\^7
$$

## 実装例

{{<code file="0.cpp" language="cpp">}}
