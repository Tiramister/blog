#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

template <class T>
struct Combination { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

const Combination<mint> C(20000000);

void solve() {
    int h, w, k;
    std::cin >> h >> w >> k;

    mint ans = C.perm(h + w, k) * k;  // (0, 0)
    for (int m = 1; m <= k; ++m) {
        // (x, 0), (0, y)
        ans += C.perm(h + w - 1, k - 1) * (h + w) * (k - m + 1);
    }
    for (int m = 2; m <= k; ++m) {
        // (x, y)
        ans += C.perm(h + w - 2, k - 2) * (m - 1) * 2 * h * w * (k - m + 1);
    }

    std::cout << ans << "\n";
}
