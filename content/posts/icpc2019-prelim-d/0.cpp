#include <iostream>
#include <algorithm>
#include <vector>

constexpr int INF = 1 << 30;

bool solve() {
    int n, m;
    std::cin >> n >> m;
    if (n == 0) return false;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& x : xs) {
        int y;
        std::cin >> y;
        x = y - x;
        if (x < 0) x += m;
    }

    // 開いている区間の数がm*i+x個のときの最小操作回数
    std::vector<int> dp(n + 1, INF);
    dp[0] = 0;

    int p = 0;
    for (auto x : xs) {
        if (x == p) continue;

        std::vector<int> ndp(n + 1, INF);
        if (p < x) {
            int d = x - p;
            for (int i = 0; i <= n; ++i) {
                // produce
                ndp[i] = std::min(ndp[i], dp[i] + d);
                // consume
                if (i < n) ndp[i] = std::min(ndp[i], dp[i + 1]);
            }

        } else {
            int d = x - p + m;
            for (int i = 0; i <= n; ++i) {
                // produce
                if (i > 0) ndp[i] = std::min(ndp[i], dp[i - 1] + d);
                // consume
                ndp[i] = std::min(ndp[i], dp[i]);
            }
        }

        std::swap(dp, ndp);
        p = x;
    }

    std::cout << *std::min_element(dp.begin(), dp.end()) << "\n";

    return true;
}
