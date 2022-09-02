#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T, class Int>
T ipow(T b, Int n) { ... }

int main() {
    int n, m;
    std::cin >> n >> m;
    mint ans = ipow(mint(2), m * 2);
    mint out = 0;

    std::vector<std::vector<mint>>
        dp(2, std::vector<mint>(n + 1, 0)),
        ndp(2, std::vector<mint>(n + 1));
    // 途中で青が0になったか, 赤の個数

    // 初期状態の和
    for (int r = 0; r <= n; ++r) {
        dp[r == n][r] = 1;
    }

    for (int i = 0; i < m; ++i) {
        out += dp[true][0] * ipow(mint(2), (m - i) * 2 - 1);
        // 矛盾した後は自由に並べられるので，後ろの係数がつく

        for (auto& v : ndp) {
            std::fill(v.begin(), v.end(), 0);
        }

        for (int b = 0; b < 2; ++b) {
            for (int r = 0; r <= n; ++r) {
                if (r > 0) {
                    // RB
                    ndp[b][r] += dp[b][r];
                    // RR
                    ndp[b][r - 1] += dp[b][r];
                }
                if (r < n) {
                    // 操作中に青玉が0になるかどうか
                    bool nb = b || (r == n - 1);
                    // BR
                    ndp[nb][r] += dp[b][r];
                    // BB
                    ndp[nb][r + 1] += dp[b][r];
                }
            }
        }
        std::swap(dp, ndp);
    }

    std::cout << ans - out * 2 << std::endl;
    return 0;
}
