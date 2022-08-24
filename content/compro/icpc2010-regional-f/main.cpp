#include <iostream>
#include <vector>
#include <queue>

// Graph, Dijkstra

bool solve() {
    int n, m, c;
    std::cin >> n >> m >> c;
    if (n == 0) return false;

    auto enc = [&](int v, int i) { return v * (m + 1) + i; };
    // 今いる頂点、選んだ辺の本数

    Graph<int> graph(n * (m + 1));
    for (int i = m; i--;) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;

        for (int i = 0; i <= m; ++i) {
            graph.span(true, enc(u, i), enc(v, i), w);
        }
        for (int i = 0; i + 1 <= m; ++i) {
            // 辺を選べば重みは0
            graph.span(true, enc(u, i), enc(v, i + 1), 0);
        }
    }

    auto ds = dijkstra(graph, enc(0, 0));

    for (int i = 0; i <= m; ++i) {
        if (ds[enc(n - 1, i)] <= c) {
            std::cout << i << "\n";
            break;
        }
    }
    return true;
}
