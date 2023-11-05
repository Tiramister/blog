---
title: "ACPC 2020 day2 J - DEG MUL SUM"
date: 2020-09-24
tags: [voluntary]
---

[3509 < UOA UAPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/UOA/UAPC/3509)

## 問題

$N$ 頂点の無向グラフがある。最初辺は存在していない。

このグラフに対して、以下の操作を $Q$ 回行う。

- 頂点 $u, v$ が指定される。
- 辺 $uv$ が存在しなければ追加し、存在していれば削除する。

頂点 $v$ の次数を $d\_v$ としたとき、グラフのスコアを $\\sum\_\{uv \\in E(G)\} d\_u d\_v$ と定める。
各操作直後における、グラフのスコアを求めよ。

### 制約

- $2 \\leq N, Q \\leq 10\^5$
- $u \\neq v$

## 考察

辺を追加したときのスコアの差分を考えると、以下のようになる。

$$
d\_u d\_v + (dsum\_u - d\_v) + (dsum\_v - d\_v)
$$

ここで $dsum\_v$ は、 $v$ と隣接する頂点全ての $d$ の和である。

しかし愚直に $dsum$ を更新していると、頂点の次数は $\\Theta(N)$ になりうるので間に合わない。
そこで「次数が大きい頂点はそれほど多くない」ということに着目する。

ある定数 $M$ を固定し、次数が $M$ 以上である頂点を「大きい頂点」、そうでない頂点を「小さい頂点」と呼ぶことにする。すると大きい頂点の個数は高々 $\\frac\{2Q\}\{M\}$ 個となる。
そして $dsum$ の更新を以下のように行うことにする。

- 小さい頂点のみ、周りの $dsum$ の更新を行う。
- 大きい頂点の次数は、スコア計算で必要になったときに見る。

すると、

- $dsum$ の更新は $O(M)$ でできる。
- 周りの大きい頂点を全て見るのに $O(\\frac\{2Q\}\{M\})$ かかる。

となるので、更新とスコア計算合わせて $O(M + \\frac\{2Q\}\{M\})$ で処理できる。
よって $M \\simeq \\sqrt\{2Q\}$ とすれば、全体の計算量は $O(N + Q\\sqrt\{Q\})$ になるので間に合う。

## 実装例

削除操作に set が必要なので、厳密には計算量に $\\log N$ が付く。

更新処理に細かい場合分けがあったりするので注意。

[Run #4867532 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3509/review/4867532/misteer/C++17)

```cpp
#include <iostream>
#include <vector>
#include <set>

using lint = long long;

constexpr int M = 400;

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<std::pair<int, int>> es(q);
    std::vector<std::set<int>> tot(n);  // 全ての辺を合わせたグラフ
    for (auto& [u, v] : es) {
        std::cin >> u >> v;
        --u, --v;
        tot[u].insert(v);
        tot[v].insert(u);
    }

    // 頂点の分類
    std::vector<bool> small(n, true);         // 小さい頂点か
    std::vector<std::vector<int>> larges(n);  // 隣接する大きい頂点
    for (int v = 0; v < n; ++v) {
        if ((int)tot[v].size() < M) continue;
        small[v] = false;
        for (auto u : tot[v]) larges[u].push_back(v);
    }

    std::vector<std::set<int>> graph(n);
    std::vector<lint> ds(n, 0), dsums(n, 0);
    lint ans = 0;

    for (auto [u, v] : es) {
        if (!graph[u].count(v)) {
            // 追加
            graph[u].insert(v);
            graph[v].insert(u);
            ++ds[u], ++ds[v];

            // dsumの更新
            if (small[u]) {
                for (auto x : graph[u]) {
                    if (x == v) {
                        dsums[x] += ds[u];
                    } else {
                        ++dsums[x];
                    }
                }
            }
            if (small[v]) {
                for (auto x : graph[v]) {
                    if (x == u) {
                        dsums[x] += ds[v];
                    } else {
                        ++dsums[x];
                    }
                }
            }

            // 差分計算
            lint usum = dsums[u], vsum = dsums[v];
            // 大きい頂点を見る
            for (auto x : larges[u]) {
                if (graph[u].count(x)) usum += ds[x];
            }
            for (auto x : larges[v]) {
                if (graph[v].count(x)) vsum += ds[x];
            }

            ans += ds[u] * ds[v] + (usum - ds[v]) + (vsum - ds[u]);

        } else {
            // 削除
            // 上の逆をやればよい

            lint usum = dsums[u], vsum = dsums[v];
            for (auto x : larges[u]) {
                if (graph[u].count(x)) usum += ds[x];
            }
            for (auto x : larges[v]) {
                if (graph[v].count(x)) vsum += ds[x];
            }

            ans -= ds[u] * ds[v] + (usum - ds[v]) + (vsum - ds[u]);

            if (small[u]) {
                for (auto x : graph[u]) {
                    if (x == v) {
                        dsums[x] -= ds[u];
                    } else {
                        --dsums[x];
                    }
                }
            }
            if (small[v]) {
                for (auto x : graph[v]) {
                    if (x == u) {
                        dsums[x] -= ds[v];
                    } else {
                        --dsums[x];
                    }
                }
            }

            graph[u].erase(v);
            graph[v].erase(u);
            --ds[u], --ds[v];
        }

        std::cout << ans << "\n";
    }
}
```

