#include <iostream>
#include <vector>

template <class T>
struct ConvexHullTrick { ... };

using lint = long long;
constexpr lint INF = 1 << 30;

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::pair<lint, lint>> ps(n);
    for (auto& [l, r] : ps) std::cin >> l;
    for (auto& [l, r] : ps) std::cin >> r;

    ConvexHullTrick<lint> cht;
    lint ans = -INF;

    for (int i = 0; i < n; ++i) {
        auto [l, r] = ps[i];
        cht.add(i, r);
        if (i == 0) continue;

        lint ok = INF, ng = ans - 1;  // 二分探索の下界をansに
        while (ok - ng > 1) {
            lint x = (ok + ng) / 2;

            if (l - x * i <= cht(-x)) {
                ok = x;
            } else {
                ng = x;
            }
        }

        ans = ok;
        std::cout << ans << "\n";
    }
}
