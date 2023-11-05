---
title: "CPSCO2019 Session2 G - MSTX"
date: 2019-11-01
tags: [voluntary]
---

[G - MSTX](https://atcoder.jp/contests/cpsco2019-s2/tasks/cpsco2019_s2_g)

## 問題

$n$ 頂点 $m$ 辺の重み付き無向連結グラフが与えられる．
$i$ 番目の辺は $u\_i$ と $v\_i$ を結び，その重みは $w\_i$ である．
ここで $w\_i$ は定数か，変数 $x$ である．

$q$ 個のクエリが与えられる．
$j$ 番目のクエリは整数 $a\_j$ からなる．
このとき， $x = a\_j$ としたときの最小全域木の重みを求めよ．

### 制約

- $1 \\leq n \\leq 5 \\times 10\^4$
- $n - 1 \\leq m \\leq 5 \\times 10\^4$
- $w\_i$ が定数のとき， $1 \\leq w\_i \\leq 10\^9$
- $1 \\leq q \\leq 5 \\times 10\^4$
- $1 \\leq a\_j \\leq 10\^9$

## 考察

以降 $w\_i$ は昇順に並んでいるものとする( $x$ は末尾)．
また重みが定数の辺は $l$ 本あるとする．

Kruskal 法を軸に考える．
まず， $x$ の辺なしで Kruskal 法を行い， $i$ 本使った時点での連結成分数は $g\_i$ ，重みは $c\_i$ だったとする．
次に $x$ の辺を全部使ってから Kruskal 法を行い， $x$ でない辺を $i$ 本使った時点での連結成分数は $xg\_i$ ，重みは $xc\_i$ だったとする．

ここで $w\_\{i - 1\} \\leq a\_j \\leq w\_i$ だったとする(0-indexed)．
すると $x$ の辺は $i$ 本を追加した後で全部追加されることになる．
つまり答えは

- $i$ 本目までを追加
- $x$ の辺を一気に追加
- 残りの辺を全部追加

としたときの Kruskal 法の解となる．

1 番目は普通に $c\_i$ となる．

ここで重要な事実として，「 $i$ 本目まで追加してから $x$ の辺を追加」と「 $x$ の辺を追加してから $i$ 本目まで追加」でどちらも同じ森が得られる．
よって 3 番目は $xc\_l - xc\_i$ で求まる．

残るは 2 番目だが，これは $x$ の辺が何本使われたかが分かれば良い．
辺を 1 つ追加すると連結成分数が 1 減ることから，これは $g\_i - xg\_i$ で求まる．
「森の辺数 = 頂点数 - 連結成分数」と考えても良い．

$i$ の値は二分探索で求まるので，これで $\\Theta((n + q) \\log n)$ でこの問題が解けた．

## 実装例

[提出 #8234140 - CPSCO2019 Session2](https://atcoder.jp/contests/cpsco2019-s2/submissions/8234140)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

template <class Cost = int>
struct Edge { ... };

struct UnionFind { ... };

using lint = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Edge<lint>> edges, xedges;
    // 重みが定数の辺とxの辺を分離
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        if (c == 0) {
            lint w;
            std::cin >> w;
            edges.emplace_back(u, v, w);
        } else {
            char w;
            std::cin >> w;
            xedges.emplace_back(u, v);
        }
    }

    std::sort(edges.begin(), edges.end());
    int l = edges.size();

    UnionFind uf(n), xuf(n);
    std::vector<lint> gnum(l + 1), cost(l + 1);
    gnum[0] = n, cost[0] = 0;
    // edgesのi本目まででKruskal

    std::vector<lint> xgnum(l + 1), xcost(l + 1);
    xgnum[0] = n, xcost[0] = 0;
    // xedgesを最初に使った状態で，edgesのi本目まででKruskal

    for (auto e : xedges) {
        if (xuf.same(e.src, e.dst)) continue;
        --xgnum[0];
        xuf.unite(e.src, e.dst);
    }

    for (int i = 1; i <= l; ++i) {
        gnum[i] = gnum[i - 1];
        cost[i] = cost[i - 1];
        xgnum[i] = xgnum[i - 1];
        xcost[i] = xcost[i - 1];

        auto e = edges[i - 1];
        if (!uf.same(e.src, e.dst)) {
            --gnum[i];
            cost[i] += e.cost;
            uf.unite(e.src, e.dst);
        }
        if (!xuf.same(e.src, e.dst)) {
            --xgnum[i];
            xcost[i] += e.cost;
            xuf.unite(e.src, e.dst);
        }
    }

    int q;
    std::cin >> q;
    for (int p = 0; p < q; ++p) {
        lint a;
        std::cin >> a;

        int i = std::lower_bound(edges.begin(), edges.end(),
                                 Edge<lint>(0, 0, a)) -
                edges.begin();
        // edgesをi本使った直後にxedgesが入る

        lint ans = cost[i] +
                   (gnum[i] - xgnum[i]) * a +
                   (xcost[l] - xcost[i]);
        // 減少した連結成分数 = xedgesから追加された辺数

        std::cout << ans << std::endl;
    }
    return 0;
}
```

