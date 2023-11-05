---
title: "キーエンス プログラミング コンテスト 2020 E - Bichromization"
date: 2020-01-19
tags: [atcoder]
---

[E - Bichromization](https://atcoder.jp/contests/keyence2020/tasks/keyence2020_e)

## 問題

$n$ 頂点 $m$ 辺の無向単純連結グラフが与えられ，頂点 $v$ には整数 $d\_v$ が割り付けられている．

可能であれば，以下を満たすように各頂点を白か黒で塗り，各辺に $1$ 以上 $10\^9$ 以下の距離を割り付けよ．

- 白および黒に塗られた頂点がそれぞれ少なくとも 1 つ存在する．
- 各頂点 $v$ について， $v$ から $v$ と異なる色の頂点への最短距離は $d\_v$ ．

### 制約

- $2 \\leq n \\leq 10\^5$
- $1 \\leq m \\leq 2 \\cdot 10\^5$
- $1 \\leq d\_i \\leq 10\^9$

## 考察

割り付けが不可能な必要十分条件は，「ある $v$ が存在して， $v$ と隣接する任意の $u$ について $d\_v \\lt d\_u$ 」である．

十分性を背理法で示す．このときある頂点 $w$ に対して $v$ から $w$ へ距離 $d\_v$ のパスが存在する．このパスは必ず $v$ と隣接するある頂点 $u$ を通るが，

- $w = u$ なら $d\_v \\leq d\_v$ より矛盾．
- $v$ と $u$ が異なる色なら $vu$ 間距離が $vw$ 間距離より短くなり矛盾．
- 同じ色なら $uw$ 間距離が $vw$ 間距離より短くなり矛盾．

ということで，どうしても矛盾が発生する．よって示された．

必要性は対偶を示す，つまり満たされないときに実際に割り付けを構築すればよい．基本方針は「最短距離の実現に十分な全域森を作り，二部グラフになるよう頂点を彩色する」というもの．

最初辺集合 $S$ は空とする．

$v$ を順に見ていく．まず $v$ と接続する距離 $d\_v$ なる辺が $S$ に存在すれば，既に条件は満たされているのでスルー(こうしないと森にならない)．

そうでないとき， $v$ と隣接する頂点 $u$ が存在して $d\_u \\leq d\_v$ となる．そこで $S$ に辺 $uv$ を追加し，辺 $uv$ の距離を $d\_v$ と定める．

これにより全域森をなす辺集合 $S$ が得られる．

任意の $uv \\in S$ に対して，その距離を $d$ とすると $d = \\min (d\_u, d\_v)$ が成り立つ．よって $d\_u \\leq d\_v$ としたとき， $u, v$ を相異なる色で塗れば，パス $uv$ が $u$ からの距離 $d\_u$ のパスとなり，かつ辺 $uv$ は $v$ からの最短距離に支障を来さない．

よってこの全域森および彩色は条件を満たす．後は選ばれなかった辺に距離 $10\^9$ を割り付ければ，これらは無視されるので条件を満たす割り付けが構成できた．

## 実装例

大分面倒な実装方針を選んでしまった．

[提出 #9591439 - キーエンス プログラミング コンテスト 2020](https://atcoder.jp/contests/keyence2020/submissions/9591439)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Edges = std::vector<Edge<Cost>>;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> ds(n);
    for (int i = 0; i < n; ++i) {
        auto& d = ds[i];
        std::cin >> d;
    }

    // 辺集合，各頂点に接続する辺番号
    Edges<int> es(m);
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        auto& e = es[i];
        std::cin >> e.src >> e.dst;
        --e.src, --e.dst;
        e.cost = 1e9;
        graph[e.src].push_back(i);
        graph[e.dst].push_back(i);
    }

    std::vector<bool> used(n, false);
    std::vector<std::vector<int>> forest(n);

    for (int v = 0; v < n; ++v) {
        if (used[v]) continue;

        // d_u <= d_vなる辺uvを探す
        int eid = -1;
        for (int i : graph[v]) {
            const auto& e = es[i];
            int u = e.src;
            if (u == v) u = e.dst;

            if (ds[u] <= ds[v]) {
                eid = i;
                break;
            }
        }

        if (eid < 0) {
            std::cout << -1 << std::endl;
            return;
        }

        // 辺を森に追加
        auto& e = es[eid];
        int u = e.src;
        if (u == v) u = e.dst;

        e.cost = ds[v];
        forest[v].push_back(u);
        forest[u].push_back(v);

        used[v] = true;
        if (ds[u] == ds[v]) used[u] = true;
        // uの条件も満たされる
    }

    // BFSで彩色
    std::vector<int> cs(n, -1);
    for (int r = 0; r < n; ++r) {
        if (cs[r] >= 0) continue;

        std::queue<int> que;
        que.push(r);
        cs[r] = 0;
        while (!que.empty()) {
            int v = que.front();
            que.pop();

            for (int u : forest[v]) {
                if (cs[u] >= 0) continue;
                cs[u] = 1 - cs[v];
                que.push(u);
            }
        }
    }

    for (auto c : cs) std::cout << "BW"[c];
    std::cout << std::endl;

    for (const auto& e : es) std::cout << e.cost << std::endl;
}
```

