#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

template <class Cost = int>
struct Centroid {
    Graph<Cost> graph;
    std::vector<bool> deleted;
    std::vector<int> sz;

    explicit Centroid(const Graph<Cost>& graph)
        : graph(graph), deleted(graph.size(), false), sz(graph.size()) {}

    // DFSで部分木のサイズを求める
    szdfs(int v, int p = -1) {
        sz[v] = 1;
        for (auto e : graph[v]) {
            if (e.dst == p || deleted[e.dst]) continue;
            sz[v] += szdfs(e.dst, v);
        }
        return sz[v];
    }

    int find(int v) {
        int n = szdfs(v);

        int p = -1;
        // 子の最大サイズがn/2以下になるまで，最大サイズの子に潜る
        while (true) {
            int nxt = -1;  // 最もサイズが大きい子
            for (auto e : graph[v]) {
                if (e.dst == p || deleted[e.dst]) continue;
                if (nxt == -1 || sz[e.dst] > sz[nxt]) nxt = e.dst;
            }

            if (nxt == -1 || sz[nxt] <= n / 2) return v;
            p = v;
            v = nxt;
        }
    }
};

void solve() {
    int n;
    std::cin >> n;

    Graph<> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        graph[u].emplace_back(u, v);
        graph[v].emplace_back(v, u);
    }

    Centroid<> cent(graph);
    std::queue<std::pair<int, int>> cents;
    cents.emplace(0, 0);
    // 次に探す連結成分中の1頂点と，その深さ

    std::vector<int> ans(n);
    while (!cents.empty()) {
        int r, d;
        std::tie(r, d) = cents.front();
        cents.pop();

        // 重心に割り当てて削除
        r = cent.find(r);
        ans[r] = d;
        cent.deleted[r] = true;

        // 各子の頂点から1つずつcentに突っ込む
        for (auto e : graph[r]) {
            if (cent.deleted[e.dst]) continue;
            cents.emplace(e.dst, d + 1);
        }
    }

    for (auto a : ans) {
        std::cout << char(a + 'A') << " ";
    }
    std::cout << std::endl;
}
