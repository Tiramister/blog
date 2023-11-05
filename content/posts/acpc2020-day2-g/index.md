---
title: "ACPC 2020 day2 G - Connect the dots"
date: 2020-09-23
tags: [voluntary]
---

[3506 < UOA UAPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/UOA/UAPC/3506)

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

[Run #4866106 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3506/review/4866106/misteer/C++17)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
#include <tuple>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T>
std::map<T, int> compress(std::vector<T>& v) { ... }

struct UnionFind { ... };

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

template <class Cost>
std::vector<Cost> dijkstra(const Graph<Cost>& graph, int s) { ... }

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> xs[i] >> ys[i];
    }

    // 座圧
    for (int q = 0; q < 2; ++q) {
        auto nxs = xs;
        auto xrev = compress(nxs);
        for (auto& x : xs) x = xrev[x];
        std::swap(xs, ys);
    }

    // UnionFindでグループ分け
    std::vector<std::vector<int>> xvs(n), yvs(n);
    for (int i = 0; i < n; ++i) {
        xvs[xs[i]].push_back(i);
        yvs[ys[i]].push_back(i);
    }

    UnionFind uf(n);
    for (int q = 0; q < 2; ++q) {
        for (auto& vs : xvs) {
            for (int i = 0; i + 1 < (int)vs.size(); ++i) {
                uf.unite(vs[i], vs[i + 1]);
            }
        }
        std::swap(xvs, yvs);
    }

    // 各グループの領域を求める
    std::vector<int> lxs(n, n), rxs(n, -n), lys(n, n), rys(n, -n);
    for (int i = 0; i < n; ++i) {
        int g = uf.find(i);
        lxs[g] = std::min(lxs[g], xs[i]);
        rxs[g] = std::max(rxs[g], xs[i]);
        lys[g] = std::min(lys[g], ys[i]);
        rys[g] = std::max(rys[g], ys[i]);
    }

    int k = 1;
    while (k < n) k <<= 1;  // セグ木の長さ

    Graph<int> graph(n + k * 8);
    // [0   , n   ): 各グループ
    // [n   , n+2k): x座標 行き
    // [n+2k, n+4k): x座標 帰り
    // [n+4k, n+6k): y座標 行き
    // [n+6k, n+8k): y座標 帰り

    for (int t = 0; t < 2; ++t) {
        int base = n + t * k * 4;                // nかn+4k
        int lbase = base, rbase = base + k * 2;  // 行きと帰りの始点

        // セグ木の辺を張る
        for (int i = k - 1; i >= 1; --i) {
            for (int c = 0; c < 2; ++c) {
                graph.span(true, lbase + i, lbase + i * 2 + c, 0);
                graph.span(true, rbase + i * 2 + c, rbase + i, 0);
            }
        }

        // 行きから帰りへ辺を張る 重み1
        for (int i = k; i < k * 2; ++i) {
            graph.span(true, lbase + i, rbase + i, 1);
        }
    }

    // グループとセグ木の間
    for (int i = 0; i < n; ++i) {
        if (!uf.ispar(i)) continue;

        for (int t = 0; t < 2; ++t) {
            int base = n + t * k * 4;                // nかn+4k
            int lbase = base, rbase = base + k * 2;  // 行きと帰りの始点

            int l = lxs[i], r = rxs[i] + 1;  // [l, r)に辺を張る
            l += k, r += k;
            while (l < r) {
                if (l & 1) {
                    graph.span(true, i, lbase + l, 0);
                    graph.span(true, rbase + l, i, 0);
                    ++l;
                }
                if (r & 1) {
                    --r;
                    graph.span(true, i, lbase + r, 0);
                    graph.span(true, rbase + r, i, 0);
                }
                l >>= 1, r >>= 1;
            }

            std::swap(lxs[i], lys[i]);
            std::swap(rxs[i], rys[i]);
        }
    }

    auto ds = dijkstra(graph, uf.find(0));
    std::cout << ds[uf.find(n - 1)] << "\n";
}
```

