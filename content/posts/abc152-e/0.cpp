#include <iostream>
#include <vector>
#include <map>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

std::map<int, int> factor(int x) {
    std::map<int, int> ret;

    for (int p = 2; p * p <= x; ++p) {
        if (x % p != 0) continue;
        ret[p] = 0;
        while (x % p == 0) {
            x /= p;
            ++ret[p];
        }
    }

    if (x > 1) ret[x] = 1;
    return ret;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> xs;
    std::vector<std::map<int, int>> facts(n);
    for (auto& fact : facts) {
        int x;
        std::cin >> x;
        fact = factor(x);
        xs.push_back(x);
    }

    // 素因数分解した状態でのLCM
    std::map<int, int> lcm = facts[0];
    for (int i = 1; i < n; ++i) {
        for (auto p : facts[i]) {
            // マージ
            if (!lcm.count(p.first)) lcm[p.first] = 0;
            lcm[p.first] = std::max(lcm[p.first], p.second);
        }
    }

    // 素因数分解から復元
    mint l = 1;
    for (auto p : lcm) {
        l *= mint(p.first).pow(p.second);
    }

    mint ans = 0;
    for (auto x : xs) ans += l / x;
    std::cout << ans << std::endl;
}
