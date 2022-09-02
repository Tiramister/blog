#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

template <class Cost = int>
struct Edge { ... };

struct UnionFind { ... };

using lint = long long;

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Edge<lint>> edges, xedges;
    // 重みが定数の辺とxの辺を分離
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u, --v;
        if (c == 0) {
            lint w;
            std::cin >> w;
            edges.emplace_back(u, v, w);
        } else {
            char w;
            std::cin >> w;
            xedges.emplace_back(u, v);
        }
    }

    std::sort(edges.begin(), edges.end());
    int l = edges.size();

    UnionFind uf(n), xuf(n);
    std::vector<lint> gnum(l + 1), cost(l + 1);
    gnum[0] = n, cost[0] = 0;
    // edgesのi本目まででKruskal

    std::vector<lint> xgnum(l + 1), xcost(l + 1);
    xgnum[0] = n, xcost[0] = 0;
    // xedgesを最初に使った状態で，edgesのi本目まででKruskal

    for (auto e : xedges) {
        if (xuf.same(e.src, e.dst)) continue;
        --xgnum[0];
        xuf.unite(e.src, e.dst);
    }

    for (int i = 1; i <= l; ++i) {
        gnum[i] = gnum[i - 1];
        cost[i] = cost[i - 1];
        xgnum[i] = xgnum[i - 1];
        xcost[i] = xcost[i - 1];

        auto e = edges[i - 1];
        if (!uf.same(e.src, e.dst)) {
            --gnum[i];
            cost[i] += e.cost;
            uf.unite(e.src, e.dst);
        }
        if (!xuf.same(e.src, e.dst)) {
            --xgnum[i];
            xcost[i] += e.cost;
            xuf.unite(e.src, e.dst);
        }
    }

    int q;
    std::cin >> q;
    for (int p = 0; p < q; ++p) {
        lint a;
        std::cin >> a;

        int i = std::lower_bound(edges.begin(), edges.end(),
                                 Edge<lint>(0, 0, a)) -
                edges.begin();
        // edgesをi本使った直後にxedgesが入る

        lint ans = cost[i] +
                   (gnum[i] - xgnum[i]) * a +
                   (xcost[l] - xcost[i]);
        // 減少した連結成分数 = xedgesから追加された辺数

        std::cout << ans << std::endl;
    }
    return 0;
}
