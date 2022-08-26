#include <iostream>
#include <vector>

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
struct Graph { ... };

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n), ys(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    Graph<> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.span(false, --u, --v);
    }

    auto dfs = [&](auto&& f, int v, int p)
        -> std::pair<lint, lint> {
        // vを選ばなかった・選んだ場合のスコアの最大値
        lint s0 = xs[v], s1 = 0;

        for (auto e : graph[v]) {
            int u = e.dst;
            if (u == p) continue;

            auto [t0, t1] = f(f, u, v);
            // 子の値をマージ
            s0 += std::max(t0, t1);
            s1 += std::max(t0, t1 + ys[v] + ys[u]);
        }
        return std::make_pair(s0, s1);
    };

    auto [s0, s1] = dfs(dfs, 0, -1);
    std::cout << std::max(s0, s1) << "\n";
}
