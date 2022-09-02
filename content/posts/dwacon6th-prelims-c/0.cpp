#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

template <class T>
struct Combination { ... };

const Combination<mint> C(10000);

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }


int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> xs(k);
    for (auto& x : xs) std::cin >> x;

    auto dp = vec(k + 1, vec(n + 1, mint(0)));
    dp[k][0] = 1;
    for (int d = k - 1; d >= 0; --d) {
        for (int m = n; m >= 0; --m) {
            for (int l = 0; l <= m; ++l) {
                dp[d][m] += dp[d + 1][m - l] * C.comb(m, l) * C.comb(n - l, xs[d] - l);
            }
        }
    }

    std::cout << dp[0][n] << std::endl;
    return 0;
}
