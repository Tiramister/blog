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
