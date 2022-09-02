#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

template <class T>
std::vector<T> vec(int len, T elem) { ... }

int main() {
    mint n, m;
    int k;
    std::cin >> n >> m >> k;

    auto dp = vec(k + 1, vec(k + 1, mint(0)));
    dp[0][0] = 1;
    // i-tuple with j distinct elements

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i + 1][j + 1] += dp[i][j] * (n - j);
            dp[i + 1][j] += dp[i][j] * j;
        }
    }

    mint ans = 0;
    for (int j = 0; j <= k; ++j) {
        ans += dp[k][j] * (m.inv().pow(j));
    }

    std::cout << ans << std::endl;
    return 0;
}
