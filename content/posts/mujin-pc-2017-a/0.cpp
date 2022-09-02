#include <iostream>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int n;
    std::cin >> n;

    mint ans = 1;
    int cnt = 0;  // 今並んでいる石の数
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        if (x < cnt * 2 + 1) {
            // i番目の石も取り除けることに注意
            ans *= (cnt + 1);
            --cnt;
        }
        ++cnt;
    }

    while (cnt > 0) {
        ans *= cnt;
        --cnt;
    }

    std::cout << ans << std::endl;
    return 0;
}
