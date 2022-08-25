#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <atcoder/modint>

constexpr int M = 45;

namespace ac = atcoder;
using mint = ac::modint998244353;

// *(1 + ax)
void mul(std::vector<mint>& f, mint a) {
    if (a == 0) return;

    f.push_back(0);
    for (int i = (int)f.size() - 1; i > 0; --i) {
        f[i] += f[i - 1] * a;
    }
}

// /(1 + ax)
void div(std::vector<mint>& f, mint a) {
    if (a == 0) return;

    for (int i = 1; i < (int)f.size(); ++i) {
        f[i] -= f[i - 1] * a;
    }
    f.pop_back();
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    // 階乗の前計算
    std::vector<mint> facts(n + 1, 1);
    for (int i = 2; i <= n; ++i) facts[i] = facts[i - 1] * i;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;

    std::vector<std::pair<int, int>> ps(q);
    for (auto& [l, r] : ps) std::cin >> l >> r;

    // Mo's algorithm: クエリを並び替える
    std::vector<int> idxs(q);
    std::iota(idxs.begin(), idxs.end(), 0);
    std::sort(idxs.begin(), idxs.end(),
              [&](auto i, auto j) {
                  auto [li, ri] = ps[i];
                  auto [lj, rj] = ps[j];

                  if (li / M == lj / M) {
                      return ri < rj;
                  } else {
                      return li < lj;
                  }
              });

    int l = 0, r = 0;
    std::vector<mint> f{1};
    std::vector<int> cnt(n, 0);

    std::vector<mint> ans(q, 0);
    for (auto i : idxs) {
        auto [nl, nr] = ps[i];

        // extend
        while (nl < l) {
            --l;
            div(f, cnt[xs[l]]);
            ++cnt[xs[l]];
            mul(f, cnt[xs[l]]);
        }
        while (r < nr) {
            div(f, cnt[xs[r]]);
            ++cnt[xs[r]];
            mul(f, cnt[xs[r]]);
            ++r;
        }

        // shrink
        while (l < nl) {
            div(f, cnt[xs[l]]);
            --cnt[xs[l]];
            mul(f, cnt[xs[l]]);
            ++l;
        }
        while (nr < r) {
            --r;
            div(f, cnt[xs[r]]);
            --cnt[xs[r]];
            mul(f, cnt[xs[r]]);
        }

        for (int k = 0; k < (int)f.size(); ++k) {
            ans[i] += f[k] * facts[n - k] * mint(-1).pow(k);
        }
    }

    for (auto a : ans) std::cout << a.val() << "\n";
}
