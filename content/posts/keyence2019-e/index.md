---
title: "キーエンス プログラミング コンテスト 2019 E - Connecting Cities"
date: 2020-02-15
tags: [atcoder]
---

[E - Connecting Cities](https://atcoder.jp/contests/keyence2019/tasks/keyence2019_e)

## 問題

重み付き完全グラフ $G = (V, E)$ が与えられる．

頂点 $i$ には整数 $a\_i$ が割り当てられていて，各 $i \\lt j$ について，頂点 $i, j$ 間には重み $a\_j + a\_i + d(j - i)$ の辺が張られている．

このグラフの最小全域木の重みを求めよ．

### 制約

- $1 \\leq |V| \\leq 2 \\cdot 10\^5$
- $1 \\leq d, a\_i \\leq 10\^9$

## 考察

まず最小全域木の特性から．カット $(X, Y)$ について最小全域木にて $XY$ 間を結ぶ辺はちょうど 1 つあるわけだが，この辺の重みは $XY$ 間を結ぶ辺の中で最小となる．

そこで頂点を $[0, m)$ と $[m, n)$ で半分に分ける．上の定理からこれらを結ぶ辺で重みが最小のものが知りたくなるが，辺は $m(n - m)$ 本あるので全探索はできない．しかしその候補は絞ることができる．

左端 $0 \\leq u \\lt m$ を固定してしまう．すると，考えるべき辺は $m \\leq v \\lt n$ のうち辺 $uv$ の重みが最小のものだけである．従って候補は固定した各頂点に対して 1 つずつとなり，結果 $n$ 本の辺に候補を絞れる．

問題は $v$ をどう求めるかだが，辺の重みは $(a\_u - d \\cdot u) + (a\_v + d \\cdot v)$ と変形できるので， $a\_v + d \\cdot v$ が最小なものが相手になる．これは全ての $u$ に対して共通．
$v$ を固定した場合も，同様に $a\_u - d \\cdot u$ が最小なものを相手にすればいい．

後は $[0, m), [m, n)$ に対してそれぞれ再帰的に辺の候補を求めることで，全体として辺の候補は $\\Theta(n \\log n)$ 本に絞られる．後はこれに対して Kruskal 法を適用することで， $\\Theta(n (\\log n)\^2)$ でこの問題が解けた．

## 実装例

TL が結構際どいが，想定解は $\\Theta(n \\log n)$ 本なので無理もない．

[提出 #10101450 - キーエンス プログラミング コンテスト 2019](https://atcoder.jp/contests/keyence2019/submissions/10101450)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <tuple>

using lint = long long;

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Edges = std::vector<Edge<Cost>>;

struct UnionFind { ... };

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void solve() {
    int n;
    lint d;
    std::cin >> n >> d;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    MinHeap<Edge<lint>> heap;
    std::queue<std::pair<int, int>> que;
    que.emplace(0, n);

    while (!que.empty()) {
        int l, r;
        std::tie(l, r) = que.front();
        que.pop();
        if (r - l <= 1) continue;

        // 区間を分割
        int m = (l + r) / 2;
        que.emplace(l, m);
        que.emplace(m, r);

        // 左右で最もコストが小さい頂点を探す
        int li = l;
        for (int i = l + 1; i < m; ++i) {
            if (xs[i] - i * d < xs[li] - li * d) li = i;
        }
        int ri = m;
        for (int i = m + 1; i < r; ++i) {
            if (xs[i] + i * d < xs[ri] + ri * d) ri = i;
        }

        // 辺を追加
        for (int i = l; i < m; ++i) {
            heap.emplace(i, ri, xs[i] + xs[ri] + (ri - i) * d);
        }
        for (int i = m; i < r; ++i) {
            heap.emplace(li, i, xs[li] + xs[i] + (i - li) * d);
        }
    }

    // Kruskal
    lint ans = 0;
    UnionFind uf(n);
    while (!heap.empty()) {
        auto e = heap.top();
        heap.pop();

        if (uf.same(e.src, e.dst)) continue;
        ans += e.cost;
        uf.unite(e.src, e.dst);
    }

    std::cout << ans << std::endl;
}
```

