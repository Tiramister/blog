#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using lint = long long;
constexpr lint INF = std::numeric_limits<lint>::max();

int main() {
    int n;
    lint m;
    std::cin >> n >> m;

    std::vector<lint> as(n);
    for (auto& a : as) std::cin >> a;
    std::sort(as.begin(), as.end());

    // Sを二分探索
    lint ok = 0, ng = INF;
    while (ng - ok > 1) {
        lint mid = (ok + ng) / 2;

        lint cnt = 0;
        for (int i = 0; i < n; ++i) {
            // S-ai以下の要素の個数
            int r = as.end() - std::lower_bound(as.begin(), as.end(), mid - as[i]);
            cnt += r;
        }

        (cnt < m ? ng : ok) = mid;
    }

    // 累積和
    std::vector<lint> ss(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ss[i + 1] = ss[i] + as[i];
    }

    lint ans = 0;
    for (int i = 0; i < n; ++i) {
        int r = as.end() - std::lower_bound(as.begin(), as.end(), ok - as[i]);
        m -= r;
        ans += ss[n] - ss[n - r] + as[i] * r;
        // 後ろr個の和 + aiをr個分
    }
    ans += ok * m;  // 余剰分を引く

    std::cout << ans << std::endl;
    return 0;
}
