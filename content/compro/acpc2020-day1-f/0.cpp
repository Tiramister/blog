#include <atcoder/maxflow>

namespace ac = atcoder;

#include <iostream>
#include <vector>
#include <map>

void solve() {
    int n, m;
    std::cin >> n >> m;

    int s = n * 2, g = n * 2 + 1;
    ac::mf_graph<int> graph(n * 2 + 2);

    std::vector<bool> exist;                 // 辺が存在するか
    std::map<std::pair<int, int>, int> eid;  // 辺のグラフ中におけるid

    auto add_edge = [&](int u, int v) {
        eid[std::make_pair(u, v)] = graph.add_edge(u, v, 1);
        exist.push_back(true);
    };

    for (int i = 0; i < n; ++i) {
        add_edge(s, i);
        add_edge(i + n, g);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        add_edge(u, v + n);
    }

    // 初期流量
    int f = graph.flow(s, g);

    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;

        if (eid.count({u, v + n})) {
            int i = eid[{u, v + n}];

            if (exist[i]) {
                // 辺iの容量を0にする
                if (graph.get_edge(i).flow == 1) {
                    // 押し戻す
                    --f;
                    graph.change_edge(eid[{s, u}], 1, 0);
                    graph.change_edge(eid[{v + n, g}], 1, 0);
                }
                graph.change_edge(i, 0, 0);

            } else {
                // 辺iの容量を1にする
                graph.change_edge(i, 1, 0);
            }
            exist[i] = !exist[i];

        } else {
            // 新たな辺を追加
            add_edge(u, v + n);
        }

        // 差分だけ流す
        f += graph.flow(s, g);

        std::cout << (f == n ? "Yes" : "No") << "\n";
    }
}
