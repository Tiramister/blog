#include <iostream>
#include <map>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

void solve() {
    int n;
    std::cin >> n;

    // [L, R]に自由に移動できるときの通り数
    std::map<std::pair<int, int>, mint> dp;
    dp[std::make_pair(0, 0)] = 1;

    int pt = 0;  // 前の命令の時刻
    while (n--) {
        int t, l, r;
        std::cin >> t >> l >> r;

        std::map<std::pair<int, int>, mint> ndp;
        for (auto [p, v] : dp) {
            auto [pl, pr] = p;

            // 左右に引き伸ばす
            pl -= t - pt;
            pr += t - pt;

            {
                // 守らない場合
                auto q = std::make_pair(pl, pr);
                if (!ndp.count(q)) ndp[q] = 0;
                ndp[q] += v;
            }

            // 守る場合
            pl = std::max(pl, l);
            pr = std::min(pr, r);
            if (pr < pl) continue;

            {
                auto q = std::make_pair(pl, pr);
                if (!ndp.count(q)) ndp[q] = 0;
                ndp[q] += v;
            }
        }

        std::swap(dp, ndp);
        pt = t;
    }

    mint ans = 0;
    for (auto [p, v] : dp) ans += v;
    std::cout << ans - 1 << "\n";  // 空集合を引く
}
