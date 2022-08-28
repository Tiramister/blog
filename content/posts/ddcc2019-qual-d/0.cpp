#include <iostream>
#include <numeric>
#include <vector>

using lint = long long;

constexpr int X = 30;

void solve() {
    std::vector<lint> rs(X + 1);
    for (int d = 2; d <= X; ++d) std::cin >> rs[d];

    lint g = 1, r = 0;  // n % g = r
    for (int d = 2; d <= X; ++d) {
        // d-1通りを全探索
        for (int i = 0; i < d - 1; ++i) {
            if (r % (d - 1) == rs[d] % (d - 1)) break;
            r += g;
        }

        if (r % (d - 1) != rs[d] % (d - 1)) {
            std::cout << "invalid\n";
            return;
        }

        g = std::lcm(g, d - 1);
    }

    if (r > 1000000000000) {
        std::cout << "invalid\n";
        return;
    }

    // チェック
    for (int d = 2; d <= X; ++d) {
        lint n = r, sum = 0;
        while (n > 0) {
            sum += n % d;
            n /= d;
        }
        if (sum != rs[d]) {
            std::cout << "invalid\n";
            return;
        }
    }

    std::cout << r << "\n";
}
