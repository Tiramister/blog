---
title: "ICPC 2019 国内予選 D - 計数カウンタ"
date: 2020-09-02
tags: [icpc]
---

[1635 < ICPC Prelim < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1635)

## 問題

長さ $n$ の整数列 $\\\{ a\_i \\\}, \\\{ b\_i \\\}$ が与えられる。

以下の操作を繰り返して $\\\{ a\_i \\\}$ を $\\\{ b\_i \\\}$ に一致させるとき、最小の操作回数を求めよ。

- $1 \\leq l \\leq r \\leq n$ なる整数 $l, r$ を選ぶ。
- $a\_l, a\_\{l + 1\}, \\cdots, a\_r$ を 1 増やす。ただし値が $m$ を上回る場合は $1$ に戻る。

### 制約

- $1 \\leq n \\leq 10\^3$
- $1 \\leq m \\leq 10\^4$
- $1 \\leq a\_i, b\_i \\leq m$

## 考察

まず $c\_i = (b\_i - a\_i) \\bmod m$ とすると、「全て $0$ の数列を区間 1 加算によって $\\\{ c\_i \\\}$ と $\\bmod\{m\}$ で一致させる」という問題になる。

「作った区間をどこで閉じるかは保留にする」という考えのもと、以下のような DP が立つ。

$$
dp\_\{i, j\} = \\text\{$c\_i$まで処理した時点で、$j$個の区間が閉じ待ちのときの最小操作回数\}
$$

これでは $j$ の値が最大 $nm$ 程度になるので、状態数が $\\Theta(n\^2 m)$ となり厳しい。

しかしよく考えてみると、 $j$ 個の区間が閉じ待ちということは直前の要素は $+j$ されていることになる。つまり $j \\equiv c\_i \\pmod\{m\}$ なる $j$ のみ考えればいい。すると以下のような DP が立つ。

$$
dp\_\{i, j\} = \\text\{$c\_i$まで処理した時点で、$jm + c\_i$個の区間が閉じ待ちのときの最小操作回数\}
$$

これなら状態数は $\\Theta(nm)$ となる。遷移は $j$ の差が高々 1 のものだけ考えればいいので、全体の計算量は $\\Theta(nm)$ となる。

## 実装例

遷移は $c\_i, c\_\{i+1\}$ の大小関係によって変わる。

[Run #4812557 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/1635/review/4812557/misteer/C++14)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

constexpr int INF = 1 << 30;

bool solve() {
    int n, m;
    std::cin >> n >> m;
    if (n == 0) return false;

    std::vector<int> xs(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& x : xs) {
        int y;
        std::cin >> y;
        x = y - x;
        if (x < 0) x += m;
    }

    // 開いている区間の数がm*i+x個のときの最小操作回数
    std::vector<int> dp(n + 1, INF);
    dp[0] = 0;

    int p = 0;
    for (auto x : xs) {
        if (x == p) continue;

        std::vector<int> ndp(n + 1, INF);
        if (p < x) {
            int d = x - p;
            for (int i = 0; i <= n; ++i) {
                // produce
                ndp[i] = std::min(ndp[i], dp[i] + d);
                // consume
                if (i < n) ndp[i] = std::min(ndp[i], dp[i + 1]);
            }

        } else {
            int d = x - p + m;
            for (int i = 0; i <= n; ++i) {
                // produce
                if (i > 0) ndp[i] = std::min(ndp[i], dp[i - 1] + d);
                // consume
                ndp[i] = std::min(ndp[i], dp[i]);
            }
        }

        std::swap(dp, ndp);
        p = x;
    }

    std::cout << *std::min_element(dp.begin(), dp.end()) << "\n";

    return true;
}
```

