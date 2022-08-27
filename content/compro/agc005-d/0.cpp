#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 924844033;
using mint = ModInt<MOD>;
using mints = std::vector<mint>;

template <class T>
struct Combination { ... };

const Combination<mint> C(10000);

template <class T>
std::vector<T> vec(int len, T elem) { ... }

void solve() {
    int n, k;
    std::cin >> n >> k;

    mints pat(1, 1);
    // i個ルールを破るものの通り数
    for (int s = 0; s < k * 2; ++s) {
        auto dp = vec(2, vec(1, mint(0)));
        dp[0][0] = 1;
        // 直前で上を選んだか否か/i個ルールを破る

        for (int i = s; i < n; i += k * 2) {
            auto ndp = vec(2, vec(dp[0].size() + 1, mint(0)));

            for (int m = 0; m < (int)dp[0].size(); ++m) {
                // 何も選ばない
                ndp[0][m] += dp[0][m] + dp[1][m];

                // 下を選ぶ
                if (i >= k) ndp[0][m + 1] += dp[0][m];

                // 上を選ぶ
                if (i + k < n) ndp[1][m + 1] += dp[0][m] + dp[1][m];
            }

            std::swap(dp, ndp);
        }

        // 多項式の積でマージ
        int m = pat.size(), l = dp[0].size();
        mints npat(m + l - 1, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < l; ++j) {
                npat[i + j] += pat[i] * (dp[0][j] + dp[1][j]);
            }
        }

        std::swap(pat, npat);
    }

    // 包除
    mint ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += pat[i] * C.fact(n - i) * (i % 2 == 0 ? 1 : -1);
    }
    std::cout << ans << std::endl;
}
