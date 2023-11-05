---
title: "Codeforces Global Round 1 D - Jongmah"
date: 2019-02-08
tags: [codeforces]
---

[Problem - D - Codeforces](https://codeforces.com/contest/1110/problem/D)

## 概要

$m$ 以下の正整数が書かれた $n$ 個の牌がある。 $i$ 個目の牌には $a\_i$ と書かれている。

このとき、以下の 2 種類の 3 枚組を合わせて最大何組作れるか求めよ。ただし 1 つの牌は 1 つの組にしか含めてはならない。

- **刻子**: 同じ数が書かれた牌 3 枚からなる組。
- **順子**: ある正整数 $k$ について、 $(k, k + 1, k + 2)$ が書かれた牌それぞれ 1 枚からなる組。

### 制約

- $1 \\leq n, m \\leq 10\^6$
- $1 \\leq a\_i \\leq m$

## 考察

数が小さい方から組み方を決める DP をしたくなるが、順子のせいで $k - 2, k - 1$ の枚数まで状態として持たなければならない。

しかし実のところ、 $k$ を含む順子は 7 組以上組む必要がない。7 組以上ある場合、鳩の巣原理から
$(k - 2, k - 1, k), (k - 1, k, k + 1), (k, k + 1, k + 2)$ のいずれかの組は 3 組以上ある。しかし同じ順子 3 組は刻子 3 組に置き換えられる。

よって $k - 2, k - 1$ の枚数は 6 枚以下のケースのみを考えればいい[^1]。これで DP の状態数が $49 m$ に落ちて間に合う。

[^1]: 厳密には $k - 2$ は 2 枚以下、 $k - 1$ は 4 枚以下のケースのみを考えればいい。

## 実装例

[Submission #171293203 - Codeforces](https://codeforces.com/contest/1110/submission/171293203)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int INF = 1 << 30;

int main() {
  int n, m;
  cin >> n >> m;

  // 最後にオーバーランするために、 m + 2 まで含める
  vector<int> cnt(m + 2, 0);
  while (n--) {
    int a;
    cin >> a;
    ++cnt[--a];  // 0-indexedに変換
  }

  // 前2つの枚数を持つ
  auto dp = vector(7, vector(7, -INF));
  dp[0][0] = 0;

  for (auto c : cnt) {
    auto ndp = vector(7, vector(7, -INF));

    for (int p = 0; p <= 6; ++p) {
      for (int q = 0; q <= 6; ++q) {
        // 以降のために残す枚数
        for (int r = 0; r <= min(c, 6); ++r) {
          for (int shuntsu = 0; shuntsu <= min({p, q, c - r}); ++shuntsu) {
            int kotsu = (c - r - shuntsu) / 3;  // 作れる刻子の数
            ndp[q - shuntsu][r] = max(ndp[q - shuntsu][r], dp[p][q] + shuntsu + kotsu);
          }
        }
      }
    }

    swap(dp, ndp);
  }

  cout << dp[0][0] << endl;
  return 0;
}
```

