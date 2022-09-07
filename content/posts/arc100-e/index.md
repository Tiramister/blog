---
title: "AtCoder Regular Contest 100 E - Or Plus Max"
date: 2019-09-02
tags: [atcoder]
links:
  - label: "Problem link"
    url: https://atcoder.jp/contests/arc100/tasks/arc100_c
  - label: "My Submission"
    url: https://atcoder.jp/contests/arc100/submissions/34675335
---

## 問題

長さ $2\^N$ の数列 $(A\_i)$ (0-indexed)が与えられる。
$k = 1, 2, 3, \\dots, 2\^N$ に対し、 $\\max \\\{ A\_i + A\_j \\mid i \\neq j, \\; i \\lor j \\leq k \\\}$ を求めよ。

ここで $\\lor$ は bitwise or を表す。

### 制約

- $1 \\leq N \\leq 18$
- $1 \\leq A\_i \\leq 10\^9$

## 考察

### 問題の言い換え

$[N] = \\\{ 0, 1, \\cdots, N - 1 \\\}$ と定める。
また集合 $S \\subseteq [N]$ と整数 $\\sum\_\{i \\in S\} 2\^i$ を同一視する。これにより、集合における和集合 $\\cup$ と、整数における bitwise or $\\lor$ が等価になる。

$k = 1, \\dots, 2\^N$ に対し、 $\\max \\\{ A\_i + A\_j \\mid i \\neq j, \\; i \\lor j \\textcolor\{pink\}\{=\} k \\\}$ の累積 max がこの問題の解となる。よって代わりに以下の問題 A' を解きたくなる。

{{<framed>}}
**問題 A'**
: 空でない全ての集合 $U \\subseteq [N]$ に対し、 $\\max \\\{ A\_S + A\_T \\mid S \\neq T, \\; S \\cup T = U \\\}$ を求めよ。
{{</framed>}}

しかし $S \\cup T = U$ という条件はとても扱いにくい。そこで代わりに $S \\cup T \\textcolor\{pink\}\{\\subseteq\} U$ とする。 $S \\cup T \\subsetneq U$ のケースが入ってしまうが、この場合 $S \\cup T \\lt U$ なので、どのみち累積 max で取り込まれる。

よって以下の問題 A を解いて、累積 max を取ればいい。 $S \\cup T \\subseteq U \\iff S, T \\subseteq U$ に注意。

{{<framed>}}
**問題 A**
: 空でない全ての集合 $U \\subseteq [N]$ に対し、 $\\max \\\{ A\_S + A\_T \\mid S \\neq T, \\; S, T \\subseteq U \\\}$ を求めよ。
{{</framed>}}

$A\_S + A\_T$ を最大化するには、 $A\_i$ を大きい方から 2 つ取ってくるのが最善である。つまり問題 A は以下の問題 B に言い換えられる。

{{<framed>}}
**問題 B**
: 空でない全ての集合 $S \\subseteq [N]$ に対し、 $\\\{ A\_T \\mid T \\subseteq S \\\}$ の中で最も大きい要素上位 2 つを求めよ。
{{</framed>}}

### 問題 B の解法

空でない $S \\subseteq [N]$ に対して、 $\\\{ A\_T \\mid T \\subseteq S \\\}$ の中で最も大きい要素 2 つを $\\mathcal\{A\}_S$ とする。 $|S| = 1$ の場合は明らかに $\\mathcal{A}_S = \\\{ A\_\{\\emptyset\}, A\_S \\\}$ となる。

$|S| \\geq 2$ の場合、 $\\mathcal\{A\}\_S \\subseteq \\left( \\bigcup\_\{ i \\in S \} \\mathcal\{A\}\_\{S \\setminus \\\{i\\\} \} \\right) \\cup \\\{ A_S \\\}$ となる。
$\\left| \\left( \\bigcup\_\{ i \\in S \} \\mathcal\{A\}\_\{S \\setminus \\\{i\\\} \} \\right) \\cup \\\{ A_S \\\} \\right| \\leq 2 |S| + 1$ なので、和集合を取ってからソートして上から 2 つ取れば計算量は $O(N \\cdot 2\^N)$ となる。

## 実装例

{{<code file="0.cpp" language="cpp">}}
