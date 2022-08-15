#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <complex>

template <int MOD>
struct ModInt { ... };

template <int K>
struct FastFourierTransform { ... };

constexpr int MOD = 200003;
using mint = ModInt<MOD>;
const FastFourierTransform<20> FFT;

using lint = long long;

void solve() {
    // g^log[x] = x
    std::vector<int> log(MOD);
    mint g = 2;
    for (int i = 0; i < MOD - 1; ++i) {
        log[g.pow(i).val] = i;
    }

    std::vector<lint> cnt(MOD - 1, 0);

    int n;
    std::cin >> n;
    while (n--) {
        int a;
        std::cin >> a;
        if (a != 0) ++cnt[log[a]];
    }

    // FFTで畳み込む
    auto res = FFT.fft(cnt, cnt);

    lint ans = 0;
    for (int i = 0; i < (int)res.size(); ++i) {
        lint num = llround(res[i]);
        ans += g.pow(i).val * num;
    }

    // a_i * a_iを省く
    for (int i = 0; i < (int)cnt.size(); ++i) {
        lint num = llround(cnt[i]);
        ans -= g.pow(i * 2).val * num;
    }

    // i > jを省く
    ans /= 2;

    std::cout << ans << "\n";
}
