#include <iostream>
#include <vector>

void solve() {
    int k, x;
    std::cin >> k >> x;

    if (x == 0) {
        std::cout << "Yes\n"
                  << 1 << "\n"
                  << (k == 0 ? 1 : 0) << "\n";
        return;
    }

    if (k == 0) ++x;
    if (__builtin_popcount(x) != 1) {
        std::cout << "No\n";
        return;
    }

    int p = __builtin_ctz(x);

    std::vector<int> ans;

    // 線形独立なものを加える
    for (int i = 0; i < 5; ++i) ans.push_back(1 << i);

    // kが従属じゃなければ追加
    if (k >= (1 << 5)) ans.push_back(k);

    // 線形従属なものを追加
    for (int q = 0; q < p; ++q) ans.push_back(q);

    std::cout << "Yes\n"
              << ans.size() << "\n";
    for (auto a : ans) std::cout << a << " ";
    std::cout << "\n";
}
