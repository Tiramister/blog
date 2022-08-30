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
