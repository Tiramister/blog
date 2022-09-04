---
title: "AtCoder Regular Contest 079 F - Namori Grundy"
date: 2019-11-15
tags: [atcoder]
links:
  - label: Problem link
    url: https://atcoder.jp/contests/arc079/tasks/arc079_d
  - label: My Submission
    url: https://atcoder.jp/contests/arc079/submissions/8436228
---

## 問題

$n$ 頂点 $n$ 辺の弱連結な有向グラフが与えられる． $i$ 番目の辺は頂点 $p\_i$ から $i$ に伸びている．

このとき，以下を満たす長さ $n$ の整数列 $(a\_i)$ が存在するか判定せよ．

- 任意の辺 $uv$ について $a\_u \\neq a\_v$ ．
- 任意の $u$ と $0 \\leq x \\lt a\_u$ なる $x$ について，ある $v$ が存在して辺 $uv$ が存在しかつ $a\_v = x$ ．

### 制約

- $2 \\leq n \\leq 2 \\times 10\^5$

## 考察

全ての子に既に割り当てが決定している場合，その MEX(Minimum EXcluded)がその頂点に割り当てられる．
よって出自数が 0 の頂点から割り当てを決めて，その頂点を消すことで連鎖的に割り当てを進めることができる．

ただしこの割り当ては最後まで行かない．最終的に 1 つのサイクルが残るためである．弱連結という前提から，2 つ以上のサイクルが残ることはない．

ここでサイクルの 1 つの頂点を選び，その子に割り当てられた整数の集合を $S$ とする． $S$ の MEX を $m$ とすると，この頂点に割り当てられるのは $m$ か $S \\cup \\\{ m \\\}$ の MEX かの 2 択となる．そしてこれのどっちを選ぶかを決めてしまえば，残りは一意に割り当てられる．
よってこの選択を全探索することで全ての可能性を潰すことができる．

## 実装例

サイクルが残ってから先だけ分岐させればいいが，実装が闇そうだったので一番最初から分岐させることにした．

{{<code file="0.cpp" language="cpp">}}