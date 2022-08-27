---
title: "SoundHound Inc. Programming Contest 2018 予選 E - + Graph"
date: 2020-03-04
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/soundhound2018-summer-qual/tasks/soundhound2018_summer_qual_e"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/soundhound2018-summer-qual/submissions/10530081"
---

## 問題

無向単純連結グラフ $G = (V, E)$ が与えられる．各辺 $e \\in E$ には正整数 $s(e)$ が割り振られている．

以下を満たすような各頂点への**正整数**の割り当て $c$ が何通りあるか求めよ．

- 任意の辺 $uv \\in E$ について， $c(u) + c(v) = s(uv)$ ．

### 制約

- $2 \\leq |V| \\leq 10\^5$
- $1 \\leq |E| \\leq 10\^5$
- $2 \\leq s(e) \\leq 10\^9$

## 考察

とりあえず頂点 $1$ を始点とし， $c(1) = 0$ として DFS で割り当てをしてみる．このときついでに二色塗り分けもしておく．

まず $G$ が二部グラフである場合を考える．それぞれの頂点集合を $U\_1, U\_2$ とする( $1 \\in U\_1$ )．  
このとき $c(1)$ を $x$ 増やすと，条件を保つためには任意の $v \\in U\_1$ について $c(v)$ を $x$ 増やし， $v \\in U\_2$ について $c(v)$ を $x$ 減らさないといけない．ここから，

- 最初の割り当てが invalid だった場合，答えは $0$
- valid だった場合， $U\_1, U\_2$ 内の $c$ の最小値をそれぞれ $m\_1, m\_2$ としたとき，答えは $\\max(m\_1 + m\_2 - 1, 0)$

となることが分かる．

次に $G$ が二部グラフでない場合を考える．このと両端が同じ色の辺 $uv$ が必ず存在する．
ここで $c(1)$ を $x$ 増やすと， $c(u)+c(v)$ は $2x$ 増えるか減るかしてしまう．よって $c(u)+c(v)=s(uv)$ を満たす $x$ は高々 1 通りとなる．

したがってこの $uv$ について $d = |c(u) + c(v) - s(uv)|$ としたとき，

- $d$ が奇数なら割り当ては存在しない．
- $d$ が偶数なら， $c(1) = \\frac\{d\}\{2\}$ でのみ[^1]条件を満たす可能性がある．

ことが分かる．よってこの元で再び DFS で割り当てを行い，valid かどうか判定すれば良い．

[^1]: 厳密には， $u,v$ の色によって $c(1)=\\frac\{d\}\{2\}$ か $c(1)=-\\frac\{d\}\{2\}$ のどちらが条件を満たす可能性があるかが変わる．しかし $c(1) \\gt 0, d \\geq 0$ より $\\frac\{d\}\{2\}$ だけ試せば十分．

## 実装例

{{<code file="0.cpp" language="cpp">}}
