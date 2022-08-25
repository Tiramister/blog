#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <functional>

template <class T>
struct SlidingWindow { ... };

using lint = long long;
constexpr lint INF = 1LL << 60;

void solve() {
    int n, l;
    std::cin >> n >> l;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    SlidingWindow<lint>
        sw([](auto a, auto b) { return a > b; });
    // [i-l, i)
    for (int i = 0; i < l; ++i) sw.push(xs[i]);

    std::vector<lint> dp(n + 1, -INF);
    auto maxdp = dp;  // [0, i)
    dp[0] = 0;
    std::fill(maxdp.begin(), maxdp.begin() + l + 1, 0);

    for (int i = l; i <= n; ++i) {
        if (i > l) dp[i] = dp[i - 1];

        dp[i] = std::max({dp[i],
                          dp[i - l] + sw.get(),
                          maxdp[i - l] + xs[i - 1]});

        if (i < n) {
            sw.push(xs[i]);
            sw.pop();
            maxdp[i + 1] = std::max(maxdp[i], dp[i]);
        }
    }

    std::cout << dp[n] << "\n";
}
