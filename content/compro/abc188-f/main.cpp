#include <iostream>
#include <map>

using namespace std;
using lint = long long;

void solve() {
    lint x, y;
    cin >> x >> y;

    map<lint, lint> dp;
    auto dfs = [&](auto&& f, lint p) -> lint {
        if (dp.count(p)) return dp[p];

        auto& ret = dp[p];

        // 2で割らない場合
        ret = abs(p - x);

        // 2で割る場合
        for (int d = -1; d <= 1; ++d) {
            lint np = p + d;
            if (np < 0 || np % 2 != 0 ||
                np / 2 >= p) continue;
            // 最後の条件は無限ループを省くのに必要

            ret = min(ret, f(f, np / 2) + abs(d) + 1);
        }
        return ret;
    };

    cout << dfs(dfs, y) << "\n";
}
