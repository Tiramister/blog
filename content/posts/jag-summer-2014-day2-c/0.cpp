#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;
    std::sort(xs.rbegin(), xs.rend());

    lint ans = 0;
    auto abort = [&]() {
        std::cout << ans << "\n";
        std::exit(0);
    };

    while (n > 0) {
        // xs[0] >= n - 1なら1つ下へ帰着
        auto f = xs.front();
        if (f < n - 1) break;

        ans += f;
        xs.erase(xs.begin());

        for (auto& x : xs) --x;
        while (!xs.empty() && xs.back() == 0) xs.pop_back();
        n = xs.size();
    }

    if (n == 0) abort();

    int m;
    std::vector<int> ys(n);

    auto dfs = [&](auto&& f, int i) -> void {
        if (i == n) abort();

        auto& y = ys[i];
        for (y = 0; y < (1 << m); ++y) {
            if (__builtin_popcount(y) != xs[i]) continue;

            bool flag = true;
            for (int j = 0; j < i; ++j) {
                if (__builtin_popcount(ys[j] & y) > 1) flag = false;
            }
            if (flag) f(f, i + 1);
        }
    };

    for (m = 1;; ++m) {
        ++ans;
        dfs(dfs, 0);
    }
}
