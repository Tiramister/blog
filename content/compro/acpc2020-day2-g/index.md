---
title: "ACPC 2020 day2 G - Connect the dots"
date: 2020-09-23
tags: [volunteer]
links:
  - label: "Problem link"
    url: "https://onlinejudge.u-aizu.ac.jp/challenges/sources/UOA/UAPC/3506"
  - label: "My Submission"
    url: "https://onlinejudge.u-aizu.ac.jp/solutions/problem/3506/review/4866106/misteer/C++17"
---

## 問題

xy 平面上の 2 つの点が以下を満たすとき、これらは互いに「接続している」という。

- x 座標か y 座標が同じである。

xy 平面上に $N$ 個の点がある。 $i$ 番目の点の座標は $(x\_i, y\_i)$ である。
これらのうち、互いに接続しているものの間に線分が引かれている。これを「接続線」という。

いくつかの点を*接続線上に*追加することで、接続する頂点のみを辿って、点 $1$ から点 $N$ へ移動できるようにしたい。
これが可能か判定し、可能なら追加する必要のある頂点の最小個数を求めよ。

### 制約

- $2 \\leq N \\leq 10\^5$
- $|x\_i|, |y\_i| \\leq 10\^9$

## 考察

まず互いに行き来可能な頂点の集合に分ける。これは UnionFind でできる。

そのうち $j$ 番目の集合について、点が存在する領域を $[lx\_j, rx\_j] \\times [ly\_j, ry\_j]$ とする。
このとき、集合 $j$ 内の接続線上に以下の操作を行うことができる。

- 好きな $x \\in [lx\_j, rx\_j]$ について、x 座標が $x$ である点を追加できる。
- 好きな $y \\in [ly\_j, ry\_j]$ について、y 座標が $y$ である点を追加できる。

よって「点を 1 つ追加することで、 $j\_1$ 番目の集合から $j\_2$ 番目の集合へ行けるようにできる」というのは、「 $[lx\_\{j\_1\}, rx\_\{j\_1\}]$ と $[lx\_\{j\_2\}, rx\_\{j\_2\}]$ か、 $[ly\_\{j\_1\}, ry\_\{j\_1\}]$ と $[ly\_\{j\_2\}, ry\_\{j\_2\}]$ の少なくとも一方が交わる」と同値となる。

そのような集合間に辺を張ったグラフを作れば、BFS で答えが求まる。
しかし辺の本数は最大 $\\Theta(N\^2)$ になるので、陽にグラフを持つことはできない。

ここで「 $[lx\_\{j\_1\}, rx\_\{j\_1\}]$ と $[lx\_\{j\_2\}, rx\_\{j\_2\}]$ が交わる」というのを、
「 $x \\in [lx\_\{j\_1\}, rx\_\{j\_1\}]$ と $x \\in [lx\_\{j\_2\}, rx\_\{j\_2\}]$ を満たす $x$ が存在する」と言い換える。
すると以下のような解法が浮かぶ。

まず各 x 座標に対応する頂点を用意する。
そして $j$ 番目の集合からは、各 $x \\in [lx\_\{j\}, rx\_\{j\}]$ と双方向に辺を張る。ただし $x$ へ向かう方の重みを $0$ 、向かってくる方の辺を $1$ とする。
こうすることで、 $[lx\_\{j\_1\}, rx\_\{j\_1\}]$ と $[lx\_\{j\_2\}, rx\_\{j\_2\}]$ が交わるときに限り、 $j\_1$ から $j\_2$ へ( $x$ を経由して)コスト 1 で向かうことができるようになる。

座圧すれば x 座標の候補は高々 $N$ 個にできるが、辺の本数が多すぎる。
そこで「区間に対して辺を張るテク」というのを使うと、集合毎に張る辺の本数を $O(\\log n)$ 本に抑えられる。
詳しくは [こちら](https://lorent-kyopro.hatenablog.com/entry/2020/07/24/170656) を参照。

後は y 座標に対しても同様にグラフを構築し、01-BFS や Dijkstra 法で最短距離を求めればよい。

## 実装例

{{<code file="0.cpp" language="cpp">}}