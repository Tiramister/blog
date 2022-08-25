#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <queue>
#include <functional>
#include <atcoder/modint>

template <int K, class T>
struct PatternsMatching { ... };

using lint = long long;
using mint = atcoder::modint1000000007;

void solve() {
    int n;
    lint l, r;
    std::cin >> n >> l >> r;

    PatternsMatching<10, char> pm('0');
    {
        // 禁止数字列を列挙
        lint a = 1, b = 1;
        while (a <= r) {
            if (l <= a && a <= r)
                pm.add(std::to_string(a));
            lint s = a + b;
            b = a;
            a = s;
        }
    }

    pm.build();
    int m = pm.nodes.size();

    // Trieのノードを状態とするDP
    std::vector<mint> dp(m, 0);
    dp[0] = 1;
    auto ndp = dp;

    while (n--) {
        std::fill(ndp.begin(), ndp.end(), 0);

        for (int i = 0; i < m; ++i) {
            for (int d = 0; d < 10; ++d) {
                int j = pm.next(i, d);
                if (pm.nodes[j].matched) continue;
                ndp[j] += dp[i];
            }
        }

        std::swap(dp, ndp);
    }

    // 0を省くために-1する
    std::cout << (std::accumulate(dp.begin(), dp.end(), mint(0)) - 1).val() << "\n";
}
