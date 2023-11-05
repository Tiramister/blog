---
title: "AtCoder Beginner Contest 116 D - Various Sushi"
date: 2019-01-20
tags: [atcoder]
---

[D - Various Sushi](https://atcoder.jp/contests/abc116/tasks/abc116_d)

## 概要

$N$ 個の寿司がある。 $i$ 個目の種類は $t\_i$ で、美味しさは $d\_i$ である。

あなたはこの寿司から $K$ 個を選んで食べる。このとき、全体の美味しさは以下の 2 つの値の和で表される。

- 選んだ寿司の $d\_i$ の総和。
- $x$ 種類の寿司を選んだとき、 $x\^2$ 。

全体の美味しさの最大値を求めよ。

### 制約

- $1 \\leq K \\leq N \\leq 10\^5$
- $1 \\leq t\_i \\leq N$
- $1 \\leq d\_i \\leq 10\^9$

## 解説

まず $d\_i$ が大きい方から貪欲に選んでみる。これで $d\_i$ の総和は最大になるが、種類数 $x$ が最適とは限らない。

そこで、ここから種類数を増やしていく。種類数を増やすには、既に選んだ中から 1 つ捨てて、まだ選ばれていない種類から 1 つ選べばいい。

捨てるものは美味しさが最小のものを選ぶのが最善だが、種類数が減らないように気をつける必要がある。
つまりその種類最後の寿司の場合は、捨てずにスキップする。

一方で選ぶものは、その種類で美味しさが最大のものを選ぶべきである。
よって、美味しさが最大のものを貪欲に選んでいくのが最善となる。

## 実装例

[提出 #34692730 - AtCoder Beginner Contest 116](https://atcoder.jp/contests/abc116/submissions/34692730)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using lint = long long;

int main() {
  int n, k;
  cin >> n >> k;

  vector<pair<lint, int>> ps(n);
  for (auto& [d, t] : ps) {
    cin >> t >> d;
    --t;
  }
  sort(ps.rbegin(), ps.rend());

  vector<int> cnt(n, 0);
  lint sum = 0, kind = 0;
  for (int i = 0; i < k; ++i) {
    auto [d, t] = ps[i];
    sum += d;

    if (cnt[t] == 0) ++kind;
    ++cnt[t];
  }

  lint ans = sum + kind * kind;

  int l = k - 1, r = k;
  while (true) {
    // 減らす
    bool chosen = false;
    while (l >= 0) {
      auto [d, t] = ps[l--];

      // 種類数を減らさないように
      if (cnt[t] == 1) continue;

      sum -= d;
      --cnt[t];
      chosen = true;
      break;
    }
    if (!chosen) break;

    // 増やす
    chosen = false;
    while (r < n) {
      auto [d, t] = ps[r++];

      // 種類数が増えないならスルー
      if (cnt[t] != 0) continue;

      sum += d;
      ++cnt[t];
      ++kind;
      chosen = true;
      break;
    }
    if (!chosen) break;

    ans = max(ans, sum + kind * kind);
  }

  cout << ans << endl;
  return 0;
}
```
