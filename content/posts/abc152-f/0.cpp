#include <iostream>
#include <vector>
#include <queue>

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

using lint = long long;

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

    // BFSでn-1を根とする根付き木に変換
    // iから親に伸びる辺の番号をiとする
    std::vector<int> par(n, -1);
    std::vector<lint> paths(n, 0);

    std::queue<int> que;
    que.push(n - 1);
    par[n - 1] = n - 1;

    while (!que.empty()) {
        int v = que.front();
        que.pop();

        for (auto e : graph[v]) {
            int u = e.dst;
            if (par[u] >= 0) continue;
            par[u] = v;
            paths[u] = (paths[v] | (1LL << u));
            que.push(u);
        }
    }

    int m;
    std::cin >> m;

    std::vector<lint> ss(m);
    // ui-vi間の辺の集合
    for (auto& s : ss) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        s = (paths[u] ^ paths[v]);
    }

    // 包除原理
    lint ans = 0;
    for (int b = 0; b < (1 << m); ++b) {
        int sign = (__builtin_popcount(b) % 2 == 0 ? 1 : -1);

        lint s = 0;  // 白で塗る辺の集合
        for (int i = 0; i < m; ++i) {
            if ((b >> i) & 1) s |= ss[i];
        }

        int free = n - 1 - __builtin_popcountll(s);
        ans += sign * (1LL << free);
    }

    std::cout << ans << std::endl;
}
