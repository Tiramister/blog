#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <map>
#include <tuple>

template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template <class T>
std::map<T, int> compress(std::vector<T>& v) { ... }

struct UnionFind { ... };

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

template <class Cost>
std::vector<Cost> dijkstra(const Graph<Cost>& graph, int s) { ... }

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> xs[i] >> ys[i];
    }

    // 座圧
    for (int q = 0; q < 2; ++q) {
        auto nxs = xs;
        auto xrev = compress(nxs);
        for (auto& x : xs) x = xrev[x];
        std::swap(xs, ys);
    }

    // UnionFindでグループ分け
    std::vector<std::vector<int>> xvs(n), yvs(n);
    for (int i = 0; i < n; ++i) {
        xvs[xs[i]].push_back(i);
        yvs[ys[i]].push_back(i);
    }

    UnionFind uf(n);
    for (int q = 0; q < 2; ++q) {
        for (auto& vs : xvs) {
            for (int i = 0; i + 1 < (int)vs.size(); ++i) {
                uf.unite(vs[i], vs[i + 1]);
            }
        }
        std::swap(xvs, yvs);
    }

    // 各グループの領域を求める
    std::vector<int> lxs(n, n), rxs(n, -n), lys(n, n), rys(n, -n);
    for (int i = 0; i < n; ++i) {
        int g = uf.find(i);
        lxs[g] = std::min(lxs[g], xs[i]);
        rxs[g] = std::max(rxs[g], xs[i]);
        lys[g] = std::min(lys[g], ys[i]);
        rys[g] = std::max(rys[g], ys[i]);
    }

    int k = 1;
    while (k < n) k <<= 1;  // セグ木の長さ

    Graph<int> graph(n + k * 8);
    // [0   , n   ): 各グループ
    // [n   , n+2k): x座標 行き
    // [n+2k, n+4k): x座標 帰り
    // [n+4k, n+6k): y座標 行き
    // [n+6k, n+8k): y座標 帰り

    for (int t = 0; t < 2; ++t) {
        int base = n + t * k * 4;                // nかn+4k
        int lbase = base, rbase = base + k * 2;  // 行きと帰りの始点

        // セグ木の辺を張る
        for (int i = k - 1; i >= 1; --i) {
            for (int c = 0; c < 2; ++c) {
                graph.span(true, lbase + i, lbase + i * 2 + c, 0);
                graph.span(true, rbase + i * 2 + c, rbase + i, 0);
            }
        }

        // 行きから帰りへ辺を張る 重み1
        for (int i = k; i < k * 2; ++i) {
            graph.span(true, lbase + i, rbase + i, 1);
        }
    }

    // グループとセグ木の間
    for (int i = 0; i < n; ++i) {
        if (!uf.ispar(i)) continue;

        for (int t = 0; t < 2; ++t) {
            int base = n + t * k * 4;                // nかn+4k
            int lbase = base, rbase = base + k * 2;  // 行きと帰りの始点

            int l = lxs[i], r = rxs[i] + 1;  // [l, r)に辺を張る
            l += k, r += k;
            while (l < r) {
                if (l & 1) {
                    graph.span(true, i, lbase + l, 0);
                    graph.span(true, rbase + l, i, 0);
                    ++l;
                }
                if (r & 1) {
                    --r;
                    graph.span(true, i, lbase + r, 0);
                    graph.span(true, rbase + r, i, 0);
                }
                l >>= 1, r >>= 1;
            }

            std::swap(lxs[i], lys[i]);
            std::swap(rxs[i], rys[i]);
        }
    }

    auto ds = dijkstra(graph, uf.find(0));
    std::cout << ds[uf.find(n - 1)] << "\n";
}
