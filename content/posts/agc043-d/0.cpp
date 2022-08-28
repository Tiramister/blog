#include <iostream>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { ... }

struct ModInt { ... };

int ModInt::MOD;
using mint = ModInt;

void solve() {
    int n;
    std::cin >> n >> ModInt::MOD;

    auto dp = vec(n + 1, vec(n * 3 + 1, mint(0)));
    dp[0][0] = 1;

    for (int k = 0; k < n * 3; ++k) {
        for (int i = 0; i <= n; ++i) {
            dp[i][k + 1] += dp[i][k];

            if (i + 1 > n) continue;

            if (k + 2 <= n * 3) dp[i + 1][k + 2] +=
                                dp[i][k] * (k + 1);
            if (k + 3 <= n * 3) dp[i + 1][k + 3] +=
                                dp[i][k] * (k + 1) * (k + 2);
        }
    }

    mint ans = 0;
    for (int i = 0; i <= n; ++i) ans += dp[i][n * 3];
    std::cout << ans << "\n";
}
