---
title: "みんなのプロコン 2019 予選 D - Ears"
date: 2019-02-10
tags: [atcoder]
---

[D - Ears](https://atcoder.jp/contests/yahoo-procon2019-qual/tasks/yahoo_procon2019_qual_d)

### 概要

$1$ から $L$ の番号が振られた箱がある。最初、全ての箱は空である。

また数直線上にいる Alice は、以下のルールに従って数直線上を移動する。

- $[0, L]$ の区間のみを移動する。
- 始点と終点の座標は整数である。
- 座標が整数の点でのみ折り返す。

ある整数 $i$ によって $i - 0.5$ と表せる座標を通過する度に、 Alice は箱 $i$ に石を 1 個入れる。

その後 Bob は以下の操作を好きなだけ行い、箱 $i$ に石が $A\_i$ 個入っているようにしたい。

- 1 つの箱から石を 1 つ取り除く。
- 1 つの箱に石を 1 つ入れる。

Bob が Alice の移動方法を自由に決められるとき、 Bob の最小の操作回数を求めよ。

#### 制約

- $1 \\leq L \\leq 2 \\times 10\^5$
- $1 \\leq A\_i \\leq 10\^9$

### 考察

石の入れ方について色々模索した結果、以下の区間が左から順に並んでいることが必要十分条件と分かる。区間は空であってもいい。

1. 何も置かない区間。
2. 偶数個の石が **少なくとも 1 つ** 置かれた区間。
3. 奇数個の石が置かれた区間。
4. 偶数個の石が **少なくとも 1 つ** 置かれた区間。
5. 何も置かない区間。

そこで、「今何番目の区間にいるか」を状態とする DP を考える。

$$
dp\_\{i, k\} =\\text\{$\\\{A\_1, \\dots, A\_i\\\}$ において、箱 $i$ が区間 $k$ に属するような石の置き方における最適解\}
$$

区間の個数を $K$ としたとき、この $dp$ は $O(KL)$ で埋まる。今回は $K=5$ なので、十分間に合う。

### 実装例

[提出 #34682264 - 「みんなのプロコン 2019」](https://atcoder.jp/contests/yahoo-procon2019-qual/submissions/34682264)

```cpp
#include <iostream>
#include <vector>

using namespace std;
using lint = long long;

const lint INF = 1LL << 50;

lint f(int k, lint a) {
  if (k == 2) {
    // 奇数の区間
    return (a + 1) % 2;
  } else if (k == 1 || k == 3) {
    // 偶数の区間
    // 0個は許されないことに注意
    return (a == 0 ? 2 : a % 2);
  } else {
    // 無の区間
    return a;
  }
}

int main() {
  int n;
  cin >> n;

  vector<lint> xs(n);
  for (auto& x : xs) cin >> x;

  vector<lint> dp(5, 0);
  for (auto x : xs) {
    // index を進める
    for (int k = 0; k < 5; ++k) dp[k] += f(k, x);
    // 区間変更
    for (int k = 1; k < 5; ++k) dp[k] = min(dp[k], dp[k - 1]);
  }

  cout << dp[4] << endl;
  return 0;
}
```

