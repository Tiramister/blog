#include <iostream>
#include <vector>

using lint = long long;

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

constexpr int N = 2000000;

void solve() {
    mint p;
    std::cin >> p;

    std::vector<mint> xs(N + 1, 0);
    xs[4] = 1;
    for (int i = 5; i <= N; ++i) {
        xs[i] = xs[i - 1] * p * 2 - xs[i - 2] * (p * p - 2) -
                xs[i - 3] * p * 2 - xs[i - 4];
    }

    int q;
    std::cin >> q;
    while (q--) {
        int n;
        std::cin >> n;
        std::cout << xs[n] << std::endl;
    }
}
