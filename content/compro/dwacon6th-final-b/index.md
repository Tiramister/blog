---
title: "第 6 回 ドワンゴからの挑戦状 本選 B - Harvest Festival"
date: 2020-02-09
tags: [atcoder]
links:
  - label: "Problem link"
    url: "https://atcoder.jp/contests/dwacon6th-final"
  - label: "My Submission"
    url: "https://atcoder.jp/contests/dwacon6th-final/submissions/9964494"
---

## 問題

$n$ 頂点 $m$ 辺の単純無向重み付きグラフが与えられる．辺 $i$ の重みは $d\_i$ ．
さらに，頂点集合の部分集合 $W \\subseteq V$ が与えられる．

$S \\subseteq V$ に対して， $f(S)$ を「 $W$ のうち， $S$ の任意の頂点からの距離が $l$ 以内である頂点の集合」と定める．より形式的には，以下のように定める．

$$
f(S) = \\\{ w \\in W \\mid \\forall v \\in S, \\; d(v, w) \\leq l \\\}
$$

各 $T \\subseteq W$ について， $f(S) = T$ なる $\\emptyset \\neq S \\subseteq V$ の個数を求めよ[^output]．

[^output]: 実際は $\\bmod 998,244,353$ を取ったものの XOR を出力する．

### 制約

- $1 \\leq n \\leq 10\^5$
- $0 \\leq m \\leq 2 \\times 10\^5$
- $1 \\leq |W| (= k) \\leq 20$
- $1 \\leq l, d\_i \\leq 10\^9$

## 考察

まず各 $w \\in W$ について，そこから距離 $l$ 以内の頂点集合を $U\_w$ とする．これは Dijkstra 法により $O(k (n + m) \\log m)$ で求まる．

これを拡張して， $T \\subseteq W$ について， $U\_T = \\bigcap\_\{w \\in T\} U\_w$ と定める．
つまり $U\_T$ は「 $T$ の任意の頂点から距離 $l$ 以内の頂点集合」である．

すると，任意の $S \\subseteq U\_T$ について $f(S) \\supseteq T$ が成り立つ．しかしこれは「ぴったり」，つまり $f(S) = T$ になっていない．
それでもこれは **メビウス変換** によって「ぴったり」にできる．

具体的には， $f(S) \\supseteq T$ を満たすものから $f(S) \\supsetneq T$ を満たすものを抜けばいい．
言い換えると， $U\_T$ から各 $T\' \\supsetneq T$ について $U\_\{T\'\}$ を抜けばいい．
よって $|U\_T|$ さえ求まっていれば， **高速メビウス変換** によって $O(k 2\^k)$ で解が求まる．

$|U\_T|$ を求めるアルゴリズムとして，「各 $v \\in V$ について $X\_v = \\\{ w \\subseteq W \\mid d(v, w) \\leq l \\\}$ を求め，各 $T \\subseteq X\_v$ に対して $|U\_T|$ を増やす」という方法を考える．
そのままでは $O(n 2\^k)$ で間に合わないのだが，

- 各 $v \\in V$ について $|U\_\{X\_v\}|$ を 1 増やす．
- これに対して(上位集合の) **高速ゼータ変換** を行う．

とすることで $O(nk + k 2\^k)$ に落ちて間に合う．

## 実装例

{{<code file="0.cpp" language="cpp">}}
