#include <iostream>
#include <vector>
#include <atcoder/modint>

namespace ac = atcoder;

using mint0 = ac::dynamic_modint<0>;
using mint1 = ac::dynamic_modint<1>;

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;

    mint0::set_mod(n + 0);
    mint1::set_mod(n + 1);

    std::vector<mint0> prods(m + 1);  // 累積積
    prods[0] = 1;
    for (int i = 1; i <= m; ++i) {
        int d;
        std::cin >> d;
        prods[i] = prods[i - 1] * d;
    }

    // [0, len)の積を返す
    auto getprod = [&](int len) {
        return prods[m].pow(len / m) * prods[len % m];
    };

    while (q--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        --y;

        auto p = getprod(y + z) / getprod(y);
        std::cout << mint1(x).pow(p.inv().val()).val() << "\n";
    }
}
