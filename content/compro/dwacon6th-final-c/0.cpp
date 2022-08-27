#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>

/* ----- Mod Int ----- */
template <int MOD>
struct ModInt { ... };
constexpr int MOD = 998244353;
using mint = ModInt<MOD>;
using mints = std::vector<mint>;

/* ----- NTT ----- */
template <int MOD, int Root>
struct NumberTheoreticalTransform { ... };
const NumberTheoreticalTransform<MOD, 3> NTT;

/* ----- Graph ----- */
template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
using Graph = std::vector<std::vector<Edge<Cost>>>;

/* ----- Centroid Decomposition ----- */
template <class Cost = int>
struct Centroid { ... };

/* ----- main ----- */
// priority queue用の比較関数
struct Compare {
    bool operator()(const mints& lhs, const mints& rhs) {
        return lhs.size() > rhs.size();
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
    std::queue<int> cents;  // 次見る部分木の代表点
    cents.push(0);
    std::vector<int> dist(n);  // BFS用

    mints distr(n, 0);
    while (!cents.empty()) {
        int r = cents.front();
        cents.pop();

        // 重心を探す
        r = cent.find(r);
        cent.deleted[r] = true;

        // 各部分木の距離分布 次数について昇順に格納
        std::priority_queue<mints, std::vector<mints>, Compare> polys;

        for (auto e : graph[r]) {
            if (cent.deleted[e.dst]) continue;
            cents.push(e.dst);

            // BFSで距離分布を求める
            mints poly(1, 0);
            std::queue<std::pair<int, int>> que;
            que.emplace(e.dst, r);
            dist[e.dst] = 1;

            while (!que.empty()) {
                int v, p;
                std::tie(v, p) = que.front();
                que.pop();

                while ((int)poly.size() <= dist[v]) poly.push_back(0);
                poly[dist[v]] += 1;

                for (auto f : graph[v]) {
                    if (p == f.dst || cent.deleted[f.dst]) continue;
                    dist[f.dst] = dist[v] + 1;
                    que.emplace(f.dst, v);
                }
            }
            polys.push(poly);
        }

        // 頂点数1の部分木を用意するとやりやすい
        mints acc(1, 1);

        while (!polys.empty()) {
            auto poly = polys.top();
            polys.pop();

            // 畳み込みして全体に加算
            auto prod = NTT.ntt(poly, acc);
            for (int d = 0; d < (int)prod.size(); ++d) {
                distr[d] += prod[d];
            }

            // 累積和にも加算
            while (acc.size() < poly.size()) acc.push_back(0);
            for (int d = 0; d < (int)poly.size(); ++d) {
                acc[d] += poly[d];
            }
        }
    }

    // 係数と共に畳み込み
    mint ans = 0;
    for (int d = 1; d < n; ++d) {
        ans += distr[d] * (d <= 2 ? 1 : mint(4) / (mint(d) * (d - 1)));
    }
    for (int d = 1; d < n; ++d) ans *= d;
    std::cout << ans << std::endl;
}
