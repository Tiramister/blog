#include <iostream>
#include <numeric>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

using lint = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<lint> xs(n), ys(m);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    mint ans = 0;
    for (auto a : xs) {
        for (auto b : ys) {
            ans += a * b + a - b + std::gcd(a, b);
        }
    }

    std::cout << ans << "\n";
}
