#include <iostream>
#include <array>
#include <atcoder/modint>

namespace ac = atcoder;

template <class T, int D>
struct Vector { ... };

template <class T, int D>
struct Matrix { ... };

using mint = ac::modint1000000007;
using Vec = Vector<mint, 3>;
using Mat = Matrix<mint, 3>;

mint calc(int n, int a) {
    Vec v;  // p, q, psum
    v[0] = 1;

    Mat m;
    m[0][0] = a, m[0][1] = mint(a) * a - 1;
    m[1][0] = 1, m[1][1] = a;
    m[2][0] = 1, m[2][2] = 1;

    auto psum = (m.pow(n) * v)[2];
    return psum * 2 - n;
}

void solve() {
    int a, l, r;
    std::cin >> a >> l >> r;

    auto ans = calc(r + 1, a) - calc(l, a);
    std::cout << ans.val() << "\n";
}
