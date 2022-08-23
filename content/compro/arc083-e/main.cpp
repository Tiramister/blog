#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
constexpr int INF = 1 << 30;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n);
    for (int v = 1; v < n; ++v) {
        int p;
        cin >> p;
        graph[--p].push_back(v);
    }

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    auto dfs = [&](auto &&f, int v) -> int {
        auto x = xs[v];

        // vの色の和がiのときの、もう一方の和の最小値
        vector<int> dp(x + 1, INF);
        dp[0] = 0;

        for (auto u : graph[v]) {
            auto y = xs[u],
                 z = f(f, u);

            vector<int> ndp(x + 1, INF);
            for (int q = 0; q < 2; ++q) {
                // yを黒、zを白にした場合の遷移
                for (int i = y; i <= x; ++i) {
                    ndp[i] = min(ndp[i], dp[i - y] + z);
                }
                swap(y, z);
            }
            swap(dp, ndp);
        }

        auto ret = *min_element(dp.begin(), dp.end());
        if (ret == INF) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
        return ret;
    };

    dfs(dfs, 0);
    cout << "POSSIBLE\n";
}
