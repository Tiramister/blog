---
title: "ACPC 2020 day1 G - 移動の最小化"
date: 2020-09-20
tags: [voluntary]
---

[3199 < VPC TUATPC < Challenges | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/challenges/sources/VPC/TUATPC/3199)

## 問題

数直線上に $N$ 個の点があり、 $i$ 番目の座標は $x\_i$ である。

いくつかの点を移動させて、点が $M$ 個ある長さ $K$ の区間が存在するようにする。
移動距離の総和の最小値を求めよ。

### 制約

- $2 \\leq M \\leq N \\leq 10\^5$
- $1 \\leq K \\leq 10\^9$
- $0 \\leq x\_1 \\lt \\cdots \\lt x\_N \\leq 10\^9$

## 考察

点 $x\_i, \\cdots, x\_\{i+M-1\}$ を長さ $K$ の区間に収めることを考える。
これを各 $i$ について高速に処理できればよい。

ここで極端な例として、 $K=0$ 、つまり全ての点を 1 点に集める場合を考える[^zero]。
これは [この問題](https://atcoder.jp/contests/arc100/tasks/arc100_a) にもあるように、集める地点を $x\_i, \\cdots, x\_\{i+M-1\}$ の中央値にするのが最善となる。

[^zero]: このケースは制約には存在しない。

これを一般の $K$ にも適用すると、区間から左・右にはみ出した点の個数が釣り合うところが最善となる。
この区間の位置は、二分探索により求めることができる。
そして区間を固定した後の移動距離も、 $(x\_i)$ の累積和を使うことで求められる。

## 実装例

[Run #4856261 < misteer < Solutions | Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/solutions/problem/3199/review/4856261/misteer/C++17)

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using lint = long long;
constexpr lint INF = 1LL << 60;

void abort() {
    std::cout << "0\n";
    std::exit(0);
}

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<lint> xs(n);
    for (auto& x : xs) std::cin >> x;

    std::vector<lint> xsum(n + 1, 0);
    for (int i = 0; i < n; ++i) xsum[i + 1] = xsum[i] + xs[i];

    lint ans = INF;
    for (int i = 0; i + m <= n; ++i) {
        // x[i, i+m)を長さkに収める

        if (xs[i + m - 1] - xs[i] <= k) abort();

        // [ok, ok+k]にて、lout <= rout
        lint ok = xs[i], ng = xs[i + m - 1] - k;
        while (ng - ok > 1) {
            auto mid = (ok + ng) / 2;

            int lout = std::lower_bound(xs.begin(), xs.end(), mid) -
                       (xs.begin() + i);
            int rout = (xs.begin() + i + m) -
                       std::upper_bound(xs.begin(), xs.end(), mid + k);
            if (lout <= rout) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        // コストを求める
        int lout = std::lower_bound(xs.begin(), xs.end(), ok) -
                   (xs.begin() + i);
        int rout = (xs.begin() + i + m) -
                   std::upper_bound(xs.begin(), xs.end(), ok + k);
        auto lcost = lout * ok - (xsum[i + lout] - xsum[i]);
        auto rcost = (xsum[i + m] - xsum[i + m - rout]) - rout * (ok + k);

        ans = std::min(ans, lcost + rcost);
    }

    std::cout << ans << "\n";
}
```

