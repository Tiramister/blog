#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

template <class T, class Int>
T ipow(T b, Int n) { ... }

template <class T>
std::map<T, int> compress(std::vector<T>& v) { ... }

template <class Data, class Operator>
class SegmentTree { ... };

int main() {
    int n;
    std::cin >> n;
    std::vector<int> xs(n), ys(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> xs[i] >> ys[i];
    }

    std::vector<int> ps(n);
    // 座圧した結果のy座標からなる順列
    {
        auto xss = xs, yss = ys;
        auto revx = compress(xss);
        auto revy = compress(yss);
        for (int i = 0; i < n; ++i) {
            ps[revx[xs[i]]] = revy[ys[i]];
        }
    }

    // 加算更新 総和取得
    SegmentTree<int, int> seg(
        n, 0,
        [](int a, int b) { return a + b; },
        [](int e, int a) { return a + e; });

    std::vector<int> ld(n);
    // left and down
    for (int x = 0; x < n; ++x) {
        ld[x] = seg.query(0, ps[x]);
        seg.update(ps[x], 1);
    }

    mint ans = 0;
    for (int x = 0; x < n; ++x) {
        // 包除原理で(x, ps[x])を含む長方形の数を求める
        // 最後の-1は空集合の分
        mint pat = ipow(mint(2), n) -
                   (ipow(mint(2), x) + ipow(mint(2), n - x - 1) +
                    ipow(mint(2), ps[x]) + ipow(mint(2), n - ps[x] - 1)) +
                   (ipow(mint(2), ld[x]) +
                    ipow(mint(2), x - ld[x]) +
                    ipow(mint(2), ps[x] - ld[x]) +
                    ipow(mint(2), n - x - ps[x] + ld[x] - 1)) -
                   1;

        ans += pat;
    }

    std::cout << ans << std::endl;
    return 0;
}
