#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

using lint = long long;

// modint
template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;


// graph
template <class Cost = int>
struct Edge { .. };

template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

// dijkstra
template <class T>
using MaxHeap = std::priority_queue<T>;
template <class T>
using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr lint INF = std::numeric_limits<lint>::max();

template <class Cost>
std::vector<Cost> dijkstra(const Graph<Cost>& graph, int s) { ... }

// main
void solve() {
    int n, m, k;
    lint l;
    std::cin >> n >> m >> k >> l;

    std::vector<int> ws(k);
    for (auto& w : ws) std::cin >> w;

    Graph<lint> graph(n);
    while (m--) {
        int u, v;
        lint d;
        std::cin >> u >> v >> d;
        graph[u].emplace_back(u, v, d);
        graph[v].emplace_back(v, u, d);
    }

    std::vector<std::vector<lint>> dist(k);
    for (int i = 0; i < k; ++i) dist[i] = dijkstra(graph, ws[i]);

    std::vector<int> cnt(1 << k, 0);
    // cnt[T] = T中の全ての街から距離l以内の街の数
    for (int v = 0; v < n; ++v) {
        int b = 0;
        for (int i = 0; i < k; ++i) {
            if (dist[i][v] <= l) b |= (1 << i);
        }
        ++cnt[b];
    }

    // 上位集合に対する高速ゼータ変換
    for (int i = 0; i < k; ++i) {
        for (int b = (1 << k) - 1; b >= 0; --b) {
            if ((b >> i) & 1) {
                cnt[b ^ (1 << i)] += cnt[b];
            }
        }
    }

    std::vector<mint> xs(1 << k);
    for (int b = 0; b < (1 << k); ++b) {
        // 選ばられるべきは，cnt[T]個の頂点集合の部分集合で空でないもの
        xs[b] = (mint(2).pow(cnt[b])).val - 1;
    }

    // 上位集合に対する高速メビウス変換
    for (int i = 0; i < k; ++i) {
        for (int b = 0; b < (1 << k) - 1; ++b) {
            if (((b >> i) & 1) == 0) {
                xs[b] -= xs[b | (1 << i)];
            }
        }
    }

    int ans = 0;
    for (int b = 0; b < (1 << k); ++b) {
        ans ^= xs[b].val;
    }

    std::cout << ans << std::endl;
}
