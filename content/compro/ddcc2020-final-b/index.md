---
title: "DDCC 2020 本戦 B - Hawker on Graph"
date: 2020-01-30
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/ddcc2020-final/tasks/ddcc2020_final_b"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/ddcc2020-final/submissions/9818927"
---

## 問題

$n$ 頂点 $m$ 辺の重み付き有向グラフが与えられる． $i$ 番目の辺の重みは $c\_i$ である．

あなたはこのグラフの頂点 $s$ からちょうど $k$ 本の辺を辿って移動する(移動できない場合もある)．

また，移動に伴って*スコア*という値が変化する．あなたの最初のスコアは $w$ であり，スコア $x$ の状態で重み $c$ の辺を通るとスコアが $\\max(x + c, 0)$ に変化する．

$s$ からちょうど $k$ 本の辺を辿って移動できるか判定し，できるならば最終的なスコアの最大値を求めよ．

### 制約

- $2 \\leq n \\leq 200$
- $0 \\leq m \\leq n(n - 1)$
- $0 \\leq w \\leq 10\^\{16\}$
- $1 \\leq k \\leq 10\^9$
- $-10\^7 \\leq c\_i \\leq 10\^7$

## 考察

制約からして行列累乗だが，そのままトロピカル半環上で隣接行列を累乗しても上手くいかない．そこで辺の重みを **関数** と見ることにする．

具体的には，辺の重みを $\\lambda x.\\max(x + a, b)$ という関数と見なし，半環をなす演算を定義する．

まず和に対応するのが $\\max$ で，

$$
\\begin\{aligned\}
  &\\lambda x.(\\max(x + a, b), (\\max(x + c, d))) \\\\
= &\\lambda x.\\max(x + \\max(a, c), \\max(b, d))
\\end\{aligned\}
$$

となる．これは関数のグラフを考えれば直感的に分かる．

次に積に対応するのが関数合成である．これはかなり非自明だが， $x$ によって場合分けをすると

$$
\\begin\{aligned\}
  &\\lambda x.(\\max(\\max(x + a, b) + c), d) \\\\
= &\\lambda x. \\max(x + (a + c), \\max(b + c, d))
\\end\{aligned\}
$$

となる。

以上より，辺の重みを $(a, b) = \\lambda x.(\\max(x + a, b))$ と表すと，

$$
\\begin\{aligned\}
(a, b) + (c, d) &= (\\max(a, c), \\max(b, d)) \\\\
(a, b) \\cdot (c, d) &= (a + c, \\max(b + c, d))
\\end\{aligned\}
$$

と演算が定義できる。そしてこれらが分配法則を満たすことも確かめられる。

ただし左零元，つまり任意の $c, d$ について $0 \\cdot (c, d) = 0$ を満たす $0$ が存在しないので厳密には半環ではない．それでも零元を適当に作ってやれば半環にはなる．実装する上では $0 := (-\\infty, -\\infty)$ と定義すれば，加法について例外処理が要らないので楽。

## 実装例

{{<code file="0.cpp" language="cpp">}}
