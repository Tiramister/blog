#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

template <class T>
std::vector<T> vec(int len, T elem) { return std::vector<T>(len, elem); }

template <class T>
std::map<T, int> compress(std::vector<T>& v) { ... }

template <int MOD>
struct ModInt { ... };

template <class T>
struct Combination { ... };

constexpr int MOD = 998244353;
using mint = ModInt<MOD>;

const Combination<mint> C(500000);

using lint = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;

    // 時間毎に頂点を管理
    std::vector<std::vector<int>> ins(n + 1), outs(n + 1);
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        ins[l].push_back(i);
        outs[r].push_back(i);
    }

    std::vector<std::pair<int, int>> es(m);
    std::vector<int> vs;  // 非孤立点
    for (auto& [u, v] : es) {
        std::cin >> u >> v;
        vs.push_back(--u);
        vs.push_back(--v);
    }

    auto vrev = compress(vs);
    int k = vrev.size();
    for (auto& [u, v] : es) u = vrev[u], v = vrev[v];

    // 非孤立点からx個選ぶ場合の数
    std::vector<mint> ind(k + 1);

    // 選べる非孤立点の集合sによって、indを再計算
    auto calc_ind = [&](lint s) {
        std::fill(ind.begin(), ind.end(), 0);

        for (int b = 0; b < (1 << m); ++b) {
            lint t = 0;  // 必ず選ぶことになる頂点集合
            for (int i = 0; i < m; ++i) {
                if ((~b >> i) & 1) continue;
                auto [u, v] = es[i];
                t |= 1LL << u;
                t |= 1LL << v;
            }

            if (~s & t) continue;  // s以外の頂点を選ぶことになった場合は該当なし

            int used = __builtin_popcountll(s & t);  // 「選ぶ」で固定されたもの
            int cnt = __builtin_popcountll(s & ~t);  // 「選ぶ・選ばない」を選べるもの

            mint sign = mint(-1).pow(__builtin_popcount(b));
            for (int z = 0; z <= cnt; ++z) {
                ind[z + used] += sign * C.binom(cnt, z);
            }
        }
    };

    mint ans = 0;
    int num = 0;    // 孤立点の個数
    lint mask = 0;  // 非孤立点の集合
    calc_ind(mask);

    for (int x = 1; x <= n; ++x) {
        // 追加処理
        for (auto v : ins[x]) {
            if (vrev.count(v)) {
                mask ^= 1LL << vrev[v];
                calc_ind(mask);
            } else {
                ++num;
            }
        }

        for (int z = 0; z <= k; ++z) {
            // 孤立点からx-z個、非孤立点からz個選ぶ
            ans += C.binom(num, x - z) * ind[z];
        }

        // 削除処理
        for (auto v : outs[x]) {
            if (vrev.count(v)) {
                mask ^= 1LL << vrev[v];
                calc_ind(mask);
            } else {
                --num;
            }
        }
    }

    std::cout << ans << "\n";
}
