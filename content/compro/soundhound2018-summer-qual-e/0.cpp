#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

template <class Cost = int>
struct Edge { ... };

template <class Cost = int>
using Edges = std::vector<Edge<Cost>>;

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

using lint = long long;
constexpr lint INF = 1LL << 50;

void solve() {
    int n, m;
    std::cin >> n >> m;

    Edges<lint> edges(m);
    Graph<lint> graph(n);
    for (auto& e : edges) {
        std::cin >> e.src >> e.dst >> e.cost;
        --e.src, --e.dst;

        graph[e.src].emplace_back(e.src, e.dst, e.cost);
        graph[e.dst].emplace_back(e.dst, e.src, e.cost);
    }

    // BFSで割り当てをする関数
    std::vector<lint> vs(n);
    std::vector<int> cs(n);
    auto paint = [&](lint w) {
        std::fill(cs.begin(), cs.end(), -1);
        vs[0] = w;
        cs[0] = 0;

        std::queue<int> que;
        que.push(0);

        while (!que.empty()) {
            int v = que.front();
            que.pop();

            for (auto e : graph[v]) {
                int u = e.dst;
                if (cs[u] != -1) continue;

                cs[u] = 1 - cs[v];
                vs[u] = e.cost - vs[v];
                que.push(u);
            }
        }
    };

    paint(0);
    bool bip = true, ok = true;
    for (auto e : edges) {
        if (cs[e.src] == cs[e.dst]) bip = false;
        if (vs[e.src] + vs[e.dst] != e.cost) ok = false;
    }

    if (bip) {
        // 各色の最小値を求める
        lint lmin = INF, rmin = INF;
        for (int v = 0; v < n; ++v) {
            if (cs[v] == 0) {
                lmin = std::min(lmin, vs[v]);
            } else {
                rmin = std::min(rmin, vs[v]);
            }
        }

        std::cout << (ok ? std::max(lmin + rmin - 1, 0LL) : 0) << std::endl;
    } else {
        // c(0)の候補を探す
        lint w = 0;
        for (auto e : edges) {
            if (cs[e.src] == cs[e.dst]) {
                w = std::abs(vs[e.src] + vs[e.dst] - e.cost);
                break;
            }
        }

        // 再度割り当てて判定
        paint(w / 2);
        ok = true;
        for (int v = 0; v < n; ++v) {
            if (vs[v] <= 0) ok = false;
        }
        for (auto e : edges) {
            if (vs[e.src] + vs[e.dst] != e.cost) ok = false;
        }

        std::cout << ok << std::endl;
    }
}
