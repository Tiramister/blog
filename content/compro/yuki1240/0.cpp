#include <iostream>
#include <numeric>
#include <vector>

using lint = long long;
constexpr int K = 18;

// 自身とのxor畳み込み
void xor_convolution(std::vector<lint>& xs) {
    for (int i = 1; i < (1 << K); i <<= 1) {
        for (int b = 0; b < (1 << K); ++b) {
            if (b & i) continue;
            auto l = xs[b],
                 r = xs[b | i];
            xs[b] = l + r;
            xs[b | i] = l - r;
        }
    }

    for (auto& x : xs) x *= x;

    for (int i = 1; i < (1 << K); i <<= 1) {
        for (int b = 0; b < (1 << K); ++b) {
            if (b & i) continue;
            auto l = xs[b],
                 r = xs[b | i];
            xs[b] = l + r;
            xs[b | i] = l - r;
        }
    }

    for (auto& x : xs) x >>= K;
}

void solve() {
    int n, a;
    std::cin >> n >> a;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;

    lint tot;  // 全体の個数
    {
        int sz = 0;
        std::vector<lint> cnt(1 << K, 0);
        for (auto x : xs) {
            ++cnt[x];
            ++sz;
        }

        xor_convolution(cnt);
        cnt[0] -= sz;                 // 0にi=jなるものが含まれることに注意
        for (auto& c : cnt) c >>= 1;  // i>jを除外
        tot = std::accumulate(cnt.begin(), cnt.begin() + a, 0LL);
    }

    lint ans = 0;
    for (int k = 1; k < (1 << K); k <<= 1) {
        // lg(k)桁目が0であるもののみの個数
        lint num;

        {
            int sz = 0;
            std::vector<lint> cnt(1 << K, 0);
            for (auto x : xs) {
                if (x & k) continue;
                ++cnt[x];
                ++sz;
            }

            xor_convolution(cnt);
            cnt[0] -= sz;
            for (auto& c : cnt) c >>= 1;
            num = std::accumulate(cnt.begin(), cnt.begin() + a, 0LL);
        }

        ans += k * (tot - num);
    }

    std::cout << ans << "\n";
}
