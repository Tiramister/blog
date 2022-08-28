#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <tuple>

using lint = long long;

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Edges = std::vector<Edge<Cost>>;

struct UnionFind { ... };

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

void solve() {
    int n;
    lint d;
    std::cin >> n >> d;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    MinHeap<Edge<lint>> heap;
    std::queue<std::pair<int, int>> que;
    que.emplace(0, n);

    while (!que.empty()) {
        int l, r;
        std::tie(l, r) = que.front();
        que.pop();
        if (r - l <= 1) continue;

        // 区間を分割
        int m = (l + r) / 2;
        que.emplace(l, m);
        que.emplace(m, r);

        // 左右で最もコストが小さい頂点を探す
        int li = l;
        for (int i = l + 1; i < m; ++i) {
            if (xs[i] - i * d < xs[li] - li * d) li = i;
        }
        int ri = m;
        for (int i = m + 1; i < r; ++i) {
            if (xs[i] + i * d < xs[ri] + ri * d) ri = i;
        }

        // 辺を追加
        for (int i = l; i < m; ++i) {
            heap.emplace(i, ri, xs[i] + xs[ri] + (ri - i) * d);
        }
        for (int i = m; i < r; ++i) {
            heap.emplace(li, i, xs[li] + xs[i] + (i - li) * d);
        }
    }

    // Kruskal
    lint ans = 0;
    UnionFind uf(n);
    while (!heap.empty()) {
        auto e = heap.top();
        heap.pop();

        if (uf.same(e.src, e.dst)) continue;
        ans += e.cost;
        uf.unite(e.src, e.dst);
    }

    std::cout << ans << std::endl;
}
