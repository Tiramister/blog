#include <iostream>
#include <vector>
#include <cmath>

using ldouble = long double;

constexpr int N = 200000;
std::vector<ldouble> fsum;

void init() {
    fsum.resize(N);
    fsum[0] = 0;
    for (int i = 1; i < N; ++i) {
        fsum[i] = fsum[i - 1] + std::log(i);
    }
}

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    auto flush = fsum[n] - fsum[k] - fsum[n - k] + std::log(m);
    auto straight = std::log1p(n - k) + std::log(m) * k;

    std::cout << (flush < straight ? "Flush" : "Straight") << "\n";
}
