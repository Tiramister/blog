#include <iostream>
#include <algorithm>
#include <vector>

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> xs(n), ys(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    // A中の最右位置、B中の最左位置を求める
    std::vector<int> xr(n + 1, -1), yl(n + 1, -1);
    for (int i = 0; i < n; ++i) xr[xs[i]] = i;
    for (int i = n - 1; i >= 0; --i) yl[ys[i]] = i;

    // 最大のシフト幅を求める
    int d = 0;
    for (int i = 1; i <= n; ++i) {
        if (xr[i] == -1 || yl[i] == -1) continue;
        d = std::max(d, xr[i] - yl[i] + 1);
    }

    // シフトする
    std::rotate(ys.begin(), ys.begin() + n - d, ys.end());

    // 被り判定
    for (int i = 0; i < n; ++i) {
        if (xs[i] == ys[i]) {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";
    for (auto y : ys) std::cout << y << " ";
    std::cout << "\n";
}
