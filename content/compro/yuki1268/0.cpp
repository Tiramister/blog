#include <iostream>
#include <set>
#include <map>

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::set<lint> xs, ks;
    while (n--) {
        lint x;
        std::cin >> x;

        xs.insert(x);
        ks.insert(x);
        ks.insert(x + 1);
    }

    lint ans = 0;
    std::map<lint, lint> dp;  // sumがF_kになる選び方の総数

    for (auto k : ks) {
        auto& pat = dp[k];
        pat = 0;

        // F_k単体
        if (xs.count(k)) ++pat;

        // F_{k-1}を使いF_{k-2}に帰着
        if (xs.count(k - 1) &&
            dp.count(k - 2)) pat += dp[k - 2];

        ans += pat;
    }

    std::cout << ans << "\n";
}
