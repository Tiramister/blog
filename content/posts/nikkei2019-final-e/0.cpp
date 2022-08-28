#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

void solve() {
    int n, k;
    std::cin >> n >> k;

    std::vector<mint> pat(n + 1);
    for (int l = 0; l <= n; ++l) {
        pat[l] = l < k ? 1 : mint(2).pow((l - k) * (l - k + 1) / 2);
    }

    std::vector<mint> just(n + 1, 0);
    just[0] = 1;
    for (int i = 1; i <= n; ++i) {
        just[i] = pat[i];
        for (int l = 0; l < i; ++l) {
            just[i] -= just[l] * pat[i - l - 1];
        }
    }

    std::cout << just[n] << std::endl;
}
