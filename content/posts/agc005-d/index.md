---
title: "AtCoder Grand Contest 005 D - ~K Perm Counting"
date: 2020-02-18
tags: [atcoder]
---

[D - ~K Perm Counting](https://atcoder.jp/contests/agc005/tasks/agc005_d)

## 問題

整数 $n, k$ が与えられる．長さ $n$ の順列 $(p\_i)$ で，以下を満たすものの個数を求めよ．

- 任意の $i$ について， $|p\_i - i| \\neq k$ ．

### 制約

- $2 \\leq n \\leq 2 \\cdot 10\^3$
- $1 \\leq k \\leq n - 1$

## 考察

どう見ても包除原理なので包除原理で考える．

順列を二部グラフで見たとき，差の絶対値が $k$ になる辺を $x$ 本先に引いてしまえば，残りはどう繋いでもよい．よって各 $x$ 本の張り方に対して $(n - x)!$ 通りの順列が対応する．

後は $x$ 本の張り方の数え方だが，厄介なことに「 $(1)-(4)\'$ を結んだ後に $(7)-(4)\'$ は結べない」みたいな依存関係がある．よって普通に DP しようとすると，直前 $2k$ 個くらいについて「上に繋いだか？」を持つ必要がある．

しかしこの依存関係について考えてみると， $(i)-(i+k)\'-(i+2k)-\\cdots$ のようなジグザグのパス上にしか依存関係が存在しない．よって二部グラフの頂点をこのジグザグなパスに分解することで，各々を独立に解ける．

各々は「直前で上に繋いだか？」を状態として持つ DP で解けて，マージは多項式の積でできる．多項式の積を普通にやると TLE しそうだが，木の二乗 DP と全く同じ理由から計算量は $O(n\^2)$ に収まる．

## 実装例

[提出 #10062125 - AtCoder Grand Contest 005](https://atcoder.jp/contests/agc005/submissions/10062125)

```cpp
#include <iostream>
#include <vector>

template <int MOD>
struct ModInt { ... };

constexpr int MOD = 924844033;
using mint = ModInt<MOD>;
using mints = std::vector<mint>;

template <class T>
struct Combination { ... };

const Combination<mint> C(10000);

template <class T>
std::vector<T> vec(int len, T elem) { ... }

void solve() {
    int n, k;
    std::cin >> n >> k;

    mints pat(1, 1);
    // i個ルールを破るものの通り数
    for (int s = 0; s < k * 2; ++s) {
        auto dp = vec(2, vec(1, mint(0)));
        dp[0][0] = 1;
        // 直前で上を選んだか否か/i個ルールを破る

        for (int i = s; i < n; i += k * 2) {
            auto ndp = vec(2, vec(dp[0].size() + 1, mint(0)));

            for (int m = 0; m < (int)dp[0].size(); ++m) {
                // 何も選ばない
                ndp[0][m] += dp[0][m] + dp[1][m];

                // 下を選ぶ
                if (i >= k) ndp[0][m + 1] += dp[0][m];

                // 上を選ぶ
                if (i + k < n) ndp[1][m + 1] += dp[0][m] + dp[1][m];
            }

            std::swap(dp, ndp);
        }

        // 多項式の積でマージ
        int m = pat.size(), l = dp[0].size();
        mints npat(m + l - 1, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < l; ++j) {
                npat[i + j] += pat[i] * (dp[0][j] + dp[1][j]);
            }
        }

        std::swap(pat, npat);
    }

    // 包除
    mint ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += pat[i] * C.fact(n - i) * (i % 2 == 0 ? 1 : -1);
    }
    std::cout << ans << std::endl;
}

```
