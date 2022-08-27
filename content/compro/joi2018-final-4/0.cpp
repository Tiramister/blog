#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <tuple>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

using lint = long long;
constexpr lint INF = 1LL << 50;

struct Edge { ... };

using Graph = std::vector<std::vector<Edge>>;

std::vector<lint> dijkstra(const Graph& graph, int r) { ... }

void solve() {
    int n, m, s, t, a, b;
    std::cin >> n >> m >> s >> t >> a >> b;
    --s, --t, --a, --b;

    Graph graph(n);
    while (m--) {
        int u, v;
        lint c;
        std::cin >> u >> v >> c;
        --u, --v;
        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }

    // s, a, bから各点への最短距離
    auto ds = dijkstra(graph, s),
         da = dijkstra(graph, a),
         db = dijkstra(graph, b);

    // sからの距離が小さい方から見る
    std::vector<int> vs(n);
    std::iota(vs.begin(), vs.end(), 0);
    std::sort(vs.begin(), vs.end(),
              [&](int u, int v) { return ds[u] < ds[v]; });

    // dist0 = dpa
    // dist1 = dpb
    // dist2 = dp
    std::vector<std::vector<lint>>
        dist(3, std::vector<lint>(n, INF));

    for (auto v : vs) {
        // 遷移1: 全部その場で繋ぐ
        dist[0][v] = da[v];
        dist[1][v] = db[v];
        dist[2][v] = da[v] + db[v];

        // 遷移2: 全部貰ってくる
        for (auto e : graph[v]) {
            int u = e.dst;
            if (ds[u] + e.cost > ds[v]) continue;
            for (int k = 0; k < 3; ++k) {
                dist[k][v] = std::min(dist[k][v], dist[k][u]);
            }
        }

        // 遷移3, 4: 片方だけ繋ぐ
        dist[2][v] = std::min({dist[2][v],
                               dist[0][v] + db[v],
                               dist[1][v] + da[v]});
    }

    // P上の辺を使わないケース(da[b])に注意
    std::cout << std::min(da[b], dist[2][t]) << std::endl;
}
