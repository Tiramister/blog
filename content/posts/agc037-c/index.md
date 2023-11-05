---
title: "AtCoder Grand Contest 037 C - Numbers on a Circle"
date: 2020-01-17
tags: [atcoder]
---

[C - Numbers on a Circle](https://atcoder.jp/contests/agc037/tasks/agc037_c)

## 問題

長さ $n$ の数列 $\\\{ a\_i \\\}, \\\{ b\_i \\\}$ が与えられる．今から $\\\{ a\_i \\\}$ に以下の操作を適用することで $\\\{ b\_i \\\}$ と一致させたい．

- $1 \\leq i \\leq n$ なる $i$ を 1 つ取る．$a\_i$ に $a\_\{i - 1\} + a\_\{i + 1\}$ を加える．
  - ただしインデックスは $\\bmod n$ で考える．

これが可能かどうか判定し，可能なら操作回数の最小値を出力せよ．

### 制約

- $3 \\leq n \\leq 2 \\cdot 10\^5$
- $1 \\leq a\_i, b\_i \\leq 10\^9 (= X)$

## 考察

逆から考えると，以下の問題と同値となる．

{{<framed>}}
$\\\{ b\_i \\\}$ に以下の操作を適用することで $\\\{ a\_i \\\}$ と一致させたい．

- $1 \\leq i \\leq n$ なる $i$ を 1 つ取る．$b\_i$ から $b\_\{i - 1\} + b\_\{i + 1\}$ を引く．

これが可能かどうか(以下略)
{{</framed>}}

ここで，操作が可能なのは $b\_i \\geq b\_\{i - 1\} + b\_\{i + 1\}$ を満たす $i$ のみである.
したがって、両隣に自分より大きい数がいる間は操作ができない．これにより，大きい数から順に操作していくことが最善策であることが分かる．

以上より，「$a\_i$ と $b\_i$ が一致していない $i$ を， $b\_i$ が大きい方から揃えていく」というアルゴリズムが考えられる．これは揃っていない $i$ を $b\_i$ と一緒に priority queue に入れるなどしてシミュレートできる．ただ愚直に引き算をしていると間に合わないので，適当に除算によって高速化する必要がある．

最後に計算量を見積もる. $b\_i$ から $b\_\{i - 1\} + b\_\{i + 1\}$ を引けるだけ引くと、最終的な $b\_i$ は元の半分以下になる. したがって 1 つの $i$ に対する操作回数は $O(\\log b\_i)$ となり、全体の計算量は $O(n \\log n \\log X)$ となる ($\\log n$ は priority queue の分)．

## 実装例

[提出 #9548175 - AtCoder Grand Contest 037](https://atcoder.jp/contests/agc037/submissions/9548175)

```cpp
#include <iostream>
#include <vector>
#include <queue>

template <class T>
using MaxHeap = std::priority_queue<T>;

using lint = long long;

void solve() {
    int n;
    std::cin >> n;

    std::vector<lint> xs(n), ys(n);
    for (auto& x : xs) std::cin >> x;
    for (auto& y : ys) std::cin >> y;

    MaxHeap<std::pair<lint, int>> heap;
    // 揃えたいものの(bi, i)
    for (int i = 0; i < n; ++i) {
        if (xs[i] < ys[i]) heap.emplace(ys[i], i);
    }

    lint cnt = 0;
    while (!heap.empty()) {
        int i = heap.top().second;
        heap.pop();

        int l = (i + n - 1) % n,
            r = (i + 1) % n;
        lint s = ys[l] + ys[r];
        lint d = ys[i] - xs[i];

        if (d % s == 0) {
            // 合わせられるので合わせる
            cnt += d / s;
            ys[i] = xs[i];
        } else {
            // 減らせるだけ減らす
            cnt += ys[i] / s;
            ys[i] %= s;

            // 操作ができない or 過剰に小さくなった
            if (s > d || ys[i] < xs[i]) {
                std::cout << -1 << std::endl;
                return;
            }

            // 再度チャレンジ
            heap.emplace(ys[i], i);
        }
    }

    std::cout << cnt << std::endl;
}
```

