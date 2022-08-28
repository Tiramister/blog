#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

struct UnionFind { ... };

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    Graph<> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.span(false, --u, --v);
    }

    lint ans = 0;

    std::vector<int> vs(n);
    std::iota(vs.begin(), vs.end(), 0);

    for (int q = 0; q < 2; ++q) {
        // vをx_vについて昇順に並べる
        std::sort(vs.begin(), vs.end(),
                  [&](int u, int v) { return xs[u] < xs[v]; });

        UnionFind uf(n);
        std::vector<bool> visited(n, false);

        for (auto v : vs) {
            visited[v] = true;

            lint c2sum = 0;
            for (auto e : graph[v]) {
                int u = e.dst;
                if (!visited[u]) continue;

                lint sz = uf.size(u);
                c2sum += sz * sz;

                uf.unite(u, v);
            }

            lint sz = uf.size(v);
            ans += (sz * sz - c2sum) * xs[v];
        }

        for (auto& x : xs) x = -x;
    }

    std::cout << ans / 2 << "\n";
}
