---
title: "Educational Codeforces Round 79 F - New Year and Handle Change"
date: 2020-01-08
tags: [codeforces]
---

[Problem - F - Codeforces](https://codeforces.com/contest/1279/problem/F)

## 問題

$0, 1$ からなる長さ $n$ の数列 $\\\{ a\_i \\\}$ が与えられる．この数列に対して，以下の操作を $k$ 回まで行う．

- $\\\{ a\_i \\\}$ から長さ $l$ の連続部分列を選ぶ．
- その部分列を全て $0$ か全て $1$ に変える．

$s = \\sum a\_i$ としたとき， $\\min(s, n - s)$ の最小値を求めよ．

### 制約

- $1 \\leq l \\leq n \\leq 10\^6$
- $1 \\leq k \\leq 10\^6$

## 考察

$s$ を小さくすることにしてしまえば，極力多くの要素を $0$ にする問題になる．これを数列の $0, 1$ を反転させて 2 回解けばいい．

まずシンプルな解法として， $dp\_\{i, j\} =$ 「 $a[0, i]$ について， $j$ 回操作を行ったときの $s$ の最小値」という DP が考えられる．選ぶ部分列は重複しないようにするのが最善なので， $\\\{ a\_i \\\}$ を $l$ だけ $0$ でかさ増しすればこれは $O(n\^2)$ で計算できる．

これの計算量を落とすために， **Alien DP** というテクニックを使う．
簡単に説明すると，

- 操作回数を覚える代わりに，操作を 1 回行う毎にペナルティ $p$ を加えることにする．
- 最適解の操作回数は $p$ が大きいほど小さくなる．
- そこで最適解の操作回数が $k$ 回になるようなペナルティを二分探索すればいい．

という感じ．ただし $k$ 回が最適であるような $p$ が存在すること(この性質は凸性と呼ばれる)が必要で，．今回の問題はこれが満たされているらしい[^1]．

[^1]: [証明らしきコメント](https://codeforces.com/blog/entry/72577?#comment-568669)

## 実装例

以下の実装では，

- ペナルティに対する操作回数は最小のものを求める．
- ペナルティの上界と下界，二分探索のループ回数はかなり適当．

としている．また，ペナルティ 0 で操作回数が $k$ 回以下の場合はそれがそのまま答えになることに注意．

[Submission #68388249 - Codeforces](https://codeforces.com/contest/1279/submission/68388249)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using ldouble = long double;
constexpr int INF = 1 << 30;

int main() {
    int n, l, k;
    std::cin >> n >> k >> l;

    std::vector<int> xs(n);
    for (auto& x : xs) {
        char c;
        std::cin >> c;
        x = (std::islower(c) ? 1 : 0);
    }
    xs.insert(xs.begin(), 0);

    // penaltyを固定したときの，最小コストとパス回数の最小値
    auto calc = [&](ldouble pena) {
        static std::vector<std::pair<ldouble, int>> dp(n + l + 1);
        dp[0] = std::make_pair(0, 0);

        for (int i = 1; i <= n + l; ++i) {
            ldouble pdist;
            int cnt;
            std::tie(pdist, cnt) = dp[i - 1];
            if (i <= n) pdist += xs[i];
            dp[i] = std::make_pair(pdist, cnt);

            if (i >= l) {
                std::tie(pdist, cnt) = dp[i - l];
                ++cnt;
                auto nxt = std::make_pair(pdist + pena, cnt);
                dp[i] = std::min(dp[i], nxt);
            }
        }
        return dp.back();
    };

    int ans = INF;
    for (int i = 0; i < 2; ++i) {
        ldouble pena = 0;

        {
            int cnt;
            std::tie(std::ignore, cnt) = calc(pena);

            // pena=0でk回も使わないならそれが最適
            if (cnt > k) {
                ldouble ok = 1e9, ng = 0;
                // pena >= ok -> used <= k

                for (int q = 0; q < 100; ++q) {
                    ldouble mid = (ok + ng) / 2;
                    int pcnt;
                    std::tie(std::ignore, pcnt) = calc(mid);
                    (pcnt <= k ? ok : ng) = mid;
                }
                pena = ok;
            }
        }

        ldouble cost;
        std::tie(cost, std::ignore) = calc(pena);
        cost -= k * pena;

        int icost = cost + 1e-10;
        ans = std::min(ans, icost);

        // 全部反転してもう1回
        for (auto& x : xs) x = 1 - x;
    }

    std::cout << ans << std::endl;
    return 0;
}
```

