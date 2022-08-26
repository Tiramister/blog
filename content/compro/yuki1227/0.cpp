#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

template <class Cost = int>
struct Edge { ... };
template <class Cost = int>
struct Graph { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

Graph<> graph;
int sz;

std::vector<mint> dfs(int v, int p) {
    std::vector<mint> dp(sz, 1);

    for (auto e : graph[v]) {
        int u = e.dst;
        if (u == p) continue;

        auto cdp = dfs(u, v);
        for (int i = 0; i < sz; ++i) {
            // 子と根の差分が3の場合を掛け合わせる
            mint sum = 0;
            for (int j : {-3, 3}) {
                int ni = i + j;
                if (ni < 0 || sz <= ni) continue;
                sum += cdp[ni];
            }
            dp[i] *= sum;
        }
    }

    return dp;
}

void solve() {
    int n, k;
    std::cin >> n >> k;

    graph = Graph<>(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.span(false, --u, --v);
    }

    mint ans = 0;
    if (k < 6000) {
        // 小さい場合は普通にDP
        sz = k;
        auto dp = dfs(0, -1);
        for (int i = 0; i < k; ++i) ans += dp[i];

    } else {
        sz = 6000;
        auto dp = dfs(0, -1);

        for (int i = 0; i < 3000; ++i) ans += dp[i];
        ans *= 2;  // 上と下の分

        // 中央の分
        ans += mint(2).pow(graph.size() - 1) * (k - 6000);
    }

    std::cout << ans << "\n";
}
