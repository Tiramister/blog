#include <iostream>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { ... }

template <int MOD>
struct ModInt { ... };

template <class T>
struct Combination { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;
const Combination<mint> C(2000000);

void solve() {
    int n, m;
    std::cin >> n >> m;

    auto xss = vec(n + 1, vec(m + 1, 0));
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            std::cin >> xss[x][y];
        }
    }

    mint ans = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            int s = xss[x][y];

            // 最後が操作Aの場合
            ans += C.binom(x + y + s - 1, x) *
                   C.binom(y + s - 1, y);

            {
                // 最後が操作Bの場合
                int t = xss[x][y + 1];
                ans += C.binom(x + y, x) *
                       (C.binom(x + y + s, s - 1) -
                        C.binom(x + y + t, t - 1));
            }

            {
                // 最後が操作Cの場合
                int t = xss[x + 1][y];
                ans += C.binom(x + y, x) *
                       (C.binom(x + y + s, s - 1) -
                        C.binom(x + y + t, t - 1));
            }
        }
    }

    std::cout << ans << "\n";
}
