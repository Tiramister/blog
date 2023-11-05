---
title: "AtCoder Beginner Contest 149 E - Handshake"
date: 2019-12-29
tags: [atcoder]
---

[E - Handshake](https://atcoder.jp/contests/abc149/tasks/abc149_e)

## 問題

長さ $n$ の数列 $\\\{a\_i\\\}$ に対し，以下の操作を $m$ 回行う．最初スコアは $0$ である．

- $1 \\leq x, y \\leq n$ なる $x, y$ を任意に選ぶ．
  - ただし，既に選んだ $(x, y)$ の組を選ぶことはできない．
- $a\_x + a\_y$ をスコアに加算する．

最終的なスコアの最大値を求めよ．

### 制約

- $1 \\leq n \\leq 10\^5$
- $1 \\leq m \\leq n\^2$
- $1 \\leq a\_i \\leq 10\^5$

## 考察

以降 $\\\{a\_i\\\}$ は昇順とする．

愚直な解法として，「PriorityQueue に全ペアを突っ込んで大きい方から $m$ 個取る」というのが考えられる．しかしこのアルゴリズムの計算量は $O(n\^2 \\log n)$ なので，今回の制約では許されない．

そこで，この上から $m$ 番目の値( $S$ とおく)を二分探索することにする． $x$ を固定したときの $S$ 以下のペアの個数は， $\\\{a\_i\\\}$ 中で $S - a\_x$ 以下の要素の個数となる．これは二分探索により十分高速に求まる．したがって $S$ 以下のペアの個数は $O(n \\log n)$ で求まる．

この $S$ が求まれば，後は $\\\{a\_i\\\}$ の累積和を使うことで十分高速に $S$ 以下のペアの和が求まる．ただし $S$ 以下の要素が $m$ 個より多い場合もあるので，その場合は余剰分を引く必要がある．

## 実装例

[提出 #9224815 - AtCoder Beginner Contest 149](https://atcoder.jp/contests/abc149/submissions/9224815)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using lint = long long;
constexpr lint INF = std::numeric_limits<lint>::max();

int main() {
    int n;
    lint m;
    std::cin >> n >> m;

    std::vector<lint> as(n);
    for (auto& a : as) std::cin >> a;
    std::sort(as.begin(), as.end());

    // Sを二分探索
    lint ok = 0, ng = INF;
    while (ng - ok > 1) {
        lint mid = (ok + ng) / 2;

        lint cnt = 0;
        for (int i = 0; i < n; ++i) {
            // S-ai以下の要素の個数
            int r = as.end() - std::lower_bound(as.begin(), as.end(), mid - as[i]);
            cnt += r;
        }

        (cnt < m ? ng : ok) = mid;
    }

    // 累積和
    std::vector<lint> ss(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        ss[i + 1] = ss[i] + as[i];
    }

    lint ans = 0;
    for (int i = 0; i < n; ++i) {
        int r = as.end() - std::lower_bound(as.begin(), as.end(), ok - as[i]);
        m -= r;
        ans += ss[n] - ss[n - r] + as[i] * r;
        // 後ろr個の和 + aiをr個分
    }
    ans += ok * m;  // 余剰分を引く

    std::cout << ans << std::endl;
    return 0;
}
```

