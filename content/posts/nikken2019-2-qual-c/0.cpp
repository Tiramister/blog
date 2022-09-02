#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

struct UnionFind { ... };

void fail() { ... }
void succ() { ... }

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (auto& x : a) std::cin >> x;
    for (auto& x : b) std::cin >> x;

    {
        // bを昇順にする
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(),
                  [&](int i, int j) { return b[i] < b[j]; });

        auto oa = a, ob = b;
        for (int i = 0; i < n; ++i) {
            a[i] = oa[idx[i]];
            b[i] = ob[idx[i]];
        }
    }

    // そもそも達成可能か
    auto sa = a;
    std::sort(sa.begin(), sa.end());
    for (int i = 0; i < n; ++i) {
        if (sa[i] > b[i]) fail();
    }

    // 全体をソートしなくて良いか
    for (int i = 0; i + 1 < n; ++i) {
        if (sa[i + 1] <= b[i]) succ();
    }

    // 座圧して順列に変換
    std::map<int, int> reva;
    for (int i = 0; i < n; ++i) reva[sa[i]] = i;
    for (auto& x : a) x = reva[x];

    // 連結成分数でスワップ回数を判定
    UnionFind uf(n);
    for (int i = 0; i < n; ++i) uf.unite(i, a[i]);

    if (uf.gnum > 1) {
        succ();
    } else {
        fail();
    }
    return 0;
}
