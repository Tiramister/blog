---
title: "CPSCO2019 Session2 E - Mogu Mogu Gummi"
date: 2019-11-01
tags: [atcoder]
---

[E - Mogu Mogu Gummi](https://atcoder.jp/contests/cpsco2019-s2/tasks/cpsco2019_s2_e)

## 問題

頂点 $0$ を根とする $n$ 頂点の根付き木が与えられる．
頂点 $v$ は頂点 $p\_v (\\lt v)$ と耐久力 $h\_v$ の辺で結ばれている．

この木に対して，以下の操作を好きな回数だけ行う．

- $0$ 以外で $0$ と連結な頂点 $v$ を 1 つ選ぶ．
- $0$ と $v$ を結ぶパス上の辺の耐久力を $1$ 減らす．
- 耐久力が $0$ になった辺は削除される．

最終的な連結成分数の最大値を求めよ．

### 制約

- $2 \\leq n \\leq 5 \\times 10\^3$
- $1 \\leq h\_i \\leq 10\^9$

## 考察

$dp\_\{v, k\} =$ 「 $v$ を根とする部分木を $k$ 個の連結成分に分解するとき， $v$ から上に伸びる辺にかかるダメージの最小値」という DP を考える．
これは $v$ の各子 $u$ に対して再帰的に $dp\_u$ を求めて， $v$ と $u$ を切るかどうかの処理をして，それらを左からマージしていくことで求められる．

気になるのは計算量だが，実はこれが $\\Theta(n\^2)$ になるというのが俗に言う「木の二乗 DP」である．これを簡単に示す．

{{<collapse summary="計算量の証明">}}
$v$ の子をそれぞれ $u\_1, \\cdots, u\_k$ として， $u\_i$ を根とする部分木のサイズを $s\_i$ とする．また頂点 $v$ を根とする部分木のサイズを $n$ とする．

長さ $s, t$ の DP 配列のマージに時間 $2st$ かかるとき[^1]，左から順にマージしていくと全体の計算量は

[^1]: 係数の $2$ は後々計算が楽なのでつけてあるだけ．

$$
2 s\_1 s\_2 + 2 (s\_1 + s\_2) s\_3 + \\cdots + 2 (s\_1 + \\cdots + s\_\{k - 1\}) s\_k
= 2 \\sum\_\{i \\lt j\} s\_i s\_j
= \\left( \\sum\_\{i\} s\_i \\right)\^2 -  \\sum\_\{i\} \{s\_i\}\^2
$$

となる．そして $u\_i$ を根とする部分木に対して DP 配列を求めるのに $\{s\_i\}\^2$ 時間かかるとすると，右辺の第 2 項が消えて $\\left( \\sum\_\{i\} s\_i \\right)\^2 = n^2$ が残る． $\\square$
{{</collapse>}}

## 実装例

[提出 #8231839 - CPSCO2019 Session2](https://atcoder.jp/contests/cpsco2019-s2/submissions/8231839)

```cpp
#include <iostream>
#include <vector>
#include <functional>

template <class Cost = int>
struct Edge {
    int src, dst;
    Cost cost;
    Edge(int src = -1, int dst = -1, Cost cost = 1)
        : src(src), dst(dst), cost(cost){};
};

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

using lint = long long;
constexpr lint INF = 1LL << 40;

int main() {
    int n;
    std::cin >> n;

    Graph<lint> graph(n);
    for (int v = 1; v < n; ++v) {
        int p;
        lint h;
        std::cin >> p >> h;
        graph[p].emplace_back(p, v, h);
    }

    std::function<std::vector<lint>(int)> dfs =
        [&](int v) {
            std::vector<lint> cost{0};
            // i個の連結成分を作るとき，上への辺が受ける最小ダメージ

            for (auto e : graph[v]) {
                auto chcost = dfs(e.dst);

                // eを切った場合を加味する
                chcost.push_back(INF);
                for (int num = chcost.size() - 1; num >= 0; --num) {
                    if (chcost[num] > e.cost) {
                        // 部分木を分解する前にeが切れてる
                        chcost[num] = INF;
                    } else {
                        // eを切って1つ増やす
                        chcost[num + 1] = std::min(chcost[num + 1], e.cost);
                    }
                }

                // マージ
                std::vector<lint> ncost(cost.size() + chcost.size() - 1, INF);
                for (int i = 0; i < cost.size(); ++i) {
                    for (int j = 0; j < chcost.size(); ++j) {
                        ncost[i + j] = std::min(ncost[i + j],
                                                cost[i] + chcost[j]);
                    }
                }
                std::swap(cost, ncost);
            }
            return cost;
        };

    auto ans = dfs(0);
    int num;
    for (num = n - 1; num >= 0; --num) {
        if (ans[num] < INF) break;
    }
    // 根の分を加算
    std::cout << num + 1 << std::endl;
    return 0;
}
```

