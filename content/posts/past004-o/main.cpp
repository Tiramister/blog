#include <atcoder/segtree>
#include <iostream>
#include <numeric>
#include <vector>

using lint = long long;

lint min(lint a, lint b) { return std::min(a, b); }
lint inf() { return 1LL << 60; }

void solve() {
    int n, m;
    std::cin >> n >> m;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;
    lint sum = std::accumulate(xs.begin(), xs.end(), 0LL);

    std::vector<std::vector<std::pair<int, lint>>> segs(n + 1);
    // r毎に(l, c)をまとめたもの
    while (m--) {
        int l, r;
        lint c;
        std::cin >> l >> r >> c;
        segs[r].emplace_back(--l, c);
    }

    atcoder::segtree<lint, min, inf> seg(n + 1);
    // [0, i)におけるペナルティの最小値

    seg.set(0, 0);
    for (int r = 1; r <= n; ++r) {
        // 宝箱を開けない場合
        seg.set(r, seg.get(r - 1) + xs[r - 1]);

        // 鍵を使う場合
        for (auto [l, c] : segs[r]) {
            auto v = seg.prod(l, r) + c;
            seg.set(r, std::min(v, seg.get(r)));
        }
    }

    std::cout << sum - seg.get(n) << "\n";
}
