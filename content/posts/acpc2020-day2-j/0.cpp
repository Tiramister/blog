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
