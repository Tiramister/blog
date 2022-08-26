#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 1000000007;
using mint = ModInt<MOD>;

using lint = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;

    // メビウス関数とエラトステネスの篩
    std::vector<int> mu(k + 1, 1);
    std::vector<bool> isp(k + 1, true);
    for (int p = 2; p <= k; ++p) {
        if (!isp[p]) continue;

        for (int q = p; q <= k; q += p) {
            mu[q] = -mu[q];
            isp[q] = false;
        }

        if (lint(p) * p > k) continue;
        for (int q = p * p; q <= k; q += p * p) mu[q] = 0;
    }

    // 約数の集合
    std::vector<std::vector<int>> ds(k + 1);
    for (int p = 1; p <= k; ++p) {
        if (mu[p] == 0) continue;
        for (int q = p; q <= k; q += p) ds[q].push_back(p);
    }

    // nべき
    std::vector<mint> npow(k + 1);
    for (int p = 0; p <= k; ++p) npow[p] = mint(p).pow(n);

    mint ans = 0, sum = 0;
    std::vector<mint> fs(k + 1, 0);
    for (int g = 1; g <= k; ++g) {
        for (auto x : ds[g]) {
            sum -= fs[x] * mu[x];
            fs[x] = npow[g / x];
            sum += fs[x] * mu[x];
        }
        ans += (sum.val ^ g);
    }

    std::cout << ans << "\n";
}
