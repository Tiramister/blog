#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

template <int MOD>
class ModInt { ... };

template <class Data, class Operator>
class SegmentTree { ... };

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int d, f, t, n;
    std::cin >> d >> f >> t >> n;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;
    xs.insert(xs.begin(), 0);
    xs.push_back(d);

    SegmentTree<mint, mint> seg(
        n + 2, 0,
        [](mint a, mint b) { return a + b; },
        [](mint e, mint a) { return e; });

    seg.update(n + 1, 1);
    for (int i = n; i >= 0; --i) {
        int x = xs[i];
        int j = std::upper_bound(xs.begin(), xs.end(), x + f - t) - xs.begin();
        // (i, j): arbitrary chosen

        if (j == n + 2) {
            seg.update(i, (mint(2) ^ (j - i - 2)));
            continue;
        }

        int k = std::upper_bound(xs.begin(), xs.end(), x + f) - xs.begin();
        // [j, k): either of them is chosen

        seg.update(i, (mint(2) ^ (j - i - 1)) * seg.query(j, k));
    }

    std::cout << seg.query(0, 1) << std::endl;
    return 0;
}
