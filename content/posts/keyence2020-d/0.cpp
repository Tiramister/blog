#include <iostream>
#include <algorithm>
#include <vector>

template <class T>
std::vector<T> vec(int len, T elem) { ... }

constexpr int INF = 1 << 30;
constexpr int X = 50;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    auto dp = vec(1 << n, vec(X + 1, INF));
    dp[0][0] = 0;
    for (int b = 0; b < (1 << n); ++b) {
        int i = __builtin_popcount(b);

        for (int a = 0; a <= X; ++a) {
            for (int j = 0; j < n; ++j) {
                if ((b >> j) & 1) continue;

                // 表裏判定
                bool side = ((i - j) % 2 == 0);
                int x = (side ? xs[j] : ys[j]);
                if (x < a) continue;

                // 転倒数の計算
                int c = 0;
                for (int k = j + 1; k < n; ++k) {
                    if ((b >> k) & 1) ++c;
                }

                dp[b | (1 << j)][x] =
                    std::min(dp[b | (1 << j)][x], dp[b][a] + c);
            }
        }
    }

    int ans = *std::min_element(dp.back().begin(), dp.back().end());
    std::cout << (ans == INF ? -1 : ans) << std::endl;
}
