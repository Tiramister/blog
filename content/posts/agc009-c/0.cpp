#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <limits>

template <int MOD>
class ModInt { ... };
template <class Data, class Operator>
class SegmentTree { ... };

using lint = long long;

constexpr int MOD = 1e9 + 7;
using mint = ModInt<MOD>;

int main() {
    int n;
    lint a, b;
    std::cin >> n >> a >> b;
    if (a < b) std::swap(a, b);
    // a >= b

    std::vector<lint> s(n);
    for (auto& x : s) std::cin >> x;

    std::vector<int> prevb(n);
    // [j, i]の任意の要素の差がb以上な最小のj
    prevb[0] = 0;
    for (int i = 1; i < n; ++i) {
        prevb[i] = (s[i] - s[i - 1] >= b ? prevb[i - 1] : i);
    }

    SegmentTree<mint, mint> seg(
        n, 0,
        [](mint a, mint b) { return a + b; },
        [](mint e, mint a) { return a + e; });
    // iがXに属する場合の数

    seg.update(0, 1);
    for (int i = 1; i < n; ++i) {
        int l = prevb[i - 1];
        int r = std::upper_bound(s.begin(), s.end(), s[i] - a) - s.begin();
        if (l - 2 < 0 || s[l] - s[l - 2] >= b) --l;
        // [l, r)を直前のXに属する要素として選択可能
        seg.update(i, seg.query(l, r));

        if (prevb[i - 1] == 0) {
            // [0, i)を全部Yに，iをXに入れられる
            seg.update(i, 1);
        }
    }

    // 最後のAに属する要素が置かれうる範囲
    int l = prevb[n - 1];
    if (l - 2 < 0 || s[l] - s[l - 2] >= b) --l;
    mint ans = seg.query(l, n);

    // 全部Yに入るケース
    if (l < 0) ++ans;

    std::cout << ans << std::endl;
    return 0;
}
