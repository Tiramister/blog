---
title: "ICPC 2019 国内予選 F - 色の切り替え"
date: 2020-09-03
tags: [icpc]
---

[1637 < ICPC Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1637)

## 問題

$n$ 頂点の無向完全重み付きグラフが与えられる。辺 $uv$ の重みは $w\_\{uv\}$ である。
また、各辺には赤か黒のいずれかの色がついている。

これからこのグラフに対して、以下の操作を好きなだけ行う。

- $v \\in V$ を選ぶ。
- $v$ と隣接する全ての辺について、その色を反転 (赤 ↔ 黒) させる。

赤い辺からなるグラフが全域木となるようにできるか判定し、できるなら赤い辺の重みの総和の最小値を求めよ。

### 制約

- $2 \\leq n \\leq 300$
- $1 \\leq w\_\{uv\} \\leq 10\^5$

## 考察

以降、辺 $uv$ が赤いときに限り「頂点 $u, v$ は隣接している」と言うことにする。

葉である頂点 $r$ を 1 つ固定する。すると、 $r$ と接続する 1 つの頂点 ($s$ とする) 以外は全て $r$ と隣接しない。つまり $r, s$ を固定すると、初期状態における辺 $vr$ の色によって、 $v$ を反転させるか否かが一意に定まる。

ここから「 $r, s$ を全探索して、得られたグラフが全域木をなすか判定する」という解法が出てくる。しかしナイーブに全域木判定をすると $O(n\^2)$ 掛かってしまうため、全体の計算量が $O(n\^4)$ となって厳しい。

### 高速化

なぜナイーブな全域木判定に $O(n\^2)$ かかるかというと、隣接する頂点を列挙するときに、他の頂点を全て見なければいけないためである。
もし隣接している頂点だけを列挙できれば、UnionFind にてサイクルが生じた時点で列挙を打ち切ることで、 $O(n)$ で判定ができる(全域木の辺は高々 $n - 1$ 本なため)。これを実現する。

まず $r$ を固定したら、全ての頂点が $r$ と隣接しないように他の頂点を反転させる。そしてこのグラフに対して隣接リストを構築する。

この後 $s$ を固定すると、 $s$ 周りの隣接関係だけが変化する。つまり $s$ が関与しなければ、先程作った隣接リストをそのまま使える。
よって $s$ に対して適当な場合分けをすることで、隣接頂点を無駄なく列挙できるようになる。

## 実装例

以下の実装では、全域木判定にて「 $s$ と接続する辺を最初に全部加える」ことで、それ以降 $s$ と接続する辺を無視できるようにしている。

[Run #4814470 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/1637/review/4814470/misteer/C++14)

```cpp
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

struct UnionFind { ... };

constexpr int INF = 1 << 30;

bool solve() {
    int n;
    std::cin >> n;
    if (n == 0) return false;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));
    for (int v = 0; v < n; ++v) {
        for (int u = v + 1; u < n; ++u) {
            std::cin >> graph[v][u];
            graph[u][v] = graph[v][u];
        }
    }

    // vと接続する辺の色を反転
    auto flip = [&](int v) {
        for (int u = 0; u < n; ++u) {
            if (u == v) continue;
            graph[u][v] = (graph[v][u] = -graph[u][v]);
        }
    };

    int ans = INF;
    for (int r = 0; r < n; ++r) {
        // 葉rを固定

        // rが孤立するように反転
        for (int v = 0; v < n; ++v) {
            if (graph[r][v] > 0) flip(v);
        }

        // この時点で隣接リストを作成
        std::vector<std::vector<int>> adj(n);
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] > 0) adj[u].push_back(v);
            }
        }

        for (int s = 0; s < n; ++s) {
            if (r == s) continue;

            // rとsが隣接
            flip(s);

            // 全域木チェック
            UnionFind uf(n);
            bool judge = true;

            int sum = 0;
            // まずsと接続する辺から追加
            for (int v = 0; v < n; ++v) {
                if (graph[s][v] > 0) {
                    sum += graph[s][v];
                    uf.unite(s, v);
                }
            }

            // 次にsと接続しない辺を追加
            for (int v = 0; v < n; ++v) {
                if (v == s) continue;

                for (auto u : adj[v]) {
                    if (u == s || u > v) continue;

                    // サイクルができたら打ち切り
                    if (uf.same(u, v)) {
                        judge = false;
                        break;
                    }

                    uf.unite(u, v);
                    sum += graph[u][v];
                }

                if (!judge) break;
            }

            if (judge && uf.gnum == 1) {
                ans = std::min(ans, sum);
            }

            flip(s);
        }
    }

    std::cout << (ans == INF ? -1 : ans) << "\n";
    return true;
}
```

