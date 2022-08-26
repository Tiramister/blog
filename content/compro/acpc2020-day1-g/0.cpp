#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;
constexpr lint INF = 1LL << 60;

void abort() {
    std::cout << "0\n";
    std::exit(0);
}

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    std::vector<lint> xsum(n + 1, 0);
    for (int i = 0; i < n; ++i) xsum[i + 1] = xsum[i] + xs[i];

    lint ans = INF;
    for (int i = 0; i + m <= n; ++i) {
        // x[i, i+m)を長さkに収める

        if (xs[i + m - 1] - xs[i] <= k) abort();

        // [ok, ok+k]にて、lout <= rout
        lint ok = xs[i], ng = xs[i + m - 1] - k;
        while (ng - ok > 1) {
            auto mid = (ok + ng) / 2;

            int lout = std::lower_bound(xs.begin(), xs.end(), mid) -
                       (xs.begin() + i);
            int rout = (xs.begin() + i + m) -
                       std::upper_bound(xs.begin(), xs.end(), mid + k);
            if (lout <= rout) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        // コストを求める
        int lout = std::lower_bound(xs.begin(), xs.end(), ok) -
                   (xs.begin() + i);
        int rout = (xs.begin() + i + m) -
                   std::upper_bound(xs.begin(), xs.end(), ok + k);
        auto lcost = lout * ok - (xsum[i + lout] - xsum[i]);
        auto rcost = (xsum[i + m] - xsum[i + m - rout]) - rout * (ok + k);

        ans = std::min(ans, lcost + rcost);
    }

    std::cout << ans << "\n";
}
